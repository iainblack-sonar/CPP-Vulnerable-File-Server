#ifndef VERSION_H
#define VERSION_H

#include <string>

namespace Version {
    constexpr const char* PROJECT_NAME = "CPP-Vulnerable-File-Server";
    constexpr const char* VERSION = "1.0.0";
    constexpr const char* DESCRIPTION = "A C++ project for SCA vulnerability demonstration";
    
    inline std::string getVersionString() {
        return std::string(PROJECT_NAME) + " v" + VERSION;
    }
}

#endif // VERSION_H

