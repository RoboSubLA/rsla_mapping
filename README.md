# Lanturn Mapping "how to install for dummies" (YOU)

## Installation

Make sure you have ROS2 Iron setup
This install script should have every thing you need for ROS
```
cd ~
git clone https://github.com/RoboSubLA/ros-iron-install
cd ros-iron-install
sudo ./install-ros2-iron.sh -d
```

Install glfw3 for the custom visualizer
`sudo apt install libglfw3-dev`


Clone the repo obviously dumbass silly

## Building

Navigate to ros workspace folder

Run these commands
```
colcon build --packages-select mapping
. install/setup.bash
ros2 run mapping driver
```

## how it works

## Dependencies

