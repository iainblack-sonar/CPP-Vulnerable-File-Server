#include "Database.h"
#include <iostream>
#include <cstring>
#include <sstream>

Database::Database() {
    m_db = nullptr;
    m_connected = false;
}

Database::~Database() {
    // RESOURCE LEAK - disconnect not always called
    if (m_db != nullptr) {
        // sqlite3_close(m_db);  // Commented out - resource leak
    }
}

bool Database::connect(const std::string& dbPath) {
    int rc = sqlite3_open(dbPath.c_str(), &m_db);
    if (rc != SQLITE_OK) {
        m_lastError = sqlite3_errmsg(m_db);
        return false;
    }
    m_connected = true;
    return true;
}

void Database::disconnect() {
    if (m_db != nullptr) {
        sqlite3_close(m_db);
        m_db = nullptr;
    }
    m_connected = false;
}

// SQL INJECTION - directly concatenating user input
bool Database::executeRawQuery(const std::string& query) {
    if (!m_connected || m_db == nullptr) {
        return false;
    }
    
    char* errMsg = nullptr;
    // VULNERABILITY: Executing raw, unsanitized query
    int rc = sqlite3_exec(m_db, query.c_str(), nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        m_lastError = errMsg;
        sqlite3_free(errMsg);
        return false;
    }
    
    return true;
}

// SQL INJECTION VULNERABILITY
std::vector<std::string> Database::findUsers(const std::string& username) {
    std::vector<std::string> results;
    
    // VULNERABLE: String concatenation for SQL query
    std::string query = "SELECT * FROM users WHERE username = '" + username + "'";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(m_db, query.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        return results;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* text = sqlite3_column_text(stmt, 0);
        if (text != nullptr) {
            results.push_back(reinterpret_cast<const char*>(text));
        }
    }
    
    sqlite3_finalize(stmt);
    return results;
}

// SQL INJECTION + PLAINTEXT PASSWORD STORAGE
bool Database::updateUserPassword(const std::string& username, const std::string& newPassword) {
    // VULNERABILITY: SQL Injection
    std::string query = "UPDATE users SET password = '" + newPassword + 
                        "' WHERE username = '" + username + "'";
    
    // SECURITY ISSUE: Password stored in plaintext
    return executeRawQuery(query);
}

// SQL INJECTION VULNERABILITY
bool Database::addUser(const std::string& username, const std::string& password, int role) {
    // VULNERABILITY: SQL Injection through string concatenation
    std::stringstream ss;
    ss << "INSERT INTO users (username, password, role) VALUES ('"
       << username << "', '" << password << "', " << role << ")";
    
    return executeRawQuery(ss.str());
}

// SQL INJECTION VULNERABILITY  
bool Database::deleteUser(const std::string& username) {
    // VULNERABILITY: SQL Injection
    std::string query = "DELETE FROM users WHERE username = '" + username + "'";
    return executeRawQuery(query);
}

// SQL INJECTION VULNERABILITY
bool Database::addFileRecord(const std::string& filename, int size, const std::string& owner) {
    // VULNERABILITY: SQL Injection
    std::string query = "INSERT INTO files (name, size, owner) VALUES ('" +
                        filename + "', " + std::to_string(size) + ", '" + owner + "')";
    return executeRawQuery(query);
}

// SQL INJECTION VULNERABILITY
std::vector<std::string> Database::getFilesByOwner(const std::string& owner) {
    std::vector<std::string> results;
    
    // VULNERABILITY: SQL Injection
    std::string query = "SELECT name FROM files WHERE owner = '" + owner + "'";
    
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(m_db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return results;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* text = sqlite3_column_text(stmt, 0);
        if (text != nullptr) {
            results.push_back(reinterpret_cast<const char*>(text));
        }
    }
    
    sqlite3_finalize(stmt);
    return results;
}

// Helper with SQL Injection
std::string Database::buildQuery(const std::string& table, const std::string& condition) {
    // VULNERABILITY: No input sanitization
    return "SELECT * FROM " + table + " WHERE " + condition;
}

