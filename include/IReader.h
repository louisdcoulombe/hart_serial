#ifndef HTS_IREADER_H
#define HTS_IREADER_H

#include <stdint.h>
#include <iostream>

namespace hts
{
    class IReader
    {
    public:
        virtual std::vector<uint8_t> read() = 0;
    };

    class ReaderConsole : public IReader
    {
    public:
        virtual std::vector<uint8_t> read() override 
        {
            std::string input;
            std::getline(std::cin, input);

            if (input == "quit")
                return std::vector<uint8_t>();
            
            std::vector<uint8_t> data;
            std::copy(input.begin(), input.end(), std::back_inserter(data));
            return data;
        }
    };
}


#endif // !HTS_IREADER_H

