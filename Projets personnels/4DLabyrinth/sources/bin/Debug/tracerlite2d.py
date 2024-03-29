# -*- coding: latin1 -*-

from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt
import numpy as np
import sys

def tracerhyper2(L):
    global T
    n = len(L)
    if n == 2:
        X = [0]*(n+1)
        Y = [0]*(n+1)
        for i in range(n):
            X[i],Y[i] = T[L[i]]
        X[n],Y[n] = T[L[0]]
        plt.plot(X, Y)

if len(sys.argv) == 2:

        nom = sys.argv[1]
        fichier = open(nom, "r")

        if fichier != None:

            contenu = fichier.read()
            fichier.close()
            contenu = contenu.split("\n")
            contenu = [l.split("\t") for l in contenu]

            d=int(contenu[0][0])
            n=int(contenu[0][1])
            del contenu[0]
            T = [[float(contenu[i][j]) for j in range(d)] for i in range(n)]
            a = int(contenu[n][0])
            del contenu[0:n+1]
            H = [[int(contenu[i][j]) for j in range(1,int(contenu[i][0])+1)] for i in range(a)]

            for L in H:
                tracerhyper2(L)

            plt.axis('equal')
            plt.show()

        else:
            print "Probleme a l'ouverture du fichier"
else:
    print 'Mettre nom du fichier'





