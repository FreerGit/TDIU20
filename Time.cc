#include "Time.h"
#include <stdexcept>
#include <sstream>

using namespace std;


void Time::check_clock_bounds() {
    if (this->hour > 23 || this->hour < 0) {
        throw logic_error{"An hour has to be in the range 0-24 (inclusive)"};
    } 
    if (this->minute > 59 || this->minute < 0 ) {
        throw logic_error{"An minute has to be in the range 0-59 (inclusive)"};
    }

    if (this->second > 59 || this->second < 0) {
        throw logic_error{"An hour has to be in the range 0-59 (inclusive)"};
    }
}

Time::Time(int hour, int minute, int second) : hour{hour}, minute{minute}, second{second} {
    this->check_clock_bounds();
}

Time::Time(string time) : hour(), minute(), second() {
    std::istringstream is( time );
    is >> this->hour;
    is.ignore(1);
    is >> this->minute;
    is.ignore(1);
    is >> this->second;
    this->check_clock_bounds();
}


int Time::get_hour() const {
    return this->hour;
}

int Time::get_minute() const {
    return this->minute;
}

int Time::get_second() const {
    return this->second;
}

bool Time::is_am() const {
    return (this->hour < 12);
}


string digit_helper(int time_t) {
    return (time_t >= 10) ? std::to_string(time_t) : "0" + std::to_string(time_t);
}

string Time::to_string(bool const format) const {
    string time_s {};
    int hour_temp{this->hour};

    // Maybe this if statement should  be nested or broken up, altough I think it's clear enough.    
    if(format && !this->is_am() && hour_temp != 12) {
        hour_temp -= 12;
    } else if (format && this->is_am() && hour_temp == 0) {
        hour_temp += 12;
    }

    time_s += digit_helper(hour_temp);
    time_s += ':';
    time_s += digit_helper(this->minute);
    time_s += ':';
    time_s += digit_helper(this->second);

    if(format && this->is_am()) {
        time_s += "am";
    } else if (format && !this->is_am()) {
        time_s += "pm";
    }

    return time_s;
}

Time Time::operator+(int const& rhs) {
    Time t{*this};
    if(t.get_second() + rhs >= 60) {
        if(t.get_minute() == 59) {
            if(t.get_hour() == 23) {
                t.second += rhs - 60;
                t.minute = 0;
                t.hour = 0;
            } else {
                t.second += rhs - 60;
                t.minute = 0;
                t.hour += 1;
            }
        } else {
            t.second += rhs - 60;
            t.minute += 1;
        }
    } else {
        t.second += rhs;
    }

    return t;
}

Time Time::operator-(int const& rhs) {
    Time t{*this};
    if(t.get_second() - rhs < 0) {
        if(t.get_minute() == 0) {
            if(t.get_hour() == 0) {
                t.second += 60 - rhs;
                t.minute = 59;
                t.hour = 23;
            } else {
                t.second += 60 - rhs;
                t.minute = 59;
                t.hour -= 1;
            }
        } else {
            t.second += 60 - rhs;
            t.minute -= 1;
        }
    } else {
        t.second -= rhs;
    }

    return t;
}

//post
Time Time::operator++(int) {
    Time t{*this};
    *this = *this + 1;
    return t;
}

//pre
Time& Time::operator++() {
    *this = *this + 1;
    return *this;
}

//post
Time Time::operator--(int) {
    Time t{*this};
    *this = *this - 1;
    return t;
}

//pre
Time& Time::operator--() {
    *this = *this - 1;
    return *this;
}


