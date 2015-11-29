#include "Pendulo.h"

Pendulo::Pendulo()
{
    ball = al_load_bitmap("Assets/balaRedonda.png");
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
    al_draw_scaled_rotated_bitmap(ball, 0, 0, 0, 0,1,1, 0, 0);
}
