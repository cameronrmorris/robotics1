#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <stdio.h>

namespace enc = sensor_msgs::image_encodings;

class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;
public:
  ImageConverter(char publisher_name[32], char usb_source[32] )
    : it_(nh_)
  {

    image_pub_ = it_.advertise( publisher_name, 1 );
    image_sub_ = it_.subscribe( usb_source, 1, &ImageConverter::imageCb, this );
  }

  ~ImageConverter()
  {

  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, enc::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

    image_pub_.publish(cv_ptr->toImageMsg());
  }
};


int main(int argc, char **argv)
{
  char buf[32];

  if ( argc < 3 ) {

    printf( "Usage: imageconvert <id> <usb_source>\n" );
    
    return 0;

  }
  ros::init(argc, argv, "imageconverter");  
  sprintf( buf,  "/image_compressed%s", argv[1] ) ;
  printf( "SOURCE=%s DESTINATION=%s\n", argv[2], buf );
  ImageConverter ic(buf, argv[2]); 	
  ros::spin();
}
