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

package src.networks.scenario1;

import org.mixim.base.modules.BaseNetwork;
import src.modules.nodes.HostBici;



network Main_Network extends BaseNetwork
{
    parameters:
        int numNodes; // total number of hosts in the network


    submodules:
        node[numNodes]: HostBici {
            parameters:
                @display("i=old/ball;b=1,1,oval,,,0;p=237,80;is=vs");

        }

}
