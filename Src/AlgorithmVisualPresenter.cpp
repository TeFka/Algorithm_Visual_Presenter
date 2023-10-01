
#include "../Inc/AlgorithmVisualPresenter.h"

AlgorithmVisualPresenter::AlgorithmVisualPresenter(RenderEngine* engine, AppEngine* theApp, InterfaceActionScreen* widget)
{
    this->renderEngine = engine;
    this->the3DViewer = new Viewer3D();
    this->appEngine = theApp;
    this->usedWidget = widget;
    this->theSortPresenter = new SortingPresenter(this->renderEngine, this);
    this->theNoisePresenter = new NoisePresenter(this->renderEngine, this);
    this->mode = SORTING;
    this->setupSortCamera();
    this->dimension = TWOD;
}

AlgorithmVisualPresenter::~AlgorithmVisualPresenter()
{



}

void AlgorithmVisualPresenter::setupFramebuffer()
{
    //rbo
    glGenRenderbuffers(1,&this->theRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, this->theRBO);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,this->screenWidth,this->screenHeight);
    glBindRenderbuffer(GL_RENDERBUFFER,0);

    //FBOs
    glGenFramebuffers(1,&this->theFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, this->theFBO);
    //texture
    glGenTextures(1, &this->FBOTexture);
    glBindTexture(GL_TEXTURE_2D,this->FBOTexture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA16F,this->screenWidth,this->screenHeight,0,GL_RGBA,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,this->FBOTexture,0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,this->theRBO);
    unsigned int attachment = GL_COLOR_ATTACHMENT0;
    glDrawBuffers(1, &attachment);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout<<"ERROR:FRAMEBUFFER1:Framebuffer is not complete!"<<std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void AlgorithmVisualPresenter::setupSortCamera()
{

    this->the3DViewer->getCamera()->setPosition(glm::vec3(13.0f, 0.0f, 30.0f));

    this->the3DViewer->getCamera()->setFront(glm::vec3(0.0, 0.0f, -1.0f));

}

void AlgorithmVisualPresenter::setupNoiseCamera()
{

    this->the3DViewer->getCamera()->setPosition(glm::vec3(100.0f, -50.0f, 100.0f));

    this->the3DViewer->getCamera()->setFront(glm::vec3(-1.0));

}

Viewer3D* AlgorithmVisualPresenter::getViewer()
{

    return this->the3DViewer;
}

void AlgorithmVisualPresenter::inputUpdate()
{

    if(glfwGetMouseButton(this->renderEngine->getWindow(),GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
    {
        if(!this->firstActivate)
        {
            this->isActive = true;

            if(this->dimension==TWOD)
            {

                //this->theActiveSchematic->checkMouse(true);

            }
            else if(this->dimension==THREED)
            {
                glfwSetInputMode(this->renderEngine->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                this->appEngine->lockActiveWidget(true);

            }
        }
        if(this->isActive){



        }
    }

    if(glfwGetMouseButton(this->renderEngine->getWindow(),GLFW_MOUSE_BUTTON_LEFT)==GLFW_RELEASE)
    {

        this->isUsed = false;
        glfwSetInputMode(this->renderEngine->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        if(this->dimension==TWOD)
        {

            //this->theActiveSchematic->checkMouse(false);

        }
        else if(this->dimension==THREED)
        {
            this->appEngine->lockActiveWidget(false);
            //this->theActiveSchematic->checkMouse(false);

        }

        if(this->firstActivate)
        {
            this->firstActivate = false;
        }

    }

    if(glfwGetKey(this->renderEngine->getWindow(), GLFW_KEY_D)==GLFW_PRESS){

        this->the3DViewer->getCamera()->setPosition(this->the3DViewer->getCamera()->getPosition());

    }
}
void AlgorithmVisualPresenter::checkApp()
{

    if(this->appEngine->activeWidgetIsON())
    {

        if(this->appEngine->getActiveWidget()==this->usedWidget)
        {
            std::cout<<this->mouseX<<"  "<<this->mouseY<<std::endl;
            this->lastMouseX = this->mouseX;
            this->lastMouseY = this->mouseY;
            this->mouseX = (this->appEngine->getMouseX()-this->appEngine->getActiveMouseMinX())/this->screenWidth;
            this->mouseY = (this->appEngine->getMouseY()-this->appEngine->getActiveMouseMinY())/this->screenHeight;
            this->activeUpdate();

        }

    }
    else
    {
        this->firstActivate = true;
    }
}

void AlgorithmVisualPresenter::activeUpdate()
{

    this->inputUpdate();

    if(this->dimension==THREED)
    {
        if(this->isUsed){
            this->update3DView();
        }

    }
}

void AlgorithmVisualPresenter::reset()
{

    if(this->mode==SORTING)
    {

        this->theSortPresenter->reset();

    }
    else if(this->mode==NOISE)
    {

        this->theNoisePresenter->reset();

    }

}

void AlgorithmVisualPresenter::update3DView()
{
    float tempMouseX = this->mouseX;
    float tempMouseY = this->mouseY;

    this->mouseX = this->lastMouseX;
    this->mouseY = this->lastMouseY;

    this->mouseOffSetX=tempMouseX-this->lastMouseX;
    this->mouseOffSetY=this->lastMouseY-tempMouseY;
    this->the3DViewer->mouseCommand(this->mouseOffSetX,this->mouseOffSetY);
}


void AlgorithmVisualPresenter::update()
{

    this->checkApp();

}

void AlgorithmVisualPresenter::run()
{

    this->update();
    //std::cout<<"running main algorithm presenter stuff"<<std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER,this->theFBO);

    glClearColor(0.7,.7,0.7,1.0);
    glViewport(0,0,this->screenWidth,this->screenHeight);

    if(this->dimension==THREED)
    {
        //std::cout<<"setting view matrix"<<std::endl;
        //this->renderEngine->getShaderProgram(this->renderEngine->BASIC_3D_SHADER, true)->getShader()->setMat4(this->the3DViewer->getCamera()->getViewMatrix(),"viewMatrix");
        //std::cout<<"done setting view matrix"<<std::endl;
    }

    if(this->mode==SORTING)
    {
        this->theSortPresenter->run();

    }
    else if(this->mode==NOISE)
    {

        this->theNoisePresenter->run();

    }
    this->renderEngine->clearVerts(this->renderEngine->BASIC_2D_SHADER, true);
    //screen top
    if(this->appEngine->activeWidgetIsON() && !this->isUsed)
    {
        this->renderEngine->setBasic2DSprite(glm::vec2(this->mouseX, this->mouseY), glm::vec2(0.01f,0.01f),
                                             glm::vec4(0.0,0.0,1.0,1.0), 15);
    }
    this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->use();

    glBindFramebuffer(GL_FRAMEBUFFER,0);

}

AppEngine* AlgorithmVisualPresenter::getApp()
{

    return this->appEngine;

}

unsigned int AlgorithmVisualPresenter::getFBO()
{

    return this->theFBO;
}

unsigned int AlgorithmVisualPresenter::getFBOTexture()
{

    return this->FBOTexture;
}

float AlgorithmVisualPresenter::getWidth()
{

    return this->screenWidth;

}

float AlgorithmVisualPresenter::getHeight()
{

    return this->screenWidth;

}

void AlgorithmVisualPresenter::setWidth(float newWidth)
{

    this->screenWidth = newWidth;

}

void AlgorithmVisualPresenter::setHeight(float newHeight)
{

    this->screenHeight = newHeight;

}


float AlgorithmVisualPresenter::getRelativeMouseX()
{

    return this->mouseX;

}

float AlgorithmVisualPresenter::getRelativeMouseY()
{

    return this->mouseY;

}

int AlgorithmVisualPresenter::getMouseX()
{

    return this->mouseX*this->screenWidth;

}

int AlgorithmVisualPresenter::getMouseY()
{

    return this->mouseY*this->screenWidth;

}

algorithmType AlgorithmVisualPresenter::getMode()
{

    return this->mode;

}

void AlgorithmVisualPresenter::setMode(algorithmType newMode)
{

    this->mode = newMode;

}

dimensionMode AlgorithmVisualPresenter::getDimension()
{

    return this->dimension;
}

void AlgorithmVisualPresenter::setDimension(dimensionMode newDimension)
{

    this->dimension = newDimension;
}

void AlgorithmVisualPresenter::changeTypeForward()
{

    if(this->mode==SORTING)
    {

        this->theSortPresenter->changeTypeForward();

    }
    else if(this->mode==NOISE)
    {

        this->theNoisePresenter->changeTypeForward();

    }

}

void AlgorithmVisualPresenter::changeTypeBackward()
{

    if(this->mode==SORTING)
    {

        this->theSortPresenter->changeTypeBackward();

    }
    else if(this->mode==NOISE)
    {

        this->theNoisePresenter->changeTypeBackward();

    }

}

SortingPresenter* AlgorithmVisualPresenter::getSortingPresenter()
{

    return this->theSortPresenter;

}

NoisePresenter* AlgorithmVisualPresenter::getNoisePresenter()
{

    return this->theNoisePresenter;

}

std::string AlgorithmVisualPresenter::getAlgorithmName()
{

    if(this->mode==SORTING)
    {

        return this->theSortPresenter->getProvider()->getSortName();

    }
    else if(this->mode==NOISE)
    {

        return this->theNoisePresenter->getProvider()->getNoiseName();

    }
    return "";
}
