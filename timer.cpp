#include "rsdl.hpp"
#include <iostream>
#include <time.h>
using namespace std;
#define WINDOW_WIDTH 612
#define WINDOW_HEIGTH 418
#define IMG_BACKGROUND "Football-Ground.png"
#define Ball "Ball.png"

bool hit (int x , int y)
{
 	if (x<= 0 || x >= 612 - 30 || y <=0 || y >=418 - 35 )
 	{
 		return 1;
 	}
 	else 
 	return 0;
}





 bool Goal (int x , int y)
 {
 	if ((x<=30 && (y >= 158-15&& y <= 30+218))||(x>=612-60 && (y >= 158-15 && y <= 218+30)) )
 	//NUMBERS HAVE ALL BEEN APPROXIMATELY CALCULATED
 	{
 		return 	1;

 	}
 	else
 	return 0;
 }




int main(int argc, char const *argv[])
{
	srand(time(0)); 
	Event ev;
	Window *win;

	win = new Window(WINDOW_WIDTH, WINDOW_HEIGTH, "Football");
	win->clear();

  	win->draw_bg(IMG_BACKGROUND, 0, 0);
    win->update_screen();
    int x = rand()%600;
    int y =  rand()%400;
    win->draw_png(Ball, x,  y, 30, 30);
	win->update_screen();
    while (true)
    {	
		ev = win->pollForEvent();
		cout << "polling" ;
		if (ev.type()== QUIT)
 		{
 			win->~Window();
 			break;
 		}
		if( ev.type()!= QUIT)
		{
			if (ev.type() == KEY_PRESS)
			{
				char pressedChar = ev.pressedKey();
				switch(pressedChar)
				{
				    case 'w' :
				    	win->clear();
				    	win->draw_bg(IMG_BACKGROUND, 0, 0);
				    	y = y- 15 ;
				    	if (hit(x,y))
				    	{
				    		y = y +15;
				    	}
				    	win->draw_png(Ball, x,  y, 30, 30);
				    	win->update_screen();
				        break;

				    case 'a' : 
				    	win->clear();
				    	win->draw_bg(IMG_BACKGROUND, 0, 0);
				    	x = x- 15;
				    	if (hit(x,y))
				    	{
				    		x = x+ 15;
				    	}
				    	win->draw_png(Ball, x,  y, 30, 30);
				    	win->update_screen();
				        break;

				    case 's' : 
				    	win->clear();
				    	win->draw_bg(IMG_BACKGROUND, 0, 0);
				    	y = y + 15 ;
				    	if (hit(x,y))
				    	{
				    		y =y - 15;
				    	}
				    	win->draw_png(Ball, x,  y, 30, 30);
				    	win->update_screen();
				        break;

				    case 'd' : 
				    	win->clear();
				    	win->draw_bg(IMG_BACKGROUND, 0, 0);
				    	x= x+ 15;
				    	if (hit(x,y))
				    	{
				    		x = x- 15;
				    	}
				    	win->draw_png(Ball, x,  y, 30, 30);
				    	win->update_screen();
				        break;

					case 'i' : 
				    	for (int i = 0; i < 100; ++i)
				    	{	
				    		if (hit(x,y-2))
				    		{
				    			y = y + 2;
				    			break;
				    		}
				    		
				    		
				    		if (Goal(x,y))
				    		{
				    			win->draw_png("Goal.png", 0,  0, 612, 418);
				    			win->update_screen();
				    			Delay(2000);
				    			win->draw_bg(IMG_BACKGROUND, 0, 0);
				    			x = rand()%600;
    							y =  rand()%400;
				    			win->draw_png(Ball, x,  y, 30, 30);
				    			win->update_screen();
				    			break;
				    		}
				    		else 
				    		{
					    		win->clear();
						    	win->draw_bg(IMG_BACKGROUND, 0, 0);
						    	y = y - 2;
						    	if (hit(x,y))
						    	{	
						    		win->draw_png(Ball, x,  y+2, 30, 30);
						    		win->update_screen();
						    		break;
						    	}
						    	win->draw_png(Ball, x,  y, 30, 30);
						    	win->update_screen();
						    	Delay(5);
						    }
				    	
				    	}
				    	break;

				    case 'j' : 
				    	for (int i = 0; i < 100; ++i)
				    	{
				    		if (hit(x-2,y))
				    		{
				    			x = x+2;
				    			break;
				    		}
					    		
				    		if (Goal(x,y))
				    		{
				    			win->draw_png("Goal.png", 0,  0, 612, 418);
				    			win->update_screen();
				    			Delay(2000);
				    			win->draw_bg(IMG_BACKGROUND, 0, 0);
				    			x = rand()%600;
    							y =  rand()%400;
				    			win->draw_png(Ball, x,  y, 30, 30);
				    			win->update_screen();
				    			break;
				    		}
				    		else 

				    		{

					    		win->clear();
						    	win->draw_bg(IMG_BACKGROUND, 0, 0);
						    	x = x-2;
						    	if (hit(x,y))
						    	{
						    		win->draw_png(Ball, x+2,  y, 30, 30);
						    		win->update_screen();
						    		break;
						    	}
						    	win->draw_png(Ball, x,  y, 30, 30);
						    	win->update_screen();
						    	Delay(5);
					        }
				    	
				    	}
				    	break;

				    case 'k' : 
				    	
				    	for (int i = 0; i < 100; ++i)

				    	{
				    		if (hit(x,y+2))
				    		{
				    			y = y - 2;
				    			break;
				    		}
				    		if (Goal(x,y))
				    		{
				    			win->draw_png("Goal.png", 0,  0, 612, 418);
				    			win->update_screen();
				    			Delay(2000);
				    			win->draw_bg(IMG_BACKGROUND, 0, 0);
				    			x = rand()%600;
    							y =  rand()%400;
				    			win->draw_png(Ball, x,  y, 30, 30);
				    			win->update_screen();
				    			break;
				    		}
				    		else 
				    		{

					    		win->clear();
						    	win->draw_bg(IMG_BACKGROUND, 0, 0);
						    	y = y + 2;
						    	if (hit(x,y))
						    	{
						    		win->draw_png(Ball, x,  y-2, 30, 30);
						    		win->update_screen();
						    		break;
						    	}
						    	win->draw_png(Ball, x,  y, 30, 30);
						    	win->update_screen();
						    	Delay(5);
					        }
				    	
				    	}
				    	break; 

				    case 'l' : 
				    	for (int i = 0; i < 100; ++i)
				    	{
				    		if (hit(x+2,y))
				    		{
				    			x = x-2;
				    			break;
				    		}
				    		if (Goal(x,y))
				    		{
				    			win->draw_png("Goal.png", 0,  0, 612, 418);
				    			win->update_screen();
				    			Delay(2000);

				    			win->draw_bg(IMG_BACKGROUND, 0, 0);
				    			x = rand()%600;
    							y =  rand()%400;
				    			win->draw_png(Ball, x,  y, 30, 30);
				    			win->update_screen();
				    			break;
				    		}
				    		else 
				    		{

					    		win->clear();
						    	win->draw_bg(IMG_BACKGROUND, 0, 0);
						    	x = x + 2;
						    	if (hit(x,y))
						    	{
							    	win->draw_png(Ball, x-2,  y, 30, 30);
							    	win->update_screen();
						    		break;
						    	}
						    	win->draw_png(Ball, x,  y, 30, 30);
						    	win->update_screen();
						    	Delay(5);
						    }    
				    	
				    	}  
				    	break;              
				}

			
				

			}
		 
		 
		}

		


	}
	
	return 0;
}