
# Where Am I

This project utilizes ROS AMCL package to accurately localize a mobile robot inside 
a map in a simulated environment.


## Description

AMCL is a probabilistic localization system for a robot moving in 2D. It implements 
the adaptive Monte Carlo localization (AMCL) approach, which uses a 
particle filter to track the 
pose of a robot against a known map[^1](http://wiki.ros.org/amcl)
## Build
Project was built and executed in Lubuntu Linux with CMake & g++/gcc, ROS and Gazebo installed.

The robot and the world are from the [Go-Chase-it](https://github.com/Uamarnat/Go-Chase-it) 
project. Packages used are [amcl](http://wiki.ros.org/amcl), [map_server](http://wiki.ros.org/map_server),
[move_base](http://wiki.ros.org/move_base) and [teleop](https://github.com/ros-teleop/teleop_twist_keyboard). 

Open the terminal and create the catkin_ws/src workspace and add the files.

Build with catkin:
```
catkin_make
source devel/setup.bash
```

Launch the world in Gazebo:
```
roslaunch my_robot world.launch
```

In a new terminal tab launch the amcl node where the map_server, amcl, and move_back packages will be launched:
```
roslaunch my_robot amcl.launch
```

In a new terminal tab launch the teleop node:
```
roslaunch teleop_twist_keyboard teleop_twist_keyboard.py
```

In the RViz window:

* Select 'odom' for fixed frame
* Click the “Add” button and add the following:
    - RobotModel
    - Map and select first topic '/map'
    - PoseArray and select topic '/particlecloud'

Now in the Gazebo world move the robot to a random position in the enviornent and move it 
with the teleop controls. In RViz the robot's particles are generated and continue to localize 
as the mobot moves around.
## Result
Localized robot:
![Localized](https://github.com/Uamarnat/Where-Am-I/blob/main/SS1.png?raw=true)

Robot Localizing:
![Localizing gif](https://github.com/Uamarnat/Where-Am-I/blob/main/Untitled%20video%20-%20Made%20with%20Clipchamp.gif?raw=true)


