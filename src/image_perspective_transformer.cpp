#include <image_perspective_transformer/image_perspective_transformer.h>

ImagePerspectiveTransformer::ImagePerspectiveTransformer()
{

}

ImagePerspectiveTransformer::ImagePerspectiveTransformer(
        const std::vector<float> &m, const std::vector<int> &dstSize)
{
    setMatrix(m, dstSize);
}

bool ImagePerspectiveTransformer::setMatrix(const cv::Mat &m,
        const cv::Size &dstSize)
{
    if(m.empty() || m.type() != CV_32FC1 ||
       m.size() != cv::Size(3, 3) || dstSize == cv::Size()){
        return false;
    }

    m_ = m;
    dstSize_ = dstSize;

    return true;
}

bool ImagePerspectiveTransformer::setMatrix(const std::vector<float> &m,
        const std::vector<int> &dstSize)
{
    if(m.empty() || dstSize.empty())
        return false;

    m_ = cv::Mat(3, 3, CV_32FC1);
    for(int i = 0; i < m.size(); ++i){
        m_.at<float>(i) = m[i];
    }
    dstSize_ = cv::Size(dstSize[0], dstSize[1]);
}

void ImagePerspectiveTransformer::transformation(const cv::Mat &src,
        cv::Mat &dst)
{
    if(m_.empty() || dstSize_ == cv::Size()){
        dst = src.clone();
        return;
    }

    cv::warpPerspective(src, dst, m_, dstSize_);

    return;
}
