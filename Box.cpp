#include "Box.h"

Box::Box(float x, float y, float width, float height, float scale)
{
    this -> x = x;
    this -> y = y;
    this -> width = width;
    this -> height = height;
    this->scale = scale;
}

Box::~Box()
{
    //dtor
}
