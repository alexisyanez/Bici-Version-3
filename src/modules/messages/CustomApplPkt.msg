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

//
// TODO generated message class
//

cplusplus {{
    #include "SimpleAddress.h"
}}

class LAddress::L3Type extends void;


packet CustomApplPkt {
    LAddress::L3Type destAddr = LAddress::L3BROADCAST; // Dirección de destino
    LAddress::L3Type srcAddr  = LAddress::L3BROADCAST; // Dirección de la fuente
    double 									xposition; // Posición x del módulo
    double 									yposition; // Posición y del módulo
    double 							     xpositionGPS; // Posición x del módulo con error de GPS
    double										speed; // Velocidad del módulo
    int											   id; // ID consecutivo del paquete
    double 								 acceleration; // Aceleración del módulo
    double						   leaderAcceleration; // Aceleraci�n del l�der
    double 								  leaderSpeed; // Velocidad del l�der
    bool 							 beaconingEnabled; // Habilitaci�n del beaconing --> true - habilitado; false - deshabilitado
	double										   TS; // Timestamp del paquete
}
