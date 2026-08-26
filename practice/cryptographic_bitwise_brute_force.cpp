#include <iostream>
#include <string>
#include <cctype>

void bruteForceXOR(const std::string& encryptedText) {
    std::cout << "Starting Brute Force...\n\n";
    
    for (int i = 0; i < 256; i++) {
        char testKey = static_cast<char>(i);
        std::string attempt = "";
        
        for (char c : encryptedText) {
            char decryptedChar = c ^ testKey;
            
            if (std::isprint(static_cast<unsigned char>(decryptedChar))) {
                attempt += decryptedChar;
            } else {
                attempt += '.'; 
            }
        }
        
        std::cout << "Key " << i << ": " << attempt << "\n";
    }
}

int main() {
    std::string originalMessage = "SecretMessage123";
    std::string encryptedMessage = "";
    
    // Encrypt the message directly in memory
    for(char c : originalMessage) {
        encryptedMessage += c ^ 'W';
    }
    
    // Brute force the perfectly intact encrypted bytes
    bruteForceXOR(encryptedMessage);
    
    return 0;
}