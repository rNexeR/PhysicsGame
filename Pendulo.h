#ifndef PENDULO_H
#define PENDULO_H

#include "Entidad.h"

class Pendulo : public Entidad
{
    public:
        Pendulo();
        virtual ~Pendulo();

        ALLEGRO_BITMAP *ball,*thread;
        vector<ALLEGRO_BITMAP *> image;

        void act(ALLEGRO_EVENT* ev);
        void draw();

    protected:
    private:
};

#endif // PENDULO_H
