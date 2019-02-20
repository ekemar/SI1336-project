#include <iostream>
#include <vector>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include "sphere.h"

using namespace std;

int X = 0;
int Y = 1;
int Z = 2;

void Sphere:: set_radius(double r){
    radius = r;
}
void Sphere:: set_surface_dot(vector<double> dot, int i){
    if( i < sphere_surface.size() || i == sphere_surface.size()){
    sphere_surface[i].set_values_in_group(dot);
    }
    else{
        cout<<"index out of range, max index is "<<sphere_surface.size()<<endl;
    }
}

void Sphere:: set_surface(vector<Triplet> surface){
    sphere_surface = surface;
}

void Sphere:: set_origo(vector<double> origo){
    sphere_origo.set_values_in_group(origo);
}

double Sphere:: get_radius(){
    return radius;
}

vector<double> Sphere:: get_surface_dot(int i){
    if( i < sphere_surface.size() || i == sphere_surface.size()){
        return sphere_surface[i].get_triplet();
    }
    else{
        cout<<"index out of range, max index is "<<sphere_surface.size()<<endl;
    }
}

vector<Triplet> Sphere:: get_surface(){
    return sphere_surface;
}
Triplet Sphere:: get_origo(){
    return sphere_origo;
} 

void Sphere:: make_sphere(Triplet origo, double r){
    sphere_origo.set_values_individual(origo.get_value(X), origo.get_value(Y), origo.get_value(Z));
    radius = r;
    const double PI = 3.141592653589793238462643383279502884197;
    int i = 0;
    sphere_surface.resize(200);
     for (double phi = 0.; phi < 2*PI; phi += PI/10.) // Azimuth [0, 2PI]
        {
            for (double theta = 0.; theta < PI; theta += PI/10.) // Elevation [0, PI]
            { 
                double x = r *cos(phi) * sin(theta) + sphere_origo.get_value(X);
                double y = r *sin(phi) * sin(theta) + sphere_origo.get_value(Y);
                double z = r * cos(theta) + sphere_origo.get_value(Z);
                sphere_surface[i].set_values_individual(x,y,z);
                i++;
            }
        }
}
