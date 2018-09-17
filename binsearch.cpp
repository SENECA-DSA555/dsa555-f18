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
    int rc;
    if(size == 0){
        rc = -1;
    }
    else{
        int mid = size/2;       
        if(key == array[mid]){
            rc = mid;
        }
        else if(key < array[mid]){
            rc = binarySearch(key, array, mid);
        }
        else{  //key > array[mid]
            rc = binarySearch(key,&(array[mid+1]),size-mid-1);
            if(rc != -1){
                rc += (mid+1);
            }
        }
    }
    return rc;
}

int binarySearch(int key, int array[],int size){
    return binarySearch(key,array,0,size-1);
}
/*this function returns the location of key in the array
between index low and high.  -1 if not found*/
int binarySearch(int key, int array[],int low,int high){
    int rc;
    if(low > high){
        rc=-1;
    }
    else{
        mid = (low + high)/2;
        if(key == array[mid]){
            rc=mid;
        }
        else if (key < array[mid]){
            rc=binarySearch(key,array,low,mid-1)
        }
        else{
            rc=binarySearch(key,array,mid+1,high);
        }
    }
    return rc;
}






