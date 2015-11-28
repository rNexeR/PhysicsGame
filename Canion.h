#ifndef CANION_H
#define CANION_H

#include "Entidad.h"

class Canion : public Entidad
{
    public:
        Canion(ALLEGRO_EVENT_QUEUE *event_queue, list<Entidad *> *entidades);
        ALLEGRO_EVENT_QUEUE *event_queue;
        ALLEGRO_BITMAP *image;
        list<Entidad *> *entidades;
        double angle;
        virtual ~Canion();
        void act(ALLEGRO_EVENT *ev);
        void draw();
    protected:
    private:
};

#endif // CANION_H
