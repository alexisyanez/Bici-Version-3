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

#ifndef NODEINFO_H_
#define NODEINFO_H_

/**
 * Clase que encapsula la información proveniente de otro nodo
 */
class NodeInfo {

private:
    int srcAddress;
    int packageID;
    double xposition;
    double yposition;
    double xpositionGPSerror;
    double speed;
    double acceleration;
    double leaderAcceleration;
    double leaderSpeed;
    double TS; // Time Stamp

public:
    NodeInfo();
    virtual ~NodeInfo();
    void setSrcAddress(int sA);
    void setPackageID(int pI);
    void setXPosition(double xP);
    void setYPosition(double yP);
    void setXPositionGPSerror(double xPe);
    void setSpeed(double s);
    void setAcceleration(double a);
    void setLeaderAcceleration(double a);
    void setLeaderSpeed(double s);
    void setTS(double timeS);
    int getSrcAddress();
    int getPackageID();
    double getXPosition();
    double getYPosition();
    double getXPositionGPSerror();
    double getSpeed();
    double getAcceleration();
    double getLeaderAcceleration();
    double getLeaderSpeed();
    double getTS();


};

#endif /* NODEINFO_H_ */
