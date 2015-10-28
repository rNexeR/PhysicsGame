#include <iostream>
#include <stdio.h>
#include <iostream>
using namespace std;

//LIBRERIAS DE ALLEGRO
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

const float FPS = 60;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;

//EVENTOS Y TIMERS
ALLEGRO_EVENT ev;
ALLEGRO_TIMEOUT timeout;
ALLEGRO_TIMER *timer = NULL;

int width = 1000, height = 450;
int initAllegro();

int main()
{
    if(initAllegro() != 0)
        return -1;


    while(true){
        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
        if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        al_clear_to_color(al_map_rgb(0,200,0));
        al_flip_display();
    }

    cout<<"---- Fin del Programa ----"<<endl;
    return 0;
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

    display = al_create_display(width, height);
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

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon

    al_register_event_source(event_queue, al_get_display_event_source(display));//registrar eventos del display
    al_register_event_source(event_queue, al_get_timer_event_source(timer));//registrar eventos del timer
    al_register_event_source(event_queue, al_get_keyboard_event_source());//registrar eventos del teclado

    al_init_timeout(&timeout, 0.06);
    return 0;
}
