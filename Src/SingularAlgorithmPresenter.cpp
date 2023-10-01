#include "SingularAlgorithmPresenter.h"
#include "AlgorithmVisualPresenter.h"

SingularAlgorithmPresenter::SingularAlgorithmPresenter(RenderEngine* engine, AlgorithmVisualPresenter* presenter){

    this->renderEngine = engine;
    this->algorithmPresenter = presenter;
    this->shouldPresent = true;

}
SingularAlgorithmPresenter::~SingularAlgorithmPresenter(){


}

float SingularAlgorithmPresenter::getUpdateCounter(){

    return this->updateValue;

}

void SingularAlgorithmPresenter::setPresentation(bool newState){

    this->shouldPresent = newState;
}

void SingularAlgorithmPresenter::setUpdateCounter(float newVal){

    this->updateValue = newVal;

}

void SingularAlgorithmPresenter::updateCounter(){

    if(!this->updateRequired){
        this->counterValue -= this->algorithmPresenter->getApp()->getDeltaTime();
    }

    if(this->counterValue<=0){
        this->updateRequired = true;
        this->counterValue = this->updateValue;

    }

}

void SingularAlgorithmPresenter::render(){

    if(this->algorithmPresenter->getDimension() == TWOD)
        {
            this->renderEngine->clearVerts(this->renderEngine->BASIC_2D_SHADER, true);
            glClear(GL_COLOR_BUFFER_BIT);
            this->render2D();
            this->renderEngine->drawBasic2D();

        }
        else if(this->algorithmPresenter->getDimension() == THREED)
        {
            this->renderEngine->clearVerts(this->renderEngine->BASIC_3D_SHADER, true);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);
            this->render3D();
            this->renderEngine->drawBasic3D();
            //this->renderEngine->renderSkyboxBackground(this->algorithmPresenter->getViewer()->getCamera()->getViewMatrix());
        }

}

void SingularAlgorithmPresenter::run()
{
    if(this->shouldPresent){
        this->update();
        this->render();
    }

}


