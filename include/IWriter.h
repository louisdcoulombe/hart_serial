#ifndef HTS_IWRITER_H
#define HTS_IWRITER_H

#include <stdint.h>
#include <iostream>

namespace hts
{
    class IWriter
    {
    public:
        virtual uint8_t write(std::vector<uint8_t>& data) = 0;
    };

    class WriterConsole : public IWriter
    {
    public:
        virtual uint8_t write(std::vector<uint8_t>& data) override 
        {
            for each (auto var in data)
            {
                std::cout << "WriterConsole:: " << var << '\n';
            }

            return 0;
        }
    };
}


#endif // !HTS_IWRITER_H

