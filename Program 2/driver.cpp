#include <iostream>
#include "greedy_robot.h"
#include <cstdlib> //atoi function

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 6) { //ensures only five arguments
        cout << "Please enter five integers!" << endl;
        return 1;
    }

    // Convert Char to Int
    int max_distance = atoi(argv[1]);
    int xi = atoi(argv[2]);
    int yi = atoi(argv[3]);
    int xf = atoi(argv[4]);
    int yf = atoi(argv[5]);

    GreedyRobot robot(max_distance, xi, yi, xf, yf);
    cout << robot << endl; //result

    return 0;
}