package com.bzh.gl.native_lesson1;

/**
 * Wrapper the native library
 */
public class NativeLesson1JniLib {

    static {
        System.loadLibrary("lesson-lib");
    }

    public static native void onSurfaceCreate();

    public static native void onSurfaceChange(int width, int height);

    public static native void onDrawFrame();
}
