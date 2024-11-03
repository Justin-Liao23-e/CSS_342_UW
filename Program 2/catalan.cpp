#include <iostream>
#include <cstdlib> //atoi function

using namespace std;

// Recursive Function: Mr. Catalan
int catalan(int n) {
    int sum = 0;
    if (n <= 1) { //base case
        return 1;
    } else {
        for (int i = 0; i < n; i++) {
            sum += catalan(i) * catalan(n - i - 1); //-1 since formula starts with Cn+1
        }
        return sum;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) { //ensures only one argument is passed
        cout << "Usage: " << argv[0] << " <number>" << endl;
        return 1;
    }

    int n = atoi(argv[1]); //converts string to integer

    if (n < 0) { //ensures number is positive
        cout << "Please enter a positive number!" << endl;
        return 1;
    }
    if (n > 10) { //ensures number is not too large
        cout << "Number is too large to solve!" << endl;
        return 1;
    }

    cout << catalan(n) << endl;
    return 0;
}