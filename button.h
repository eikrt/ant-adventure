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
    public:
        bool selected;
        Button(Vector2 pos, vector<Texture2D> textures) {
            this->pos = pos;
            this->status = 0;
            this->textures = textures;
            this->selected;
        }
        void render(Camera camera);
        void tick();
};
#endif
