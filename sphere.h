#include <iostream>
#include <vector>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include "triplet.h"

using namespace std;


class Sphere{
    Triplet sphere_origo;
    double radius;
    vector<Triplet> sphere_surface; 
    public:
    void set_radius(double);
    void set_surface_dot(vector<double>, int);
    void set_surface(vector<Triplet>);
    void set_origo(vector<double>);
    double get_radius();
    vector<double> get_surface_dot(int);
    vector<Triplet> get_surface();
    Triplet get_origo();
    void make_sphere(Triplet, double);
};
