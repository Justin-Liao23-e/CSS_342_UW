#include <iostream>
#include <sstream>
#include "time_span.h"

using namespace std;

bool CheckValues(TimeSpan time, int hours, int minutes, int seconds) {
    if ((time.hours() != hours) || (time.minutes() != minutes) || (time.seconds()
    != seconds)) {
        return false;
    }
    return true;
}

bool TestZeros() {
    TimeSpan ts(0, 0, 0);
    return CheckValues(ts, 0, 0, 0);
}

bool TestFloatSeconds() {
    TimeSpan ts(127.86);
    return CheckValues(ts, 0, 2, 8);
}

bool TestNegativeMinute() {
    TimeSpan ts(8, -23, 0);
    return CheckValues(ts, 7, 37, 0);
}

bool TestNegativeHour() {
    TimeSpan ts(-3, 73, 2);
    return CheckValues(ts, -1, -46, -58);
}

bool TestAdd() {
    TimeSpan ts1, ts2(5), ts3(7, 0), ts4(4, 0, 0);
    TimeSpan add_it_up = ts1 + ts2 + ts3 + ts4;
    return CheckValues(add_it_up, 4, 7, 5);
}

bool TestAddInPlace() {
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, 1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 1, 1, 1))) {
        return false;
    }
    ts1 += ts2;
    if ((!CheckValues(ts1, 6, 7, 8)) || (!CheckValues(ts2, 1, 1, 1))) {
        return false;
    }
    return true;
}

// Subtraction Operator
bool TestSubtract() {
    TimeSpan ts1(2, 65, 31);
    TimeSpan ts2(2, 15, 15);
    TimeSpan result = ts1 - ts2;
    return CheckValues(result, 0, 50, 16);
}

// In-place Subtraction Operator
bool TestSubtractInPlace() {
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, 1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 1, 1, 1)))
    {
        return false;
    }
    ts1 -= ts2;
    if ((!CheckValues(ts1, 4, 5, 6)) || (!CheckValues(ts2, 1, 1, 1)))
    {
        return false;
    }
    return true;
}

// == Operator
bool TestEquality() {
    TimeSpan ts1(2, 3, 65);
    TimeSpan ts2(2, 3, 65);
    TimeSpan ts3(1, 15, 25);
    return (ts1 == ts2) && !(ts1 == ts3);
}

// != Operator
bool TestInequality() {
    TimeSpan ts1(2, 3, 65);
    TimeSpan ts2(2, 3, 65);
    TimeSpan ts3(1, 15, 25);
    return !(ts1 != ts2) && (ts1 != ts3);
}

// < Operator
bool TestLessThan() {
    TimeSpan ts1(2, 15, 10);
    TimeSpan ts2(2, 15, 35);
    return (ts1 < ts2);
}

// <= Operator
bool TestLessThanOrEqual() {
    TimeSpan ts1(2, 15, 10);
    TimeSpan ts2(2, 15, 35);
    TimeSpan ts3(2, 15, 35);
    return (ts1 <= ts2) && (ts2 <= ts3);
}

// > Operator
bool TestGreaterThan() {
    TimeSpan ts1(2, 15, 35);
    TimeSpan ts2(2, 15, 10);
    return (ts1 > ts2);
}

// >= Operator
bool TestGreaterThanOrEqual() {
    TimeSpan ts1(2, 15, 35);
    TimeSpan ts2(2, 15, 10);
    TimeSpan ts3(2, 15, 10);
    return (ts1 >= ts2) && (ts2 >= ts3);
}

// Input Operator
bool InputStream() {
    istringstream temp("2 15 35"); //create an input string stream with the values "2 15 35"
    TimeSpan ts;
    temp >> ts; //extract the values into the TimeSpan object
    return CheckValues(ts, 2, 15, 35); 
}

// Output Operator
bool OutputStream() {
    TimeSpan ts(2, 15, 35);
    ostringstream temp; //create an output string stream
    temp << ts; //insert the TimeSpan object into the stream
    string eTemp = "Hours: 2, Minutes: 15, Seconds: 35";
    return (temp.str() == eTemp);
}

int main() {
    cout << "Testing TimeSpan Class" << endl;
    if (!TestZeros()) cout << "Failed: TestZeros" << endl;
    if (!TestFloatSeconds()) cout << "Failed: TestFloatSeconds" << endl;
    if (!TestNegativeMinute()) cout << "Failed: TestNegativeMinute" << endl;
    if (!TestNegativeHour()) cout << "Failed: TestNegativeHour" << endl;
    if (!TestAdd()) cout << "Failed: TestAdd" << endl;
    if (!TestAddInPlace) cout << "Failed: TestAddInPlace" << endl;
    // New Tests (below)
    if (!TestSubtract()) cout << "Failed: TestSubtract" << endl;
    if (!TestSubtractInPlace) cout << "Failed: TestSubtractInPlace" << endl;
    if (!TestEquality()) cout << "Failed: TestEquality" << endl;
    if (!TestInequality()) cout << "Failed: TestInequality" << endl;
    if (!TestLessThan()) cout << "Failed: TestLessThan" << endl;
    if (!TestLessThanOrEqual()) cout << "Failed: TestLessThanOrEqual" << endl;
    if (!TestGreaterThan()) cout << "Failed: TestGreaterThan" << endl;
    if (!TestGreaterThanOrEqual()) cout << "Failed: TestGreaterThanOrEqual" << endl;
    if (!InputStream()) cout << "Failed: InputStream" << endl;
    if (!OutputStream()) cout << "Failed: OutputStream" << endl;
    cout << "Testing Complete" << endl;

    return 0;
}