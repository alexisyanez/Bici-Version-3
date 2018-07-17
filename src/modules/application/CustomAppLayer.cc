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

#include "CustomAppLayer.h"

#include <MobilityAccess.h>

#include <CustomMobilityAccess.h>

#include "CustomApplPkt_m.h"

#include <Coord.h>

using namespace std;
using std::endl;

Define_Module(CustomAppLayer);

void CustomAppLayer::initialize(int stage)
{
    //Registrar señales
    //receivedSignal = registerSignal("received");
    positionXSignal = registerSignal("xposition");
    //positionXGPSErrorSignal = registerSignal("xpositionGPSerror");
    positionYSignal = registerSignal("yposition");
    velNodeSignal = registerSignal("vel");/*
    sentSignal = registerSignal("sent");
    receivedBroadcastSignal = registerSignal("received_broadcast");
    arrivalTimeSignal = registerSignal("arrival_time");*/
    accelerationPlatoonSignal = registerSignal("accelerationPlatoon");
    accelerationErrorSignal = registerSignal("accelerationError");/*
    accelerationSinSignal = registerSignal("accelerationSin");*/
    accelerationFilteredSignal = registerSignal("accelerationFiltered");/*
    distanceToFwdSignal = registerSignal("distanceToFwd");
    distanceToFwdRTTSignal = registerSignal("distanceToFwdRTT");
    leaderInfoSignal = registerSignal("leaderInfo");
    leaderInfoDirectSignal = registerSignal("leaderInfoDirect");
    leaderInfoMultihopSignal = registerSignal("leaderInfoMultihop");
    leaderInfoMultihopUsedSignal = registerSignal("leaderInfoMultihopUsed");
    targetSpeedSignal = registerSignal("targetSpeed");*/
    precisionSignal = registerSignal("precision");
    accuracySignal = registerSignal("accuracy");
    humanErrorSignal = registerSignal("humanError");

    accelerationSinSignal = registerSignal("accelerationSin");
    distanceToFwdSignal = registerSignal("distanceToFwd");


    // Inicializar variables
    packageID = 0;
    numSent = 0;
    numReceived = 0;
    numReceivedBroadcast = 0;
    totalDistance = 0;
    lastAccelerationPlatoon = 0;
    comEnabled = true;
    llegada = false;
    finalSpeed = 0;
    finalAcceleration = 0;
    localLeaderAcceleration = 0;
    localLeaderSpeed = 0;

    WATCH(numSent);
    WATCH(numReceived);
    WATCH(packageID);
    WATCH(numReceivedBroadcast);

    /*alpha1 = par("alpha1");
    alpha2 = par("alpha2");
    alpha3 = par("alpha3");
    alpha4 = par("alpha4");
    alpha5 = par("alpha5");*/
    C1 = par("C1");
    epsilon = par("epsilon");
    omegan = par("omega_n");

    alphaLag = par("alphaLag");

    alpha1 = 1-C1;
    alpha2 = C1;
    alpha3 = (2*epsilon-C1*(epsilon+sqrt(pow(epsilon,2)-1)))*omegan;
    alpha4 = (epsilon+sqrt(pow(epsilon,2)-1))*omegan*C1;
    alpha5 = pow(omegan,2);


    // Error humano asociado a la velocidad
    mean_error = par("mean_error");
    std_error = par("std_error");
    mean_vel_obj = par("mean_vel_obj");

    // Error humano asociado a la velocidad para performance de multiples velocidades
    // Velocidad  1
    mean_error_S1 = par("mean_error_S1");
    std_error_S1 = par("std_error_S1");

    // Velocidad  2
    mean_error_S2 = par("mean_error_S2");
    std_error_S2 = par("std_error_S2");

    // Velocidad  3
    mean_error_S3 = par("mean_error_S3");
    std_error_S3 = par("std_error_S3");

    // Promedio de Aceleración para cada nodo con la velocidad respectiva

    MEANac_n1 = par("MEANac_n1");
    MEANac_n2 = par("MEANac_n2");
    MEANac_n3 = par("MEANac_n3");
    MEANac_n4 = par("MEANac_n4");
    MEANac_n5 = par("MEANac_n5");
    MEANac_n6 = par("MEANac_n6");
    MEANac_n7 = par("MEANac_n7");
    MEANac_n8 = par("MEANac_n8");
    MEANac_n9 = par("MEANac_n9");
    MEANac_n10 = par("MEANac_n10");
    MEANac_n11 = par("MEANac_n11");
    MEANac_n12 = par("MEANac_n12");
    MEANac_n13 = par("MEANac_n13");
    MEANac_n14 = par("MEANac_n14");
    MEANac_n15 = par("MEANac_n15");
    MEANac_n16 = par("MEANac_n16");
    MEANac_n17 = par("MEANac_n17");
    MEANac_n18 = par("MEANac_n18");
    MEANac_n19 = par("MEANac_n19");
    MEANac_n20 = par("MEANac_n20");
    MEANac_n21 = par("MEANac_n21");
    MEANac_n22 = par("MEANac_n22");
    MEANac_n23 = par("MEANac_n23");
    MEANac_n24 = par("MEANac_n24");
    MEANac_n25 = par("MEANac_n25");
    MEANac_n26 = par("MEANac_n26");
    MEANac_n27 = par("MEANac_n27");
    MEANac_n28 = par("MEANac_n28");
    MEANac_n29 = par("MEANac_n29");

    // Desviación estandar para cada nodo con la velocidad respectiva

    STDac_n1 = par("STDac_n1");
    STDac_n2 = par("STDac_n2");
    STDac_n3 = par("STDac_n3");
    STDac_n4 = par("STDac_n4");
    STDac_n5 = par("STDac_n5");
    STDac_n6 = par("STDac_n6");
    STDac_n7 = par("STDac_n7");
    STDac_n8 = par("STDac_n8");
    STDac_n9 = par("STDac_n9");
    STDac_n10 = par("STDac_n10");
    STDac_n11 = par("STDac_n11");
    STDac_n12 = par("STDac_n12");
    STDac_n13 = par("STDac_n13");
    STDac_n14 = par("STDac_n14");
    STDac_n15 = par("STDac_n15");
    STDac_n16 = par("STDac_n16");
    STDac_n17 = par("STDac_n17");
    STDac_n18 = par("STDac_n18");
    STDac_n19 = par("STDac_n19");
    STDac_n20 = par("STDac_n20");
    STDac_n11 = par("STDac_n21");
    STDac_n22 = par("STDac_n22");
    STDac_n23 = par("STDac_n23");
    STDac_n24 = par("STDac_n24");
    STDac_n25 = par("STDac_n25");
    STDac_n26 = par("STDac_n26");
    STDac_n27 = par("STDac_n27");
    STDac_n28 = par("STDac_n28");
    STDac_n29 = par("STDac_n29");

    // Error en la posición debido al GPS
    GPSErrorEnabled = par("GPS_error");
    position_error_a = par("position_error_a"); // Corresponde al Parametro Sigma de la distribución de raylegh (setear en 5)
    position_error_b = par("position_error_b"); // Corresponde a que tan desviados estan los datos (setear en 1.5)

    // Activar RTT para calcular distancia
    RTTEnabled = par("RTT_on");

    length_vehicle_front = par("lenghtVehicle");
    desiredSpacing = par("spacing");
    beaconInterval = par("beaconInterval");
    platoonInterval = par("platoonInterval");
    beaconingEnabled = par("beaconing");

    // Umbral de Aceleración
    Thr_Ac = par("Thr_Ac");

    // Para aplicar Ajuste de distribución
    fitDistEnabled = par("fitDist");
    if(fitDistEnabled){
        EV <<"Entro al if stage 0 distvector values: "<< endl;
    //readCSV("DistVectorLowSpeed.csv",VectorDistLS);
    //readCSV("DistVectorMediumSpeed.csv",VectorDistMS);
    readCSV("DistVectorLowSpeed.csv",VectorDistHS);

//    for (int i = 0; i < VectorDistLS.size(); i++) {
//        EV <<"distvector values: "<< VectorDistLS.at(i) << endl;
//    }
//    for (int i = 0; i < VectorDistMS.size(); i++) {
//        EV <<"distvector values: "<< VectorDistMS.at(i) <<endl;
//    }
//    for (int i = 0; i < VectorDistHS.size(); i++) {
//        EV <<"distvector values: "<<VectorDistHS.at(i) <<endl;
//    }
}
//    for (int i = 0; i < VectorDistLS.size(); i++) {
//        EV <<"distvector values: "<< VectorDistLS.at(i) << endl;
//
//    for (int i = 0; i < VectorDistMS.size(); i++) {
//        EV <<"distvector values: "<< VectorDistMS.at(i) <<endl;
//    }
//    for (int i = 0; i < VectorDistHS.size(); i++) {
//        EV <<"distvector values: "<<VectorDistHS.at(i) <<endl;
//    }

    MyTestAppLayer::initialize(stage);
    if (stage == 0)
    {
//        if(fitDistEnabled){
//        readCSV("DistVectorLowSpeed.csv",VectorDistLS);
//        readCSV("DistVectorMediumSpeed.csv",VectorDistMS);
//        readCSV("DistVectorHighSpeed.csv",VectorDistHS);
//
//        for (int i = 0; i < VectorDistLS.size(); i++) {
//            EV <<"distvector values: "<< VectorDistLS.at(i) << endl;
//        }
//        for (int i = 0; i < VectorDistMS.size(); i++) {
//            EV <<"distvector values: "<< VectorDistMS.at(i) <<endl;
//        }
//        for (int i = 0; i < VectorDistHS.size(); i++) {
//            EV <<"distvector values: "<<VectorDistHS.at(i) <<endl;
//        }
//    }
        if (hasPar("burstSize"))
            burstSize = par("burstSize");
        else
            burstSize = 3;
        if (hasPar("burstReply"))
            bSendReply = par("burstReply");
        else
            bSendReply = true;
    }
}

/**
 * Mensajes que se envia el nodo a si mismo
 */
void CustomAppLayer::handleSelfMsg(cMessage *msg)
{
    if (comEnabled == true)
    {

        switch (msg->getKind())
        {
             //El mensaje POSITION_TIMER indica que es tiempo de enviar sus datos en broadcast
            case POSITION_TIMER:
            {
                //Aumentar el ID actual para asignar al paquete que se va a enviar
                packageID++;

                //Obtener datos del nodo para añadir al paquete
                double xposition = getModuleXPosition();
                double yposition = getModuleYPosition();
                double xpositionGPSerror = getModuleXPositionGPSError();
                double speed = getModuleSpeed();
                double acceleration = getModuleAcceleration();

//                totalDistance = par("totalDistance");
//
//                //Detener a todos los nodos al estar en x_final y en el 70% del y_final
//                if (xposition >= totalDistance)
//                {
//                    if (!llegada)
//                    {
//                        finalSpeed = speed;
//                        finalAcceleration = acceleration;
//                        CustomMobilityAccess().get(findHost())->stop();
//                        cout << myApplAddr() << " finish at time " << simTime() << endl;
//                        //Emitir señal indicando tiempo de llegada
//                        //emit(arrivalTimeSignal, simTime());
//                        //comEnabled = false;
//                        cancelEvent(timeToPlatoonInfo);
//                        llegada = true;
//                    }

                    //Enviar paquete con la posicion y velocidad al resto de nodos
                   // sendNodeInfo(packageID, xposition, yposition, xpositionGPSerror, speed, acceleration, LAddress::L3BROADCAST,
                    //        localLeaderAcceleration, localLeaderSpeed, beaconingEnabled);
                    //msg->setTimestamp(simTime()); // enviar Timestamp


//                else
//                {

                    //Enviar paquete con la posicion y velocidad al resto de nodos
                    sendNodeInfo(packageID, xposition, yposition, xpositionGPSerror, speed, acceleration, LAddress::L3BROADCAST,
                            localLeaderAcceleration, localLeaderSpeed, beaconingEnabled);
                    //msg->setTimestamp(simTime()); // enviar Timestamp
               // }

                //Actualizar GUI con numero de paquetes enviados
                numSent++;
                if (ev.isGUI())
                    updateDisplay();

                //Se emite una senal cada vez que se envia un paquete con su ID

                //emit(sentSignal, packageID);

                //Se emiten dos senales con la posicion x e y del nodo al enviar un paquete
                emit(positionXSignal, xposition);
                emit(positionYSignal, yposition);
                //emit(positionXGPSErrorSignal, xpositionGPSerror);

                //Volver a iniciar el timer para enviar el siguiente paquete
                positionTimer = new cMessage("position-timer", POSITION_TIMER);
                scheduleAt(simTime() + beaconInterval, positionTimer);

                //EV << "Node[" << myApplAddr() << "]: Sending Position Update" << endl;
                //EV << "My X Position=" << xposition << "; My X GPS position = " << xpositionGPSerror << endl;

                break;
            }
            case PLATOON_TIMER:
            {
                // 1. PREPARACION

                //Lista sin duplicados

                // setear el tiempo de simulación
             //  if(myApplAddr()!=0){
                std::vector<NodeInfo*> noDuplicateInfo;
                double distanceBetweenActualAndFront;
                double distanceBetweenActualAndFrontGPS;
                double distanceBetweenActualAndFrontRTT;



                //Se agrega la informacion a la lista sin duplicados
                for (int i = 0; i < int(nodeInfoVector.size()); i++)
                {
                    NodeInfo* nodeInfo = nodeInfoVector.back();

                    bool existeInfo = false;

                    //Se recorre  la lista sin duplicados
                    for (std::vector<NodeInfo*>::iterator it = noDuplicateInfo.begin(); it != noDuplicateInfo.end();
                            ++it)
                    {
                        NodeInfo* n = *it;

                        //Si existe algun paquete de la misma fuente no se agrega
                        if (n->getSrcAddress() == nodeInfo->getSrcAddress())
                        {
                            existeInfo = true;
                            break;
                        }
                    }

                    //Si nunca se encontro un paquete de la misma fuente se agrega a la lista
                    if (existeInfo == false)
                    {
                        noDuplicateInfo.push_back(nodeInfo);

                    }

                    //Se elimina el elemento que se acabo de usar
                    nodeInfoVector.pop_back();
                }

                // 2. EMPIEZA EL PLATOON

                //Obtener la posicion del nodo actual
                double posx = getModuleXPosition();
                double posxGPS = getModuleXPositionGPSError();
                int NearestNodeIndex;

                //Calcular distancias desde los nodos hacia el actual para determinar el mas cercano
                NodeInfo*nearestNode = NULL;
                NodeInfo*leaderNode = NULL;

                EV << "Node[" << myApplAddr() << "]: Running Platoon Update" << endl;



                if (noDuplicateInfo.size() > 0)
                {

                    //a. Determinar nodo mas cercano y nodo lider
                    for (std::vector<NodeInfo*>::iterator it = noDuplicateInfo.begin(); it != noDuplicateInfo.end();++it)
                    {
                        NodeInfo* nodeInfo = *it;

                        //Obtener la distancia del nodo del que se recibio el paquete al nodo actual
                        int addr_node = nodeInfo->getSrcAddress();
                        double posx_node = nodeInfo->getXPosition();
                        double distanceToActual = getDistanceBetweenNodes2(posx, posx_node);

                        if (addr_node == 0)
                          {
                              leaderNode = *it;
                              nearestNode = *it;
                              EV << "Lider: " << addr_node << endl;
                          }
                        //SC:Remueve el else para que se asigne el nearest nodo cuando es el nodo 1
                        if (addr_node == myApplAddr()-1 )
                          {
                              nearestNode = *it;
                              EV << "Nodo Mas Cercano: " << addr_node << endl;
                              NearestNodeIndex=addr_node;
                          }

                        /*if (myApplAddr()==1)
                        {
                            NearestNodeIndex=0;
                        }

*///                        //Si actualmente no hay un nodo mas cercano y la distancia del nodo al actual es mayor a cero,
//                        //este es el nodo mas cercano por el momento
//                        if (distanceToActual > 0 && nearestNode == NULL)
//                        {
//                            nearestNode = *it;
//                        }
//
//                        //Si actualmente hay un nodo mas cercano, se compara con el nodo del cual se recibio un paquete
//                        if (nearestNode != NULL)
//                        {
//                            //Comparar con el nodo mas cercano hasta el momento
//                            //int addr_node_nearest = nearestNode->getSrcAddress();
//                            double posx_node_nearest = nearestNode->getXPosition();
//                            //double speed_node_nearest = nearestNode->getSpeed();
//                            double distanceToActual_nearest = getDistanceBetweenNodes2(posx, posx_node_nearest); // Se asume que el grupo mantiene un orden fijado con anetrioridad por lo que no se aplica el erro del GPS para detectar el nodo de enfrete
//
//                            //Se cambia el nodo mas cercano si la distancia es menor a la del mas cercano actual
//                            if (distanceToActual > 0 && distanceToActual < distanceToActual_nearest)
//                            {
//                                nearestNode = *it;
//                            }
//                        }
                    }

                    //b. Obtener informacion del nodo mas cercano que se encuentre al frente
                    double rel_speed_front;

                    double spacing_error;
                    double spacing_error_GPS;
                    double spacing_error_RTT;
                    double nodeFrontAcceleration;
                    double Speed_Ligth = 299792458.0;
                    //double RTT;

                    if (nearestNode != NULL)
                    {
                        //Velocidad relativa al vehiculo del frente
                        rel_speed_front = getModuleSpeed() - nearestNode->getSpeed();
                        ostringstream str1;
                        str1 << NearestNodeIndex;
                        //string nearestPath = "Main_Network.node[";//+ str1.str() +"]";
                        string nearestPath = "Main_Network.node["+ str1.str() +"]";
                        cModule *module = simulation.getModuleByPath(nearestPath.c_str());
                        double newpos;
                        if (module){
                            newpos = (MobilityAccess().get(module)->getCurrentPosition()).x;
                        }

                        //Obtener spacing error
                        //distanceBetweenActualAndFront = getDistanceBetweenNodes2(posx, nearestNode->getXPosition());
                        distanceBetweenActualAndFront = getDistanceBetweenNodes2(posx, newpos);
                        spacing_error = -distanceBetweenActualAndFront + length_vehicle_front + desiredSpacing;
                        emit(distanceToFwdSignal, spacing_error); // Spacing Real
                        //Obtener spacing error con GPS
                        distanceBetweenActualAndFrontGPS = getDistanceBetweenNodes2(posxGPS, nearestNode->getXPositionGPSerror());
                        spacing_error_GPS = -distanceBetweenActualAndFrontGPS + length_vehicle_front + desiredSpacing;

                        // obtener spacing error con RTT

                        //RTT = 2 * ( ST - nearestNode->getTS());

                        //EV << "GetBackRTT=" << nearestNode->getRTTBack() << endl;
                        distanceBetweenActualAndFrontRTT =  (Speed_Ligth * nearestNode->getRTTBack());
                        spacing_error_RTT = -distanceBetweenActualAndFrontRTT + length_vehicle_front + desiredSpacing;



                        //emit(distanceToFwdRTTSignal,distanceBetweenActualAndFrontRTT );

                        nodeFrontAcceleration = nearestNode->getAcceleration();

                    }
                    else
                    {
                        rel_speed_front = 0;
                        spacing_error = 0;
                        spacing_error_GPS = 0;
                        spacing_error_RTT = 0;
                        nodeFrontAcceleration = 0;
                    }

                    //c. Obtener la informacion del lider
                    double leaderAcceleration;
                    double leaderSpeed;

                    if (leaderNode == NULL)
                    {
                        //Se usan los datos del mecanismo beaconing
                        if (nearestNode != NULL && beaconingEnabled == true)
                        {
                            //emit(leaderInfoMultihopUsedSignal,packageID);

                            leaderAcceleration = nearestNode->getLeaderAcceleration();
                            leaderSpeed = nearestNode->getLeaderSpeed();
                            localLeaderAcceleration = nearestNode->getLeaderAcceleration();
                            localLeaderSpeed = nearestNode->getLeaderSpeed();
                            EV << "Aceleración del lider atraves de beaconing" << leaderAcceleration << endl;
                        }
                        else
                        {
                            //SC:Poner en 0 datos del lider y del i-1 pues no recibio de nadie
                            rel_speed_front = 0;
                            spacing_error = 0;
                            spacing_error_GPS = 0;
                            spacing_error_RTT = 0;
                            nodeFrontAcceleration = 0;
                            leaderAcceleration = 0;
                            leaderSpeed = 0;
                            localLeaderAcceleration = 0;
                            localLeaderSpeed = 0;
                        }

                    }
                    else
                    {
                        leaderAcceleration = leaderNode->getAcceleration();
                        leaderSpeed = leaderNode->getSpeed();
                        EV << "Aceleración del lider atraves de beaconing" << leaderAcceleration << endl;
                    }

                    double TargetS = getTS();

                    //Print data for calculation
                   /* EV << "Node[" << myApplAddr() << "]: Platoon parameters" << endl;
                    EV << "distance to Vehicle in Front=" << distanceBetweenActualAndFront << endl;
                    EV << "distance to vehicle in Front RTT =" << distanceBetweenActualAndFrontRTT << endl;
                    EV << "Vehicle in Front Acceleration=" << nodeFrontAcceleration << endl;
                    EV << "Leader Acceleration=" << leaderAcceleration << endl;
                    EV << "Relative speed vehicule in front=" << rel_speed_front << endl;
                    EV << "Leader speed=" << leaderSpeed << endl;
                    EV << "My speed=" << getModuleSpeed() << endl;
                    EV << "Target speed=" << TargetS << endl;
                    EV << "Spacing Error=" << spacing_error << endl;*/

                    // Enviar valores de la velocidad
                    emit(velNodeSignal,getModuleSpeed());
                    double A_des;

                    if (GPSErrorEnabled == true) // se activa solo si el usuario quiere incluir el error del GPS
                    {
                         //d. Calcular A_des (Acceleration desired)
                        A_des = alpha1 * nodeFrontAcceleration + alpha2 * leaderAcceleration
                                - alpha3 * rel_speed_front - alpha4 * (getModuleSpeed() - leaderSpeed)
                                - alpha5 * spacing_error_GPS;
                    }
                    else if (RTTEnabled == true)
                    {
                        A_des = alpha1 * nodeFrontAcceleration + alpha2 * leaderAcceleration
                                - alpha3 * rel_speed_front - alpha4 * (getModuleSpeed() - leaderSpeed)
                                - alpha5 * spacing_error_RTT;
                    }
                    else
                    {
                        A_des = alpha1 * nodeFrontAcceleration + alpha2 * leaderAcceleration
                                - alpha3 * rel_speed_front - alpha4 * (getModuleSpeed() - leaderSpeed)
                                - alpha5 * spacing_error;
                    }

                    //if(spacing_error>desiredSpacing){A_des=0;} // Si un nodo sobrepasa a su antecesor no aplica ninguna aceleración

                    emit(accelerationPlatoonSignal, A_des);


                    // Calcular el error en base a una normal con parámetros de resultados en simulación
                    //double vel_error; = normal(mean_error,std_error);
                    double human_error;// = (mean_vel_obj + vel_error)/(mean_vel_obj);

                    // Umbral para aplicar a la aceleración
                    double Umbral_Ac;
                    double Mean_Ac;

                    if (getMS())
                    {
                        //EV << "TargetSpeed= " << getTS() << " S1= " << getS1() << " S2= " << getS2() << " S3= " << getS3() << endl;

                        // Setear valores en base a la desviacion estandar de cada nodo según su velocidad.
                       if (TargetS == getS1())
                        {
                            human_error = normal(mean_error_S1,std_error_S1);

                            if(fitDistEnabled){
                                if(mean_error_S1==-0.016428571){
                                    human_error = getRandValLowSpeed();
                              //(getS1() + vel_error)/(getS1());
                                }
                                else if(mean_error_S1==-0.043688525 ){
                                    human_error = getRandValMediumSpeed();
                                }
                                else if(mean_error_S1==0.009107143){
                                    human_error = getRandValHighSpeed();
                                }
                            }
                            if(myApplAddr()==1)
                            {
                               Umbral_Ac = STDac_n1*Thr_Ac/2;
                               Mean_Ac = MEANac_n1;
                            }
                            else if(myApplAddr()==2)
                            {
                               Umbral_Ac = STDac_n2*Thr_Ac/2;
                               Mean_Ac = MEANac_n2;
                            }
                            else if(myApplAddr()==3)
                            {
                               Umbral_Ac = STDac_n3*Thr_Ac/2;
                               Mean_Ac = MEANac_n3;
                            }
                            else if(myApplAddr()==4)
                            {
                               Umbral_Ac = STDac_n4*Thr_Ac/2;
                               Mean_Ac = MEANac_n4;
                            }
                            else if(myApplAddr()==5)
                            {
                               Umbral_Ac = STDac_n5*Thr_Ac/2;
                               Mean_Ac = MEANac_n5;
                            }
                            else if(myApplAddr()==6)
                            {
                               Umbral_Ac = STDac_n6*Thr_Ac/2;
                               Mean_Ac = MEANac_n6;
                            }
                            else if(myApplAddr()==7)
                            {
                               Umbral_Ac = STDac_n7*Thr_Ac/2;
                               Mean_Ac = MEANac_n7;
                            }
                            else if(myApplAddr()==8)
                            {
                               Umbral_Ac = STDac_n8*Thr_Ac/2;
                               Mean_Ac = MEANac_n8;
                            }
                            else if(myApplAddr()==9)
                            {
                               Umbral_Ac = STDac_n9*Thr_Ac/2;
                               Mean_Ac = MEANac_n9;
                            }
                            else if(myApplAddr()==10)
                            {
                               Umbral_Ac = STDac_n10*Thr_Ac/2;
                               Mean_Ac = MEANac_n10;
                            }
                            else if(myApplAddr()==11)
                            {
                               Umbral_Ac = STDac_n11*Thr_Ac/2;
                               Mean_Ac = MEANac_n11;
                            }
                            else if(myApplAddr()==12)
                            {
                               Umbral_Ac = STDac_n12*Thr_Ac/2;
                               Mean_Ac = MEANac_n12;
                            }
                            else if(myApplAddr()==13)
                            {
                               Umbral_Ac = STDac_n13*Thr_Ac/2;
                               Mean_Ac = MEANac_n13;
                            }
                            else if(myApplAddr()==14)
                            {
                               Umbral_Ac = STDac_n14*Thr_Ac/2;
                               Mean_Ac = MEANac_n14;
                            }
                            else if(myApplAddr()==15)
                            {
                               Umbral_Ac = STDac_n15*Thr_Ac/2;
                               Mean_Ac = MEANac_n15;
                            }
                            else if(myApplAddr()==16)
                            {
                               Umbral_Ac = STDac_n16*Thr_Ac/2;
                               Mean_Ac = MEANac_n16;
                            }
                            else if(myApplAddr()==17)
                            {
                               Umbral_Ac = STDac_n17*Thr_Ac/2;
                               Mean_Ac = MEANac_n17;
                            }
                            else if(myApplAddr()==18)
                            {
                               Umbral_Ac = STDac_n18*Thr_Ac/2;
                               Mean_Ac = MEANac_n18;
                            }
                            else if(myApplAddr()==19)
                            {
                               Umbral_Ac = STDac_n19*Thr_Ac/2;
                               Mean_Ac = MEANac_n19;
                            }
                            else if(myApplAddr()==20)
                            {
                               Umbral_Ac = STDac_n20*Thr_Ac/2;
                               Mean_Ac = MEANac_n20;
                            }
                            else if(myApplAddr()==21)
                            {
                               Umbral_Ac = STDac_n21*Thr_Ac/2;
                               Mean_Ac = MEANac_n21;
                            }
                            else if(myApplAddr()==22)
                            {
                               Umbral_Ac = STDac_n22*Thr_Ac/2;
                               Mean_Ac = MEANac_n22;
                            }
                            else if(myApplAddr()==23)
                            {
                               Umbral_Ac = STDac_n23*Thr_Ac/2;
                               Mean_Ac = MEANac_n23;
                            }
                            else if(myApplAddr()==24)
                            {
                               Umbral_Ac = STDac_n24*Thr_Ac/2;
                               Mean_Ac = MEANac_n24;
                            }
                            else if(myApplAddr()==25)
                            {
                               Umbral_Ac = STDac_n25*Thr_Ac/2;
                               Mean_Ac = MEANac_n25;
                            }
                            else if(myApplAddr()==26)
                            {
                               Umbral_Ac = STDac_n26*Thr_Ac/2;
                               Mean_Ac = MEANac_n26;
                            }
                            else if(myApplAddr()==27)
                            {
                               Umbral_Ac = STDac_n27*Thr_Ac/2;
                               Mean_Ac = MEANac_n27;
                            }
                            else if(myApplAddr()==28)
                            {
                               Umbral_Ac = STDac_n28*Thr_Ac/2;
                               Mean_Ac = MEANac_n28;
                            }
                            else if(myApplAddr()==29)
                            {
                               Umbral_Ac = STDac_n29*Thr_Ac/2;
                               Mean_Ac = MEANac_n29;
                            }
                        }

                        /*if (TargetS== getS2())
                        {
                            human_error = normal(mean_error_S2,std_error_S2);
                            //(getS2() + vel_error)/(getS2());

                            if(myApplAddr()==1)
                            {
                               Umbral_Ac = STDac_s2_n1*Thr_Ac/2;
                               Mean_Ac = MEANac_s2_n1;
                            }
                            else if(myApplAddr()==2)
                            {
                               Umbral_Ac = STDac_s2_n2*Thr_Ac/2;
                               Mean_Ac = MEANac_s2_n2;
                            }
                            else if(myApplAddr()==3)
                            {
                               Umbral_Ac = STDac_s2_n3*Thr_Ac/2;
                               Mean_Ac = MEANac_s2_n3;
                            }
                        }

                        if (TargetS== getS3())
                        {
                            human_error = normal(mean_error_S3,std_error_S3);
                            //(getS3() + vel_error)/(getS3());

                            if(myApplAddr()==1)
                            {
                               Umbral_Ac = STDac_s3_n1*Thr_Ac/2;
                               Mean_Ac = MEANac_s3_n1;
                            }
                            else if(myApplAddr()==2)
                            {
                               Umbral_Ac = STDac_s3_n2*Thr_Ac/2;
                               Mean_Ac = MEANac_s3_n2;
                            }
                            else if(myApplAddr()==3)
                            {
                               Umbral_Ac = STDac_s3_n3*Thr_Ac/2;
                               Mean_Ac = MEANac_s3_n3;

                            }
                        }*/
                    }
                    /*else {
                        human_error = normal(mean_error_S1,std_error_S1);
                        Mean_Ac = 0;
                        Umbral_Ac =0;

                    }*/
                   // emit(targetSpeedSignal,TargetS);

                   // EV << "The Human Error is:  " << human_error << endl ;

                    //e. Calcular la aceleración deseada incluyéndole el retardo
                    double A_des_lag_sin = 0;
                    if (A_des!=0){
                       A_des_lag_sin = ((alphaLag * A_des) + ((1 - alphaLag) * lastAccelerationPlatoon));
                    }
                    //if(distanceBetweenActualAndFront-length_vehicle_front<0){A_des_lag_sin=-0.5;} // Si un nodo sobrepasa a su antecesor no aplica ninguna aceleración

                    emit(accelerationSinSignal, A_des_lag_sin);

                    // Calcular aceleración con error humano
                    double A_des_lag_Err = 0;

                    int Node_precision = 0;
                    double Node_accuracy = 0;

                   // EV << "The Acceleration threshold is:  " << Mean_Ac - Umbral_Ac << " y " <<  Mean_Ac + Umbral_Ac << endl;

                   // Aplicar Filtro con el umbral de la aceleración

                    if(myApplAddr()==0)
                    {
                       Umbral_Ac = 0;
                       Mean_Ac = 0;
                    }


                    if(A_des_lag_sin > Mean_Ac + Umbral_Ac || A_des_lag_sin < Mean_Ac - Umbral_Ac) // Si la aceleración es mayor o menor que el Umbral
                    {
                        emit(accelerationFilteredSignal, A_des_lag_sin);
                        A_des_lag_Err = A_des_lag_sin + human_error;
                        if  (A_des_lag_Err > 1.2)
                            A_des_lag_Err = 1.2;
                        else if (A_des_lag_Err < -2.6)
                            A_des_lag_Err = -2.6;

                        if(A_des_lag_sin>0 && A_des_lag_Err>0){Node_precision=1;}
                        else if(A_des_lag_sin<0 && A_des_lag_Err<0){Node_precision=1;}
                        else {Node_precision=0;}

                        emit(precisionSignal,Node_precision);

                        Node_accuracy = fabs(A_des_lag_sin-A_des_lag_Err);
                        emit(accuracySignal,Node_accuracy);
                    }
                    else
                    {
                        emit(accelerationFilteredSignal,0);
                        //A_des_lag_Err = human_error; //Corresponde solo al error humano dado que la aceleración deseada es cero
                        //SC: Aplica 0 aceleraci[on (por la incercia es mas facil mantener la velocidad que ya trae)
                        A_des_lag_Err = 0;
                        //emit(precisionSignal,Node_precision);
                    }

                    setAcceleration(A_des_lag_Err); // se aplica la aceleración al nodo con error humano

                    lastAccelerationPlatoon = A_des_lag_Err;
                   // EV << "The Acceleration asigned is: " << A_des_lag_Err << endl;
                    emit(accelerationErrorSignal, A_des_lag_Err);


                   // EV << "Node[" << myApplAddr() << "]: New desired acceleration: " << getModuleAcceleration() << endl;

                    emit(humanErrorSignal, human_error);
           }


                //Iniciar el timer para hacer la logica del platoon
                timeToPlatoonInfo = new cMessage("platoon-timer", PLATOON_TIMER);
                scheduleAt(simTime() + platoonInterval, timeToPlatoonInfo);

                break;
            }

            default:
                //EV << " Unkown self message! -> delete, kind: " << msg->getKind() << endl;
                break;
        }
    //}
        delete msg;

    }
    else
    {
        //EV << "Communication is disabled in " << myApplAddr() << endl;
    }

}

/**
 * Manejar mensajes que llegan desde las capas inferiores
 */
void CustomAppLayer::handleLowerMsg(cMessage* msg)
{

    //Mensaje de otro nodo con sus datos
    if (msg->getKind() == POSITION_MESSAGE)
    {
        CustomApplPkt *m = static_cast<CustomApplPkt *>(msg);

        EV << "I receive a message Type: " << m << endl;

        //Actualizar GUI con número de paquetes recibidos
        numReceived++;
        if (ev.isGUI())
            updateDisplay();

        //Se obtiene el ID del paquete
        int packageID = m->getId();

        //Se emite una señal indicando que llegó un paquete nuevo al nodo
        //emit(receivedSignal, packageID);

        //Se emiten las señales correspondientes a las posiciones del nodo al llegar un paquete
        emit(positionXSignal, getModuleXPosition());
        emit(positionYSignal, getModuleYPosition());
        //emit(positionXGPSErrorSignal, getModuleXPositionGPSError());


        //Obtener información del paquete para reenviar al resto de nodos
        double xposition = m->getXposition();
        double yposition = m->getYposition();
        double xpositionGPSerror = m->getXpositionGPS();
        double speed = m->getSpeed();
        double acceleration = m->getAcceleration();
        double RTTB;

        //Calculo del RTT
        //if (m->getSrcAddr() == myApplAddr()+1 &&  myApplAddr() != 3 ) // Solo hace el calculo si el paquete recibido es del nodo de atras y si no es el último, *ver como obtener el numero de nodos
        //{
        double ST = SIMTIME_DBL(simTime());  // Obtener tiempo de simulación
        double GTS = SIMTIME_DBL(m->getTimestamp()); // Obtener tiempo de envio del paquete
        RTTB = SIMTIME_DBL(m->getTimestamp()); //Calcular RTT al nodo del frente
        EV << "RTT(s)=" << m->getTimestamp()<< endl;
        EV << "SimTime=" << ST << endl;
        EV << "GetTimestamp=" << GTS << endl;
        EV << "My X Position=" << xposition << "; My X GPS position = " << xpositionGPSerror << endl;
        //}

        EV << "srcAddress" << m->getSrcAddr();

        //Crear paquete con los datos recibidos
        NodeInfo* nodeInfo = new NodeInfo();
        nodeInfo->setPackageID(packageID);
        nodeInfo->setSrcAddress(m->getSrcAddr());
        nodeInfo->setXPosition(xposition);
        nodeInfo->setYPosition(yposition);
        nodeInfo->setXPositionGPSerror(xpositionGPSerror);
        nodeInfo->setSpeed(speed);
        nodeInfo->setAcceleration(acceleration);
        nodeInfo->setLeaderAcceleration(m->getLeaderAcceleration());
        nodeInfo->setLeaderSpeed(m->getLeaderSpeed());
        nodeInfo->setRTTBack(RTTB);


        //Guardar aceleraci�n y velocidad si pertenecen al l�der
        if (m->getSrcAddr() == 0)
        {
            localLeaderAcceleration = acceleration;
            localLeaderSpeed = speed;

            //Emitir senal que indica la recepcion de un paquete del lider
            //emit(leaderInfoSignal, packageID);
            //Emitir senal que indica la recepcion de un paquete directamente del lider
            //emit(leaderInfoDirectSignal, packageID);

        }
        else if (m->getBeaconingEnabled() == true)
        {
            //Emitir senal que indica la recepcion de un paquete del lider
            //emit(leaderInfoSignal, packageID);
            //Emitir senal que indica la recepcion de un paquete del lider por multisalto
            //emit(leaderInfoMultihopSignal, packageID);
        }

        //Guardar paquete
        nodeInfoVector.push_back(nodeInfo);

        totalDistance = par("totalDistance");

//        //Detener el nodo
//        double distanceToOrigin = getAbsoluteDistance(getModuleXPosition(), getModuleYPosition(),
//                getZonaNodo(getModuleXPosition(), getModuleYPosition()));
//        if (distanceToOrigin >= totalDistance)
//        {
//            CustomMobilityAccess().get(findHost())->stop();
//
//        }
        //Se emite una senal cada vez que se envía un paquete con su ID
        //emit(sentSignal, packageID);
        delete msg;

        return;
    }

    MyTestAppLayer::handleLowerMsg(msg);
}

int CustomAppLayer::getZonaNodo(double posx, double posy)
{
    if (posx == 0 && (posy <= 800 || posy >= 0))
    {
        return 1;
    }
    else if (posy == 0 && (posx <= 800 || posx >= 0))
    {
        return 2;
    }
    else if (posx == 800 && (posy >= 0 || posy <= 800))
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

/*
 * Obtener la posición x del módulo
 */
double CustomAppLayer::getModuleXPosition()
{
    Coord c;
    double posx = 0;
    c = MobilityAccess().get(findHost())->getCurrentPosition();
    posx = c.x;
    return posx;
}

/*
 * Obtener la posición x del módulo incluido el error del gps
 */
double CustomAppLayer::getModuleXPositionGPSError()
{
    Coord c;
    double posxGPS = 0;
    c = MobilityAccess().get(findHost())->getCurrentPosition();
    posxGPS = c.x;

    //double r = (rand() % 2) * 2 - 1;
    double u = uniform(0,1);
    double position_error = position_error_a * sqrt(-position_error_b * log(u)); /* generating Rayleigh-distributed variates */
    posxGPS = posxGPS + position_error;
    return posxGPS;
}

// Función signo
int CustomAppLayer::signo(double x)
{
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

/*
 * Obtener la posición y del módulo
 */
double CustomAppLayer::getModuleYPosition()
{
    Coord c;
    double posy = 0;
    c = MobilityAccess().get(findHost())->getCurrentPosition();
    posy = c.y;
    return posy;
}

/*
 * Obtener velocidad del módulo
 */
double CustomAppLayer::getModuleSpeed()
{
    return CustomMobilityAccess().get(findHost())->getMySpeed();
}

/**
 * Obtener la aceleracion de un nodo
 */
double CustomAppLayer::getModuleAcceleration()
{
    return CustomMobilityAccess().get(findHost())->getMyAcceleration();
}

//Obtener boolean MultiSpeed
bool CustomAppLayer::getMS()
{
    return CustomMobilityAccess().get(findHost())->getMultiSpeed();
}

//Obtener tiempo de duración de cada velocidad
double CustomAppLayer::getSD()
{
    return CustomMobilityAccess().get(findHost())->getSpeedDuration();
}


//Obtener valor de la velocidad
double CustomAppLayer::getTS()
{
    return CustomMobilityAccess().get(findHost())->getTargetSpeed();
}

//Obtener valor de la velocidad 1
double CustomAppLayer::getS1()
{
    return CustomMobilityAccess().get(findHost())->getSpeed1();
}

//Obtener valor de la velocidad 2
double CustomAppLayer::getS2()
{
    return CustomMobilityAccess().get(findHost())->getSpeed2();
}

//Obtener valor de la velocidad 3
double CustomAppLayer::getS3()
{
    return CustomMobilityAccess().get(findHost())->getSpeed3();
}

/**
 * Modificar la aceleracion de un nodo
 */
void CustomAppLayer::setAcceleration(double acceleration)
{
    CustomMobilityAccess().get(findHost())->setAcceleration(acceleration);
}

/**
 * Actualizar el tag del nodo mostrando el número de paquetes recibidos y envíados
 */
void CustomAppLayer::updateDisplay()
{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    findHost()->getDisplayString().setTagArg("t", 0, buf);
}

/**
 * Obtener distancia que hay del nodo 2 al nodo 1, si el primero est� adelante del �ltimo
 */
double CustomAppLayer::getDistanceBetweenNodes(double posx_1, double posy_1, int zona_1, double posx_2, double posy_2,
        int zona_2)
{

    double absoluteDistanceN1 = getAbsoluteDistance(posx_1, posy_1, zona_1);
    double absoluteDistanceN2 = getAbsoluteDistance(posx_2, posy_2, zona_2);

    double totalDistance = absoluteDistanceN2 - absoluteDistanceN1;

    return totalDistance;
}

double CustomAppLayer::getDistanceBetweenNodes2(double posx_1, double posx_2)
{

    double totalDistance = posx_2 - posx_1;

    return totalDistance;
}

/**
 * Permite obtener la distancia del nodo al punto de referencia (0,800)
 */
double CustomAppLayer::getAbsoluteDistance(double posx, double posy, int zona)
{
    double absoluteDistance = 0;

    if (zona == 1)
    {
        absoluteDistance = 800 - posy;
    }
    else if (zona == 2)
    {
        absoluteDistance = 800 + posx;
    }
    else if (zona == 3)
    {
        absoluteDistance = 1600 + posy;
    }

    return absoluteDistance;

}

void CustomAppLayer::readCSV(const std::string &s,std::vector<double> &elems)
{
    EV << "entro a la función ReadCSV: "<< endl;
    string line;
    ifstream myfile(s.c_str());//myfile(s.c_str(),ios::app);
    //myfile.open();
    //myfile.open(s.c_str());
    if (myfile.is_open())
    {
        int a=0;
        EV << "se abre el archivo "<< endl;
        while (getline (myfile,line))// getline (myfile,line,','))
        {
            a++;
            //EV << "entro al while: "<< endl;
            //getline (myfile,line);
            //EV << "values : " << line << endl;
            //double a = atof(line);//.c_str());
            EV << "values : " << a<< endl;
            //elems.push_back(a);

        }
        EV << "values : " << a<< endl;
        myfile.close();
    }
    else{
        EV << "Error abriendo el archivo"<< endl;

    }
}

double CustomAppLayer::getRandValLowSpeed(){
    int iLS = intuniform(0,VectorDistLS.size());
    return VectorDistLS.at(iLS);
}

double CustomAppLayer::getRandValMediumSpeed(){
    int iMS = intuniform(0,VectorDistMS.size());

    return VectorDistMS.at(iMS);
}

double CustomAppLayer::getRandValHighSpeed(){
    int iHS = intuniform(0,VectorDistHS.size());
    return VectorDistHS.at(iHS);
}

CustomAppLayer::~CustomAppLayer()
{

    cancelAndDelete(timeToPlatoonInfo);

}
