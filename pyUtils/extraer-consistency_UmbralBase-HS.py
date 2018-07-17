import sys
import numpy as np

#Create the name of the file, SinGPS-error-Umbral-STD033-PlatoonSize-57
namePrefix = "/home/ayanez/Bici-Version-3/src/networks/scenario1/results/PlatoonSize-Umbral-withError039-High-BaseN4" 
#Extract the packets received from the .sca file  , $0=0.05, $1=0.05, $2=8"
out = "Consistency-UmbralBase"

ListG = [[],[],[],[],[],[]]

for k in range(0,30):
	name= namePrefix + "-" + str(k) + ".sca" 
	f = open(name, 'r')
	temp = f.readlines()    
	j = 0
	#rV = []
	Ns = []
	h=0
	
	while j<len(temp):
		
		#if "attr iterationvars" in temp[j] and "$0=0.25" in temp[j]: 
		#	rV=0 
			
		#if "attr iterationvars" in temp[j] and "$0=0.3" in temp[j]:rV=1 
		
	
		if "accuracy:stats" in temp[j] and not "Main_Network.node[0]" in temp[j]:# and rV==1 :
			value = temp[j+2].split()
			Acc= float(value[2])
			ListG[5].append(Acc);
			#print('Dentro del if 1',Acc);
			
		if "precision:stats" in temp[j] and "Main_Network.node[1]" in temp[j]: Ns=1
		if "precision:stats" in temp[j] and "Main_Network.node[2]" in temp[j]: Ns=2 
		if "precision:stats" in temp[j] and "Main_Network.node[3]" in temp[j]: Ns=3
		if "precision:stats" in temp[j] and not "Main_Network.node[0]" in temp[j]:# and rV==1 :
			value = temp[j+1].split()
			uno= float(value[2]) #Count
			
			#~ value = temp[j+2].split()
			#~ dos= float(value[2])

			value = temp[j+4].split()
			tres= float(value[2]) #Sum
							
			Hit=tres;
			Miss=uno-Hit
			Und=530-uno
			#print(Miss);							
			ListG[0].append(Ns);
			ListG[1].append(k);
			ListG[2].append(Hit);
			ListG[3].append(Miss);
			ListG[4].append(Und);
		
		j=j+1
					
	f.close()

#print(ListG);

nameOut = out+".csv" 
fw = open(nameOut, 'w')
fw.write('Node, run , hit , miss , und , Acc \n')

for i in range(0,len(ListG[0])):
	#file.write(str(a[index]) + " " + str(b[index]) + "\n")
	fw.write(str(ListG[0][i])+" ,"+str(ListG[1][i])+" ,"+str(ListG[2][i])+" ,"+str(ListG[3][i])+" ,"+str(ListG[4][i])+" ,"+str(ListG[5][i]))
	fw.write("\n")
  
#fw.write(ListG) #np.savetxt(fw,ListG)
  
fw.close()	


#Create the name of the file, SinGPS-error-Umbral-STD033-PlatoonSize-57
namePrefix = "/home/ayanez/Bici-Version-3/src/networks/scenario1/results/PlatoonSize-Umbral-withError039-High-STDN4" 
#Extract the packets received from the .sca file  , $0=0.05, $1=0.05, $2=8"
out = "Consistency-UmbralSTD"

ListG = [[],[],[],[],[],[],[]]

for k in range(0,90):
	name= namePrefix + "-" + str(k) + ".sca" 
	f = open(name, 'r')
	temp = f.readlines()    
	j = 0
	rV = []
	Ns = []
	h=0


	while j<len(temp):
		if "attr iterationvars" in temp[j] and "$0=0.25," in temp[j]: rV=0.25 
		if "attr iterationvars" in temp[j] and "$0=0.33" in temp[j]:rV=0.33 
		if "attr iterationvars" in temp[j] and "$0=0.5" in temp[j]:rV=0.5 
		

		
	
		if "accuracy:stats" in temp[j] and not "Main_Network.node[0]" in temp[j]:
			value = temp[j+2].split()
			Acc= float(value[2])
			ListG[5].append(Acc);
		if "precision:stats" in temp[j] and "Main_Network.node[1]" in temp[j]: Ns=1
		if "precision:stats" in temp[j] and "Main_Network.node[2]" in temp[j]: Ns=2 
		if "precision:stats" in temp[j] and "Main_Network.node[3]" in temp[j]: Ns=3
		if "precision:stats" in temp[j] and not "Main_Network.node[0]" in temp[j]:
			value = temp[j+1].split()
			uno= float(value[2]) #Count
			
			#~ value = temp[j+2].split()
			#~ dos= float(value[2])

			value = temp[j+4].split()
			tres= float(value[2]) #Sum
							
			Hit=tres;
			Miss=uno-Hit
			Und=530-uno
										
			ListG[0].append(Ns);
			ListG[1].append(k);
			ListG[2].append(Hit);
			ListG[3].append(Miss);
			#print(Miss);
			ListG[4].append(Und);
			
			ListG[6].append(rV);
		j=j+1
					
	f.close()

#print(ListG);

nameOut = out+".csv" 
fw = open(nameOut, 'w')
fw.write('Node, run , hit , miss , und , Acc , Filtro \n')
for i in range(0,len(ListG[0])):
	#file.write(str(a[index]) + " " + str(b[index]) + "\n")
	fw.write(str(ListG[0][i])+" ,"+str(ListG[1][i])+" ,"+str(ListG[2][i])+" ,"+str(ListG[3][i])+" ,"+str(ListG[4][i])+" ,"+str(ListG[5][i])+" ,"+str(ListG[6][i]))
	fw.write("\n")
  
fw.close()	




	








