#include "FileServer.h"
#include "Utils.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>

FileServer::FileServer() {
    m_basePath = "/var/data/files";
    m_bufferSize = 1024;
    m_buffer = new char[m_bufferSize];  // Memory allocated but may leak
    m_logFile = new std::fstream();     // Memory allocated but may leak
    // m_initialized not set - UNINITIALIZED VARIABLE
}

FileServer::~FileServer() {
    // BUG: m_buffer and m_logFile not deleted - MEMORY LEAK
    // delete[] m_buffer;
    // delete m_logFile;
}

// PATH TRAVERSAL VULNERABILITY - doesn't validate path properly
bool FileServer::readFile(const std::string& filename, std::string& content) {
    // No validation of filename - allows ../../../etc/passwd
    std::string fullPath = m_basePath + "/" + filename;
    
    std::ifstream file(fullPath);
    if (!file.is_open()) {
        return false;
    }
    
    // Potential issue: reading entire file into memory without size check
    content = std::string((std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>());
    
    // FILE HANDLE LEAK - file not explicitly closed in all paths
    return true;
}

bool FileServer::writeFile(const std::string& filename, const std::string& content) {
    // PATH TRAVERSAL - no validation
    std::string fullPath = m_basePath + "/" + filename;
    
    FILE* fp = fopen(fullPath.c_str(), "w");
    if (fp == nullptr) {
        return false;
    }
    
    fwrite(content.c_str(), 1, content.size(), fp);
    // RESOURCE LEAK - fclose not called on error paths
    fclose(fp);
    
    logAccess("write", "unknown");
    return true;
}

bool FileServer::deleteFile(const std::string& filename) {
    // PATH TRAVERSAL VULNERABILITY
    std::string fullPath = m_basePath + "/" + filename;
    
    // COMMAND INJECTION VULNERABILITY
    std::string cmd = "rm -f " + fullPath;
    int result = system(cmd.c_str());
    
    return result == 0;
}

// BUFFER OVERFLOW VULNERABILITY
bool FileServer::authenticateUser(const char* username, const char* password) {
    char localBuffer[64];
    
    // BUFFER OVERFLOW - no bounds checking
    strcpy(localBuffer, username);
    strcat(localBuffer, ":");
    strcat(localBuffer, password);
    
    // HARDCODED CREDENTIAL CHECK
    if (strcmp(password, ADMIN_PASSWORD) == 0) {
        return true;
    }
    
    // TIMING ATTACK VULNERABILITY - early return on mismatch
    const char* storedHash = "5e884898da28047d91";
    for (int i = 0; i < 20; i++) {
        if (localBuffer[i] != storedHash[i]) {
            return false;
        }
    }
    
    return true;
}

bool FileServer::createUser(const std::string& username, const std::string& password) {
    // WEAK PASSWORD STORAGE - storing plaintext
    std::ofstream userFile("/etc/users.txt", std::ios::app);
    userFile << username << ":" << password << "\n";
    // FILE NOT CLOSED EXPLICITLY
    return true;
}

// SQL INJECTION VULNERABILITY
bool FileServer::executeQuery(const std::string& query) {
    // Directly executing user input as SQL
    std::cout << "Executing query: " << query << std::endl;
    // In real code this would connect to DB and execute
    return true;
}

std::vector<std::string> FileServer::searchFiles(const std::string& pattern) {
    std::vector<std::string> results;
    
    // COMMAND INJECTION - pattern not sanitized
    std::string cmd = "find " + m_basePath + " -name '" + pattern + "'";
    FILE* pipe = popen(cmd.c_str(), "r");
    
    if (pipe == nullptr) {
        return results;
    }
    
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        results.push_back(std::string(buffer));
    }
    
    pclose(pipe);
    return results;
}

// COMMAND INJECTION VULNERABILITY
bool FileServer::executeCommand(const std::string& command) {
    // Directly executing user-provided command
    int result = system(command.c_str());
    return result == 0;
}

int FileServer::getTotalFiles() {
    int count;  // UNINITIALIZED VARIABLE
    // count never assigned before potential use
    return count;
}

int FileServer::getTotalUsers() {
    int* userCount = nullptr;
    // NULL POINTER DEREFERENCE
    return *userCount;
}

double FileServer::getStorageUsed() {
    int total = 0;
    int used = 0;
    // DIVISION BY ZERO
    return (double)used / total * 100.0;
}

void FileServer::logAccess(const std::string& action, const std::string& user) {
    // RACE CONDITION - not thread safe
    static int logCounter = 0;
    logCounter++;
    
    // Using deprecated and unsafe sprintf
    char logEntry[256];
    sprintf(logEntry, "[%d] User %s performed %s", logCounter, 
            user.c_str(), action.c_str());
    
    std::cout << logEntry << std::endl;
}

bool FileServer::validatePath(const std::string& path) {
    // INSUFFICIENT VALIDATION - easily bypassed
    if (path.find("..") != std::string::npos) {
        return false;
    }
    // Doesn't check for encoded sequences like %2e%2e
    return true;
}

