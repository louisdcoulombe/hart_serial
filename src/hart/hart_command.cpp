#include "hart_command.h"

hart::HartCommand()
{
}

size_t hart::HartCommand::size() const
{
    return 0;
}
uint8_t hart::HartCommand::operator[](int i)
{
    return 0;
}

std::string hart::HartCommand::serialize()
{
    return "";
}

util::Status hart::HartCommand::deserialize(std::string value)
{
    return Status();
}

