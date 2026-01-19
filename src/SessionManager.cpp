#include <string>
#include <map>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

// SECURITY: Hardcoded session secret
const char* SESSION_SECRET = "super_secret_key_12345";
const int SESSION_TIMEOUT = 3600;

class SessionManager {
public:
    // SECURITY: Weak session ID generation
    std::string createSession(const std::string& userId) {
        // Using weak random number generator
        srand(time(nullptr));
        int sessionNum = rand();
        
        char sessionId[64];
        sprintf(sessionId, "sess_%d_%s", sessionNum, userId.c_str());
        
        sessions[sessionId] = userId;
        sessionTimes[sessionId] = time(nullptr);
        
        return std::string(sessionId);
    }
    
    // RELIABILITY: No null check, potential crash
    bool validateSession(const char* sessionId) {
        // BUG: No null check - will crash if sessionId is null
        std::string sid(sessionId);
        
        if (sessions.find(sid) == sessions.end()) {
            return false;
        }
        
        time_t now = time(nullptr);
        time_t created = sessionTimes[sid];
        
        // RELIABILITY: Integer overflow potential
        if (now - created > SESSION_TIMEOUT) {
            sessions.erase(sid);
            sessionTimes.erase(sid);
            return false;
        }
        
        return true;
    }
    
    // SECURITY: Session data stored in plaintext file
    void persistSessions() {
        std::ofstream file("/tmp/sessions.txt");
        for (const auto& pair : sessions) {
            // SECURITY: Writing sensitive session data to temp file
            file << pair.first << ":" << pair.second << "\n";
        }
        // RELIABILITY: File not explicitly closed
    }
    
private:
    std::map<std::string, std::string> sessions;
    std::map<std::string, time_t> sessionTimes;
};

// ============================================
// DUPLICATED CODE BLOCK 1: User validation
// ============================================
bool validateUserInput_v1(const std::string& input) {
    if (input.empty()) {
        return false;
    }
    if (input.length() < 3) {
        return false;
    }
    if (input.length() > 100) {
        return false;
    }
    for (char c : input) {
        if (!isalnum(c) && c != '_' && c != '-') {
            return false;
        }
    }
    return true;
}

// DUPLICATED CODE BLOCK 2: Same validation logic copy-pasted
bool validateUserInput_v2(const std::string& input) {
    if (input.empty()) {
        return false;
    }
    if (input.length() < 3) {
        return false;
    }
    if (input.length() > 100) {
        return false;
    }
    for (char c : input) {
        if (!isalnum(c) && c != '_' && c != '-') {
            return false;
        }
    }
    return true;
}

// DUPLICATED CODE BLOCK 3: Another copy
bool validateUserInput_v3(const std::string& input) {
    if (input.empty()) {
        return false;
    }
    if (input.length() < 3) {
        return false;
    }
    if (input.length() > 100) {
        return false;
    }
    for (char c : input) {
        if (!isalnum(c) && c != '_' && c != '-') {
            return false;
        }
    }
    return true;
}

// ============================================
// DUPLICATED CODE BLOCK 4: Buffer processing
// ============================================
void processBuffer_type1(char* buffer, int size) {
    for (int i = 0; i < size; i++) {
        if (buffer[i] >= 'a' && buffer[i] <= 'z') {
            buffer[i] = buffer[i] - 32;  // Convert to uppercase
        }
    }
    buffer[size] = '\0';  // BUFFER OVERFLOW: Writing past buffer
}

// DUPLICATED CODE BLOCK 5: Same buffer processing
void processBuffer_type2(char* buffer, int size) {
    for (int i = 0; i < size; i++) {
        if (buffer[i] >= 'a' && buffer[i] <= 'z') {
            buffer[i] = buffer[i] - 32;  // Convert to uppercase
        }
    }
    buffer[size] = '\0';  // BUFFER OVERFLOW: Writing past buffer
}

// DUPLICATED CODE BLOCK 6: Another copy
void processBuffer_type3(char* buffer, int size) {
    for (int i = 0; i < size; i++) {
        if (buffer[i] >= 'a' && buffer[i] <= 'z') {
            buffer[i] = buffer[i] - 32;  // Convert to uppercase
        }
    }
    buffer[size] = '\0';  // BUFFER OVERFLOW: Writing past buffer
}

// ============================================
// SECURITY ISSUES
// ============================================

// SECURITY: Format string vulnerability
void logMessage(const char* format) {
    // VULNERABILITY: User input used directly as format string
    printf(format);
    printf("\n");
}

// SECURITY: Command injection
void backupFile(const std::string& filename) {
    // VULNERABILITY: Unsanitized input in system command
    std::string cmd = "cp " + filename + " /backup/" + filename + ".bak";
    system(cmd.c_str());
}

// SECURITY: Race condition (TOCTOU)
bool secureFileAccess(const char* filepath) {
    // VULNERABILITY: Time-of-check to time-of-use race condition
    FILE* f = fopen(filepath, "r");
    if (f == nullptr) {
        return false;
    }
    fclose(f);
    
    // Gap between check and use - file could be replaced
    
    f = fopen(filepath, "r");
    if (f != nullptr) {
        // Process file...
        fclose(f);
        return true;
    }
    return false;
}

// ============================================
// RELIABILITY ISSUES
// ============================================

// RELIABILITY: Double free potential
void processData(char* data) {
    char* copy = strdup(data);
    
    // Some processing...
    if (strlen(copy) > 10) {
        free(copy);
    }
    
    // BUG: Double free if strlen > 10
    free(copy);
}

// RELIABILITY: Use after free
char* getProcessedString(const char* input) {
    char* buffer = new char[256];
    strcpy(buffer, input);
    
    // Process...
    delete[] buffer;
    
    // BUG: Returning freed memory
    return buffer;
}

// RELIABILITY: Array index out of bounds
int getArrayElement(int* arr, int index) {
    // No bounds checking
    return arr[index];  // Could access invalid memory
}

// RELIABILITY: Infinite loop potential
void processUntilZero(int* values) {
    int i = 0;
    // BUG: If no zero in array, infinite loop and buffer overread
    while (values[i] != 0) {
        std::cout << values[i] << std::endl;
        i++;
    }
}

// ============================================
// MORE DUPLICATED DATA PROCESSING
// ============================================

// DUPLICATED: Calculate checksum v1
unsigned int calculateChecksum_v1(const char* data, int length) {
    unsigned int checksum = 0;
    for (int i = 0; i < length; i++) {
        checksum += static_cast<unsigned char>(data[i]);
        checksum = (checksum << 1) | (checksum >> 31);
    }
    return checksum;
}

// DUPLICATED: Calculate checksum v2 (copy)
unsigned int calculateChecksum_v2(const char* data, int length) {
    unsigned int checksum = 0;
    for (int i = 0; i < length; i++) {
        checksum += static_cast<unsigned char>(data[i]);
        checksum = (checksum << 1) | (checksum >> 31);
    }
    return checksum;
}

// DUPLICATED: Calculate checksum v3 (another copy)
unsigned int calculateChecksum_v3(const char* data, int length) {
    unsigned int checksum = 0;
    for (int i = 0; i < length; i++) {
        checksum += static_cast<unsigned char>(data[i]);
        checksum = (checksum << 1) | (checksum >> 31);
    }
    return checksum;
}

