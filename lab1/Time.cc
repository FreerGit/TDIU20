#include "Time.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace std;


void Time::check_clock_bounds(Time const* t) const {
    if (t->get_hour() > 23 || t->get_hour() < 0) {
        throw logic_error{"An hour has to be in the range 0-24 (inclusive)"};
    } 
    if (t->get_minute() > 59 || t->get_minute() < 0 ) {
        throw logic_error{"An minute has to be in the range 0-59 (inclusive)"};
    }

    if (t->get_second() > 59 || t->get_second() < 0) {
        throw logic_error{"An hour has to be in the range 0-59 (inclusive)"};
    }
}

Time::Time(int hour, int minute, int second) : hour{hour}, minute{minute}, second{second} {
    check_clock_bounds(this);
}

Time::Time(string time) : hour(), minute(), second() {
    std::istringstream is( time );
    char anything_left;
    
    if(time.size() != 8) {
        throw logic_error{"Faulty input string, \"hh:mm:ss\""};
    }

    if (!(is >> this->hour)) {
        throw logic_error{"Faulty input string, no hour"};
    }

    is.ignore(1);
    
    if (!(is >> this->minute)) {
        throw logic_error{"Faulty input string, no minute"};
    } 
    
    is.ignore(1);

    if (!(is >> this->second)) {
        throw logic_error{"Faulty input string, no second"};
    } 

    if (is >> anything_left) {
        throw logic_error{"Faulty input string, \"hh:mm:ss\""};
    }

    check_clock_bounds(this);
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
    return (this->get_hour() < 12);
}


string digit_helper(int time_t) {
    return (time_t >= 10) ? std::to_string(time_t) : "0" + std::to_string(time_t);
}

string Time::to_string(bool const format) const {
    string time_s {};
    int hour_temp{this->get_hour()};

    // Maybe this if statement should  be nested or broken up, altough I think it's clear enough.    
    if(format && !this->is_am() && hour_temp != 12) {
        hour_temp -= 12;
    } else if (format && this->is_am() && hour_temp == 0) {
        hour_temp += 12;
    }

    time_s += digit_helper(hour_temp);
    time_s += ':';
    time_s += digit_helper(this->get_minute());
    time_s += ':';
    time_s += digit_helper(this->get_second());

    if(format && this->is_am()) {
        time_s += "am";
    } else if (format && !this->is_am()) {
        time_s += "pm";
    }

    return time_s;
}

Time Time::operator+(int const& rhs) const {
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

Time Time::operator-(int const& rhs) const {
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

//note I did not write out this explicitly, too long.
bool Time::operator<(Time const& rhs) const {
    return (get_hour() < rhs.get_hour())

        || (get_hour() == rhs.get_hour() 
            && get_minute() < rhs.get_minute()) 
    
        || (get_hour()  == rhs.get_hour() 
            && get_minute() == rhs.get_minute() 
                && get_second() < rhs.get_second());

}

bool Time::operator==(Time const& rhs) const {
    return (get_hour() == rhs.get_hour() 
        && get_minute() == rhs.get_minute() 
            && get_second() == rhs.get_second());
}

bool Time::operator>(Time const& rhs) const {
    return (rhs < *this);
}

bool Time::operator!=(Time const& rhs) const {
    return !(*this == rhs);
}

bool Time::operator<=(Time const& rhs) const {
    return (*this < rhs) || (*this == rhs);
}

bool Time::operator>=(Time const& rhs) const {
    return (*this > rhs) || (*this == rhs);
}

Time operator+(int const& lhs, Time const& rhs) {
    return rhs + lhs;
}

std::ostream& operator<<(std::ostream &os, Time const &t) {
    return os << t.to_string();
}

std::istream& operator>>(std::istream& is, Time& t) {
    char c;
    int hour, minute, second;

    is >> hour >> c >> minute >> c >> second;

    try{
        t = Time{hour,minute,second};
    } catch(std::exception& err) {
        is.setstate(ios_base::failbit);
    }
    return is;
}