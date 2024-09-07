// C-CPP libraries
#include <iostream>
#include <fstream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
#include <locale>

// Crypto++ libraries headers
#include <cryptopp/sha.h> // sha-1, sha-2
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/integer.h>

using namespace std;
using namespace CryptoPP;


int main (int argc, char* argv[])
{
    // Check for correct argument usage
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <hash_type> <filename>" << std::endl;
        std::cerr << "Hash types: SHA224, SHA256, SHA384, SHA512" << std::endl;
        return 1;
    }

    // Set locale to support UTF-8
    #ifdef _linux_ 
    locale::global locale("C.utf8"));
    #endif

    #ifdef _WIN32
    // Set console code page to UTF-8 on Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8); 
    #endif

    // Determine hash algorithm
    unique_ptr<HashTransformation> hash; 
    if (string(argv[1]) == "SHA224") {
         hash.reset(new SHA224); 
    } else if (string(argv[1]) == "SHA256") { 
        hash.reset(new SHA256);
    } else if (string(argv[1]) == "SHA384") {
        hash.reset(new SHA384); 
    } else if (string(argv[1]) == "SHA512") {
        hash.reset(new SHA512); 
    } else {
        cerr << "Invalid hash type: " << argv[1] << endl; 
        return 1;
    }

    // Open file 
    ifstream file(argv[2], ios::binary); 
    // Debug: Print the file path received 
    cout << "Received file path: " << argv[2] << endl; 
    if (!file) {
        cerr << "Error opening file: " << argv[2] << endl; 
        return 1;
    }

    // Read content from file into a string
    string message((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));

    // Compute digest 
    string digest; 
    hash->Update((const CryptoPP::byte*)message.data(), message.size()); 
    digest.resize(hash->DigestSize()); 
    hash->TruncatedFinal((CryptoPP:: byte*)&digest[0], digest.size());

    // Pretty print digest information
    cout << "Name: " << hash->AlgorithmName() << endl;
    cout << "Digest size: " << hash->DigestSize() << endl;
    cout << "Block size: " << hash->BlockSize() << endl;
    cout << "Digest: ";
    string encodedDigest;
    StringSource ss(digest, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(encodedDigest)));
    cout << encodedDigest << std::endl;

    // Hash to Z_p
    string wdigest = digest + "H";
    Integer idigest((const CryptoPP::byte*)wdigest.data(), wdigest.size());
    Integer p("AADD9DB8DBE9C48B3FD4E6AE33C9FC07CB308DB3B3C9D20ED6639CCA703308717D4D9B009BC66842AECDA12AE6A380E62881FF2F2D82C68528AA6056583A48F3H");
    cout << "Prime number p for Z_p: " << p << endl;
    cout << "Hash digest in Z_p: " << (idigest % p) << endl;


    return 0;

}