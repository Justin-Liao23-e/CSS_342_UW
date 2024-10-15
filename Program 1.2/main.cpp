#include <iostream>
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

int main() {
    cout << "Testing TimeSpan Class" << endl;
    if (!TestZeros()) cout << "Failed: TestZeros" << endl;
    if (!TestFloatSeconds()) cout << "Failed: TestFloatSeconds" << endl;
    if (!TestNegativeMinute()) cout << "Failed: TestNegativeMinute" << endl;
    if (!TestNegativeHour()) cout << "Failed: TestNegativeHour" << endl;
    if (!TestAdd()) cout << "Failed: TestAdd" << endl;
    if (!TestAddInPlace) cout << "Failed: TestAddInPlace" << endl;
    cout << "Testing Complete" << endl;

    // Test constructors
    TimeSpan ts1;
    TimeSpan ts2(1, 30, 45);
    TimeSpan ts3(90.75);
    TimeSpan ts4(1, 30.5);
    TimeSpan ts5(1, 30, 45.5);

    // Test functions
    cout << "Hours: " << ts2.hours() << endl;
    cout << "Minutes: " << ts2.minutes() << endl;
    cout << "Seconds: " << ts2.seconds() << endl;

    ts2.set_time(9, 90, 90);
    cout << "Set Time - Hours: " << ts2.hours() << ", Minutes: " << ts2.minutes() << ", Seconds: " << ts2.seconds() << endl;

    // Test operator overloads
    TimeSpan ts6 = ts2 + ts3;
    cout << "Addition: " << ts6 << endl;

    TimeSpan ts7 = ts2 - ts3;
    cout << "Subtraction: " << ts7 << endl;

    TimeSpan ts8 = -ts2;
    cout << "Negation: " << ts8 << endl;

    ts2 += ts3;
    cout << "Addition Assignment: " << ts2 << endl;

    ts2 -= ts3;
    cout << "Subtraction Assignment: " << ts2 << endl;

    if (ts2 == ts3) {
        cout << "Equality: ts2 is equal to ts3" << endl;
    } else {
        cout << "Equality: ts2 is not equal to ts3" << endl;
    }

    if (ts2 != ts3) {
        cout << "Inequality: ts2 is not equal to ts3" << endl;
    } else {
        cout << "Inequality: ts2 is equal to ts3" << endl;
    }

    if (ts2 < ts3) {
        cout << "Less than: ts2 is less than ts3" << endl;
    } else {
        cout << "Less than: ts2 is not less than ts3" << endl;
    }

    if (ts2 <= ts3) {
        cout << "Less than or equal: ts2 is less than or equal to ts3" << endl;
    } else {
        cout << "Less than or equal: ts2 is not less than or equal to ts3" << endl;
    }

    if (ts2 > ts3) {
        cout << "Greater than: ts2 is greater than ts3" << endl;
    } else {
        cout << "Greater than: ts2 is not greater than ts3" << endl;
    }

    if (ts2 >= ts3) {
        cout << "Greater than or equal: ts2 is greater than or equal to ts3" << endl;
    } else {
        cout << "Greater than or equal: ts2 is not greater than or equal to ts3" << endl;
    }

    // Test input/output operators
    TimeSpan ts9;
    cout << "Enter time (hours minutes seconds): ";
    cin >> ts9;
    cout << "You entered: " << ts9 << endl;

    return 0;
}