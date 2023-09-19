#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define ENCRYPT_TYPE_PHRASE "encrypt"
#define DECRYPT_TYPE_PHRASE "decrypt"
#define SIMPLE_KIND_PHRASE "simple"
#define COMPLICATED_KIND_PHRASE "complicated"
#define MAX_RANDOM 11
#define DELIMITER '\n'

enum cipherType
{
	Encryption,
	Decrytpion
};
enum cipherKind
{
	Simple,
	Complicated
};
struct Cipher
{
	cipherKind kind;
	cipherType type;
};
struct IO
{
	string inputAddress;
	string outputAddress;
};

typedef vector<char> encryptionInput_t;
typedef vector<int> decryptionInput_t;
typedef string output_t;
typedef int seed_t;

Cipher getCipher();
string getKey();
IO getIO();
seed_t getSeed(const string &key);
encryptionInput_t readEncryptionFileContent(const string &inputAddress);
decryptionInput_t readDecryptionFileContent(const string &inputAddress);
output_t encryptSimple(const string &key, const encryptionInput_t &input);
output_t encryptComplicated(const string &key, const encryptionInput_t &input);
output_t decryptSimple(const string &key, const decryptionInput_t &input);
output_t decryptComplicated(const string &key, const decryptionInput_t &input);
output_t generateOutput(const Cipher &cipher, const string &inputAddress, const string &key);
output_t encrypt(const cipherKind &kind, const string &key, const encryptionInput_t &input);
output_t decrypt(const cipherKind &kind, const string &key, const decryptionInput_t &input);
void writeOutput(const output_t &output, const string &outputAddress);

int main()
{
	Cipher cipher = getCipher();
	string key = getKey();
	IO io = getIO();
	string output = generateOutput(cipher, io.inputAddress, key);
	writeOutput(output, io.outputAddress);
}
Cipher getCipher()
{
	string type, kind;
	Cipher cipher;
	cin >> type >> kind;
	cipher.type = type == ENCRYPT_TYPE_PHRASE ? Encryption : Decrytpion;
	cipher.kind = kind == SIMPLE_KIND_PHRASE ? Simple : Complicated;
	return cipher;
}
string getKey()
{
	string key;
	cin >> key;
	return key;
}
IO getIO()
{
	IO io;
	cin >> io.inputAddress >> io.outputAddress;
	return io;
}
encryptionInput_t readEncryptionFileContent(const string &inputAddress)
{
	char newChar;
	encryptionInput_t input;
	ifstream file(inputAddress);
	while (file.get(newChar))
	{
		input.push_back(newChar);
	}
	return input;
}
decryptionInput_t readDecryptionFileContent(const string &inputAddress)
{
	int newNumber;
	decryptionInput_t input;
	ifstream file(inputAddress);
	while (file >> newNumber)
	{
		input.push_back(newNumber);
	}
	return input;
}
seed_t getSeed(const string &key)
{
	seed_t seed = 0;
	for (seed_t i = 0; i < key.size(); i++)
	{
		seed += int(key[i]);
	}
	return seed;
}
output_t encryptSimple(const string &key, const encryptionInput_t &input)
{
	ostringstream output;
	for (int i = 0; i < input.size(); i++)
	{
		output << (int(input[i]) + int(key[i % (key.size())])) << DELIMITER;
	}
	return output.str();
}
output_t encryptComplicated(const string &key, const encryptionInput_t &input)
{
	srand(getSeed(key));
	ostringstream output;
	for (int i = 0; i < input.size(); i++)
	{
		output << (int(input[i]) + rand() % MAX_RANDOM) << DELIMITER;
	}
	return output.str();
}

output_t decryptSimple(const string &key, const decryptionInput_t &input)
{
	ostringstream output;
	for (int i = 0; i < input.size(); i++)
	{
		output << char(input[i] - int(key[i % (key.size())]));
	}
	return output.str();
}
output_t decryptComplicated(const string &key, const decryptionInput_t &input)
{
	ostringstream output;
	srand(getSeed(key));
	for (int i = 0; i < input.size(); i++)
	{
		output << char(input[i] - rand() % MAX_RANDOM);
	}
	return output.str();
}
output_t encrypt(const cipherKind &kind, const string &key, const encryptionInput_t &input)
{
	switch (kind)
	{
	case Simple:
		return encryptSimple(key, input);
	case Complicated:
		return encryptComplicated(key, input);
	}
}
output_t decrypt(const cipherKind &kind, const string &key, const decryptionInput_t &input)
{
	switch (kind)
	{
	case Simple:
		return decryptSimple(key, input);
	case Complicated:
		return decryptComplicated(key, input);
	}
}
output_t generateOutput(const Cipher &cipher, const string &inputAddress, const string &key)
{
	encryptionInput_t encryptionInput;
	decryptionInput_t decryptInput;
	switch (cipher.type)
	{
	case Encryption:
		encryptionInput = readEncryptionFileContent(inputAddress);
		return encrypt(cipher.kind, key, encryptionInput);
	case Decrytpion:
		decryptInput = readDecryptionFileContent(inputAddress);
		return decrypt(cipher.kind, key, decryptInput);
	}
}
void writeOutput(const string &output, const string &outputAddress)
{
	ofstream file(outputAddress);
	file << output;
}
