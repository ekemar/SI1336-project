from typing import List
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D


fig = plt.figure()
ax=plt.axes(projection='3d')
with open("spheres_nonavoiding.csv") as f:
    data = f.read()
    spheres_data: List[str] = data.split("XYZ\n")
    spheres_coordinates = []
    for sphere_data in spheres_data:
        sphere_x_coordinates = []
        sphere_y_coordinates = []
        sphere_z_coordinates = []
        for line in sphere_data.split("\n"):
            line = line.strip()
            if not line:
                continue
            #if line != " ":
            #print("line ", line)
            x, y, z = line.split(",")
            sphere_x_coordinates.append(float(x))
            sphere_y_coordinates.append(float(y))
            sphere_z_coordinates.append(float(z))
        ax.plot(sphere_x_coordinates, sphere_y_coordinates, sphere_z_coordinates,"b")
        #ax.set_xlim3d(0.8, 1.0)
        #ax.set_ylim3d(0.8,1.0)
        #ax.set_zlim3d(0.8,1.0)
    plt.show()

