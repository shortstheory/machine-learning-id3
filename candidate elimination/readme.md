# Candidate Elimination - BITS F464 Assigment 1

## Introduction

One of the most naive processes of finding out the hypothesis given a target concept is the process of Cabdidate elimination which gives the hypothesis which will be a conjunction of the attributes of the instance for which the target concept is to be applied. For this case there are 7 target concepts each dividing animals into a set of 7 classes, and with the one for all approach the general and specific boundaries of the version space are calculated.
The general boundary is updated for every negative training example, and removes the inconsistent hypothesis from the specific boundary. But it exits if the entire specific boundary is true for the negative training example, or when the general boundary is too general for the new test case and no minimum generalization which is less general than the specific boundary exists.
The specific boundary is updated for every positive training example, amd removes the inconsistent hypothesis from general. But it exits if the entire general boundary does not satisfy the test case or if the new specific boundary is more general than the general boundary.

## Compilation

In the working directory where the data.txt is present type:
```
g++ -std=c++11 main.cpp 
./a.out
```
c++11 is needed to support stoi function used in the code.

## Results

The execution time for the given data set is: 0.149 s.

It succeeds for classes: 1, 2, 4, 5, 6, and fails for: 3, 7.

It fails for 3 and 7 due to the exit case where the entire general boundary does not satisfy a positive test case.

For case 3 it is: slowworm,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,3

For case 7 it is: scorpion,0,0,0,0,0,0,1,0,0,1,1,0,8,1,0,0,7

The results for the others are:

Class: 1             

*****General boundary*****     

\<?,?,?,1,?,?,?,?,?,?,?,?,?,?,?,?\>  

*****Specific boundary*****       

\<?,0,?,1,?,?,?,?,1,1,0,?,?,?,?,?\>   

Class: 2                   

*****General boundary*****     

\<?,1,?,?,?,?,?,?,?,?,?,?,?,?,?,?\>   

*****Specific boundary*****        

\<0,1,1,0,?,?,?,0,1,1,0,0,2,1,?,?\>     

Class: 4                 

*****General boundary*****   

\<?,?,?,0,?,?,?,?,?,?,?,1,?,?,?,?\> \<?,?,1,?,?,?,?,?,?,?,?,1,?,?,?,?\> \<?,?,?,?,?,?,?,?,?,0,?,1,?,?,?,?\>      

*****Specific boundary*****                   

\<0,0,1,0,0,1,?,1,1,0,?,1,0,1,?,?\>        

Class: 5                      

*****General boundary*****     

\<0,?,?,?,?,1,?,1,?,?,?,0,4,?,?,?\>  

*****Specific boundary*****         

\<0,0,1,0,0,1,?,1,1,1,?,0,4,?,0,0\>      

Class: 6      

*****General boundary*****       

\<?,?,?,?,?,0,?,?,?,?,?,?,6,?,?,?\> \<?,?,?,?,?,?,?,?,?,1,?,?,6,?,?,?\>                               
*****Specific boundary*****      

\<?,0,1,0,?,0,?,0,0,1,?,0,6,0,?,0\>                                                                                   