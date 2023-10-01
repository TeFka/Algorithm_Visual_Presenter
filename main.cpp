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

#include "Render/Shader.h"
#include "Render/Camera.h"
#include "Render/Texture.h"

#include "Render/RenderEngine.h"
#include "Interface/InterfaceWidget.h"
#include "Interface/InterfaceLayout.h"
#include "Interface/InterfaceBox.h"
#include "Interface/InterfaceScreen.h"
#include "Interface/InterfaceButton.h"
#include "App/AppEngine.h"

#include "helpers/RootDir.h"

#include "AlgorithmVisualPresenter.h"
#include "AlgorithmVisualPresenterScreen.h"

//retasdf


int main(){
    std::string rootDir = ROOT_DIR;
    std::string shaderDir = "Resources/shaders/";
     //setting up render engine
    RenderEngine renderEngine("AlgorithmVisuals",
                              1200, 800,
                              4, 4,
                              ROOT_DIR+shaderDir);

    renderEngine.setDefaultShaderUniforms();
    std::cout<<"setup0"<<std::endl;
    std::string textFont = "arial";
    renderEngine.getTextManager()->setTextType(textFont);
    std::cout<<"setup01"<<std::endl;
    std::string textureDir = "Resources/images/";
    std::string textureNames[1] = {"algo.jpg"};
    renderEngine.getShaderProgram(renderEngine.SKYBOX_SHADER, true)->setTexture((ROOT_DIR+textureDir+textureNames[0]).c_str(), 1, 1);
    std::cout<<"setup02"<<std::endl;
    std::vector<std::string> skyboxTextures;
    skyboxTextures.push_back((ROOT_DIR+textureDir+textureNames[0]).c_str());
    skyboxTextures.push_back((ROOT_DIR+textureDir+textureNames[0]).c_str());
    skyboxTextures.push_back((ROOT_DIR+textureDir+textureNames[0]).c_str());
    skyboxTextures.push_back((ROOT_DIR+textureDir+textureNames[0]).c_str());
    skyboxTextures.push_back((ROOT_DIR+textureDir+textureNames[0]).c_str());
    skyboxTextures.push_back((ROOT_DIR+textureDir+textureNames[0]).c_str());
    renderEngine.setupSkyBoxTexture(skyboxTextures);
    std::cout<<"setup1"<<std::endl;
    //setting up interface engine

    InterfaceEngine theInterfaceEngine(&renderEngine);

    AlgorithmVisualPresenterScreen theAlgorithmScreen("Simulator", &theInterfaceEngine, &renderEngine, 1);

    InterfaceLayout mainLayout1(&renderEngine, 1, VERTICAL);
    theAlgorithmScreen.addChildWidget(&mainLayout1);

    InterfaceBox box1(&renderEngine, 2, "Algorithm Presenter", glm::vec4(0.2,0.2,0.2,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f, false,1.0f,0.1f);
    std::cout<<"setup2"<<std::endl;
    mainLayout1.addWidget(&box1);
    std::cout<<"setup3"<<std::endl;
    InterfaceLayout tripleLayout1(&renderEngine, 3, HORIZONTAL, false,0.9f,0.1f);
    mainLayout1.addWidget(&tripleLayout1);

    InterfaceButton button11(&renderEngine, &theInterfaceEngine, 31, "New Data", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    tripleLayout1.addWidget(&button11);

    InterfaceButton button12(&renderEngine, &theInterfaceEngine, 4, "Reset", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    tripleLayout1.addWidget(&button12);

    InterfaceButton button13(&renderEngine, &theInterfaceEngine, 5, "Sort", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    tripleLayout1.addWidget(&button13);

    InterfaceButton button14(&renderEngine, &theInterfaceEngine, 6, "Noise", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    tripleLayout1.addWidget(&button14);
    std::cout<<"setup4"<<std::endl;

    InterfaceLayout tripleLayout2(&renderEngine, 7, HORIZONTAL, false,1.0f,0.1f);
    mainLayout1.addWidget(&tripleLayout2);

    InterfaceBox dimensionLabel(&renderEngine, 8, "Dimension: 2D", glm::vec4(0.3,0.3,0.3,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    tripleLayout2.addWidget(&dimensionLabel);

    InterfaceButton button21(&renderEngine, &theInterfaceEngine, 9, "2D", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    tripleLayout2.addWidget(&button21);

    InterfaceButton button22(&renderEngine, &theInterfaceEngine, 10, "3D", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    tripleLayout2.addWidget(&button22);
    std::cout<<"setup5"<<std::endl;

    InterfaceLayout operationLayout(&renderEngine, 11);
    mainLayout1.addWidget(&operationLayout);

    InterfaceActionScreen canvas1(&renderEngine, 12);
    operationLayout.addWidget(&canvas1);
    std::cout<<"setup6"<<std::endl;

    //sort tools
    InterfaceLayout sortToolsLayout1(&renderEngine, 17, VERTICAL, false,0.2f,1.0f);
    operationLayout.addWidget(&sortToolsLayout1);

    //period update
    InterfaceLayout sortPeriodUpdateLayout1(&renderEngine, 18, HORIZONTAL);
    sortToolsLayout1.addWidget(&sortPeriodUpdateLayout1);

    InterfaceButton buttonSP1(&renderEngine, &theInterfaceEngine, 19, "-", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    sortPeriodUpdateLayout1.addWidget(&buttonSP1);

    InterfaceBox nameLabelSP1(&renderEngine, 20, "Update Period: 2s", glm::vec4(0.3,0.3,0.3,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    sortPeriodUpdateLayout1.addWidget(&nameLabelSP1);

    InterfaceButton buttonSP2(&renderEngine, &theInterfaceEngine, 21, "+", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    sortPeriodUpdateLayout1.addWidget(&buttonSP2);

    //data amount update
    InterfaceLayout sortDataUpdateLayout1(&renderEngine, 22, HORIZONTAL);
    sortToolsLayout1.addWidget(&sortDataUpdateLayout1);

    InterfaceButton buttonSD1(&renderEngine, &theInterfaceEngine, 23, "-", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    sortDataUpdateLayout1.addWidget(&buttonSD1);

    InterfaceBox nameLabelSD1(&renderEngine, 24, "Data Points: 10", glm::vec4(0.3,0.3,0.3,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    sortDataUpdateLayout1.addWidget(&nameLabelSD1);

    InterfaceButton buttonSD2(&renderEngine, &theInterfaceEngine, 25, "+", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    sortDataUpdateLayout1.addWidget(&buttonSD2);

    //noise tools
    InterfaceLayout noiseToolsLayout1(&renderEngine, 26, VERTICAL, false,0.2f,1.0f);
    noiseToolsLayout1.disable();
    operationLayout.addWidget(&noiseToolsLayout1);

    //Octaves
    InterfaceLayout noiseOctavesLayout1(&renderEngine, 31, HORIZONTAL);
    noiseToolsLayout1.addWidget(&noiseOctavesLayout1);

    InterfaceButton buttonNO1(&renderEngine, &theInterfaceEngine, 32, "-", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    noiseOctavesLayout1.addWidget(&buttonNO1);

    InterfaceBox nameLabelNO1(&renderEngine, 33, "Octaves: 7", glm::vec4(0.3,0.3,0.3,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    noiseOctavesLayout1.addWidget(&nameLabelNO1);

    InterfaceButton buttonNO2(&renderEngine, &theInterfaceEngine, 34, "+", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    noiseOctavesLayout1.addWidget(&buttonNO2);

    //Smoothness
    InterfaceLayout noiseSmoothnessLayout1(&renderEngine, 30, HORIZONTAL);
    noiseToolsLayout1.addWidget(&noiseSmoothnessLayout1);

    InterfaceButton buttonNS1(&renderEngine, &theInterfaceEngine, 27, "-", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    noiseSmoothnessLayout1.addWidget(&buttonNS1);

    InterfaceBox nameLabelNS1(&renderEngine, 28, "Smoothness: 235", glm::vec4(0.3,0.3,0.3,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    noiseSmoothnessLayout1.addWidget(&nameLabelNS1);

    InterfaceButton buttonNS2(&renderEngine, &theInterfaceEngine, 29, "+", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    noiseSmoothnessLayout1.addWidget(&buttonNS2);

    //Amplitude
    InterfaceLayout noiseAmplitudeLayout1(&renderEngine, 35, HORIZONTAL);
    noiseToolsLayout1.addWidget(&noiseAmplitudeLayout1);

    InterfaceButton buttonNA1(&renderEngine, &theInterfaceEngine, 36, "-", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    noiseAmplitudeLayout1.addWidget(&buttonNA1);

    InterfaceBox nameLabelNA1(&renderEngine, 37, "Amplitude: 70", glm::vec4(0.3,0.3,0.3,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    noiseAmplitudeLayout1.addWidget(&nameLabelNA1);

    InterfaceButton buttonNA2(&renderEngine, &theInterfaceEngine, 38, "+", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    noiseAmplitudeLayout1.addWidget(&buttonNA2);

    //Height Offset
    InterfaceLayout noiseHeightOffsetLayout1(&renderEngine, 39, HORIZONTAL);
    noiseToolsLayout1.addWidget(&noiseHeightOffsetLayout1);

    InterfaceButton buttonNHO1(&renderEngine, &theInterfaceEngine, 40, "-", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    noiseHeightOffsetLayout1.addWidget(&buttonNHO1);

    InterfaceBox nameLabelNHO1(&renderEngine, 41, "Height Offset: -5", glm::vec4(0.3,0.3,0.3,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    noiseHeightOffsetLayout1.addWidget(&nameLabelNHO1);

    InterfaceButton buttonNHO2(&renderEngine, &theInterfaceEngine, 42, "+", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    noiseHeightOffsetLayout1.addWidget(&buttonNHO2);

    //Roughness
    InterfaceLayout noiseRoughnessLayout1(&renderEngine, 43, HORIZONTAL);
    noiseToolsLayout1.addWidget(&noiseRoughnessLayout1);

    InterfaceButton buttonNR1(&renderEngine, &theInterfaceEngine, 44, "-", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    noiseRoughnessLayout1.addWidget(&buttonNR1);

    InterfaceBox nameLabelNR1(&renderEngine, 45, "Roughness: 0.53", glm::vec4(0.3,0.3,0.3,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    noiseRoughnessLayout1.addWidget(&nameLabelNR1);

    InterfaceButton buttonNR2(&renderEngine, &theInterfaceEngine, 46, "+", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    noiseRoughnessLayout1.addWidget(&buttonNR2);

    //general tools layout
    InterfaceLayout toolsLayout2(&renderEngine, 13, VERTICAL, false,0.2f,1.0f);
    operationLayout.addWidget(&toolsLayout2);

    InterfaceButton buttonZ1(&renderEngine, &theInterfaceEngine, 14, ">>>", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    toolsLayout2.addWidget(&buttonZ1);

    InterfaceBox algorithmNameLabel(&renderEngine, 15, "Selection Sort", glm::vec4(0.3,0.3,0.3,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    toolsLayout2.addWidget(&algorithmNameLabel);

    InterfaceButton buttonZ2(&renderEngine, &theInterfaceEngine, 16, "<<<", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    toolsLayout2.addWidget(&buttonZ2);
    std::cout<<"setup7"<<std::endl;

    std::cout<<"setup8"<<std::endl;

    theInterfaceEngine.addScreen(&theAlgorithmScreen);
    std::cout<<"setup9"<<std::endl;
    //menu scree
    //DefaultInterfaceScreen menuScreen = DefaultInterfaceScreen("MainMenu", &theInterfaceEngine);

    //theInterfaceEngine.addScreen(&menuScreen);

    //stuff screen
    //DefaultInterfaceScreen stuffScreen = DefaultInterfaceScreen("Stuff", &theInterfaceEngine);

    //the app
    AppEngine theApp(&renderEngine, &theInterfaceEngine);

    //interface engine setup
    theInterfaceEngine.setApp(&theApp);
    std::cout<<"setup10"<<std::endl;
    //additional functions/programs
    AlgorithmVisualPresenter theVisualPresenter(&renderEngine, &theApp, &canvas1);
    theVisualPresenter.setMode(SORTING);
    theVisualPresenter.setDimension(TWOD);
    std::cout<<"setup11"<<std::endl;
    //additional setup
    theVisualPresenter.setWidth(canvas1.getRealWidth());
    theVisualPresenter.setHeight(canvas1.getRealHeight());
    theVisualPresenter.setupFramebuffer();

    canvas1.setTexture(theVisualPresenter.getFBOTexture(), 0);

    theAlgorithmScreen.setPresenter(&theVisualPresenter);
    std::cout<<"setup done"<<std::endl;
    //app structure
    while(!glfwWindowShouldClose(renderEngine.getWindow()))
    {

        theVisualPresenter.run();
        theApp.run();

    }

    theApp.endApp();

    return 0;
}


