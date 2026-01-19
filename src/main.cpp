#include <iostream>
#include <string>
#include <vector>
#include <openssl/ssl.h>
#include <openssl/opensslv.h>
#include <sqlite3.h>
#include "Version.h"

// Duplicated function 1: Process user data
void processUserData(const std::string& username, int userId) {
    std::cout << "Processing user data..." << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "User ID: " << userId << std::endl;
    
    if (username.empty()) {
        std::cout << "Error: Username cannot be empty" << std::endl;
        return;
    }
    
    if (userId < 0) {
        std::cout << "Error: User ID must be positive" << std::endl;
        return;
    }
    
    std::cout << "Validating user credentials..." << std::endl;
    std::cout << "Checking database connection..." << std::endl;
    std::cout << "Fetching user profile..." << std::endl;
    std::cout << "User data processed successfully" << std::endl;
}

// Duplicated function 2: Process admin data (copy-paste of processUserData)
void processAdminData(const std::string& adminName, int adminId) {
    std::cout << "Processing admin data..." << std::endl;
    std::cout << "Admin name: " << adminName << std::endl;
    std::cout << "Admin ID: " << adminId << std::endl;
    
    if (adminName.empty()) {
        std::cout << "Error: Admin name cannot be empty" << std::endl;
        return;
    }
    
    if (adminId < 0) {
        std::cout << "Error: Admin ID must be positive" << std::endl;
        return;
    }
    
    std::cout << "Validating admin credentials..." << std::endl;
    std::cout << "Checking database connection..." << std::endl;
    std::cout << "Fetching admin profile..." << std::endl;
    std::cout << "Admin data processed successfully" << std::endl;
}

// Duplicated function 3: Process guest data (another copy-paste)
void processGuestData(const std::string& guestName, int guestId) {
    std::cout << "Processing guest data..." << std::endl;
    std::cout << "Guest name: " << guestName << std::endl;
    std::cout << "Guest ID: " << guestId << std::endl;
    
    if (guestName.empty()) {
        std::cout << "Error: Guest name cannot be empty" << std::endl;
        return;
    }
    
    if (guestId < 0) {
        std::cout << "Error: Guest ID must be positive" << std::endl;
        return;
    }
    
    std::cout << "Validating guest credentials..." << std::endl;
    std::cout << "Checking database connection..." << std::endl;
    std::cout << "Fetching guest profile..." << std::endl;
    std::cout << "Guest data processed successfully" << std::endl;
}

// Duplicated block 1: Calculate statistics
void calculateUserStatistics(const std::vector<int>& data) {
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
    
    std::cout << "User Statistics:" << std::endl;
    std::cout << "  Count: " << data.size() << std::endl;
    std::cout << "  Sum: " << sum << std::endl;
    std::cout << "  Min: " << min << std::endl;
    std::cout << "  Max: " << max << std::endl;
    std::cout << "  Average: " << average << std::endl;
}

// Duplicated block 2: Calculate statistics (copy-paste)
void calculateOrderStatistics(const std::vector<int>& data) {
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
    
    std::cout << "Order Statistics:" << std::endl;
    std::cout << "  Count: " << data.size() << std::endl;
    std::cout << "  Sum: " << sum << std::endl;
    std::cout << "  Min: " << min << std::endl;
    std::cout << "  Max: " << max << std::endl;
    std::cout << "  Average: " << average << std::endl;
}

// Duplicated block 3: Calculate statistics (another copy-paste)
void calculateProductStatistics(const std::vector<int>& data) {
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
    
    std::cout << "Product Statistics:" << std::endl;
    std::cout << "  Count: " << data.size() << std::endl;
    std::cout << "  Sum: " << sum << std::endl;
    std::cout << "  Min: " << min << std::endl;
    std::cout << "  Max: " << max << std::endl;
    std::cout << "  Average: " << average << std::endl;
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

    // Demo the duplicated functions
    processUserData("john_doe", 1001);
    std::cout << std::endl;
    
    processAdminData("admin_jane", 2001);
    std::cout << std::endl;
    
    processGuestData("guest_visitor", 3001);
    std::cout << std::endl;

    // Demo the duplicated statistics functions
    std::vector<int> sampleData = {10, 20, 30, 40, 50};
    calculateUserStatistics(sampleData);
    std::cout << std::endl;
    
    calculateOrderStatistics(sampleData);
    std::cout << std::endl;
    
    calculateProductStatistics(sampleData);

    return 0;
}
