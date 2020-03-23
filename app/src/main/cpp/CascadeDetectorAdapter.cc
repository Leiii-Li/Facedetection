//
// Created by Administrator on 2020/3/23.
//

#include "CascadeDetectorAdapter.h"
#include <android/log.h>

#define LOG_TAG "CascadeDetectorAdapter"
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))

CascadeDetectorAdapter::CascadeDetectorAdapter(cv::Ptr<cv::CascadeClassifier> detector)
        : IDetector(),
          Detector(detector) {
    LOGD(" Init CascadeDetectorAdapter");
}

void CascadeDetectorAdapter::detect(const cv::Mat &Image, std::vector<cv::Rect> &objects) {
    Detector->detectMultiScale(Image,
                               objects,
                               scaleFactor,
                               minNeighbours,
                               0,
                               minObjSize,
                               maxObjSize);
}


CascadeDetectorAdapter::~CascadeDetectorAdapter() {
    LOGD(" Release CascadeDetectorAdapter");
}