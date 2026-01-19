#include <iostream>
#include <string>
#include <vector>
#include <openssl/ssl.h>
#include <openssl/opensslv.h>
#include <sqlite3.h>
#include "Version.h"

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

    return 0;
}
