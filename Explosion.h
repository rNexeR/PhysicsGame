#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Entidad.h"

class Explosion : public Entidad
{
    public:
        int frame=0,tFrames, fActual;
        int time=0;
        bool destroied;
        vector<ALLEGRO_BITMAP *> image;

        void act(ALLEGRO_EVENT* ev);
        void draw();

        Explosion(double xpos, double ypos);
        Explosion(double xpos, double ypos, double scale);
        virtual ~Explosion();
    protected:
    private:
};

#endif // EXPLOSION_H
