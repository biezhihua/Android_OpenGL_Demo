package com.bzh.gl.lesson2;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.support.annotation.RequiresApi;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

@RequiresApi(api = Build.VERSION_CODES.CUPCAKE)
class LessonTwoRenderer implements GLSurfaceView.Renderer {

    private Cube mCube;

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        // Set the background clear color to black.
        GLES20.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        // Use culling to remove back face.
        GLES20.glEnable(GLES20.GL_CULL_FACE);

        // Enable depth testing
        GLES20.glEnable(GLES20.GL_DEPTH_TEST);

        mCube = new Cube();
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
