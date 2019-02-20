#include <iostream>
#include <vector>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <tuple>

using namespace std;

class Lattice{
    int columns, rows, dept; 
    vector<vector<vector<bool>>> lattice;
    public:
        void create_lattice(int, int, int); 
        void occupy_point(int, int, int);
        bool is_point_occupied(int, int, int);
        vector<vector<int>> get_occupied_points();
        int get_number_of_occupied();
        vector<int> get_first_occupied();
};
