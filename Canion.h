#include "Entidad.h"
#ifndef CANION_H
#define CANION_H

#include "Entidad.h"
#include "Bullet.h"
#include "Explosion.h"
#include <vector>

enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

class Canion : public Entidad
{
    public:
        Canion(ALLEGRO_EVENT_QUEUE *event_queue, list<Entidad *> *entidades);
        ALLEGRO_EVENT_QUEUE *event_queue;
        vector<ALLEGRO_BITMAP *> image;
        list<Entidad *> *entidades;
        Box *hitbox2;
        bool key[4] = { false, false, false, false};
        double angle;
        ALLEGRO_FONT *font;
        ALLEGRO_SAMPLE *shoot = NULL;
        ALLEGRO_SAMPLE_ID ishoot;

        virtual ~Canion();
        void act(ALLEGRO_EVENT *ev);
        void draw();
        void validarTeclas(ALLEGRO_EVENT* ev);
    protected:
    private:
};

#endif // CANION_H
