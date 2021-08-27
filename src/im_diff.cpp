#include <ros/ros.h>
#include <ros/console.h>
#include <image_transport/image_transport.h>

image_transport::Publisher pub;


void imageCallback(const sensor_msgs::ImageConstPtr& new_image)
{
    static bool have_old=false;
    static sensor_msgs::Image::Ptr old_image(new sensor_msgs::Image);
    
    if (have_old)
    {
        for(uint row=0; row < new_image->height; row++)
        {
            for (uint col=0; col < new_image->width; col++)
            {
                int index = row*new_image->step + col;
                old_image->data[index] = abs(old_image->data[index] - new_image->data[index]);
            }
        }
        // /*

        pub.publish(old_image);
    }
    else
    {
    	have_old=true;
    	old_image->height = new_image->height;
    	old_image->width = new_image->width;
        old_image->encoding = new_image->encoding;
        old_image->is_bigendian = new_image->is_bigendian;
        old_image->step = new_image->step;
        old_image->data.resize(new_image->width*new_image->height);
        ROS_INFO("First image received");
    }
    
    // old_image = new_image;
    old_image->header = new_image->header;
    old_image->data = new_image->data;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_differencer");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    pub = it.advertise("camera/image_diff", 1);
    
    image_transport::Subscriber sub = 
        it.subscribe("camera/image_raw", 1, imageCallback);
    
    ros::spin();

    return 0;
}
