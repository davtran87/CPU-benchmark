/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myBenchMark.cpp
 * Author: David Tran
 *
 * Created on February 14, 2017, 9:45 PM
 */


#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <stdio.h>
#include <ctime>

using namespace std;
int ARRAY_SIZE = 50000; //array_size for quick sort
int const MATRIX_SIZE = 340; // size for matrix inversion
int nInt;
int nFloat;
double sec(void);
void quickSort(unsigned int arr[], int left, int right); //quick sort function prototype.
void matrixInversion(double arr[][MATRIX_SIZE*2], double det); //matrix inversion function prototype.


int main(void) // Main function of program.
{
// Start and Initializing of variables
    double vInt, avgSpeed, qSortTime, mInvTime;
    double end, vFloat, start;
    double T[MATRIX_SIZE][MATRIX_SIZE*2],deter = 1.0;
    int left=0, right=ARRAY_SIZE; // set beginning and end of array.
    unsigned int Array[ARRAY_SIZE]; // initializing array for sort.
    srand(3);
    cout << "@@@BenchMark is currently running, results will be displayed soon...@@@\n";
    for(int i=0; i<(ARRAY_SIZE); i++)// populating array with integers from 0 to 100.
        Array[i] = rand()%100;
    nInt = 0;
    start = sec(); //start timing quicksort function.
    while( sec() < start+10.0)
    {
        for(int i=0; i<1000; i++)// too allow the function to run for 1 second.
            quickSort(Array, left, right); // call to quickSort function.
            
        nInt++;  
    }
    end = sec();
    qSortTime = end-start;
    vInt = (60*nInt)/(end-start);
    
    
    /*
     * Start of Matrix Inverse and Initialization.
     */

    
    for(int i=0; i<MATRIX_SIZE; i++)
    {
        for(int j=0; j<MATRIX_SIZE; j++)
        {
            if(i == j)
            {
                T[i][j] = 2.0001;
                T[i][MATRIX_SIZE+1+j] = 1.0;
            }
            else
            {
                T[i][j] = 1.0001;
                T[i][MATRIX_SIZE+1+j] = 0.0;
            }
        }

    }
        
        start = sec();
        nFloat = 0;
        while(sec() < start+10.0)
        {
            for(int i=0; i<16; i++) // used to allow function to run for 1 second
                matrixInversion(T, deter);
        
            nFloat++;
        }
       end = sec();
       mInvTime = end-start;
       cout << "Quick sort ran for this many second: " << qSortTime;
       cout << "\nnInt: " << nInt << "\nvInt: " << vInt;
       cout << "\nMatrix inversion ran for this many seconds seconds: " << mInvTime;
       vFloat = 60*nFloat/(end-start);
       cout << "\nnFloat: " << nFloat << "\nvFloat: " << vFloat;
        
        avgSpeed = 2*vFloat*vInt/(vFloat+vInt);
        cout << "\nThe average speed is: " << avgSpeed;
   
        int hi;
        cout << "\nPress any key then Enter to EXIT: ";
        cin >> hi; //easy fix to keep program running.
        
    return 0;
}



/*
 * Quicksort function that sorts an array of integers.
 * 
 * http://www.algolist.net/Algorithms/Sorting/Quicksort
 *
 * @param takes array of integers, left of the array and right of the array index.
 */
void quickSort(unsigned int arr[], int left, int right)
{
    int i=left, j=right; // i = beginning of array and j = end of array;
    unsigned int pivot = arr[(i+j)/2]; //computes the pivot to be middle index of array.
    int temp; 
    
    while(i<=j)
    {
        while(arr[i] < pivot)
            i++;
        while(arr[j] > pivot)
            j--;
        if(i<=j)
        {
            temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
            i++;
            j--;
        } 
    }
    if(left < j)
        quickSort(arr, left, j); //recurse function until finish sort.
    if(i < right)
        quickSort(arr, i, right);
}


/*
 * Matrix Inversion Function that inverses a matrix.
 * 
 * Function found in CSC 641 reader pg. 277 
 * 
 * @Param takes a 2d array that holds real numbers and the determinate.
 */
void matrixInversion(double arr[][MATRIX_SIZE*2], double det)
{


    double tik, tkk;

    for(int k=0; k<MATRIX_SIZE; k++)
    {
        tkk = arr[k][k]; 
        det *= tkk;

        for(int j=0; j<2*(MATRIX_SIZE+1); j++)
            arr[k][j] = arr[k][j]/tkk;
        for(int i=0; i<MATRIX_SIZE; i++)
            if(i != k)
            {

                tik = arr[i][k];
                for(int j=0; j<2*(MATRIX_SIZE+1); j++)
                    arr[i][j] = arr[i][j]-arr[k][j]*tik;

            }
    } 

}
/*Seconds function used to get current time in seconds*/
double sec(void)
{
    return double(clock()/CLOCKS_PER_SEC);
}