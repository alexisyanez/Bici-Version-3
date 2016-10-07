//
// Author: Emin Ilker Cetinbas (niw3_at_yahoo_d0t_com)
// Copyright (C) 2005 Emin Ilker Cetinbas
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "CustomLinearMobility.h"
#include "FWMath.h"
#include "FindModule.h"

Define_Module(CustomLinearMobility);

CustomLinearMobility::CustomLinearMobility()
{
    speed = 0;
    speed2 = 0;
    speed3 = 0;

    angle = 0;
    acceleration = 0;
    stopModule = false;

    currentSpeed = 0;

    acceleration = 0;

    totalTime = 0;
    totalDistance = 0;

    variability = 0;
    variability2 = 0;
    variability3 = 0;
}

std::string CustomLinearMobility::logName(void) const
{

    std::ostringstream ost;
    const cModule * const parent = findHost();
    parent->hasPar("logName") ? ost << parent->par("logName").stringValue() : ost << parent->getName();
    ost << "[" << parent->getIndex() << "]";

    return ost.str();
}

const cModule* CustomLinearMobility::findHost(void) const
{
    return FindModule<>::findHost(this);
}

void CustomLinearMobility::initialize(int stage)
{

    accelerationLeaderSignal = registerSignal("accelerationLeader");

    CustomMovingMobilityBase::initialize(stage);

    //EV_TRACE << "initializing CustomLinearMobility stage " << stage << endl;
    if (stage == 0)
    {
        currentSpeed = totalDistance / totalTime;

        speed = par("speed");
        speed2 = par("speed2");
        speed3 = par("speed3");

        speedDuration = par("speedDuration");

        angle = fmod((double) par("angle"), 360);
        acceleration = par("acceleration");
        stationary = (currentSpeed == 0) && (acceleration == 0.0);

        //Obtener tiempo y distancia totales para llegar a la meta
        totalTime = par("totalTime");
        totalDistance = par("totalDistance");

        //Obtener la aceleracion
        acceleration = par("acceleration");
        variability = par("variability");
        variability2 = par("variability2");
        variability3 = par("variability3");
        //Obtener bandera para saber si es lider
        leader = par("leader");
        //Inicializa a todos los nodos con una velocidad fija (objetivo)
        currentSpeed = speed;

    }
    else if (stage == 2)
    {
        move();
    }
}

void CustomLinearMobility::move()
{
    // Aplicar diferentes velocidades y variabilidad de la misma según corresponda al intervalo
    if (MultiSpeed == true)
    {
        if ((simTime()).dbl() <= speedDuration) //
        {
            speed = par("speed");
            variability = par("variability");
        }

        if (speedDuration < (simTime()).dbl() && (simTime()).dbl() <= 2*speedDuration)
        {
            speed = speed2;
            variability = variability2;
        }

        if (2*speedDuration < (simTime()).dbl() && (simTime()).dbl() <= 3*speedDuration)
        {
            speed = speed3;
            variability = variability3;
        }
        if (3*speedDuration <(simTime()).dbl() && (simTime()).dbl() <= 4*speedDuration)
        {
            speed = par("speed");
            variability = par("variability");
        }
        if (4*speedDuration <(simTime()).dbl() && (simTime()).dbl() <= 5*speedDuration)
        {
            speed = speed2;
            variability = variability2;
        }
        if (5*speedDuration <(simTime()).dbl() && (simTime()).dbl() <= 6*speedDuration)
        {
            speed = speed3;
            variability = variability3;
        }
        if (6*speedDuration <(simTime()).dbl() && (simTime()).dbl() <= 7*speedDuration)
        {
            speed = par("speed");
            variability = par("variability");
        }
        if (7*speedDuration <(simTime()).dbl() && (simTime()).dbl() <= 8*speedDuration)
        {
            speed = speed2;
            variability = variability2;
        }
        if (8*speedDuration <(simTime()).dbl() && (simTime()).dbl() <= 9*speedDuration)
        {
            speed = speed3;
            variability = variability3;
        }

    }


    double rad = PI * angle / 180;
    Coord direction(cos(rad), sin(rad));
    // lastSpeed = direction * speed;
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
            double vObj;
            vObj = speed;
            EV << logName() << "::" << getClassName() << " Minimum speed: " << vObj << endl;

            //Recalcular la velocidad mientras sea menor o mayor a la permitida
            do
            {
                double floor = vObj - vObj * variability;
                double ceiling = vObj + vObj * variability;
                double range = ceiling - floor;

                currentSpeed = floor + (range * rand()) / (RAND_MAX + 1.0);
                acceleration = (currentSpeed - previousSpeed) / elapsedTime;

            } while (currentSpeed < (vObj - vObj * variability) || currentSpeed > (vObj + vObj * variability));

            //Emitir se�al para la aceleraci�n del l�der
            emit(accelerationLeaderSignal, acceleration);

        }
        else
        { //Actualiza velocidad de acuerdo a la aceleración del platoon para el resto de nodos

            currentSpeed += acceleration * elapsedTime;
        }

    }

    lastSpeed = direction * currentSpeed;
    lastPosition += lastSpeed * elapsedTime;

    EV << " " << logName() << "::" << getClassName() << " Acceleration= " << acceleration << endl;
    EV << " " << logName() << "::" << getClassName() << " Speed= " << currentSpeed << endl;
    // do something if we reach the wall
    Coord dummy;
    handleIfOutside(REFLECT, dummy, dummy, angle);

    // accelerate
    //speed += acceleration * elapsedTime;
    if (currentSpeed <= 0)
    {
        currentSpeed = 0;
        stationary = true;
    }
}

/**
 * Detener el módulo
 */
void CustomLinearMobility::stop()
{
    stopModule = true;
}

/**
 * Obtener velocidad actual del módulo
 */
double CustomLinearMobility::getMySpeed()
{
    return currentSpeed;
}

/**
 * Obtener aceleración actual del módulo
 */
double CustomLinearMobility::getMyAcceleration()
{
    return acceleration;
}

// Obtener Activación de multi Speed
bool CustomLinearMobility::getMultiSpeed()
{
    return MultiSpeed;
}

// Obtener duración de velocidad
double CustomLinearMobility::getSpeedDuration()
{
    return speedDuration;
}

// Obtener Velocidad objetivo
double CustomLinearMobility::getTargetSpeed()
{
    return speed;
}

double CustomLinearMobility::getSpeed1()
{
    speed = par("speed");
    return speed;
}

double CustomLinearMobility::getSpeed2()
{
    return speed2;
}

double CustomLinearMobility::getSpeed3()
{
    return speed3;
}
/**
 * Modificar aceleración actual del módulo
 */
void CustomLinearMobility::setAcceleration(double newAcceleration)
{
    acceleration = newAcceleration;
}

