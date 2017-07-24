
#include <android/log.h>
#include <jni.h>
#include <graphics/GLUtils.h>
#include "Native7Lesson.h"

#define LOG_TAG "Lesson"
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##args)

Native7Lesson *lesson7;

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson7_NativeSevenJniLib_onSurfaceCreate(JNIEnv *env, jclass type,
                                                          jobject assetManager) {

    LOGD("onSurfaceCreate");
    GLUtils::setEnvAndAssetManager(env, assetManager);
    if (lesson7) {
        delete lesson7;
        lesson7 = NULL;
    }
    lesson7 = new Native7Lesson();
    lesson7->create();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson7_NativeSevenJniLib_onSurfaceChange(JNIEnv *env, jclass type, jint width,
                                                          jint height) {

    LOGD("onSurfaceChange");
    lesson7->change(width, height);

}
extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson7_NativeSevenJniLib_onDrawFrame(JNIEnv *env, jclass type) {
    lesson7->draw();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson7_NativeSevenJniLib_setDelta(JNIEnv *env, jclass type, jfloat x, jfloat y) {

    LOGD("setDelta");
    if (lesson7 != nullptr) {
        lesson7->setDelta(x, y);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson7_NativeSevenJniLib_decreaseCubeCount(JNIEnv *env, jclass type) {

    LOGD("decreaseCubeCount");
    if (lesson7 != nullptr) {
        lesson7->decreaseCubeCount();
    }

}
extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson7_NativeSevenJniLib_increaseCubeCount(JNIEnv *env, jclass type) {

    LOGD("increaseCubeCount");
    if (lesson7 != nullptr) {
        lesson7->increaseCubeCount();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson7_NativeSevenJniLib_toggleVBOs(JNIEnv *env, jclass type) {

    LOGD("toggleVBOs");
    if (lesson7 != nullptr) {
        lesson7->toggleVBOs();
    }

}
extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson7_NativeSevenJniLib_toggleStride(JNIEnv *env, jclass type) {

    LOGD("toggleStride");
    if (lesson7 != nullptr) {
        lesson7->toggleStride();
    }

}
