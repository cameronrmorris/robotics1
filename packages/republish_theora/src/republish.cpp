#include <ros/ros.h>
#include <sensor_msgs/CompressedImage.h>
#include <sys/types.h>
#include <signal.h>

int n = 0;

void messageCallBack( const sensor_msgs::CompressedImage::ConstPtr& msg ) {

  ROS_INFO( "Message detected\n");
  n = 5;

}

int main( int argc, char *argv[] ) {

  pid_t pid ;
  char in_topic[32];
  char out_topic[32];

  if( argc < 2 ) {
    ROS_INFO("Usage: republish_theora <in topic> <out topic> <out plugin>\n");

    return 0;
  }

  switch( pid = fork() ) {

  case -1:
    perror("Failed to fork!\n");
    exit(-1);
  case 0: // Republisher
    
    sprintf( in_topic, "in:=%s", argv[1] );
    sprintf( out_topic, "out=%s", argv[2] );
    execlp("rosrun", "rosrun", "image_transport", "republish", "theora",
	   in_topic, argv[3], out_topic, NULL );

    perror("execlp");
    exit(1);

  default: // Monitor

    ROS_INFO( "Created republisher node with pid : %d", pid );
    ros::init(argc, argv, "republish_monitor" );

    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe( argv[2], 10, messageCallBack );
    
    ros::Rate loop_rate(10);

    while( ros::ok() ) {

      ros::spinOnce();
      n = n - 1;

      // Probably not working, KILL THYSELF
      if( n < 0 ) {
	
	// Kill child
	kill(pid, SIGTERM);
	

      }
      loop_rate.sleep();

    }
    
    exit(1);
  }
  return  0;
}
