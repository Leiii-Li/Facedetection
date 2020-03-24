//
// Created by Administrator on 2020/3/23.
//

#include "FaceCompileHelper.h"
#include <opencv2/opencv.hpp>

cv::Mat FaceCompileHelper::getYunSrcData(JNIEnv *env,
                                         jbyteArray data_,
                                         int width,
                                         int height) {

    jbyte *data = env->GetByteArrayElements(data_, NULL);
    cv::Mat src(height * 3 / 2, width, CV_8UC1, data);
    return src;
}

cv::Mat FaceCompileHelper::yuv2Rgb(cv::Mat yuvMat) {
    // 转RGB
    cvtColor(yuvMat, yuvMat, cv::COLOR_YUV2RGBA_NV21);
    return yuvMat;
}

cv::Mat FaceCompileHelper::getGrayData(cv::Mat src) {
    cv::Mat gray;
    //灰度化
    cvtColor(src, gray, cv::COLOR_RGBA2GRAY);
    return gray;
}

cv::Mat FaceCompileHelper::getBinarizationHist(cv::Mat gray) {
    //二值化
    equalizeHist(gray, gray);
    return gray;
}

cv::Mat FaceCompileHelper::getImageSrcData(JNIEnv *env, jbyteArray data_, int width, int height) {
    jbyte *data = env->GetByteArrayElements(data_, NULL);
    cv::Mat src(height, width, CV_8UC3, data);
    return src;
}

