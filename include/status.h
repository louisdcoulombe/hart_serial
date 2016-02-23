#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>
#include <sstream>

namespace util
{
    enum class ErrorCode
    {
        OK = 0,
        INVALID_ARGUMENT,
    };

    class Status
    {
    public:
        Status() : m_code(ErrorCode::OK) {}
        Status(ErrorCode error_code, std::string error_msg): m_code(error_code), m_msg(error_msg) {}

        bool ok() { return m_code == ErrorCode::OK; }
        const std::string& error_message() { return m_msg; }
        ErrorCode error_code() { return m_code; }
            
    private:
        ErrorCode m_code;
        std::string m_msg;
    };
   
   inline int is_big_endian(void)
   {
        union {
            uint32_t i;
            char c[4];
        } bint = {0x01020304};

        return bint.c[0] == 1; 
   } 

   inline std::vector<std::string> split(const std::string& str, char delimiter)
   {
       std::vector<std::string> tokens;

       std::stringstream ss(str);
       std::string item;
       while (std::getline(ss, item, delimiter))
               tokens.push_back(item);

       return tokens;
   }
};
#endif
