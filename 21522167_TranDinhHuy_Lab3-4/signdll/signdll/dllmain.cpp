// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
//digital-sign-1.cpp
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h> // Include for SHA256
#include <iostream>
#include <fstream>
#include <vector> // Include for std::vector
#include <iterator> // Include for std::istreambuf_iterator

extern "C" {
    __declspec(dllexport) bool signPdf(const char* privateKeyPath, const char* pdfPath, const char* signaturePath);
}

bool signPdf(const char* privateKeyPath, const char* pdfPath, const char* signaturePath) {
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    // Read the private key
    BIO* bio = BIO_new(BIO_s_file());
    BIO_read_filename(bio, privateKeyPath);
    EVP_PKEY* privateKey = PEM_read_bio_PrivateKey(bio, NULL, NULL, NULL);
    BIO_free(bio);
    if (!privateKey) {
        std::cerr << "Error reading private key." << std::endl;
        ERR_print_errors_fp(stderr);
        return false;
    }

    // Create a buffer to hold the document hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    std::ifstream pdfFile(pdfPath, std::ios::binary);
    if (!pdfFile.is_open()) {
        std::cerr << "Error opening PDF file." << std::endl;
        return false;
    }
    std::vector<unsigned char> pdfContents((std::istreambuf_iterator<char>(pdfFile)), std::istreambuf_iterator<char>());
    pdfFile.close();

    // Hash the PDF
    std::cout << "Hashing the PDF" << std::endl;
    SHA256(&pdfContents[0], pdfContents.size(), hash);

    // Sign the hash
    std::cout << "Signing the hash" << std::endl;
    EVP_MD_CTX* mdCtx = EVP_MD_CTX_new();
    EVP_SignInit(mdCtx, EVP_sha256());
    EVP_SignUpdate(mdCtx, hash, SHA256_DIGEST_LENGTH);

    unsigned int signatureLen = EVP_PKEY_size(privateKey);
    std::vector<unsigned char> signature(signatureLen);
    if (!EVP_SignFinal(mdCtx, &signature[0], &signatureLen, privateKey)) {
        std::cerr << "Error signing PDF." << std::endl;
        EVP_MD_CTX_free(mdCtx);
        EVP_PKEY_free(privateKey);
        return false;
    }
    // Write the signature to a file
    std::cout << "Writing the signature to file: " << signaturePath << std::endl;
    std::ofstream signatureFile(signaturePath, std::ios::binary);
    if (!signatureFile.is_open()) {
        std::cerr << "Error opening signature file." << std::endl;
        return false;
    }
    signatureFile.write(reinterpret_cast<const char*>(&signature[0]), signatureLen);
    signatureFile.close();
    // Clean up
    EVP_MD_CTX_free(mdCtx);
    EVP_PKEY_free(privateKey);
    EVP_cleanup();
    ERR_free_strings();
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <private key file> <PDF file> <signature output file>" << std::endl;
        return 1;
    }
    if (signPdf(argv[1], argv[2], argv[3])) {
        std::cout << "PDF signed successfully." << std::endl;
    }
    else {
        std::cout << "Failed to sign PDF." << std::endl;
    }
    return 0;
}

