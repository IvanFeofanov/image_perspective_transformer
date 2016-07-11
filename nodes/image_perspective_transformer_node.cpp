#include <image_perspective_transformer/image_perspective_transformer_node.h>

#include <cv.h>
#include <cv_bridge/cv_bridge.h>

#include <string>

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "image_perspective_transformer");

    ImagePerspectiveTransformerNode iptn;
    iptn.spin();
    return 0;
}

ImagePerspectiveTransformerNode::ImagePerspectiveTransformerNode() :
    node_("~"),
    imageTr_(node_)
{
    imageSub_ = imageTr_.subscribe("input_image", 1,
            &ImagePerspectiveTransformerNode::takeHandleAndSendImage, this);
    imagePub_ = imageTr_.advertise("out_image", 1);

    serviceUpdateParameters_ = node_.advertiseService("update_parameters",
            &ImagePerspectiveTransformerNode::updateParametersCap, this);

    //parameters
    defaultImageSize_ = std::vector<int>(2);
    defaultImageSize_[0] = 640;
    defaultImageSize_[1] = 480;

    defaultMatrix_ = std::vector<float>(9);
    defaultMatrix_[0] = 1.0;
    defaultMatrix_[4] = 1.0;
    defaultMatrix_[8] = 1.0;

    defaultFrameRate_ = 30;

    updateParameters();
    
    ROS_INFO("Starting");
}

void ImagePerspectiveTransformerNode::spin()
{
    ros::Rate loop_rate(30);
    while(node_.ok()){
        ros::spinOnce();
        loop_rate.sleep();
    }
}

void ImagePerspectiveTransformerNode::takeHandleAndSendImage(
        const sensor_msgs::ImageConstPtr &msg)
{
    cv_bridge::CvImagePtr sourceImagePtr;
    cv_bridge::CvImagePtr distanceImagePtr;

    sourceImagePtr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

    transformer_.transformation(sourceImagePtr->image, sourceImagePtr->image);

    imagePub_.publish(sourceImagePtr->toImageMsg());
}

void ImagePerspectiveTransformerNode::updateParameters()
{

    node_.param("frame_rate", frameRate_, defaultFrameRate_);
    node_.param("distane_image_size", distanceImageSize_, defaultImageSize_);
    node_.param("matrix", matrix_, defaultMatrix_);

    transformer_.setMatrix(matrix_, distanceImageSize_);
}

bool ImagePerspectiveTransformerNode::updateParametersCap(
        std_srvs::Empty::Request &req, std_srvs::Empty::Response &res)
{
    updateParameters();
    return true;
}


