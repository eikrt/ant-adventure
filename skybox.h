#ifndef SKYBOX_H
#define SKYBOX_H
#include <raylib.h>
class SkyBox {
    public:
        Texture2D texture;
        Vector3 pos;
        Color skyColor;
        SkyBox(Texture2D texture, Color skyColor, Vector3 pos) {
           this->texture = texture; 
           this->skyColor = skyColor;
           this->pos = pos;
        }
        void render(Camera camera);
};

#endif
