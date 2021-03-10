def CompteurLigne():
    from os import listdir

    fichier = [ f for f in listdir() if ".cpp" in f or ".h" in f ]
    print(fichier)

    line=""
    total=NbrFonction=truc=0
    compteur=[ 0 for x in range(len(fichier ) )]

    for i in range( len(fichier) ) :
        
        FichierTemp = open(fichier[i],"r")
        line = FichierTemp.readline()
        
        while line != "" :
            line = FichierTemp.readline()
            if "def" in line:
                NbrFonction+=1
            compteur[i]+= 1
        total += compteur[i]
        FichierTemp.close()
    
    line="Nombre de fonction : {}".format(NbrFonction)
    print(line)

    line="Nombre de fichier : {}\n".format(len(fichier))
    print(line)
    for i in range(0, len(fichier)):
        line="{} lignes dans {}, soit : {}%".format(compteur[i], fichier[i], float(compteur[i])*100/float(total))
        print(line)
        truc +=  float(compteur[i])*100/float(total)

    line="\nNombre de lignes totale : {}".format(total)
    print(line)
    print( truc )

CompteurLigne()
while True :
    pass

