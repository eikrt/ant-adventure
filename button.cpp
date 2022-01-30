#include "button.h"

void Button::render(Camera camera) {
        if (this->selected)
            DrawTexture(this->textures[0],this->pos.x, this->pos.y, WHITE);
        else if (!this->selected)
            DrawTexture(this->textures[0],this->pos.x, this->pos.y, WHITE);
        DrawTextEx(this->font, this->text, {this->pos.x + 16,this->pos.y + 8},18, 2, {255,255,255, 255});
}
void Button::tick() {
    
}
