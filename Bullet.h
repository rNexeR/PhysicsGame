#ifndef BULLET_H
#define BULLET_H
#include "Entidad.h"
#include "Explosion.h"
#include <ctime>


class Bullet : public Entidad
{
    public:
        Bullet(ALLEGRO_EVENT_QUEUE *event_queue, list<Entidad *> *entidades, float angle, float velocity, double xposition, double yposition);
        ALLEGRO_EVENT_QUEUE *event_queue;
        ALLEGRO_BITMAP *image;
        list<Entidad *> *entidades;
        double angle, degree, vox, voy, xo, yo, tiempo;
        vector<float> x_axis,y_axis;
        float r=0.5;
        bool checked;
        virtual ~Bullet();
        void init(float xposition, float yposition, float velocity, float angle);
        void act(ALLEGRO_EVENT *ev);
        void draw();
    protected:
    private:
};

#endif // BULLET_H
