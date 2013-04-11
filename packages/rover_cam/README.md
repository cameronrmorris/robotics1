Setup with this:

cd ~ros/stacks OR WHATEVER ROS YOU HAVE
svn co http://svn.code.sf.net/p/bosch-ros-pkg/code/trunk/stacks/bosch_drivers/usb_cam/
rosdep install usb_cam --os=ubuntu:quantal
rosmake usb_cam

