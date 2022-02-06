#include "skybox.h"
void SkyBox::render(Camera camera) {
    
        DrawBillboard(camera,this->texture,{this->pos.x, this->pos.y, this->pos.z}, 1000.0, WHITE);
}
