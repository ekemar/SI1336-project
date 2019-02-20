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
#include "lattice.h"

using namespace std;

void Lattice:: create_lattice(int col, int row, int deep){
    columns = col; 
    rows = row;
    dept = deep;
    lattice.resize(columns);
    for(int i = 0; i< columns; i++){
        lattice[i].resize(rows);
        for(int j = 0; j < rows; j++){
            lattice[i][j].resize(dept);
        }
    }
}

void Lattice:: occupy_point(int x, int y, int z){
    lattice[x][y][z] = true;
} 

bool Lattice:: is_point_occupied(int y, int x, int z){
    return lattice[x][y][z];
}



vector<vector<int>> Lattice:: get_occupied_points(){
   vector<vector<int>> occupied_points;
   for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++){
            for(int k = 0; k < dept; k++){ 
                if(lattice[i][j][k] == true){
                    vector<int> temp;
                    temp.push_back(i);
                    temp.push_back(j);
                    temp.push_back(k);
                    occupied_points.push_back(temp);
                }
            }
        }
    }
    return occupied_points;
}

int Lattice:: get_number_of_occupied(){
    int point_counter = 0;
    for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++){
            for(int k = 0; k < dept; k++){
                if(lattice[i][j][k] == true){
                    point_counter++;
                }
            }
        }
    } 
    return point_counter;
}

vector<int> Lattice:: get_first_occupied(){
    if(get_number_of_occupied() == 1){
        for(int i = 0; i < columns; i++){
            for(int j = 0; j < rows; j++){
                for(int k = 0; k < dept; k++){
                    if(lattice[i][j][k] == true){
                        return vector<int> {i,j, k};
                    }
                }
            }
        } 
    }
    else if(get_number_of_occupied() == 0){
        cout<<"no points exists"<<endl;
        }
    else{
        cout<<"more than one point found"<<endl;
    }
}
