#ifndef NOISEPRESENTER_H_INCLUDED
#define NOISEPRESENTER_H_INCLUDED

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

#include "Render/RenderEngine.h"
#include "NoiseProvider.h"
#include "SingularAlgorithmPresenter.h"

class AlgorithmVisualPresenter;

class NoisePresenter : public SingularAlgorithmPresenter
{

private:

    NoiseProvider* theNoiseProvider;

    int usedNoise = 0;
    std::vector<std::vector<double>> randomNoise;
    std::vector<std::vector<double>> noiseHeightMap;

    int maxOctaves = 10;
    int minOctaves = 1;
    int maxAmplitude = 100;
    int minAmplitude = 5;
    int maxSmoothness = 300;
    int minSmoothness = 20;
    int maxHeightOffset = 50;
    int minHeightOffset = -50;
    double maxRoughness = 1.0f;
    double minRoughness = 0.02f;

    //3D variable
    float blockSize = 1.0f;

    void update2D();
    void update3D();

public:
    NoisePresenter(RenderEngine*, AlgorithmVisualPresenter*);
    ~NoisePresenter();

    std::vector<std::vector<double>>& getData();

    void reset();
    void update();

    void render2D();

    void render3DTest();
    void render3D();

    int getUsedNoise(int);
    int getUsedNoise();

    void changeTypeForward();

    void changeTypeBackward();

    NoiseProvider* getProvider();

    void incrementOctaves();
    void incrementAmplitude();
    void incrementSmoothness();
    void incrementHeightOffset();
    void incrementRoughness();

    void decrementOctaves();
    void decrementAmplitude();
    void decrementSmoothness();
    void decrementHeightOffset();
    void decrementRoughness();

};

#endif // NOISEPRESENTER_H_INCLUDED
