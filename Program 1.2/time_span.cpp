#include <cmath>
#include "time_span.h"
#include <iostream>

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
    double temp = minutes*60.0 + seconds; //same as above but with min
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
    double temp = hours*3600.0 + minutes*60.0 + seconds; //same as above but with hr
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
void TimeSpan::convert(int total_s)
{
    // Recalculate Total Seconds (including out-of-range exceptions)
    hours_ = total_s / 3600; 
    int temp = total_s % 3600; //remaining seconds after hours conversion (for calculation below)
    minutes_ = temp / 60;
    seconds_ = temp % 60;

    // Reset Range For Seconds (-59 to 59)
    if (seconds_ >= 60) {
        minutes_ += seconds_ / 60;
        seconds_ %= 60; //reset seconds
    } else if (seconds_ <= -60) {
        minutes_ += seconds_ / 60;
        seconds_ %= 60;
    }

    // Reset Range For Minutes (-59 to 59)
    if (minutes_ >= 60) {
        hours_ += minutes_ / 60;
        minutes_ %= 60; //reset minutes
    } else if (minutes_ <= -60) {
        hours_ += minutes_ / 60;
        minutes_ %= 60;
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
    hours_ = hours;
    minutes_ = minutes;
    seconds_ = seconds;
    int total = hours_*3600 + minutes_*60 + seconds_;
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
    if (hours_ != timeObj.hours_) {
        return hours_ < timeObj.hours_;
    } else if (minutes_ != timeObj.minutes_) {
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
    int hours, minutes, seconds;
    stream >> hours >> minutes >> seconds; //read the values
    timeObj.set_time(hours, minutes, seconds); //set time to the object
    return stream; 
}

ostream& operator<<(ostream &stream, const TimeSpan &timeObj) {
    stream << "Hours: "<< timeObj.hours() << ", Minutes: " << timeObj.minutes() << ", Seconds: " << timeObj.seconds();
    return stream;
}


/* Turn In 
A .zip file which contains: 
• time_span.h  
• time_span.cpp 
• A file containing your Unit Tests utilized during TDD.   
o These should be comprehensive. 
o These can come in any form depending on the Unit Test Framework you 
utilize; or they can take the form of the tests below. 
o These test cases will not be executed by the grader;  we will inspect these 
manually to see if they are comprehensive. 
• vending_bank.h */



/* Overloaded less-than operator
bool TimeSpan::operator<(const TimeSpan& other) const {
    if (hours_ != other.hours_) {
        return hours_ < other.hours_;  // Compare hours
    } else if (minutes_ != other.minutes_) {
        return minutes_ < other.minutes_;  // Compare minutes
    } else {
        return seconds_ < other.seconds_;  // Compare seconds
    }
}

// Overloaded less-than-or-equal-to operator
bool TimeSpan::operator<=(const TimeSpan& other) const {
    return (*this < other) || (*this == other);  // Use < and == operators
}

// Overloaded greater-than operator
bool TimeSpan::operator>(const TimeSpan& other) const {
    return !(*this <= other);  // Opposite of <= operator
}

// Overloaded greater-than-or-equal-to operator
bool TimeSpan::operator>=(const TimeSpan& other) const {
    return !(*this < other);   // Opposite of < operator
}*/