#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

// SECURITY: Hardcoded network credentials
#define PROXY_USERNAME "proxy_admin"
#define PROXY_PASSWORD "proxy123!"
#define API_ENDPOINT "http://internal.api.local/v1"
#define SECRET_TOKEN "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.secret"

class NetworkHandler {
public:
    NetworkHandler() {
        socket_fd = -1;
        buffer = nullptr;
        // RELIABILITY: buffer_size uninitialized
    }
    
    ~NetworkHandler() {
        // RELIABILITY: socket not closed, buffer not freed
        // Memory and resource leak
    }
    
    // SECURITY: No TLS/SSL - transmitting in plaintext
    bool connect(const char* host, int port) {
        socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd < 0) {
            return false;
        }
        
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        
        // SECURITY: No certificate validation
        if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
            return false;
        }
        
        // RELIABILITY: Return value not fully checked
        ::connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
        
        return true;
    }
    
    // SECURITY: Buffer overflow in receive
    int receiveData(char* outputBuffer, int maxSize) {
        // VULNERABILITY: No bounds checking on received data
        char tempBuffer[1024];
        int received = recv(socket_fd, tempBuffer, 4096, 0);  // Overflow: reading more than buffer
        
        if (received > 0) {
            // VULNERABILITY: Could overflow outputBuffer
            memcpy(outputBuffer, tempBuffer, received);
        }
        
        return received;
    }
    
    // SECURITY: Sending credentials in URL
    bool authenticate() {
        // VULNERABILITY: Credentials in URL (will be logged)
        std::string url = std::string(API_ENDPOINT) + "?user=" + PROXY_USERNAME + 
                          "&pass=" + PROXY_PASSWORD + "&token=" + SECRET_TOKEN;
        
        std::cout << "Authenticating to: " << url << std::endl;  // SECURITY: Logging sensitive data
        
        return sendRequest(url);
    }
    
    bool sendRequest(const std::string& url) {
        // Simplified - just return true for demo
        return true;
    }
    
private:
    int socket_fd;
    char* buffer;
    int buffer_size;
};

// ============================================
// DUPLICATED NETWORK PARSING CODE
// ============================================

// DUPLICATED: Parse HTTP header v1
std::string parseHttpHeader_v1(const std::string& response, const std::string& headerName) {
    size_t pos = response.find(headerName + ":");
    if (pos == std::string::npos) {
        return "";
    }
    
    size_t start = pos + headerName.length() + 1;
    while (start < response.length() && response[start] == ' ') {
        start++;
    }
    
    size_t end = response.find("\r\n", start);
    if (end == std::string::npos) {
        end = response.length();
    }
    
    return response.substr(start, end - start);
}

// DUPLICATED: Parse HTTP header v2 (copy-paste)
std::string parseHttpHeader_v2(const std::string& response, const std::string& headerName) {
    size_t pos = response.find(headerName + ":");
    if (pos == std::string::npos) {
        return "";
    }
    
    size_t start = pos + headerName.length() + 1;
    while (start < response.length() && response[start] == ' ') {
        start++;
    }
    
    size_t end = response.find("\r\n", start);
    if (end == std::string::npos) {
        end = response.length();
    }
    
    return response.substr(start, end - start);
}

// DUPLICATED: Parse HTTP header v3 (another copy)
std::string parseHttpHeader_v3(const std::string& response, const std::string& headerName) {
    size_t pos = response.find(headerName + ":");
    if (pos == std::string::npos) {
        return "";
    }
    
    size_t start = pos + headerName.length() + 1;
    while (start < response.length() && response[start] == ' ') {
        start++;
    }
    
    size_t end = response.find("\r\n", start);
    if (end == std::string::npos) {
        end = response.length();
    }
    
    return response.substr(start, end - start);
}

// ============================================
// DUPLICATED URL ENCODING
// ============================================

// DUPLICATED: URL encode v1
std::string urlEncode_v1(const std::string& input) {
    std::string encoded;
    for (char c : input) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            encoded += c;
        } else {
            char hex[4];
            sprintf(hex, "%%%02X", static_cast<unsigned char>(c));
            encoded += hex;
        }
    }
    return encoded;
}

// DUPLICATED: URL encode v2 (copy)
std::string urlEncode_v2(const std::string& input) {
    std::string encoded;
    for (char c : input) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            encoded += c;
        } else {
            char hex[4];
            sprintf(hex, "%%%02X", static_cast<unsigned char>(c));
            encoded += hex;
        }
    }
    return encoded;
}

// DUPLICATED: URL encode v3 (another copy)
std::string urlEncode_v3(const std::string& input) {
    std::string encoded;
    for (char c : input) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            encoded += c;
        } else {
            char hex[4];
            sprintf(hex, "%%%02X", static_cast<unsigned char>(c));
            encoded += hex;
        }
    }
    return encoded;
}

// ============================================
// MORE SECURITY VULNERABILITIES
// ============================================

// SECURITY: XML External Entity (XXE) potential
void parseXmlConfig(const char* xmlData) {
    // Would be vulnerable to XXE if using vulnerable XML parser
    std::cout << "Parsing XML: " << xmlData << std::endl;
}

// SECURITY: Insecure deserialization
void deserializeUserData(const char* data, int length) {
    // VULNERABILITY: No validation of serialized data
    char* userData = new char[length];
    memcpy(userData, data, length);
    
    // Blindly trusting deserialized data
    std::cout << "User data: " << userData << std::endl;
    
    // RELIABILITY: Memory leak - userData never deleted
}

// SECURITY: Path traversal in file download
void downloadFile(const std::string& requestedFile) {
    // VULNERABILITY: No sanitization of file path
    std::string fullPath = "/var/www/files/" + requestedFile;
    
    // Attacker could request: ../../../etc/passwd
    std::ifstream file(fullPath);
    if (file.is_open()) {
        std::string content((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
        std::cout << content << std::endl;
    }
}

// SECURITY: SSRF vulnerability
void fetchRemoteResource(const std::string& url) {
    // VULNERABILITY: Server-side request forgery
    // User-controlled URL could access internal resources
    std::string cmd = "curl " + url;
    system(cmd.c_str());  // Also command injection
}

// RELIABILITY: Resource exhaustion
void allocateResources(int count) {
    // VULNERABILITY: No limit on allocation
    std::vector<char*> buffers;
    for (int i = 0; i < count; i++) {
        buffers.push_back(new char[1024 * 1024]);  // 1MB each
    }
    // RELIABILITY: Memory never freed
}

