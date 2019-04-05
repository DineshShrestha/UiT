#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>



struct Data {
    double x, y, z, rho;
};

class Datahandler {

public:
    std::vector<Data> loadData(const std::string fileName);
};

