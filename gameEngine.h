#include "rsdl.hpp"
#include "readGameInfo.h"
#include <string>
#include <math.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define GAME_NAME "Kingdom Rush"
#define TOWER_RANGE 85
#define ARROW_SPEED 100
#define DELTA_TIME 10
#define PI 3.14159265
#define FONT "Future TimeSplitters.otf"
#define STATS_FONT "starcraft.ttf"
#define ARCHER_ARROW_PATH "arrows/1.png"
#define CANNON_ARROW_PATH "arrows/2.png"
#define MAGE_ARROW_PATH "arrows/3.png"
#define ICY_ARROW_PATH "arrows/4.png"

struct EndGameException
{
	
};


void startGame (Game g);
void updateEnemyTarget( Enemy &e , vector<Point> path);
void moveEnemy(Enemy &e,int deltaT,vector<Point> path);
void renderGame (Window * win , Game g);
double getDistance(Point p1 ,Point p2 );
bool isCloseEnough(Point p1 , Point p2, int d);
bool isTowerPosition(int mouseXLocation , int mouseYLocation);
void buildTower(char pressedChar , int mouseXLocation ,int mouseYLocation, Game &g);
bool isTowerPosition(int mouseXLocation ,int mouseYLocation , Game &g);
void fireArrow ( Game &g ,int time);
void fire(Tower &t , Enemy &enemy  , Game &g );
void moveArrow(Game &g);
void hitEnemies(Game &g);
void checkIfEnemiesReachedEnd( Game &g);
bool didIJustWin (Game &g,int time);
bool didIJustLose (Game &g);