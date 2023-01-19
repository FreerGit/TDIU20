#include <string>

#ifndef Time_H
#define Time_H

class Time {
public:
    Time() = default;
    Time(int hour, int minute, int second);
    Time(std::string time);

    Time operator +(int const& rhs);
    Time operator -(int const& rhs);
    Time operator ++(int);
    Time& operator ++();
    Time operator --(int);
    Time& operator --();

    bool operator >(Time const& rhs);
    bool operator <(Time const& rhs);
    bool operator ==(Time const& rhs);
    bool operator !=(Time const& rhs);
    bool operator <=(Time const& rhs);
    bool operator >=(Time const& rhs);

    int get_hour() const;
    int get_minute() const;
    int get_second() const;
    bool is_am() const;
    std::string to_string(bool const format = false) const;

private:
    void check_clock_bounds();
    int hour;
    int minute;
    int second;
};

#endif