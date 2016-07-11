#ifndef IMAGE_PERSPECTIVE_TRANSFORMER_H
#define IMAGE_PERSPECTIVE_TRANSFORMER_H

#include <cv.h>
#include <vector>

class ImagePerspectiveTransformer
{
public:
    ImagePerspectiveTransformer();
    ImagePerspectiveTransformer(const std::vector<float> &m,
            const std::vector<int> &dstSize);
    bool setMatrix(const cv::Mat &m, const cv::Size &dstSize);
    bool setMatrix(const std::vector<float> &m, const std::vector<int> &dstSize);
    void transformation(const cv::Mat &src, cv::Mat &dst);

private:
    cv::Mat m_;
    cv::Size dstSize_;
};

#endif
