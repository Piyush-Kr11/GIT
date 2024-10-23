#include <iostream>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>

std::string sha1(const std::string& input) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    std::ostringstream oss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return oss.str();
}

int main() {
    std::string input = "Hello, world!";
    std::string hash = sha1(input);
    
    std::cout << "SHA-1 hash of \"" << input << "\": " << hash << std::endl;
    return 0;
}
