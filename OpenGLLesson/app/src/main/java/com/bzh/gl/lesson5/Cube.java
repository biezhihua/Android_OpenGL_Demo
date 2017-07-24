package com.bzh.gl.lesson5;

import android.app.Activity;
import android.opengl.GLES20;
import android.opengl.Matrix;
import android.os.SystemClock;

import com.bzh.gl.R;
import com.bzh.gl.RawResourceReader;
import com.bzh.gl.Utils;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

public class Cube {

    /**
     * Store the model matrix. This matrix is used to move models from object space (where each model can be thought
     * of being located at the center of the universe) to world space.
     */
    private float[] mModelMatrix = new float[16];

    /**
     * Store the view matrix. This can be thought of as our camera. This matrix transforms world space to eye space;
     * it positions things relative to our eye.
     */
    private float[] mViewMatrix = new float[16];

    /**
     * Store the projection matrix. This is used to project the scene onto a 2D viewport.
     */
    private float[] mProjectionMatrix = new float[16];

    /**
     * Allocate storage for the final combined matrix. This will be passed into the shader program.
     */
    private float[] mMVPMatrix = new float[16];

    /**
     * Store our model data in a float buffer.
     */
    private FloatBuffer mCubePositions;
    private FloatBuffer mCubeColors;

    /**
     * This will be used to pass in the transformation matrix.
     */
    private int mMVPMatrixHandle;

    /**
     * This will be used to pass in model position information.
     */
    private int mPositionHandle;

    /**
     * This will be used to pass in model color information.
     */
    private int mColorHandle;

    /**
     * How many bytes per float.
     */
    private final int mBytesPerFloat = 4;

    /**
     * Size of the position data in elements.
     */
    private final int mPositionDataSize = 3;

    /**
     * Size of the color data in elements.
     */
    private final int mColorDataSize = 4;

    /**
     * This is a handle to our cube shading program.
     */
    private int mProgramHandle;

    /**
     * This will be used to switch between blending mode and regular mode
     */
    private boolean mBlendng = true;

    private Activity mActivity;


    public Cube(Activity activity) {
        mActivity = activity;

        initBuffer();

        initViewMatrix();

        initProgram();
    }

    private void initBuffer() {

        // Define points for a cube.
        // X, Y, Z
        final float[] p1p = {-1.0f, 1.0f, 1.0f};
        final float[] p2p = {1.0f, 1.0f, 1.0f};
        final float[] p3p = {-1.0f, -1.0f, 1.0f};
        final float[] p4p = {1.0f, -1.0f, 1.0f};
        final float[] p5p = {-1.0f, 1.0f, -1.0f};
        final float[] p6p = {1.0f, 1.0f, -1.0f};
        final float[] p7p = {-1.0f, -1.0f, -1.0f};
        final float[] p8p = {1.0f, -1.0f, -1.0f};

        final float[] cubePositionData = Utils.generateCubeData(p1p, p2p, p3p, p4p, p5p, p6p, p7p, p8p, p1p.length);

        // Points of the cube: color information
        // R, G, B, A
        final float[] p1c = {1.0f, 0.0f, 0.0f, 1.0f};        // red
        final float[] p2c = {1.0f, 0.0f, 1.0f, 1.0f};        // magenta
        final float[] p3c = {0.0f, 0.0f, 0.0f, 1.0f};        // black
        final float[] p4c = {0.0f, 0.0f, 1.0f, 1.0f};        // blue
        final float[] p5c = {1.0f, 1.0f, 0.0f, 1.0f};        // yellow
        final float[] p6c = {1.0f, 1.0f, 1.0f, 1.0f};        // white
        final float[] p7c = {0.0f, 1.0f, 0.0f, 1.0f};        // green
        final float[] p8c = {0.0f, 1.0f, 1.0f, 1.0f};        // cyan

        final float[] cubeColorData = Utils.generateCubeData(p1c, p2c, p3c, p4c, p5c, p6c, p7c, p8c, p1c.length);

        mCubePositions =
                ByteBuffer.allocateDirect(cubePositionData.length * mBytesPerFloat)
                        .order(ByteOrder.nativeOrder()).asFloatBuffer();
        mCubePositions.put(cubePositionData).position(0);

        mCubeColors = ByteBuffer.allocateDirect(cubeColorData.length * mBytesPerFloat)
                .order(ByteOrder.nativeOrder()).asFloatBuffer();
        mCubeColors.put(cubeColorData).position(0);
    }


    private void initViewMatrix() {
        // Position the eye in front of the origin
        final float eyeX = 0.0f;
        final float eyeY = 0.0f;
        final float eyeZ = 0f;

        // We are looking toward the distance.
        final float lookX = 0.0f;
        final float lookY = 0.0f;
        final float lookZ = -5.0f;

        // Set our up vector.
        // This is where our head would be pointing
        // were we holding the camera.
        final float upX = 0.0f;
        final float upY = 1.0f;
        final float upZ = 0.0f;

        // Set the view matrix.
        // This matrix can be said to represent the camera position,
        Matrix.setLookAtM(mViewMatrix, 0,
                eyeX, eyeY, eyeZ,
                lookX, lookY, lookZ,
                upX, upY, upZ);
    }

    private String getVertexShader() {
        return RawResourceReader.readTextFileFromRawResource(mActivity, R.raw.color_vertex_shader);
    }

    private String getFragmentShader() {
        return RawResourceReader.readTextFileFromRawResource(mActivity, R.raw.color_fragment_shader);
    }

    private void initProgram() {
        final int vertexShaderHandle = Utils.compileShader(GLES20.GL_VERTEX_SHADER, getVertexShader());
        final int fragmentShaderHandle = Utils.compileShader(GLES20.GL_FRAGMENT_SHADER, getFragmentShader());

        mProgramHandle = Utils.createAndLinkProgram(vertexShaderHandle, fragmentShaderHandle,
                new String[]{"a_Position", "a_Color"});
    }

    public void switchMode() {
        mBlendng = !mBlendng;

        if (mBlendng) {
            // No culling of back faces
            GLES20.glDisable(GLES20.GL_CULL_FACE);

            // No depth testing
            GLES20.glDisable(GLES20.GL_DEPTH_TEST);

            // Enable blending
            GLES20.glEnable(GLES20.GL_BLEND);
            GLES20.glBlendFunc(GLES20.GL_ONE, GLES20.GL_ONE);
        } else {
            // Culling back faces.
            GLES20.glEnable(GLES20.GL_CULL_FACE);

            // Enable depth testing
            GLES20.glEnable(GLES20.GL_DEPTH_TEST);

            // Disable blending
            GLES20.glDisable(GLES20.GL_BLEND);
        }
    }

    public void initProjectionMatrix(int width, int height) {
        // Set the OpenGL viewport to the same size as the surface.
        GLES20.glViewport(0, 0, width, height);

        // Create a new perspective projection matrix.
        // The height will stay the same.
        // while the width will vary as per aspect ratio.
        final float ratio = (float) width / height;
        final float left = -ratio;
        final float right = ratio;
        final float bottom = -1.0f;
        final float top = 1.0f;
        final float near = 1.0f;
        final float far = 10.0f;

        Matrix.frustumM(mProjectionMatrix, 0, left, right, bottom, top, near, far);
    }

    public void draw() {
        if (mBlendng) {
            GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
        } else {
            GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT | GLES20.GL_DEPTH_BUFFER_BIT);
        }
        // Do a compile rotation every 10 seconds.
        long time = SystemClock.uptimeMillis() % 10000L;
        float angleInDegrees = (360.0f / 10000.0f) * ((int) time);

        // Set our pre-vertex lighting program.
        GLES20.glUseProgram(mProgramHandle);

        // Set program handle for cube drawing.
        mMVPMatrixHandle = GLES20.glGetUniformLocation(mProgramHandle, "u_MVPMatrix");

        mPositionHandle = GLES20.glGetAttribLocation(mProgramHandle, "a_Position");
        mColorHandle = GLES20.glGetAttribLocation(mProgramHandle, "a_Color");

        // right
        Matrix.setIdentityM(mModelMatrix, 0);
        Matrix.translateM(mModelMatrix, 0, 4.0f, 0.0f, -7.0f);
        Matrix.rotateM(mModelMatrix, 0, angleInDegrees, 1.0f, 0.0f, 0.0f);
        drawCube();

        // left
        Matrix.setIdentityM(mModelMatrix, 0);
        Matrix.translateM(mModelMatrix, 0, -4.0f, 0.0f, -7.0f);
        Matrix.rotateM(mModelMatrix, 0, angleInDegrees, 0.0f, 1.0f, 0.0f);
        drawCube();

        // top
        Matrix.setIdentityM(mModelMatrix, 0);
        Matrix.translateM(mModelMatrix, 0, 0.0f, 4.0f, -7.0f);
        Matrix.rotateM(mModelMatrix, 0, angleInDegrees, 0.0f, 0.0f, 1.0f);
        drawCube();

        // bottom
        Matrix.setIdentityM(mModelMatrix, 0);
        Matrix.translateM(mModelMatrix, 0, 0.0f, -4.0f, -7.0f);
        Matrix.rotateM(mModelMatrix, 0, angleInDegrees, 0.0f, 1.0f, 0.0f);
        drawCube();

        // center
        Matrix.setIdentityM(mModelMatrix, 0);
        Matrix.translateM(mModelMatrix, 0, 0.0f, 0.0f, -5.0f);
        Matrix.rotateM(mModelMatrix, 0, angleInDegrees, 1.0f, 1.0f, 1.0f);
        drawCube();
    }

    /**
     * Draws a cube.
     */
    private void drawCube() {
        // Pass in the position information.
        mCubePositions.position(0);
        GLES20.glVertexAttribPointer(
                mPositionHandle,
                mPositionDataSize,
                GLES20.GL_FLOAT,
                false,
                0,
                mCubePositions
        );
        GLES20.glEnableVertexAttribArray(mPositionHandle);

        // Pass in the color information
        mCubeColors.position(0);
        GLES20.glVertexAttribPointer(
                mColorHandle,
                mColorDataSize,
                GLES20.GL_FLOAT,
                false,
                0, mCubeColors
        );
        GLES20.glEnableVertexAttribArray(mColorHandle);

        // This multiplies the view matrix by the model matrix
        // and stores the result the MVP matrix.
        // which currently contains model * view.
        Matrix.multiplyMM(mMVPMatrix, 0, mViewMatrix, 0, mModelMatrix, 0);

        // This multiplies the model view matrix by the projection matrix,
        // and stores the result in the MVP matrix.
        // which now contains model * view * projection.
        Matrix.multiplyMM(mMVPMatrix, 0, mProjectionMatrix, 0, mMVPMatrix, 0);

        // Pass in the combined matrix
        GLES20.glUniformMatrix4fv(mMVPMatrixHandle, 1, false, mMVPMatrix, 0);

        // Draw the cube.
        GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, 36);
    }
}
