#include "qttest.h"

int main()
{
	QuadTree qt;
	City * qt_root;
	string line;
	string command;
	string param;
	string in_attr;
	size_t pos;
	vector<string> info;
	
	while(!cin.eof())
	{
		getline(cin, line);
		pos = line.find(" ");

		if(pos == string::npos)
			command = line;
		else
		{
			command = line.substr(0, pos); 
			param = line.substr(pos + 1, line.size());
		
			stringstream ss(param);
			while(ss.good())
			{
				getline(ss, in_attr, ';');
				info.push_back(in_attr);
			}
		}

		qt_root = qt.getRoot();

		if(command == "i")
		{
			bool is_inserted = qt.i(info[0], stod(info[1]), stod(info[2]), stoi(info[3]), stoi(info[4]), stoi(info[5]));
			if(is_inserted)
				cout << "success" << endl;
			else
				cout << "failure" << endl;
		}
		else if(command == "s")
		{
			//info[0] = x, info[1] = y
			double x = stod(info[0]);
			double y = stod(info[1]);
			if(qt.s(x, y) == "false")
				cout << "not found" << endl;
			else
				cout << "found " << qt.s(x, y) << endl;
		}
		else if(command == "q_max")
		{
			//info[0] = x, info[1] = y, info[2] = d, info[3] = attr
			double x = stod(info[0]);
            double y = stod(info[1]);
            City * city = qt.getCity(qt_root, x, y);
            if(city == nullptr || city->getValue("x") != x || city->getValue("y") != y || qt.isDEmtpy(city, info[2]) == true)
                cout << "failure" << endl;
            else
                cout << "max " << qt.qMax(city->getNextCity(info[2]), info[3]) << endl;
		}
		else if (command == "q_min")
		{
			//info[0] = x, info[1] = y, info[2] = d, info[3] = attr
            double x = stod(info[0]);
            double y = stod(info[1]);
            City * city = qt.getCity(qt_root, x, y);
            if(city == nullptr || city->getValue("x") != x || city->getValue("y") != y || qt.isDEmtpy(city, info[2]) == true)
                cout << "failure" << endl;
            else
                cout << "min " << qt.qMin(city->getNextCity(info[2]), info[3]) << endl;
		}
		else if (command == "q_total")
		{	
			//info[0] = x, info[1] = y, info[2] = d, info[3] = attr
			double x = stod(info[0]);
			double y = stod(info[1]);
			City * city = qt.getCity(qt_root, x, y);
			if(city == nullptr || city->getValue("x") != x || city->getValue("y") != y || qt.isDEmtpy(city, info[2]) == true)
				cout << "failure" << endl;
			else
				cout << "total " << qt.qTotal(city->getNextCity(info[2]), info[3]) << endl;
		}
		else if(command == "print")
		{
			qt.print(qt_root);
			if(qt_root != nullptr)
				cout << endl;
		}
		else if(command == "clear")
		{
			qt.clear(qt_root);
			cout << "success" << endl;
		}
		else if (command == "size")
		{
			cout << "tree size " << qt.size() << endl;		
		}
		info.clear();
	}
	
	return 0;
}
