package com.bzh.gl.lesson1;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class LessonOneRenderer implements GLSurfaceView.Renderer {

    private Triangle mTriangle1;

    /**
     * The method is called when the surface is first created.
     * It will also be called if we lose our surface context and
     * it is later recreated by the system.
     */
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        // Set the background clear color to gray.
        GLES20.glClearColor(0.5F, 0.5F, 0.5F, 0.5F);
        mTriangle1 = new Triangle(Triangle.Triangle1VerticesData);
    }

    /**
     * This method is called whenever the surface changes;
     * for example, when switching from portrait to landscape.
     * It is called after the surface has been created.
     */
    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        mTriangle1.initProjectionMatrix(width, height);
    }

    /**
     * This method is called whenever it's time to draw a new frame.
     */
    @Override
    public void onDrawFrame(GL10 gl) {
        mTriangle1.draw();
    }
}
