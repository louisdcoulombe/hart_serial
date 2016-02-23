#include "hart_command.h"

#include <iostream>
#include <sstream>
#include <string>

hart::HartCommand::HartCommand() 
{
}

size_t hart::HartCommand::size() const
{
    return 0;
}

uint8_t hart::HartCommand::operator[](int i)
{
    (void) i;
    return 0;
}

std::string hart::HartCommand::serialize()
{
    std::stringstream ss;
    for (auto t : m_type_list)
    {
        ss << t->serialize();
        ss << ";";
    }
    
    // remove the last delimiter
    std::string retval = ss.str();
    return retval.erase(retval.size() - 1);
}

util::Status hart::HartCommand::deserialize(std::string value)
{
    auto tokens = util::split(value, ';');
    for (auto t : tokens)
        std::cout << t << std::endl;
    return util::Status();
}


util::Status hart::HartCommand::add_type(IHartType* t)
{
    m_type_list.push_back(t);
    return util::Status();
}

