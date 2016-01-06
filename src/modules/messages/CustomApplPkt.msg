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
    LAddress::L3Type destAddr = LAddress::L3BROADCAST; // Direcci贸n de destino
    LAddress::L3Type srcAddr  = LAddress::L3BROADCAST; // Direcci贸n de la fuente
    double 									xposition; // Posici贸n x del m贸dulo
    double 									yposition; // Posici贸n y del m贸dulo
    double										speed; // Velocidad del m贸dulo
    int											   id; // ID consecutivo del paquete
    double 								 acceleration; // Aceleraci贸n del m贸dulo
    double						   leaderAcceleration; //Aceleraci梟 del l抎er
    double 								  leaderSpeed; //Velocidad del l抎er
    bool 							 beaconingEnabled; //Habilitaci梟 del beaconing --> true - habilitado; false - deshabilitado
}
