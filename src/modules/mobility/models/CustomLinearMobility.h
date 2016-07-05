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

#ifndef LINEAR_MOBILITY_H
#define LINEAR_MOBILITY_H

#include "INETDefs.h"

#include "CustomMovingMobilityBase.h"

/**
 * @brief Linear movement model. See NED file for more info.
 *
 * @ingroup mobility
 * @author Emin Ilker Cetinbas
 */
class INET_API CustomLinearMobility : public CustomMovingMobilityBase
{

    private:
        //Se�al para emitir la aceleraci�n del l�der
        simsignal_t accelerationLeaderSignal;

   protected:
        double speed;          ///< speed of the host
        double angle;          ///< angle of linear motion
        double acceleration;   ///< acceleration of linear motion
        // configuration
        double currentSpeed; //Velocidad actual del host
        double totalTime; //Tiempo objetivo para llegar a la meta
        double totalDistance; //Distancia total para llegar a la meta
        double variability; //Variabilidad en la velocidad objetivo
        bool leader; //Bandera para indicar si es lider o no
        bool stopModule;

    protected:
        virtual int numInitStages() const
        {
            return 3;
        }

        /** @brief Initializes mobility model parameters.*/
        virtual void initialize(int stage);

        /** @brief Move the host*/
        virtual void move();
        /** @brief Function to get a pointer to the host module*/
        cModule* findHost(void);
        const cModule* findHost(void) const;

    public:
        CustomLinearMobility();
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
        std::string logName(void) const;
};

#endif
