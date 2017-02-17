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
    	double MEANac_s1_n1 = default(0);
		double MEANac_s2_n1 = default(0);
		double MEANac_s3_n1 = default(0);
		double MEANac_s1_n2 = default(0);
		double MEANac_s2_n2 = default(0);
		double MEANac_s3_n2 = default(0);
		double MEANac_s1_n3 = default(0);
		double MEANac_s2_n3 = default(0);
		double MEANac_s3_n3 = default(0);
    	
    	//STD acceleration for each node
    	double STDac_s1_n1 = default(0);
		double STDac_s2_n1 = default(0);
		double STDac_s3_n1 = default(0);
		double STDac_s1_n2 = default(0);
		double STDac_s2_n2 = default(0);
		double STDac_s3_n2 = default(0);
		double STDac_s1_n3 = default(0);
		double STDac_s2_n3 = default(0);
		double STDac_s3_n3 = default(0);
        
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