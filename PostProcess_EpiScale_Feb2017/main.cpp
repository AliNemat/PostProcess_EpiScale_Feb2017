//main.cpp
//======================
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include "data.h"
#include "stat.h"

using namespace std;
  
bool parse_File(string, vector<Data*>&);
void parse_Folder(string, vector<vector<Data*>>&);
void calc_Stats(string, ofstream&, ofstream&, vector<double> bounds, vector<vector<Data*>>);

int main()
{
	//For each stat that you want to do a calculation on:
	//  -create ofstream for simple file output
	//  -other helper functions create more files, but this one is for 
	//   quick checks
	string p_out_file = "perim_graph.csv";
	ofstream ofs_p(p_out_file.c_str());
	string a_out_file = "area_graph.csv";
	ofstream ofs_a(a_out_file.c_str());

	//Name of folders that hold data output files
	vector<string> folders = {"Folder1", "Folder2", "Folder3"};
    vector<vector<Data*>> data;
	
	//Bounds vectors
	vector<double> bounds = {0.0, 0.45, 0.85, 0.95, 0.98, 1.0};

	for (unsigned int i = 0; i < folders.size(); i++) {
		//get Data from folder
		parse_Folder(folders.at(i), data);		
		//calc area and perim stats
		calc_Stats(folders.at(i), ofs_a, ofs_p, bounds, data);
		data.clear();
	}
   
    cout << "Finished with everything" << endl;

	ofs_p.close();
	ofs_a.close();

    return 0;
}

void calc_Stats(string folder, ofstream& ofs_area, ofstream& ofs_perim, 
				vector<double> bounds ,vector<vector<Data*>> data) {

	string filename;

    // Computing Cell Area statistical analysis
    cout << "Compute Area Stats" << endl;
	filename = folder + "_Area";
    Area_Stat area(filename, bounds);
    area.add_values(data);
    area.calc_Stats();
    area.display(folder);
	area.print_Raw_Data(folder);
	area.print_Simple_Graph(ofs_area);

    cout << "Area completed" << endl << endl;
    
    cout << "Compute Perimeter Stats" << endl;
	
	filename = folder + "_Perim";
	Perim_Stat perim(filename, bounds);
    perim.add_values(data);
    perim.calc_Stats();
    perim.display(folder);
	perim.print_Raw_Data(folder);
	perim.print_Simple_Graph(ofs_perim);
	
	cout << "Perim completed" << endl;
 
	return;
}

void parse_Folder(string folder_name, vector<vector<Data*>>& data) {

	vector<Data*> cells;
    string Initial = folder_name + "/detailedStat_B_"; 
    string Format (".txt"); 
    string Number;
    string FileName;
    int digits;
    bool Finished = false;

    for (int Ti = 1; (!Finished) && (Ti < 400); Ti++)
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

	return;
}


bool parse_File(string FileName, vector<Data*>& cells) {
    
    ifstream ifs(FileName.c_str());

    if (!ifs) {
        cout << FileName << " is not available" << endl;
        //return false because it couldn't read file
        return false;
    }
    //cout << FileName << " is good" << endl;

    stringstream ss; 
    string line;
    string temp;
    int num;
    double val;
    Data* cell;

    // while loop to parse one file
    while (getline(ifs,line)) {
        //cout << "line: " << line << endl;
        ss.str(line);
        getline(ss,temp,':');

        //cout << "temp: " << temp << endl;
            
        if(temp == "CellRank") {
            ss >> num;
            //cout << "CellRank: " << num << endl;
            if (num > 0) {
                //first push_back old cell onto vector
                cells.push_back(cell);
            }
            //creates new current cell to store information
            cell = new Data;
            cell->CellRank = num;
        }
        else if (temp == "    GrowthProgress") {
            ss >> val;
            cell->GrowthProgress = val;
        }
        else if (temp == "    MembrGrowthProgress") {
            ss >> val;
            cell->MembrGrowthProgress = val;
        }
        else if (temp == "    IsBoundrayCell") { //fix later
            ss >> num;
			if (num == 0) {
				cell->IsBoundaryCell = false;
			}
			else if (num == 1) {
				cell->IsBoundaryCell = true;
			}
			else {
				cout << "ISBOUNDARYCELL ERROR -- num = " << num << endl;
			}
        }
        else if (temp == "    NumOfNeighbors") {
            ss >> num;
            cell->NumOfNeighbors = num;
        }
        else if (temp == "    CellArea") {
            ss >> val;
            cell->CellArea = val;
        }
        else if (temp == "    CellPerim") {
            ss >> val;
            cell->CellPerim = val;
        }
        else if (temp == "    NeighborCellsOrdered") {
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
        else if (temp == "    NumberOfPointsInContactOrdered") {
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
        else if (temp == "    CurrentActiveIntnlNode") {
            ss >> num;
            cell->CurrentActiveIntnlNodes = num;
        }
        else if (temp == "    CurrentActiveMembrNodes") {
            ss >> num;
            cell->CurrentActiveMembrNodes = num;
        }
        else if (temp == "    CellCenter") {
            //for later
        }

        //clear stringstream for next input string
        ss.clear();

    } //finished reading one file

    ifs.close();

    return true;
}


