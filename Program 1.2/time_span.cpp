#include <iostream>
#include "time_span.h"

using namespace std;

TimeSpan::TimeSpan() { //default constructor
    hours_ = 0;
    minutes_ = 0;
    seconds_ = 0;
}

TimeSpan::TimeSpan(double seconds) { 
    double temp = seconds; //temp variable to store the seconds in double
    // Rounding to Second
    if (temp >= 0.0) { //positive values
        temp += 0.5;  
    } else { //negative values
        temp -= 0.5;
    }
    int total = temp; //convert to integer
    convert(total);
}

TimeSpan::TimeSpan(double minutes, double seconds) {
    double temp = minutes*60.00 + seconds; //same as above but with min
    // Same As Above
    if (temp >= 0.0) {
        temp += 0.5;  
    } else {
        temp -= 0.5;  
    }
    int total = temp;
    convert(total);
}

TimeSpan::TimeSpan(double hours, double minutes, double seconds) {
    double temp = hours*3600.00 + minutes*60.00 + seconds; //same as above but with hr
    // Same As Above
    if (temp >= 0.0) {
        temp += 0.5;  
    } else {
        temp -= 0.5;  
    }
    int total = temp;
    convert(total);
}

// convert Function: Convert each unit to the right range
void TimeSpan::convert(int total_s) {
    // Recalculate Total Seconds (including out-of-range exceptions)
    hours_ = total_s / 3600; 
    int temp = total_s % 3600; //remaining seconds after hours conversion (for calculation below)
    minutes_ = temp / 60;
    seconds_ = temp % 60;

    // Reset Range For Seconds (-59 to 59)
    if (seconds_ >= 60 || seconds_ <= -60) {
        minutes_ += seconds_ / 60;
        seconds_ %= 60; //reset seconds
    }
    // Reset Range For Minutes (-59 to 59)
    if (minutes_ >= 60 || minutes_ <= -60) {
        hours_ += minutes_ / 60;
        minutes_ %= 60; //reset minutes
    } 
}

// Accessor Functions
int TimeSpan::hours() const {
    return hours_;
}

int TimeSpan::minutes() const {
    return minutes_;
}

int TimeSpan::seconds()const {
    return seconds_;
}

void TimeSpan::set_time(int hours, int minutes, int seconds) {
    int total = hours*3600 + minutes*60 + seconds;
    convert(total); //reset the time
}

// Arithmetic Operators Overloads
TimeSpan TimeSpan::operator+(const TimeSpan &timeObj) const {
    int total = (hours_ + timeObj.hours_)*3600 + (minutes_ + timeObj.minutes_)*60 + (seconds_ + timeObj.seconds_);
    return TimeSpan(total); //no need to convert due to created constructor
}

TimeSpan TimeSpan::operator-(const TimeSpan &timeObj) const {
    int total = (hours_ - timeObj.hours_)*3600 + (minutes_ - timeObj.minutes_)*60 + (seconds_ - timeObj.seconds_);
    return TimeSpan(total); //no need to convert due to created constructor
}

TimeSpan TimeSpan::operator-() const {
    return TimeSpan(-hours_, -minutes_, -seconds_); //negate the time
}

TimeSpan &TimeSpan::operator+=(const TimeSpan &timeObj) {
    // Directly Modify Current Object
    hours_ += timeObj.hours_;
    minutes_ += timeObj.minutes_;
    seconds_ += timeObj.seconds_;
    int temp = hours_*3600 + minutes_*60 + seconds_; //no need to round since both objects are already rounded when created
    convert(temp); //reset the time
    return *this; //return current object
}

TimeSpan& TimeSpan::operator-=(const TimeSpan &timeObj) {
    // Directly Modify Current Object
    hours_ -= timeObj.hours_;
    minutes_ -= timeObj.minutes_;
    seconds_ -= timeObj.seconds_;
    int temp = hours_*3600 + minutes_*60 + seconds_; //no need to round since both objects are already rounded when created
    convert(temp); //reset the time
    return *this; //return current object
}

// Comparison Operators Overloads
bool TimeSpan::operator==(const TimeSpan &timeObj) const {
    return (hours_ == timeObj.hours_ && minutes_ == timeObj.minutes_ && seconds_ == timeObj.seconds_);
}

bool TimeSpan::operator!=(const TimeSpan &timeObj) const { //similar to above
    return !(hours_ == timeObj.hours_ && minutes_ == timeObj.minutes_ && seconds_ == timeObj.seconds_);
}

bool TimeSpan::operator<(const TimeSpan &timeObj) const {
    if (hours_ != timeObj.hours_) { //compare if equal, if not then return bool to check
        return hours_ < timeObj.hours_;
    } else if (minutes_ != timeObj.minutes_) { //same as above, if equal then move to third one to check
        return minutes_ < timeObj.minutes_;
    } else {
        return seconds_ < timeObj.seconds_;
    }
}

bool TimeSpan::operator<=(const TimeSpan &timeObj) const {
    if (hours_ != timeObj.hours_) {
        return hours_ < timeObj.hours_;
    } else if (minutes_ != timeObj.minutes_) {
        return minutes_ < timeObj.minutes_;
    } else {
        return seconds_ <= timeObj.seconds_;
    }
}

bool TimeSpan::operator>(const TimeSpan &timeObj) const {
    if (hours_ != timeObj.hours_) {
        return hours_ > timeObj.hours_;
    } else if (minutes_ != timeObj.minutes_) {
        return minutes_ > timeObj.minutes_;
    } else {
        return seconds_ > timeObj.seconds_;
    }
}

bool TimeSpan::operator>=(const TimeSpan &timeObj) const {
    if (hours_ != timeObj.hours_) {
        return hours_ > timeObj.hours_;
    } else if (minutes_ != timeObj.minutes_) {
        return minutes_ > timeObj.minutes_;
    } else {
        return seconds_ >= timeObj.seconds_;
    }
}

istream& operator>>(istream &stream, TimeSpan& timeObj) {
    stream >> timeObj.hours_ >> timeObj.minutes_ >> timeObj.seconds_; //read the values
    int total = timeObj.hours_*3600 + timeObj.minutes_*60 + timeObj.seconds_;
    timeObj.convert(total); //range conversion
    return stream; 
}

ostream& operator<<(ostream &stream, const TimeSpan &timeObj) {
    stream << "Hours: "<< timeObj.hours() << ", Minutes: " << timeObj.minutes() << ", Seconds: " << timeObj.seconds();
    return stream;
}