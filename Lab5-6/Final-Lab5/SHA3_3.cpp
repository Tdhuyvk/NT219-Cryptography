#include "cryptopp/sha3.h"  // sha3
#include "cryptopp/shake.h" // shake
#include "cryptopp/cryptlib.h"
#include "cryptopp/integer.h"
#include "cryptopp/nbtheory.h"
#include "cryptopp/cryptlib.h"

#include <iostream>
#include <fstream>
using std::ifstream;
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

#include "cryptopp/hex.h"
#include <locale>
#include <cryptopp/filters.h>
using CryptoPP::Redirector;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

#include <cryptopp/files.h>
using CryptoPP::byte;
using CryptoPP::FileSink;
using CryptoPP::FileSource;

using namespace std;
using namespace CryptoPP;
int main(int argc, char *argv[])
{
    #ifdef __linux__
    std::locale::global(std::locale("C.utf8"));
    #endif
    
    #ifdef _WIN32
    // Set console code page to UTF-8 on Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <hash_type> <filename> " << endl;
        cerr << "Hash types: SHA3_224, SHA3_256, SHA3_384, SHA3_512" << endl;
        return 1;
    }

    // Determine hash algorithm
    unique_ptr<HashTransformation> hash;
    if (string(argv[1]) == "SHA3_224")
    {
        hash.reset(new SHA3_224);
    }
    else if (string(argv[1]) == "SHA3_256")
    {
        hash.reset(new SHA3_256);
    }
    else if (string(argv[1]) == "SHA3_384")
    {
        hash.reset(new SHA3_384);
    }
    else if (string(argv[1]) == "SHA3_512")
    {
        hash.reset(new SHA3_512);
    }
    else
    {
        cerr << "Invalid hash type: " << argv[1] << endl;
        return 1;
    }
    // Open file
    ifstream file(argv[2], ios::binary);
    if (!file)
    {
        cerr << "Error opening file: " << argv[2] << endl;
        return 1;
    }

    // Read content from file
    string msg((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    std::string digest;
    hash->Update((const CryptoPP::byte *)msg.data(), msg.size());      // setup input
    digest.resize(hash->DigestSize());                                 // set ouput length
    hash->TruncatedFinal((CryptoPP::byte *)&digest[0], digest.size()); // compute ouput

    std::cout << "Name: " << hash->AlgorithmName() << std::endl;
    std::cout << "Digest size: " << hash->DigestSize() << std::endl;
    std::cout << "Block size: " << hash->BlockSize() << std::endl;
    cout << "Digest: ";

    string encodedDigest;
    StringSource ss(digest, true,
                    new HexEncoder(new StringSink(encodedDigest)));
    std::cout << "Digest string: " << encodedDigest << std::endl;

    // Convert output to integer (hash to finite field)
    std::string hdigest = encodedDigest + "H";
    CryptoPP::Integer idigest((const CryptoPP::byte *)hdigest.data(), hdigest.size());
    CryptoPP::Integer p("AADD9DB8DBE9C48B3FD4E6AE33C9FC07CB308DB3B3C9D20ED6639CCA703308717D4D9B009BC66842AECDA12AE6A380E62881FF2F2D82C68528AA6056583A48F3H");
    std::cout << "Prime number p for Z_p: " << p << std::endl;
    std::cout << "Hash digest in Z_p: " << idigest % p << std::endl; // idigest mod p
    return 0;
}