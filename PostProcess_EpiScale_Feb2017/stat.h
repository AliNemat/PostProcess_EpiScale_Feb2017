//stat.h
//===========================
//include guard
#ifndef _STAT_H_INCLUDED_
#define _STAT_H_INCLUDED_
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

class StatBin {
    private:
        double min_prog;
        double max_prog;
        string data_field;
        double mean;
        double std_dev;
        vector <double> values;
    public:
        StatBin(double min, double max, string name);
        void add_value(double val);
        void calc_Stats();
        void display(ofstream& ofs);
};

class Stat{
    private:
        vector <StatBin*> area;
        vector <StatBin*> pressure;
        vector <double> bounds;
    public:
        Stat();
        void add_values(vector<vector<Data*>>& cells);
        void calc_Stats();
        void display();
};

//============================
#endif

