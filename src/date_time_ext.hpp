//
// Extended boost::date_time functionality
//

#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <sstream>
#include <vector>

using namespace boost::gregorian;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// Helper functions

auto inc_year(date d, int n = 1) noexcept
    // increment the year but keep month and day the same
{
    return date{d.year() + n, d.month(), d.day()};
}

auto date_in_year(date d, greg_year y = day_clock::local_day().year()) noexcept
    // return date d in the provided year
{
    return date{y, d.month(), d.day()};
}

auto next_occurrence(date d, date ref = day_clock::local_day()) noexcept
    // return the next occurrence of date d after reference date
{
    auto d_ref_year = date_in_year(d, ref.year());
    return (d_ref_year <= ref) ? inc_year(d_ref_year) : d_ref_year;
}

auto next_date_of_day(date d, greg_day wd) noexcept
    // return the year in which date d falls on weekday wd
{
    do {
        d = inc_year(d);
    } while (d.day_of_week() != wd);

    return d;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

auto get_date_results(const std::string& s)
    // return vector<string> report of date data
{
    std::vector<std::string> res;
    std::stringstream ss1;          // QUESTION: Is there a better way?
    std::stringstream ss2;
    std::stringstream ss3;

    res.push_back(s);

    auto birthday(from_simple_string(s));
    ss1 << "You were born on a "
        << birthday.day_of_week().as_long_string() << '.';
    res.emplace_back(ss1.str());

    auto this_bd = date_in_year(birthday);
    auto next_bd = next_occurrence(this_bd);
    auto days_away = (next_bd - day_clock::local_day()).days();
    ss2 << "Your next birthday is in "
        << days_away << " days on a "
        << next_bd.day_of_week().as_long_string() << '.';
    res.emplace_back(ss2.str());

    auto sat_bd = next_date_of_day(inc_year(next_bd), Saturday);
    ss3 << "The next time your birthday is on a Saturday is in "
        << sat_bd.year() << '.';
    res.emplace_back(ss3.str());

    return res;
}
