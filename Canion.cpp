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
    hitbox->x = 15;
    hitbox->y = HEIGHT - hitbox->y - 10;
}

Canion::~Canion()
{

}

void Canion::act(ALLEGRO_EVENT *ev){

}

void Canion::draw(){
    al_draw_scaled_rotated_bitmap(image, xcenter, ycenter, hitbox->x, hitbox->y,1,1, angle, 0);
}
