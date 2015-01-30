#pragma once

class Balle{
  public:
   Balle(int x, int y);
   ~Balle();
   void reset(int x, int y);
   void inverserVitesseH();
   void inverserVitesseV();
   void setXY(int x, int y);
   int getX();
   int getDX();
   int getXPrevious();
   int getY();
   int getDY();
   int getYPrevious();
   void bouger(); 
   void updatePositionPrevious();
  private:
   int x, xPrev, y, yPrev, dx, dy;
};
