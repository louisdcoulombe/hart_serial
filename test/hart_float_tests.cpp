#include "catch.hpp"
#include <string>

#include "hart_float.h"


TEST_CASE("hart_float", "[types]")
{
    SECTION("serialize")
    {
        std::string expected("float:13.3"); 
        auto i = hart::HartFloat(13.3);

        REQUIRE(i.serialize() == expected);
    }

    SECTION("valid deserialize")
    {
        auto i = hart::HartFloat();
        auto s = i.deserialize("float:13.3");
        REQUIRE(s.ok());
        REQUIRE(13.3f == i.value());
    }

    SECTION("deserialize invalid int")
    {
        auto i = hart::HartFloat();
        auto s = i.deserialize("float:allo");
        REQUIRE(!s.ok());
        REQUIRE(s.error_code() == util::ErrorCode::INVALID_ARGUMENT);
        REQUIRE(0.0f == i.value());
    }

    SECTION("deserialize invalid prefix")
    {
        auto i = hart::HartFloat();
        auto s = i.deserialize("int:13.3");
        REQUIRE(!s.ok());
        REQUIRE(s.error_code() == util::ErrorCode::INVALID_ARGUMENT);
        REQUIRE(0 == i.value());
    }

    SECTION("operator []")
    {
        float x = 13.3;
        uint8_t* expected = (uint8_t*)&x;
        auto i = hart::HartFloat(x);
        REQUIRE(i[0] == expected[3]);
        REQUIRE(i[1] == expected[2]);
        REQUIRE(i[2] == expected[1]);
        REQUIRE(i[3] == expected[0]);
    }
}

