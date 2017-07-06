//data.h
//=====================
#include <vector>
using namespace std;

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

