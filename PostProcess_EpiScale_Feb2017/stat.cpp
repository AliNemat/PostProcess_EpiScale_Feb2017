//stat.cpp
//====================
//
//include dependencies
#include "data.h"
#include "stat.h"
#include <fstream>
#include <iostream>
//====================

/*****AreaGroup Class*******/
StatBin::StatBin(double min, double max, string name) {
    this->min_prog = min;
    this->max_prog = max;
    this->data_field = name;
}
void StatBin::add_value(double val) {
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

    ofs << data_field << " for cell progress: (" << min_prog << ", ";
    ofs << max_prog << ')' << endl;

    ofs << "    Total number of entries: " << values.size() << endl;
    ofs << "    Mean: " << this->mean << endl;
    ofs << "    Std. Deviation: " << this->std_dev << endl;

    return;
}

/*****AreaStat Class********/
Stat::Stat() {
    this->bounds = {0.35, 0.7, 0.8, 0.9, 0.95, 0.97, 0.98, 0.99, 1.0};
    StatBin* sb;
    double low = 0.0;
    for (unsigned int i = 0; i < bounds.size(); i++) {
        // create area bin
        sb = new StatBin(low, bounds.at(i), "Area_Bin");
        area.push_back(sb);
        //create pressure bin
        //  sb = new StatBin(low, bounds.at(i), "Pressure_Bin");
        //  pressure.push_back(sb);
        //update low
        low = bounds.at(i);
    }
}
void Stat::add_values(vector<vector<Data*>>& cells) {
    
    for (unsigned int i = 0; i < cells.size(); i++) {

        for (unsigned int j = 0; j < cells.at(i).size(); j++) {
            double p = cells.at(i).at(j)->GrowthProgress;
            //find correct index for area group by comparing cell progress
            //  with our set boundaries
            unsigned int k = 0;
            while ( (k < bounds.size()) && (p > bounds.at(k)) ) {
                k++;
            }
            //pass cell's area into correct area grouping
            double a = cells.at(i).at(j)->CellArea;
            area.at(k)->add_value(a);   
            //pass cell's pressure into correct pressure grouping
            //   a = cells.at(i).at(j)->CellPressure;
            //   pressure.at(k)->add_value(a);
        }
    }

    return;
}

void Stat::calc_Stats() {
    
    for (unsigned int i = 0; i < area.size(); i++) {
        area.at(i)->calc_Stats();
    }

    return;
}

void Stat::display() {
    
    ofstream ofs;
    ofs.open("Area_Stats.txt");

    ofs << "Statistical Data for Cell Area" << endl;

    for (unsigned int i = 0; i < area.size(); i++) {
        area.at(i)->display(ofs);
    }

    ofs.close();

    return;
}

