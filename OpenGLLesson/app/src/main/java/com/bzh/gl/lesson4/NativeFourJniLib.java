package com.bzh.gl.lesson4;

import android.content.res.AssetManager;

public class NativeFourJniLib {

    static {
        System.loadLibrary("lesson-lib");
    }

    public static native void onSurfaceCreate(AssetManager assetManager);

    public static native void onSurfaceChange(int width, int height);

    public static native void onDrawFrame();


}
