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
    receivedSignal = registerSignal("received");
    positionXSignal = registerSignal("xposition");
    positionXGPSErrorSignal = registerSignal("xpositionGPSerror");
    positionYSignal = registerSignal("yposition");
    velNodeSignal = registerSignal("vel");
    sentSignal = registerSignal("sent");
    receivedBroadcastSignal = registerSignal("received_broadcast");
    arrivalTimeSignal = registerSignal("arrival_time");
    accelerationPlatoonSignal = registerSignal("accelerationPlatoon");
    accelerationErrorSignal = registerSignal("accelerationError");
    accelerationSinSignal = registerSignal("accelerationSin");
    distanceToFwdSignal = registerSignal("distanceToFwd");
    distanceToFwdRTTSignal = registerSignal("distanceToFwdRTT");
    leaderInfoSignal = registerSignal("leaderInfo");
    leaderInfoDirectSignal = registerSignal("leaderInfoDirect");
    leaderInfoMultihopSignal = registerSignal("leaderInfoMultihop");
    leaderInfoMultihopUsedSignal = registerSignal("leaderInfoMultihopUsed");


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

    alpha1 = par("alpha1");
    alpha2 = par("alpha2");
    alpha3 = par("alpha3");
    alpha4 = par("alpha4");
    alpha5 = par("alpha5");
    alphaLag = par("alphaLag");

    // Error humano asociado a la velocidad
    mean_error = par("mean_error");
    std_error = par("std_error");
    mean_vel_obj = par("mean_vel_obj");

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

    MyTestAppLayer::initialize(stage);
    if (stage == 0)
    {
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

                totalDistance = par("totalDistance");

                //Detener a todos los nodos al estar en x_final y en el 70% del y_final
                if (xposition >= totalDistance)
                {
                    if (!llegada)
                    {
                        finalSpeed = speed;
                        finalAcceleration = acceleration;
                        CustomMobilityAccess().get(findHost())->stop();
                        cout << myApplAddr() << " finish at time " << simTime() << endl;
                        //Emitir señal indicando tiempo de llegada
                        emit(arrivalTimeSignal, simTime());
                        //comEnabled = false;
                        cancelEvent(timeToPlatoonInfo);
                        llegada = true;
                    }
                    //Enviar paquete con la posicion y velocidad al resto de nodos
                    sendNodeInfo(packageID, xposition, yposition, xpositionGPSerror, speed, acceleration, LAddress::L3BROADCAST,
                            localLeaderAcceleration, localLeaderSpeed, beaconingEnabled);
                    //msg->setTimestamp(simTime()); // enviar Timestamp

                }
                else
                {

                    //Enviar paquete con la posicion y velocidad al resto de nodos
                    sendNodeInfo(packageID, xposition, yposition, xpositionGPSerror, speed, acceleration, LAddress::L3BROADCAST,
                            localLeaderAcceleration, localLeaderSpeed, beaconingEnabled);
                    //msg->setTimestamp(simTime()); // enviar Timestamp
                }

                //Actualizar GUI con numero de paquetes enviados
                numSent++;
                if (ev.isGUI())
                    updateDisplay();

                //Se emite una senal cada vez que se envia un paquete con su ID
                emit(sentSignal, packageID);

                //Se emiten dos senales con la posicion x e y del nodo al enviar un paquete
                emit(positionXSignal, xposition);
                emit(positionYSignal, yposition);
                emit(positionXGPSErrorSignal, xpositionGPSerror);

                //Volver a iniciar el timer para enviar el siguiente paquete
                positionTimer = new cMessage("position-timer", POSITION_TIMER);
                scheduleAt(simTime() + beaconInterval, positionTimer);

                EV << "Node[" << myApplAddr() << "]: Sending Position Update" << endl;

                break;
            }
            case PLATOON_TIMER:
            {
                // 1. PREPARACION

                //Lista sin duplicados

                // setear el tiempo de simulación

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

                //Calcular distancias desde los nodos hacia el actual para determinar el mas cercano
                NodeInfo*nearestNode = NULL;
                NodeInfo*leaderNode = NULL;

                EV << "Node[" << myApplAddr() << "]: Running Platoon Update" << endl;

                if (noDuplicateInfo.size() > 0)
                {

                    //a. Determinar nodo mas cercano y nodo lider
                    for (std::vector<NodeInfo*>::iterator it = noDuplicateInfo.begin(); it != noDuplicateInfo.end();
                            ++it)
                    {
                        NodeInfo* nodeInfo = *it;

                        //Obtener la distancia del nodo del que se recibio el paquete al nodo actual
                        int addr_node = nodeInfo->getSrcAddress();
                        double posx_node = nodeInfo->getXPosition();
                        double distanceToActual = getDistanceBetweenNodes2(posx, posx_node);

                        //Asignar lider
                        if (addr_node == 0)
                        {
                            leaderNode = *it;
                        }

                        //Si actualmente no hay un nodo mas cercano y la distancia del nodo al actual es mayor a cero,
                        //este es el nodo mas cercano por el momento
                        if (distanceToActual > 0 && nearestNode == NULL)
                        {
                            nearestNode = *it;
                        }

                        //Si actualmente hay un nodo mas cercano, se compara con el nodo del cual se recibio un paquete
                        if (nearestNode != NULL)
                        {
                            //Comparar con el nodo mas cercano hasta el momento
                            //int addr_node_nearest = nearestNode->getSrcAddress();
                            double posx_node_nearest = nearestNode->getXPosition();
                            //double speed_node_nearest = nearestNode->getSpeed();
                            double distanceToActual_nearest = getDistanceBetweenNodes2(posx, posx_node_nearest); // Se asume que el grupo mantiene un orden fijado con anetrioridad por lo que no se aplica el erro del GPS para detectar el nodo de enfrete

                            //Se cambia el nodo mas cercano si la distancia es menor a la del mas cercano actual
                            if (distanceToActual > 0 && distanceToActual < distanceToActual_nearest)
                            {
                                nearestNode = *it;
                            }
                        }
                    }

                    //b. Obtener informacion del nodo mas cercano que se encuentre al frente
                    double rel_speed_front;

                    double spacing_error;
                    double spacing_error_GPS;
                    double spacing_error_RTT;
                    double nodeFrontAcceleration;
                    double Speed_Ligth = 3 * (10 ^ 8);
                    //double RTT;

                    if (nearestNode != NULL)
                    {

                        //Velocidad relativa al vehiculo del frente
                        rel_speed_front = getModuleSpeed() - nearestNode->getSpeed();

                        //Obtener spacing error
                        distanceBetweenActualAndFront = getDistanceBetweenNodes2(posx, nearestNode->getXPosition());
                        spacing_error = -distanceBetweenActualAndFront + length_vehicle_front + desiredSpacing;

                        //Obtener spacing error con GPS
                        distanceBetweenActualAndFrontGPS = getDistanceBetweenNodes2(posxGPS, nearestNode->getXPositionGPSerror());
                        spacing_error_GPS = -distanceBetweenActualAndFrontGPS + length_vehicle_front + desiredSpacing;

                        // obtener spacing error con RTT

                        //RTT = 2 * ( ST - nearestNode->getTS());
                        distanceBetweenActualAndFrontRTT =  (Speed_Ligth * nearestNode->getRTTBack())/ 2;
                        spacing_error_RTT = -distanceBetweenActualAndFrontRTT + length_vehicle_front + desiredSpacing;

                        emit(distanceToFwdRTTSignal,distanceBetweenActualAndFrontRTT );

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
                            emit(leaderInfoMultihopUsedSignal,packageID);

                            leaderAcceleration = nearestNode->getLeaderAcceleration();
                            leaderSpeed = nearestNode->getLeaderSpeed();
                            localLeaderAcceleration = nearestNode->getLeaderAcceleration();
                            localLeaderSpeed = nearestNode->getLeaderSpeed();
                        }
                        else
                        {
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
                    }

                    //Print data for calculation
                    EV << "Node[" << myApplAddr() << "]: Platoon parameters" << endl;
                    EV << "distance to Vehicle in Front=" << distanceBetweenActualAndFront << endl;
                    EV << "distance to vehicle in Front RTT =" << distanceBetweenActualAndFrontRTT << endl;
                    EV << "Vehicle in Front Acceleration=" << nodeFrontAcceleration << endl;
                    EV << "Leader Acceleration=" << leaderAcceleration << endl;
                    EV << "Relative speed vehicule in front=" << rel_speed_front << endl;
                    EV << "Leader speed=" << leaderSpeed << endl;
                    EV << "My speed=" << getModuleSpeed() << endl;
                    EV << "Spacing Error=" << spacing_error << endl;

                    // Enviar valores de la velocidad
                    emit(velNodeSignal,getModuleSpeed());
                    double A_des;

                    if (GPSErrorEnabled == true) // se activa solo si el usurio quiere incluir el error del GPS
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

                    emit(accelerationPlatoonSignal, A_des);


                    // Calcular el error en base a una normal con parámetros de resultados en simulación
                    double vel_error = normal(mean_error,std_error);
                    double human_error = (mean_vel_obj + vel_error)/(mean_vel_obj);

                    //e. Calcular la aceleración deseada incluyéndole el retardo
                    double A_des_lag = ((alphaLag * A_des) + ((1 - alphaLag) * lastAccelerationPlatoon)) * human_error;

                    emit(accelerationErrorSignal, A_des_lag);

                    double A_des_lag_sin = A_des_lag/human_error;

                    emit(accelerationSinSignal, A_des_lag_sin);

                    lastAccelerationPlatoon = A_des_lag;
                    setAcceleration(A_des_lag);

                    EV << "Node[" << myApplAddr() << "]: New desired acceleration: " << getModuleAcceleration() << endl;

                    emit(distanceToFwdSignal, spacing_error); // Spacing Real
                    emit(accelerationPlatoonSignal, A_des_lag);

                }
                else
                {
                    EV << "No near nodes " << endl;
                }

                //Iniciar el timer para hacer la logica del platoon
                timeToPlatoonInfo = new cMessage("platoon-timer", PLATOON_TIMER);
                scheduleAt(simTime() + platoonInterval, timeToPlatoonInfo);

                break;
            }

            default:
                EV << " Unkown self message! -> delete, kind: " << msg->getKind() << endl;
                break;
        }
        delete msg;

    }
    else
    {
        EV << "Communication is disabled in " << myApplAddr() << endl;
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
        emit(receivedSignal, packageID);

        //Se emiten las señales correspondientes a las posiciones del nodo al llegar un paquete
        emit(positionXSignal, getModuleXPosition());
        emit(positionYSignal, getModuleYPosition());
        emit(positionXGPSErrorSignal, getModuleXPositionGPSError());


        //Obtener información del paquete para reenviar al resto de nodos
        double xposition = m->getXposition();
        double yposition = m->getYposition();
        double xpositionGPSerror = m->getXpositionGPS();
        double speed = m->getSpeed();
        double acceleration = m->getAcceleration();
        double RTTB;

        //Calculo del RTT
        if (m->getSrcAddr() == myApplAddr()+1 &&  myApplAddr() != 3 ) // Solo hace el calculo si el paquete recibido es del nodo de atras y si no es el último, *ver como obtener el numero de nodos
        {
        double ST = SIMTIME_DBL(simTime());  // Obtener tiempo de simulación
        double GTS = SIMTIME_DBL(m->getTimestamp()); // Obtener tiempo de envio del paquete
        RTTB = 2 * ( ST - GTS); //Calcular RTT al nodo del frente

        }

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
            emit(leaderInfoSignal, packageID);
            //Emitir senal que indica la recepcion de un paquete directamente del lider
            emit(leaderInfoDirectSignal, packageID);

        }
        else if (m->getBeaconingEnabled() == true)
        {
            //Emitir senal que indica la recepcion de un paquete del lider
            emit(leaderInfoSignal, packageID);
            //Emitir senal que indica la recepcion de un paquete del lider por multisalto
            emit(leaderInfoMultihopSignal, packageID);
        }

        //Guardar paquete
        nodeInfoVector.push_back(nodeInfo);

        totalDistance = par("totalDistance");

        //Detener el nodo
        double distanceToOrigin = getAbsoluteDistance(getModuleXPosition(), getModuleYPosition(),
                getZonaNodo(getModuleXPosition(), getModuleYPosition()));
        if (distanceToOrigin >= totalDistance)
        {
            CustomMobilityAccess().get(findHost())->stop();

        }
        //Se emite una senal cada vez que se envía un paquete con su ID
        emit(sentSignal, packageID);
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
    double r = (rand() % 2) * 2 - 1;
    double u = uniform(0,1);
    double position_error = position_error_a * sqrt(-position_error_b * log(u)); /* generating Rayleigh-distributed variates */
    posxGPS = posxGPS + r*position_error;
    return posxGPS;
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

CustomAppLayer::~CustomAppLayer()
{

    cancelAndDelete(timeToPlatoonInfo);

}
