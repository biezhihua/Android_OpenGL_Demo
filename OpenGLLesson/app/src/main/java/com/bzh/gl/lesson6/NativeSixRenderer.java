package com.bzh.gl.lesson6;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.support.annotation.RequiresApi;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

@RequiresApi(api = Build.VERSION_CODES.CUPCAKE)
public class NativeSixRenderer implements GLSurfaceView.Renderer, Action {

    private Activity mActivity;

    public NativeSixRenderer(Activity activity) {
        mActivity = activity;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        NativeSixJniLib.onSurfaceCreate(mActivity.getAssets());
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        NativeSixJniLib.onSurfaceChange(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        NativeSixJniLib.onDrawFrame();
    }

    @Override
    public void setMinFilter(int filter) {
        NativeSixJniLib.setMinFilter(filter);
    }

    @Override
    public void setMagFilter(int filter) {
        NativeSixJniLib.setMagFilter(filter);
    }

    @Override
    public void setDelta(float deltaX, float deltaY) {
        NativeSixJniLib.setDelta(deltaX, deltaY);
    }
}
