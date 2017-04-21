
using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <conio.h>

struct Data {

	int CellRank;
	double GrowthProgress;
	double MembrGrowthProgress;
	int IsBoundrayCell;
	int NumOfNeighbors;
	double CellArea;
	double CellPerim;
	double CurrentActiveIntnlNode;
	double CurrentActiveMembrNodes;
	vector <int> NeighborCells;
	double CellCenter[2];

};

