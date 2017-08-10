//stat.cpp
//====================
//
//include dependencies
#include "data.h"
#include "stat.h"
#include <fstream>
#include <iostream>
//====================

/*****StatBin Class*******/
StatBin::StatBin(double min, double max) {
    this->min_prog = min;
    this->max_prog = max;
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

    for (int i = 0; i < values.size(); i++) {
        ofs << progress.at(i) << ',' << values.at(i) << endl;
    }

    return;
}

/*****Base_Stat Class********/
Base_Stat::Base_Stat(string data_field) {
    this->data_field = data_field;

    this->bounds = {0.35, 0.7, 0.8, 0.9, 0.95, 0.97, 0.98, 0.99, 1.0};
    StatBin* sb;
    double low = 0.0;
    for (unsigned int i = 0; i < bounds.size(); i++) {
        // create area bin
        sb = new StatBin(low, bounds.at(i));
        bins.push_back(sb);
        //create pressure bin
        //  sb = new StatBin(low, bounds.at(i), "Pressure_Bin");
        //  pressure.push_back(sb);
        //update low
        low = bounds.at(i);
    }
}


void Base_Stat::calc_Stats() {
    
    for (unsigned int i = 0; i < bins.size(); i++) {
        bins.at(i)->calc_Stats();
    }

    return;
}

void Base_Stat::display() {
    
    ofstream ofs;
    string Filename = data_field + "_Stats.txt"; 

    ofs.open(Filename.c_str());

    ofs << "Statistical Data for Cell " << data_field << endl;

    for (unsigned int i = 0; i < bins.size(); i++) {
        bins.at(i)->display(ofs);
    }

    ofs.close();

    return;
}

void Base_Stat::print_Graph_Output() {

    string Filename = data_field + "_Stats.csv";
    ofstream ofs(Filename.c_str());

    for (int i = 0; i < bins.size(); i++) {
        bins.at(i)->print_Graph(ofs);
    }

    ofs.close();
    
    return;
}

/******Area_Stat Class*************/
Area_Stat::Area_Stat() : Base_Stat("Area") {}

void Area_Stat::add_values(vector<vector<Data*>>& cells) {
    
    for (unsigned int i = 0; i < cells.size(); i++) {

        for (unsigned int j = 0; j < cells.at(i).size(); j++) {
            double p = cells.at(i).at(j)->GrowthProgress;
            //find correct index for area bin by comparing cell progress
            //  with our set boundaries
            unsigned int k = 0;
            while ( (k < bounds.size()) && (p > bounds.at(k)) ) {
                k++;
            }
            //pass cell's area into correct area bin
            double a = cells.at(i).at(j)->CellArea;
            bins.at(k)->add_value(p,a);   
        }
    }

    return;
}

/*******Perim_Stat Class *************/
Perim_Stat::Perim_Stat() : Base_Stat("Perimeter") {}

void Perim_Stat::add_values(vector<vector<Data*>>& cells) {
    
    for (unsigned int i = 0; i < cells.size(); i++) {

        for (unsigned int j = 0; j < cells.at(i).size(); j++) {
            double p = cells.at(i).at(j)->GrowthProgress;
            //find correct index for perim bin by comparing cell progress
            //  with our set boundaries
            unsigned int k = 0;
            while ( (k < bounds.size()) && (p > bounds.at(k)) ) {
                k++;
            }
            //pass cell's perim into correct perim bin
            double a = cells.at(i).at(j)->CellPerim;
            bins.at(k)->add_value(p,a);
        }
    }

    return;
}

