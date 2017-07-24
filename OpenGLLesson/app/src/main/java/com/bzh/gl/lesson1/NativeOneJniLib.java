package com.bzh.gl.lesson1;


public class NativeOneJniLib {

    static {
        System.loadLibrary("lesson-lib");
    }

    public static native void onSurfaceCreate();

    public static native void onSurfaceChange(int width, int height);

    public static native void onDrawFrame();

}
