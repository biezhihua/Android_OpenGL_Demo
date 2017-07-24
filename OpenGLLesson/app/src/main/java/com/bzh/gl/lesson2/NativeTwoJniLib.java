package com.bzh.gl.lesson2;

public class NativeTwoJniLib {

    static {
        System.loadLibrary("lesson-lib");
    }

    public static native void onSurfaceCreate();

    public static native void onSurfaceChange(int width, int height);

    public static native void onDrawFrame();


}
