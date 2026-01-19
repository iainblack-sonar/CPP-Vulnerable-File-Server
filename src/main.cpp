#include <iostream>
#include <openssl/ssl.h>
#include <openssl/opensslv.h>
#include <sqlite3.h>
#include "Version.h"

int main() {
    // Print welcome message
    std::cout << "========================================" << std::endl;
    std::cout << "  " << Version::getVersionString() << std::endl;
    std::cout << "  " << Version::DESCRIPTION << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    // Display OpenSSL version (vulnerable version for SCA demo)
    std::cout << "OpenSSL Version: " << OPENSSL_VERSION_TEXT << std::endl;

    // Display SQLite version (vulnerable version for SCA demo)
    std::cout << "SQLite Version: " << sqlite3_libversion() << std::endl;

    return 0;
}

