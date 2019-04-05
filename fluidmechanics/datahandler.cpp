#include "datahandler.hpp"
#include<cstdio>
#include<iostream>

std::vector<Data> Datahandler::loadData(const std::string fileName) {

    // Open the file
    std::ifstream dataFile(fileName);
    std::string value;

	if (dataFile.is_open())
	{
		value = std::string((std::istreambuf_iterator<char>(dataFile)), std::istreambuf_iterator<char>());
		
	}
    else
        std::cerr << "ERROR: could not open file " << fileName.c_str() << std::endl;

    std::istringstream iss(value);

    std::vector<Data> temp;

    int i = 0;
    Data data;

	while (iss) {

		std::string datastring;
		iss >> datastring;
		double v = std::atof(datastring.c_str());



		switch (i) {
		case 0:
			data.x = v;
			i++;
			break;
		case 1:
			data.y = v;
			i++;
			break;
		case 2:
			data.z = v;
			i++;
			break;
		case 3:
			data.rho = v;
			i = 0;
			break;
		}

		if (i == 0)
			if (data.rho < 1000.f)
			{

			temp.push_back(data);
		
			}
    }
	
    return temp;
}
