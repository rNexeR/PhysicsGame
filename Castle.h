#ifndef CASTLE_H
#define CASTLE_H
#include "Entidad.h"

class Castle : public Entidad
{
    public:
        Castle();
        virtual ~Castle();

        int frame=0,tFrames;
        int time=0;
        bool destroied;
        vector<ALLEGRO_BITMAP *> image;

        void hurt();

        void act(ALLEGRO_EVENT* ev);
        void draw();
    protected:
    private:
};

#endif // CASTLE_H
