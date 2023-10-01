
#include "AlgorithmVisualPresenterScreen.h"


AlgorithmVisualPresenterScreen::AlgorithmVisualPresenterScreen(std::string name, InterfaceEngine* interface, RenderEngine* engine, int theId)
    : InterfaceScreen(name, interface, theId)
{

    this->renderEngine = engine;

}

AlgorithmVisualPresenterScreen::~AlgorithmVisualPresenterScreen()
{



}

AlgorithmVisualPresenter* AlgorithmVisualPresenterScreen::getPresenter()
{

    return this->theAlgorithmPresenter;
}

void AlgorithmVisualPresenterScreen::setPresenter(AlgorithmVisualPresenter* presenter)
{

    this->theAlgorithmPresenter = presenter;

}

void AlgorithmVisualPresenterScreen::setSortMode(){

    this->theAlgorithmPresenter->setupSortCamera();
    this->getWidget(17)->enable();
    this->getWidget(26)->disable();
    this->getWidget(11)->setMembersParameters();
    this->theAlgorithmPresenter->setMode(SORTING);
    this->renderEngine->setSkyBoxTexture();

}

void AlgorithmVisualPresenterScreen::setNoiseMode(){
    this->theAlgorithmPresenter->setupNoiseCamera();
    this->getWidget(17)->disable();
    this->getWidget(11)->setMembersParameters();
    this->theAlgorithmPresenter->setMode(NOISE);
}

void AlgorithmVisualPresenterScreen::setValueNoiseMode(){
    this->getWidget(26)->disable();
    this->getWidget(11)->setMembersParameters();
}

void AlgorithmVisualPresenterScreen::setPerlinNoiseMode(){
    this->getWidget(26)->enable();
    this->getWidget(11)->setMembersParameters();
}

void AlgorithmVisualPresenterScreen::manageSortChange(){



}

void AlgorithmVisualPresenterScreen::manageNoiseChange(){

    int usedNoise = this->theAlgorithmPresenter->getNoisePresenter()->getUsedNoise();

    if(usedNoise==this->theAlgorithmPresenter->getNoisePresenter()->getProvider()->VALUE_NOISE){

        this->setValueNoiseMode();

    }
    else if(usedNoise==this->theAlgorithmPresenter->getNoisePresenter()->getProvider()->PERLIN_NOISE){

        this->setPerlinNoiseMode();

    }

}

void AlgorithmVisualPresenterScreen::checkForFunctions()
{

    int id = this->interfaceEngine->getActiveScreen()->getLatestActiveId();
    switch(id)
    {
    case 31:
        this->theAlgorithmPresenter->getSortingPresenter()->setData(this->theAlgorithmPresenter->getSortingPresenter()->getDataSize());
        this->theAlgorithmPresenter->reset();
        break;
    case 4:
        this->theAlgorithmPresenter->reset();
        break;
    case 5:
        if(this->theAlgorithmPresenter->getMode() == NOISE){
        this->setSortMode();
        }
        this->getWidget(15)->setText(this->theAlgorithmPresenter->getAlgorithmName());
        break;
    case 6:
        std::cout<<"using noise"<<std::endl;
        if(this->theAlgorithmPresenter->getMode() == SORTING){
        this->setNoiseMode();
        }
        this->getWidget(15)->setText(this->theAlgorithmPresenter->getAlgorithmName());
        break;
    case 9:
        this->theAlgorithmPresenter->setDimension(TWOD);
        this->getWidget(8)->setText("Dimension: 2D");
        this->theAlgorithmPresenter->reset();
        break;
    case 10:
        this->theAlgorithmPresenter->setDimension(THREED);
        this->getWidget(8)->setText("Dimension: 3D");
        this->theAlgorithmPresenter->reset();
        break;
    case 14:
        this->theAlgorithmPresenter->changeTypeForward();
        this->getWidget(15)->setText(this->theAlgorithmPresenter->getAlgorithmName());
        if(this->theAlgorithmPresenter->getMode() == SORTING){

            this->manageSortChange();

        }
        else if(this->theAlgorithmPresenter->getMode() == NOISE){

             this->manageNoiseChange();

        }
        break;
    case 16:
        this->theAlgorithmPresenter->changeTypeBackward();
        this->getWidget(15)->setText(this->theAlgorithmPresenter->getAlgorithmName());

        if(this->theAlgorithmPresenter->getMode() == SORTING){

            this->manageSortChange();

        }
        else if(this->theAlgorithmPresenter->getMode() == NOISE){

             this->manageNoiseChange();

        }

        break;
    case 19:
        this->theAlgorithmPresenter->getSortingPresenter()->setUpdateCounter(this->theAlgorithmPresenter->getSortingPresenter()->getUpdateCounter()*0.5);
        this->getWidget(20)->setText("Update Period: "+std::to_string(this->theAlgorithmPresenter->getSortingPresenter()->getUpdateCounter())+"s");
        break;
    case 21:
        this->theAlgorithmPresenter->getSortingPresenter()->setUpdateCounter(this->theAlgorithmPresenter->getSortingPresenter()->getUpdateCounter()*2);
        this->getWidget(20)->setText("Update Period: "+std::to_string(this->theAlgorithmPresenter->getSortingPresenter()->getUpdateCounter())+"s");
        break;
    case 23:
        if(this->theAlgorithmPresenter->getSortingPresenter()->getDataSize()>3){
            this->theAlgorithmPresenter->getSortingPresenter()->setData(this->theAlgorithmPresenter->getSortingPresenter()->getDataSize()*0.5);
            this->getWidget(24)->setText("Data Points: "+std::to_string(this->theAlgorithmPresenter->getSortingPresenter()->getDataSize()));
            this->theAlgorithmPresenter->reset();
        }
        break;
    case 25:
        if(this->theAlgorithmPresenter->getSortingPresenter()->getDataSize()<1000){
            this->theAlgorithmPresenter->getSortingPresenter()->setData(this->theAlgorithmPresenter->getSortingPresenter()->getDataSize()*2);
            this->getWidget(24)->setText("Data Points: "+std::to_string(this->theAlgorithmPresenter->getSortingPresenter()->getDataSize()));
            this->theAlgorithmPresenter->reset();
        }
        break;
    case 27:
            this->theAlgorithmPresenter->getNoisePresenter()->decrementSmoothness();
            this->getWidget(28)->setText("Smoothness: "+std::to_string(this->theAlgorithmPresenter->getNoisePresenter()->getProvider()->getSmoothness()));
        break;
    case 29:
            this->theAlgorithmPresenter->getNoisePresenter()->incrementSmoothness();
            this->getWidget(28)->setText("Smoothness: "+std::to_string(this->theAlgorithmPresenter->getNoisePresenter()->getProvider()->getSmoothness()));
        break;
    case 32:
            this->theAlgorithmPresenter->getNoisePresenter()->decrementOctaves();
            this->getWidget(33)->setText("Octave: "+std::to_string(this->theAlgorithmPresenter->getNoisePresenter()->getProvider()->getOctaves()));
        break;
    case 34:
            this->theAlgorithmPresenter->getNoisePresenter()->incrementOctaves();
            this->getWidget(33)->setText("Octave: "+std::to_string(this->theAlgorithmPresenter->getNoisePresenter()->getProvider()->getOctaves()));
        break;
    case 36:
            this->theAlgorithmPresenter->getNoisePresenter()->decrementAmplitude();
            this->getWidget(37)->setText("Amplitude: "+std::to_string(this->theAlgorithmPresenter->getNoisePresenter()->getProvider()->getAmplitude()));
        break;
    case 38:
            this->theAlgorithmPresenter->getNoisePresenter()->incrementAmplitude();
            this->getWidget(37)->setText("Amplitude: "+std::to_string(this->theAlgorithmPresenter->getNoisePresenter()->getProvider()->getAmplitude()));
        break;
    case 40:
            this->theAlgorithmPresenter->getNoisePresenter()->decrementHeightOffset();
            this->getWidget(41)->setText("Height Offset: "+std::to_string(this->theAlgorithmPresenter->getNoisePresenter()->getProvider()->getHeightOffset()));
        break;
    case 42:
            this->theAlgorithmPresenter->getNoisePresenter()->incrementHeightOffset();
            this->getWidget(41)->setText("Height Offset: "+std::to_string(this->theAlgorithmPresenter->getNoisePresenter()->getProvider()->getHeightOffset()));
        break;
    case 44:
            this->theAlgorithmPresenter->getNoisePresenter()->decrementRoughness();
            this->getWidget(45)->setText("Roughness: "+std::to_string(this->theAlgorithmPresenter->getNoisePresenter()->getProvider()->getRoughness()));
        break;
    case 46:
            this->theAlgorithmPresenter->getNoisePresenter()->incrementRoughness();
            this->getWidget(45)->setText("Roughness: "+std::to_string(this->theAlgorithmPresenter->getNoisePresenter()->getProvider()->getRoughness()));
        break;
    }

}
void AlgorithmVisualPresenterScreen::update()
{
    this->checkForFunctions();
}

void AlgorithmVisualPresenterScreen::render()
{
    this->update();
    for(int i=0; i<this->widgets.size(); i++)
    {
        this->widgets[i]->render();

    }

}
