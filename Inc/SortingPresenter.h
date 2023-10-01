#ifndef SORTINGPRESENTER_H_INCLUDED
#define SORTINGPRESENTER_H_INCLUDED

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
#include<random>
#include<ctime>

#include "Render/Shader.h"
#include "Render/Camera.h"
#include "Render/Texture.h"
#include "Render/ShaderPipeline.h"
#include "Render/RenderEngine.h"

#include "SortingProvider.h"
#include "SingularAlgorithmPresenter.h"

struct sortinDataPoint{

    double value;
    bool updating;
};

class AlgorithmVisualPresenter;

class SortingPresenter : public SingularAlgorithmPresenter
{

private:

    RenderEngine* renderEngine;
    SortingProvider* theSortProvider;

    int usedSort = 0;
    std::vector<double> theOriginalActiveData;
    std::vector<bool> theOriginalActiveDataUpdates;
    std::vector<std::vector<int>> theActiveDataProgression;

    int sortProgression  = 0;

    //2D additions
    int twoDUpdateState = 0;

    //3D additions
    float movementSpeed = 30;
    int lineObjectAmount = 10;
    std::vector<glm::vec3> originalPositionData3D;
    std::vector<glm::vec3> positionData3D;
    std::vector<glm::vec3> newPositionData3D;
    std::vector<glm::vec4> colorsFor3D;
    bool updating3DPositions = false;
    float platformSize = 100.0f;
    float platformHeight = 1.0f;
    float blockSize = 1.0f;
    int blockInLine = 20;

    glm::mat4 perspectiveProjectionMatrix;
    glm::vec3 blockPos = glm::vec3(0.0);
    glm::vec3 moveDir = glm::vec3(0.0);

    void update2D();
    void update3D();

public:
    SortingPresenter(RenderEngine*, AlgorithmVisualPresenter*);
    ~SortingPresenter();

    void reset();
    void resetPositions();
    void update();

    void render2D();

    void render3DTest();
    void render3D();

    void changeTypeForward();

    void changeTypeBackward();

    SortingProvider* getProvider();

    void setData(float);
    int getDataSize();

};

#endif // SORTINGPRESENTER_H_INCLUDED
