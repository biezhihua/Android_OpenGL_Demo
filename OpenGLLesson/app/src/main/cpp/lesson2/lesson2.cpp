
#include <jni.h>
#include <android/log.h>
#include "Native2Lesson.h"

#define LOG_TAG "Lesson"
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##args)

extern "C" {
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson2_NativeTwoJniLib_onSurfaceCreate(JNIEnv *env, jclass type);
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson2_NativeTwoJniLib_onSurfaceChange(JNIEnv *env, jclass type, jint width,
                                                        jint height);
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson2_NativeTwoJniLib_onDrawFrame(JNIEnv *env, jclass type);
}

static Native2Lesson *lesson2 = NULL;


static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s \n", name, v);
}

static void checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson2_NativeTwoJniLib_onSurfaceCreate(JNIEnv *env, jclass type) {
    if (lesson2) {
        delete lesson2;
        lesson2 = NULL;
    }

    // Print some OpenGL info
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    lesson2 = new Native2Lesson();
    lesson2->create();
}

JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson2_NativeTwoJniLib_onSurfaceChange(JNIEnv *env, jclass type, jint width,
                                                        jint height) {
    if (lesson2) {
        lesson2->change(width, height);
    }
}

JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson2_NativeTwoJniLib_onDrawFrame(JNIEnv *env, jclass type) {
    if (lesson2) {
        lesson2->draw();
    }
}