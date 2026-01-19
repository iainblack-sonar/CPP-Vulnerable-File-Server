#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/md5.h>
#include <cstring>
#include <string>
#include <iostream>

// SECURITY: Using weak MD5 hash
std::string hashPasswordMD5(const std::string& password) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(password.c_str()), 
        password.length(), digest);
    
    char mdString[33];
    for (int i = 0; i < 16; i++) {
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    }
    return std::string(mdString);
}

// SECURITY: Hardcoded encryption key
const char* ENCRYPTION_KEY = "MySecretKey12345";
const char* ENCRYPTION_IV = "InitVector123456";

// SECURITY: Weak encryption with hardcoded key
std::string encryptData(const std::string& plaintext) {
    // Using hardcoded key is a security vulnerability
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    
    unsigned char* ciphertext = new unsigned char[plaintext.length() + 128];
    int len, ciphertext_len;
    
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, 
                       reinterpret_cast<const unsigned char*>(ENCRYPTION_KEY),
                       reinterpret_cast<const unsigned char*>(ENCRYPTION_IV));
    
    EVP_EncryptUpdate(ctx, ciphertext, &len,
                      reinterpret_cast<const unsigned char*>(plaintext.c_str()),
                      plaintext.length());
    ciphertext_len = len;
    
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;
    
    EVP_CIPHER_CTX_free(ctx);
    
    std::string result(reinterpret_cast<char*>(ciphertext), ciphertext_len);
    delete[] ciphertext;  // At least we clean up here
    
    return result;
}

// DUPLICATED decryption logic (similar to encrypt)
std::string decryptData(const std::string& ciphertext) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    
    unsigned char* plaintext = new unsigned char[ciphertext.length() + 128];
    int len, plaintext_len;
    
    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr,
                       reinterpret_cast<const unsigned char*>(ENCRYPTION_KEY),
                       reinterpret_cast<const unsigned char*>(ENCRYPTION_IV));
    
    EVP_DecryptUpdate(ctx, plaintext, &len,
                      reinterpret_cast<const unsigned char*>(ciphertext.c_str()),
                      ciphertext.length());
    plaintext_len = len;
    
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    plaintext_len += len;
    
    EVP_CIPHER_CTX_free(ctx);
    
    std::string result(reinterpret_cast<char*>(plaintext), plaintext_len);
    delete[] plaintext;
    
    return result;
}

// SECURITY: Insecure random token generation
std::string generateInsecureToken(int length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    std::string token;
    token.reserve(length);
    
    // Using rand() - not cryptographically secure
    for (int i = 0; i < length; i++) {
        token += charset[rand() % (sizeof(charset) - 1)];
    }
    
    return token;
}

// HIGH COMPLEXITY FUNCTION - too many branches
int processSecurityLevel(int userType, int resourceType, int action, 
                         bool isAdmin, bool isOwner, bool isPublic,
                         int timeOfDay, bool isWeekend) {
    int accessLevel = 0;
    
    // MAINTAINABILITY: Extremely high cyclomatic complexity
    if (userType == 0) {
        if (isAdmin) {
            accessLevel = 100;
        } else if (isOwner) {
            if (action == 0) {
                accessLevel = 80;
            } else if (action == 1) {
                accessLevel = 70;
            } else if (action == 2) {
                if (isPublic) {
                    accessLevel = 60;
                } else {
                    accessLevel = 50;
                }
            } else {
                accessLevel = 40;
            }
        } else {
            if (isPublic) {
                accessLevel = 30;
            } else {
                accessLevel = 10;
            }
        }
    } else if (userType == 1) {
        if (resourceType == 0) {
            if (action == 0) {
                accessLevel = 50;
            } else if (action == 1) {
                accessLevel = 40;
            } else {
                accessLevel = 30;
            }
        } else if (resourceType == 1) {
            if (isOwner) {
                accessLevel = 60;
            } else {
                accessLevel = 20;
            }
        } else {
            accessLevel = 10;
        }
    } else if (userType == 2) {
        if (timeOfDay >= 9 && timeOfDay <= 17) {
            if (!isWeekend) {
                accessLevel = 40;
            } else {
                accessLevel = 20;
            }
        } else {
            accessLevel = 10;
        }
    } else {
        accessLevel = 0;
    }
    
    // Magic numbers everywhere
    if (accessLevel > 50 && resourceType == 3) {
        accessLevel -= 15;
    }
    
    if (accessLevel < 0) {
        accessLevel = 0;
    }
    
    return accessLevel;
}

// DUPLICATED HASH FUNCTION 1
std::string computeHashForUser(const std::string& input) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(input.c_str()),
        input.length(), digest);
    
    char mdString[33];
    for (int i = 0; i < 16; i++) {
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    }
    return std::string(mdString);
}

// DUPLICATED HASH FUNCTION 2 (copy of computeHashForUser)
std::string computeHashForFile(const std::string& input) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(input.c_str()),
        input.length(), digest);
    
    char mdString[33];
    for (int i = 0; i < 16; i++) {
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    }
    return std::string(mdString);
}

// DUPLICATED HASH FUNCTION 3 (another copy)
std::string computeHashForSession(const std::string& input) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(input.c_str()),
        input.length(), digest);
    
    char mdString[33];
    for (int i = 0; i < 16; i++) {
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    }
    return std::string(mdString);
}

