//
// Created by Administrator on 2020/3/23.
//

#include "FaceRepository.h"

FaceRepository::FaceRepository() {
    mFaceCompile = new FaceCompileHelper();
}

void FaceRepository::putFaceData(JNIEnv *env, jbyteArray faceData, jint width, jint height) {
    FaceModel *faceModel = new FaceModel();

    cv::Mat src = mFaceCompile->getImageSrcData(env, faceData, width, height);
    cv::Mat gray = mFaceCompile->getGrayData(src);

    faceModel->faceData = faceData;
    faceModel->mSrcMat = src;
    faceModel->mBinarizationMat = mFaceCompile->getBinarizationHist(gray);
    faceModel->width = width;
    faceModel->height = height;

    mFaceList[mCurrentIndex] = faceModel;

    mCurrentIndex++;
}
