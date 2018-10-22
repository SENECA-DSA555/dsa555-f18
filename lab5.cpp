#include <cstdlib>
#include <iostream>
#include <fstream>
#include "timer.h"

using namespace std;

void insertionSort(int arr[],int left,int right){
    int curr;
    int i, j;
    for(i=left+1;i<=right;i++){
        curr=arr[i];
        for(j=i;j>0 && arr[j-1] > curr;j--){
            arr[j]=arr[j-1];
        }
        arr[j]=curr;
    }
}

//quicksort has been slightly modified to take threshold as an argument
//when size of partition is at or below threshold, insertion sort is done
void quickSort(int arr[], int left, int right, int threshold){
    if(right-left <= threshold){
        insertionSort(arr,left,right);
    }
    else{
        int i=left;
        int j=right-1;

        /* whatever you do to choose pivot, put the code here
           ensure pivot is at end of array (so if you choose middle)
           of array as pivot then swap it with arr[right]*/

        int pivot=arr[right];   //set pivot
        int pivotpt=right;   //NOTE: don't change this, pivot needs
                             //to be at end of array to be out of the way
                             //regardless of pivot picking method

        while(i<j){
            while(i< right-1 && arr[i]<pivot) i++;
            while(j > 0 && arr[j]>pivot) j--;
            if(i<j)
                swap(arr[i++],arr[j--]);
        }
        if(i==j && arr[i] < arr[pivotpt])
        i++;
        swap(arr[i],arr[pivotpt]);
        quickSort(arr,left,i-1,threshold);
        quickSort(arr,i+1,right,threshold);
    }
}

//non-recursive interface to quicksort, real work
//done in recursive version.
void quickSort(int arr[],int size,int threshold=3){
    quickSort(arr,0,size-1,threshold);
}

/*This function is passed an empty array of size elements
it will fill the array with random numbers*/
void generateRandom(int array[],int size){
    for(int i=0;i<size;i++){
        array[i]=rand();
    }
}

/*This function is passed an empty array with sz elements. It will 
fill this array with numbers where the numbers are ordered is ordered 
from big to small. Note that the values in here need not be random 
only that it goes from biggest to smallest*/
void generateReverse(int array[],int size){

}


/*This function is passed an empty array with size elements. 
This function generate 20 random numbers. Each element of the
array will get one of these 20 numbers.*/
void generateManyDuplicates(int array[],int size){

}

/*This function is passed an empty array with size elements. 
This function generates a nearly sorted array (small to big). 
This can be done by creating a sorted array(doesn't have to be
random numbers...just small to big) and then randomly
performing a small number of swaps on the array. The small
number can be based on percentage of size around 5%. Thus if
 sz was 100, you would do 5 swaps (making around 10 numbers 
 out of place, leaving 90 sorted)*/

void generateNearlySorted(int array[],int size){

}

int main(int argc, char* argv[]){
    int size=atoi(argv[1]);
    int* myarr=new int[size];
    Timer stopwatch;
    ofstream log("quick.log");
    generateRandom(myarr,size);
    stopwatch.start();
    quickSort(myarr,size,3);
    stopwatch.stop();
    cout << stopwatch.currtime() << endl;
    for(int i=0;i<size;i++){
        log << myarr[i]<< endl;
    }
    return 0;
}

