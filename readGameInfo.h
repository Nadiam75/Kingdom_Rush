#include <fstream>
#include <vector>
#include <algorithm>
#include "model.h"
using namespace std;
vector<string> stringSplitter(string s, char splitter );
vector<string> readFile(string path);
Level readLevelInfo(vector <string> v);
int getTimeStamp(string s);
string removeSpaces(string s);