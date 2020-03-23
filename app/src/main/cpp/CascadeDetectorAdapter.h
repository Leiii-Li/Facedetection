//
// Created by Administrator on 2020/3/23.
//

#ifndef DEMOOPENCV1_CASCADEDETECTORADAPTER_H
#define DEMOOPENCV1_CASCADEDETECTORADAPTER_H

#include <opencv2/opencv.hpp>

class CascadeDetectorAdapter: public cv::DetectionBasedTracker::IDetector {
 public:
  CascadeDetectorAdapter(cv::Ptr<cv::CascadeClassifier> detector);

  void detect(const cv::Mat &Image, std::vector<cv::Rect> &objects);

  virtual ~CascadeDetectorAdapter();

 private:
  CascadeDetectorAdapter();
  cv::Ptr<cv::CascadeClassifier> Detector;
};


#endif //DEMOOPENCV1_CASCADEDETECTORADAPTER_H
