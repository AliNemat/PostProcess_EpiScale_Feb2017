
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <conio.h>

struct Data {

	int CellRank;
	double GrowthProgress;
	double MembrGrowthProgress;
	int IsBoundaryCell;
	int NumOfNeighbors;
	double CellArea;
	double CellPerim;
	vector<int> NeighborCellsOrdered;
    vector<int> NumOfPointsInContactOrdered;
	int CurrentActiveIntnlNodes;
	int CurrentActiveMembrNodes;
	double CellCenter[3];

};

