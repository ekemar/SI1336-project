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
#include<cstdlib>
#include "lattice.h"


using namespace std;


int X = 0;
int Y= 1;
int Z = 2;
const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;
const int IN = 4;
const int OUT = 5;

vector<int> set_next_point(int x, int y, int(z)){
    vector<int> new_point;
    int random = rand()%(6);
    switch(random){
        case(LEFT):
            new_point.push_back(x - 1);
            new_point.push_back(y);
            new_point.push_back(z);
            break;
        case(RIGHT):
            new_point.push_back(x + 1);
            new_point.push_back(y);
            new_point.push_back(z);
            break;
        case(DOWN):
            new_point.push_back(x);
            new_point.push_back(y + 1);
            new_point.push_back(z);
            break;
        case(UP):
            new_point.push_back(x);
            new_point.push_back(y - 1);
            new_point.push_back(z);
            break;
        case(IN):
            new_point.push_back(x);
            new_point.push_back(y);
            new_point.push_back(z-1);
            break;
        case(OUT):
            new_point.push_back(x);
            new_point.push_back(y);
            new_point.push_back(z + 1);
            break;
    }
    return new_point;
}

bool control_point_is_valid(int &columns, int &rows, int &dept, vector<int> &point, Lattice &lattice){
    if(point[X] >= columns  || point[X] < 0 || point[Y] >= rows || point[Y] < 0 || point[Z] >= dept || point[Z] < 0){
        return false;
    } else { 
        return true;
    }
}

vector<int> generate_new_point(int &columns, int &rows, int &dept, vector<int> &point, Lattice &lattice){
    vector<int> new_point;
    while (true) {
        new_point = set_next_point(point[X], point[Y], point[Z]);
        if (control_point_is_valid(columns, rows, dept, new_point, lattice)) {
            return new_point;
        }
    }
}
Lattice start_walk(int columns, int rows, int dept){
    Lattice lattice;
    lattice.create_lattice(columns, rows, dept); 
    int x = rand() % columns;
    int y = rand() % rows;
    int z = rand() % dept;
    lattice.occupy_point(x, y, z);
    vector<int> point= lattice.get_first_occupied();
    return lattice;
}


bool stop_going_back(vector<int> &old_point, vector<int> &new_point){
    if(new_point[X] == old_point[X] && new_point[Y] == old_point[Y] && new_point[Z] == old_point[Z]){
        return true;
    }
    else{return false;}
}

bool did_finish(int vector_length, int steps){
    if (vector_length == steps){
        return true;
    } 
    else{
        return false;
    }
}

void write_to_file(vector<vector<int>> occupied_points, const char* filename, const char* title){
    ofstream outfile;
    outfile.open(filename);
    outfile<<title;
    for(int i = 0; i < occupied_points.size(); i++){
                outfile<<endl;
                outfile<<occupied_points[i][X]<<","<<occupied_points[i][Y]<<", "<<occupied_points[i][Z];
            }
    outfile.close();
}

double calculate_MSD(vector<vector<int>> &positions){
    double sum = 0;
    for_each(positions.begin(), positions.end(), [&] (vector<int> n){
        for(int i = 0; i < 3; i++){
           sum += pow(n[i]-positions[0][i], 2);
    }
    });
    return sum/positions.size();
}
vector<vector<int>> perform_walk(int columns, int rows,int dept, int steps, bool self_avoding, bool cant_go_back){
    Lattice lattice = start_walk(columns, rows, dept);
    vector<int> point = lattice.get_first_occupied();
    vector<vector<int>> points;
    for(int i = 0; i < steps;){
        points.push_back(point);
        point = generate_new_point(columns, rows, dept, point, lattice);
        if(self_avoding){
            if(cant_go_back){
                if(i > 1){

                    if(stop_going_back(points[i-1], point)){
                        i--;
                        continue;
                    }
                }
                if(points.size() > 20){
                    write_to_file(points, "lattice_cant_go_back_100.csv", "X, Y, Z");
                }
            }
            if(lattice.is_point_occupied(point[X], point[Y], point[Z])){
                break;
            }
            else if(points.size() > 20){
                write_to_file(points, "lattice_self_avoiding_100.csv", "X, Y, Z");
            }
        }
        else if(points.size() > 80){
            write_to_file(points, "lattice_positions_100.csv", "X, Y, Z");
        }
        i++;
        lattice.occupy_point(point[X], point[Y], point[Z]);
    } 
    return lattice.get_occupied_points();
}

vector<float> get_statistics(int times, int columns, int rows,int dept, int steps, bool cant_go_back, bool self_avoding){
    vector<double> MSD;
    vector<float> statistics;
    vector<vector<int>> points;
    bool write_spheres = false;
    float count_finish = 0;
    for(int i = 0; i < times; i++){
        points = perform_walk(columns, rows,dept, steps, self_avoding, write_spheres);
        if(did_finish(points.size(), steps) == true){
            count_finish++;
        }
        MSD.push_back(calculate_MSD(points));
    }
    float average = (accumulate( MSD.begin(), MSD.end(), 0.0)/MSD.size());              
    statistics.push_back(average);
    statistics.push_back(count_finish);
    return statistics;
}
vector<int> create_step_vector(int start, int length, int delta){
    vector<int> step_vector;
    for(int i = start; i < length; i += delta){
        step_vector.push_back(i);
    }
    return step_vector;
}

void save_data(vector<int> steps, vector<float> MSD, const char* filename, const char *title){
    ofstream outfile;
    outfile.open(filename);
    vector<double> surface_dot;
    outfile<<title;
    for(int i = 0; i < MSD.size(); i++){
                outfile<<endl;
                outfile<<steps[i]<<","<<MSD[i];
            }
    outfile.close();
}
void walk_multible_times(int start_step, int end_step, int delta, int runs, int columns, int rows, int dept, bool self_avoiding, bool cant_go_back){
    if((end_step-start_step)%delta !=0){
        cout<<"error! vector length not an integer"<<endl;
    }
    vector<int> step_vector = create_step_vector(start_step, end_step, delta);
    vector<float> MSD;
    vector<float> statistics_Data;
    vector<float>  finished_runs;
    for(int i =0; i <step_vector.size(); i++){
        cout<<"step size is "<<step_vector[i]<<endl;
        cout<<endl;
        statistics_Data = get_statistics(runs, columns, rows, dept, step_vector[i],  cant_go_back, self_avoiding);
        MSD.push_back(statistics_Data[0]);
        finished_runs.push_back(statistics_Data[1]);
    }
    if(self_avoiding){
        if(cant_go_back){
            save_data(step_vector, MSD, "MSD_lattice_cant_go_back_50.csv", "steps, MSD");
            save_data(step_vector, finished_runs, "lattice_finishedruns_cant_go_back_50.csv", "steps, finished runs");
        }
        else{
            save_data(step_vector, MSD, "MSD_lattice_avoiding_can_go_back_50.csv", "steps, MSD");
            save_data(step_vector, finished_runs, "lattice_finishedruns_can_go_back_50.csv", "steps, finished runs");
        }
    }
    else{
            save_data(step_vector, MSD, "MSD_non_avoiding_lattice_50.csv", "steps, MSD");
        }
}
    

int main (int argc, char *argv[]) {
    srand(time(0));
    cout<<"standard walk"<<endl;
    cout<<endl;
    walk_multible_times(1, 50, 1, 10000, 50,50, 50, true, true);
    cout<<"Self avoiding runs"<<endl;
    cout<<endl;
    walk_multible_times(1, 50, 1, 10000,50,50,50, true, false);
    cout<<"Self avoiding runs can't go back"<<endl;
    cout<<endl;
    walk_multible_times(1, 100, 1, 10000,50,50,50, false, false);
}
