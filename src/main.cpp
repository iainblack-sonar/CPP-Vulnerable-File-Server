#include <iostream>
#include <string>
#include <vector>
#include <openssl/ssl.h>
#include <openssl/opensslv.h>
#include <sqlite3.h>
#include "Version.h"
#include "FileServer.h"
#include "Database.h"
#include "Utils.h"

// SECURITY: Hardcoded credentials at file scope
const char* DEFAULT_ADMIN_USER = "admin";
const char* DEFAULT_ADMIN_PASS = "admin123";
const char* DATABASE_PATH = "/var/db/fileserver.db";

// Generic function to process entity data
void processEntityData(const std::string& entityType, const std::string& name, int id) {
    std::cout << "Processing " << entityType << " data..." << std::endl;
    std::cout << entityType << " name: " << name << std::endl;
    std::cout << entityType << " ID: " << id << std::endl;
    
    if (name.empty()) {
        std::cout << "Error: " << entityType << " name cannot be empty" << std::endl;
        return;
    }
    
    if (id < 0) {
        std::cout << "Error: " << entityType << " ID must be positive" << std::endl;
        return;
    }
    
    std::cout << "Validating " << entityType << " credentials..." << std::endl;
    std::cout << "Checking database connection..." << std::endl;
    std::cout << "Fetching " << entityType << " profile..." << std::endl;
    std::cout << entityType << " data processed successfully" << std::endl;
}

// Generic function to calculate statistics
void calculateStatistics(const std::string& category, const std::vector<int>& data) {
    if (data.empty()) {
        std::cout << "No data to process" << std::endl;
        return;
    }
    
    int sum = 0;
    int min = data[0];
    int max = data[0];
    
    for (size_t i = 0; i < data.size(); i++) {
        sum += data[i];
        if (data[i] < min) min = data[i];
        if (data[i] > max) max = data[i];
    }
    
    double average = static_cast<double>(sum) / data.size();
    
    std::cout << category << " Statistics:" << std::endl;
    std::cout << "  Count: " << data.size() << std::endl;
    std::cout << "  Sum: " << sum << std::endl;
    std::cout << "  Min: " << min << std::endl;
    std::cout << "  Max: " << max << std::endl;
    std::cout << "  Average: " << average << std::endl;
}

// SECURITY: Function that logs sensitive data
void logUserActivity(const std::string& username, const std::string& password, 
                     const std::string& action) {
    // SECURITY ISSUE: Logging password in plaintext
    std::cout << "User: " << username << " Password: " << password 
              << " Action: " << action << std::endl;
}

// RELIABILITY: Function with potential null dereference
void processUserRequest(const char* request) {
    // No null check before use
    int len = strlen(request);  // Crash if request is null
    std::cout << "Processing request of length: " << len << std::endl;
}

// RELIABILITY: Function with memory leak
char* createBuffer(int size) {
    char* buffer = new char[size];
    // BUG: If caller forgets to delete, memory leaks
    // No RAII pattern used
    return buffer;
}

// MAINTAINABILITY: Long function with too many responsibilities
void initializeSystem(bool enableLogging, bool enableAuth, bool enableEncryption,
                      const std::string& logPath, const std::string& dbPath,
                      int maxConnections, int timeout, bool debugMode) {
    // This function does too many things
    std::cout << "Starting system initialization..." << std::endl;
    
    // Initialize logging
    if (enableLogging) {
        std::cout << "Enabling logging to: " << logPath << std::endl;
        // ... logging setup code
    }
    
    // Initialize authentication
    if (enableAuth) {
        std::cout << "Enabling authentication" << std::endl;
        // SECURITY: Using hardcoded default credentials
        std::cout << "Default admin: " << DEFAULT_ADMIN_USER << std::endl;
        // ... auth setup code
    }
    
    // Initialize encryption
    if (enableEncryption) {
        std::cout << "Enabling encryption" << std::endl;
        // ... encryption setup code
    }
    
    // Initialize database
    std::cout << "Connecting to database: " << dbPath << std::endl;
    // ... database setup code
    
    // Configure connections
    std::cout << "Max connections: " << maxConnections << std::endl;
    std::cout << "Timeout: " << timeout << std::endl;
    
    // Debug mode
    if (debugMode) {
        std::cout << "DEBUG MODE ENABLED - NOT FOR PRODUCTION" << std::endl;
        // SECURITY: Debug mode might expose sensitive info
    }
    
    std::cout << "System initialization complete" << std::endl;
}

int main() {
    // Print welcome message
    std::cout << "========================================" << std::endl;
    std::cout << "  " << Version::getVersionString() << std::endl;
    std::cout << "  " << Version::DESCRIPTION << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    // Display OpenSSL version
    std::cout << "OpenSSL Version: " << OPENSSL_VERSION_TEXT << std::endl;

    // Display SQLite version
    std::cout << "SQLite Version: " << sqlite3_libversion() << std::endl;
    std::cout << std::endl;

    // SECURITY: Seeding random with predictable value
    srand(12345);  // Predictable seed

    // Demo the generic entity processing
    processEntityData("User", "john_doe", 1001);
    std::cout << std::endl;
    
    processEntityData("Admin", "admin_jane", 2001);
    std::cout << std::endl;
    
    processEntityData("Guest", "guest_visitor", 3001);
    std::cout << std::endl;

    // Demo the generic statistics function
    std::vector<int> sampleData = {10, 20, 30, 40, 50};
    calculateStatistics("User", sampleData);
    std::cout << std::endl;
    
    calculateStatistics("Order", sampleData);
    std::cout << std::endl;
    
    calculateStatistics("Product", sampleData);

    // SECURITY: Logging sensitive information
    logUserActivity("admin", "secretpassword123", "login");

    // Initialize with debug mode on (security issue in production)
    initializeSystem(true, true, false, "/var/log/app.log", 
                     DATABASE_PATH, 100, 30, true);

    return 0;
}
