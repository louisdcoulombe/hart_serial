#include "catch.hpp"
#include <string>

#include "hart_command.h"
#include "hart_integer.h"
#include "hart_float.h"

using namespace util;
using namespace hart;

TEST_CASE("hart_command", "[types]")
{
    SECTION("serialize")
    {
        HartFloat f = HartFloat(44.3);
        HartCommand c = HartCommand();
        c.add_type(&f);
        c.add_type(&f);
        c.add_type(&f);

        std::string expected = "float:44.3;float:44.3;float:44.3";
        REQUIRE(c.serialize() == expected);
    }

    SECTION("deserialize")
    {
        HartCommand c = HartCommand();
        std::string expected = "float:44.3;float:44.3;float:44.3";
        c.deserialize(expected);

    }
}
 
