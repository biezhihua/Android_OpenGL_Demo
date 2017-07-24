#include <jni.h>
#include <GLES2/gl2.h>
#include <android/log.h>

#define  LOG_TAG    "Native"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C" {
JNIEXPORT void JNICALL
Java_com_bzh_gl_native_1lesson1_NativeLesson1JniLib_onSurfaceCreate(JNIEnv *env, jclass type);
JNIEXPORT void JNICALL
Java_com_bzh_gl_native_1lesson1_NativeLesson1JniLib_onDrawFrame(JNIEnv *env, jclass type);
JNIEXPORT void JNICALL
Java_com_bzh_gl_native_1lesson1_NativeLesson1JniLib_onSurfaceChange(JNIEnv *env, jclass type,
                                                                    jint width, jint height);
};


void on_surface_create() {
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    LOGD("on_surface_create");
}

void on_surface_change() {
    LOGD("on_surface_change");
}

void on_draw_frame() {
    glClear(GL_COLOR_BUFFER_BIT);
    LOGD("on_draw_frame");
}

JNIEXPORT void JNICALL
Java_com_bzh_gl_native_1lesson1_NativeLesson1JniLib_onSurfaceCreate(JNIEnv *env, jclass type) {
    on_surface_create();
}

JNIEXPORT void JNICALL
Java_com_bzh_gl_native_1lesson1_NativeLesson1JniLib_onDrawFrame(JNIEnv *env, jclass type) {
    on_draw_frame();
}

JNIEXPORT void JNICALL
Java_com_bzh_gl_native_1lesson1_NativeLesson1JniLib_onSurfaceChange(JNIEnv *env, jclass type,
                                                                    jint width, jint height) {
    on_surface_change();
}
