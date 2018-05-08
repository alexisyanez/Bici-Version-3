/*
 * Mydist.cc
 *
 *  Created on: May 8, 2018
 *      Author: root
 */

#include <Mydist.h>
#include <random>
#include <omnetpp.h>
#include <stdlib.h>
#include <stdint.h>

using namespace std;
using std::endl;

Mydist::Mydist() {
    // TODO Auto-generated constructor stub

}

Mydist::~Mydist() {
    // TODO Auto-generated destructor stub
}

void Mydist::initialize(){
    split("DistVectorLowSpeed.csv",',',VectorDistLS);
    split("DistVectorMediumSpeed.csv",',',VectorDistMS);
    split("DistVectorHighiSpeed.csv",',',VectorDistHS);

}

double Mydist::getRandValLowSpeed(){
    int i = intuniform(0,sizeof(VectorDistLS));
    return VectorDistLS[i];
}

double Mydist::getRandValMediumSpeed(){
    int i = intuniform(0,sizeof(VectorDistMS));
    return VectorDistMS[i];
}

double Mydist::getRandValHighSpeed(){
    int i = intuniform(0,sizeof(VectorDistHS));
    return VectorDistHS[i];
}

void Mydist::split(const string &s, char delim, vector<double> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(atof(item.c_str()));
    }
    //return elems;
}
