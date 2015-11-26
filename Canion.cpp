#include "Canion.h"

Canion::Canion(ALLEGRO_EVENT_QUEUE *event_queue, list<Entidad *> *entidades) : Entidad()
{
    this->event_queue = event_queue;
    this->entidades = entidades;
    velocity = 0;
    angle = 0;
    tipoObjeto = "Canion";

    //Aqui va mas programacion :D
    image = al_load_bitmap("Assets/Canon.png");
    hitbox->width = al_get_bitmap_width(image);
    hitbox->height = al_get_bitmap_height(image);
    xcenter = hitbox->width/2;
    ycenter = hitbox->height/2;
    hitbox->scale = 0.3;
    hitbox->x = 0 + (hitbox->width*hitbox->scale/2);
    hitbox->y = HEIGHT - (hitbox->height * hitbox->scale /2);
}

Canion::~Canion()
{

}

void Canion::act(ALLEGRO_EVENT *ev){
    validarTeclas(ev);
    if(key[KEY_UP])
        angle -= PI/40;
    if(key[KEY_DOWN])
        angle += PI/40;
    if(key[KEY_RIGHT] && velocity <= 148)
        velocity += 2;
    if(key[KEY_LEFT] && velocity >= 2)
        velocity -= 2;
    if(angle < -PI/2)
        angle = -PI/2;
    if(angle > 0)
        angle = 0;
}

void Canion::draw(){
    al_draw_scaled_rotated_bitmap(image, xcenter, ycenter, hitbox->x, hitbox->y,hitbox->scale,hitbox->scale, angle, 0);
}
