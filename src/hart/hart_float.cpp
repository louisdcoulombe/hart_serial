#include <sstream>
#include <iostream>

#include "hart_float.h"

using namespace util;

hart::HartFloat::HartFloat(void) 
{
   m_data.reserve(m_size);
   m_data.assign(4, 0);
}

hart::HartFloat::HartFloat(float v)
{
    m_data.reserve(m_size);
    fromFloat(v);
}

size_t hart::HartFloat::size() const
{
    return m_size;
}

float hart::HartFloat::value() const
{
    return toFloat();
}

std::string hart::HartFloat::serialize()
{
    std::stringstream ss;
    ss << STRING << ":" << toFloat();    
    return ss.str();
}

util::Status hart::HartFloat::deserialize(std::string string)
{
    auto pos = string.find(':');
    if (pos == std::string::npos)
        return Status(ErrorCode::INVALID_ARGUMENT, "Could not find ':'");

    std::string prefix = string.substr(0, pos);
    if (prefix != STRING)
        return Status(ErrorCode::INVALID_ARGUMENT, "Invalid prefix");

    std::string strValue = string.substr(pos + 1, string.length());
    try
    {
        float value = std::stof(strValue);
        fromFloat(value);
    }
    catch(...)
    {
        m_data.assign(4, 0);
        return Status(ErrorCode::INVALID_ARGUMENT, "Could not parse float");
    }
    
    return Status();
}

uint8_t hart::HartFloat::operator[](int i)
{
    return m_data[i];
}

float hart::HartFloat::toFloat() const
{
    float retfloat = 0;
    uint8_t *floatbuff = (uint8_t*)&retfloat;
    floatbuff[3] = m_data[0];
    floatbuff[2] = m_data[1];
    floatbuff[1] = m_data[2];
    floatbuff[0] = m_data[3];

    return retfloat;
}

void hart::HartFloat::fromFloat(float v)
{
    uint8_t *floatbuff = (uint8_t*)&v;
    if (util::is_big_endian())
    {
        m_data[3] = floatbuff[3];
        m_data[2] = floatbuff[2];
        m_data[1] = floatbuff[1];
        m_data[0] = floatbuff[0]; 
    }
    else
    {
        m_data[3] = floatbuff[0];
        m_data[2] = floatbuff[1];
        m_data[1] = floatbuff[2];
        m_data[0] = floatbuff[3]; 
    }
}

