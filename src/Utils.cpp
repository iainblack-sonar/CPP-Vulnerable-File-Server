#include "Utils.h"
#include <cstring>
#include <algorithm>
#include <cctype>
#include <regex>

namespace Utils {

// BUFFER OVERFLOW VULNERABILITY
void copyString(char* dest, const char* src, int maxLen) {
    // BUG: Off-by-one error, doesn't account for null terminator
    for (int i = 0; i < maxLen; i++) {
        dest[i] = src[i];
        if (src[i] == '\0') break;
    }
    // Missing null terminator if src >= maxLen
}

// BUFFER OVERFLOW VULNERABILITY
void concatenateStrings(char* dest, const char* src1, const char* src2) {
    // No bounds checking at all
    strcpy(dest, src1);
    strcat(dest, src2);
}

// DIVISION BY ZERO - no validation
int divide(int a, int b) {
    // No check for b == 0
    return a / b;
}

// DIVISION BY ZERO - no validation
double calculatePercentage(int part, int total) {
    // No check for total == 0
    return (static_cast<double>(part) / total) * 100.0;
}

// DUPLICATED CODE - trimLeft
std::string trimLeft(const std::string& str) {
    size_t start = 0;
    while (start < str.length() && std::isspace(str[start])) {
        start++;
    }
    return str.substr(start);
}

// DUPLICATED CODE - trimRight (similar logic to trimLeft)
std::string trimRight(const std::string& str) {
    size_t end = str.length();
    while (end > 0 && std::isspace(str[end - 1])) {
        end--;
    }
    return str.substr(0, end);
}

// DUPLICATED CODE - trim calls both (could be optimized)
std::string trim(const std::string& str) {
    return trimLeft(trimRight(str));
}

// DUPLICATED VALIDATION PATTERN 1
bool isValidEmail(const std::string& email) {
    if (email.empty()) {
        return false;
    }
    if (email.length() < 5) {
        return false;
    }
    if (email.length() > 255) {
        return false;
    }
    size_t atPos = email.find('@');
    if (atPos == std::string::npos) {
        return false;
    }
    size_t dotPos = email.find('.', atPos);
    if (dotPos == std::string::npos) {
        return false;
    }
    return true;
}

// DUPLICATED VALIDATION PATTERN 2 (similar structure to isValidEmail)
bool isValidUsername(const std::string& username) {
    if (username.empty()) {
        return false;
    }
    if (username.length() < 3) {
        return false;
    }
    if (username.length() > 50) {
        return false;
    }
    for (char c : username) {
        if (!std::isalnum(c) && c != '_') {
            return false;
        }
    }
    return true;
}

// DUPLICATED VALIDATION PATTERN 3 (similar structure)
bool isValidPassword(const std::string& password) {
    if (password.empty()) {
        return false;
    }
    if (password.length() < 8) {
        return false;
    }
    if (password.length() > 128) {
        return false;
    }
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    for (char c : password) {
        if (std::isupper(c)) hasUpper = true;
        if (std::islower(c)) hasLower = true;
        if (std::isdigit(c)) hasDigit = true;
    }
    return hasUpper && hasLower && hasDigit;
}

// PATH TRAVERSAL VULNERABILITY
std::string joinPath(const std::string& base, const std::string& relative) {
    // No sanitization of relative path - allows ../
    if (base.empty()) {
        return relative;
    }
    if (base.back() == '/') {
        return base + relative;
    }
    return base + "/" + relative;
}

std::string getFileExtension(const std::string& filename) {
    size_t dotPos = filename.rfind('.');
    if (dotPos == std::string::npos) {
        return "";
    }
    return filename.substr(dotPos + 1);
}

std::string getFileName(const std::string& path) {
    size_t slashPos = path.rfind('/');
    if (slashPos == std::string::npos) {
        return path;
    }
    return path.substr(slashPos + 1);
}

}  // namespace Utils

