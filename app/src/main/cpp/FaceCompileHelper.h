//
// Created by Administrator on 2020/3/23.
//

#ifndef DEMOOPENCV1_FACECOMPILEHELPER_H
#define DEMOOPENCV1_FACECOMPILEHELPER_H
#include <opencv2/opencv.hpp>
#include <jni.h>
#include "include/opencv2/core/mat.hpp"

class FaceCompileHelper {
 public:
  cv::Mat getYunSrcData(JNIEnv *env, jbyteArray data_, int width, int height);
  cv::Mat yuv2Rgb(cv::Mat yuvMat);
  cv::Mat getGrayData(cv::Mat src);
  cv::Mat getBinarizationHist(cv::Mat gray);
  cv::Mat getImageSrcData(JNIEnv *env, jbyteArray data_, int width, int height);
};


#endif //DEMOOPENCV1_FACECOMPILEHELPER_H
