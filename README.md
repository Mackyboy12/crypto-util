# crypto-util
A crypto utility for my own learning. This uses RSA and can create public and private keys, encrypt files, and decrypt files. 

# usage

./a.out -c *priv_key* *pub_key*
This creates new public and private keys. *priv_key* is the path to where the private key will be saved. *pub_key* is the path to where the public key will be stored

./a.out -e *pub_key* *file* *enc_file*
This encrypts *file* and saves it to *enc_file* using *pub_key*

./a.out -d *priv_key* *enc_file*
Decrypts *enc_file* using *priv_key* and sends it to stdout
