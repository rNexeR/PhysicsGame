#include "Pendulo.h"

Pendulo::Pendulo() : Entidad()
{
    tipoObjeto = "Pendulo";
    checked=false;
    f=0;
    angle=0;
    signo=1;

    ball = al_load_bitmap("Assets/EsferaM.png");
    thread = al_load_bitmap("Assets/varillametal.png");

    hitboxCuerda = new Box(0,0,0,0,1);
    hitboxCuerda->scale = 0.5;
    hitboxCuerda->width = al_get_bitmap_width(thread);
    hitboxCuerda->height = al_get_bitmap_height(thread);
    xcenterCuerda = hitboxCuerda->width/2;
    ycenterCuerda = 0;//hitboxCuerda->height/2;
    hitboxCuerda->x = WIDTH/2 - (xcenterCuerda*hitboxCuerda->scale);
    hitboxCuerda->y = 0;

    cout<<"r: "<<hitboxCuerda->height*hitboxCuerda->scale/2<<endl;
    t=0;
    A=hitboxCuerda->height*hitboxCuerda->scale/2;
    w=0.2491451;//0.098245614;//0.313441564;
    phi=PI/2;
    angle=PI/2;

    hitbox->scale = 0.15;
    hitbox->width = al_get_bitmap_width(ball);
    hitbox->height = al_get_bitmap_height(ball);
    xcenter = hitbox->width/2;
    ycenter = hitbox->height/2;
    hitbox->x = hitboxCuerda->x - 2*A*cos(t*PI/180);//(xcenter*hitbox->scale) + xcenterCuerda/4-A*100;
    hitbox->y = 2*A*sin(t*PI/180);

}

Pendulo::~Pendulo()
{
    delete hitbox;
    delete hitboxCuerda;
    delete ball;
    delete thread;
}

void Pendulo::act(ALLEGRO_EVENT* ev)
{
    f++;
    t+=0.07;
//    angle -= signo*PI/180;
    angle = atan2((-hitbox->y),(WIDTH/2 - (hitbox->x + hitbox->width*hitbox->scale/2 + signo*hitboxCuerda->width*hitboxCuerda->scale/8))) + PI/2;
    hitbox->x = hitboxCuerda->x + 2*A*sin((w*t - phi));
    hitbox->y = signo*2*A*cos((w*t - phi));

//    angle = 4*atan((WIDTH/2 - hitbox->x)/(HEIGHT - hitbox->y));

    if(hitbox->y<0)//(f%180==0)
    {
        signo*=-1;
    }
}

void Pendulo::draw()
{
    if(!checked)
    {
        al_draw_scaled_rotated_bitmap(thread, xcenterCuerda, ycenterCuerda, hitboxCuerda->x, hitboxCuerda->y,hitboxCuerda->scale,hitboxCuerda->scale,angle, 0);

        al_draw_scaled_rotated_bitmap(ball, xcenter, ycenter, hitbox->x, hitbox->y,hitbox->scale,hitbox->scale,angle, 0);
    }
//    if(checked)
//        al_draw_filled_rectangle(hitboxCuerda->x,hitboxCuerda->y, hitboxCuerda->x + hitboxCuerda->width*hitboxCuerda->scale, hitboxCuerda->y + hitboxCuerda->height*hitboxCuerda->scale, al_map_rgb(0,250,0));
//    al_draw_filled_rectangle(hitboxCuerda->x,hitboxCuerda->y, hitboxCuerda->width*hitboxCuerda->scale, hitboxCuerda->height*hitboxCuerda->scale, al_map_rgb(0,200,0));
}
