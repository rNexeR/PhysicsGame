#include "Canion.h"

Canion::Canion(ALLEGRO_EVENT_QUEUE *event_queue, list<Entidad *> *entidades) : Entidad()
{
    shoot = al_load_sample("canion.ogg");
    this->event_queue = event_queue;
    this->entidades = entidades;
    velocity = 80;
    angle = 0;
    tipoObjeto = "Canion";

    //Aqui va mas programacion :D
    //image = new vector<ALLEGRO_BITMAP*>();

    hitbox2 = new Box(0,0,0,0,0);
    image.push_back(al_load_bitmap("Assets/canon_rueda.png"));
    image.push_back(al_load_bitmap("Assets/canon_base.png"));
    hitbox->scale = 0.1;
    hitbox2->scale = 0.1;
    hitbox->width = al_get_bitmap_width(image[0]);
    hitbox->height = al_get_bitmap_height(image[0]);

    hitbox2->width = al_get_bitmap_width(image[1]);
    hitbox2->height = al_get_bitmap_height(image[1]);

    xcenter = hitbox->width/2;
    ycenter = hitbox->height/2;
    hitbox->x = 30 + (hitbox->width*hitbox->scale/2);
    hitbox->y = HEIGHT - (hitbox->height*hitbox->scale /2) - 15;

    hitbox2->x = hitbox->x;
    hitbox2->y = hitbox->y - hitbox->height*hitbox->scale + 250*hitbox2->scale;

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon

    font = al_load_ttf_font("kenvector_future_thin.ttf",20,0 );

}

Canion::~Canion()
{
    al_destroy_bitmap(image[0]);
    al_destroy_bitmap(image[1]);
    al_destroy_sample(shoot);
    delete(hitbox);
}

void Canion::act(ALLEGRO_EVENT *ev){
    validarTeclas(ev);
    if(key[KEY_UP])
        angle -= PI/1000;
    if(key[KEY_DOWN])
        angle += PI/1000;
    if(key[KEY_RIGHT] && velocity <= 148)
        velocity += 0.05;
    if(key[KEY_LEFT] && velocity >= 2)
        velocity -= 0.05;
    if(ev->type == ALLEGRO_EVENT_KEY_DOWN && ev->keyboard.keycode == ALLEGRO_KEY_SPACE && this->bullet_actual == 0 && this->bullet_count < this->bullet_max){
        int xbullet = hitbox2->x + hitbox2->width/2*cos(angle)*hitbox2->scale;
        int ybullet = HEIGHT - (hitbox2->y + (hitbox2->width/2*sin(angle)*hitbox2->scale));
        entidades->push_back(new Bullet(event_queue, entidades, -1*angle, velocity, xbullet, ybullet));
        entidades->push_back(new Explosion(xbullet, HEIGHT - ybullet));
        al_play_sample(shoot, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &ishoot);
    }
    if(angle < -PI/2)
        angle = -PI/2;
    if(angle > 0)
        angle = 0;
    if(velocity < 0)
        velocity = 0;
}

void Canion::validarTeclas(ALLEGRO_EVENT* ev)
{
    if(ev->type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch(ev->keyboard.keycode)
        {
        case ALLEGRO_KEY_W:
            key[KEY_UP] = true;
            break;

        case ALLEGRO_KEY_S:
            key[KEY_DOWN] = true;
            break;

        case ALLEGRO_KEY_A:
            key[KEY_LEFT] = true;
            break;

        case ALLEGRO_KEY_D:
            key[KEY_RIGHT] = true;
            break;
        }

    }
    if(ev->type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(ev->keyboard.keycode)
        {
        case ALLEGRO_KEY_W:
            key[KEY_UP] = false;
            break;

        case ALLEGRO_KEY_S:
            key[KEY_DOWN] = false;
            break;

        case ALLEGRO_KEY_A:
            key[KEY_LEFT] = false;
            break;

        case ALLEGRO_KEY_D:
            key[KEY_RIGHT] = false;
            break;
        }
    }
}


void Canion::draw(){
    string mostrar = "velocity: " + intToString(velocity) + " m/s";
    al_draw_text(font, al_map_rgb(255,255,255), 0, 0, ALLEGRO_ALIGN_LEFT, mostrar.c_str());
    mostrar = "angle: " + intToString(angle*-1*180/PI) + " deg";
    al_draw_text(font, al_map_rgb(255,255,255), 0, 20, ALLEGRO_ALIGN_LEFT, mostrar.c_str());
    mostrar = "max bullets: " + intToString(this->bullet_max);
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH, 0, ALLEGRO_ALIGN_RIGHT, mostrar.c_str());
    mostrar = "disponibles: " + intToString(this->bullet_max - this->bullet_count);
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH, 20, ALLEGRO_ALIGN_RIGHT, mostrar.c_str());

    //Dibujar el canon
    //cout<<"HITBOX 2 Y: "<<hitbox2->y<<endl;
    al_draw_scaled_rotated_bitmap(image[1], hitbox2->width/2, hitbox2->height/2, hitbox2->x, hitbox2->y,hitbox2->scale,hitbox2->scale, angle, 0);

    //Dibujar la rueda
    al_draw_scaled_rotated_bitmap(image[0], xcenter, ycenter, hitbox->x, hitbox->y,hitbox->scale,hitbox->scale, 0, 0);
}
