#include "button.h"

void Button::render(Camera camera) {
        if (this->selected)
            DrawTexture(this->textures[0],this->pos.x, this->pos.y, WHITE);
        else if (!this->selected)
            DrawTexture(this->textures[0],this->pos.x, this->pos.y, WHITE);
}
void Button::tick() {
    
}
