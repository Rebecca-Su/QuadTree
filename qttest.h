#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>

using std::string;
using std::stoi;
using std::cout;
using std::endl;
using std::min;
using std::max;
using std::cin;
using std::stringstream;
using std::vector;

class City
{
public:
    City(string in_name, double in_x, double in_y, int in_p, int in_r, int in_s);
	double getValue(string in_attr);
    City* getNextCity(string in_d);

private:
    City * nw;
    City * ne;
    City * sw;
    City * se;
    string name;
    double x;   //longitude
    double y;   //latitude
    int p;   //population
    int r;   //cost of living
    int s;   //average net salary
    friend class QuadTree;
};

class QuadTree
{
public:
    QuadTree();
    ~QuadTree();
    bool i(string in_name, double in_x, double in_y, int in_p, int in_r, int in_s);
    string s(double in_x, double in_y);
    void print(City * in_ptr);
    void clear(City* &in_ptr);
    int size();
    int qMax(City* in_ptr, string in_attr);
    int qMin(City* in_ptr, string in_attr);
    int qTotal(City* in_ptr, string in_attr);
    City * getCity(City* in_ptr, double in_x, double in_y);
    bool isDEmtpy(City* in_ptr, string in_d);
	City * getRoot();
private:
    City * root;
    int treeSize;
};
