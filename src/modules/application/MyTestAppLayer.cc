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

#include "MyTestAppLayer.h"
#include "NetwControlInfo.h"
#include "SimpleAddress.h"
#include "CustomApplPkt_m.h"

using std::endl;

MyTestAppLayer::MyTestAppLayer() :
        BaseApplLayer(), positionTimer(NULL), coreDebug(false)
{
    // TODO Auto-generated constructor stub
}

/**
 * First we have to initialize the module from which we derived ours,
 * in this case BasicModule.
 *
 * Then we will set a timer to indicate the first time we will send a
 * message
 *
 **/
void MyTestAppLayer::initialize(int stage)
{
    BaseApplLayer::initialize(stage);

    if (stage == 0)
    {
        hasPar("coreDebug") ? coreDebug = par("coreDebug").boolValue() : coreDebug = false;
        positionTimer = new cMessage("position-timer", POSITION_TIMER);
        platoonTimer = new cMessage("platoon-timer", PLATOON_TIMER);
    }
    else if (stage == 1)
    {

        //scheduleAt(simTime() + dblrand() * 10, positionTimer);
        scheduleAt(simTime() + uniform(0, 5), positionTimer);
        //scheduleAt(simTime() + dblrand() * 20, platoonTimer);
        scheduleAt(simTime() + 10, platoonTimer);
    }
}

/**
 * There are two kinds of messages that can arrive at this module: The
 * first (kind = BROADCAST_MESSAGE) is a broadcast packet from a
 * neighbor node to which we have to send a reply. The second (kind =
 * BROADCAST_REPLY_MESSAGE) is a reply to a broadcast packet that we
 * have send and just causes some output before it is deleted
 **/
void MyTestAppLayer::handleLowerMsg(cMessage* msg)
{
    CustomApplPkt *m;
    switch (msg->getKind())
    {
        case BROADCAST_MESSAGE:
            m = static_cast<CustomApplPkt *>(msg);
            coreEV << "Received a broadcast packet from host[" << m->getSrcAddr() << "] -> sending reply" << endl;
            // sendReply(m);
            break;
        case BROADCAST_REPLY_MESSAGE:
            m = static_cast<CustomApplPkt *>(msg);
            coreEV << "Received reply from host[" << m->getSrcAddr() << "]; delete msg" << endl;
            delete msg;
            break;
        default:
            EV << "Error! got packet with unknown kind: " << msg->getKind() << endl;
            delete msg;
            break;
    }
}

/**
 * A timer with kind = SEND_BROADCAST_TIMER indicates that a new
 * broadcast has to be send (@ref sendBroadcast).
 *
 * There are no other timer implemented for this module.
 *
 * @sa sendBroadcast
 **/
void MyTestAppLayer::handleSelfMsg(cMessage *msg)
{
    switch (msg->getKind())
    {
        case SEND_BROADCAST_TIMER:
            //sendBroadcast();
            delete msg;
            positionTimer = NULL;

            break;
        default:
            EV << "Unknown selfmessage! -> delete, kind: " << msg->getKind() << endl;
            delete msg;
            break;
    }
}

/**
 * This function creates a new broadcast message and sends it down to
 * the network layer
 **/
void MyTestAppLayer::sendBroadcast(int id, double xpos, double ypos, double speed)
{
    CustomApplPkt *pkt = new CustomApplPkt("BROADCAST_MESSAGE", BROADCAST_MESSAGE);
    pkt->setDestAddr(LAddress::L3BROADCAST);
    // we use the host modules getIndex() as a appl address
    pkt->setSrcAddr(myApplAddr());
    pkt->setBitLength(headerLength);

    //Añadir id, posiciones y velocidad al paqueteLAddress::L3BROADCAST
    pkt->setId(id);
    pkt->setXposition(xpos);
    pkt->setYposition(ypos);
    pkt->setSpeed(speed);

    // set the control info to tell the network layer the layer 3
    // address;
    NetwControlInfo::setControlInfo(pkt, LAddress::L3BROADCAST);
    coreEV << "Sending broadcast packet!" << endl;
    sendDown(pkt);

}

void MyTestAppLayer::sendReply(CustomApplPkt *msg)
{
    simtime_t delay;

    delay = uniform(0, 0.01);

    msg->setDestAddr(msg->getSrcAddr());
    msg->setSrcAddr(myApplAddr());
    msg->setKind(BROADCAST_REPLY_MESSAGE);
    msg->setName("BROADCAST_REPLY_MESSAGE");
    sendDelayedDown(msg, delay);

    coreEV << "sent message with delay " << delay << endl;

    //NOTE: the NetwControl info was already ste by the network layer
    //and stays the same
}

/**
 * Permite enviar un paquete que contiene la información de un nodo al resto de nodos
 */
void MyTestAppLayer::sendNodeInfo(int id, double xpos, double ypos, double speed, double acceleration, int destAddress,
        double leaderAcceleration, double leaderSpeed, bool beaconingEnabled)
{
    CustomApplPkt *pkt = new CustomApplPkt("Node Info", POSITION_MESSAGE);
    pkt->setDestAddr(destAddress);
    // we use the host modules getIndex() as a appl address
    pkt->setSrcAddr(myApplAddr());
    pkt->setBitLength(headerLength);

    //Añadir id, posiciones, velocidad y aceleración al paquete
    pkt->setId(id);
    pkt->setXposition(xpos);
    pkt->setYposition(ypos);
    pkt->setSpeed(speed);
    pkt->setAcceleration(acceleration);
    pkt->setBeaconingEnabled(beaconingEnabled);

    //Agregar datos del l�der
    if (beaconingEnabled)
    {
        pkt->setLeaderAcceleration(leaderAcceleration);
        pkt->setLeaderSpeed(leaderSpeed);
    }
    else
    {
        pkt->setLeaderAcceleration(0.0);
        pkt->setLeaderSpeed(0.0);
    }

    // set the control info to tell the network layer the layer 3
    // address;
    NetwControlInfo::setControlInfo(pkt, LAddress::L3BROADCAST);
    coreEV << "Sending broadcast packet!" << endl;
    sendDown(pkt);
}

MyTestAppLayer::~MyTestAppLayer()
{
    // TODO Auto-generated destructor stub
    cancelAndDelete(positionTimer);
//    cancelAndDelete(platoonTimer);
}

