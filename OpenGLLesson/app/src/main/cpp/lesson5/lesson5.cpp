
#include <jni.h>
#include <graphics/GLUtils.h>
#include "Native5Lesson.h"

#define LOG_TAG "Lesson"
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##args)

Native5Lesson *lesson5;

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson5_NativeFiveJniLib_onSurfaceCreate(JNIEnv *env, jclass type,
                                                         jobject assetManager) {

    GLUtils::setEnvAndAssetManager(env, assetManager);
    if (lesson5) {
        delete lesson5;
        lesson5 = NULL;
    }
    lesson5 = new Native5Lesson();
    lesson5->create();

}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson5_NativeFiveJniLib_onSurfaceChange(JNIEnv *env, jclass type, jint width,
                                                         jint height) {
    if (lesson5) {
        lesson5->change(width, height);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson5_NativeFiveJniLib_onDrawFrame(JNIEnv *env, jclass type) {
    if (lesson5) {
        lesson5->draw();
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson5_NativeFiveJniLib_switchMode(JNIEnv *env, jclass type) {

    if (lesson5) {
        lesson5->switchMode();
    }
}