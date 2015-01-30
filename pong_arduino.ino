/* Arduino Due VGA-Out v0.2 by stimmer
http://arduino.cc/forum/index.php/topic,130742.0.html */

#include "Barre.h"
#include "Balle.h"

inline void digitalWriteDirect(int pin, boolean val){
  if(val) g_APinDescription[pin].pPort -> PIO_SODR = g_APinDescription[pin].ulPin;
  else    g_APinDescription[pin].pPort -> PIO_CODR = g_APinDescription[pin].ulPin;
}

volatile short line;
byte fb[240][320];

#define do20(x) x x x x x x x x x x x x x x x x x x x x
#define do80(x)  do20(x) do20(x) do20(x) do20(x) 
#define do320(x) do80(x) do80(x) do80(x) do80(x) 
#define MNOP(x) asm volatile (" .rept " #x "\n\t nop \n\t .endr \n\t")

#define BLACK B00000000
#define WHITE B11111111
#define RED B11100000
#define GREEN B00011100
#define BLUE B00000011
#define YELLOW B11111100
#define PURPLE B11100011
#define CYAN B00011111

void TC0_Handler()
{
    long dummy=REG_TC0_SR0; 
                           
    if(line < 480){        
        byte * p=fb[line>>1];
        MNOP(160);
        do320(REG_PIOD_ODSR = *p++;MNOP(2);)
        REG_PIOD_ODSR = 0;
    }      
    if(line==490) digitalWriteDirect(3,1); //or digitalWriteDirect(3,0); to invert vsync
    if(line==492) digitalWriteDirect(3,0); //or digitalWriteDirect(3,1); to invert vsync
    
    line++; if(line == 525) line=0;
}


/*************
Draw Functions
*************/
void drawPoint(int x, int y, byte color){
  fb[y][x]=color;
}

void drawRect(int x1, int y1, int x2, int y2, byte color){
  for(int i=x1;i<x2;i++)for(int j=y1;j<y2;j++)fb[j][i]=color;
}

void drawCircle(int x, int y, int r, byte color){
  for(int i=x-r;i<x+r;i++)for(int j=y-r;j<y+r;j++){
    if((x-i)*(x-i) + (y-j)*(y-j) < r*r){ fb[j][i]=color; }
  }
}

void drawNum(int x, int y, byte n){
  switch(n){
    case 0:
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y+5, x+10, y+20, BLACK);
      break;
    case 1:
      drawRect(x+5, y, x+10, y+25, WHITE);
      break;
    case 2:
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x, y+5, x+10, y+10, BLACK);
      drawRect(x+5, y+15, x+15, y+20, BLACK);
      break;
    case 3:
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x, y+5, x+10, y+20, BLACK);
      drawRect(x+5, y+10, x+10, y+15, WHITE);
      break;
    case 4:
      drawRect(x+10, y, x+15, y+25, WHITE);
      drawRect(x, y, x+10, y+15, WHITE);
      drawRect(x+5, y, x+10, y+10, BLACK);
      break;
    case 5:
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y+5, x+15, y+10, BLACK);
      drawRect(x, y+15, x+10, y+20, BLACK);
      break;
    case 6:
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y+5, x+15, y+10, BLACK);
      drawRect(x+5, y+15, x+10, y+20, BLACK);
      break;
    case 7:
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x, y+5, x+10, y+25, BLACK);
      break;
    case 8:
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y+5, x+10, y+10, BLACK);
      drawRect(x+5, y+15, x+10, y+20, BLACK);
      break;
    case 9:
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y+5, x+10, y+10, BLACK);
      drawRect(x, y+15, x+10, y+20, BLACK);
      break;
  }
}

void drawNumber(int x, int y, int n){
  int dx = 0, maxn = 1, tmp;
  if(n == 0 || n == 1){
    drawNum(x, y, n);
  }else{
    while(maxn<=n){
      maxn*=10;
    }
    while(maxn>1){
      maxn/=10;
      tmp = n-(n%maxn);
      drawNum(x+dx, y, tmp/maxn);
      n -= tmp;
      dx+=20;
    }
  }
}

void drawLetter(int x, int y, char c){
  switch(c){
    case 'a':
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y+5, x+10, y+10, BLACK);
      drawRect(x+5, y+15, x+10, y+25, BLACK);
      break;
    case 'b':
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y+5, x+10, y+10, BLACK);
      drawRect(x+5, y+15, x+10, y+20, BLACK);
      drawRect(x+10, y+10, x+15, y+15, BLACK);
      break;
    case 'c':
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y+5, x+15, y+20, BLACK);
      break;
    case 'd':
      drawRect(x, y, x+10, y+25, WHITE);
      drawRect(x+5, y+5, x+10, y+20, BLACK);
      drawRect(x+10, y+5, x+15, y+20, WHITE);
      break;
    case 'e':
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y+5, x+15, y+20, BLACK);
      drawRect(x+5, y+10, x+10, y+15, WHITE);
      break;
    case 'f':
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y+5, x+15, y+25, BLACK);
      drawRect(x+5, y+10, x+10, y+15, WHITE);
      break;
    case 'g':
      drawRect(x, y, x+20, y+25, WHITE);
      drawRect(x+5, y+5, x+20, y+20, BLACK);
      drawRect(x+10, y+10, x+25, y+15, WHITE);
      drawRect(x+15, y+15, x+20, y+20, WHITE);
      break;
    case 'h':
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y, x+10, y+10, BLACK);
      drawRect(x+5, y+15, x+10, y+25, BLACK);
      break;
    case 'i':
      drawRect(x, y, x+15, y+5, WHITE);
      drawRect(x+5, y+5, x+10, y+20, WHITE);
      drawRect(x, y+20, x+15, y+25, WHITE);
      break;
    case 'j':
      drawRect(x, y, x+15, y+5, WHITE);
      drawRect(x+5, y+5, x+10, y+20, WHITE);
      drawRect(x, y+20, x+10, y+25, WHITE);
      break;
    case 'k':
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y, x+10, y+10, BLACK);
      drawRect(x+5, y+15, x+10, y+25, BLACK);
      drawRect(x+10, y+10, x+15, y+15, BLACK);
      break;
    case 'l':
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y, x+15, y+20, BLACK);
      break;
    case 'm':
      drawRect(x, y, x+25, y+25, WHITE);
      drawRect(x+5, y, x+20, y+25, BLACK);
      drawRect(x+5, y+5, x+10, y+10, WHITE);
      drawRect(x+10, y+10, x+15, y+15, WHITE);
      drawRect(x+15, y+5, x+20, y+10, WHITE);
      break;
    case 'n':
      drawRect(x, y, x+25, y+25, WHITE);
      drawRect(x+5, y, x+20, y+25, BLACK);
      drawRect(x+5, y+5, x+10, y+10, WHITE);
      drawRect(x+10, y+10, x+15, y+15, WHITE);
      drawRect(x+15, y+15, x+20, y+20, WHITE);
      break;
    case 'o':
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y+5, x+10, y+20, BLACK);
      break;
    case 'p':
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y+5, x+10, y+10, BLACK);
      drawRect(x+5, y+15, x+15, y+25, BLACK);
      break;
    case 'q':
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y+5, x+10, y+10, BLACK);
      drawRect(x, y+15, x+10, y+25, BLACK);
      break;
    case 'r':
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y+5, x+10, y+15, BLACK);
      drawRect(x+5, y+20, x+15, y+25, BLACK);
      drawRect(x+10, y+15, x+15, y+20, BLACK);
      drawRect(x+10, y+20, x+15, y+25, WHITE);
      break;
    case 's':
      drawRect(x, y, x+15, y+25, WHITE);
      drawRect(x+5, y+5, x+15, y+10, BLACK);
      drawRect(x, y+15, x+10, y+20, BLACK);
      break;
    case 't':
      drawRect(x, y, x+15, y+5, WHITE);
      drawRect(x+5, y+5, x+10, y+25, WHITE);
      break;
    case 'u':
      drawRect(x, y, x+5, y+25, WHITE);
      drawRect(x+10, y, x+15, y+25, WHITE);
      drawRect(x, y+20, x+15, y+25, WHITE);
      break;
    case 'v':
      drawRect(x, y, x+5, y+20, WHITE);
      drawRect(x+10, y, x+15, y+20, WHITE);
      drawRect(x+5, y+20, x+10, y+25, WHITE);
      break;
    case 'w':
      drawRect(x, y, x+5, y+25, WHITE);
      drawRect(x+20, y, x+25, y+25, WHITE);
      drawRect(x+5, y+15, x+10, y+20, WHITE);
      drawRect(x+15, y+15, x+20, y+20, WHITE);
      drawRect(x+10, y+10, x+15, y+15, WHITE);
      break;
    case 'x':
      drawRect(x, y, x+5, y+25, WHITE);
      drawRect(x+10, y, x+15, y+25, WHITE);
      drawRect(x, y+10, x+5, y+15, BLACK);
      drawRect(x+10, y+10, x+15, y+15, BLACK);
      drawRect(x+5, y+10, x+10, y+15, WHITE);
      break;
    case 'y':
      drawRect(x, y, x+5, y+10, WHITE);
      drawRect(x+5, y+10, x+10, y+15, WHITE);
      drawRect(x+10, y, x+15, y+20, WHITE);
      drawRect(x+5, y+20, x+10, y+25, WHITE);
      break;
    case 'z':
      drawRect(x, y, x+15, y+5, WHITE);
      drawRect(x, y+20, x+15, y+25, WHITE);
      drawRect(x+10, y+5, x+15, y+10, WHITE);
      drawRect(x, y+15, x+5, y+20, WHITE);
      drawRect(x+5, y+10, x+10, y+15, WHITE);
      break;
    }
}

void drawText(int x, int y, String str){
  int dx = 0, i;
  for(i=0; i<str.length(); i++){
    if(str[i] == ' '){
      dx+=20;
    }else{
      drawLetter(x+dx, y, str[i]);
      dx+=20;
      if(str[i] == 'g' || str[i] == 'm' || str[i] == 'n' || str[i] == 'w'){
        dx+=10;
      }
    }
  }
}

void drawHearts(int x, int y, int n){
  int i;
  for(i=0; i<n; i++){
    drawRect(x+2, y, x+4, y+2, WHITE);
    drawRect(x+6, y, x+8, y+2, WHITE);
    drawRect(x, y+2, x+10, y+6, WHITE);
    drawRect(x+2, 6, x+8, y+8, WHITE);
    drawRect(x+4, y+8, x+6, y+10, WHITE);
    x+=12;
  }
}

void screenColor(byte col){
  drawRect(0, 0, 320, 240, col);
}

/**************
Sound Functions
**************/
void playSound(int n){
  int pin;
  switch(n){
    case 0:
      pin = 33;
      break;
    case 1:
      pin = 35;
      break;
    case 2:
      pin = 37;
      break;
  }
  digitalWrite(pin, HIGH);
  delay(10);
  digitalWrite(pin, LOW);
}

/****
Score
****/
typedef struct{
  String name;
  int score;
}score;

score HS[6];

/*************
Setup Function
*************/
void setup(){
  screenColor(BLACK);
  menuStart();
  int i;
  for(i=3; i<6; i++){
    HS[i].score = (6-i)*100;
  }
  HS[0].name = "ant";
  HS[0].score = 1000;
  HS[1].name = "ala";
  HS[1].score = 750;
  HS[2].name = "pim";
  HS[2].score = 500;
  HS[3].name = "bbb";
  HS[4].name = "ccc";
  HS[5].name = "ddd";
  
  pinMode(3,OUTPUT);  pinMode(2,OUTPUT);                      // vsync=3 hsync=2
  pinMode(25,OUTPUT); pinMode(26,OUTPUT);                     // blue  (26=msb,25=lsb)
  pinMode(27,OUTPUT); pinMode(28,OUTPUT); pinMode(14,OUTPUT); // green (14=msb,28,27=lsb)
  pinMode(15,OUTPUT); pinMode(29,OUTPUT); pinMode(11,OUTPUT); // red   (11=msb,29,15=lsb)
  
  //sons
  pinMode(33, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(37, OUTPUT);
  
  pinMode(50, INPUT); //down
  pinMode(51, INPUT); //up
  pinMode(46, INPUT); //bt1
  
  REG_PIOD_OWER= 0xff;
  REG_PMC_PCER0= 1<<27;  
  REG_PIOB_PDR = 1<<25; 
  REG_PIOB_ABSR= 1<<25; 
  REG_TC0_WPMR = 0x54494D00; 
  REG_TC0_CMR0 = 0b00000000000010011100010000000000;
//  REG_TC0_CMR0 = 0b00000000000001101100010000000000; // this inverts hsync
  REG_TC0_RC0  = 1334; 
  REG_TC0_RA0  = 1174;  
  REG_TC0_CCR0 = 0b101;    
  REG_TC0_IER0 = 0b00010000; 
  REG_TC0_IDR0 = 0b11101111; 
  NVIC_EnableIRQ(TC0_IRQn);
  
  playSound(0);
  playSound(1);
  playSound(2);
}

using namespace std;

int gameState;
boolean prevBT1, BT1;
/*************
Menu Functions
*************/
int prevJoy, joy, cursorPos;
void menuStart(){
  screenColor(BLACK);
  drawText(120, 20, "pong");
  drawText(120,120, "play");
  drawText(60, 160, "highscore");
  gameState = 1;
  prevJoy=0;
  joy = 0;
  cursorPos = 0;
  prevBT1=true;
  BT1=true;
}

void updateMenu(){
  prevJoy = joy;
  joy = 0;
  prevBT1 = BT1;
  if(digitalRead(51) == HIGH){
    joy = 1; //up
  }
  if(digitalRead(50) == HIGH){
    joy = 2; //down
  }
  if(joy==1 && prevJoy==0){
    playSound(1);
    if(cursorPos==0){
      cursorPos = 1;
    }else{
      cursorPos--;
    }
  }
  if(joy==2 && prevJoy==0){
    playSound(1);
    if(cursorPos==1){
      cursorPos = 0;
    }else{
      cursorPos++;
    }
  }
  if(cursorPos == 0){
    drawRect(95, 125, 110, 140, WHITE);
    drawRect(35, 165, 50, 180, BLACK);
  }else{
    drawRect(95, 125, 110, 140, BLACK);
    drawRect(35, 165, 50, 180, WHITE);
  }
  if(digitalRead(46) == LOW){
    BT1 = true;
  }else{
    BT1 = false;
  }
  if(BT1 && !prevBT1){
    playSound(2);
    switch(cursorPos){
      case 0:
        gameStart();
        break;
      case 1:
        highscoreStart();
        break;
    }
  }
}

/***************
InGame Functions
***************/
int timer, health, sco;
Barre barre(120);
Balle balle(160, 120);
void gameStart(){
  screenColor(BLACK);
  gameState = 2;
  
  barre.setY(120);
  barre.updateYPrevious();
  timer = 30;
  health = 3;
  sco = 0;
}

void updateGame(){
  int yp = barre.getY();
  int ypp = barre.getYPrevious();
  int bx = balle.getX();
  int by = balle.getXPrevious();
  int pbx = balle.getY();
  int pby = balle.getYPrevious();
  int dx = balle.getDX();
  int dy = balle.getDY();
  drawRect(50, 5, 320, 30, BLACK);
  drawHearts(50, 5, health);
  drawNumber(90, 5, sco);
  drawRect(pbx-8, pby-8, pbx+8, pby+8, BLACK);
  drawRect(304,0, 320, 240, WHITE);
  drawRect(bx-8, by-8, bx+8, by+8, WHITE);
  drawRect(0, ypp-24, 16, ypp+24, BLACK);
  drawRect(0, yp-24, 16, yp+24, WHITE);
  balle.updatePositionPrevious();
  barre.updateYPrevious();
  if(timer==0){
    balle.bouger();
  }else{
    timer--;
  }
  if(digitalRead(50)==HIGH && yp<216){
    barre.allerBas();
  }
  if(digitalRead(51)==HIGH && yp>=24){
    barre.allerHaut();
  }
  if(bx<28 && dx==-4){
    if(bx<28 && abs(by-yp)<32){
      balle.inverserVitesseH();
      sco++;
      playSound(0);
    }else if(bx<8){
      balle.setXY(160, 120);
      timer = 30;
      health--;
      if(health==0){
        drawText(65, 40, "you lose");
        delay(2000);
        if(sco > HS[5].score){
          newHighStart();
        }else{
          menuStart();
        }
      }
    }
  }
  if(bx>=296 && dx==4){
    balle.inverserVitesseH();
    playSound(0);
  }
  if((by<12 && dy==-4)||(by>228 && dy==4)){
    balle.inverserVitesseV();
    playSound(0);
  }
}

/***************
new HS Functions
***************/
int charPos;
String name;
void newHighStart(){
  screenColor(BLACK);
  drawText(5, 10, "new highscore");
  drawText(125, 110, "aaa");
  prevJoy = 0;
  joy = 0;
  charPos = 0;
  name = "aaa";
  prevBT1=true;
  BT1=true;
  gameState = 3;
}

void updateNewHigh(){
  drawRect(125, 110, 215, 135, BLACK);
  drawText(125, 110, name);
  int i;
  for(i=0; i<3; i++){
    if(i == charPos){
      drawRect(125+i*20, 140, 140+i*20, 155, WHITE);
    }else{
      drawRect(125+i*20, 140, 145+i*20, 155, BLACK);
    }
  }
  prevJoy = joy;
  joy = 0;
  prevBT1 = BT1;
  if(digitalRead(51) == HIGH){
    joy = 1; //up
  }
  if(digitalRead(50) == HIGH){
    joy = 2; //down
  }
  if(digitalRead(46) == LOW){
    BT1 = true;
  }else{
    BT1 = false;
  }
  if(joy==1 && prevJoy==0){
    playSound(1);
    if(name[charPos]=='z'){
      name[charPos]='a';
    }else{
      name[charPos]++;
    }
  }
  if(joy==2 && prevJoy==0){
    playSound(1);
    if(name[charPos]=='a'){
      name[charPos]='z';
    }else{
      name[charPos]--;
    }
  }
  if(BT1 && !prevBT1){
    playSound(2);
    if(charPos<2){
      charPos++;
    }else{
      i = 5;
      while(i>0 && sco>HS[i-1].score){
        i--;
      }
      for(int j=5; j>i; j--){
        HS[j].name = HS[j-1].name;
        HS[j].score = HS[j-1].score;
      }
      HS[i].name = name;
      HS[i].score = sco;
      highscoreStart();
    }
  }
}

/******************
Highscore Functions
******************/
void highscoreStart(){
  gameState = 4;
  prevBT1=true;
  BT1=true;
  screenColor(BLACK);
  drawText(60, 5, "highscore");
  int i;
  for(i = 0; i < 6; i++){
    drawNum(10, 50+i*30, i+1);
    drawText(50, 50+i*30, HS[i].name);
    drawNumber(140, 50+i*30, HS[i].score);
  }
}

void updateHighscore(){
  prevBT1 = BT1;
  if(digitalRead(46)==LOW){
    BT1=true;
  }else{
    BT1=false;
  }
  if(BT1 && !prevBT1){
    playSound(2);
    menuStart();
  }
}

/********
Main Loop
********/
void loop(){
  switch(gameState){
    case 1:
      updateMenu();
      break;
    case 2:
      updateGame();
      break;
    case 3:
      updateNewHigh();
      break;
    case 4:
      updateHighscore();
      break;
  }
  delay(33);
}
