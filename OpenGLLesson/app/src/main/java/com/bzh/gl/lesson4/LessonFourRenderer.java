
package com.bzh.gl.lesson4;

import android.app.Activity;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class LessonFourRenderer implements GLSurfaceView.Renderer {

    private Activity mActivity;

    public LessonFourRenderer(Activity activity) {

        mActivity = activity;
    }

    private Cube mCube;

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        // Set the background clear color to black.
        GLES20.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        // Use culling to remove back face.
        GLES20.glEnable(GLES20.GL_CULL_FACE);

        // Enable depth testing
        GLES20.glEnable(GLES20.GL_DEPTH_TEST);

        mCube = new Cube(mActivity);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        mCube.initProjectionMatrix(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        mCube.draw();
    }
}
