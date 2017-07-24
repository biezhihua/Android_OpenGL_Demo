
package com.bzh.gl.lesson5;

import android.app.Activity;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class LessonFiveRenderer implements GLSurfaceView.Renderer, BlendingMode {

    private Activity mActivity;

    public LessonFiveRenderer(Activity activity) {

        mActivity = activity;
    }

    private Cube mCube;

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        // Set the background clear color to black.
        GLES20.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        // Use culling to remove back face.
        GLES20.glDisable(GLES20.GL_CULL_FACE);

        // Enable depth testing
        GLES20.glDisable(GLES20.GL_DEPTH_TEST);

        // Enable blending
        GLES20.glEnable(GLES20.GL_BLEND);

        GLES20.glBlendFunc(GLES20.GL_ONE, GLES20.GL_ONE);

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

    @Override
    public void switchMode() {
        mCube.switchMode();
    }
}
