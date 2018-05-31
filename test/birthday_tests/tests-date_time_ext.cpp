// 
// date_time_ext.hpp tests
//

#include "../lib/catch.hpp"

#include "../../src/date_time_ext.hpp"

// Most helper functions reference "today" by default
auto today = day_clock::local_day();

// auto inc_year(date d, int n = 1)
TEST_CASE("inc_year increases year appropriately", "[inc_year]") {
    auto d = date{1979, 2, 27};
    
    SECTION("inc_year increases only year") {
        auto result = inc_year(d);
        REQUIRE(result.year() == 1980);
        REQUIRE(result.month() == 2);
        REQUIRE(result.day() == 27);
    }

    SECTION("2 arg inc_year increases year appropriately") {
        REQUIRE(inc_year(d, 1).year() == 1980);
        REQUIRE(inc_year(d, -1).year() == 1978);
        REQUIRE(inc_year(d, 2).year() == 1981);
        REQUIRE(inc_year(d, 50).year() == 2029);
        REQUIRE(inc_year(d, 100).year() == 2079);
    }
}

// auto date_in_year(date d, greg_year y = day_clock::local_day().year())
TEST_CASE("date_in_year returns date in ref year", "[date_in_year]") {
    auto xbox_launch = date{2001, 11, 15};

    SECTION("1 arg references today") {
        auto result = date_in_year(xbox_launch);
        REQUIRE(result.year() == today.year());
        REQUIRE(result.month() == xbox_launch.month());
        REQUIRE(result.day() == xbox_launch.day());
    }

    SECTION("2 arg references provided year") {
        REQUIRE(date_in_year(xbox_launch, 2015).year() == 2015);    // future
        REQUIRE(date_in_year(xbox_launch, 2001).year() == 2001);    // same
        REQUIRE(date_in_year(xbox_launch, 1990).year() == 1990);    // past
    }
}

// auto next_occurrence(date d, date ref = day_clock::local_day())
TEST_CASE("next_occurrence returns next m/d date after reference",
        "[next_occurrence]") {
    auto one_day = date_duration{1};

    SECTION("1 arg next_occurrence references today") {
        auto yesterday = today - one_day;
        REQUIRE(next_occurrence(yesterday).year() == yesterday.year() + 1);
        REQUIRE(next_occurrence(yesterday).month() == yesterday.month());
        REQUIRE(next_occurrence(yesterday).day() == yesterday.day());

        auto tomorrow = today + one_day;
        REQUIRE(next_occurrence(tomorrow).year() == tomorrow.year());
        REQUIRE(next_occurrence(tomorrow).month() == tomorrow.month());
        REQUIRE(next_occurrence(tomorrow).day() == tomorrow.day());
    }

    SECTION("next_occurrence returns future date") {
        auto years_ago = date{2015, 2, 18};      // Feb 18, 2015
        REQUIRE(next_occurrence(years_ago).year() >= today.year());
    }

    SECTION("next_occurrence of today is next year") {
        REQUIRE(next_occurrence(today).year() == today.year() + 1);
    }
}

// auto next_date_of_day(date d, greg_day wd)
TEST_CASE("next_date_of_day returns the next year date is on given weekday",
        "[next_date_of_day]") {
    auto d17 = date{2017, 5, 30};               // a Tuesday
    auto d18 = date{2018, 5, 30};               // a Wednesday
    auto d19 = date{2019, 5, 30};               // a Thursday
    auto d20 = date{2020, 5, 30};               // a Saturday (leap year)
    REQUIRE(next_date_of_day(d17, Wednesday).year() == 2018);
    REQUIRE(next_date_of_day(d17, Saturday).year() == 2020);
    REQUIRE(next_date_of_day(d20, Saturday).year() > 2020);     // not 2020
}

// auto get_date_results(const std::string& s)
SCENARIO("get_date_results") {

    GIVEN("a properly formatted date-string is passed") {
        std::string date_str = "1979-02-27";
        std::vector<std::string> vs = get_date_results(date_str);

        THEN("a vector filled with 4 strings is returned") {
            REQUIRE(vs.size() == 4);
        }
    }
}

