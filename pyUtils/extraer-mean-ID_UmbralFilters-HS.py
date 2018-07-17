import sys
import numpy as np

#Create the name of the file, SinGPS-error-Umbral-STD033-PlatoonSize-57
namePrefix = "/home/ayanez/Bici-Version-3/src/networks/scenario1/results/PlatoonSize-Umbral-withError039-High-BaseN4" 
#Extract the packets received from the .sca file  , $0=0.05, $1=0.05, $2=8" 
out = "IDsizesplatoon-UmbralFilters"

ListG = [[[],[],[]],[[],[],[]],[[],[],[]],[[],[],[]],]#[[[],[],[]],[[],[],[]]],[[[],[],[]],[[],[],[]]],[[[],[],[]],[[],[],[]]]]#,[[[],[],[]],[[],[],[]]]]

for k in range(0,30):
	#if k==417 or k==885 or k==234 or k==286 or k==545 or k==1041 or k==1630 or k==12 or k==475 or k==216 or k==144 or k==673 or k==55 or k==219 or k==1084 or k==273 or k==291 or k==266 or k==122 or k==106 or k==966 or k==820 or k==1465 or k==1364 or k==1345 or k==1378 or k==769 or k==1657 or k==1595 or k==258 or k==1111 or k==800 or k==1585 or k==549 or k==534 or k==823 or k==523 or k==571 or k==1293 or k==414 or k==982 or k==1143 or k==1291 or k==214 or k==805 or k==502 or k==691 or k==1271 or k==1633 or k==777 or k==911 or k==1087 or k==1112 or k==1297 or k==1127 or k==21 or k==763 or k==377 or k==385 or k==1629 or k==1661 or k==1285 or k==84 or k==362 or k==1490 or k==869 or k==542 or k==1065 or k==1648 or k==158 or k==503 or k==1318 or k==324 or k==583 or k==977 or k==233 or k==562 or k==1148 or k==114 or k==1400 : continue
	name= namePrefix + "-" + str(k) + ".sca" 
	f = open(name, 'r')
	temp = f.readlines()    
	j = 0
	#~ rV = []
	Ns = []
	h=0


	while j<len(temp):
		#~ if "attr iterationvars" in temp[j] and "$0=0.25," in temp[j]: rV=0 
		#~ if "attr iterationvars" in temp[j] and "$0=0.3" in temp[j]:rV=1 
		if "distanceToFwd:stats" in temp[j] and "Main_Network.node[1]" in temp[j]: Ns=0
		if "distanceToFwd:stats" in temp[j] and "Main_Network.node[2]" in temp[j]: Ns=1 
		if "distanceToFwd:stats" in temp[j] and "Main_Network.node[3]" in temp[j]: Ns=2
		

		if "distanceToFwd:stats" in temp[j] and not "Main_Network.node[0]" in temp[j]:
			value = temp[j+2].split()
			#print("Tamano del peloton: "+ str(NS))
			#print("variabilidad: "+str(rV))
			uno= float(value[2])
			#print("promedio: "+ str(uno))
			#~ NS=int(NS)
			ListG[0][Ns].append(uno)
			#print("Var: "+str(rV)+" SizeP: "+str(NS)+" mean: "+str(uno))
			#print(uno)
			#h=h+1
			#print(h)
		j=j+1
					
	f.close()


namePrefix = "/home/ayanez/Bici-Version-3/src/networks/scenario1/results/PlatoonSize-Umbral-withError039-High-STDN4" 

for k in range(0,90):
	#if k==417 or k==885 or k==234 or k==286 or k==545 or k==1041 or k==1630 or k==12 or k==475 or k==216 or k==144 or k==673 or k==55 or k==219 or k==1084 or k==273 or k==291 or k==266 or k==122 or k==106 or k==966 or k==820 or k==1465 or k==1364 or k==1345 or k==1378 or k==769 or k==1657 or k==1595 or k==258 or k==1111 or k==800 or k==1585 or k==549 or k==534 or k==823 or k==523 or k==571 or k==1293 or k==414 or k==982 or k==1143 or k==1291 or k==214 or k==805 or k==502 or k==691 or k==1271 or k==1633 or k==777 or k==911 or k==1087 or k==1112 or k==1297 or k==1127 or k==21 or k==763 or k==377 or k==385 or k==1629 or k==1661 or k==1285 or k==84 or k==362 or k==1490 or k==869 or k==542 or k==1065 or k==1648 or k==158 or k==503 or k==1318 or k==324 or k==583 or k==977 or k==233 or k==562 or k==1148 or k==114 or k==1400 : continue
	name= namePrefix + "-" + str(k) + ".sca" 
	f = open(name, 'r')
	temp = f.readlines()    
	j = 0
	rV = []
	Ns = []
	h=0
	#print("Hola, Voy a abrir Archivo")

	while j<len(temp):
		#~ if "attr iterationvars" in temp[j] and "$0=0.25," in temp[j]: rV=0 
		#~ if "attr iterationvars" in temp[j] and "$0=0.3" in temp[j]:rV=1 
		if "attr iterationvars" in temp[j] and "$0=0.25," in temp[j]: rV=1#0.25 
		if "attr iterationvars" in temp[j] and "$0=0.33" in temp[j]:rV=2#0.33 
		if "attr iterationvars" in temp[j] and "$0=0.5" in temp[j]:rV=3#0.5 
		if "distanceToFwd:stats" in temp[j] and "Main_Network.node[1]" in temp[j]: Ns=0
		if "distanceToFwd:stats" in temp[j] and "Main_Network.node[2]" in temp[j]: Ns=1 
		if "distanceToFwd:stats" in temp[j] and "Main_Network.node[3]" in temp[j]: Ns=2
		
		#~ if "attr iterationvars" in temp[j] and "$2=4" in temp[j]: NS=0	
		#~ if "attr iterationvars" in temp[j] and "$2=6" in temp[j]: NS=1
		#~ if "attr iterationvars" in temp[j] and "$2=8" in temp[j]: NS=2
		#~ if "attr iterationvars" in temp[j] and "$2=10" in temp[j]: NS=3
		#~ if "attr iterationvars" in temp[j] and "$2=12" in temp[j]: NS=4
		#~ if "attr iterationvars" in temp[j] and "$2=14" in temp[j]: NS=5
		#~ if "attr iterationvars" in temp[j] and "$2=16" in temp[j]: NS=6
		#~ if "attr iterationvars" in temp[j] and "$2=18" in temp[j]: NS=7
		#~ if "attr iterationvars" in temp[j] and "$2=20" in temp[j]: NS=8
		#~ if "attr iterationvars" in temp[j] and "$2=22" in temp[j]: NS=9
		#~ if "attr iterationvars" in temp[j] and "$2=24" in temp[j]: NS=10
		#~ if "attr iterationvars" in temp[j] and "$2=26" in temp[j]: NS=11
		#~ if "attr iterationvars" in temp[j] and "$2=28" in temp[j]: NS=12
		#~ if "attr iterationvars" in temp[j] and "$2=30" in temp[j]: NS=13	
		#~ if "attr iterationvars" in temp[j] and "$varia=0.05," in temp[j]: rV=0 
		#~ if "attr iterationvars" in temp[j] and "$varia=0.1" in temp[j]: rV=1 
		#~ if "attr iterationvars" in temp[j] and "$varia=0.15" in temp[j]: rV=2 
		#~ if "attr iterationvars" in temp[j] and "$varia=0.2" in temp[j]:rV=3 
		#~ if "attr iterationvars" in temp[j] and "$varia=0.25" in temp[j]: rV=4 			
		#~ if "attr iterationvars" in temp[j] and "$varia=0.3" in temp[j]: rV=5 
	
		if "distanceToFwd:stats" in temp[j] and not "Main_Network.node[0]" in temp[j]:
			value = temp[j+2].split()
			#print("Tamano del peloton: "+ str(NS))
			#print("variabilidad: "+str(rV))
			uno= float(value[2])
			#print("promedio: "+ str(uno))
			#~ NS=int(NS)
			ListG[rV][Ns].append(uno)
			#print("Var: "+str(rV)+" SizeP: "+str(NS)+" mean: "+str(uno))
			#print(uno)
			#h=h+1
			#print(h)
		j=j+1
					
	f.close()


	#print("Cerre el archivo") 

# Promedios y desviacion estandar paracada config
# Filas -> variability Columnas -> Sizes
M=np.zeros((4,3))
STD = np.zeros((4,3))	

#print(str(np.mean(ListG[0][0])))
for i in range(0,4):
	for j in range(0,3):
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

nameOut = out+".txt" 
fw = open(nameOut, 'w')
fw.write('Promedios Filas -> Tipo de filtro , Columnas -> Nodo \n')
np.savetxt(fw, mat)
fw.write('Desviacion estandar Filas -> Tipo de filtro , Columnas -> Nodo\n')
np.savetxt(fw, mat2)
fw.close()	
    #for line in mat:
    #   np.savetxt(fw, line, fmt='%.3f')


#~ nameOut = out+"STD.txt" 
#~ fw = open(nameOut, 'w')
#~ fw.write('Desviacion estandar Filas -> variability Columnas -> Sizes \n')
#~ np.savetxt(fw, mat2)
#~ fw.close()


	

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






