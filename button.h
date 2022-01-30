#ifndef BUTTON_H
#define BUTTON_H
#include <vector>
#include <raylib.h>
using namespace std;
class Button {
    private:
        Vector2 pos;
        int status;
        vector<Texture2D> textures;
        Font font;
        const char* text;
    public:
        bool selected;
        Button(Vector2 pos, const char* text, Font font, vector<Texture2D> textures) {
            this->pos = pos;
            this->status = 0;
            this->textures = textures;
            this->selected;
            this->text = text;
            this->font = font;
        }
        void render(Camera camera);
        void tick();
};
#endif
