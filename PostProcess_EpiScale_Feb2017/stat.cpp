//stat.cpp
//====================
//
//include dependencies
#include "data.h"
#include "stat.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
//====================

/*****StatBin Class*******/
StatBin::StatBin(double min, double max) {
    this->min_prog = min;
    this->max_prog = max;
}

double StatBin::get_mean() {
	return mean;
}

void StatBin::add_value(double prog, double val) {
    progress.push_back(prog);
    values.push_back(val);
    return;
}
void StatBin::calc_Stats() {
    //first: calculate mean
    double sum = 0;
    for (unsigned int i = 0; i < values.size(); i++) {
        sum += values.at(i);
    }

    this->mean = sum / values.size();

    //second: calc std deviation
    sum = 0;
    for (unsigned int i = 0; i < values.size(); i++) {
        sum += pow((values.at(i) - this->mean),2.0);
    }
    this->std_dev = sqrt(sum / (values.size() - 1));

	//calculate z-score for each value
	double z = 0.0;
	for (unsigned int i = 0; i < values.size(); i++) {
		z = ( (values.at(i) - this->mean) / this->std_dev );
		if ( fabs(z) > 4.5 ) {
			cout << "Z: " << z << endl;
		}
		z_scores.push_back(z);
	}

	/*
	//recalc mean and std dev
	int count = 0;
	sum = 0;
    for (unsigned int i = 0; i < values.size(); i++) {
        if ( fabs(z_scores.at(i)) < 4.5 ) {
			sum += values.at(i);
			count++;
		}
    }

    this->mean = sum / count;

    //second: calc std deviation
    sum = 0;
    for (unsigned int i = 0; i < values.size(); i++) {
		if ( fabs(z_scores.at(i)) < 4.5 ) {
        	sum += pow((values.at(i) - this->mean),2.0);
		}
    }
    this->std_dev = sqrt(sum / (count - 1));
	*/

    return;
}
void StatBin::display(ofstream& ofs) {

    ofs << " For cell progress: (" << min_prog << ", ";
    ofs << max_prog << ')' << endl;

    ofs << "    Total number of entries: " << values.size() << endl;
    ofs << "    Mean: " << this->mean << endl;
    ofs << "    Std. Deviation: " << this->std_dev << endl;

    return;
}

void StatBin::print_Graph(ofstream& ofs) {

	ofs << ((min_prog + max_prog) / 2) << ',' << mean << ',' << (2 * std_dev) << endl;

	return;
}

void StatBin::print_Raw_Data(ofstream& ofs) {

	for (unsigned int i = 0; i + 1 < values.size(); i++) {
		ofs << values.at(i) << ',';
	}
	ofs << values.at(values.size() - 1) << endl;

	return;
}

/*****Base_Stat Class********/
Base_Stat::Base_Stat(string data_field, vector<double>& prog_bounds) {
    this->data_field = data_field;

	if ( prog_bounds.size() < 2 ) {
		cout << "ERROR: Can't construct Base_Stat -- prog_bounds is empty." << endl;
		exit(1);
	}

	this->bounds = prog_bounds;

    StatBin* sb;
    double low = prog_bounds.at(0);
    for (unsigned int i = 1; i < bounds.size(); i++) {
		//new stat_bin with particular prog bounds
        sb = new StatBin(low, bounds.at(i));
        bins.push_back(sb);
		//update low
        low = bounds.at(i);
    }

	cout << "bins size: " << bins.size() << endl;
	cout << "bounds size: " << bounds.size() << endl;
}


void Base_Stat::calc_Stats() {
    
    for (unsigned int i = 0; i < bins.size(); i++) {
        bins.at(i)->calc_Stats();
    }

    return;
}

void Base_Stat::display(string folder) {
    
    ofstream ofs;
    string Filename = folder + '/' + data_field + "_Stats.txt"; 

    ofs.open(Filename.c_str());

    ofs << "Statistical Data for Cell " << data_field << endl;

    for (unsigned int i = 0; i < bins.size(); i++) {
        bins.at(i)->display(ofs);
    }

    ofs.close();

    return;
}

void Base_Stat::print_Graph_Output() {

    string Filename = "low/" + data_field + "_Stats.csv";
	ofstream ofs(Filename.c_str());

	ofs << "X,Y,error" << endl;

    for (int i = 0; i < bins.size(); i++) {
       	bins.at(i)->print_Graph(ofs);
    }

    ofs.close();
    
    return;
}

void Base_Stat::print_Raw_Data(string folder) {
	ofstream ofs;
	string Filename = folder + '/' + data_field + "_Raw.csv";
	ofs.open(Filename.c_str());

	for (unsigned int i = 0; i < bins.size(); i++) {
		bins.at(i)->print_Raw_Data(ofs);
	}

	ofs.close();
	return;
}

void Base_Stat::print_Simple_Graph(ofstream& ofs) {

	for (unsigned int i = 0; i < bins.size(); i++) {
		ofs << bins.at(i)->get_mean();
		if (i < bins.size() - 1) {
			ofs << ',';
		}
	}

	ofs << endl;

	return;
}

/******Area_Stat Class*************/
Area_Stat::Area_Stat(string datafield, vector<double>& bounds) : Base_Stat(datafield, bounds) {}

void Area_Stat::add_values(vector<vector<Data*>>& cells) {
    
	double prog = 0.0;
	double area = 0.0;
	bool is_boundary = false;

    for (unsigned int i = 0; i < cells.size(); i++) {

        for (unsigned int j = 0; j < cells.at(i).size(); j++) {
            prog = cells.at(i).at(j)->GrowthProgress;
			is_boundary = cells.at(i).at(j)->IsBoundaryCell;
            //find correct index for area bin by comparing cell progress
            //  with our set boundaries

			if ( (!is_boundary) && (prog > bounds.at(0)) ) {
			
            	unsigned int k = 1;

            	while ( k < bounds.size() ) {
                
					if ( prog < bounds.at(k) ) {
						area = cells.at(i).at(j)->CellArea;
						bins.at(k-1)->add_value(prog,area);
						break;
					}
					else {
						//not small enough for this bin
						k++;
					}
            	}
			}
			else {
				//not large enough for lowest bin
			}
        }
    }

    return;
}

/*******Perim_Stat Class *************/
Perim_Stat::Perim_Stat(string datafield, vector<double>& bounds) : Base_Stat(datafield, bounds) {}

void Perim_Stat::add_values(vector<vector<Data*>>& cells) {
    
	double prog = 0.0;
    double perim = 0.0;
	bool is_boundary = false;

	for (unsigned int i = 0; i < cells.size(); i++) {

        for (unsigned int j = 0; j < cells.at(i).size(); j++) {
            prog = cells.at(i).at(j)->GrowthProgress;
            is_boundary = cells.at(i).at(j)->IsBoundaryCell;
			//find correct index for perim bin by comparing cell progress
            //  with our set boundaries
            
			if ( (!is_boundary) && (prog > bounds.at(0)) ) {

				unsigned int k = 1;
			
				while ( k < bounds.size() ) {

					if ( prog < bounds.at(k) ) {
						perim = cells.at(i).at(j)->CellPerim;
						bins.at(k-1)->add_value(prog,perim);
						break;
					}
					else {
						//not small enough for this bin
						k++;
					}
				}
			}
			else {
				//not large enough for lowest bin
			}
		}
    }

    return;
}













