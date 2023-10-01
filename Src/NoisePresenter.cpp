#include "../Inc/NoisePresenter.h"
#include "../Inc/AlgorithmVisualPresenter.h"


NoisePresenter::NoisePresenter(RenderEngine* engine, AlgorithmVisualPresenter* presenter) : SingularAlgorithmPresenter(engine, presenter)
{
    this->theNoiseProvider = new NoiseProvider();
    this->reset();

}

NoisePresenter::~NoisePresenter()
{


}

void NoisePresenter::reset()
{
    std::cout<<"reset1"<<std::endl;
    this->theNoiseProvider->generateNoise(this->usedNoise);
    std::cout<<"reset2"<<std::endl;
    this->noiseHeightMap = this->theNoiseProvider->getData();
    /* for(int x = 0; x<this->theNoiseProvider->getWidthNum(); x++)
     {
         for(int y = 0; y<this->theNoiseProvider->getHeightNum(); y++)
         {

                 std::cout<<this->noiseHeightMap[x][y]<<" ";
         }
         std::cout<<std::endl;
     }
     std::cout<<"reset3"<<std::endl;*/

}

std::vector<std::vector<double>>& NoisePresenter::getData()
{




}

void NoisePresenter::update2D()
{


}

void NoisePresenter::update3D()
{


}

void NoisePresenter::update()
{

    if(this->updateRequired)
    {
        this->noiseHeightMap = this->theNoiseProvider->getData();
    }

}


void NoisePresenter::render2D()
{
    for(int x = 0; x<this->theNoiseProvider->getWidthNum(); x++)
    {
        for(int y = 0; y<this->theNoiseProvider->getHeightNum(); y++)
        {
            this->renderEngine->setBasic2DSprite(glm::vec2(((float)x+0.5)/this->theNoiseProvider->getWidthNum(),
                                                 ((float)y+0.5)/this->theNoiseProvider->getHeightNum()),
                                                 glm::vec2(1.0f/this->theNoiseProvider->getWidthNum(), 1.0f/this->theNoiseProvider->getHeightNum()),
                                                 glm::vec4(1.0f-this->noiseHeightMap[x][y],1.0f-this->noiseHeightMap[x][y],1.0f-this->noiseHeightMap[x][y],1.0f));
        }
    }

}

void NoisePresenter::render3D()
{

    glm::mat4 viewMatrix = this->algorithmPresenter->getViewer()->getCamera()->getViewMatrix();
    this->renderEngine->getShaderProgram(this->renderEngine->BASIC_3D_SHADER, true)->getShader()->setMat4(viewMatrix,"viewMatrix");
    for(int x = 0; x<this->theNoiseProvider->getWidthNum(); x++)
    {
        for(int z = 0; z<this->theNoiseProvider->getHeightNum(); z++)
        {
            this->renderEngine->setBasic3DSprite(glm::vec3((float)this->blockSize/2+x*this->blockSize,
                                                 (float)-this->theNoiseProvider->getRealVal(x, z)/2,
                                                 (float)this->blockSize/2+z*this->blockSize),
                                                 glm::vec3(this->blockSize, this->theNoiseProvider->getRealVal(x, z), this->blockSize),
                                                 glm::vec4(0.3f,0.3f,0.3f,1.0f));
        }
    }
}

void NoisePresenter::render3DTest()
{



}

int NoisePresenter::getUsedNoise(int newVal)
{

    return this->usedNoise;
}

int NoisePresenter::getUsedNoise()
{

    return this->usedNoise;
}

void NoisePresenter::changeTypeForward()
{

    this->usedNoise++;
    if(this->usedNoise>this->theNoiseProvider->getMaxNoiseNum())
    {

        this->usedNoise=0;
    }

    this->reset();

}

void NoisePresenter::changeTypeBackward()
{

    this->usedNoise--;
    if(this->usedNoise<0)
    {

        this->usedNoise=this->theNoiseProvider->getMaxNoiseNum();
    }

    this->reset();

}

NoiseProvider* NoisePresenter::getProvider()
{

    return this->theNoiseProvider;

}

void NoisePresenter::incrementOctaves()
{
    this->theNoiseProvider->setOctaves(this->theNoiseProvider->getOctaves()+1);
    if(this->theNoiseProvider->getOctaves()>this->maxOctaves)
    {
        this->theNoiseProvider->setOctaves(this->minOctaves);
    }
    this->reset();

}
void NoisePresenter::incrementAmplitude()
{
    this->theNoiseProvider->setAmplitude(this->theNoiseProvider->getAmplitude()+5);
    if(this->theNoiseProvider->getAmplitude()>this->maxAmplitude)
    {
        this->theNoiseProvider->setAmplitude(this->minAmplitude);
    }
    this->reset();

}
void NoisePresenter::incrementSmoothness()
{
    this->theNoiseProvider->setSmoothness(this->theNoiseProvider->getSmoothness()+10);
    if(this->theNoiseProvider->getSmoothness()>this->maxSmoothness)
    {
        this->theNoiseProvider->setSmoothness(this->minSmoothness);
    }
    this->reset();

}
void NoisePresenter::incrementHeightOffset()
{
    this->theNoiseProvider->setHeightOffset(this->theNoiseProvider->getHeightOffset()+2);
    if(this->theNoiseProvider->getHeightOffset()>this->maxHeightOffset)
    {
        this->theNoiseProvider->setHeightOffset(this->minHeightOffset);
    }
    this->reset();

}
void NoisePresenter::incrementRoughness()
{
    this->theNoiseProvider->setRoughness(this->theNoiseProvider->getRoughness()+0.02f);
    if(this->theNoiseProvider->getRoughness()>this->maxRoughness)
    {
        this->theNoiseProvider->setRoughness(this->minRoughness);
    }
    this->reset();

}

void NoisePresenter::decrementOctaves()
{
    this->theNoiseProvider->setOctaves(this->theNoiseProvider->getOctaves()-1);
    if(this->theNoiseProvider->getOctaves()<this->minOctaves)
    {
        this->theNoiseProvider->setOctaves(this->maxOctaves);
    }
    this->reset();

}
void NoisePresenter::decrementAmplitude()
{
    this->theNoiseProvider->setAmplitude(this->theNoiseProvider->getAmplitude()-5);
    if(this->theNoiseProvider->getAmplitude()<this->minAmplitude)
    {
        this->theNoiseProvider->setAmplitude(this->maxAmplitude);
    }

}
void NoisePresenter::decrementSmoothness()
{
    this->theNoiseProvider->setSmoothness(this->theNoiseProvider->getSmoothness()-10);
    if(this->theNoiseProvider->getSmoothness()<this->minSmoothness)
    {
        this->theNoiseProvider->setSmoothness(this->maxSmoothness);
    }
    this->reset();

}
void NoisePresenter::decrementHeightOffset()
{
    this->theNoiseProvider->setHeightOffset(this->theNoiseProvider->getHeightOffset()-2);
    if(this->theNoiseProvider->getHeightOffset()<this->minHeightOffset)
    {
        this->theNoiseProvider->setHeightOffset(this->minHeightOffset);
    }
    this->reset();

}
void NoisePresenter::decrementRoughness()
{
    this->theNoiseProvider->setRoughness(this->theNoiseProvider->getRoughness()-0.02f);
    if(this->theNoiseProvider->getRoughness()<this->minRoughness)
    {
        this->theNoiseProvider->setRoughness(this->maxRoughness);
    }
    this->reset();

}


