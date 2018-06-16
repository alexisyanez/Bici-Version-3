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

package src.modules.application;

import org.mixim.base.modules.IBaseApplLayer;

simple CustomAppLayer like IBaseApplLayer
{
    parameters:
        double totalDistance @unit(m);//Distancia total desde el inicio hasta la meta
        bool coreDebug = default(false); //debug switch for base class (TestApplLayer)
    	bool debug      = default(false); // debug switch
    	int headerLength @unit("bit"); // length of the application message header (in bits)
    	int burstSize; // size of the burst
    	bool burstReply = default(false);  // if true, send unicast replies to received broadcasts
    	
    	//Alpha values of CACC
    	double alpha1;
    	double alpha2;
    	double alpha3;
    	double alpha4;
    	double alpha5;
    	    	    	
    	//Alpha values of CACC with lag
    	double alphaLag;
    	
    	
    	//Human error in velocity response
    	double mean_error = default(0);
    	double std_error = default(0);
    	double mean_vel_obj = default(0); 
    	
    	//Human error in velocity response for multi-Speed performance
    	//Speed 1
    	double mean_error_S1 = default(0);
    	double std_error_S1 = default(0);
    	
    	//Speed2
    	double mean_error_S2 = default(0);
    	double std_error_S2 = default(0);
    	
    	//Speed3
    	double mean_error_S3 = default(0);
    	double std_error_S3 = default(0);
    	
    	//MEAN acceleration for each node
    	double MEANac_n1 = default(0);
	double MEANac_n2 = default(0);
	double MEANac_n3 = default(0);
	double MEANac_n4 = default(0);
	double MEANac_n5 = default(0);
	double MEANac_n6 = default(0);
	double MEANac_n7 = default(0);
	double MEANac_n8 = default(0);
	double MEANac_n9 = default(0);
	double MEANac_n10 = default(0);
        double MEANac_n11 = default(0);
        double MEANac_n12 = default(0);
        double MEANac_n13 = default(0);
        double MEANac_n14 = default(0);
        double MEANac_n15 = default(0);
        double MEANac_n16 = default(0);
        double MEANac_n17 = default(0);
        double MEANac_n18 = default(0);
        double MEANac_n19 = default(0);
        double MEANac_n20 = default(0);
        double MEANac_n21 = default(0);
        double MEANac_n22 = default(0);
        double MEANac_n23 = default(0);
        double MEANac_n24 = default(0);
        double MEANac_n25 = default(0);
        double MEANac_n26 = default(0);
        double MEANac_n27 = default(0);
        double MEANac_n28 = default(0);
        double MEANac_n29 = default(0);    	
    
	//STD acceleration for each node
    	        double STDac_n1 = default(0);
		double STDac_n2 = default(0);
		double STDac_n3 = default(0);
		double STDac_n4 = default(0);
		double STDac_n5 = default(0);
		double STDac_n6 = default(0);
		double STDac_n7 = default(0);
		double STDac_n8 = default(0);
		double STDac_n9 = default(0);
		double STDac_n10 = default(0);
		double STDac_n11 = default(0);
		double STDac_n12 = default(0);
		double STDac_n13 = default(0);
		double STDac_n14 = default(0);
		double STDac_n15 = default(0);
		double STDac_n16 = default(0);
		double STDac_n17 = default(0);
		double STDac_n18 = default(0);
		double STDac_n19 = default(0);
		double STDac_n20 = default(0);
		double STDac_n21 = default(0);
		double STDac_n22 = default(0);
		double STDac_n23 = default(0);
		double STDac_n24 = default(0);
		double STDac_n25 = default(0);
		double STDac_n26 = default(0);
		double STDac_n27 = default(0);
		double STDac_n28 = default(0);
		double STDac_n29 = default(0);
		
        
        //GPS Measure error
        bool GPS_error;
        double position_error_a = default(0);
        double position_error_b = default(0);
        
        //RTT Calculing distance method
        bool RTT_on;
    	
    	//Values for spacing error
    	double spacing;
    	double lenghtVehicle;
    	
    	//Update interval for beacons (position update)
    	double beaconInterval @unit(s);
    	
    	//Update interval for platoon
    	double platoonInterval @unit(s);
    	
    	//Beaconing
    	bool beaconing;
    	
    	//Threshold Acceleration
    	double Thr_Ac = default(0);
    	
    gates:
    	input lowerLayerIn; // from network layer
        output lowerLayerOut; // to network layer
        input lowerControlIn; // control from network layer
        output lowerControlOut; // control to network layer
}
