#pragma once
#include <vector>
#include <time.h>  

using namespace std;

class LevelManager
{
private:
	vector<vector<float>> EDRandList;

public:
	vector<vector<float>> initializeWave(int numberEnemies);

};

