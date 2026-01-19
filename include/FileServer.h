#ifndef FILE_SERVER_H
#define FILE_SERVER_H

#include <string>
#include <vector>
#include <fstream>

// Hardcoded credentials - SECURITY ISSUE
#define ADMIN_PASSWORD "admin123"
#define API_KEY "sk-1234567890abcdef"
#define DB_CONNECTION_STRING "mysql://root:password@localhost:3306/prod"

class FileServer {
public:
    FileServer();
    ~FileServer();

    // File operations
    bool readFile(const std::string& filename, std::string& content);
    bool writeFile(const std::string& filename, const std::string& content);
    bool deleteFile(const std::string& filename);
    
    // User management
    bool authenticateUser(const char* username, const char* password);
    bool createUser(const std::string& username, const std::string& password);
    
    // Database operations
    bool executeQuery(const std::string& query);
    std::vector<std::string> searchFiles(const std::string& pattern);
    
    // System operations
    bool executeCommand(const std::string& command);
    
    // Statistics
    int getTotalFiles();
    int getTotalUsers();
    double getStorageUsed();

private:
    std::string m_basePath;
    std::fstream* m_logFile;  // Potential memory leak
    char* m_buffer;           // Potential memory leak
    int m_bufferSize;
    bool m_initialized;
    
    // Internal helpers
    void logAccess(const std::string& action, const std::string& user);
    bool validatePath(const std::string& path);
};

#endif // FILE_SERVER_H

