#ifndef ALGORITHMVISUALPRESENTER_H_INCLUDED
#define ALGORITHMVISUALPRESENTER_H_INCLUDED

#include<glad/glad.h>
#include<GLFW/glfw3.h>


#include<ft2build.h>
#include FT_FREETYPE_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<cmath>

#include<iostream>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include<map>
#include<tuple>

#include <Render/Shader.h>
#include <Render/Camera.h>
#include <Render/Viewer3D.h>
#include <Render/Texture.h>
#include <Render/ShaderPipeline.h>
#include <Render/RenderEngine.h>

#include "App/AppEngine.h"
#include "SortingPresenter.h"
#include "NoisePresenter.h"

enum algorithmType
{
    SORTING,
    NOISE
};

enum dimensionMode
{
    TWOD,
    THREED
};

class AlgorithmVisualPresenter
{

private:

    float screenWidth;
    float screenHeight;

    RenderEngine* renderEngine;
    AppEngine* appEngine;

    Viewer3D* the3DViewer; //camera for 3D view

    InterfaceActionScreen* usedWidget;

    unsigned int theRBO;
    unsigned int theFBO;
    unsigned int FBOTexture;

    float mouseX = 0;
    float mouseY = 0;
    float lastMouseX = 0;
    float lastMouseY = 0;
    float mouseOffSetX = 0;
    float mouseOffSetY = 0;

    bool isActive;
    bool isUsed;

    bool firstActivate;

    float viewRadius;

    SortingPresenter* theSortPresenter;
    NoisePresenter* theNoisePresenter;

    std::vector<std::vector<int>> sortingValues;
    std::vector<int> currentSortingValues;

    std::vector<std::vector<double>> noiseHeightMap;

    algorithmType mode;
    dimensionMode dimension;

    void inputUpdate();
    void activeUpdate();
    void update3DView();

public:

    AlgorithmVisualPresenter(RenderEngine*, AppEngine*, InterfaceActionScreen*);

    ~AlgorithmVisualPresenter();

    void setupFramebuffer();

    void setupSortCamera();
    void setupNoiseCamera();
    Viewer3D* getViewer();

    void checkApp();

    void reset();

    void update();

    void run();

    AppEngine* getApp();

    unsigned int getFBO();

    unsigned int getFBOTexture();

    float getWidth();

    float getHeight();

    void setWidth(float);

    void setHeight(float);

    float getRelativeMouseX();

    float getRelativeMouseY();

    int getMouseX();

    int getMouseY();

    algorithmType getMode();

    void setMode(algorithmType);

    void shiftAlgorithm();

    void shiftAlgorithmType();

    dimensionMode getDimension();

    void setDimension(dimensionMode);

    void changeTypeForward();

    void changeTypeBackward();

    SortingPresenter* getSortingPresenter();

    NoisePresenter* getNoisePresenter();

    std::string getAlgorithmName();
};

#endif // ALGORITHMVISUALPRESENTER_H_INCLUDED
