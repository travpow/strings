
#include "fstring.hpp"
#include <cassert>
#include <iostream>
#include <string>

#define CATCH_CONFIG_MAIN
#include "Catch/include/catch.hpp"

using std::string;
using std::cout;
using std::endl;

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
    fstring<64> a("My bologna has a first name");
    fstring<64> b(" it's o-s-c-a-r!");

    fstring<64> c = a + b;
    string expected = "My bologna has a first name it's o-s-c-a-r!";
    REQUIRE(expected == c.c_str());
    REQUIRE(c == expected);
}

TEST_CASE("Concat of larger and smaller string") {
    fstring<64> a = "A string to append: ";
    fstring<1> b = "1";
    fstring<2> c = "2";

    fstring<64> d = a;
    d += b;
    d += c;

    fstring<64> e = a + b + c;

    REQUIRE(d == e);

    cout << "Concat: " << d << endl;
    cout << "Concat: " << a << endl;

    REQUIRE(d.size() == e.size());
    REQUIRE(d.size() == (a.size() + 2));
}
