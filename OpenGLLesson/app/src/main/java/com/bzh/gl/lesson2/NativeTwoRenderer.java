package com.bzh.gl.lesson2;

import android.opengl.GLSurfaceView;
import android.os.Build;
import android.support.annotation.RequiresApi;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

@RequiresApi(api = Build.VERSION_CODES.CUPCAKE)
public class NativeTwoRenderer implements GLSurfaceView.Renderer {

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        NativeTwoJniLib.onSurfaceCreate();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        NativeTwoJniLib.onSurfaceChange(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        NativeTwoJniLib.onDrawFrame();
    }
}
