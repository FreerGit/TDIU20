#include <string>

#ifndef H_Time
#define H_Time

class Time {
public:
    Time() = default;
    Time(int hour, int minute, int second);
    Time(std::string time);

    int get_hour();
    int get_minute();
    int get_second();
    bool is_am();
    std::string to_string(); 

private:
    void check_clock_bounds();
    int hour;
    int minute;
    int second;
};

#endif