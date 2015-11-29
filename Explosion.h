#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Entidad.h"

class Explosion : public Entidad
{
    public:
        int frame=0,tFrames;
        int time=0;
        bool destroied;
        vector<ALLEGRO_BITMAP *> image;

        Explosion();
        virtual ~Explosion();
    protected:
    private:
};

#endif // EXPLOSION_H
