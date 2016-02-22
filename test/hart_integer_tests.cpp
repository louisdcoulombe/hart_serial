#include "catch.hpp"
#include <string>

#include "hart_integer.h"


TEST_CASE("hart_integer", "[types]")
{
    SECTION("serialize")
    {
        std::string expected("int:99"); 
        auto i = hart::HartInteger(99);

        REQUIRE(i.serialize() == expected);
    }

    SECTION("valid deserialize")
    {
        auto i = hart::HartInteger();
        auto s = i.deserialize("int:33");
        REQUIRE(s.ok());
        REQUIRE(33 == i.value());
    }

    SECTION("deserialize invalid int")
    {
        auto i = hart::HartInteger();
        auto s = i.deserialize("int:allo");
        REQUIRE(!s.ok());
        REQUIRE(s.error_code() == util::ErrorCode::INVALID_ARGUMENT);
        REQUIRE(0 == i.value());
    }

    SECTION("deserialize invalid prefix")
    {
        auto i = hart::HartInteger();
        auto s = i.deserialize("float:33");
        REQUIRE(!s.ok());
        REQUIRE(s.error_code() == util::ErrorCode::INVALID_ARGUMENT);
        REQUIRE(0 == i.value());
    }

    SECTION("operator []")
    {
        auto i = hart::HartInteger(0xDEADBEEF);
        REQUIRE(i[0] == 0xDE);
        REQUIRE(i[1] == 0xAD); 
        REQUIRE(i[2] == 0xBE);
        REQUIRE(i[3] == 0xEF);
    }
}

