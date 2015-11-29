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
#include "Pendulo.h"
#include "Entidad.h"
#include "Castle.h"

using namespace std;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;

//EVENTOS Y TIMERS
ALLEGRO_EVENT ev;
ALLEGRO_TIMEOUT timeout;
ALLEGRO_TIMER *timer = NULL;

ALLEGRO_BITMAP *bg1, *bg2;

ALLEGRO_SAMPLE *game = NULL, *effect = NULL;
ALLEGRO_SAMPLE_ID igame, ieffect;

int initAllegro();
bool checkCollicion(Castle *castle,Entidad*bullet);
int Entidad::bullet_count = 0;
int Entidad::bullet_max = 4;
int Entidad::bullet_actual = 0;
int main()
{

    if(initAllegro() != 0)
        return -1;

    Castle *castle = new Castle();
    Pendulo *pendulo = new Pendulo();
    list<Entidad*> *entidades = new list<Entidad*>();
    vector<list<Entidad*>::iterator>borrar;
    entidades->push_back(new Canion(event_queue, entidades));
    entidades->push_back(castle);
    entidades->push_back(pendulo);

    al_play_sample(game, 0.7, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &igame);
    while(true)
    {
        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
        if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        al_clear_to_color(al_map_rgb(0,200,0));

        al_draw_bitmap(bg1, 0, 0, 0);
        for(list<Entidad*>::iterator i = entidades->begin(); i != entidades->end(); i++)
        {
            (*i)->act(&ev);
            (*i)->draw();

            //if((*i)->tipoObjeto!="Castle" && (*i)->tipoObjeto!="Canion" && (*i)->tipoObjeto!="Pendulo" && (*i)->tipoObjeto!="Explosion")
            if((*i)->tipoObjeto=="Bullet")
            {
                if((((Bullet*)(*i))->checked==false) && checkCollicion(castle,*i))
                {
                    //((Bullet*)(*i))->checked=true;
                    //((Bullet*)(*i))->init((*i)->hitbox->x,HEIGHT - (*i)->hitbox->y,-((Bullet*)(*i))->velocity/8,0.1);
                    entidades->push_back(new Explosion((*i)->hitbox->x, (*i)->hitbox->y, 1));
                    al_play_sample(effect, 0.5, 0.0, 4.0, ALLEGRO_PLAYMODE_ONCE, &ieffect);
                    borrar.push_back(i);
                }
            }

            if((*i)->hitbox->x > WIDTH || (*i)->hitbox->y > HEIGHT || ( (*i)->tipoObjeto == "Explosion" ) && (((Explosion*)(*i))->destroied))
                borrar.push_back(i);

        }

        for(int x = 0; x < borrar.size(); x++){
            delete((*borrar[x]));
            entidades->erase(borrar[x]);
        }
        borrar.clear();
        al_draw_bitmap(bg2, 0, 0, 0);
        al_flip_display();
    }

    al_destroy_bitmap(bg1);
    al_destroy_bitmap(bg2);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_sample(game);
    al_destroy_sample(effect);
    //al_stop_sample(&igame);
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

    if(!al_install_audio() || !al_init_acodec_addon() || !al_reserve_samples(5))
    {
        cout<<"failed to initialize Audio!"<<endl;
    }

    if(!al_install_audio() || !al_init_acodec_addon() || !al_reserve_samples(5))
    {
        cout<<"failed to initialize Audio!"<<endl;
    }

    game = al_load_sample("Szymon Matuszewski - Space Chase.ogg");
    effect = al_load_sample("explosion.ogg");

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon

    al_register_event_source(event_queue, al_get_display_event_source(display));//registrar eventos del display
    al_register_event_source(event_queue, al_get_timer_event_source(timer));//registrar eventos del timer
    al_register_event_source(event_queue, al_get_keyboard_event_source());//registrar eventos del teclado

    al_init_timeout(&timeout, 0.06);

    bg1 = al_load_bitmap("Assets/bg1.jpg");
    bg2 = al_load_bitmap("Assets/bg2.png");
    return 0;
}
