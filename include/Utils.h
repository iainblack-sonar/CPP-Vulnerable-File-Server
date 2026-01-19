#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <cstdlib>

namespace Utils {

// Insecure random number generation - SECURITY ISSUE
inline int generateSessionId() {
    return rand();  // Weak RNG
}

inline std::string generateToken() {
    char token[32];
    for (int i = 0; i < 31; i++) {
        token[i] = 'a' + (rand() % 26);  // Weak RNG
    }
    token[31] = '\0';
    return std::string(token);
}

// Buffer operations with potential overflow
void copyString(char* dest, const char* src, int maxLen);
void concatenateStrings(char* dest, const char* src1, const char* src2);

// Numeric operations
int divide(int a, int b);  // Potential division by zero
double calculatePercentage(int part, int total);

// String operations - duplicated logic
std::string trimLeft(const std::string& str);
std::string trimRight(const std::string& str);
std::string trim(const std::string& str);

// Validation functions - duplicated patterns
bool isValidEmail(const std::string& email);
bool isValidUsername(const std::string& username);
bool isValidPassword(const std::string& password);

// File path operations
std::string joinPath(const std::string& base, const std::string& relative);
std::string getFileExtension(const std::string& filename);
std::string getFileName(const std::string& path);

}  // namespace Utils

#endif // UTILS_H

