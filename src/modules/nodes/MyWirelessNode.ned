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

import org.mixim.modules.nic.IWirelessNicUpperCtrl;
import org.mixim.base.modules.IBaseArp;
import org.mixim.base.modules.IBaseApplLayer;
import org.mixim.base.modules.IBaseNetwLayer;
import org.mixim.modules.power.battery.BatteryStats;
import org.mixim.modules.power.battery.SimpleBattery;
import inet.mobility.IMobility;
import src.modules.mobility.models.CustomLinearMobility;
import src.modules.application.CustomAppLayer;


//
// Standard host module for a wireless MiXiM host with configurable NIC, and OSI 
// layers, and mobility module.
//
module MyWirelessNode{
    parameters:
        double totalDist @unit(m) = default(2400 m);
        string networkType = default("BaseNetwLayer");       //type of the network layer
        string applicationType = default("CustomAppLayer");  //type of the application layer
        string mobilityType; //type of the mobility module
        string arpType = default("org.mixim.modules.netw.ArpHost");  //type of address resolution module
        string nicType = default("Nic802154_TI_CC2420");

        @display("bgb=210,450,white;i=device/palm;b=40,40,rect");
        @node();
        
    gates:
        input radioIn; // gate for sendDirect
    submodules:
        arp: <arpType> like IBaseArp {
                @display("p=140,100;i=block/network2");
        }
        mobility: CustomLinearMobility{
            parameters:
                totalDistance = totalDist;
                @display("p=140,30;i=block/cogwheel");
        }
        nic: <nicType> like IWirelessNicUpperCtrl {
            parameters:
                @display("p=70,380;i=block/wrxtx,#008000");
        }
        // OSI network layer
        netwl: <networkType> like IBaseNetwLayer {
            parameters:
                @display("p=70,200;i=block/layer");
        }
        
        appl: CustomAppLayer {
            parameters:
                totalDistance = totalDist;
                @display("p=70,30;i=app");
        }
        
        batteryStats: BatteryStats {
            @display("p=140,240;i=block/table,#FF8040");
        }
        battery: SimpleBattery {
            @display("p=140,170;i=block/plug,#FF8000");
        }
    connections:
        nic.upperLayerOut --> netwl.lowerLayerIn;
        nic.upperLayerIn <-- netwl.lowerLayerOut;
        nic.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> netwl.lowerControlIn;
        nic.upperControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- netwl.lowerControlOut;

        //# finaly we connect the highest existing layer of transport, session, or presentation to
        //# the application layer if specified
        //if (applicationType != "") {
            netwl.upperLayerOut --> appl.lowerLayerIn;
            netwl.upperLayerIn <-- appl.lowerLayerOut;
            netwl.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> appl.lowerControlIn;
            netwl.upperControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- appl.lowerControlOut;
        //}

        
        radioIn --> nic.radioIn;
}

module MyWirelessNodeNetwl extends MyWirelessNode
{
    parameters:
        applicationType = default("");  //type of the application layer

	connections allowunconnected:
}

module MyWirelessNodePlusTran extends MyWirelessNode
{
    parameters:
        applicationType = default("");  //type of the application layer
}

