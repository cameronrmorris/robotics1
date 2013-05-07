Setup with this:

* cd ~ros/stacks OR WHATEVER ROS YOU HAVE
* svn co http://svn.code.sf.net/p/bosch-ros-pkg/code/trunk/stacks/bosch_drivers/usb_cam/
* rosdep install usb_cam --os=ubuntu:quantal
* rosmake usb_cam

UDEV Rules:

The rules are located in the udev folder

To setup simply copy this to the /etc/udev/rules.d directory and restart the 
udev service. Then plug the usb cameras in. These can configured for any name.