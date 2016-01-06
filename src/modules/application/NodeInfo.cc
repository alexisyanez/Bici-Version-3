//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "NodeInfo.h"

NodeInfo::NodeInfo()
{
    // TODO Auto-generated constructor stub

    srcAddress = -1;
    speed = 0;
    xposition = 0;
    yposition = 0;
    packageID = 0;
    acceleration = 0;
    leaderAcceleration = 0;
    leaderSpeed = 0;

}

NodeInfo::~NodeInfo()
{
    // TODO Auto-generated destructor stub
}

int NodeInfo::getSrcAddress()
{
    return srcAddress;
}

double NodeInfo::getSpeed()
{
    return speed;
}

double NodeInfo::getXPosition()
{
    return xposition;
}

double NodeInfo::getYPosition()
{
    return yposition;
}

double NodeInfo::getAcceleration()
{
    return acceleration;
}

int NodeInfo::getPackageID()
{
    return packageID;
}

double NodeInfo::getLeaderAcceleration()
{
    return leaderAcceleration;
}

double NodeInfo::getLeaderSpeed()
{
    return leaderSpeed;
}

void NodeInfo::setSrcAddress(int sA)
{
    srcAddress = sA;
}

void NodeInfo::setSpeed(double s)
{
    speed = s;
}

void NodeInfo::setXPosition(double xP)
{
    xposition = xP;
}

void NodeInfo::setYPosition(double yP)
{
    yposition = yP;
}

void NodeInfo::setPackageID(int pI)
{
    packageID = pI;
}

void NodeInfo::setAcceleration(double a)
{
    acceleration = a;
}

void NodeInfo::setLeaderAcceleration(double a)
{
    leaderAcceleration = a;
}

void NodeInfo::setLeaderSpeed(double s)
{
    leaderSpeed = s;
}

