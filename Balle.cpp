#include "Balle.h"
  
Balle::Balle(int x, int y){
  Balle::reset(x, y);
}

Balle::~Balle(){
  
}

void Balle::reset(int x, int y){
  Balle::x = x;
  Balle::y = y;
  Balle::xPrev = x;
  Balle::yPrev = y;
  Balle::dx = 4;
  Balle::dy = 4;
}

void Balle::inverserVitesseH(){
  Balle::dx *= -1;
}

void Balle::inverserVitesseV(){
  Balle::dy *= -1;
}

void Balle::setXY(int x, int y){
  Balle::x = x;
  Balle::y = y;
}

int Balle::getX(){
  return Balle::x;
}

int Balle::getDX(){
  return Balle::dx;
}

int Balle::getXPrevious(){
  return Balle::xPrev;
}

int Balle::getY(){
  return Balle::y;
}

int Balle::getDY(){
  return Balle::dy;
}

int Balle::getYPrevious(){
  return Balle::yPrev;
}

void Balle::bouger(){
  Balle::x += Balle::dx;
  Balle::y += Balle::dy;
}

void Balle::updatePositionPrevious(){
  Balle::xPrev = Balle::x;
  Balle::yPrev = Balle::y;
}
