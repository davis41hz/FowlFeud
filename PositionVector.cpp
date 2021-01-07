#include "PositionVector.h"

PositionVector::PositionVector(int x, int y){
    position = {x, y};
}

PositionVector::~PositionVector() {}

void PositionVector::multiply(int x){
    position.x = position.x * x;
    position.y = position.y * x;
}

void PositionVector::multiply(PositionVector * pvect){
    position.x = pvect->getX() * position.x;
    position.y = pvect->getY() * position.y;
}

void PositionVector::add(PositionVector * pvect){
    position.x = pvect->getX() + position.x;
    position.y = pvect->getY() + position.y;
}

void PositionVector::subtract(PositionVector * pvect){
    position.x = position.x - pvect->getX();
    position.y = position.y - pvect->getY();
}

void PositionVector::divide(PositionVector * pvect){
    // rounding using floor
    position.x = floor((position.x / pvect->getX()) + 0.5);
    position.y = floor((position.y / pvect->getY()) + 0.5);
}

void PositionVector::divide(int x){
    // rounding using floor
    position.x = floor((position.x / x) + 0.5);
    position.y = floor((position.y / x) + 0.5);
}

void PositionVector::setX(int x){
    position.x = x;
}

void PositionVector::setY(int y){
    position.y = y;
}

int PositionVector::getX(){
    return position.x;
}

int PositionVector::getY(){
    return position.y;
}
