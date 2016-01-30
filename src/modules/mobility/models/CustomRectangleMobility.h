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


#ifndef CUSTOM_RECTANGLE_MOBILITY_H
#define CUSTOM_RECTANGLE_MOBILITY_H

#include "INETDefs.h"

#include "CustomMovingMobilityBase.h"


/**
 * @brief Rectangle movement model. See NED file for more info.
 *
 * @ingroup mobility
 * @author Andras Varga
 */
class INET_API CustomRectangleMobility : public CustomMovingMobilityBase
{
  private:
        //Se–al para emitir la aceleraci—n del l’der
        simsignal_t accelerationLeaderSignal;

  protected:
    // configuration
    double currentSpeed; //Velocidad actual del host
    double totalTime; //Tiempo objetivo para llegar a la meta
    double totalDistance; //Distancia total para llegar a la meta
    double acceleration; //Aceleracion del host
    double variability; //Variabilidad en la velocidad objetivo
    bool leader; //Bandera para indicar si es lider o no


    // state
    double d;  ///< distance from (x1,y1), measured clockwise on the perimeter
    double corner1, corner2, corner3, corner4;
    bool stopModule;


  protected:
    /** @brief Initializes mobility model parameters.
     *
     * If the host is not stationary it calculates a random position on the rectangle.
     */
    virtual void initialize(int stage);

    /** @brief Initializes the position according to the mobility model. */
    virtual void initializePosition();

    /** @brief Move the host */
    virtual void move();

    /** @brief Function to get a pointer to the host module*/
       cModule* findHost(void);
       const cModule* findHost(void) const;

  public:
    CustomRectangleMobility();
    //Parar el modulo
    virtual void stop();
    //Obtener velocidad del modulo
    virtual double getMySpeed();
    //Obtener aceleracion del modulo
    virtual double getMyAcceleration();
    //Modificar aceleracion del modulo
    virtual void setAcceleration(double newAcceleration);

    /**
        * @brief Function to get the logging name of the host
        *
        * The logging name is the ned module name of the host (unless the
        * host ned variable loggingName is specified). It can be used for
        * logging messages to simplify debugging in TKEnv.
        */
     std::string logName(void) const ;

};

#endif
