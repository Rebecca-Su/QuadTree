#include "qttest.h"

City::City(string in_name, double in_x, double in_y, int in_p, int in_r, int in_s)
{
    nw = nullptr;
    ne = nullptr;
    sw = nullptr;
    se = nullptr;
    
    name = in_name;
    x = in_x;
    y = in_y;
    p = in_p;
    r = in_r;
    s = in_s;
}

QuadTree::QuadTree()
{
    treeSize = 0;
	root = nullptr;
}

QuadTree::~QuadTree()
{
    clear(root);
}

bool QuadTree::i(string in_name, double in_x, double in_y, int in_p, int in_r, int in_s)
{
    City* city = getCity(root, in_x, in_y);
    
    City * new_city = new City(in_name, in_x, in_y, in_p, in_r, in_s);
    
    if(root == nullptr)
    {
        root = new_city;
        treeSize ++;
        return true;
    }
    
    if(city->x == in_x && city->y == in_y)
        return false;
    else if(city->x != in_x || city->y != in_y)
    {
        if((in_x >= city->x) && (in_y > city->y))
            city->ne = new_city;
        if((in_x < city->x) && (in_y >= city->y))
            city->nw = new_city;
        if((in_x <= city->x) && (in_y < city->y))
            city->sw = new_city;
        if((in_x > city->x) && (in_y <= city->y))
            city->se = new_city;
        treeSize ++;
        return true;
    }
    
    return false;
}

string QuadTree::s(double in_x, double in_y)
{
    City * city = getCity(root, in_x, in_y);
    
    if(city == nullptr || city->x != in_x || city->y != in_y)
        return "false";
    return city->name;
}

void QuadTree::print(City * in_ptr)
{
    if(in_ptr == nullptr)
        return;
    
    print(in_ptr->ne);
    print(in_ptr->nw);
    cout << in_ptr->name << " ";
    print(in_ptr->sw);
    print(in_ptr->se);
}

void QuadTree::clear(City * &in_ptr)
{
    if(in_ptr == nullptr)
        return;
 	   
    clear(in_ptr->nw);
    clear(in_ptr->ne);
    clear(in_ptr->sw);
    clear(in_ptr->se);
    
	if(treeSize == 1)
	{
		delete root;
		root = nullptr;
		this->treeSize = 0;
		return;
	}
	delete in_ptr;
    in_ptr = nullptr;
	treeSize--;
}

int QuadTree::size()
{
    return treeSize;
}

int QuadTree::qMax(City* in_ptr, string in_attr)
{
    if(in_ptr == nullptr)
        return 0;
    
    int max_nw = max((int)in_ptr->getValue(in_attr), qMax(in_ptr->getNextCity("NW"), in_attr));
    int max_ne = max((int)in_ptr->getValue(in_attr), qMax(in_ptr->getNextCity("NE"), in_attr));
    int max_sw = max((int)in_ptr->getValue(in_attr), qMax(in_ptr->getNextCity("SW"), in_attr));
    int max_se = max((int)in_ptr->getValue(in_attr), qMax(in_ptr->getNextCity("SE"), in_attr));
    return max(max(max_nw, max_ne), max(max_sw, max_se));
}

int QuadTree::qMin(City* in_ptr, string in_attr)
{
    int val = in_ptr->getValue(in_attr);
	
	if(in_ptr->getNextCity("NW") != nullptr)
		val = min(val, qMin(in_ptr->nw, in_attr));
	if(in_ptr->getNextCity("NE") != nullptr)
          val = min(val, qMin(in_ptr->ne, in_attr));
	if(in_ptr->getNextCity("SW") != nullptr)
          val = min(val, qMin(in_ptr->sw, in_attr));
	if(in_ptr->getNextCity("SE") != nullptr)
          val = min(val, qMin(in_ptr->se, in_attr));
    return val;
}

int QuadTree::qTotal(City* in_ptr, string in_attr)
{
    if(in_ptr == nullptr)
        return 0;
    
    return in_ptr->getValue(in_attr) +
            qTotal(in_ptr->getNextCity("NW"), in_attr) +
            qTotal(in_ptr->getNextCity("NE"), in_attr) +
            qTotal(in_ptr->getNextCity("SW"), in_attr) +
            qTotal(in_ptr->getNextCity("SE"), in_attr);
}

City* City::getNextCity(string in_d)
{
    if(in_d == "NW")
        return this->nw;
    if(in_d == "NE")
        return this->ne;
    if(in_d == "SW")
        return this->sw;
    if(in_d == "SE")
        return this->se;
    return nullptr;
}

double City::getValue(string in_attr)
{
    if(in_attr == "x")
        return this->x;
    if(in_attr == "y")
        return this->y;
    if(in_attr == "p")
        return this->p;
    if(in_attr == "r")
        return this->r;
    if(in_attr == "s")
        return this->s;
    return -1;
}

City * QuadTree::getCity(City* in_ptr, double in_x, double in_y)
{
    //if doesn't find the targeted city, return the last city in that direction
    if(in_ptr == nullptr
       || ((in_x >= in_ptr->x) && (in_y > in_ptr->y) && (in_ptr->ne == nullptr))
       || ((in_x < in_ptr->x) && (in_y >= in_ptr->y) && (in_ptr->nw == nullptr))
       || ((in_x <= in_ptr->x) && (in_y < in_ptr->y) && (in_ptr->sw == nullptr))
       || ((in_x > in_ptr->x) && (in_y <= in_ptr->y) && (in_ptr->se == nullptr))
       || ((in_ptr->x == in_x) && (in_ptr->y == in_y)))
        return in_ptr;
    
    if(in_x >= in_ptr->x && in_y > in_ptr->y)
        return getCity(in_ptr->ne, in_x, in_y);
    if(in_x < in_ptr->x && in_y >= in_ptr->y)
        return getCity(in_ptr->nw, in_x, in_y);
    if(in_x <= in_ptr->x && in_y < in_ptr->y)
        return getCity(in_ptr->sw, in_x, in_y);
    if(in_x > in_ptr->x && in_y <= in_ptr->y)
        return getCity(in_ptr->se, in_x, in_y);
    else
        return nullptr;
}

bool QuadTree::isDEmtpy(City* in_ptr, string in_d)
{
    if((in_d == "NW" && in_ptr->nw == nullptr)
       || (in_d == "NE" && in_ptr->ne == nullptr)
       || (in_d == "SW" && in_ptr->sw == nullptr)
       || (in_d == "SE" && in_ptr->se == nullptr))
        return true;
    else
        return false;
}

City * QuadTree::getRoot()
{
    return root;
}

