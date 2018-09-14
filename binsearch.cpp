int binarySearch(int key, int array[], int size){
    int rc=-1;
    int low=0;
    int high=size-1;
    int mid;
    while(low<=high && rc==-1){
        mid=(low+high)/2;
        if(key < arr[mid])
            high=mid-1;
        else if(key > arr[mid] )
            low=mid+1;
        else
            rc=mid;
    }/*while*/
    return rc;
}
/*function returns index of where key is found in array, 
-1 if not found*/
int binarySearch(int key, int array[],int size){

}