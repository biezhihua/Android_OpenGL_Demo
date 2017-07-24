#include "../graphics/common.cpp"
#include "Native1Lesson.h"
#include <android/log.h>
#include <jni.h>

#define  LOG_TAG    "lesson1"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C" {

JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson1_NativeOneJniLib_onSurfaceCreate(JNIEnv *env, jclass type);

JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson1_NativeOneJniLib_onSurfaceChange(JNIEnv *env, jclass type, jint width,
                                                        jint height);

JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson1_NativeOneJniLib_onDrawFrame(JNIEnv *env, jclass type);

}

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s \n", name, v);
}

static void checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

auto gVertexShader =
        "uniform mat4 u_MVPMatrix;        \n"     // A constant representing the combined model/view/projection matrix.
                "attribute vec4 a_Position;     \n"     // Per-vertex position information we will pass in.
                "attribute vec4 a_Color;        \n"     // Per-vertex color information we will pass in.
                "varying vec4 v_Color;          \n"     // This will be passed into the fragment shader.
                "void main()                    \n"     // The entry point for our vertex shader.
                "{                              \n"
                "   v_Color = a_Color;          \n"     // Pass the color through to the fragment shader.
                "   gl_Position = u_MVPMatrix * a_Position; \n"     // gl_Position is a special variable used to store the final position.
                "}                              \n";    // normalized screen coordinates.


auto gFragmentShader = "precision mediump float;         \n"     // Set the default precision to medium. We don't need as high of a
        "varying vec4 v_Color;          \n"     // This is the color from the vertex shader interpolated across the
        "void main()                    \n"     // The entry point for our fragment shader.
        "{                              \n"
        "   gl_FragColor = v_Color;     \n"     // Pass the color directly through the pipeline.
        "}                              \n";


GLuint loadShader(GLenum shaderType, const char *pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char *buf = (char *) malloc((size_t) infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                         shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}


GLuint createProgram(const char *pVertexSource, const char *pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char *buf = (char *) malloc((size_t) bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLfloat gViewMatrix[16] = {0};
GLfloat gModelMatrix[16] = {0};
GLfloat gProjectionMatrix[16] = {0};
GLfloat gMVPMatrix[16] = {0};

GLfloat gTriangleVerticesData[] = {
        // X, Y, Z,
        -0.5f, -0.25f, 0.0f,

        // X, Y, Z,
        0.5f, -0.25f, 0.0f,

        // X, Y, Z,
        0.0f, 0.5f, 0.0f,
};

GLfloat gTriangleColorData[] = {
        // R, G, B, A
        1.0f, 0.0f, 0.0f, 1.0f,

        // R, G, B, A
        0.0f, 0.0f, 1.0f, 1.0f,

        // R, G, B, A
        0.0f, 1.0f, 0.0f, 1.0f
};

GLuint gProgram;
GLint gMVPMatrixHandle;
GLint gPositionHandle;
GLint gColorHandle;

void native_one_on_surface_create() {
    // Print some OpenGL info.
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGD("on_surface_create");

    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        LOGE("Could not create program");
        return;
    }

    // Set program handles
    // These will later be used to pass in values to the program.
    gMVPMatrixHandle = glGetUniformLocation(gProgram, "u_MVPMatrix");
    gPositionHandle = glGetAttribLocation(gProgram, "a_Position");
    gColorHandle = glGetAttribLocation(gProgram, "a_Color");

    // Position the eye behind the origin.
    GLfloat eyeX = 0.0F;
    GLfloat eyeY = 0.0F;
    GLfloat eyeZ = 1.5F;

    // We are looking toward the distance.
    GLfloat lookX = 0.0F;
    GLfloat lookY = 0.0F;
    GLfloat lookZ = -5.0F;

    // Set out up vector.
    // This is where our head would be pointing were we holding
    // the camera.
    GLfloat upX = 0.0F;
    GLfloat upY = 1.0F;
    GLfloat upZ = 0.0F;

    // Set the view matrix;
    matrixSetIdentityM(gViewMatrix);
    matrixLookAtM(gViewMatrix, eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);
}

void native_one_on_surface_change(int width, int height) {
    LOGD("on_surface_change");

    // Set the OpenGL viewport to the same size as the surface.
    glViewport(0, 0, width, height);

    // Create a new perspective projection matrix.
    // while the width will vary as per aspect ratio.
    GLfloat ratio = (float) width / height;
    GLfloat left = -ratio;
    GLfloat right = ratio;
    GLfloat bottom = -1.0f;
    GLfloat top = 1.0f;
    GLfloat near = 1.0f;
    GLfloat far = 2.0f;

    matrixFrustumM(gProjectionMatrix, left, right, bottom, top, near, far);
}

void native_one_on_draw_frame() {
    glClearColor(0.5F, 0.5F, 0.5F, 0.5F);
    glClear(GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");
    LOGD("on_draw_frame");

    // Tell OpenGL to use this program when rendering.
    glUseProgram(gProgram);

    matrixSetIdentityM(gModelMatrix);
    // rotateM(gModelMatrix, 0, 0.0f, 0.0f, 1.0f);

    glVertexAttribPointer(
            (GLuint) gPositionHandle,
            3,
            GL_FLOAT,
            GL_FALSE,
            4 * 7,
            gTriangleVerticesData
    );
    glEnableVertexAttribArray((GLuint) gPositionHandle);

    glVertexAttribPointer(
            (GLuint) gColorHandle,
            4,
            GL_FLOAT,
            GL_FALSE,
            4 * 7,
            gTriangleColorData
    );
    glEnableVertexAttribArray((GLuint) gColorHandle);

    // model * view
    matrixMultiplyMM(gMVPMatrix, gViewMatrix, gModelMatrix);

    // model * view * projection
    matrixMultiplyMM(gMVPMatrix, gProjectionMatrix, gMVPMatrix);

    glUniformMatrix4fv(gMVPMatrixHandle, 1, GL_FALSE, gMVPMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    checkGlError("glDrawArrays");

}

Native1Lesson *lesson = NULL;

JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson1_NativeOneJniLib_onSurfaceCreate(JNIEnv *env, jclass type) {
//    native_one_on_surface_create();

    lesson = new Native1Lesson();
    lesson->create();
}

JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson1_NativeOneJniLib_onSurfaceChange(JNIEnv *env, jclass type, jint width,
                                                        jint height) {

//    native_one_on_surface_change(width, height);
    if (lesson) {
        lesson->change(width, height);
    }
}

JNIEXPORT void JNICALL
Java_com_bzh_gl_lesson1_NativeOneJniLib_onDrawFrame(JNIEnv *env, jclass type) {
//    native_one_on_draw_frame();
    if (lesson) {
        lesson->draw();
    }
}