#ifndef TIME_SPAN_H_
#define TIME_SPAN_H_

#include <iostream>
#include <string>

using namespace std;

class TimeSpan {
private:
    int hours_;
    int minutes_;
    int seconds_;
    
public:
    // Constructors
    TimeSpan();
    TimeSpan(double seconds);
    TimeSpan(double minutes, double seconds);
    TimeSpan(double hours, double minutes, double seconds);

    // convert Function
    void convert(int total_s);

    // Accessor Functions
    int hours() const;
    int minutes() const;
    int seconds() const;
    void set_time(int hours, int minutes, int seconds);

    // Arithmetic Operators Overloads 
    TimeSpan operator+(const TimeSpan &timeObj) const;
    TimeSpan operator-(const TimeSpan &timeObj) const;
    TimeSpan operator-() const;
    TimeSpan &operator+=(const TimeSpan &timeObj);
    TimeSpan &operator-=(const TimeSpan &timeObj);

    // Comparison Operators Overloads
    bool operator==(const TimeSpan &timeObj) const;
    bool operator!=(const TimeSpan &timeObj) const;
    bool operator<(const TimeSpan &timeObj) const;
    bool operator<=(const TimeSpan &timeObj) const;
    bool operator>(const TimeSpan &timeObj) const;
    bool operator>=(const TimeSpan &timeObj) const;

    // Input/Output Operators Overloads (non-member function)
    friend istream& operator>>(istream &stream, TimeSpan& timeObj);
    friend ostream& operator<<(ostream &stream, const TimeSpan &timeObj);
};      

#endif