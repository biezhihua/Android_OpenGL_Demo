package com.bzh.gl.lesson5;

import android.content.res.AssetManager;

public class NativeFiveJniLib {

    static {
        System.loadLibrary("lesson-lib");
    }

    public static native void onSurfaceCreate(AssetManager assetManager);

    public static native void onSurfaceChange(int width, int height);

    public static native void onDrawFrame();

    public static native void switchMode();





}
