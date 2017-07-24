package com.bzh.gl.lesson7;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.support.annotation.RequiresApi;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

@RequiresApi(api = Build.VERSION_CODES.CUPCAKE)
public class NativeSevenRenderer implements GLSurfaceView.Renderer, Action {

    private Activity mActivity;
    private GLSurfaceView mGlSurfaceView;

    public NativeSevenRenderer(Activity activity, GLSurfaceView glSurfaceView) {
        mActivity = activity;
        mGlSurfaceView = glSurfaceView;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        NativeSevenJniLib.onSurfaceCreate(mActivity.getAssets());
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        NativeSevenJniLib.onSurfaceChange(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        NativeSevenJniLib.onDrawFrame();
    }

    @Override
    public void setDelta(float deltaX, float deltaY) {
        NativeSevenJniLib.setDelta(deltaX, deltaY);
    }

    @Override
    public void decreaseCubeCount() {
        NativeSevenJniLib.decreaseCubeCount();
    }

    @Override
    public void increaseCubeCount() {
        NativeSevenJniLib.increaseCubeCount();
    }

    @Override
    public void toggleVBOs() {
        NativeSevenJniLib.toggleVBOs();
    }

    @Override
    public void toggleStride() {
        NativeSevenJniLib.toggleStride();
    }
}
