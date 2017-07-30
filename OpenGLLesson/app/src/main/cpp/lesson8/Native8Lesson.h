#ifndef OPENGLLESSON_NATIVE8LESSON_H
#define OPENGLLESSON_NATIVE8LESSON_H

#include <graphics/Matrix.h>
#include <GLES2/gl2.h>
#include <string>
#include "HeightMap.h"

using namespace std;

class Native8Lesson {

public :


    Native8Lesson();

    ~Native8Lesson();

    void create();

    void change(int width, int height);

    void draw();

    void setDelta(float x, float y);

private:

    /**
    * Identifiers for our uniforms and attributes inside the shaders.
    */
    static const string MVP_MATRIX_UNIFORM = "u_MVPMatrix";
    static const string MV_MATRIX_UNIFORM = "u_MVMatrix";
    static const string LIGHT_POSITION_UNIFORM = "u_LightPos";

    static const string POSITION_ATTRIBUTE = "a_Position";
    static const string NORMAL_ATTRIBUTE = "a_Normal";
    static const string COLOR_ATTRIBUTE = "a_Color";

    /**
     * Additional constants.
     */
    static const int POSITION_DATA_SIZE_IN_ELEMENTS = 3;
    static const int NORMAL_DATA_SIZE_IN_ELEMENTS = 3;
    static const int COLOR_DATA_SIZE_IN_ELEMENTS = 4;

    static const int BYTES_PER_FLOAT = 4;
    static const int BYTES_PER_SHORT = 2;

    static const int STRIDE = (POSITION_DATA_SIZE_IN_ELEMENTS + NORMAL_DATA_SIZE_IN_ELEMENTS +
                               COLOR_DATA_SIZE_IN_ELEMENTS) * BYTES_PER_FLOAT;

    /**
     * Used to hold a light centered on the origin in model space.
     * We need a 4th coordinate so we can get translations to
     * work when we multiply this by our transformation matrices.
     */
    float lightPosInModelSpace[] = {0.0f, 0.0f, 0.0f, 1.0f};

    /**
     * Used to hold the current position of the light in world space
     * (after transformation via model matrix).
     */
    float lightPosInWorldSpace[] = {0.0f, 0.0f, 0.0f, 0.0f};

    /**
     * Used to hold the transformed position of the light in eye space
     * (after transformation via modelview matrix).
     */
    float lightPosInEyeSpace[] = {0.0f, 0.0f, 0.0f, 0.0f};

    /**
     * Store the model matrix.
     * This matrix is used to move models from
     * object space (where each model can be tought of
     * being located at the center of the universe)
     * to world space.
     */
    Matrix *modelMatrix;

    /**
     * Store the view matrix.
     * This can be tought of as our camera.
     * This matrix transforms world space to eye space.
     * it positions things relative to our eye.
     */
    Matrix *viewMatrix;

    /**
     * Store the projection matrix.
     * This is used to projet the scene onto a 2D viewport.
     */
    Matrix *projectionMatrix;

    /**
     * Allocate storage for the final combined matrix.
     * This will be passed into the shader program.
     */
    Matrix *mvpMatrix;

    Matrix *accumulatedRotation;
    Matrix *currentRotaion;
    Matrix *lightModelMatrix;

    /**
     * OpenGL handles to our program uniforms
     */
    GLint mvpMatrixUniform;
    GLint mvMatrixUniform;
    GLint lightPosUniform;

    /**
     * OpenGL handles to our program attributes.
     */
    GLint posotionAttribute;
    GLint normalAttribute;
    GLint colorAttribute;

    /**
     * This is a handle to our cube shading program.
     */
    GLuint program;

    /**
     * Retaion the most recent delta for touch events.
     */
    volatile float deltaX;
    volatile float deltaY;


    /**
     * The current heightmap object.
     */
    HeightMap *heightMap;
};

#endif //OPENGLLESSON_NATIVE8LESSON_H
