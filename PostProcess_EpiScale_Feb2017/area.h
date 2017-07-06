//area.h
//===========================
//include guard
#ifndef _AREA_H_INCLUDED_
#define _AREA_H_INCLUDED_
//===========================
//forward declare dependencies
class Data;
//===========================
//include dependencies
#include <vector>
#include <fstream>
#include <math.h>
//===========================
using namespace std;

class AreaGroup {
    private:
        double min_prog;
        double max_prog;
        double mean;
        double std_dev;
        vector <double> values;
    public:
        AreaGroup(double min, double max);
        double get_high_end();
        void add_value(double val);
        void calc_Stats();
        void display(ofstream& ofs);
};

class AreaStat{
    private:
        vector <AreaGroup*> groups;
        vector <double> bounds;
    public:
        AreaStat();
        void add_values(vector<vector<Data*>>& cells);
        void calc_Stats();
        void display();
};

//============================
#endif

