#include "Render/Texture.h"

#include "helpers/RootDir.h"

Texture::Texture(){


}

Texture::Texture(unsigned int textureSource, GLenum type,GLint textureUnt, std::string typ)
{

    this->id = textureSource;
    this->type = type;
    this->typ = typ;
    this->textureUnit = textureUnt;
}

Texture::Texture(const char* fileName,GLenum type,GLint textureUnt,std::string typ)
{
    this->type = type;
    this->typ = typ;
    this->path = (char*)fileName;
    this->textureUnit = textureUnt;

    int nrChannels;
    unsigned char *data = stbi_load(this->path,&this->width,&this->height,  &nrChannels, 0);
    glGenTextures(1, &this->id);
    glBindTexture(type, this->id);
    glTexParameteri(type,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(type,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(type,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(type,GL_TEXTURE_WRAP_T,GL_REPEAT);
    if(data)
    {
        
        glTexImage2D(type,0,GL_RGB,this->width,this->height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(type);

    }
    else
    {
        std::cout<<"ERROR:TEXTURE:Couldnt load texture"<<fileName<<std::endl;
    }

    glActiveTexture(0);
    glBindTexture(type, 0);
    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1,&this->id);
}

inline GLuint Texture::getId() const
{
    return this->id;
}

std::string Texture::getTyp()
{
    return this->typ;
}

char* Texture::getPath()
{
    return this->path;
}

void Texture::bindT()
{
    glActiveTexture(GL_TEXTURE0 + this->textureUnit);
    glBindTexture(this->type,this->id);
}

void Texture::unBindT()
{
    glActiveTexture(0);
    glBindTexture(this->type, 0);
}

GLuint Texture::getUnit() const
{
    return this->textureUnit;
}

void Texture::loadNewTex(const char* fileName,GLenum type)
{
    if(this->id)
    {
        glDeleteTextures(1,&this->id);
    }

    int nrChannels;
    unsigned char *data = stbi_load((char*)fileName,&this->width,&this->height,  &nrChannels, 0);

    glGenTextures(1, &this->id);
    glBindTexture(type, this->id);

    glTexParameteri(type,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(type,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(type,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(type,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    if(data)
    {
        glTexImage2D(type,0,GL_RGB,this->width,this->height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(type);

    }
    else
    {
        std::cout<<"ERROR:TEXTURE:Couldnt load texture from file"<<fileName<<std::endl;
    }
    glActiveTexture(0);
    glBindTexture(type, 0);
    stbi_image_free(data);
}
