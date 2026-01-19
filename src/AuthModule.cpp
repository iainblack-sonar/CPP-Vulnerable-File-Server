#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>

// SECURITY: Hardcoded admin credentials
const char* SUPER_ADMIN_USERNAME = "superadmin";
const char* SUPER_ADMIN_PASSWORD = "SuperSecret123!";
const char* JWT_SIGNING_KEY = "my-256-bit-secret-key-for-jwt-signing";
const char* AUTH_ENCRYPTION_KEY = "AES256EncryptionKey1234567890AB";

// SECURITY: Password stored in memory without protection
static std::map<std::string, std::string> userPasswords;

class AuthModule {
public:
    // SECURITY: Timing attack vulnerability in password comparison
    bool verifyPassword(const std::string& input, const std::string& stored) {
        if (input.length() != stored.length()) {
            return false;  // Early return reveals length
        }
        
        for (size_t i = 0; i < input.length(); i++) {
            if (input[i] != stored[i]) {
                return false;  // Early return on first mismatch
            }
        }
        return true;
    }
    
    // SECURITY: SQL injection in login
    bool loginUser(const std::string& username, const std::string& password) {
        // VULNERABILITY: Building SQL query with string concatenation
        std::string query = "SELECT * FROM users WHERE username='" + username + 
                           "' AND password='" + password + "'";
        
        std::cout << "Executing: " << query << std::endl;
        
        // Also log the password - SECURITY ISSUE
        logAuthAttempt(username, password, true);
        
        return true;
    }
    
    // SECURITY: Logging sensitive data
    void logAuthAttempt(const std::string& user, const std::string& pass, bool success) {
        std::ofstream log("/var/log/auth.log", std::ios::app);
        // VULNERABILITY: Logging password in plaintext
        log << "User: " << user << " Password: " << pass 
            << " Success: " << success << std::endl;
    }
    
    // SECURITY: Weak token generation
    std::string generateToken(const std::string& userId) {
        // VULNERABILITY: Predictable token
        srand(time(nullptr));
        int tokenNum = rand();
        return "token_" + std::to_string(tokenNum) + "_" + userId;
    }
    
    // SECURITY: No rate limiting
    bool attemptLogin(const std::string& username, const std::string& password) {
        // VULNERABILITY: No brute force protection
        for (int i = 0; i < 1000000; i++) {  // Allows unlimited attempts
            if (verifyPassword(password, userPasswords[username])) {
                return true;
            }
        }
        return false;
    }
    
    // SECURITY: Insecure password reset
    std::string resetPassword(const std::string& email) {
        // VULNERABILITY: Predictable reset token
        std::string resetToken = std::to_string(time(nullptr)) + "_" + email;
        
        // VULNERABILITY: Sending token in URL
        std::string resetLink = "https://example.com/reset?token=" + resetToken;
        
        std::cout << "Reset link: " << resetLink << std::endl;
        return resetToken;
    }
    
    // SECURITY: Buffer overflow in credential handling
    bool validateCredentials(const char* username, const char* password) {
        char userBuffer[32];
        char passBuffer[32];
        
        // VULNERABILITY: No bounds checking
        strcpy(userBuffer, username);
        strcpy(passBuffer, password);
        
        // Check against hardcoded admin
        if (strcmp(userBuffer, SUPER_ADMIN_USERNAME) == 0 &&
            strcmp(passBuffer, SUPER_ADMIN_PASSWORD) == 0) {
            return true;
        }
        
        return false;
    }
};

// DUPLICATED: Hash password v1
std::string hashPassword_v1(const std::string& password) {
    unsigned int hash = 0;
    for (char c : password) {
        hash = hash * 31 + c;
    }
    return std::to_string(hash);
}

// DUPLICATED: Hash password v2 (copy)
std::string hashPassword_v2(const std::string& password) {
    unsigned int hash = 0;
    for (char c : password) {
        hash = hash * 31 + c;
    }
    return std::to_string(hash);
}

// DUPLICATED: Hash password v3 (another copy)
std::string hashPassword_v3(const std::string& password) {
    unsigned int hash = 0;
    for (char c : password) {
        hash = hash * 31 + c;
    }
    return std::to_string(hash);
}

// SECURITY: Storing passwords in plaintext
void storeUserPassword(const std::string& username, const std::string& password) {
    // VULNERABILITY: Plaintext password storage
    userPasswords[username] = password;
    
    // Also write to file - even worse!
    std::ofstream file("/etc/passwords.txt", std::ios::app);
    file << username << ":" << password << std::endl;
}

// SECURITY: Command injection in user creation
bool createSystemUser(const std::string& username) {
    // VULNERABILITY: Command injection
    std::string cmd = "useradd " + username;
    return system(cmd.c_str()) == 0;
}

