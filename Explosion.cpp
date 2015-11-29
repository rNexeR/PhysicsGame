#include "Explosion.h"

Explosion::Explosion() : Entidad()
{
    destroied=false;
    tipoObjeto = "Explosion";
    image.push_back(al_load_bitmap("Assets/Castle 1.png"));
    image.push_back(al_load_bitmap("Assets/Castle 2.png"));
    image.push_back(al_load_bitmap("Assets/Castle 4.png"));
    image.push_back(al_load_bitmap("Assets/Castle 5.png"));
    image.push_back(al_load_bitmap("Assets/Castle 6.png"));
    tFrames=image.size();
    hitbox->scale = 0.5;
    hitbox->width = al_get_bitmap_width(image[0]);
    hitbox->height = al_get_bitmap_height(image[0]);
    xcenter = hitbox->width/2;
    ycenter = hitbox->height/2;
    hitbox->x = WIDTH - (xcenter*hitbox->scale);
    hitbox->y = HEIGHT - (ycenter*hitbox->scale);
}

Explosion::~Explosion()
{
    //dtor
}
