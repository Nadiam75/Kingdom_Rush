#include "readGameInfo.h"
#include <iostream>

vector<string> stringSplitter(string s, char splitter )
{
	s = s+splitter;
	vector<string> v;
	v.clear();
	while(s.find(splitter)!= -1)
	{
		
		int slashPos = s.find(splitter);
		string temp = s.substr(0, slashPos);
		v.push_back(temp);
		s = s.substr(slashPos + 1);
	}

	return v;

}

string removeSpaces(string str) 
{ 
    int count = 0; 
    for (int i = 0; str[i]; i++) 
        if (str[i] != ' ') 
            str[count++] = str[i]; 
                                 
    str[count] = '\0'; 
    return str;
}

int getTimeStamp (string s )
{	
	vector<string> temp;
	temp = stringSplitter(s , ':');
	return stoi(removeSpaces(temp[0]))*60 + stoi(removeSpaces(temp[1]) );
}

vector<string> readFile(string path){
	ifstream infile(path);
	string line;
	vector<string> result;
	while(getline(infile,line))
	{
		result.push_back(line);
	}
	return result;
}

Level readLevelInfo(vector <string> v)
{

	Level l;
	vector<int> towerX;
	vector<int> towerY;
	vector<int> pathX;
	vector<int> pathY;
	vector<Wave> waves;



	l.backgroundAddress=v[0];

	for (int i = 1; i < v.size(); ++i)
	{
		if (v[i][0]=='t')
		{
			vector<string> tx;
			vector<string> ty;
			tx =stringSplitter(v[i+1] , '/');
			ty =stringSplitter(v[i+2] , '/');
			for (int j = 0; j < tx.size(); ++j)
			{
				towerX.push_back(stoi(tx[j]));
			}
			for (int j = 0; j < tx.size(); ++j)
			{
				towerY.push_back(stoi(ty[j]));
			}
		}


		if (v[i][0]== 'p')
		{
			vector<string> tx;
			vector<string> ty;
			tx =stringSplitter(v[i+1] , '/');
			ty =stringSplitter(v[i+2] , '/');
			for (int j = 0; j < tx.size(); ++j)
			{
				pathX.push_back(stoi(tx[j]));
			}
			for (int j = 0; j < tx.size(); ++j)
			{
				pathY.push_back(stoi(ty[j]));
			}
		}

		if (v[i][0]== 'w')
		{
		
			vector<vector<Enemy> > waveEnemies;
			vector<int> entryTimes;
			int startingIndex = i+1;
			int endingIndex ;
			while (v[i+1][0]!='w')
			{
				i++;
				if(i==v.size()-1)
					break;
			}
			endingIndex =1+ i;
			for (int k = startingIndex; k < endingIndex; ++k)
			{
				vector<string> w;
				if (v[k].size() < 3)
				{
					continue;
				}

				w = stringSplitter (v[k], ',');
				
				entryTimes.push_back(getTimeStamp (w[0]));
				vector<Enemy> e;
				for (int q = 1; q < w.size() ; ++q)
				{
					vector<string> splitted;
					splitted =stringSplitter((w[q]), 'x');
					Point startingp,targetp;
					srand(time(0)); 
					double randx = rand()%pathX[0];

					randx = randx /pathX[0] ;

					double randy = rand()%pathY[0];
					randy = randy /pathY[0] ;


					startingp.x = pathX[0];
					startingp.y = pathY[0];
					targetp.x = pathX[1];
					targetp.y= pathY[1];
					for (int z = 0; z < stoi(removeSpaces(splitted[0]) ); ++z)
					{
						Enemy temp ;
						temp = generateEnemy(removeSpaces (splitted[1]),startingp, targetp);
						
						e.push_back(temp);
					}
					
				}
				waveEnemies.push_back(e);


			}
			Wave w;
			w.enemies = waveEnemies;
			w.entryTimes = entryTimes;
			w.waveNumber = waves.size()+1;

			waves.push_back(w);
		}




	}

	vector<Point> strategicPoints;
	for (int i = 0; i < towerX.size(); ++i)
	{
		Point p;
		p.x = towerX[i];
		p.y = towerY[i];
		strategicPoints.push_back(p);
	}

	vector<Point> pathPoints;
	for (int i = 0; i < pathX.size(); ++i)
	{
		Point p;
		p.x = pathX[i];
		p.y = pathY[i];
		pathPoints.push_back(p);
	}


	l.path = pathPoints;
	l.strategicPoints =strategicPoints ;
	l.waves = waves;




	return l;
}