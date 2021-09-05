#include <Servo.h>

// definition generale
#define AXIS_Z      0
#define AXIS_X      1

#define CW          HIGH
#define CCW         LOW

// direction du trait
#define HAUT        CW
#define BAS         CCW
#define GAUCHE      CCW
#define DROITE      CW
#define GUP         0
#define DUP         1
#define GDOWN       2
#define DDOWN       3

// index TabAxis
#define DIR         0
#define STEP        1
#define LIMIT       2
#define CURSOR      3

// definition des pins
#define DIR_Z       2
#define STEP_Z      3
#define LIMIT_Z     4
#define DIR_X       5
#define STEP_X      6
#define LIMIT_X     7
#define AXIS_Y      9

// definition des positions d'Y
#define TOP         170
#define UP          130
#define MIDDLE      90
#define DOWN        50
#define BOTTOM      10
#define SURFACE     36

void init_axis ();
void pulse(bool slct);
void move_axis (bool slct, bool dir, unsigned char len);
void move_diagonal(unsigned char dir,unsigned char len);

Servo servo_Y;
 
int i;
bool TabDig [4][2] = {{HAUT,GAUCHE},{HAUT,DROITE},{BAS,GAUCHE},{BAS,DROITE}};
unsigned char TabAxis [2][4] = {{DIR_Z,STEP_Z,LIMIT_Z,0},{DIR_X,STEP_X,LIMIT_X,0}};

void setup() 
{  
  init_axis();

//  servo_Y.write(SURFACE);  
//  delay(200);
//
//  delay(200);
//  servo_Y.write(UP);
}

void loop() 
{

}

void init_axis ()
{
  servo_Y.attach(AXIS_Y);
  servo_Y.write(UP);
  delay(100);
  
  for (i=0;i<2;i++)
  {
    pinMode(TabAxis[i][DIR],OUTPUT);
    digitalWrite(TabAxis[i][DIR],CW);
    pinMode(TabAxis[i][STEP],OUTPUT);
    digitalWrite(TabAxis[i][STEP],HIGH);
    pinMode(TabAxis[i][LIMIT],INPUT_PULLUP);
    digitalWrite(TabAxis[i][DIR],i);
    while(digitalRead(TabAxis[i][LIMIT]) == 1) pulse(i);
  }
   
  move_diagonal(GUP,255);

  TabAxis[AXIS_Z][CURSOR] = 0;
  TabAxis[AXIS_X][CURSOR] = 0;
}

void pulse (bool slct)
{
  digitalWrite(TabAxis[slct][STEP],LOW);
  delay(1);
  digitalWrite(TabAxis[slct][STEP],HIGH);
  delay(1);
}

void move_axis (bool slct, bool dir, unsigned char len)
{
  digitalWrite(TabAxis[slct][DIR],dir);  
    
  for (i = 0; i < len; i++) pulse(slct);
  
  if (slct == dir) TabAxis[slct][CURSOR] += len;         // droite & bas
  else TabAxis[slct][CURSOR] -= len;                    // gauche & haut

  delay(250);
}

void move_diagonal(unsigned char dir,unsigned char len)
{
  digitalWrite(TabAxis[AXIS_Z][DIR],TabDig[dir][AXIS_Z]);
  digitalWrite(TabAxis[AXIS_X][DIR],TabDig[dir][AXIS_X]);
  
  for (i = 0; i < len; i++)
  {
    pulse(AXIS_Z);
    pulse(AXIS_X);
  }
  
  if(TabDig[dir][AXIS_Z]) TabAxis[AXIS_Z][CURSOR] -= len;           // haut
  else TabAxis[AXIS_Z][CURSOR] += len;                               // bas

  if(TabDig[dir][AXIS_X]) TabAxis[AXIS_X][CURSOR] += len;         // droite
  else TabAxis[AXIS_X][CURSOR] -= len;                            // gauche
  
  delay(250);  
}
