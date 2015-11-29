#include "Castle.h"

Castle::Castle() : Entidad()
{
    destroied=false;
    tipoObjeto = "Castle";
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
    hitbox->y = HEIGHT - (ycenter*hitbox->scale) - 15;

    cout<<"WIDTH: "<<WIDTH<<endl;
    cout<<"WIDTH castle: "<<hitbox->width<<endl;
    cout<<"x castle: "<<hitbox->x<<endl;
}

Castle::~Castle()
{
    //dtor
}

void Castle::act(ALLEGRO_EVENT* ev)
{
//    time++;
//    if(time%100==0)
//        hurt();
}

void Castle::hurt()
{
    if(frame<tFrames-1)
    {
        frame++;
    }else{
        destroied=true;
    }
}

void Castle::draw()
{
    //Dibuja el castillo en el frame actual
    al_draw_scaled_rotated_bitmap(image[frame], xcenter, ycenter, hitbox->x, hitbox->y,hitbox->scale,hitbox->scale,0, 0);

//    al_draw_filled_rectangle(hitbox->x, hitbox->y,hitbox->x+hitbox->width, hitbox->y + hitbox->height,al_map_rgb(150,0,0));
}
