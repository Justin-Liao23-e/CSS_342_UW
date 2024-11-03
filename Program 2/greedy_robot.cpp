#include <iostream>
#include <cmath>
#include "greedy_robot.h"

using namespace std;

// Main Constructor
GreedyRobot::GreedyRobot(int max_distance, int xi, int yi, int xf, int yf) { 
    max_distance_ = max_distance;
    xi_ = xi;
    yi_ = yi;
    xf_ = xf;
    yf_ = yf;
    shortest_distance_ = abs(xi_ - xf_) + abs(yi_ - yf_); //calculate shortest distance with the specified formula
    findPaths(xi_, yi_, "", ' ', 0); //call to find all unique shortest paths
}

// Outstream Operator Overload
ostream& operator<<(ostream& stream, const GreedyRobot& robot) {
    for (int i = 0; i < robot.paths_.size(); i++) { //iterate through the paths vector
        stream << robot.paths_[i] << endl;
    }
    stream << "Number of paths: " << robot.paths_.size() << endl;
    return stream;
}

void GreedyRobot::findPaths(int x, int y, string path, char pre_direction, int pre_count) {
    // Base Case: same position as the treasure
    if (x == xf_ && y == yf_) {
        paths_.push_back(path); //add the unique path to the vector
        return; //exit the function
    }

    int steps_remaining = shortest_distance_ - path.length(); //remaining steps to the treasure
    int current_distance = abs(x - xf_) + abs(y - yf_); //current shortest distance to the treasure

    if (current_distance > steps_remaining) { //when the treasure is unreachable
        return;
    }

    // Moving North
    if (pre_direction != 'N' || pre_count < max_distance_) {
        int new_y = y + 1; //move up one
        int new_distance = abs(x - xf_) + abs(new_y - yf_); //calculate new shortest distance
        if (new_distance <= current_distance) { 
            findPaths(x, new_y, path + 'N', 'N', (pre_direction == 'N') ? pre_count + 1 : 1);
        }
    }

    // Moving South
    if (pre_direction != 'S' || pre_count < max_distance_) {
        int new_y = y - 1;
        int new_distance = abs(x - xf_) + abs(new_y - yf_);
        if (new_distance <= current_distance) {
            findPaths(x, new_y, path + 'S', 'S', (pre_direction == 'S') ? pre_count + 1 : 1);
        }
    }

    // Moving East
    if (pre_direction != 'E' || pre_count < max_distance_) {
        int new_x = x + 1;
        int new_distance = abs(new_x - xf_) + abs(y - yf_);
        if (new_distance <= current_distance) {
            findPaths(new_x, y, path + 'E', 'E', (pre_direction == 'E') ? pre_count + 1 : 1);
        }
    }

    // Moving West
    if (pre_direction != 'W' || pre_count < max_distance_) {
        int new_x = x - 1;
        int new_distance = abs(new_x - xf_) + abs(y - yf_);
        if (new_distance <= current_distance) {
            findPaths(new_x, y, path + 'W', 'W', (pre_direction == 'W') ? pre_count + 1 : 1);
        }
    }
}