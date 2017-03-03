
#include "sstring.hpp"
#include <string>

#include "Catch/include/catch.hpp"

using std::string;
using std::cout;
using std::endl;

TEST_CASE("Can extract substring, call substr() from string") {
    string input = "this is a test of shallow string";
    sstring res(input);

    res.substr(10, 4);

    REQUIRE(res == "test");
}
