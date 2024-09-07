// Linux help: http://www.cryptopp.com/wiki/Linux

// Debug:
// g++ -g3 -ggdb -O0 -Wall -Wextra -Wno-unused -Wno-type-limits -I. -I/usr/include/cryptopp cryptopp-key-encode.cpp -o cryptopp-key-encode.exe -lcryptopp

// Release:
// g++ -O2 -Wall -Wextra -Wno-unused -Wno-type-limits -I. -I/usr/include/cryptopp cryptopp-key-encode.cpp -o cryptopp-key-encode.exe -lcryptopp && strip --strip-all cryptopp-key-encode.exe

#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#ifdef _WIN32
#include <Windows.h>
#endif

#include <stdexcept>
using std::runtime_error;

// Cryptopp libraries
#include <cryptopp/queue.h>
using CryptoPP::ByteQueue;

#include <cryptopp/files.h>
using CryptoPP::FileSink;
using CryptoPP::FileSource;
using CryptoPP::PK_DecryptorFilter;
using CryptoPP::PK_EncryptorFilter;

#include "cryptopp/dsa.h"
using CryptoPP::DSA;

#include "cryptopp/rsa.h"
using CryptoPP::RSA;

#include <cryptopp/cryptlib.h>
using CryptoPP::BufferedTransformation;
using CryptoPP::PrivateKey;
using CryptoPP::PublicKey;

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include <cryptopp/hex.h>
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include <cryptopp/base64.h>
using CryptoPP::Base64Decoder;
using CryptoPP::Base64Encoder;

using namespace CryptoPP;

// Binary encode for PrivateKey
void EncodePrivateKey(const string &filename, const RSA::PrivateKey &key);
void DecodePrivateKey(const string &filename, RSA::PrivateKey &key);

void EncodePublicKey(const string &filename, const RSA::PublicKey &key);
void DecodePublicKey(const string &filename, RSA::PublicKey &key);

void save(const string &filename, const BufferedTransformation &bt);
void load(const string &filename, BufferedTransformation &bt);

int main(int argc, char **argv)
{
    // Set locale to support UTF-8
    #ifdef __linux__
    std::locale::global(std::locale("C.utf8"));
    #endif

    #ifdef _WIN32
    // Set console code page to UTF-8 on Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif


	AutoSeededRandomPool rnd;
	cout << "RSA Program for Key generate, Encrypt, Decrypt" << endl;
	cout << "1. KeyGeneration()" << endl;
	cout << "2. Encrypt()" << endl;
	cout << "3. Decrypt()" << endl;
	cout << "What would you like to do (1,2,3): ";
	int getinput;
	cin >> getinput;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	switch (getinput)
	{
	case 1:
	{
		// Private key
		RSA::PrivateKey rsaPrivate;
		rsaPrivate.GenerateRandomWithKeySize(rnd, 3072);
		// Generate public key
		RSA::PublicKey rsaPublic(rsaPrivate);
		cout << "Module n: " << std::hex << rsaPrivate.GetModulus() << endl
			 << endl;
		cout << "Prime number p: " << std::hex << rsaPrivate.GetPrime1() << endl
			 << endl;
		cout << "Prime number q: " << std::hex << rsaPrivate.GetPrime2() << endl
			 << endl;
		cout << "Private key d: " << std::hex << rsaPrivate.GetPrivateExponent() << endl
			 << endl;
		// Save key to file
		EncodePrivateKey("rsa-private.der", rsaPrivate);
		EncodePublicKey("rsa-public.der", rsaPublic);

		cout << "Successfully generated and saved RSA keys" << endl;

		break;
	}

	case 2:
	{
		// Encryption C=Encryption(publicKey, plaintext)
		//string plain = "Welcome UIT Cryptography class", cipher, encoded;
        string plain = "Xin chào lớp Mật mã học UIT ", cipher, encoded;
		RSA::PublicKey pk;
		DecodePublicKey("rsa-public.der", pk);
		cout << "successfully loaded RSA keys" << endl;
		RSAES_OAEP_SHA_Encryptor encrypt(pk);

		StringSource(plain, true,
					 new PK_EncryptorFilter(rnd, encrypt,
											new StringSink(cipher)) // PK_EncryptorFilter
					 );								// StringSource
			// Pretty print cipher
			encoded.clear();
		StringSource(cipher, true,
					 new HexEncoder(new StringSink(encoded)));
		cout << "ciphertext (hex) :" << encoded << endl;
		encoded.clear();
		StringSource(cipher, true,
					 new Base64Encoder(new StringSink(encoded)));
				cout << "ciphertext (base64): " << encoded << endl;
		break;
	}

	case 3:
	{
		// Decryption Plaintext=decrypt(PrivateKey, cipher)
        // Load private Key;
		RSA::PrivateKey prik;
		DecodePrivateKey("rsa-private.der", prik);
        RSAES_OAEP_SHA_Decryptor d(prik);

		// Decrypt function
		cout << "Please input ciphertext (hex): ";
		string hexcipher, dcipher, recovered;
		getline(cin, hexcipher);

		// Decode cipher from hex string to binary string
		//cout << "hex cipher (input):" << hexcipher << endl;
		
        StringSource(hexcipher, true,
					 new HexDecoder(new StringSink(dcipher)));

		StringSource(dcipher, true,
					 new PK_DecryptorFilter(rnd, d,
											new StringSink(recovered)) // PK_EncyptionFilter
		);															   // StringSource

		cout << "plaintext(recovered): " << recovered << endl;
		break;
	}

	default:
		cout << "Invalid option selected." << endl;
	}
	// std::ios_base::sync_with_stdio(false);
	// AutoSeededRandomPool rnd;

	// RSA::PrivateKey rsaPrivate;
	// rsaPrivate.GenerateRandomWithKeySize(rnd, 3072);

	// RSA::PublicKey rsaPublic(rsaPrivate);
	// cout << "Module n: " << std::hex << rsaPrivate.GetModulus() << endl
	// 	 << endl;
	// cout << "Prime number p: " << std::hex << rsaPrivate.GetPrime1() << endl
	// 	 << endl;
	// cout << "Prime number q: " << std::hex << rsaPrivate.GetPrime2() << endl
	// 	 << endl;
	// cout << "Private key d: " << std::hex << rsaPrivate.GetPrivateExponent() << endl
	// 	 << endl;

	// EncodePrivateKey("rsa-private.der", rsaPrivate);
	// EncodePublicKey("rsa-public.der", rsaPublic);
	// cout << "Successfully generated and saved RSA keys" << endl;

	// ////////////////////////////////////////////////////////////////////////////////////
	// // Load and Decode key
	// RSA::PrivateKey k1;
	// DecodePrivateKey("rsa-private.der", k1);

	// RSA::PublicKey k2;
	// DecodePublicKey("rsa-public.der", k2);

	// cout << "Successfully loaded RSA keys" << endl;

	// //////////////////////////////////////////////////////////////////////////////////// Verify the key

	// if (!k1.Validate(rnd, 3))
	// 	throw runtime_error("Rsa private key validation failed");

	// if (!k2.Validate(rnd, 3))
	// 	throw runtime_error("Rsa public key validation failed");

	// cout << "Successfully validated RSA keys" << endl;

	// ////////////////////////////////////////////////////////////////////////////////////

	// if (rsaPrivate.GetModulus() != k1.GetModulus() ||
	// 	rsaPrivate.GetPublicExponent() != k1.GetPublicExponent() ||
	// 	rsaPrivate.GetPrivateExponent() != k1.GetPrivateExponent())
	// {
	// 	throw runtime_error("private key data did not round trip");
	// }

	// if (rsaPublic.GetModulus() != k2.GetModulus() ||
	// 	rsaPublic.GetPublicExponent() != k2.GetPublicExponent())
	// {
	// 	throw runtime_error("public key data did not round trip");
	// }

	// cout << "Successfully round-tripped RSA keys" << endl;

	// ////////////////////////////////////////////////////////////////////////////////////

	return 0;
}

// Binary encode for PrivateKey
void EncodePrivateKey(const string &filename, const RSA::PrivateKey &key)
{

	ByteQueue queue;
	key.DEREncodePrivateKey(queue);

	save(filename, queue);
}

void DecodePrivateKey(const string &filename, RSA::PrivateKey &key)
{

	ByteQueue queue;

	load(filename, queue);
	key.BERDecodePrivateKey(queue, false /*optParams*/, queue.MaxRetrievable());
}

// Binary encode for PublicKey
void EncodePublicKey(const string &filename, const RSA::PublicKey &key)
{

	ByteQueue queue;
	key.DEREncodePublicKey(queue);

	save(filename, queue);
}

void DecodePublicKey(const string &filename, RSA::PublicKey &key)
{

	ByteQueue queue;
	load(filename, queue);
	key.BERDecodePublicKey(queue, false /*optParams*/, queue.MaxRetrievable());
}

// Save to file from buffer
void save(const string &filename, const BufferedTransformation &bt)
{

	FileSink file(filename.c_str());

	bt.CopyTo(file);
	file.MessageEnd();
}

// Load from file to buffer
void load(const string &filename, BufferedTransformation &bt)
{

	FileSource file(filename.c_str(), true /*pumpAll*/);

	file.TransferTo(bt);
	bt.MessageEnd();
}
