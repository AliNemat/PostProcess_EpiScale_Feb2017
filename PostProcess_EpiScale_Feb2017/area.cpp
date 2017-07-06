//area.cpp
//====================
class Data;
//include dependencies
#include "data.h"
#include "area.h"
#include <fstream>
//====================

/*****AreaGroup Class*******/
AreaGroup::AreaGroup(double min, double max) {
    this->min_prog = min;
    this->max_prog = max;
}
double AreaGroup::get_high_end() {
    return max_prog;
}
void AreaGroup::add_value(double val) {
    values.push_back(val);
    return;
}
void AreaGroup::calc_Stats() {
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
void AreaGroup::display(ofstream& ofs) {

    ofs << "AreaGroup for cell progress: (" << min_prog << ", ";
    ofs << max_prog << ')' << endl;

    ofs << "    Total number of entries: " << values.size() << endl;
    ofs << "    Mean: " << this->mean << endl;
    ofs << "    Std. Deviation: " << this->std_dev << endl;

    return;
}

/*****AreaStat Class********/
AreaStat::AreaStat() {
    this->bounds = {0.35, 0.7, 0.8, 0.9, 0.95, 0.97, 0.98, 0.99, 1.0};
    AreaGroup* ag;
    double low = 0.0;
    for (unsigned int i = 0; i < bounds.size(); i++) {
         ag = new AreaGroup(low, bounds.at(i));
         groups.push_back(ag);
    }
}
void AreaStat::add_values(vector<vector<Data*>>& cells) {
    
    for (unsigned int i = 0; i < cells.size(); i++) {

        for (unsigned int j = 0; j < cells.at(i).size(); j++) {
            double p = cells.at(i).at(j)->GrowthProgress;
            //find correct index for area group by comparing cell progress
            //  with our set boundaries
            unsigned int k = 0;
            while ( (k < bounds.size()) && (p > bounds.at(k)) ) {
                k++;
            }
            //pass cell's area into corrent area grouping
            double a = cells.at(i).at(j)->CellArea;
            groups.at(k)->add_value(a);   
        }
    }

    return;
}

void AreaStat::calc_Stats() {
    
    for (unsigned int i = 0; i < groups.size(); i++) {
        groups.at(i)->calc_Stats();
    }

    return;
}

void AreaStat::display() {
    
    ofstream ofs;
    ofs.open("Area_Stats.txt");

    ofs << "Statistical Data for Cell Area" << endl;

    for (unsigned int i = 0; i < groups.size(); i++) {
        groups.at(i)->display(ofs);
    }

    ofs.close();

    return;
}

