#include <iostream>
#include <string>

// A simple XOR function that works for both encryption and decryption
std::string xorEncryptDecrypt(const std::string& input, char key) {
    std::string output = input;
    for (char& c : output) {
        c ^= key; // Bitwise XOR operation
    }
    return output;
}

int main() {
    std::string message = "SecretMessage123";
    char secretKey = 'K';

    // Encrypt the message
    std::string encrypted = xorEncryptDecrypt(message, secretKey);
    std::cout << "Encrypted: " << encrypted << "\n";

    // Decrypt it back using the same function and key
    std::string decrypted = xorEncryptDecrypt(encrypted, secretKey);
    std::cout << "Decrypted: " << decrypted << "\n";

    return 0;
}