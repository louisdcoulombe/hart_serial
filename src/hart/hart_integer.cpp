#include <sstream>
#include <iostream>

#include "hart_integer.h"

using namespace util;

hart::HartInteger::HartInteger(void) 
{
   m_data.reserve(m_size);
   m_data.assign(4, 0);
}

hart::HartInteger::HartInteger(int v)
{
    m_data.reserve(m_size);
    fromInt(v);
}

size_t hart::HartInteger::size() const
{
    return m_size;
}

int hart::HartInteger::value() const
{
    return toInt();
}

std::string hart::HartInteger::serialize()
{
    std::stringstream ss;
    ss << STRING << ":" << toInt();    
    return ss.str();
}

util::Status hart::HartInteger::deserialize(std::string string)
{
    auto pos = string.find(':');
    if (pos == std::string::npos)
        return Status(ErrorCode::INVALID_ARGUMENT, "Could not find ':'");

    std::string prefix = string.substr(0, pos);
    if (prefix != STRING)
        return Status(ErrorCode::INVALID_ARGUMENT, "Invalid prefix");

    std::string strValue = string.substr(pos + 1, string.length());
    std::cout << strValue;
    try
    {
        int value = std::stoi(strValue);
        fromInt(value);
    }
    catch(...)
    {
        m_data.assign(4, 0);
        return Status(ErrorCode::INVALID_ARGUMENT, "Could not parse integer");
    }
    
    return Status();
}

uint8_t hart::HartInteger::operator[](int i)
{
    return m_data[i];
}

int hart::HartInteger::toInt() const
{
    int v = (m_data[0] << 24) |
            (m_data[1] << 16) |
            (m_data[2] << 8) |
            m_data[3];
    return v;
}

void hart::HartInteger::fromInt(int v)
{
    if (util::is_big_endian())
    {
        m_data[3] = (v >> 24) & 0xFF;
        m_data[2] = (v >> 16) & 0xFF;
        m_data[1] = (v >> 8) & 0xFF;
        m_data[0] = v & 0xFF;
    }
    else
    {
        m_data[0] = (v >> 24) & 0xFF;
        m_data[1] = (v >> 16) & 0xFF;
        m_data[2] = (v >> 8) & 0xFF;
        m_data[3] = v & 0xFF;
    }
}

