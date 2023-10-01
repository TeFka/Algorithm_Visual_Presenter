#ifndef VIEWER3D_H_INCLUDED
#define VIEWER3D_H_INCLUDED

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>

#include <Render/Camera.h>

class Viewer3D
{

private:
    Camera* ViewerCamera;
    glm::vec3 faceDirection;
    glm::vec3 upDirection = glm::vec3(0.0,1.0,0.0);
    glm::vec3 pos;
    glm::mat4 rotationMatrix;
    float defaultSpeed;
    float xRotation = 0;
    float yRotation = 0;

    void updateCamera();

    void updateFrontVec();

public:

    Viewer3D();

    void positionCommand(float xSet, float ySet, GLboolean pitchConstr = true);

    void update();

    Camera* getCamera();

    void mouseCommand(float, float, GLboolean = true);

};

#endif // VIEWER3D_H_INCLUDED
