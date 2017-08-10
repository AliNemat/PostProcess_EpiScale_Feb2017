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
        double mean;
        double std_dev;
        vector <double> values;
        vector <double> progress;
    public:
        StatBin(double min, double max);
        void add_value(double prog, double val);
        void calc_Stats();
        void display(ofstream& ofs);
        void print_Graph(ofstream& ofs);
};

class Base_Stat{
    protected:
        string data_field;
        vector <StatBin*> bins;
        vector <double> bounds;
    public:
        Base_Stat(string data_field);
        virtual void calc_Stats();
        virtual void display();
        virtual void print_Graph_Output();
        //Pure Virtual
        virtual void add_values(vector<vector<Data*>>& cells) = 0;
};

class Area_Stat: public Base_Stat{
    public:
        Area_Stat();
        virtual void add_values(vector<vector<Data*>>& cells);
};

class Perim_Stat: public Base_Stat{
    public:
        Perim_Stat();
        virtual void add_values(vector<vector<Data*>>& cells);
};

//============================
#endif

