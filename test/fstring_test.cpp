
#include "fstring.hpp"
#include <cassert>
#include <iostream>

#define CATCH_CONFIG_MAIN
#include "Catch/include/catch.hpp"

TEST_CASE("Cannot append to a zero-sized buffer") {
    fstring<0> one;
    one += "test";
    REQUIRE(one.size() == 0);
}

TEST_CASE("Truncating a string sets the dirty bit") {
    const char* const test = "This is a test";
    fstring<10> two = test;
    two[4] = '\0';
    REQUIRE(two.size() == 4);
}

TEST_CASE("Concat two strings") {
    fstring<64> a("My bologa has a first name");
    fstring<64> b(" it's OSCAR!");

    fstring<64> c = a + b;
    string expected = "My bologna has a first name it's OSCAR!";
    REQUIRE(expected == c.c_str());
    REQUIRE(c == expected);
}
