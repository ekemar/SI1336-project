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
#include <thread>         
#include "sphere.h"


using namespace std;

int X1 = 0;
int Y1= 1;
int Z1 = 2;
const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;
const int IN = 4;
const int OUT = 5;

Triplet set_next_origo(Triplet sphere_center, double radius){
    int random = rand()%(6);
    switch(random){
    
    case LEFT: 
        sphere_center.change_value(sphere_center.get_value(X1) - 2*radius, X1);
            break;
    case RIGHT: 
        sphere_center.change_value(sphere_center.get_value(X1) + 2*radius, X1);
            break;
    case IN: 
        sphere_center.change_value(sphere_center.get_value(Y1) - 2*radius, Y1);
            break;
    case OUT: 
        sphere_center.change_value(sphere_center.get_value(Y1) + 2*radius, Y1);
            break;
    case DOWN: 
        sphere_center.change_value(sphere_center.get_value(Z1) - 2*radius, Z1);
            break;
    case UP: 
        sphere_center.change_value(sphere_center.get_value(Z1) + 2*radius, Z1);
            break;
    
    }
    
    return sphere_center;
}

bool check_space_is_free(vector<Triplet> &origos, Triplet &potential_origo, float radius1, float radius2){
    double distanse;
    double sum;
    double intersection_radi;
    int collison_counter = 0;
    int free_space_counter = origos.size();
    for(int j = 0; j < origos.size(); j++){
        sum = 0;
        for(int i = 0; i < 3; i++){
           sum += pow((origos[j].get_value(i)-potential_origo.get_value(i)), 2);
    }
        distanse = sqrt(sum);
        if(distanse < radius1+radius2){
            return false;
        }
    }
    return true;
}

Sphere create_new_sphere(Triplet origo, double radius){
    Sphere sphere;
    sphere.make_sphere(origo, radius);
    return sphere;
}

bool stop_going_back(Triplet &old_origo, Triplet &new_origo){
    if(old_origo.is_identical(new_origo)){
        return false;
    }
    else{return true;}
}
void write_spheres_to_file(vector<Sphere> spheres, const char* filename){
    ofstream outfile;
    outfile.open(filename);
    vector<double> surface_dot;
    for(int i = 0; i < spheres.size(); i++){
        outfile<<"XYZ";
        for(int j = 0; j < spheres[i].get_surface().size(); j++){
                outfile<<endl;
                 surface_dot = spheres[i].get_surface_dot(j);
                    for(int k = 0; k<3;k++){
                        switch(k){
                        case(2):
                            outfile<< surface_dot[k];
                            break;
                        default:
                            outfile<< surface_dot[k]<<",";
                            
                    }
                }
            }
    }
    outfile.close();
}

bool did_finish(int vector_length, int steps){
    if (vector_length == steps){
        return true;
    } 
    else{
        return false;
    }
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

vector<Sphere> perform_random_walk(double radius, int steps, bool cant_go_back, bool self_avoiding, bool write_spheres){

    vector<Sphere> approved_spheres;
    vector<Triplet> origos;
    Triplet sphere_center;
    sphere_center.set_values_individual(0.0, 0.0, 0.0);
    Sphere sphere;
    sphere.make_sphere(sphere_center,radius);
    approved_spheres.push_back(sphere);
    Triplet origo = sphere.get_origo();
    origos.push_back(origo);
    for(int j = 0; j <steps; j++){
        origo = set_next_origo(origo, radius);
        if(self_avoiding){
            if(cant_go_back){
                if(j > 1){
                    if(stop_going_back(origos[j-1], origo)==false){
                        origo = origos[j];
                        j--;
                        continue;
                    }
                }
            }
            if(check_space_is_free(origos, origo, radius, radius) == false){ 
                break;
            }
        }
        
        sphere=create_new_sphere(origo, radius);
        approved_spheres.push_back(sphere);
        origos.push_back(origo);
    }
        
    if(self_avoiding){
        if(20 < approved_spheres.size()){
             if(cant_go_back){
                write_spheres_to_file(approved_spheres, "spheres_avoiding_cant_go_back9.csv");
                }
                else{
                    write_spheres_to_file(approved_spheres, "spheres_avoiding_can_go_back9.csv");
                }
        }
    }
    else if(write_spheres){
        write_spheres_to_file(approved_spheres, "spheres_nonavoiding9.csv");
    }
    return approved_spheres;
}
double calculate_MSD(vector<Triplet> &origos){
    double sum = 0;
    double dist;
    for_each(origos.begin(), origos.end(), [&] (Triplet n){
         dist = 0; 
        for(int i = 0; i < 3; i++){
           sum += pow(n.get_value(i)-origos[0].get_value(i), 2);
    }
    });
    return sum/origos.size();
}
vector<Triplet> get_origos(vector<Sphere> &spheres){
    vector<Triplet> origos;
    for(int i = 0; i < spheres.size(); i++){
        origos.push_back(spheres[i].get_origo());
    }
    return origos;
}
vector<float> get_statistics(int times, int steps, float radius, bool cant_go_back, bool self_avoding){
    vector<double> MSD;
    vector<Sphere> test;
    vector<Triplet> origos;
    vector<float> statistics;
    bool write_spheres = false;
    float count_finish = 0;
    for(int i = 0; i < times; i++){
        test = perform_random_walk(radius, steps, cant_go_back, self_avoding, write_spheres);
        if(did_finish(test.size(), steps) == true){
            count_finish++;
        }
        origos = get_origos(test);
        MSD.push_back(calculate_MSD(origos));
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


void perform_multiple_walks(int start_step, int end_step, int delta, int times, bool cant_go_back, bool self_avoiding){ 
    float radius = 1;
    if((end_step-start_step)%delta !=0){
        cout<<"error! vector length not an integer"<<endl;
    }
    vector<int> step_vector = create_step_vector(start_step, end_step, delta);
    vector<float> MSD;
    vector<float> statistics_Data;
    vector<float>  finished_runs;
    for(int i =0; i <step_vector.size(); i++){
       // srand(time(0));
        statistics_Data = get_statistics(times, step_vector[i], radius, cant_go_back, self_avoiding);
        MSD.push_back(statistics_Data[0]);
        finished_runs.push_back(statistics_Data[1]);
    }
    if(self_avoiding){
        if(cant_go_back){
            save_data(step_vector, MSD, "MSDtestavoiding_cant_go_back9_50.csv", "steps, MSD");
            save_data(step_vector, finished_runs, "finishedruns_cant_go_back9_test3.csv", "steps, finished runs");
        }
        else{
            save_data(step_vector, MSD, "MSDtestavoiding_can_go_back9_50.csv", "steps, MSD");
            save_data(step_vector, finished_runs, "finishedruns_can_go_back9_test3.csv", "steps, finished runs");
        }
    }
    else{
            save_data(step_vector, MSD, "MSD_non_avoiding9_3.csv", "steps, MSD");
           // save_data(step_vector, finished_runs, "finishedruns_cant_go_back.csv", "steps, finished runs");
        }
}




    
int main (int argc, char *argv[]) {
    srand(time(0));
   perform_multiple_walks(1, 50, 1, 10000, true, true);
   srand(time(0));
   perform_multiple_walks(1, 50, 1, 10000, false, true);
   srand(time(0));
   perform_multiple_walks(1, 100, 1, 10000, false, false);
   //vector<Sphere> test =  perform_random_walk(0.5, 1000, true, true, false);
    //test =  perform_random_walk(0.5, 1000, true, true, false);
}
