package com.bzh.gl.lesson7;

interface Action {
    void setDelta(float deltaX, float deltaY);
    void decreaseCubeCount();
    void increaseCubeCount();
    void toggleVBOs();
    void toggleStride();
}
