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

#ifndef CUSTOMAPPLAYER_H_
#define CUSTOMAPPLAYER_H_

#include "MiXiMDefs.h"
#include <MyTestAppLayer.h>
#include <NodeInfo.h>
#include <fstream>
#include <stdio.h>

class MIXIM_API CustomAppLayer : public MyTestAppLayer
{
    private:
        //Cantidad de paquetes enviados
        long numSent;
        //Cantidad de paquetes recibidos
        long numReceived;
        //ID consecutivo del paquete
        int packageID;
        //Cantidad de paquetes broadcast recibidos
        long numReceivedBroadcast;

        //Distancia total entre el inicio y la meta
        double totalDistance;

        //Bandera para determinar si hay o no comunicacion
        bool comEnabled;

        //Indicadores de llegada a la meta
        bool llegada;
        double finalSpeed;
        double finalAcceleration;

        //Datos del l�der
        double localLeaderAcceleration;
        double localLeaderSpeed;

        //Message to schedule next platoon update
        cMessage* timeToPlatoonInfo;

        std::vector<NodeInfo*> nodeInfoVector;

 /*       //Se�al para emitir la aceleraci�n aplicada*/
        simsignal_t accelerationPlatoonSignal;

        //Se�al para emitir la aceleraci�n aplicada con error humano
        simsignal_t accelerationErrorSignal;/*

        //Se�al para emitir la aceleraci�n aplicada sin error humano
        simsignal_t accelerationSinSignal;

        //Se�al para emitir la aceleraci�n filtrada por el umbral
        simsignal_t accelerationFilteredSignal;

        //Se�al para emitir la distancia del nodo actual al nodo frontal
        simsignal_t distanceToFwdSignal;

        //Se�al para emitir la distancia del nodo actual al nodo frontal
        simsignal_t distanceToFwdRTTSignal;

        //Señal para emitir tiempo de llegada del nodo a la meta
        simsignal_t arrivalTimeSignal;

        //Señal para emitir cuando se envía un paquete
        simsignal_t sentSignal;

        //Señal para emitir cuando se recibe un paquete
        simsignal_t receivedSignal;

        //Señal para emitir la posición x del módulo cuando se recibe un paquete*/
        simsignal_t positionXSignal;

        //Señal para emitir la posición con error GPS x del módulo cuando se recibe un paquete
        //simsignal_t positionXGPSErrorSignal;

        //Señal para emitir la velocidad del nodo*/
        simsignal_t velNodeSignal;/*

        //Señal para emitir la velocidad objetiva del nodo
        simsignal_t targetSpeedSignal;

        //Señal para emitir la posición y del módulo cuando se recibe un paquete*/
        simsignal_t positionYSignal;/*

        //Señal para emitir cuando se recibe un paquete broadcast
        simsignal_t receivedBroadcastSignal;

        //Señal para emitir cuando se recibe un paquete del l�der
        simsignal_t leaderInfoSignal;

        //Señal para emitir cuando se recibe un paquete DIRECTAMENTE del l�der
        simsignal_t leaderInfoDirectSignal;

        //Señal para emitir cuando se recibe un paquete del l�der por MULTISALTO
        simsignal_t leaderInfoMultihopSignal;

        //Señal para emitir cuando se USA un paquete del l�der por MULTISALTO
        simsignal_t leaderInfoMultihopUsedSignal;

        //Señal para emitir el calculo de la precision por nodo
        simsignal_t precisionSignal;

        //Señal para emitir el calculo de la exactitud por nodo
        simsignal_t accuracySignal;

        //Señal para emitir el error humano obtenido
        simsignal_t humanErrorSignal;
*/
        simsignal_t accelerationSinSignal;
        simsignal_t distanceToFwdSignal;


        //Aceleracion del ultimo platoon
        double lastAccelerationPlatoon;

        //Alpha values of CACC
        double alpha1;
        double alpha2;
        double alpha3;
        double alpha4;
        double alpha5;

        double C1;
        double omegan;
        double epsilon;

        //Alpha values of CACC with lag
        double alphaLag;

        //Human error in velocity response
        double mean_error;
        double std_error;
        double mean_vel_obj;

        //Human error in velocity response for multi-Speed performance
        //Speed 1
        double mean_error_S1;
        double std_error_S1;

        //Speed 2
        double mean_error_S2;
        double std_error_S2;

        //Speed 3
        double mean_error_S3;
        double std_error_S3;

        //MEAN acceleration for each node
        double MEANac_n1;
        double MEANac_n2;
        double MEANac_n3;
        double MEANac_n4;
        double MEANac_n5;
        double MEANac_n6;
        double MEANac_n7;
        double MEANac_n8;
        double MEANac_n9;
        double MEANac_n10;
        double MEANac_n11;
        double MEANac_n12;
        double MEANac_n13;
        double MEANac_n14;
        double MEANac_n15;
        double MEANac_n16;
        double MEANac_n17;
        double MEANac_n18;
        double MEANac_n19;
        double MEANac_n20;
        double MEANac_n21;
        double MEANac_n22;
        double MEANac_n23;
        double MEANac_n24;
        double MEANac_n25;
        double MEANac_n26;
        double MEANac_n27;
        double MEANac_n28;
        double MEANac_n29;


        //STD acceleration for each node
        double STDac_n1;
        double STDac_n2;
        double STDac_n3;
        double STDac_n4;
        double STDac_n5;
        double STDac_n6;
        double STDac_n7;
        double STDac_n8;
        double STDac_n9;
        double STDac_n10;
        double STDac_n11;
        double STDac_n12;
        double STDac_n13;
        double STDac_n14;
        double STDac_n15;
        double STDac_n16;
        double STDac_n17;
        double STDac_n18;
        double STDac_n19;
        double STDac_n20;
        double STDac_n21;
        double STDac_n22;
        double STDac_n23;
        double STDac_n24;
        double STDac_n25;
        double STDac_n26;
        double STDac_n27;
        double STDac_n28;
        double STDac_n29;

        //GPS Measure error
        bool GPSErrorEnabled;
        double position_error_a;
		double position_error_b;

		//RTT calculing distance method
	    bool RTTEnabled;


        //Values for calculating Spacing Error
        double length_vehicle_front;
        double desiredSpacing;

        //Position update interval
        double beaconInterval;

        //Platoon update interval
        double platoonInterval;

        //Beaconing
        bool beaconingEnabled;

        //Acceleration threshold
        double Thr_Ac;

        bool fitDistEnabled;

        std::vector<double> VectorDistLS;
        std::vector<double> VectorDistMS;
        std::vector<double> VectorDistHS;

    public:
        CustomAppLayer() :
                MyTestAppLayer(), burstSize(0), bSendReply(true)
        {

        }
        virtual ~CustomAppLayer();

        /** @brief Initialize module parameters*/
        virtual void initialize(int);

    protected:
        /** @brief Handle self messages such as timer... */
        virtual void handleSelfMsg(cMessage*);

        /** @brief Handle messages from lower layer */
        virtual void handleLowerMsg(cMessage*);

        /** @brief Permite obtener la posición x del módulo */
        virtual double getModuleXPosition();

        /** @brief Permite obtener la posición y del módulo */
        virtual double getModuleYPosition();

        /** @brief Permite obtener la posición x del módulo */
        virtual double getModuleXPositionGPSError();

        /** @brief Permite obtener la velocidad del módulo */
        virtual double getModuleSpeed();

        /** @brief Permite obtener la aceleración del módulo */
        virtual double getModuleAcceleration();

        /** @brief Permite obtener boolean MultiSpeed*/
        virtual bool getMS();

        /** @brief Permite obtener la Duración de cada velocidad (SpeedDuration)*/
        virtual double getSD();

        /** @brief Permite obtener la velocidad objetivo)*/
        virtual double getTS();

        //Obtener valor de la velocidad 1
        virtual double getS1();

        //Obtener valor de la velocidad 2
        virtual double getS2();

        //Obtener valor de la velocidad 3
        virtual double getS3();


        /** @brief Permite actualizar el tag del módulo donde se muestran los datos*/
        virtual void updateDisplay();

        /** @brief Permite obtener la zona en la que se encuentra un nodo, dadas sus posiciones x e y */
        virtual int getZonaNodo(double posx, double posy);

        /** @brief Permite determinar la distancia entre dos nodos dadas sus posiciones x e y y la zon en la cual est�n*/
        virtual double getDistanceBetweenNodes(double posx_1, double posy_1, int zona_1, double posx_2, double posy_2,
                int zona_2);

        /** @brief Permite determinar la distancia entre dos nodos dadas sus posiciones x**/
        virtual double getDistanceBetweenNodes2(double posx_1, double posx_2);

        /** @brief Permite obtener la distancia del nodo al punto de referencia (0,800)*/
        virtual double getAbsoluteDistance(double posx, double posy, int zona);

        /** @brief Permite modificar la aceleracion de un nodo */
        virtual void setAcceleration(double acceleration);

        //Función signo
        virtual int signo(double x);

        /** @brief Number of messages to send in a burst*/
        int burstSize;
        /** @brief If true, send a unicast BROADCAST_REPLY message to each
         * received BROADCAST message. */
        bool bSendReply;

        void readCSV(const std::string &s,std::vector<double> &elems);

        virtual double getRandValLowSpeed();
        virtual double getRandValMediumSpeed();
        virtual double getRandValHighSpeed();
};

#endif /* CUSTOMAPPLAYER_H_ */
