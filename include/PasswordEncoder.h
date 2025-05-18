#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <cstring>

void handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
}

std::string rsaEncrypt(const std::string& plaintext, const std::string& pubKeyPath) {
    FILE* pubKeyFile = fopen(pubKeyPath.c_str(), "rb");
    if (!pubKeyFile) {
        std::cerr << "Unable to open public key file.\n";
        exit(EXIT_FAILURE);
    }

    RSA* rsa = PEM_read_RSA_PUBKEY(pubKeyFile, nullptr, nullptr, nullptr);
    fclose(pubKeyFile);
    if (!rsa) {
        std::cerr << "Unable to read public key.\n";
        handleErrors();
    }

    int keySize = RSA_size(rsa);
    std::vector<unsigned char> encrypted(keySize);

    int result = RSA_public_encrypt(
        plaintext.length(),
        reinterpret_cast<const unsigned char*>(plaintext.c_str()),
        encrypted.data(),
        rsa,
        RSA_PKCS1_OAEP_PADDING
    );

    RSA_free(rsa);

    if (result == -1) {
        std::cerr << "Encryption failed.\n";
        handleErrors();
    }

    return std::string(encrypted.begin(), encrypted.end());
}

void encryptPassword() {
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    std::string password = "my_secure_password";
    std::string publicKeyPath = "public.pem";

    std::string encrypted = rsaEncrypt(password, publicKeyPath);

    std::cout << "Encrypted password (hex): ";
    for (unsigned char c : encrypted)
        printf("%02x", c);
    std::cout << std::endl;

}
