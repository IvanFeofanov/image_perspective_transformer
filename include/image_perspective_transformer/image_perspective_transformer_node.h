#ifndef IMAGE_PERSPECTIVE_TRANSFORMER_NODE_H
#define IMAGE_PERSPECTIVE_TRANSFORMER_NODE_H

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <std_srvs/Empty.h>
#include <sensor_msgs/image_encodings.h>
#include <image_perspective_transformer/image_perspective_transformer.h>

#include <vector>

class ImagePerspectiveTransformerNode
{
public:
    ImagePerspectiveTransformerNode();
    void spin();

private:
    void takeHandleAndSendImage(const sensor_msgs::ImageConstPtr &msg);
    void updateParameters();
    bool updateParametersCap(std_srvs::Empty::Request &req,
            std_srvs::Empty::Response &res);

private:
    ros::NodeHandle node_;
    ros::ServiceServer serviceUpdateParameters_;
    image_transport::ImageTransport imageTr_;
    image_transport::Subscriber imageSub_;
    image_transport::Publisher imagePub_;

    ImagePerspectiveTransformer transformer_;

    //parameters
    std::vector<int> distanceImageSize_;
    std::vector<float> matrix_;
    int frameRate_;

    std::vector<int> defaultImageSize_;
    std::vector<float> defaultMatrix_;
    int defaultFrameRate_;
};

#endif
