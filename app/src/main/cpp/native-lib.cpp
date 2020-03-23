#include <jni.h>
#include <string>
#include "opencv2/opencv.hpp"
#include "CascadeDetectorAdapter.h"
#include <android/native_window_jni.h>

ANativeWindow *window = 0;

cv::DetectionBasedTracker *tracker = 0;


extern "C"
JNIEXPORT void JNICALL
Java_com_nelson_demoopencv1_OpencvHelper_init(JNIEnv *env, jobject instance, jstring path_) {
    const char *path = env->GetStringUTFChars(path_, 0);


    //创建检测器  Ptr是智能指针，不需要关心释放
    cv::Ptr<cv::CascadeClassifier> mainClassifier = cv::makePtr<cv::CascadeClassifier>(path);
    cv::Ptr<CascadeDetectorAdapter> mainDetector = cv::makePtr<CascadeDetectorAdapter>(mainClassifier);

    //创建跟踪器
    cv::Ptr<cv::CascadeClassifier> trackClassifier = cv::makePtr<cv::CascadeClassifier>(path);
    cv::Ptr<CascadeDetectorAdapter> trackingDetector = cv::makePtr<CascadeDetectorAdapter>(trackClassifier);

    //开始识别，结果在CascadeDetectorAdapter中返回
    cv::DetectionBasedTracker::Parameters DetectorParams;
    tracker = new cv::DetectionBasedTracker(mainDetector, trackingDetector, DetectorParams);
    tracker->run();

    env->ReleaseStringUTFChars(path_, path);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nelson_demoopencv1_OpencvHelper_postData(JNIEnv *env, jobject instance, jbyteArray data_,
                                                  jint width, jint height, jint cameraId) {
    jbyte *data = env->GetByteArrayElements(data_, NULL);

    // 数据的行数也就是数据高度，因为数据类型是NV21，所以为Y+U+V的高度, 也就是height + height/4 + height/4
    cv::Mat src(height * 3 / 2, width, CV_8UC1, data);

    // 转RGB
    cvtColor(src, src, cv::COLOR_YUV2RGBA_NV21);

    cv::Mat gray;
    //灰度化
    cvtColor(src, gray, cv::COLOR_RGBA2GRAY);
    //二值化
    equalizeHist(gray, gray);

    std::vector<cv::Rect> faces;
    //检测图片
    tracker->process(gray);
    //获取CascadeDetectorAdapter中的检测结果
    tracker->getObjects(faces);
    //画出矩形
    for (cv::Rect face : faces) {
        rectangle(src, face, cv::Scalar(255, 0, 0));
    }

    //显示到surface
    if (window) {
        ANativeWindow_setBuffersGeometry(window, src.cols, src.rows, WINDOW_FORMAT_RGBA_8888);
        ANativeWindow_Buffer window_buffer;
        do {
            //lock失败 直接brek出去
            if (ANativeWindow_lock(window, &window_buffer, 0)) {
                ANativeWindow_release(window);
                window = 0;
                break;
            }

            uint8_t *dst_data = static_cast<uint8_t *>(window_buffer.bits);
            //stride : 一行多少个数据
            //（RGBA） * 4
            int dst_linesize = window_buffer.stride * 4;

            //一行一行拷贝，src.data是图片的RGBA数据，要拷贝到dst_data中，也就是window的缓冲区里
            for (int i = 0; i < window_buffer.height; ++i) {
                memcpy(dst_data + i * dst_linesize, src.data + i * src.cols * 4, dst_linesize);
            }
            //提交刷新
            ANativeWindow_unlockAndPost(window);
        } while (0);

    }
    src.release();
    gray.release();
    env->ReleaseByteArrayElements(data_, data, 0);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_nelson_demoopencv1_OpencvHelper_setSurface(JNIEnv *env,
                                                    jobject instance,
                                                    jobject surface) {

    if (window) {
        ANativeWindow_release(window);
        window = 0;
    }
    window = ANativeWindow_fromSurface(env, surface);

}