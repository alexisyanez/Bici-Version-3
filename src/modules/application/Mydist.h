/*
 * Mydist.h
 *
 *  Created on: May 8, 2018
 *      Author: root
 */

#ifndef MYDIST_H_
#define MYDIST_H_

#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <random>
#include <omnetpp.h>
#include <stdlib.h>
#include <stdint.h>

class Mydist {
public:
    Mydist();
    virtual ~Mydist();
    virtual void initialize();
    double getRandValLowSpeed();
    double getRandValMediumSpeed();
    double getRandValHighSpeed();

private:
    void split(const std::string &s, char delim, std::vector<double> &elems);

    std::vector<double> VectorDistLS;
    std::vector<double> VectorDistMS;
    std::vector<double> VectorDistHS;
};

#endif /* MYDIST_H_ */
