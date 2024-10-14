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
}