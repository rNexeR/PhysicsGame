#include "Pendulo.h"

Pendulo::Pendulo() : Entidad()
{
    tipoObjeto = "Pendulo";

    ball = al_load_bitmap("Assets/EsferaM.png");
    thread = al_load_bitmap("Assets/varillametal.png");

    hitboxCuerda = new Box(0,0,0,0,0);
    hitboxCuerda->scale = 1;
    hitboxCuerda->width = al_get_bitmap_width(thread);
    hitboxCuerda->height = al_get_bitmap_height(thread);
    xcenterCuerda = hitboxCuerda->width/2;
    ycenterCuerda = hitboxCuerda->height/2;
    hitboxCuerda->x = WIDTH - (xcenterCuerda*hitboxCuerda->scale);
    hitboxCuerda->y = HEIGHT - (ycenterCuerda*hitboxCuerda->scale);

    hitbox->scale = 1;
    hitbox->width = al_get_bitmap_width(ball);
    hitbox->height = al_get_bitmap_height(ball);
    xcenter = hitbox->width/2;
    ycenter = hitbox->height/2;
    hitbox->x = WIDTH - (xcenter*hitbox->scale);
    hitbox->y = HEIGHT - (ycenter*hitbox->scale);

}

Pendulo::~Pendulo()
{
    //dtor
}

void Pendulo::act(ALLEGRO_EVENT* ev)
{

}

void Pendulo::draw()
{
    al_draw_scaled_rotated_bitmap(thread, xcenterCuerda, ycenterCuerda, hitboxCuerda->x, hitboxCuerda->y,hitboxCuerda->scale,hitboxCuerda->scale,0, 0);

    al_draw_scaled_rotated_bitmap(ball, xcenter, ycenter, hitbox->x, hitbox->y,hitbox->scale,hitbox->scale,0, 0);
}
