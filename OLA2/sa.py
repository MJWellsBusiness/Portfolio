#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#Matthew Wells
#OLA 2
#Due: October 8, 2021
#
#This is sa.py, which performs simulated annealing to find the maximum in SoG
import SumofGaussians as SG
import numpy as np, sys
import math

seed = int(sys.argv[1])
dims = int(sys.argv[2])
ncenters = int(sys.argv[3])

np.random.seed(seed)

sog = SG.SumofGaussians(dims,ncenters)

epsilon = 1e-8

#empty list of X dimensions and a corresponding Y array
dimArray = []
Y = []

#assigns each X value
for i in range(dims):
    X = 10 * np.random.ranf()
    Y.append(X)
    dimArray.append(X)

    T = 1-((i+1)/100000)
    
#this loop will iterate 100,000 times to find the greatest maximum
for i in range(100000):
    
    T = 1000/(i+1)

    for j in range(dims):
        print("%.8f"%(dimArray[j]), end = " ")
    
    print("%.8f"%(sog.Eval(dimArray)))
    
    for k in range(dims):
        Y[k] = dimArray[k] + np.random.uniform(-0.05,0.05)
    
    if (sog.Eval(Y)) > (sog.Eval(dimArray)):
        for k in range(dims):
            dimArray[k] = Y[k]
    else:
        probChoice = math.exp((sog.Eval(Y) - sog.Eval(dimArray))/T)
        randnum = np.random.random()
        if randnum < probChoice:
            dimArray[k] = Y[k]

    