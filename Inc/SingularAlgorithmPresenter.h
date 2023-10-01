#ifndef SINGULARALGORITHMPRESENTER_H_INCLUDED
#define SINGULARALGORITHMPRESENTER_H_INCLUDED

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
#include <Render/Texture.h>
#include <Render/ShaderPipeline.h>
#include <Render/RenderEngine.h>

class AlgorithmVisualPresenter;

class SingularAlgorithmPresenter
{

protected:

    AlgorithmVisualPresenter* algorithmPresenter;
    RenderEngine* renderEngine;

    float counterValue = 0.0;

    float updateValue = 2;

    bool updateRequired = false;

    bool shouldPresent = false;

    virtual void update2D() = 0;
    virtual void update3D() = 0;

public:
    SingularAlgorithmPresenter(RenderEngine*, AlgorithmVisualPresenter*);
    ~SingularAlgorithmPresenter();

    float getUpdateCounter();

    void setPresentation(bool);
    void setUpdateCounter(float);

    void updateCounter();

    virtual void update() = 0;

    virtual void render2D() = 0;

    virtual void render3DTest() = 0;
    virtual void render3D() = 0;

    void render();

    void run();

};

#endif // SINGULARALGORITHMPRESENTER_H_INCLUDED
