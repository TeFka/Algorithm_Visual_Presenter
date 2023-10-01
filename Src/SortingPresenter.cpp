#include "../Inc/SortingPresenter.h"
#include "../Inc/AlgorithmVisualPresenter.h"

SortingPresenter::SortingPresenter(RenderEngine* engine, AlgorithmVisualPresenter* presenter) : SingularAlgorithmPresenter(engine, presenter)
{

    this->renderEngine = engine;
    this->theSortProvider = new SortingProvider();

    this->setData(10);

    this->sortProgression = 0;

    this->updating3DPositions = false;

    this->moveDir = glm::vec3(((float)(rand() % 100 + 1)/100),((float)(rand() % 100 + 1)/100),((float)(rand() % 100 + 1)/100));

    this->blockPos = glm::vec3(0.0f, 0.0f, -5.0f);
}
SortingPresenter::~SortingPresenter()
{


}

void SortingPresenter::reset()
{

    this->sortProgression = 0;
    this->counterValue = this->updateValue;

    this->positionData3D.clear();
    this->newPositionData3D.clear();

    this->updating3DPositions = false;

    this->resetPositions();
}

void SortingPresenter::update2D()
{
    this->twoDUpdateState++;
    if(this->twoDUpdateState==1)
    {
        for(int i = 0; i<this->theActiveDataProgression[this->sortProgression].size(); i++)
        {
            if(this->theActiveDataProgression[this->sortProgression+1][i]!=this->theActiveDataProgression[this->sortProgression][i])
            {

                this->theOriginalActiveDataUpdates[this->theActiveDataProgression[this->sortProgression][i]] = true;

            }

        }
    }

    if(this->twoDUpdateState==2)
    {
        if(this->sortProgression<this->theActiveDataProgression.size()-1)
        {
            this->sortProgression++;
            this->twoDUpdateState=0;

            for(int i = 0; i<this->theOriginalActiveDataUpdates.size(); i++)
            {

                this->theOriginalActiveDataUpdates[i] = false;

            }

        }
    }

}

void SortingPresenter::update3D()
{
    bool doneUpdating = true;
    //std::cout<<"new check"<<std::endl;

    //std::cout<<"index comparison"<<std::endl;
    for(int i = 0; i<this->theOriginalActiveData.size(); i++)
    {

        //std::cout<<this->theActiveDataProgression[this->sortProgression][i]<<" ";
    }
    //std::cout<<std::endl;

    for(int i = 0; i<this->theOriginalActiveData.size(); i++)
    {

        //std::cout<<this->theActiveDataProgression[this->sortProgression+1][i]<<" ";
    }
    //std::cout<<std::endl;

    //std::cout<<"position comparison"<<std::endl;
    for(int i = 0; i<this->theOriginalActiveData.size(); i++)
    {

        //std::cout<<this->newPositionData3D[this->theActiveDataProgression[this->sortProgression][i]].x<<" ";
    }
    //std::cout<<std::endl;

    for(int i = 0; i<this->theOriginalActiveData.size(); i++)
    {

        //std::cout<<(float)this->positionData3D[this->theActiveDataProgression[this->sortProgression+1][i]].x<<" ";
    }
    //std::cout<<std::endl;
    for(int i = 0; i<this->theActiveDataProgression[this->sortProgression].size(); i++)
    {

        if(this->theActiveDataProgression[this->sortProgression][i]!=this->theActiveDataProgression[this->sortProgression+1][i])
        {
            //std::cout<<"position need from: "<<this->newPositionData3D[this->theActiveDataProgression[this->sortProgression][i]].x<<" to: "<<this->positionData3D[this->theActiveDataProgression[this->sortProgression+1][i]].x<<std::endl;
            this->newPositionData3D[this->theActiveDataProgression[this->sortProgression][i]].x = this->positionData3D[this->theActiveDataProgression[this->sortProgression+1][i]].x;
            this->theOriginalActiveDataUpdates[i] = true;
            doneUpdating = false;
        }

    }

    if(doneUpdating)
    {
        //std::cout<<"updating progression"<<std::endl;
        if(this->sortProgression<this->theActiveDataProgression.size())
        {
            this->sortProgression++;
        }

    }

    if(!doneUpdating)
    {
        //std::cout<<"updating positions"<<std::endl;
        this->updating3DPositions = true;
    }

}

void SortingPresenter::update()
{

    if(this->sortProgression<this->theActiveDataProgression.size()-1)
    {
        this->updateCounter();
        if(this->updateRequired)
        {
            if(this->algorithmPresenter->getDimension() == TWOD)
            {
                this->update2D();
            }
            else if(this->algorithmPresenter->getDimension() == THREED)
            {
                ////std::cout<<"updating algorithm 3D presenter: "<<std::endl;
                if(this->updating3DPositions)
                {
                    ////std::cout<<"updating positions"<<std::endl;
                    ////std::cout<<"progression: "<<this->sortProgression<<std::endl;
                    bool doneUpdating = true;
                    ////std::cout<<"updating algorithm 3D presenter positions: "<<std::endl;
                    for(int i = 0; i<this->theActiveDataProgression[this->sortProgression].size(); i++)
                    {
                        ////std::cout<<"checking "<<i<<": "<<this->theOriginalActiveDataUpdates[i]<<std::endl;
                        //if(this->theOriginalActiveDataUpdates[i])
                        //{
                            ////std::cout<<"updating position: "<<this->positionData3D[i].x<<std::endl;
                            if(abs(this->newPositionData3D[i].x-this->positionData3D[i].x)>this->blockSize*0.5)
                            {
                                doneUpdating = false;
                                if(this->positionData3D[i].y>(this->platformHeight+this->blockSize)/2+this->blockSize*3.0f)
                                {
                                    ////std::cout<<"moving Y up"<<std::endl;
                                    this->positionData3D[i].y -= this->movementSpeed*this->algorithmPresenter->getApp()->getDeltaTime();
                                }
                                else
                                {
                                    ////std::cout<<"moving X"<<std::endl;
                                    this->positionData3D[i].x += (2*(this->newPositionData3D[i].x>this->positionData3D[i].x)-1)*this->movementSpeed*this->algorithmPresenter->getApp()->getDeltaTime();
                                }
                            }
                            else
                            {
                                this->positionData3D[i].x = this->newPositionData3D[i].x;
                                ////std::cout<<"moving Y down"<<std::endl;
                                if(this->positionData3D[i].y<(this->platformHeight+this->blockSize)/2)
                                {
                                    doneUpdating = false;
                                    this->positionData3D[i].y += this->movementSpeed*this->algorithmPresenter->getApp()->getDeltaTime();
                                }
                                else
                                {
                                    ////std::cout<<"done"<<std::endl;
                                    this->positionData3D[i].y = (this->platformHeight+this->blockSize)/2;
                                    this->theOriginalActiveDataUpdates[i] = false;
                                }
                            }

                        //}
                    }

                    if(doneUpdating)
                    {
                        this->updating3DPositions = false;
                        this->sortProgression++;
                    }
                }
                else
                {
                    //std::cout<<"updating algorithm 3D presenter needed positions"<<std::endl;
                    this->update3D();

                }
                ////std::cout<<"done updating algorithm 3D presenter: "<<std::endl;
            }
            this->updateRequired = false;
        }
    }
}

void SortingPresenter::render2D()
{
    ////std::cout<<"rendering sort"<<std::endl;
    for(int i = 0; i<this->theActiveDataProgression[this->sortProgression].size(); i++)
    {
        if(this->theOriginalActiveDataUpdates[this->theActiveDataProgression[this->sortProgression][i]])
        {
            if(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]>0)
            {
                this->renderEngine->setBasic2DSprite(glm::vec2((((float)(i))+0.5f)/(this->theActiveDataProgression[this->sortProgression].size()),
                                                     0.5f*(1.0f-0.5*(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]/this->theSortProvider->getMaximumValue()))),
                                                     glm::vec2(1.0f/(this->theActiveDataProgression[this->sortProgression].size()),
                                                             0.5f*(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]/this->theSortProvider->getMaximumValue())),
                                                     glm::vec4(0.9f,0.9f,0.0f,1.0f));
            }
            else if(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]<0)
            {
                this->renderEngine->setBasic2DSprite(glm::vec2((((float)(i))+0.5f)/(this->theActiveDataProgression[this->sortProgression].size()),
                                                     0.5f*(1.0f+0.5*(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]/this->theSortProvider->getMinimumValue()))),
                                                     glm::vec2(1.0f/(this->theActiveDataProgression[this->sortProgression].size()),
                                                             0.5f*(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]/this->theSortProvider->getMinimumValue())),
                                                     glm::vec4(0.9f,0.9f,0.0f,1.0f));
            }
        }
        else
        {
            if(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]>0)
            {
                this->renderEngine->setBasic2DSprite(glm::vec2((((float)(i))+0.5f)/(this->theActiveDataProgression[this->sortProgression].size()),
                                                     0.5f*(1.0f-0.5*(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]/this->theSortProvider->getMaximumValue()))),
                                                     glm::vec2(1.0f/(this->theActiveDataProgression[this->sortProgression].size()),
                                                             0.5f*(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]/this->theSortProvider->getMaximumValue())),
                                                     glm::vec4(0.7f,0.0f,0.0f,1.0f));
            }
            else if(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]<0)
            {
                this->renderEngine->setBasic2DSprite(glm::vec2((((float)(i))+0.5f)/(this->theActiveDataProgression[this->sortProgression].size()),
                                                     0.5f*(1.0f+0.5*(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]/this->theSortProvider->getMinimumValue()))),
                                                     glm::vec2(1.0f/(this->theActiveDataProgression[this->sortProgression].size()),
                                                             0.5f*(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]/this->theSortProvider->getMinimumValue())),
                                                     glm::vec4(0.0f,0.0f,0.7f,1.0f));
            }
        }

    }
    ////std::cout<<"done rendering sort"<<std::endl;
}

void SortingPresenter::render3D()
{
    glm::mat4 viewMatrix = this->algorithmPresenter->getViewer()->getCamera()->getViewMatrix();
    this->renderEngine->getShaderProgram(this->renderEngine->BASIC_3D_SHADER, true)->getShader()->setMat4(viewMatrix,"viewMatrix");

    //render platform
    this->renderEngine->setBasic3DSprite(glm::vec3(0.0f), glm::vec3(this->platformSize,this->platformHeight,this->platformSize), glm::vec4(0.0f,1.0f,1.0f,1.0f));

    ////std::cout<<"3D block num: "<<this->positionData3D.size()<<std::endl;
    for(int i = 0; i<this->theOriginalActiveData.size(); i++)
    {
        ////std::cout<<"3D block pos: "<<this->positionData3D[this->theActiveDataProgression[this->sortProgression][i]].x<<std::endl;
        if(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]>=0)
        {
            //render block
            this->renderEngine->setBasic3DSprite(this->positionData3D[this->theActiveDataProgression[this->sortProgression][i]],
                                                 glm::vec3(this->blockSize),
                                                 glm::vec4((float)(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]/this->theSortProvider->getMaximumValue()),0.0f,0.0f,1.0f));
        }
        else if(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]<0)
        {
            //render block
            this->renderEngine->setBasic3DSprite(this->positionData3D[this->theActiveDataProgression[this->sortProgression][i]],
                                                 glm::vec3(this->blockSize),
                                                 glm::vec4(0.0f,0.0f,(float)(this->theOriginalActiveData[this->theActiveDataProgression[this->sortProgression][i]]/this->theSortProvider->getMinimumValue()),1.0f));
        }

    }

}

void SortingPresenter::render3DTest()
{
    //std::cout<<"rendering test"<<std::endl;
    if(this->blockPos.x > 15.0f || this->blockPos.x < 5.0f)
    {
        this->moveDir.x = -this->moveDir.x;
    }
    if(this->blockPos.y > 5.0f || this->blockPos.y < -5.0f)
    {
        this->moveDir.y = -this->moveDir.y;
    }
    if(this->blockPos.z > 5.0f || this->blockPos.z < -5.0f)
    {
        this->moveDir.z = -this->moveDir.z;
    }

    //movement
    this->blockPos += 2.0f*this->moveDir*this->algorithmPresenter->getApp()->getDeltaTime();

    this->renderEngine->getShaderProgram(this->renderEngine->BASIC_3D_SHADER, true)->getShader()->setMat4(this->algorithmPresenter->getViewer()->getCamera()->getViewMatrix(),"viewMatrix");

    this->renderEngine->setBasic3DSprite(this->blockPos,glm::vec3(1.0), glm::vec4(1.0,0.0,0.0,1.0));
}

void SortingPresenter::changeTypeForward()
{

    this->usedSort++;
    if(this->usedSort>this->theSortProvider->getMaxSortNum())
    {

        this->usedSort=0;
    }

    this->theSortProvider->performSort(this->usedSort);
    this->theActiveDataProgression = this->theSortProvider->getDataIndexing();
    for(int i =0;i<this->theActiveDataProgression.size();i++){
        for(int n =0;n<this->theActiveDataProgression[i].size();n++){
            //std::cout<<this->theActiveDataProgression[i][n]<<"->"<<this->theOriginalActiveData[this->theActiveDataProgression[i][n]]<<" ";
        }
        //std::cout<<std::endl;
    }
    this->reset();

}

void SortingPresenter::changeTypeBackward()
{

    this->usedSort--;
    if(this->usedSort<0)
    {

        this->usedSort=this->theSortProvider->getMaxSortNum();
    }

    this->theSortProvider->performSort(this->usedSort);
    this->theActiveDataProgression = this->theSortProvider->getDataIndexing();
    /*for(int i =0;i<this->theActiveDataProgression.size();i++){
        for(int n =0;n<this->theActiveDataProgression[i].size();n++){
            //std::cout<<this->theActiveDataProgression[i][n]<<"->"<<this->theOriginalActiveData[this->theActiveDataProgression[i][n]]<<" ";
        }
        //std::cout<<std::endl;
    }*/
    this->reset();

}

SortingProvider* SortingPresenter::getProvider()
{

    return this->theSortProvider;

}

void SortingPresenter::resetPositions(){

    this->positionData3D.clear();
    this->newPositionData3D.clear();

    for(int i=0;i<this->theOriginalActiveData.size();i++){

        this->positionData3D.push_back(glm::vec3(this->blockSize+this->blockSize*3*(i%this->blockInLine),(this->platformHeight+this->blockSize)/2, this->blockSize*3*(i/this->blockInLine)));
        this->newPositionData3D.push_back(glm::vec3(this->blockSize+this->blockSize*3*(i%this->blockInLine),(this->platformHeight+this->blockSize)/2, this->blockSize*3*(i/this->blockInLine)));

    }

}

void SortingPresenter::setData(float dataNum)
{

    //std::srand(//std::time(nullptr));

    this->theOriginalActiveData.clear();
    this->theOriginalActiveDataUpdates.clear();

    for(int i = 0; i<dataNum; i++)
    {
        ////std::cout<<"random value: "<<std::rand()<<std::endl;
        this->theOriginalActiveData.push_back(2*((double)std::rand()/RAND_MAX)-1);
        this->theOriginalActiveDataUpdates.push_back(false);

    }

    this->resetPositions();

    this->theSortProvider->setOriginalData(this->theOriginalActiveData);
    this->theSortProvider->performSort(this->usedSort);
    this->theActiveDataProgression = this->theSortProvider->getDataIndexing();

    for(int i =0;i<this->theActiveDataProgression.size();i++){
        for(int n =0;n<this->theActiveDataProgression[i].size();n++){
            //std::cout<<this->theActiveDataProgression[i][n]<<"->"<<this->theOriginalActiveData[this->theActiveDataProgression[i][n]]<<" ";
        }
        //std::cout<<std::endl;
    }
}

int SortingPresenter::getDataSize()
{

    return this->theOriginalActiveData.size();

}
