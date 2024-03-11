#include "LevelManager.h"

vector<vector<float>> LevelManager::initializeWave(int n) {

    srand(time(NULL));

    vector<vector<float>> EDRandList;

    for (int i = 0; i < n; i++) {

        vector<float> RandList;

        for (int j = 0; j <= 2; j++) {
            if (j == 1) {
                float w = rand() % 100;
                RandList.push_back(w);
            }
            else {
                float neg = rand() % 2;
                float w = rand() % 950;
                if (w == 0) {
                    float v = rand() % 950;
                    if (neg == 0) {
                        v = -v;
                    }
                    RandList.push_back(v);
                }
                else {
                    if (neg == 0) {
                        w = -w;
                    }
                    RandList.push_back(w);
                }
            }
        }

        EDRandList.push_back(RandList);
    }

    return EDRandList;

}

