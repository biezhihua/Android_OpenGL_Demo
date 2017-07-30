package com.bzh.gl.lesson8;

import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.support.annotation.RequiresApi;

import com.bzh.gl.lesson7.LessonSevenActivity;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

@RequiresApi(api = Build.VERSION_CODES.CUPCAKE)
public class NativeEightRenderer implements GLSurfaceView.Renderer, Action {

    private LessonSevenActivity mActivity;
    private GLSurfaceView mGlSurfaceView;

    static {
        System.loadLibrary("lesson-lib");
    }

    public NativeEightRenderer(LessonSevenActivity activity, GLSurfaceView glSurfaceView) {
        mActivity = activity;
        mGlSurfaceView = glSurfaceView;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        nativeSurfaceCreate(mActivity.getAssets());
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        nativeSurfaceChange(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        nativeDrawFrame();
    }

    @Override
    public void setDelta(float deltaX, float deltaY) {
        nativeSetDelta(deltaX, deltaY);
    }

    public native void nativeSurfaceCreate(AssetManager assetManager);

    public native void nativeSurfaceChange(int width, int height);

    public native void nativeDrawFrame();

    public native void nativeSetDelta(float x, float y);
}
