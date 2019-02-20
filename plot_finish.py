from typing import List
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from scipy.optimize import curve_fit
import math

X = 0
Y = 1
Z = 2
def read_csv_file_with_2_columns(filename, textstring):
    with open(filename) as f:
        data = f.read()
        file_data: List[str] = data.split(textstring)
        coordinates = []
        for vectors in file_data:
            vector_x = []
            vector_y = []
            for line in vectors.split("\n"): 
                line = line.strip()
                if not line:
                    continue
                x, y = line.split(",")
                vector_x.append(float(x))
                vector_y.append(float(y))
            coordinates.append(vector_x)
            coordinates.append(vector_y)
    return coordinates
        
def read_csv_with3_columns(filename, textstring):
    with open(filename) as f:
        data = f.read()
        spheres_data: List[str] = data.split(textstring)
        spheres_coordinates = []
        for sphere_data in spheres_data:
            sphere_x_coordinates = []
            sphere_y_coordinates = []
            sphere_z_coordinates = []
            for line in sphere_data.split("\n"):
                line = line.strip()
                if not line:
                    continue
                x, y, z = line.split(",")
                sphere_x_coordinates.append(float(x))
                sphere_y_coordinates.append(float(y))
                sphere_z_coordinates.append(float(z))
            spheres_coordinates.append(sphere_x_coordinates)
            spheres_coordinates.append(sphere_y_coordinates)
            spheres_coordinates.append(sphere_z_coordinates)
    return spheres_coordinates
            
def plot_3d(coordinates):
    for i in range(0,len(coordinates), 3):
        ax.plot(coordinates[i+X], coordinates[i+Y], coordinates[i+Z],"b")

def plot_2d(coordinates, graph_name, scaling):
    for i in range(2, len(coordinates), 2):
        plt.plot(np.array(coordinates[i+X]), np.array(coordinates[i+Y])/scaling, label=graph_name)

def calculate_probability(event_list, total_cases):
    event_array = np.array(event_list)
    return event_array/total_cases


def calculate_MD(steps, v, step_length):
    MD = np.power(steps, v)* step_length
    return MD

def MD_normalised(MSD, step_length):
    return np.sqrt(MSD)/step_length

def plot_grid(start_value, end_value, x, y, z):
    scat = ax.plot(x, y, z, "-o")

#Plotting how many finished runs 
coordinates_grid = read_csv_file_with_2_columns("lattice_finishedruns_can_go_back_50.csv", "steps, finished runs")
plot_2d(coordinates_grid, "grid", 10000)
coordinates_chain = read_csv_file_with_2_columns("finishedruns_can_go_back9.csv", "steps, finished runs")
plot_2d(coordinates_chain, "freely jointed chain", 10000)
plt.legend()
plt.title("Finished runs, going back allowed")
plt.xlabel("End steps")
plt.ylabel("Probability run finish")
plt.show()
coordinates_grid = read_csv_file_with_2_columns("lattice_finishedruns_cant_go_back_50.csv", "steps, finished runs")
plot_2d(coordinates_grid, "grid", 10000)
coordinates_chain = read_csv_file_with_2_columns("finishedruns_cant_go_back9_test.csv", "steps, finished runs")
plot_2d(coordinates_chain, "freely jointed chain", 10000)
plt.legend()
plt.title("Finished runs, going back forbidden")
plt.xlabel("End steps")
plt.ylabel("Probability run finish")
plt.show()
values = read_csv_file_with_2_columns("MSD_non_avoiding9.csv","steps, MSD" )
steps = values[2]
MSD = values[3]
MD = calculate_MD(steps,0.5, 2)
lattice_values = read_csv_file_with_2_columns("MSD_non_avoiding_lattice_50.csv", "steps, MSD")
steps_lattice = lattice_values[2]
MSD_lattice = lattice_values[3]
MD_lattice = calculate_MD(steps_lattice,0.5, 1)

plt.plot(steps, MD_normalised(MSD, 2), label="freely jointed chain")
plt.plot(steps_lattice, MD_normalised(np.array(MSD_lattice), 1), label="Walk on grid")
plt.plot(steps, MD_normalised(np.power(MD, 2), 3), label="analytical")
plt.legend()
plt.xlabel("steps")
plt.ylabel("$\langle R^2\\rangle$")
plt.title("Non avoiding walk")
plt.legend()
plt.show()
fig = plt.figure()
ax=plt.axes(projection='3d')
coordiates_grid = read_csv_with3_columns("lattice_positions_10.csv", "X, Y, Z\n")
coordinates_free = read_csv_with3_columns("spheres_avoiding_cant_go_back8.csv", "XYZ\n")
plot_grid(0, 10, coordiates_grid[3], coordiates_grid[4], coordiates_grid[5])
plot_3d(coordinates_free)
plt.show()
error_free = 100*np.divide(np.subtract(np.array(MD_normalised(np.power(MD, 2),3)), np.array(MD_normalised(MSD, 2))), np.array(MD_normalised(np.power(MD, 2),3)))
error_lattice = 100*np.divide(np.subtract(np.array(MD_normalised(np.power(MD_lattice, 2),3)), np.array(MD_normalised(MSD_lattice, 2))), np.array(MD_normalised(np.power(MD_lattice, 2),3)))
plt.plot(steps, error_free, label="Error freely jointed chain")
plt.plot(steps, error_lattice, label="Error walk on grid")
plt.legend()
plt.xlabel("steps")
plt.ylabel("Error in %")
plt.title("Percentage error")
plt.show()
