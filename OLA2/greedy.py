#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#Matthew Wells
#OLA 2
#Due: October 8, 2021
#
#This is greedy.py, which performs greedy local search to find the local maximum of a hill in SoG
import SumofGaussians as SG
import numpy as np, sys

seed = int(sys.argv[1])
dims = int(sys.argv[2])
ncenters = int(sys.argv[3])

np.random.seed(seed)

sog = SG.SumofGaussians(dims,ncenters)

epsilon = 1e-8

#empty list of X dimensions
dimArray = []

#flag to know when to stop iterating
stop = False

#assigns each X value
for i in range(dims):
    X = 10 * np.random.ranf()
    dimArray.append(X)

#this loop will iterate 100,000 times or until stop is true (when the change to SoG is less than the threshold)
for i in range(100000):
    
    if stop == True:
        break
    
    for j in range(dims):
        print("%.8f"%(dimArray[j]), end = " ")
    
    print("%.8f"%(sog.Eval(dimArray)))
    
    #this stores the value of SOG at the previous point
    SOGPrev = sog.Eval(dimArray)
    
    for k in range(dims):
        
        #this updates the loop and then checks for the threshold with the new value
        X = dimArray[k] + (.01 * sog.Deriv(dimArray[k]))[k]
    
        dimArray[k] = X
        
        if(sog.Eval(dimArray) - SOGPrev) < epsilon:
            stop = True
            break 

