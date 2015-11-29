#ifndef PENDULO_H
#define PENDULO_H

#include "Entidad.h"

class Pendulo : public Entidad
{
    public:
        Pendulo();
        virtual ~Pendulo();

        ALLEGRO_BITMAP *ball,*thread;
        Box *hitboxCuerda;
        double xcenterCuerda, ycenterCuerda, A,w,t,phi;
        float angle=0;
        int f=0,signo=1;

        void act(ALLEGRO_EVENT* ev);
        void draw();

    protected:
    private:
};

#endif // PENDULO_H
