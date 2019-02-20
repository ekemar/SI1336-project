#include <iostream>
#include <vector>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include "triplet.h"

using namespace std;
vector<double> Triplet:: get_triplet(){
    return triplet;
 }

double Triplet:: get_value(int i){
        if( i ==0 ||  0 < i && i < 3){
            return triplet[i];
        }
        else {
            cout<<"index out of range, triplet takes index between 0 and 2"<<endl;}
    
}

void Triplet:: change_value(double value, int i){
    if( i ==0 ||  0 < i && i < 3){
        triplet.at(i) = value; 
    }
    else {
        cout<<"index out of range, triplet takes index between 0 and 2"<<endl;}
}
void Triplet:: add_values(double x, double y, double z){
    triplet.at(0) +=x;
    triplet.at(1) +=y;
    triplet.at(2) +=z;
}
void Triplet:: subtract_values(double x, double y, double z){
    triplet.at(0) -=x;
    triplet.at(1) -=y;
    triplet.at(2) -=z;
}

void Triplet:: set_values_individual(double x, double y, double z){
    triplet = {x, y,z};
} 
void Triplet:: set_values_in_group(vector<double> values){
    if(values.size() == 3){
        triplet = values;
    }
    else{ 
        cout<<"triplets requiers a vector with 3 elements"<<endl;
    }
} 

bool Triplet:: is_identical(Triplet compare){
    if(triplet.at(0) == compare.get_value(0) && triplet.at(1) == compare.get_value(1) &&triplet.at(2) == compare.get_value(2)){
        return true;
    }
    else{ return false;}
}
