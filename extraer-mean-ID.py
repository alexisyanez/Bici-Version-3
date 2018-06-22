import sys
import numpy as np

#Create the name of the file, SinGPS-error-Umbral-STD033-PlatoonSize-57
namePrefix = "SinGPS-error-Umbral-STD033-PlatoonSize" 
#Extract the packets received from the .sca file  , $0=0.05, $1=0.05, $2=8"
out = "IDsizesplatoon-"

#ListS4 = []
#ListS6 = []
#ListS8 = []
#ListS10 = []
#ListS12 = []
#ListS14 = []
#ListS16 = []
#ListS18 = []
#ListS20 = []
#ListS22 = []
#ListS24 = []
#ListS26 = []
#ListS28 = []
#ListS30 = []

#listV0 = [ListS4,ListS6,ListS8,ListS10,ListS12,ListS14,ListS16,ListS18,ListS20,ListS22,ListS24,ListS26,ListS28,ListS30]
#listV1 = [ListS4,ListS6,ListS8,ListS10,ListS12,ListS14,ListS16,ListS18,ListS20,ListS22,ListS24,ListS26,ListS28,ListS30]
#listV2 = [ListS4,ListS6,ListS8,ListS10,ListS12,ListS14,ListS16,ListS18,ListS20,ListS22,ListS24,ListS26,ListS28,ListS30]
#listV3 = [ListS4,ListS6,ListS8,ListS10,ListS12,ListS14,ListS16,ListS18,ListS20,ListS22,ListS24,ListS26,ListS28,ListS30]
#listV4 = [ListS4,ListS6,ListS8,ListS10,ListS12,ListS14,ListS16,ListS18,ListS20,ListS22,ListS24,ListS26,ListS28,ListS30]
#listV5 = [ListS4,ListS6,ListS8,ListS10,ListS12,ListS14,ListS16,ListS18,ListS20,ListS22,ListS24,ListS26,ListS28,ListS30]

ListG = [[[],[],[],[],[],[],[],[],[],[],[],[],[],[]],[[],[],[],[],[],[],[],[],[],[],[],[],[],[]],[[],[],[],[],[],[],[],[],[],[],[],[],[],[]],[[],[],[],[],[],[],[],[],[],[],[],[],[],[]],[[],[],[],[],[],[],[],[],[],[],[],[],[],[]],[[],[],[],[],[],[],[],[],[],[],[],[],[],[]]]

for k in range(0,1679):
	if k==217 or k==233 or k==266 or k==291 or k==512 or k==513 or k==552 or k==670 or k==687 or k==752 or k==785 or k==800 or k==805 or k==809 or k==820 or k==910 or k==1004 or k==1027 or k==1029 or k==1065 or k==1067 or k==1084 or k==1087 or k==1092 or k==1111 or k==1112 or k==1257 or k==1277 or k==1297 or k==1331 or k==1360 or k==1364 or k==1365 or k==1373 or k==1382 or k==1394 or k==1513 or k==1555 or k==1582 or k==1612 or k==1626 or k==1633 or k==1636 or k==1661: continue
	name= namePrefix + "-" + str(k) + ".sca" 
	f = open(name, 'r')
	temp = f.readlines()    
	j = 0
	rV = []
	NS = []
	h=0
	#print("Hola, Voy a abrir Archivo")

	while j<len(temp):
		if "attr iterationvars" in temp[j] and "$2=4" in temp[j]: NS=0	
		if "attr iterationvars" in temp[j] and "$2=6" in temp[j]: NS=1
		if "attr iterationvars" in temp[j] and "$2=8" in temp[j]: NS=2
		if "attr iterationvars" in temp[j] and "$2=10" in temp[j]: NS=3
		if "attr iterationvars" in temp[j] and "$2=12" in temp[j]: NS=4
		if "attr iterationvars" in temp[j] and "$2=14" in temp[j]: NS=5
		if "attr iterationvars" in temp[j] and "$2=16" in temp[j]: NS=6
		if "attr iterationvars" in temp[j] and "$2=18" in temp[j]: NS=7
		if "attr iterationvars" in temp[j] and "$2=20" in temp[j]: NS=8
		if "attr iterationvars" in temp[j] and "$2=22" in temp[j]: NS=9
		if "attr iterationvars" in temp[j] and "$2=24" in temp[j]: NS=10
		if "attr iterationvars" in temp[j] and "$2=26" in temp[j]: NS=11
		if "attr iterationvars" in temp[j] and "$2=28" in temp[j]: NS=12
		if "attr iterationvars" in temp[j] and "$2=30" in temp[j]: NS=13	
		if "attr iterationvars" in temp[j] and "$varia=0.05," in temp[j]: rV=0 
		if "attr iterationvars" in temp[j] and "$varia=0.1" in temp[j]: rV=1 
		if "attr iterationvars" in temp[j] and "$varia=0.15" in temp[j]: rV=2 
		if "attr iterationvars" in temp[j] and "$varia=0.2" in temp[j]:rV=3 
		if "attr iterationvars" in temp[j] and "$varia=0.25" in temp[j]: rV=4 			
		if "attr iterationvars" in temp[j] and "$varia=0.3" in temp[j]: rV=5 
	
		if "distanceToFwd:stats" in temp[j] and not "Main_Network.node[0]" in temp[j]:
			value = temp[j+2].split()
			#print("Tamano del peloton: "+ str(NS))
			#print("variabilidad: "+str(rV))
			uno= float(value[2])
			#print("promedio: "+ str(uno))
			NS=int(NS)
			ListG[rV][NS].append(uno)
			#print("Var: "+str(rV)+" SizeP: "+str(NS)+" mean: "+str(uno))
			#print(uno)
			#h=h+1
			#print(h)
		j=j+1
					
	f.close()
	#print("Cerre el archivo") 

# Promedios y desviacion estandar paracada config
# Filas -> variability Columnas -> Sizes
M=np.zeros((6,14))
STD = np.zeros((6,14))	

#print(str(np.mean(ListG[0][0])))
for i in range(0,6):
	for j in range(0,14):	
		M[i][j]=np.mean(ListG[i][j])
		#print(np.mean(ListG[i][j]))
		STD[i][j]=np.std(ListG[i][j])
		#print(np.std(ListG[i][j]))
	
	
#Imprimir datos en un archivo .txt
print("Promedios de configuracion")
print(M)
print("Desviacion Estandar de configuracion")
print(STD)
	
mat=np.matrix(M)
mat2=np.matrix(STD)	

nameOut = out+"MEAN.txt" 
fw = open(nameOut, 'w')
fw.write('Promedios Filas -> variability Columnas -> Sizes \n')
np.savetxt(fw, mat)
fw.close()	
    #for line in mat:
    #   np.savetxt(fw, line, fmt='%.3f')


nameOut = out+"STD.txt" 
fw = open(nameOut, 'w')
fw.write('Desviacon estandar Filas -> variability Columnas -> Sizes \n')
np.savetxt(fw, mat2)
fw.close()


	

#with open(nameOut, 'w') as f:
#    for line in mat:
#        np.savetxt(f, line, fmt='%.2f')


#fw.close()	

#l = 0
#for i in range(0,h):
#	fw.write('run'+str(l)+'= {0} \n'.format(item, list1[l]))
#	l = l+1

#nameOut = out + str(4) + "-Nodo2.txt" 
#fw = open(nameOut, 'w')
#l = 0
#for item in list2:
#	fw.write('run'+str(l)+'= {0} \n'.format(item, list2[l]))
#	l = l+1
	
#nameOut = out + str(4) + "-Nodo3.txt" 
#fw = open(nameOut, 'w')
#l = 0
#for item in list3:
#	fw.write('run'+str(l)+'= {0} \n'.format(item, list3[l]))
#	l = l+1	

#fw.close()	






