#include "Entidad.h"

Entidad::Entidad() : Entidad(new Box(0,0,0,0),1,"")
{

}

Entidad::Entidad(Box*b,float v,string t)
{
    hitbox=b;
    velocity=v;
    tipoObjeto=t;
}

Entidad::~Entidad()
{
    //dtor
}

//Detecta si el objeto está colisionando o no
bool Entidad::colision(Box* hitBox, Box* pCaja){
    if(pCaja->x + pCaja->width < hitBox->x
        || pCaja->x-5 > hitBox->x-5 + hitBox->width-5
        || pCaja->y-5 + pCaja->height-5 < hitBox->y-5
        || pCaja->y-5 > hitBox->y-5 + hitBox->height-5)
        return false;
    else
        return true;
}
