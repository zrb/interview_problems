#include <cstring>
#include <string>
#include <utility>

namespace zrb::interview_problems
{

void reverse(char * s, std::size_t const l)
{
    using std::swap;
    auto * p = s + l - 1;
    while (s < p)
        swap(*s++, *p--);
}

void reverse(char * s)
{
    reverse(s, std::strlen(s));
}

std::string reverse(char const * s)
{
    std::string v{s};    
    reverse(v.data(), v.length());
    return v;
}

}

using namespace zrb::interview_problems;

#include <catch2/catch.hpp>

TEST_CASE("inplace string reversal", "[inplace_string_reversal]") {
    REQUIRE(reverse("") == "");  //  empty
    REQUIRE(reverse("a") == "a");  //  1 char
    REQUIRE(reverse("hello") == "olleh");  //  odd length
    REQUIRE(reverse("hello!") == "!olleh");  //  even length
}

