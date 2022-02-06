#include "model.h"
#include <iostream>
using namespace std;


Enemy generateEnemy(string enemytype,Point startingPosition, Point targetPosition)
{
	Enemy e;
	e.isAlive = true;
	e.location = startingPosition;
	e.target = targetPosition;

	char c = enemytype[0];
	switch (c)
	{

		case 'o':
		{
			e.type= ORC;
			e.life = 200;
			e.speed = 42;
			e.armor = NOARMOR;
			e.reward = +5;
			e.damage = 1;
			break;
		}	
		case 'w':
		{ 
			e.type= WOLF;
			e.life = 100;
			e.speed = 85;
			e.armor =NOARMOR ;
			e.reward = +4;
			e.damage = 1;
			break;
		}
		case 'a':
		{
			e.type= ARMORED ;
			e.life = 450	;
			e.speed = 21;
			e.armor = PHYSICAL;
			e.reward = +8;
			e.damage = 3;
			break;
		}
		case 'd':
		{
			e.type= DEMON;
			e.life = 400;
			e.speed = 28;
			e.armor = MAGICAL;
			e.reward = +8;
			e.damage = 3;
			break;
		}
	}


	return e;


}