//
// Copyright (C) 2005 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "CustomRectangleMobility.h"
#include "FWMath.h"
//Libraries for random operations
#include<stdlib.h>
#include<time.h>
#include "FindModule.h"

using namespace std;
using std::endl;

Define_Module(CustomRectangleMobility);

CustomRectangleMobility::CustomRectangleMobility()
{
    d = 0;
    corner1 = corner2 = corner3 = corner4 = 0;
    stopModule = false;

    currentSpeed = 0;

    acceleration = 0;

    totalTime = 0;
    totalDistance = 0;

    variability = 0;



}
std::string CustomRectangleMobility::logName(void) const
{

    std::ostringstream ost;
        const cModule *const parent = findHost();
        parent->hasPar("logName") ?
            ost << parent->par("logName").stringValue() : ost << parent->getName();
        ost << "[" << parent->getIndex() << "]";

    return ost.str();
}

const cModule* CustomRectangleMobility::findHost(void) const
{
    return FindModule<>::findHost(this);
}

void CustomRectangleMobility::initialize(int stage)
{


    CustomMovingMobilityBase::initialize(stage);
    EV << "initializing RectangleMobility stage " << stage << endl;
    if (stage == 0)
    {

        accelerationLeaderSignal = registerSignal("accelerationLeader");


        //Obtener tiempo y distancia totales para llegar a la meta
        totalTime = par("totalTime");
        totalDistance = par("totalDistance");

        //Obtener la aceleracion
        acceleration = par("acceleration");
        variability = par("variability");

        //Obtener bandera para saber si es lider
        leader = par("leader");
        //Inicializa a todos los nodos con una velocidad fija (objetivo)
        currentSpeed =totalDistance / totalTime;

        //Alimentar la funcion aleatoria
        srand(time(NULL));

        //currentSpeed = minSpeed + ((maxSpeed - minSpeed) * rand()) / (RAND_MAX + 1.0);

        //If it's stationary
        stationary = (currentSpeed == 0);

        // calculate helper variables
        double dx = constraintAreaMax.x - constraintAreaMin.x;
        double dy = constraintAreaMax.y - constraintAreaMin.y;
        corner1 = dx;
        corner2 = corner1 + dy;
        corner3 = corner2 + dx;
        corner4 = corner3 + dy;

        // determine start position
        double startPos = par("startPosition");
        startPos = fmod(startPos, 4);
        if (startPos < 1)
            d = startPos * dx; // top side
        else if (startPos < 2)
            d = corner1 + (startPos - 1) * dy; // right side
        else if (startPos < 3)
            d = corner2 + (startPos - 2) * dx; // bottom side
        else
            d = corner3 + (startPos - 3) * dy; // left side
        WATCH(d);
    }
}

void CustomRectangleMobility::initializePosition()
{
    move();
}

void CustomRectangleMobility::move()
{
    double elapsedTime = (simTime() - lastUpdate).dbl();
    double previousSpeed = currentSpeed;
    EV << logName() << "::" << getClassName() << " Running Move() " << endl;
    //Si el metodo stop fue invocado previamente, se detiene el movimiento del modulo (speed=0)
    if (stopModule == true)
    {
        currentSpeed = 0;
        acceleration = 0;

        //De lo contario, calcular velocidad aleatoria
    }
    else
    {
        if (leader == true)
        {
            //Minima velocidad permitida en la simulacion
            double vObj = totalDistance / totalTime;
            EV << logName() << "::" << getClassName() << " Minimum speed: " << vObj << endl;

            //Recalcular la velocidad mientras sea menor o mayor a la permitida
            //FIXED: Para la primera vez que se mueve, currentSpeed debe inicializarse en el rango permitido
            do
            {
                double floor = vObj - vObj * variability;
                double ceiling = vObj + vObj * variability;
                double range = ceiling - floor;

                currentSpeed = floor + (range * rand()) / (RAND_MAX + 1.0);
                acceleration = (currentSpeed-previousSpeed)/elapsedTime;

            }while (currentSpeed < (vObj - vObj * variability) || currentSpeed > (vObj + vObj * variability));

            //Emitir se朼l para la aceleraci梟 del l抎er
            emit(accelerationLeaderSignal,acceleration);

        }else
        { //Actualiza velocidad de acuerdo a la aceleraci贸n del platoon para el resto de nodos

            currentSpeed += acceleration * elapsedTime;

        }


    }



    EV << " " << logName() << "::" << getClassName() << " Acceleration= " << acceleration << endl;

    d += currentSpeed * elapsedTime;

    while (d < 0)
        d += corner4;

    while (d >= corner4)
        d -= corner4;

    if (d < corner1)
    {
        // top side
        lastPosition.x = constraintAreaMin.x + d;
        lastPosition.y = constraintAreaMin.y;
    }
    else if (d < corner2)
    {
        // right side
        lastPosition.x = constraintAreaMax.x;
        lastPosition.y = constraintAreaMin.y + d - corner1;
    }
    else if (d < corner3)
    {
        // bottom side
        lastPosition.x = constraintAreaMax.x - d + corner2;
        lastPosition.y = constraintAreaMax.y;
    }
    else
    {
        // left side
        lastPosition.x = constraintAreaMin.x;
        lastPosition.y = constraintAreaMax.y - d + corner3;
    }

    EV << " " << logName() << "::" << getClassName() << " xpos= " << lastPosition.x << " ypos=" << lastPosition.y << " currentSpeed=" << currentSpeed << " accel="
            << acceleration << endl;
    EV << " " << logName() << "::" << getClassName() << " previous Speed=" << previousSpeed << " elapsed = " << elapsedTime << endl;
}

/**
 * Detener el m贸dulo
 */
void CustomRectangleMobility::stop()
{
    stopModule = true;
}

/**
 * Obtener velocidad actual del m贸dulo
 */
double CustomRectangleMobility::getMySpeed()
{
    return currentSpeed;
}

/**
 * Obtener aceleraci贸n actual del m贸dulo
 */
double CustomRectangleMobility::getMyAcceleration()
{
    return acceleration;
}

/**
 * Modificar aceleraci贸n actual del m贸dulo
 */
void CustomRectangleMobility::setAcceleration(double newAcceleration)
{
    acceleration = newAcceleration;
}

