#include <iostream>
#include <vector>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>

using namespace std;

class Triplet{
    double x, y, z;
    vector<double> triplet = {x, y,z};
    public:
        void set_values_individual(double, double, double); 
        void set_values_in_group(vector<double>); 
        vector<double> get_triplet();
        double get_value(int i);
        void change_value(double, int);
        void add_values(double, double, double);
        void subtract_values(double, double, double);
        bool is_identical(Triplet);
};
