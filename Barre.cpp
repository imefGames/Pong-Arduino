#include "Barre.h"

Barre::Barre(int y){
  Barre::y = y;
  Barre::yPrev = y;
}

Barre::~Barre(){
  
}

void Barre::allerHaut(){
  Barre::y -= 4;
}

void Barre::allerBas(){
  Barre::y += 4;
}

int Barre::getY(){
  return Barre::y;
}

void Barre::setY(int y){
  Barre::y = y;
}

int Barre::getYPrevious(){
  return Barre::yPrev;
}

void Barre::updateYPrevious(){
  Barre::yPrev = Barre::y;
}
