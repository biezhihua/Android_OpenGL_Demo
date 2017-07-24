package com.bzh.gl.lesson5;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.support.annotation.RequiresApi;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

@RequiresApi(api = Build.VERSION_CODES.CUPCAKE)
public class NativeFiveRenderer implements GLSurfaceView.Renderer, BlendingMode {

    private Activity mActivity;

    public NativeFiveRenderer(Activity activity) {
        mActivity = activity;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        NativeFiveJniLib.onSurfaceCreate(mActivity.getAssets());
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        NativeFiveJniLib.onSurfaceChange(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        NativeFiveJniLib.onDrawFrame();
    }

    @Override
    public void switchMode() {
        NativeFiveJniLib.switchMode();
    }
}
