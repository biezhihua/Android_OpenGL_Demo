package com.bzh.gl.native_lesson1;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class RendererWrapper implements GLSurfaceView.Renderer {

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        NativeLesson1JniLib.onSurfaceCreate();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        NativeLesson1JniLib.onSurfaceChange(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        NativeLesson1JniLib.onDrawFrame();
    }
}
