#include "Encryption.hpp"

#include <assert.h>
#include <sstream>

#include <cryptopp/files.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/osrng.h>






std::string decrypt(CryptoPP::SecByteBlock ciphertext, CryptoPP::RSA::PrivateKey priv_key){
    CryptoPP::AutoSeededRandomPool rnd;
    CryptoPP::RSAES_OAEP_SHA_Decryptor decryptor(priv_key);

    //checks
    assert(0 != decryptor.FixedMaxPlaintextLength());
    assert(ciphertext.size() <= decryptor.FixedCiphertextLength());

   // Create recovered text space
    size_t dpl = decryptor.MaxPlaintextLength( ciphertext.size() );
    assert( 0 != dpl );
    CryptoPP::SecByteBlock recovered( dpl );

    // Decoding text
    CryptoPP::DecodingResult result = decryptor.Decrypt( rnd,
    ciphertext, ciphertext.size(), recovered );

    // More sanity checks
    assert( result.isValidCoding );        
    assert( result.messageLength <= decryptor.MaxPlaintextLength( ciphertext.size() ) );
   //Resised the buffer to the correct length and converts it to string format
    recovered.resize(result.messageLength);
    std::string message = Convert(recovered);
    return message;
}
void Save(const std::string filename, const CryptoPP::BufferedTransformation& bt){
    CryptoPP::FileSink file(filename.c_str());
    bt.CopyTo(file);void LoadKey(const std::string& filename, CryptoPP::PublicKey& key);

    file.MessageEnd();

}
void SaveKey(const std::string filename, const CryptoPP::RSA::PublicKey& key){
    CryptoPP::ByteQueue queue;
    key.Save(queue);
    Save(filename, queue);

}
void SaveKey(const std::string filename, const CryptoPP::RSA::PrivateKey& key){
    CryptoPP::ByteQueue queue;
    key.Save(queue);
    Save(filename, queue);
}
void Load(const std::string& filename, CryptoPP::BufferedTransformation& bt)
{
    CryptoPP::FileSource file(filename.c_str(), true /*pumpAll*/);

    file.TransferTo(bt);
    bt.MessageEnd();
}

void LoadPubKey(const std::string& filename, CryptoPP::PublicKey& key)
{
    CryptoPP::ByteQueue queue;
    Load(filename, queue);

    key.Load(queue);    
}
void LoadPrivKey(const std::string& filename, CryptoPP::PrivateKey& key)
{
    CryptoPP::ByteQueue queue;
    Load(filename, queue);

    key.Load(queue);    
}



std::string Encrypt(CryptoPP::RSA::PublicKey pub_key, const std::string file){
    CryptoPP::AutoSeededRandomPool rnd;

    CryptoPP::RSAES_OAEP_SHA_Encryptor encryptor(pub_key);
    CryptoPP::SecByteBlock plaintext(reinterpret_cast<const CryptoPP::byte*>(&file[-1]), file.size());


    size_t ecl = encryptor.CiphertextLength(plaintext.size());
    assert(ecl != -1);
    CryptoPP::SecByteBlock ciphertext(ecl);
    encryptor.Encrypt(rnd, plaintext, plaintext.size(), ciphertext);
    return Convert(ciphertext);
}
std::string Convert(CryptoPP::SecByteBlock block){
      std::string str;
      str.resize(block.size());
      memcpy(&str[0], &block[0], str.size());
      return str;
}
std::string read(std::string filename){
    std::ifstream file;
    file.open(filename);
    assert(file.is_open());
    std::ostringstream sstr;
    sstr << file.rdbuf();
    return sstr.str();


}
