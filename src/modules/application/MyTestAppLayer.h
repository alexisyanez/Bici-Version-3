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

#ifndef MYTESTAPPLAYER_H_
#define MYTESTAPPLAYER_H_

#include "MiXiMDefs.h"
#include "BaseApplLayer.h"

class CustomApplPkt;

class MIXIM_API MyTestAppLayer : public BaseApplLayer
{
    public:
        MyTestAppLayer();
        virtual ~MyTestAppLayer();

        /** @brief Initialization of the module and some variables*/
        virtual void initialize(int);

        /** @brief Message kinds used by this layer.*/
        enum MyTestAppMessageKinds
        {
            SEND_BROADCAST_TIMER = LAST_BASE_APPL_MESSAGE_KIND,
            BROADCAST_MESSAGE,
            BROADCAST_REPLY_MESSAGE,
            LAST_TEST_APPL_MESSAGE_KIND,
            POSITION_TIMER,
            POSITION_MESSAGE,
            PLATOON_TIMER
        };

    private:
        /** @brief Copy constructor is not allowed.
         */
        MyTestAppLayer(const MyTestAppLayer&);
        /** @brief Assignment operator is not allowed.
         */
        MyTestAppLayer& operator=(const MyTestAppLayer&);

    protected:
        /** @brief Timer message for scheduling next position message.*/
        cMessage *positionTimer;

        cMessage *platoonTimer;

        /** @brief Enables debugging of this module.*/
        bool coreDebug;

    protected:
        /** @brief Handle self messages such as timer... */
        virtual void handleSelfMsg(cMessage*);

        /** @brief Handle messages from lower layer */
        virtual void handleLowerMsg(cMessage*);

        /** @brief send a broadcast packet to all connected neighbors */
        void sendBroadcast(int id, double xpos, double ypos, double speed);

        /** @brief send a reply to a broadcast message */
        void sendReply(CustomApplPkt *msg);

        /** @brief Permite enviar la información del nodo al resto de nodos */
        void sendNodeInfo(int id, double xpos, double ypos, double speed, double acceleration, int destAdress,
                double leaderAcceleration, double leaderSpeed, bool beaconingEnabled);
};

#endif /* MYTESTAPPLAYER_H_ */
