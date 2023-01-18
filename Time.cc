#include "Time.h"
#include <stdexcept>
#include <sstream>

using namespace std;


void Time::check_clock_bounds() {
    if (this->hour > 23 || this->hour < 0) {
        throw range_error{"An hour has to be in the range 0-24 (inclusive)"};
    } 
    if (this->minute > 59 || this->minute < 0 ) {
        throw range_error{"An minute has to be in the range 0-59 (inclusive)"};
    }

    if (this->second > 59 || this->second < 0) {
        throw range_error{"An hour has to be in the range 0-59 (inclusive)"};
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


int Time::get_hour() {
    return this->hour;
}

int Time::get_minute() {
    return this->minute;
}

int Time::get_second() {
    return this->second;
}

bool Time::is_am() {
    return (this->hour < 12);
}


string digit_helper(int time_t) {
    return (time_t >= 10) ? std::to_string(time_t) : "0" + std::to_string(time_t);
}

string Time::to_string() {
    string time_s {};
    time_s += digit_helper(this->hour);
    time_s += ':';
    time_s += digit_helper(this->minute);
    time_s += ':';
    time_s += digit_helper(this->second);

    return time_s;
}