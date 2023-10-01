
#include "Interface/InterfaceEngine.h"
#include "App/AppEngine.h"

InterfaceEngine::InterfaceEngine(RenderEngine* engine)
{

    this->renderEngine = engine;

}

InterfaceEngine::~InterfaceEngine(){


}

void InterfaceEngine::addScreen(InterfaceScreen* newScreen){

    this->screens.push_back(newScreen);
    this->screens[this->screens.size()-1]->setup();

}

InterfaceScreen* InterfaceEngine::getActiveScreen(){

    return this->screens[this->currentScreen];

}

void InterfaceEngine::setActiveScreen(int newActive){

    this->currentScreen = newActive;

}

void InterfaceEngine::renderActiveScreen(){
    this->renderEngine->clearVerts(this->renderEngine->BASIC_2D_SHADER, true);
    this->screens[this->currentScreen]->render();
    this->renderEngine->drawBasic2D();
}

void InterfaceEngine::renderActiveScreenText(){

    this->screens[this->currentScreen]->renderText();

}


void InterfaceEngine::addActiveCommandId(int activeId){

    this->screens[this->currentScreen]->addActiveCommandId(activeId);

}

InterfaceWidget* InterfaceEngine::getWidget(int neededId){

    return this->screens[this->currentScreen]->getWidget(neededId);
}

void InterfaceEngine::setApp(AppEngine* newApp){

    this->theApp = newApp;

}

AppEngine* InterfaceEngine::getApp(){

    return this->theApp;
}
