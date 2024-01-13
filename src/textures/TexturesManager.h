#ifndef TEXTURES_MANAGER_H
#define TEXTURES_MANAGER_H

#include <iostream>
#include <GL/glew.h>
#include <FreeImage.h>

class TexturesManager {
    
    public:
               
        void         initTexture(const char *textureFile); 
        unsigned int getTexture(); 

        virtual ~TexturesManager();
           
    private:
       
        unsigned int  texture;
        
        unsigned char *loadTexture(const char *textureFile, unsigned int &w, unsigned int &h);
        
};

#endif /* TEXTURES_MANAGER_H */
