import sys
import numpy as np

#Create the name of the file, SinGPS-error-Umbral-STD033-PlatoonSize-57
namePrefix = "SinGPS-error-Umbral-Base-PlatoonSize" 
#Extract the packets received from the .sca file  , $0=0.05, $1=0.05, $2=8"
out = "MeanACC-"
# Mean -> ListG1[0] , STD -> ListG[1] -> 0.5 Var
# Mean -> ListG2[0] , STD -> ListG[1] -> 2 Var
ListG1 = [[[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]],[[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]]]
ListG2 = [[[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]],[[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]]]

for k in range(0,1679):
	name= namePrefix + "-" + str(k) + ".sca" 
	f = open(name, 'r')
	temp = f.readlines()    
	j = 0
	rV = []
	NS = []
	h=0
	#print("Hola, Voy a abrir Archivo")

	while j<len(temp):
		if "attr iterationvars" in temp[j] and "$varia=0.05," in temp[j]: rV=0 
		if "attr iterationvars" in temp[j] and "$varia=0.2" in temp[j]:rV=1 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[1]" in temp[j]: Ns=0 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[2]" in temp[j]: Ns=1 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[3]" in temp[j]: Ns=2
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[4]" in temp[j]: Ns=3 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[5]" in temp[j]: Ns=4 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[6]" in temp[j]: Ns=5 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[7]" in temp[j]: Ns=6 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[8]" in temp[j]: Ns=7 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[9]" in temp[j]: Ns=8 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[10]" in temp[j]: Ns=9 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[11]" in temp[j]: Ns=10 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[12]" in temp[j]: Ns=11
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[13]" in temp[j]: Ns=12
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[14]" in temp[j]: Ns=13
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[15]" in temp[j]: Ns=14 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[16]" in temp[j]: Ns=15 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[17]" in temp[j]: Ns=16 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[18]" in temp[j]: Ns=17 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[19]" in temp[j]: Ns=18 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[20]" in temp[j]: Ns=20 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[21]" in temp[j]: Ns=21 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[22]" in temp[j]: Ns=22
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[23]" in temp[j]: Ns=23 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[24]" in temp[j]: Ns=24 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[25]" in temp[j]: Ns=25 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[26]" in temp[j]: Ns=26 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[27]" in temp[j]: Ns=27
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[28]" in temp[j]: Ns=28 
		if "accelerationSin:stats" in temp[j] and "Main_Network.node[29]" in temp[j]: Ns=29 
		if "accelerationSin:stats" in temp[j]:
			value = temp[j+2].split()
			mean= float(value[2])
			value2 = temp[j+3].split()
			std= float(value2[2])
			if rv == 0 : 
				ListG1[0][NS].append(mean)
				ListG1[1][NS].append(std)
			if rv == 0 : 
				ListG1[0][NS].append(mean)
				ListG1[1][NS].append(std)				
				
			
		j=j+1
					
	f.close()

Var1=np.zeros((2,30))
Var2=np.zeros((2,30))


#print(str(np.mean(ListG[0][0])))
for i in range(0,30):
	Var1[0][i]=np.mean(ListG1[0][i])
	Var1[1][i]=np.mean(ListG1[1][i])
	
for i in range(0,30):
	Var2[0][i]=np.mean(ListG2[0][i])
	Var2[1][i]=np.mean(ListG2[1][i])


		
	
	
#Imprimir datos en un archivo .txt
mat=np.matrix(Var1)
mat2=np.matrix(Var2)	

nameOut = out+"Var05.txt" 
fw = open(nameOut, 'w')
fw.write('Promedios (fila 1) y STD (fila 2) ACC para Var 0.05\n')
np.savetxt(fw, mat)
fw.close()	



nameOut = out+"STD.txt" 
fw = open(nameOut, 'w')
fw.write('Promedios (fila 1) y STD (fila 2) ACC para Var 0.2n')
np.savetxt(fw, mat2)
fw.close()