#include "Entidad.h"

Entidad::Entidad() : Entidad(new Box(0,0,0,0,1),1,"")
{

}

Entidad::Entidad(Box*b,float v,string t)
{
    readyToDelete = false;
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

//    cout<<"hitBox-x: "<<hitBox->x<<"hitBox-y: "<<hitBox->y<<endl;
//    cout<<"pCaja-x: "<<pCaja->x<<"pCaja-y: "<<pCaja->y<<endl;
    if(((pCaja->x + pCaja->width*pCaja->scale) < hitBox->x - hitBox->width*hitBox->scale/2 + 5)
    || ((hitBox->x + hitBox->width*hitBox->scale) < pCaja->x - pCaja->width*pCaja->scale/2 + 5)
    || ((pCaja->y + pCaja->height*pCaja->scale) < hitBox->y)
    || ((hitBox->y + hitBox->height*hitBox->scale) < pCaja->y))
    {
        return false;
    }
    return true;

//    if(pCaja->x + pCaja->width < hitBox->x
//        || pCaja->x-5 > hitBox->x-5 + hitBox->width-5
//        || pCaja->y-5 + pCaja->height-5 < hitBox->y-5
//        || pCaja->y-5 > hitBox->y-5 + hitBox->height-5)
//        return false;
//    else
//        return true;
}

//string Entidad::intToString(int number)
//{
//    if (number == 0)
//        return "0";
//    std::string temp="";
//    std::string returnvalue="";
//    while (number>0)
//    {
//        temp+=number%10+48;
//        number/=10;
//    }
//    for (int i=0; i<(int)temp.length(); i++)
//        returnvalue+=temp[temp.length()-i-1];
//    return returnvalue;
//}
