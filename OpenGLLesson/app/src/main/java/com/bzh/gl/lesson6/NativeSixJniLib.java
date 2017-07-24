package com.bzh.gl.lesson6;

import android.content.res.AssetManager;

public class NativeSixJniLib {

    static {
        System.loadLibrary("lesson-lib");
    }

    public static native void onSurfaceCreate(AssetManager assetManager);

    public static native void onSurfaceChange(int width, int height);

    public static native void onDrawFrame();

    public static native void setDelta(float x, float y);

    public static native void setMinFilter(int filter);

    public static native void setMagFilter(int filter);
}
