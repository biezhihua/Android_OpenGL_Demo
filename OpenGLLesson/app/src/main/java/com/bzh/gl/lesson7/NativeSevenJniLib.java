package com.bzh.gl.lesson7;

import android.content.res.AssetManager;

public class NativeSevenJniLib {

    static {
        System.loadLibrary("lesson-lib");
    }

    public static native void onSurfaceCreate(AssetManager assetManager);

    public static native void onSurfaceChange(int width, int height);

    public static native void onDrawFrame();

    public static native void setDelta(float x, float y);

    public static native void decreaseCubeCount();

    public static native void increaseCubeCount();

    public static native void toggleVBOs();

    public static native void toggleStride();
}
