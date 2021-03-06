#include "Explosion.h"

Explosion::Explosion(double xpos, double ypos) : Entidad()
{
    destroied=false;
    tipoObjeto = "Explosion";
    image.push_back(al_load_bitmap("Assets/explosion1.png"));
    image.push_back(al_load_bitmap("Assets/explosion2.png"));
    image.push_back(al_load_bitmap("Assets/explosion4.png"));
    image.push_back(al_load_bitmap("Assets/explosion5.png"));

    tFrames=image.size();
    hitbox->scale = 0.5;
    hitbox->width = al_get_bitmap_width(image[0]);
    hitbox->height = al_get_bitmap_height(image[0]);
    xcenter = hitbox->width/2;
    ycenter = hitbox->height/2;
    hitbox->x = xpos;
    hitbox->y = ypos;
    fActual = 0;
}

Explosion::Explosion(double xpos, double ypos, double scale) : Explosion(xpos, ypos)
{
    hitbox->scale = scale;
    hitbox->x = xpos + 15;
    hitbox->y = ypos;
    //effect = al_load_sample("explosion.ogg");
    //al_play_sample(effect, 0.7, 0.0, 3.0, ALLEGRO_PLAYMODE_ONCE, &ieffect);
}

Explosion::~Explosion()
{
    for (int x = 0; x < image.size(); x++)
        al_destroy_bitmap(image[x]);
    //al_destroy_sample(effect);
    delete(hitbox);
}

void Explosion::act(ALLEGRO_EVENT* ev)
{
    frame++;
    if (frame%10 == 0)
        fActual++;
    if (fActual >= tFrames){
        fActual = tFrames-1;
        destroied = true;
    }
}

void Explosion::draw()
{
    al_draw_scaled_rotated_bitmap(image[fActual], xcenter, ycenter, hitbox->x, hitbox->y,hitbox->scale,hitbox->scale,0, 0);
}
