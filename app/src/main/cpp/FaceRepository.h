//
// Created by Administrator on 2020/3/23.
//

#ifndef DEMOOPENCV1_FACEREPOSITORY_H
#define DEMOOPENCV1_FACEREPOSITORY_H


#include <jni.h>
#include <opencv2/core/mat.hpp>
#include "FaceCompileHelper.h"

struct FaceModel {
  jbyteArray faceData;
  cv::Mat mSrcMat;
  cv::Mat mBinarizationMat;
  int width;
  int height;
};

class FaceRepository {
 public:
  FaceRepository();
  void putFaceData(JNIEnv *env, jbyteArray faceData, jint width, jint height);
 private:
  FaceModel *mFaceList[10] = {};
  int mCurrentIndex = 0;
  FaceCompileHelper *mFaceCompile;
};


#endif //DEMOOPENCV1_FACEREPOSITORY_H
