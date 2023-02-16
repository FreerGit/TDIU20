#include <string>

#ifndef Time_H
#define Time_H

class Time {
public:
    Time() = default;
    Time(int hour, int minute, int second);
    Time(std::string time);

    Time operator +(int const& rhs) const;
    Time operator -(int const& rhs) const;
    Time operator ++(int);
    Time& operator ++();
    Time operator --(int);
    Time& operator --();


    bool operator >(Time const& rhs) const;
    bool operator <(Time const& rhs) const;
    bool operator ==(Time const& rhs) const;
    bool operator !=(Time const& rhs) const;
    bool operator <=(Time const& rhs) const;
    bool operator >=(Time const& rhs) const;

    int get_hour() const;
    int get_minute() const;
    int get_second() const;
    bool is_am() const;
    std::string to_string(bool const format = false) const;

private:
    void check_clock_bounds(Time const* t) const;
    std::string digit_helper(int const time_t) const;
    
    int hour;
    int minute;
    int second;
};

Time operator+(int const& lhs, Time const& rhs);

std::ostream& operator<<(std::ostream &os, Time const &ti);
std::istream& operator>>(std::istream &is, Time &ti);

#endif