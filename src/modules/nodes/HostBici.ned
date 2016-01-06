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

package src.modules.nodes;

import src.modules.mobility.models.CustomRectangleMobility;
import src.modules.mobility.models.CustomLinearMobility;
import src.modules.nodes.MyWirelessNode;


module HostBici extends MyWirelessNode
{
    parameters:

        mobilityType = default("CustomLinearMobility");


        //Parametros de la bateria
        batteryStats.detail = default(false);
        batteryStats.timeSeries = default(false);

        battery.nominal = default(1000 mAh);
        battery.capacity = default(battery.nominal);
        battery.voltage = default(3 V);
        battery.resolution = default(60 s);
        battery.publishDelta = default(1);
        battery.publishTime = default(battery.resolution);
        battery.numDevices = default(1);


        //Señal para indicar el envío de un paquete
        @signal[sent](type="int");
        @statistic[sentPackages](title="sent package"; source="sent"; record=vector,stats; interpolationmode=none);

        //Señal para indicar la recepción de un paquete
        @signal[received](type="int");
        @statistic[receivedPackages](title="received package"; source="received"; record=vector,stats; interpolationmode=none);

        //Señal para indicar la posición x cuando se recibe un paquete
        @signal[xposition](type="double");
        @statistic[xPosition](title="position x"; source="xposition"; record=vector,stats; interpolationmode=none);
		
		//Señal para indicar la velocidad 
        @signal[vel](type="double");
        @statistic[velNodo](title="velocidad nodo"; source="vel"; record=vector,stats; interpolationmode=none);
        
        //Señal para indicar la posición y cuando se recibe un paquete
        @signal[yposition](type="double");
        @statistic[yPosition](title="position y"; source="yposition"; record=vector,stats; interpolationmode=none);

        //Señal para indicar la recepción de un paquete broadcast
        @signal[received_broadcast](type="int");
        @statistic[received_broadcast](title="received broadcast"; source="received_broadcast"; record=vector,stats; interpolationmode=none);

        //Señal para indicar el tiempo de llegada del nodo a la meta
        @signal[arrival_time](type="double");
        @statistic[arrival_time](title="arrival time"; source="arrival_time"; record=last);

        //Se�al para indicar la aceleraci�n que se aplica al nodo
        @signal[accelerationPlatoon](type="double");
        @statistic[accelerationPlatoon](title="acceleration platoon"; source="accelerationPlatoon"; record=vector,stats; interpolationmode=none);
        
        //Señal para indicar la aceleracion con error y lag
        @signal[accelerationError](type="double");
        @statistic[accelerationError](title="acceleration platoon con error"; source="accelerationError"; record=vector,stats; interpolationmode=none);
		
		//Señal para indicar la aceleracion sin error con lag
		@signal[accelerationSin](type="double");
        @statistic[accelerationSin](title="acceleration platoon sin error"; source="accelerationSin"; record=vector,stats; interpolationmode=none);
        
        //Se�al para indicar la distancia al nodo del frente
        @signal[distanceToFwd](type="double");
        @statistic[distanceToFwd](title="distance to fwd"; source="distanceToFwd"; record=vector,stats; interpolationmode=none);

        //Se�al para indicar la aceleraci�n del l�der
        @signal[accelerationLeader](type="double");
        @statistic[accelerationLeader](title="leader acceleration"; source="accelerationLeader"; record=vector,stats; interpolationmode=none);

		//Señal para indicar la recepcion de un paquete con informacion del lider
        @signal[leaderInfo](type="int");
        @statistic[leaderInfo](title="leader info"; source="leaderInfo"; record=vector,stats; interpolationmode=none);

		//Señal para indicar la recepcion DIRECTA de un paquete con informacion del lider
        @signal[leaderInfoDirect](type="int");
        @statistic[leaderInfoDirect](title="leader info direct"; source="leaderInfoDirect"; record=vector,stats; interpolationmode=none);

        //Señal para indicar la recepcion POR MULTISALTO de un paquete con informacion del lider
        @signal[leaderInfoMultihop](type="int");
        @statistic[leaderInfoMultihop](title="leader info multihop"; source="leaderInfoMultihop"; record=vector,stats; interpolationmode=none);

        //Señal para indicar el USO de un paquete con informacion del lider recibido por MULTISALTO
        @signal[leaderInfoMultihopUsed](type="int");
        @statistic[leaderInfoMultihopUsed](title="leader info multihop used"; source="leaderInfoMultihopUsed"; record=vector,stats; interpolationmode=none);
}
