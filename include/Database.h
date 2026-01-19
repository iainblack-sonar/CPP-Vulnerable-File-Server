#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <sqlite3.h>

class Database {
public:
    Database();
    ~Database();
    
    bool connect(const std::string& dbPath);
    void disconnect();
    
    // Vulnerable query methods - SQL INJECTION
    bool executeRawQuery(const std::string& query);
    std::vector<std::string> findUsers(const std::string& username);
    bool updateUserPassword(const std::string& username, const std::string& newPassword);
    
    // User operations
    bool addUser(const std::string& username, const std::string& password, int role);
    bool deleteUser(const std::string& username);
    
    // File metadata
    bool addFileRecord(const std::string& filename, int size, const std::string& owner);
    std::vector<std::string> getFilesByOwner(const std::string& owner);

private:
    sqlite3* m_db;
    bool m_connected;
    std::string m_lastError;
    
    // Helper that doesn't sanitize input
    std::string buildQuery(const std::string& table, const std::string& condition);
};

#endif // DATABASE_H

