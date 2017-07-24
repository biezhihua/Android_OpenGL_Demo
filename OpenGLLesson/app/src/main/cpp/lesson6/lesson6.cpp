
#include <jni.h>
#include <graphics/GLUtils.h>
#include "Native6Lesson.h"

#define LOG_TAG "Lesson"
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##args)

Native6Lesson *lesson6;

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson6_NativeSixJniLib_setMinFilter(JNIEnv *env, jclass type, jint filter) {


    if (lesson6) {
        lesson6->setMinFilter(filter);
    }

}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson6_NativeSixJniLib_setMagFilter(JNIEnv *env, jclass type, jint filter) {

    if (lesson6) {
        lesson6->setMagFilter(filter);
    }

}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson6_NativeSixJniLib_setDelta(JNIEnv *env, jclass type, jfloat x, jfloat y) {

    if (lesson6) {
        lesson6->setDelta(x, y);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson6_NativeSixJniLib_onSurfaceCreate(JNIEnv *env, jclass type,
                                                        jobject assetManager) {

    GLUtils::setEnvAndAssetManager(env, assetManager);
    if (lesson6) {
        delete lesson6;
        lesson6 = NULL;
    }
    lesson6 = new Native6Lesson();
    lesson6->create();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson6_NativeSixJniLib_onSurfaceChange(JNIEnv *env, jclass type, jint width,
                                                        jint height) {
    if (lesson6) {
        lesson6->change(width, height);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson6_NativeSixJniLib_onDrawFrame(JNIEnv *env, jclass type) {

    if (lesson6) {
        lesson6->draw();
    }
}