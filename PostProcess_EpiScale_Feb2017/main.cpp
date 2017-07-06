//main.cpp
//======================
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include "data.h"
#include "area.h"

using namespace std;
  
bool parse_File(string, vector<Data*>&);

int main()
{
    vector<vector<Data*>> data;
	vector<Data*> cells;
    string  Initial ("detailedStat_B_") ; 
    string Format (".txt"); 
    string Number;
    string FileName;
    int digits;
    bool Finished = false;

    for (int Ti = 0; !Finished; Ti++)
    {
        digits = ceil(log10(Ti + 1)); 
        if (digits==1 || digits == 0) {
            Number = "0000" + to_string(Ti);	
        }
        else if (digits == 2) {
            Number = "000" + to_string(Ti);
        }
        else if (digits == 3) {
            Number = "00" + to_string(Ti);
        }
        else if (digits == 4) {
            Number = "0" + to_string(Ti);
        }

		FileName = Initial + Number + Format;
        //parse_File returns:
        //  false if it can't read file => Finished should be true
        //  true if it can read file => Finished should be false
        Finished = !parse_File(FileName,cells);

        if (!Finished) {
            //push file's cell data onto main 2d vector
            data.push_back(cells);
            //clear temp vector for next file
            cells.clear();
        }

    } //finished reading all the files

    // Computing Cell Area statistical analysis
    AreaStat area;;
    area.add_values(data);
    area.calc_Stats();
    area.display();

    return 0;
}

bool parse_File(string FileName, vector<Data*>& cells) {
    ifstream ifs;

    ifs.open(FileName.c_str());

    if (!ifs.is_open()) {
        cout << FileName << " is not available" << endl;
        //return false because it couldn't read file
        return false;
    }

    cout << FileName << " is open" << endl;

    stringstream ss; 
    string line;
    string temp;
    int num;
    double val;
    Data* cell;

    // while loop to parse one file
    while (getline(ifs, line)); {
        ss.str(line);
        getline(ss,temp,':');
            
        if(temp == "CellRank") {
            ss >> num;
            if (num > 0) {
                //first push_back old cell onto vector
                cells.push_back(cell);
            }
            //creates new current cell to store information
            cell = new Data;
            cell->CellRank = num;
        }
        else if (temp == "GrowthProgress") {
            ss >> val;
            cell->GrowthProgress = val;
        }
        else if (temp == "MembrGrowthProgress") {
            ss >> val;
            cell->MembrGrowthProgress = val;
        }
        else if (temp == "IsBoundrayCell") { //fix later
            ss >> num;
            cell->IsBoundaryCell = num;
        }
        else if (temp == "NumOfNeighbors") {
            ss >> num;
            cell->NumOfNeighbors = num;
        }
        else if (temp == "CellArea") {
            ss >> val;
            cell->CellArea = val;
        }
        else if (temp == "CellPerim") {
            ss >> val;
            cell->CellPerim = val;
        }
        else if (temp == "NeighborCellsOrdered") {
            vector<int> neigh;
            //throw away the '{' and '}'
            getline(ss,temp,'{');
            getline(ss,temp,'}');
            ss.clear();
            ss.str(temp);
            while(!ss.eof()) {
                ss >> num;
                neigh.push_back(num);
            }
            //at the moment, pushes one too many
            neigh.pop_back();
            cell->NeighborCellsOrdered = neigh;
        }
        else if (temp == "NumberOfPointsInContactOrdered") {
            vector<int> points;
            //throw away the '{' and '}'
            getline(ss,temp,'{');
            getline(ss,temp,'}');
            ss.clear();
            ss.str(temp);
            while(!ss.eof()) {
                ss >> num;
                points.push_back(num);
            }
            //at the moment, pushes one too many
            points.pop_back();
            cell->NeighborCellsOrdered = points;
        }
        else if (temp == "CurrentActiveIntnlNode") {
            ss >> num;
            cell->CurrentActiveIntnlNodes = num;
        }
        else if (temp == "CurrentActiveMembrNodes") {
            ss >> num;
            cell->CurrentActiveMembrNodes = num;
        }
        else if (temp == "CellCenter") {
            //for later
        }
        else {
            //come across some other string
            cout << "Error: Unknown Data Field: " << temp << endl;
        }

        //clear stringstream for next input string
        ss.clear();

    } //finished reading one file

    return true;
}


