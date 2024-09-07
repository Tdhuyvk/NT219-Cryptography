#include "cryptopp/cryptlib.h"
#include "cryptopp/sha3.h"
#include <iostream>

int main (int argc, char* argv[])
{
    using namespace CryptoPP;

    SHA3_256 hash;	
    std::cout << "Name: " << hash.AlgorithmName() << std::endl;
    std::cout << "Digest size: " << hash.DigestSize() << std::endl;
    std::cout << "Block size: " << hash.BlockSize() << std::endl;

    return 0; 
}