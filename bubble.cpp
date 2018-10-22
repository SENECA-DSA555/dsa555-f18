#include <cstdlib>
#include <iostream>
#include <fstream>
#include "timer.h"

using namespace std;
void bubbleSort(int arr[],int size){
  int tmp;                          /*used for swapping*/
  int i;
  int j;
  for (i=0; i<size-1; i++) {
    for (j=0; j<size-1-i; j++){
      if (arr[j+1] < arr[j]) {          /* compare the two neighbors */
        tmp = arr[j];                   /* swap a[j] and a[j+1]      */
        arr[j] = arr[j+1];
        arr[j+1] = tmp;
      }
    }
  }
}


int main(int argc, char* argv[]){
  int size=atoi(argv[1]);
  int *myarr=new int[size];
  Timer stopwatch;
  ofstream log("bubblelog.txt");
  for(int i=0;i<size;i++){
    myarr[i]=rand();
  }
  stopwatch.start();
  bubbleSort(myarr,size);
  stopwatch.stop();
  cout << stopwatch.currtime() << endl;
  /*for(int i=0;i<size;i++){
    log <<myarr[i]<< endl;
  }*/
  delete [] myarr;
  return 0;
}

