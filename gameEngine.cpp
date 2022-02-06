#include "gameEngine.h"
#include <time.h>
#include <iterator>
#include <random>
double angleCalculation (Point a, Point b)
{

	double angle;
	angle = atan2(a.y, a.x) - atan2(b.y, b.x);
	if (angle < 0){
		angle = angle + 2*PI;
	}
	return angle;
}
bool didIJustLose (Game &g)
{
	return (g.player.health<=0 ||g.player.health>15);
}

bool didIJustWin (Game &g,int time)

{
	
	int temp = time/1000;

	if (temp >= g.currentLevel.waves[g.currentLevel.waves.size()-1].entryTimes[ g.currentLevel.waves[g.currentLevel.waves.size()-1].entryTimes.size()-1] )
	{
		
		for (int i = 0; i <g.aliveEnemies.size() ; ++i)
		{
			if (g.aliveEnemies[i].isAlive)
			{
				return false;
			}
		}
		return true;
	}

	return false;
	
}

void checkIfEnemiesReachedEnd( Game &g)
{
	for (int i = 0; i < g.aliveEnemies.size(); ++i)
	{
		if(isCloseEnough(g.aliveEnemies[i].location, g.currentLevel.path[g.currentLevel.path.size()-1] , 30) )
		{
			if (g.player.health >=0)
			{
			
				if (g.aliveEnemies[i].isAlive)
				{
					g.player.health -= g.aliveEnemies[i].damage ;


					g.aliveEnemies[i].isAlive = false ;					
					g.aliveEnemies.erase(g.aliveEnemies.begin()+i);
				
				}

			}
		}

	}
}




void hitEnemies(Game &g , int &time)
{


	for (int i = g.firedArrows.size()-1; i >=0 ; i--)
	{
		if (g.firedArrows[i].isHit)
		{
			g.firedArrows.erase(g.firedArrows.begin()+i); 
		}
	}


	for (int i = 0; i < g.firedArrows.size(); ++i)

	{
		if (g.firedArrows[i].tower->towerType == CANNON)
		{
			for (int j = 0; j < g.aliveEnemies.size(); ++j)
			{
				if (isCloseEnough(g.firedArrows[i].position , g.aliveEnemies[j].location, 10))
				{
					if (!g.firedArrows[i].isHit )
					{
						if ( g.aliveEnemies[j].armor == PHYSICAL)
						{
						
						
							for (int h = 0; h < g.aliveEnemies.size(); ++h)
							{
								if (isCloseEnough(g.aliveEnemies[h].location , g.firedArrows[i].targetEnemy->location , 50))
								{
									g.aliveEnemies[h].life-= g.firedArrows[i].tower->damage*0.5;	
								}

								if (g.aliveEnemies[h].life <= 0)
								{
									g.aliveEnemies.erase(g.aliveEnemies.begin()+h); 
									g.aliveEnemies[h].isAlive = false;
									g.player.money+= g.aliveEnemies[h].reward;
									
								}
							}

						}

						else 
						{
					
								
							for (int h = 0; h < g.aliveEnemies.size(); ++h)
							{
								if (isCloseEnough(g.aliveEnemies[h].location , g.firedArrows[i].targetEnemy->location , 50))
								{
									g.aliveEnemies[h].life-= g.firedArrows[i].tower->damage;	
								}

								if (g.aliveEnemies[h].life <= 0)
								{
									g.aliveEnemies.erase(g.aliveEnemies.begin()+h); 
									g.aliveEnemies[h].isAlive = false;
									g.player.money+= g.aliveEnemies[h].reward;
									
								}
							}
							
					
				
						}

							


						if (g.aliveEnemies[j].life <= 0)
						{
							g.aliveEnemies.erase(g.aliveEnemies.begin()+j); 
							g.aliveEnemies[j].isAlive = false;
							g.player.money+= g.aliveEnemies[j].reward;
							
						}
						g.firedArrows[i].isHit = true ;
					}

				}
			}
		}
	 


		else if (g.firedArrows[i].tower->towerType == ICY)
		{
		//	cout << "we are HERE " << endl;
			//capturedTime = time;
			//reduceSpeed( g.firedArrows[i].targetEnemy->location,capturedTime , time , g);

			if (!g.firedArrows[i].isHit )
			{
				if (isCloseEnough(g.firedArrows[i].position , g.firedArrows[i].targetEnemy->location ,3 ))
				{
					g.firedArrows[i].isHit = true ;

					for (int v = 0; v < g.aliveEnemies.size(); ++v)
					{
						if (isCloseEnough(g.firedArrows[i].targetEnemy->location , g.aliveEnemies[v].location , 50))
						{

							g.aliveEnemies[v].isIceAffected= 1;
							g.aliveEnemies[v].iceEffectTime = time ;
							if (g.aliveEnemies[v].armor == MAGICAL)
							{
								g.aliveEnemies[v].life-= (g.firedArrows[i].tower->damage)*0.5;
							}
							else
							g.aliveEnemies[v].life-= (g.firedArrows[i].tower->damage);
						}

						if (g.aliveEnemies[v].life <= 0)
						{
							g.aliveEnemies.erase(g.aliveEnemies.begin()+v); 
							g.aliveEnemies[v].isAlive = false;
							g.player.money+= g.aliveEnemies[v].reward;
							
						}
					}	
				}
			}
		}	

	
		else if (g.firedArrows[i].tower -> towerType == MAGE || g.firedArrows[i].tower -> towerType == ARCHER)
		{
			if (!g.firedArrows[i].isHit && isCloseEnough(g.firedArrows[i].position , g.firedArrows[i].targetEnemy->location , 3))
			{
				
				if ((g.firedArrows[i].tower->damageType == PHYSICALDAMAGE && g.firedArrows[i].targetEnemy->armor == PHYSICAL) ||(g.firedArrows[i].tower->damageType == MAGICALDAMAGE && g.firedArrows[i].targetEnemy->armor== MAGICAL))
				{
					g.firedArrows[i].targetEnemy->life-= (g.firedArrows[i].tower->damage)*0.5;
				}
				else 
					g.firedArrows[i].targetEnemy->life-= (g.firedArrows[i].tower->damage);

				if (g.firedArrows[i].targetEnemy->life <= 0)
				{
					g.firedArrows[i].targetEnemy->isAlive = false;
					g.player.money+= g.firedArrows[i].targetEnemy->reward;
	//				g.aliveEnemies.erase(g.aliveEnemies.begin()+j); 
				}

				g.firedArrows[i].isHit = true ;


			}
		}
	}

}

void moveArrow(Game &g)
{
	srand(time(0));
	for (int i = 0; i < g.firedArrows.size(); ++i)
	{
		if (!g.firedArrows[i].isHit)
		{
			double dirX = g.firedArrows[i].targetEnemy->location.x - g.firedArrows[i].position.x;
			double dirY = g.firedArrows[i].targetEnemy->location.y - g.firedArrows[i].position.y;
			

			dirX = (dirX) / sqrt(pow(dirX,2) + pow(dirY,2));
			dirY = (dirY) / sqrt(pow(dirX,2) + pow(dirY,2));
			

			g.firedArrows[i].position.x = DELTA_TIME*dirX*ARROW_SPEED/1000 + g.firedArrows[i].position.x ;
			g.firedArrows[i].position.y = DELTA_TIME*dirY*ARROW_SPEED/1000 + g.firedArrows[i].position.y ;	

		}
		

	}
}
void fire(Tower &t , Enemy &enemy  , Game &g , int time)
{

	Arrow arrow;
	arrow.position = t.position ;
	arrow.tower = &t;
	arrow.targetEnemy = &enemy;
	arrow.launchTime = time;
	bool flag = 0;
	for (int i = 0; i < g.firedArrows.size(); ++i)
	{
		if( (arrow.launchTime == g.firedArrows[i].launchTime )&&(arrow.tower == g.firedArrows[i].tower) &&( arrow.targetEnemy == g.firedArrows[i].targetEnemy))
		{
			flag  = 1;	
		}
	}

	if (!flag)
		g.firedArrows.push_back(arrow);

}

void fireArrow ( Game &g ,int time)
{
	bool fired=false;

	for (int i = 0; i < g.builtTowers.size(); ++i)
	{
		if(fired){
			fired = false;
			continue;
		}
		for (int j = 0; j < g.aliveEnemies.size(); ++j)
		{

			if(isCloseEnough(g.aliveEnemies[j].location , g.builtTowers[i].position, TOWER_RANGE))
			{
				if (g.aliveEnemies[j].isAlive)
				{
					if(time % g.builtTowers[i].fireRate == 0){
						fire(g.builtTowers[i] , g.aliveEnemies[j],g , time );
						fired = true;
						break;
					}					
				}
			}
		}
	}
}
bool isTowerPosition(Point p , Game &g)
{
	
	for (int i = 0; i < g.currentLevel.strategicPoints.size(); ++i)
	{
		if ( isCloseEnough(p ,g.currentLevel.strategicPoints[i], 15) )
		{
	//		cout << "isTowerPosition" <<endl ;
			return true;
		}
	}
	//cout << "is not tower position"<<endl;
	return false;

}



//push back kardane y tower tuye built towers

bool buildTower(char pressedChar ,Point p, Game &g)
{	
	Tower temp;
	p.x = p.x - 35;
	p.y = p.y - 35;
	temp.position = p ;
	for (int i = 0; i < g.builtTowers.size(); ++i)
	{
		if (isCloseEnough(g.builtTowers[i].position, temp.position , 30))
		{
			return false;
		}
	} 

	if ( !(pressedChar == 'a' || pressedChar == 'c' || pressedChar =='m' || pressedChar == 'i'))
		return false;

	switch(pressedChar)
	{
		case 'a':
		{
			temp.towerType = ARCHER;
			temp.damage = 50;
			temp.price = 70;
			temp.damageType = PHYSICALDAMAGE;
			temp.fireRate= 700;


		
			break;
		}

		case 'c':
		{
			temp.towerType = CANNON;
			temp.damage = 140;
			temp.price = 125;
			temp.damageType = PHYSICALDAMAGE;
			temp.fireRate=2000;
			temp.fireRange=50;

			break;
		}
		case 'm':
		{
			temp.towerType = MAGE;
			temp.damage = 140;
			temp.price = 90;
			temp.damageType = MAGICALDAMAGE;
			temp.fireRate=1500;

			break;
		}
		case 'i':
		{
			temp.towerType = ICY;
			temp.damage = 30;
			temp.price = 80;
			temp.damageType = MAGICALDAMAGE;
			temp.fireRate=2000;
			temp.fireRange=50;


			break;
		}
		
	}
	

	if ((g.player.money >= temp.price) )
	{
		g.player.money-=temp.price;
		g.builtTowers.push_back(temp);
		return 1;
	}
	else
	{
		return 0;
	}
	

}
double getDistance(Point p1 ,Point p2 )
{
	return  sqrt(pow(p1.x-p2.x,2) + pow(p2.y-p1.y,2));
}

bool isCloseEnough(Point p1 , Point p2 , int range)
{
	return	(getDistance(p1 , p2) <range);
	
}

bool foundAmongPoints ( Point p , vector<Point> &v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		if ((p.x == v[i].x ) && p.y == v[i].y )
		{
			return true;
		}
	}
	return false;
}
void checkTimeAddEnemies(int &time , Game &g , vector<Point> &passedWaves )
{
	Point p;
	
	for (int i = 0; i < g.currentLevel.waves.size(); ++i)
	{

		for (int j = 0; j <g.currentLevel.waves[i].entryTimes.size() ; ++j)
		{
			p.x = i;
			p.y = j;
			if (!foundAmongPoints(p, passedWaves))
			{
				if (g.currentLevel.waves[i].entryTimes[j] *1000== time)
				{
					
					g.aliveEnemies.insert(g.aliveEnemies.end(), g.currentLevel.waves[i].enemies[j].begin(), g.currentLevel.waves[i].enemies[j].end());	
					passedWaves.push_back(p);

				}

			}			
		
		}
	}
}


void updateEnemyTarget( Enemy &e , vector<Point> path)
{

	//\srand(time(0));


	for (int  in = 0; in < path.size(); ++in)
	{
		if (isCloseEnough(path[in],e.target , 20 ))
		{
			if(isCloseEnough(e.location , e.target , 15 ))
			{
				random_device rd;
				mt19937 gen(rd()); 
    			uniform_int_distribution<> dis(-10, 10);

				double randx = dis(gen);
				double randy = dis(gen);

				e.target.x = path[in+1].x+randx;
				e.target.y = path[in+1].y+randy;
					
			}

		}
	}




	
}


void moveEnemy(Enemy &e,int deltaT,vector<Point> path, int &t)
{
	
	double dirX =e.target.x - e.location.x;
	double dirY = e.target.y - e.location.y;
	


	dirX = (dirX) / sqrt(pow(dirX,2) + pow(dirY,2));
	dirY = (dirY) / sqrt(pow(dirX,2) + pow(dirY,2));

	double tan = dirY / dirX;
	if (tan>-1 && tan <1)
	{
		if (dirX>0)
		{
			e.dir= RIGHT;
		}
		else
			e.dir = LEFT;
	}
	else
	{
		if (dirY>0)
		{
			e.dir = DOWN;
		}
		else
			e.dir = UP;
	}
	
	if (e.isIceAffected && (t - e.iceEffectTime <= 3000 ))
	{
		deltaT /=2;
	}
	e.location.x = deltaT*dirX*e.speed/1000  + e.location.x ;
	e.location.y = deltaT*dirY*e.speed/1000 + e.location.y ;



	if (isCloseEnough(e.location, path[path.size()-1], 20))
	{
		e.isAlive = false;
	}

	

}







void renderGame (Window * win , Game g , vector<Point> &passedWaves , int &time, bool &showCantBuildMessage,int frame)
{

	int maximum = max(g.firedArrows.size(),g.aliveEnemies.size());

	

	win->clear();
	char buffer[30];
	string bgAddress = (g.currentLevel.backgroundAddress);
	bgAddress.copy(buffer,bgAddress.length()-1,0);
	win->draw_bg(buffer, 0, 0);

	for (int i = 0; i < maximum; ++i)
	{
		if (i<g.aliveEnemies.size())
		{
			string enemyPath;
			if (g.aliveEnemies[i].isAlive)
			{
				switch (g.aliveEnemies[i].type)
				{
					case ORC:
					{
						switch(g.aliveEnemies[i].dir)
						{
							case UP:
							{
								enemyPath = "enemies/orc/back" + to_string(frame%2 +1) + ".png";
								break;
							}
							case DOWN:
							{
								enemyPath = "enemies/orc/front"+ to_string(frame%2 +1) + ".png";
								break;
							}
							case LEFT:
							{
								enemyPath = "enemies/orc/left"+ to_string(frame%2 +1) + ".png";
								break;
							}
							case RIGHT:
							{
								enemyPath = "enemies/orc/right"+  to_string(frame%2 +1) + ".png";
								break;
							}
						}
						break;
						
					}	
					case WOLF:
					{
						switch(g.aliveEnemies[i].dir)
						{
							case UP:
							{
								enemyPath = "enemies/wolf/back.png";
								break;
							}
							case DOWN:
							{
								enemyPath = "enemies/wolf/front.png";
								break;
							}
							case LEFT:
							{
								enemyPath = "enemies/wolf/left" + to_string(frame%4 +1) + ".png";
								break;
							}
							case RIGHT:
							{
								enemyPath = "enemies/wolf/right" + to_string(frame%4 +1) + ".png";
								break;
							}
						}
						break;
					}
					case ARMORED:
					{
						switch(g.aliveEnemies[i].dir)
						{
							case UP:
							{
								enemyPath = "enemies/armored/back" + to_string(frame%2 + 1)+ ".png";
								break;
							}
							case DOWN:
							{
								enemyPath = "enemies/armored/front" + to_string (frame%2 + 1) +".png";
								break;
							}
							case LEFT:
							{
								enemyPath = "enemies/armored/left"+ to_string (frame%3+1) +".png" ;
								break;
							}
							case RIGHT:
							{
								enemyPath = "enemies/armored/right"+ to_string (frame%3+1) +".png";
								break;
							}
						}
						break;
					}
					case DEMON:
					{
						switch(g.aliveEnemies[i].dir)
						{
							case UP:
							{
								enemyPath = "enemies/demon/back" + to_string(frame%2 + 1)+ ".png";
								break;
							}
							case DOWN:
							{
								enemyPath = "enemies/demon/front" + to_string (frame%2 + 1)+ ".png";
								break;
							}
							case LEFT:
							{
								enemyPath = "enemies/demon/left" +to_string (frame%2+1) +".png";
								break;
							}
							case RIGHT:
							{
								enemyPath = "enemies/demon/right"+  to_string(frame%2 + 1)+ ".png";
								break;
							}
						}
						break;
					}

				}
				RGB myColor(88,15,15);
								
				win->draw_png(enemyPath, g.aliveEnemies[i].location.x, g.aliveEnemies[i].location.y, 30, 30) ;
				win->show_text(to_string(g.aliveEnemies[i].life),g.aliveEnemies[i].location.x, g.aliveEnemies[i].location.y-20,myColor,STATS_FONT ,12);

			}
		}

		if (i < g.firedArrows.size())

		{
			string arrowPath;
			switch (g.firedArrows[i].tower->towerType)
			{
				case ARCHER:
				{
					arrowPath = "arrows/1.png";
					break;
				}	
				case CANNON:
				{
					arrowPath = "arrows/2.png";
					break;
				}
				case MAGE:
				{
					arrowPath = "arrows/3.png";
					break;
				}
				case ICY:
				{
					arrowPath = "arrows/4.png";
					break;
				}
			}
			
				win->draw_png(arrowPath, g.firedArrows[i].position.x, g.firedArrows[i].position.y, 15 , 15 , angleCalculation (g.firedArrows[i].targetEnemy->location , g.firedArrows[i].position )) ;
		}
	}

	for (int i = 0; i < g.builtTowers.size(); ++i)
	{
		string towerPath;
		switch (g.builtTowers[i].towerType)
		{
			case ARCHER:
			{
				towerPath = "towers/archer.png";
				break;
			}	
			case CANNON:
			{
				towerPath = "towers/canon.png";
				break;
			}
			case MAGE:
			{
				towerPath = "towers/mage.png";
				break;
			}
			case ICY:
			{
				towerPath = "towers/icy.png";
				break;
			}
		}
		
		win->draw_png(towerPath, g.builtTowers[i].position.x, g.builtTowers[i].position.y, 60 , 60) ;
	}
	

	win->draw_png("stats.png", 10, 10, 189, 67) ;
	if (g.player.health>= 0 && g.player.health <=15)
	{
		win->show_text( to_string(g.player.health), 65, 25,YELLOW,STATS_FONT, 13);
	}
	else
		win->show_text( "0", 65, 25,YELLOW,FONT, 13);
	

	win->show_text( to_string(g.player.money), 130, 25,YELLOW,STATS_FONT ,13);
	if (passedWaves.size()>=1)
	{
		win->show_text( to_string( ((int)passedWaves[passedWaves.size()-1].x) +1), 125, 52,YELLOW,STATS_FONT ,13);
}





	if (didIJustLose (g)||didIJustWin(g, time))
	{

		if (didIJustLose(g))
		{
			
			RGB Color(255, 255, 255);
			win->draw_png("gameover.png", 300, 300 , 161, 116) ;	


		}


		if (didIJustWin(g, time))
		{
			RGB PERSIAN_BLUE(255, 255, 255);
			win->draw_png("winner.png", 50, 160 , 700, 359) ;
		}

		RGB myColor(88,15,15);
		string exit = "Press E to exit the game";
		

		win->show_text( exit , 500, 500,myColor,FONT, 40);
		

	}
		RGB myColor(88,15,15);
	if (showCantBuildMessage)
	{
		win->show_text( "Cannot Build Tower Here !!", 100, 100,myColor,FONT, 60);
	}
	




	win->update_screen();



}

void startGame(Game g)
{
	char buffer[30];
	Window * win;
	win = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);
	string bgAddress = (g.currentLevel.backgroundAddress);
	bgAddress.copy(buffer,bgAddress.length()-1,0);
	win->draw_bg(buffer, 0, 0);

	win->update_screen();
	Event ev;
	int counter=0;
	int capturedTime;
	bool towerConstructionMode =0;
	Point towerConstructionLocation;
	bool unableTobuild = 0 ;
	bool isLost;
	bool showCantBuildMessage=0;
	srand(time(0)); 
	int frame;
	
	vector<Point> passedWaves;
	
    while (ev.type()!= QUIT)
    {
    	ev = win->pollForEvent();
       	if (ev.type()==QUIT)
    	{
    		win->~Window();
 			break;
    	}
   	
    	
    	++counter;
    	if(counter%200 == 0)
    		frame++;
    	int time = clock()/(CLOCKS_PER_SEC/1000);
    	renderGame(win ,g , passedWaves , time , showCantBuildMessage,frame);
    	
    	

		if (towerConstructionMode && ev.type()==KEY_PRESS)
		{	
				
			char pressedChar = ev.pressedKey();
			 unableTobuild =!buildTower(pressedChar , towerConstructionLocation , g) ;
			if (unableTobuild)
			{
				capturedTime = time ;
			}
			else
			{
				towerConstructionMode = 0;
			}

				//cout << shortOfMoney << endl;
			
		}




    	if (ev.type()==LCLICK)
    	{
    		int mouseYLocation,mouseXLocation;
    		mouseXLocation = ev.mouseX();
			mouseYLocation = ev.mouseY();
			Point p;
			p.x = mouseXLocation;
			p.y = mouseYLocation;
			towerConstructionMode =isTowerPosition(p, g);
			if(towerConstructionMode){
				towerConstructionLocation.x = mouseXLocation;
				towerConstructionLocation.y = mouseYLocation;
			}
		
	   	}

    	
		

    	checkTimeAddEnemies(time , g , passedWaves);
    	if (time % DELTA_TIME ==0)
    	{

   	    	for (int i = 0; i < g.aliveEnemies.size(); ++i)
	    	{
	    	
	    		if(!isLost){

	    		updateEnemyTarget(g.aliveEnemies[i] , g.currentLevel.path);
	    		moveEnemy(g.aliveEnemies[i],DELTA_TIME,g.currentLevel.path , time);}
	    		
	    	}
    	moveArrow(g);
    	}




    	hitEnemies(g, time);
    	fireArrow ( g ,time);
    	

    	checkIfEnemiesReachedEnd( g);
    

    	showCantBuildMessage =unableTobuild&& towerConstructionMode;
		if (unableTobuild&& towerConstructionMode)	
		{

		
			
			if ((time - capturedTime +5)%2000 == 0)	
			{
				unableTobuild = 0;					
			} 
				//win->update_screen();
		}


	


	if (didIJustLose(g)|| didIJustWin(g, time))
	{	
		isLost =didIJustLose(g);
		if (ev.type() == KEY_PRESS &&   ev.pressedKey()== 'e'  )
		{
			break;
		}
		/*
		if  (ev.type() == KEY_PRESS &&   ev.pressedKey()== 's'  )
		{
			EndGameException e;
			throw e;
		} */
	}

	}
}



