//data.h
//=====================
#include <vector>
using namespace std;

struct Data {

	int CellRank;
	double GrowthProgress;
	double MembrGrowthProgress;
	bool IsBoundaryCell;
	int NumOfNeighbors;
	double CellArea;
	double CellPerim;
	vector<int> NeighborCellsOrdered;
    vector<int> NumOfPointsInContactOrdered;
	int CurrentActiveIntnlNodes;
	int CurrentActiveMembrNodes;
	vector <double> cellCenter ;
	vector <double> cellBasalLoc ;
	vector <double> cellNucLoc ;
	vector <double> cellApicalLoc ;

};

