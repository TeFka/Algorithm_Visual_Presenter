#include "Render/Viewer3D.h"

Viewer3D::Viewer3D()
{
    this->ViewerCamera = new Camera();
}

void Viewer3D::updateCamera()
{
    this->ViewerCamera->setPosition(this->pos);
    this->ViewerCamera->setFront(this->faceDirection);
}

void Viewer3D::updateFrontVec()
{
    glm::vec3 frontCm;
    this->rotationMatrix = glm::mat4(1.0);

    frontCm.x=cos(glm::radians(this->xRotation))*cos(glm::radians(this->yRotation));

    frontCm.y=sin(glm::radians(this->xRotation));

    frontCm.z=cos(glm::radians(this->xRotation))*sin(glm::radians(this->yRotation));

    this->faceDirection=-glm::normalize(frontCm);
}

void Viewer3D::mouseCommand(float xSet, float ySet, GLboolean pitchConstr)
{

    xSet*=this->ViewerCamera->getSensetivity();
    ySet*=this->ViewerCamera->getSensetivity();

    xRotation-=ySet;
    yRotation+=xSet;

    if(pitchConstr)
    {
        if(xRotation>89.0)
        {
            xRotation=89.0;
        }
        if(xRotation<-89.0)
        {
            xRotation=-89.0;
        }
    }
    this->updateFrontVec();
    this->updateCamera();
}

void Viewer3D::update()
{
    this->updateFrontVec();
    this->updateCamera();
}

Camera* Viewer3D::getCamera()
{

    return this->ViewerCamera;
}
