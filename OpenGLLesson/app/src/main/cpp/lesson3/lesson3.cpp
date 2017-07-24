
#include <jni.h>
#include "Native3Lesson.h"

Native3Lesson *lesson3;

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson3_NativeThreeJniLib_onSurfaceCreate(JNIEnv *env, jclass type) {
    if (lesson3) {
        delete lesson3;
        lesson3 = NULL;
    }
    lesson3 = new Native3Lesson();
    lesson3->create();

}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson3_NativeThreeJniLib_onSurfaceChange(JNIEnv *env, jclass type, jint width,
                                                          jint height) {

    if (lesson3) {
        lesson3->change(width, height);
    }

}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson3_NativeThreeJniLib_onDrawFrame(JNIEnv *env, jclass type) {

    if (lesson3) {
        lesson3->draw();
    }

}