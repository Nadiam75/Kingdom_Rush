
#include <iostream>
#include "readGameInfo.h"
//#include "model.h"

using namespace std;
int main(int argc, char const *argv[])
{
	
	
	Level l =readLevelInfo(readFile("levels/1/level1-waves.txt"));


	cout << l.backgroundAddress;
	for (int i = 0; i < l.path.size(); ++i)
	{
		
		cout << l.path[i].x << endl;
	}


	cout << l.backgroundAddress << endl ;
	for (int i = 0; i < l.path.size(); ++i)
	{
		
		cout << l.path[i].x<< " ";
	}
	cout << endl;
	for (int i = 0; i < l.strategicPoints.size(); ++i)
	{
		cout<<l.strategicPoints[i].y << " ";
	}
	cout << endl;
	



	return 0;
}