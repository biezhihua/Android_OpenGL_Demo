
#include <jni.h>
#include <graphics/GLUtils.h>
#include "Native4Lesson.h"

#define LOG_TAG "Lesson"
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##args)

Native4Lesson *lesson4;

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson4_NativeFourJniLib_onSurfaceCreate(JNIEnv *env, jclass type,
                                                         jobject assetManager) {

    GLUtils::setEnvAndAssetManager(env, assetManager);
    if (lesson4) {
        delete lesson4;
        lesson4 = NULL;
    }
    lesson4 = new Native4Lesson();
    lesson4->create();

}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson4_NativeFourJniLib_onSurfaceChange(JNIEnv *env, jclass type, jint width,
                                                         jint height) {
    if (lesson4) {
        lesson4->change(width, height);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson4_NativeFourJniLib_onDrawFrame(JNIEnv *env, jclass type) {
    if (lesson4) {
        lesson4->draw();
    }
}