#include <iostream>
using namespace std;

//LIBRERIAS DE ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Canion.h"
#include "Entidad.h"
#include "Castle.h"

using namespace std;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;

//EVENTOS Y TIMERS
ALLEGRO_EVENT ev;
ALLEGRO_TIMEOUT timeout;
ALLEGRO_TIMER *timer = NULL;

ALLEGRO_SAMPLE *game = NULL;
ALLEGRO_SAMPLE_ID igame;

int initAllegro();
bool checkCollicion(Castle *castle,Entidad*bullet);
int Entidad::bullet_count = 0;
int main()
{

    if(initAllegro() != 0)
        return -1;

    Castle *castle = new Castle();
    list<Entidad*> *entidades = new list<Entidad*>();
    vector<list<Entidad*>::iterator>borrar;
    entidades->push_back(new Canion(event_queue, entidades));
    entidades->push_back(castle);

    while(true)
    {
        al_play_sample(game, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &igame);
        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
        if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        al_clear_to_color(al_map_rgb(0,200,0));

        for(list<Entidad*>::iterator i = entidades->begin(); i != entidades->end(); i++)
        {
            (*i)->act(&ev);
            (*i)->draw();

            if((*i)->tipoObjeto!="Castle" && (*i)->tipoObjeto!="Canion")
            {
                if((((Bullet*)(*i))->checked==false) && checkCollicion(castle,*i))
                {
                    ((Bullet*)(*i))->checked=true;
                    ((Bullet*)(*i))->init((*i)->hitbox->x,HEIGHT - (*i)->hitbox->y,-((Bullet*)(*i))->velocity,0.1);
//                   ((Bullet*)(*i))->vo = -0.5;
//                   ((Bullet*)(*i))->vo = -0.5;//-(((Bullet*)(*i))->vox);
//                    borrar.push_back(i);
//                    break;
                }
            }

            if((*i)->hitbox->x > WIDTH || (*i)->hitbox->y > HEIGHT)
                borrar.push_back(i);

        }

        for(int x = 0; x < borrar.size(); x++){
            delete((*borrar[x]));
            entidades->erase(borrar[x]);
        }
        borrar.clear();
        al_flip_display();
    }


    al_stop_sample(&igame);
    cout<<"---- Fin del Programa ----"<<endl;
    return 0;
}

bool checkCollicion(Castle *castle,Entidad*bullet)
{
    if(castle->colision(castle->hitbox,bullet->hitbox))
    {
        castle->hurt();
        return true;
    }
    return false;
}

/**
    Inicialización de las funciones de Allegro
**/
int initAllegro()
{
    if(!al_init())
    {
        cout<<"failed to initialize allegro!\n"<<endl;
        return -1;
    }

    if(!al_init_image_addon())
    {
        cout<<"Error: Failed to initialize al_init_image_addon!"<<endl;
        return -1;
    }

    display = al_create_display(WIDTH, HEIGHT);
    if(!display)
    {
        cout<<"failed to create display!\n"<<endl;
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        cout<<"failed to create event_queue!\n"<<endl;
        al_destroy_display(display);
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        cout<<"failed to create timer!"<<endl;
    }

    if(!al_install_keyboard())
    {
        cout<<"failed to initialize the keyboard!"<<endl;
    }

    if(!al_install_audio() || !al_init_acodec_addon() || !al_reserve_samples(2))
    {
        cout<<"failed to initialize Audio!"<<endl;
    }

    if(!al_install_audio() || !al_init_acodec_addon() || !al_reserve_samples(2))
    {
        cout<<"failed to initialize Audio!"<<endl;
    }

    game = al_load_sample("FiveHoursOriginalMixtonoku.wav");

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon

    al_register_event_source(event_queue, al_get_display_event_source(display));//registrar eventos del display
    al_register_event_source(event_queue, al_get_timer_event_source(timer));//registrar eventos del timer
    al_register_event_source(event_queue, al_get_keyboard_event_source());//registrar eventos del teclado

    al_init_timeout(&timeout, 0.06);
    return 0;
}
