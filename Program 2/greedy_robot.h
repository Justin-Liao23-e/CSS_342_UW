#ifndef GREEDY_ROBOT_H
#define GREEDY_ROBOT_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class GreedyRobot {
public:
    GreedyRobot(int max_distance, int xi, int yi, int xf, int yf); //constructor
    friend ostream& operator<<(ostream& stream, const GreedyRobot& robot);
private:
    int max_distance_, xi_, yi_, xf_, yf_, shortest_distance_; //private members
    vector<string> paths_; //vectors to store all possible unique paths
    void findPaths(int x, int y, string path, char pre_direction, int pre_count); //recursive function to find all unique shortest paths
};

#endif