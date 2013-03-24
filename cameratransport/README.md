Links for bagfiles : 

www.cs.uml.edu/~bschroed/rover_cam/uvc_camera_raw.bag.zip
www.cs.uml.edu/~bschroed/rover_cam/usb_cam_raw.bag.zip


Useful links : 

http://www.ros.org/wiki/image_transport

http://www.ros.org/wiki/rostopic


Things we need to do : 

- Measure bandwidth of the video information given (ros_topic)

- Stream data from the rosbag file over network from one computer to another

  - This requires some way of viewing the video once it's transported through
    ROS.

- Work on minimizing data sent and maximizing quality

- Test 4G connection via tether