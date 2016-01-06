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


package src.modules.mobility.models;

import src.modules.mobility.models.CustomMovingMobilityBase;

//
// Moves the node around a rectangle.
//
// @see ~ChannelControl
// @author Andras Varga
//
simple CustomRectangleMobility extends CustomMovingMobilityBase
{
    parameters:
        double totalTime @unit(s); //Tiempo total para llegar a la meta
        double totalDistance @unit(m);//Distancia total para llegar a la meta
        
        double startPosition; // in range [0.0,4.0): topleft=0, topright=1, bottomright=2, bottomleft=3
        double acceleration = default(0);
        bool leader;
        double variability;
        
        
        @class(CustomRectangleMobility);
        

}
