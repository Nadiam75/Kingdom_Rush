#include<vector>
#include <string>
using namespace std;

enum EnemyType { ORC, WOLF, ARMORED, DEMON};
enum ArmorType {NOARMOR, PHYSICAL , MAGICAL};
enum TowerType {ARCHER,	CANNON,	MAGE, ICY};
enum DamageType {PHYSICALDAMAGE,MAGICALDAMAGE};
enum Direction {UP , DOWN , RIGHT , LEFT};

struct Point 
{
	double x;
	double y;
};

struct Player 
{
	int health = 15;
	int money = 220;
};



struct Enemy
{
	bool isAlive;
	Point location;
	Point target;
	EnemyType type;
	int life;
	int speed;
	ArmorType armor;
	int reward;
	int damage;
	bool isIceAffected = false ;
	int iceEffectTime;
	Direction dir;
};

struct Wave
{
	vector<vector<Enemy>> enemies;
	vector<int> entryTimes;
	int waveNumber;

};

struct Tower
{
	Point position;
	TowerType towerType;
	DamageType damageType;
	int damage;
	int price;
	
	int fireRate;
	int fireRange;
};

struct Arrow
{
	Point position;
	Tower *tower; 
	Enemy *targetEnemy;
	bool isHit = false;
	int launchTime;
};



struct Level
{
	vector<Point> path;
	vector<Point> strategicPoints;
	vector<Wave> waves;
	string backgroundAddress;
};

struct Game
{
	Player player;
	Level currentLevel ;
	vector<Enemy> aliveEnemies;
	vector<Tower> builtTowers;
	vector<Arrow> firedArrows;
};

Player generatePlayer();
Enemy generateEnemy(string enemytype, Point p1, Point p2);