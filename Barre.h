#pragma once

class Barre{
  public:
   Barre(int y);
   ~Barre();
   void allerHaut();
   void allerBas();
   int getY();
   void setY(int y);
   int getYPrevious();
   void updateYPrevious();
  private:
   int y, yPrev;
};
