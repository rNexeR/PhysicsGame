#include "Bullet.h"

Bullet::Bullet(ALLEGRO_EVENT_QUEUE *event_queue, list<Entidad *> *entidades, float angle, float velocity, double xposition, double yposition) : Entidad()
{
    this->event_queue = event_queue;

    init(xposition,yposition,velocity, angle);
    this->checked = false;

    cout<<"Angulo: "<<angle<<endl;

    tipoObjeto = "Bullet";
    tiempo = 0;

    //Aqui va mas programacion :D
    this->entidades = entidades;
    image = al_load_bitmap("Assets/Bala.png");
    hitbox->width = al_get_bitmap_width(image);
    hitbox->height = al_get_bitmap_height(image);
    xcenter = hitbox->width/2;
    ycenter = hitbox->height/2;
    hitbox->scale = 0.035;
    hitbox->x = 0;
    hitbox->y = HEIGHT - (hitbox->height * hitbox->scale /2);
//    this->bullet_count++;
    this->bullet_actual = 1;
}

Bullet::~Bullet()
{

    cout<<"Distancia Final: "<<hitbox->x<<" m"<<endl;
    bullet_actual = 0;
    al_destroy_bitmap(image);
    delete(hitbox);
}

void Bullet::init(float xposition, float yposition, float velocity, float angle)
{
//    tiempo = 0;

    this->velocity = velocity;
    this->angle = angle;

    this->xo = xposition;
    this->yo = yposition;
    this->vox = this->velocity*cos(this->angle);
    this->voy = this->velocity*sin(this->angle);
}

void Bullet::act(ALLEGRO_EVENT *ev){
    degree+=PI/6;
    tiempo += 0.07;
    hitbox->x = xo + vox*tiempo;
    hitbox->y = HEIGHT - (yo + voy*tiempo - (0.5*GRAVITY*tiempo*tiempo));
}

void Bullet::draw(){
    al_draw_scaled_rotated_bitmap(image, xcenter, ycenter, hitbox->x, hitbox->y,hitbox->scale,hitbox->scale, degree, 0);
}
