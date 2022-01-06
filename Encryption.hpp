#include <iostream>

#include <cryptopp/rsa.h>
#include <cryptopp/secblock.h>


void SaveKey(const std::string filename, const CryptoPP::RSA::PublicKey& key);
void SaveKey(const std::string filename, const CryptoPP::RSA::PrivateKey& key);
void Load(const std::string& filename, CryptoPP::BufferedTransformation& bt);
void LoadPubKey(const std::string& filename, CryptoPP::PublicKey& key);
void LoadPrivKey(const std::string& filename, CryptoPP::PrivateKey& key);
void Save(const std::string filename, const CryptoPP::BufferedTransformation& bt);
std::string Convert(CryptoPP::SecByteBlock block);
std::string decrypt(CryptoPP::SecByteBlock ciphertext, CryptoPP::RSA::PrivateKey priv_key);
CryptoPP::RSA::PrivateKey createPrivateKey(int size);
std::string Encrypt(CryptoPP::RSA::PublicKey pub_key, const std::string file);
std::string read(std::string filename);




