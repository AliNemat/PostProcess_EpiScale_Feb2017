//area.h

#ifndef _AREA_H_
#define _AREA_H_



class AreaGroup {
    private:
        double min_prog;
        double max_prog;
        double mean;
        double std_dev;
        vector<double> values;
    public:
        AreaGroup(double min, double max);
        double get_high_end();
        void add_value(double val);
        void calc_Stats();
        void display(ofstream& ofs);
};

class AreaStat{
    private:
        vector<AreaGroup*> groups;
        vector<double> bounds;
    public:
        AreaStat();
        void add_values(vector<vector<Data*>>& cells);
        void calc_Stats();
        void display();
};
