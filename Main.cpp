#include <cryptopp/cryptlib.h>
#include <cryptopp/osrng.h>
#include <fstream>

#include "Encryption.hpp"



int main(int argc, char* argv[]){
    if(strcmp(argv[1], "-c") == 0){
        if (argc < 4) {std::cout << "Invalid arguments\n"; return -1;}
        CryptoPP::AutoSeededRandomPool prng;
        CryptoPP::RSA::PrivateKey priv_key;
        priv_key.GenerateRandomWithKeySize(prng, 3072);
        CryptoPP::RSA::PublicKey pub_key(priv_key);
        SaveKey(argv[2], priv_key);
        SaveKey(argv[3], pub_key);
     
        }else if (strcmp(argv[1], "-e") == 0){
            if(argc < 4) {std::cout << "Invalid arguments\n"; return -1;}
            CryptoPP::RSA::PublicKey loadedKey;
            LoadPubKey(argv[2], loadedKey);
            std::string file = read(argv[3]);
            std::string encFile = Encrypt(loadedKey, file);
            std::cout << encFile;
        } else if(strcmp(argv[1], "-d") == 0){
            if(argc < 4) {std::cout << "Invalid arguments\n"; return -1;}
            CryptoPP::RSA::PrivateKey loadedPrivateKey;
            LoadPrivKey(argv[2], loadedPrivateKey);
            std::string encryptedFile = read(argv[3]);
            CryptoPP::SecByteBlock encryptedBlock(reinterpret_cast<const CryptoPP::byte*>(&encryptedFile[0]), encryptedFile.size());
            std::cout << decrypt(encryptedBlock, loadedPrivateKey);
        
        
        }
    return 0;
}
      /*
      std::string file = read(argv[1]);
      //creates a public and private key

      //Encrypts the file using the public key
      CryptoPP::SecByteBlock ciphertext = Encrypt(pub_key, file);
      //Converts the encrypted data to string format and saves it in a file^S
      std::string encryptStr = Convert(ciphertext);
       << "\n";*/



