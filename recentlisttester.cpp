/*********************************************************************/
/*                                                                   */
/* Tester for assignment 1, part 2                                   */
/* Version 1.0                                                       */
/* To compile:                                                       */
/*                                                                   */
/*                                                                   */
/*      g++ a1q1main.cpp -std=c++0x                                  */
/*                                                                   */
/*********************************************************************/

#include "recentlist.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
//change the #define VERBOSE to 1 for a bit more error information
#define VERBOSE 1

struct Record{
    char word_[30];
    int count_;
};
ostream& operator<<(ostream& os, const Record rec){
    os << rec.word_;
    return os;
}
bool operator==(const Record& a,const Record& b){
    bool rc=false;
    if(strcmp(a.word_,b.word_)==0 && a.count_==b.count_){
        rc=true;
    }
    return rc;
}
bool operator!=(const Record& a,const Record& b){
    return !(a==b);
}
bool operator <(const Record& a, const Record& b){
    bool rc=false;
    if(strcmp(a.word_,b.word_) < 0){
        rc=true;
    }
    return rc;
}

template <typename T>
void removeItem(T arr[],int idx,int sz);
template <typename T>
bool checkList(const RecentList<T>& list,const T arr2[],int sz);
template <typename T>
void duplicateArray(T dest[], const T src[],int sz);
template <typename T>
void printLists(const RecentList<T>& list,const T array[],int sz);
template<typename T>
typename RecentList<T>::iterator setIterator(RecentList<T>& list, int idx);
template <typename T>
void addFront(const T& data,T arr[],int sz);
template <typename T>
void addBack(const T& data,T arr[],int sz);
template <typename T>
void add(const T& data,int idx, T arr[],int sz);
template <typename T>
void moveItem(T arr[],int fromIdx, int toIdx, int sz);


int main(void){
    const int cap=10000;
    const int numSearches=200;
    Record data[20]={
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };
    //used for adjusting list for searching test
    int searchParams[30][2]={
        {19,0},
        {19,0},
        {19,0},
        {19,0},
        {19,0},
        {19,0},
        {19,0},
        {0,0},
        {1,0},
        {2,0},

        {3,0},
        {4,0},
        {5,0},
        {8,0},
        {7,0},
        {6,0},
        {5,0},
        {4,0},
        {3,0},
        {2,0},

        {1,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {10,0},
        {11,0},
        {9,0},
        {18,0},
        {19,0}

    };
    int intData[cap];

//these array will mirror what happens to LL
    Record mirror[20];
    Record tmp[20];
    int intMirror[cap];
    for(int i=0;i<cap;i++){
        intData[cap-1-i]=rand();
        intMirror[cap-1-i]=intData[cap-1-i];
    }

    RecentList<Record> recList;
    RecentList<int> intList;

    bool passtest=true;
    int numPassed=0;



/* Test constructors, begin and end functions*/
    cout << "test 1: create list empty list, check begin() and end()" << endl;
    if((recList.begin() != recList.end()) || (intList.begin() != intList.end()) || 
        (recList.cbegin() != recList.cend()) || (intList.cbegin() != intList.cend())){
        cout << "error 1: check your constructor, begin()/end(), cbegin()/cend() functions" << endl;
        passtest=false;
    }
    else{
        numPassed++;
    }

    if(passtest){
        for(int i=0;i<20;i++){
            addBack(data[i],mirror,i);
            recList.insert(data[i]);
        }
        for(int i=0;i<cap;i++){
            intList.insert(intData[i]);
        }
        cout << "test 2: create list, insert some records." << endl;
        if(recList.size() != 20 || intList.size() != cap || recList.empty() || intList.empty()){
            passtest=false;
            cout << "Error 2a: Bug is likely to be in: constructor, size() or empty() insert() or iterator (operator++(int) or operator*)"<< endl;
        }	
        if(!checkList(recList,mirror,20)){
            passtest=false;
            cout << "Error 2b: Bug is likely to be in: constructor, insert() or iterator (operator++(int) or operator*)"<< endl;
            #if VERBOSE >= 1
            printLists(recList,mirror,20);
            #endif
        }
        if(!checkList(intList,intMirror,cap)){
            passtest=false;
            cout << "Error 2c: Bug is likely to be in: constructor, insert() or iterator (operator++(int) or operator*)"<< endl;
            #if VERBOSE > 1
            printLists(intList,intMirror,cap);
            #endif
        }
    }
    if(passtest){
        numPassed++;
        cout << "test 3: check const_iterator ++ and -- operators"  << endl;
        RecentList<Record>::const_iterator it=recList.cbegin();
        for(int i=0;i<20 && passtest;i++){
            if(mirror[i] != *(it++)){
                passtest=false;
                cout << "Error 3a: postfix ++ operator is not returning iterator to correct node" << endl;
            }
        }
        if(passtest && it!=recList.cend()){
            passtest=false;
            cout << "Error 3b: postfix ++ operator did not advance iterator pass last data" << endl;
        }
        //puts iterator back to last data, should return cend()
        if(passtest && (it--) != recList.cend()){
            passtest=false;
            cout << "Error 3c: postfix -- operator did not return iterator to correct node" << endl;
        }
        if(passtest && it == recList.cend()){
            passtest=false;
            cout << "Error 3d: postfix -- operator iterator did not move to last data from cend()" << endl;
        }
        for(int i=19;i>0 && passtest;i--){
            if(mirror[i] != *(it--)){
                passtest=false;
                cout << "Error 3e: postfix -- operator is not returning iterator to correct node" << endl;
            }
        }
        for(int i=0;i<19 && passtest;i++){
            if(*(++it) != mirror[i+1]){
                passtest=false;
                cout << "Error 3f: prefix ++ operator is not returning iterator to correct node" << endl;
            }
        }
        if(passtest && (++it) != recList.cend()){
            passtest=false;
            cout << "Error 3g: prefix ++ operator did not return cend() when advancing from last node" << endl;
        }
        if(passtest && it!=recList.cend()){
            passtest=false;
            cout << "Error 3h: prefix ++ operator did not advance iterator pass last data" << endl;
        }
        //puts iterator back to last data, should return cend()
        if(passtest && *(--it) != mirror[19]){
            passtest=false;
            cout << "Error 3i: prefix -- operator did not return iterator to correct node" << endl;
        }
        if(passtest && it == recList.cend()){
            passtest=false;
            cout << "Error 3j: prefix -- operator iterator did not move to last data from cend()" << endl;
        }
        for(int i=19;i>0 && passtest;i--){
            if(*(--it) != mirror[i-1]){
                passtest=false;
                cout << "Error 3k: prefix -- operator is not returning iterator to correct node" << endl;
            }
        }
    }

    if(passtest){
        numPassed++;
        cout << "test 4: check iterator ++ and -- operators"  << endl;
        RecentList<Record>::iterator it=recList.begin();
        for(int i=0;i<20 && passtest;i++){
            if(mirror[i] != *(it++)){
                passtest=false;
                cout << "Error 4a: postfix ++ operator is not returning iterator to correct node" << endl;
            }
        }
        if(passtest && it!=recList.end()){
            passtest=false;
            cout << "Error 4b: postfix ++ operator did not advance iterator pass last data" << endl;
        }
        //puts iterator back to last data, should return end()
        if(passtest && (it--) != recList.end()){
            passtest=false;
            cout << "Error 4c: postfix -- operator did not return iterator to correct node" << endl;
        }
        if(passtest && it == recList.end()){
            passtest=false;
            cout << "Error 4d: postfix -- operator iterator did not move to last data from end()" << endl;
        }
        for(int i=19;i>0 && passtest;i--){
            if(mirror[i] != *(it--)){
                passtest=false;
                cout << "Error 4e: postfix -- operator is not returning iterator to correct node" << endl;
            }
        }
        for(int i=0;i<19 && passtest;i++){
            if(*(++it) != mirror[i+1]){
                passtest=false;
                cout << "Error 4f: prefix ++ operator is not returning iterator to correct node" << endl;
            }
        }
        if(passtest && (++it) != recList.end()){
            passtest=false;
            cout << "Error 4g: prefix ++ operator did not return end() when advancing from last node" << endl;
        }
        if(passtest && it!=recList.end()){
            passtest=false;
            cout << "Error 4h: prefix ++ operator did not advance iterator pass last data" << endl;
        }
        //puts iterator back to last data, should return end()
        if(passtest && *(--it) != mirror[19]){
            passtest=false;
            cout << "Error 4i: prefix -- operator did not return iterator to correct node" << endl;
        }
        if(passtest && it == recList.end()){
            passtest=false;
            cout << "Error 4j: prefix -- operator iterator did not move to last data from end()" << endl;
        }
        for(int i=19;i>0 && passtest;i--){
            if(*(--it) != mirror[i-1]){
                passtest=false;
                cout << "Error 4k: prefix -- operator is not returning iterator to correct node" << endl;
            }
        }
    }
      

    RecentList<Record> recCopy=recList;
    RecentList<int> intCopy=intList;               //copy constructor calls
    RecentList<Record> recCopy2=recCopy;
    RecentList<int> intCopy2=intCopy;

    duplicateArray(data,mirror,20);              //ensure that data and mirror hold same data
    duplicateArray(intData,intMirror,cap);

    if(passtest){
        numPassed++;
        cout << "test 5: create a duplicate of the lists with copy constructor, ensure they match" << endl;
        if(!checkList(recCopy,mirror,20) || !checkList(recCopy2,mirror,20) || recCopy.size()!=20 || recCopy2.size() != 20 || recCopy.empty() || recCopy2.empty()){
            passtest=false;
            cout << "Error 5a: Bug in copy constructor, either your rhs or current object does not contain the correct data"  << endl;  		
            #if VERBOSE >= 1
            printLists(recCopy,mirror,20);
            #endif
        }
        if(!checkList(intCopy,intMirror,cap) || !checkList(intCopy2,intMirror,cap) || intCopy.size()!=cap ||intCopy2.size()!=cap || recCopy.empty() || recCopy2.empty()){
            passtest=false;
            cout << "Error 5b: Bug in copy constructor" << endl;
            #if VERBOSE > 1
            printLists(intList,intMirror,cap);
            #endif
        }
    }
    if(passtest){
        numPassed++;
        cout << "test 6: test search() function" << endl;
        for(int i=0;i<20;i++){
            RecentList<Record>::iterator it = recList.search(data[i]);
            moveItem(mirror,i,0,20);
            if(it == recList.end() || *it != data[i]){
                passtest=false;
                cout << "Error 6a: Bug in search, returned iterator returned does not point at correct node" << endl;
                #if VERBOSE >= 1
                if(it == recList.end()){
                    cout << "your function returned end() but iterator to node with " << mirror[i] << " should have been returned" << endl;
                }
                else{
                    cout << "your function returned " << *it  << " but it should have been iterator to node with " << mirror[i] << " should have been returned" << endl;
                }
                #endif
            }
            if(!checkList(recList,mirror,20)){
                passtest = false;
                cout << "Error 6b: Bug in search(), your list was not properly adjusted" << endl;
                #if VERBOSE >= 1
                printLists(recList,mirror,20);
                #endif
            }
        }
        for(int i=0;i<30;i++){
            RecentList<Record>::iterator it = recList.search(mirror[searchParams[i][0]]);
            moveItem(mirror,searchParams[i][0],searchParams[i][1],20);
            if(it == recList.end() || *it != mirror[searchParams[i][1]]){
                passtest=false;
                cout << "Error 6c: Bug in search, returned iterator returned does not point at correct node" << endl;
                #if VERBOSE >= 1
                if(it == recList.end()){
                    cout << "your function returned end() but iterator to node with " << mirror[searchParams[i][1]] << " should have been returned" << endl;
                }
                else{
                    cout << "your function returned " << *it  << " but it should have been iterator to node with " << mirror[searchParams[i][1]] << " should have been returned" << endl;
                }
                #endif
            }
            if(!checkList(recList,mirror,20)){
                passtest = false;
                cout << i << endl;
                cout << "Error 6d: Bug in search(), your list was not properly adjusted" << endl;
                cout << "search key was: " << mirror[searchParams[i][1]] << endl;
                #if VERBOSE >= 1
                printLists(recList,mirror,20);
                #endif
            }            

        }
    }
    duplicateArray(tmp,mirror,20);
    if(passtest){
        numPassed++;
        cout << "test 7: test erase function"  << endl;
        RecentList<Record>::iterator it;
        it=setIterator(recList,19);
        recList.erase(it);
        removeItem(mirror,19,20);
        if(!checkList(recList,mirror,19)){
            passtest=false;
            cout << "Error 7a: Bug in erase.  something went wrong when erasing last item from list" << endl;
            #if VERBOSE >= 1
            printLists(recList,mirror,19);
            #endif
        }
        recList.erase(recList.begin());
        removeItem(mirror,0,19);
        if(!checkList(recList,mirror,18)){
            passtest=false;
            cout << "Error 7b: Bug in erase. something went wrong when erasing first item from list" << endl;
            #if VERBOSE >= 1
            printLists(recList,mirror,18);
            #endif
        }
        for(int i=0;i<3 && passtest;i++){
            int pick=rand()%(18-i);
            it=setIterator(recList,pick);
            recList.erase(it);
            removeItem(mirror,pick,18-i);
            if(!checkList(recList,mirror,18-i-1)){
                passtest=false;
                cout << "Error 7c:  Bug in erase." << endl;
            }
        }
        intList.erase(intList.begin());
        removeItem(intMirror,0,cap);
        if(!checkList(intList,intMirror,cap-1)){
            passtest=false;
            cout << "Error 7d: Bug in erase, something went wrong when erasing first item from list" << endl;
        }
        intList.erase(intList.begin());
        removeItem(intMirror,0,cap-1);
        if(!checkList(intList,intMirror,cap-2)){
            passtest=false;
            cout << "Error 7e: Bug in erase. something went wrong when erasing first item from list a second time" << endl;
        }
        RecentList<int>::iterator it2;
        it2=setIterator(intList,cap-3);
        intList.erase(it2);
        removeItem(intMirror,cap-3,cap-2);
        if(!checkList(intList,intMirror,cap-3)){
            passtest=false;
            cout << "Error 7f: Bug in erase.  something went wrong when erasing last item from list" << endl;
        }
        it2=setIterator(intList,cap-4);
        intList.erase(it2);
        removeItem(intMirror,cap-4,cap-3);
        if(!checkList(intList,intMirror,cap-4)){
            passtest=false;
            cout << "Error 7g: Bug in erase. something went wrong when erasing last item from list a second time" << endl;
        }
        #if VERBOSE > 1
        if(!passtest){
            printLists(intList,intMirror,cap-4);
        }
        #endif
        for(int i=0;i<100 && passtest;i++){
            int pick=rand()%(cap-4-i);
            it2=setIterator(intList,pick);
            intList.erase(it2);
            removeItem(intMirror,pick,cap-4-i);
            if(!checkList(intList,intMirror,cap-i-5)){
                passtest=false;
                cout << "Error 7h:  Bug in erase." << endl;
                #if VERBOSE > 1
                printLists(intList,intMirror,cap-i-5);
                #endif
            }
        }
    }
    if(passtest){
        numPassed++;
        cout << "test 8: ensure that copied list were not altered (proper deep copy was made) " << endl;
        if(!checkList(recCopy,data,20) || !checkList(recCopy2,data,20)){
            passtest=false;
            cout << "Error 8a: Bug in copy constructor"  << endl;
            #if VERBOSE >= 1
            printLists(recCopy,data,20);
            #endif
        }
        if(!checkList(intCopy,intData,cap) || !checkList(intCopy2,intData,cap)){
            passtest=false;
            cout << "Error 8b: Bug in copy constructor" << endl;
            #if VERBOSE >= 2
            printLists(intCopy,intData,cap);
            #endif
        }
    }
    if(passtest){
        numPassed++;
        cout << "test 9: test assignment operator"  << endl;
        recCopy2 = recList;
        intCopy2 = intList;
        if(!checkList(recCopy2,mirror,15) || recCopy2.size() != 15){
            passtest=false;
            cout << "Error 9a: Bug in assignment operator, copy doesn't match or size is wrong"  << endl;  		
            #if VERBOSE >= 1
            printLists(recCopy2,mirror,15);
            #endif
        }
        if(!checkList(intCopy2, intMirror,cap-104) || intCopy2.size() != (cap-104)){
            passtest=false;
            cout << "Error 9b: Bug in assignment operator, copy doesn't match or size is wrong"  << endl;  		
            #if VERBOSE >= 2
            printLists(intCopy2,intMirror,cap-104);
            #endif
        }
    }

    if(passtest){

        numPassed++;

        cout << "test 10: test assignment operator (deep copy)"  << endl;
        recCopy2.erase(recCopy2.begin());
        intCopy2.erase(intCopy2.begin());
        if(!checkList(recList,mirror,15)|| recList.empty() || recList.size()!=15){
            passtest=false;
            cout << "Error 10a: Bug in = operator, original list was modified when copy was altered"  << endl;
        }
        if(!checkList(intList,intMirror,cap-104)|| intList.empty() || intList.size()!=cap-104){
            passtest=false;
            cout << "Error 10b: Bug in = operator, original list was modified when copy was altered"  << endl;     
        }
    }

    if(passtest){
        numPassed++;
        cout << "test 11: search for removed items" << endl;
        int pick[2]={0,19};
        for(int i=0;i<2;i++){
            auto it =recList.search(tmp[pick[i]]);
            if(it!=recList.end()){
                cout << "Error 11a: Bug in search, returned iterator is not correct.  search should have returned end()" << endl;
                passtest=false;
            }
        }

    }
    if(passtest){
        int pick[4]={0,1,cap-1,cap-2};
        for(int i=0;i<4;i++){
            auto it = intList.search(intData[pick[i]]);
            if(it != intList.end()){
                passtest=false;
                cout << "Error 11b: Bug in search, returned iterator is not correct.  search should have returned end()"<< endl;
            }
        }
    }
    if(passtest){
        numPassed++;
        cout << "test 12: test erase(a,b) function"  << endl;
        RecentList<Record>::iterator it;
        RecentList<Record>::iterator it2;
  
        duplicateArray(tmp,mirror,15);
        removeItem(tmp,0,15);
        it=setIterator(recCopy2,2);
        it2=setIterator(recCopy2,5);

        recCopy2.erase(it,it2);
        removeItem(tmp,4,14);
        removeItem(tmp,3,13);  
        removeItem(tmp,2,12);
        if(!checkList(recCopy2,tmp,11)){
            passtest=false;
            cout << "Error 12a: Bug erase(it) function"  << endl;  		
            #if VERBOSE >= 1
            printLists(recCopy2,tmp,11);
            #endif
        }
        if(!checkList(recList,mirror,15)){
            passtest=false;
            cout << "Error 12b: assignment operator"  << endl;  		
            #if VERBOSE >= 1
            printLists(recList,mirror,15);
            #endif

        }
    }
    if(passtest){
        numPassed++;
        cout << "test 13: test erase(it,end()) function"  << endl;
        RecentList<Record>::iterator it;
        RecentList<Record>::iterator it2;
        recCopy2=recList;
        duplicateArray(tmp,mirror,15);
        it=setIterator(recCopy2,11);

        recCopy2.erase(it,recCopy2.end());
        removeItem(tmp,14,15);
        removeItem(tmp,13,14);  
        removeItem(tmp,12,13);
        removeItem(tmp,11,12);
        if(!checkList(recCopy2,tmp,11)){
            passtest=false;
            cout << "Error 13a: Bug erase(it,end()) function"  << endl;  		
            #if VERBOSE >= 1
            printLists(recCopy2,tmp,11);
            #endif
        }
        if(!checkList(recList,mirror,15)){
            passtest=false;
            cout << "Error 13b: assignment operator, (deep copy not made?)"  << endl;  		
            #if VERBOSE >= 1
            printLists(recList,mirror,15);
            #endif

        }
    }

    RecentList<Record> recCopy3=std::move(recList);
    if(passtest){
        numPassed++;
        cout << "test 14: test move constructor"  << endl;

        if(!checkList(recCopy3,mirror,15) || recCopy3.size() != 15){
            passtest=false;
            cout << "Error 14a: Bug in move constructor"  << endl;  		
            #if VERBOSE >= 1
            printLists(recCopy3,mirror,15);
            #endif
        }
    }

    if(passtest){
        numPassed++;
        RecentList<Record> recCopy4;
        recCopy4.insert(mirror[0]);
        recCopy4.insert(mirror[1]);
        cout << "test 15: test move assignment operator"  << endl;
        recCopy4=std::move(recCopy3);
        if(!checkList(recCopy4,mirror,15)){
            passtest=false;
            cout << "Error 15a: Bug in move assignment operator"  << endl;  		
            #if VERBOSE >= 1
            printLists(recCopy4,mirror,15);
            #endif
        }

    }


    if(passtest){
        numPassed++;
    }
    if(numPassed == 15){
        cout << "Testing for Assignment 1, part 2 completed successfully" << endl;
        cout << "15/15 tests passed" << endl;
    }
    else{
        cout << numPassed << " / 15 tests passed.  Looks like you still" << endl;
        cout << "have some work to do" << endl;
    }
    return 0;
}
template <typename T>
void addFront(const T& data,T arr[],int sz){
    add(data,0,arr,sz);
}
template <typename T>
void addBack(const T& data,T arr[],int sz){
    arr[sz]=data;
}
template <typename T>
void add(const T& data,int idx, T arr[],int sz){
    for(int i=sz-1;i>=idx;i--){
        arr[i+1]=arr[i];
    }
    arr[idx]=data;
}
template <typename T>
void removeItem(T arr[],int idx,int sz){
    for(int i=idx;i<sz-1;i++){
        arr[i]=arr[i+1];
    }
}
template <typename T>
bool checkList(const RecentList<T>& list,const T array[],int sz){
    bool rc=true;
    if(sz != list.size()){
        rc=false;
    }
    else{
        auto it=list.cbegin();
        int i;
        for(i=0;i<sz && it!=list.cend() && rc;i++,it++){
            if(*it != array[i]){
                rc=false;
            }
        }
        if(it!=list.cend() || i < sz){
            rc=false;
        }
    }
    return rc;
}

template <typename T>
void duplicateArray(T dest[], const T src[],int sz){
    for(int i=0;i<sz;i++){
        dest[i]=src[i];
    }
}

template <typename T>
void printLists(const RecentList<T>& list,const T array[],int sz){
    auto it=list.cbegin();
    int i;
    for(i=0;i<sz && it!=list.cend();i++,it++){
        cout << "correct item: " ;
        cout.width(25);
        cout.setf(ios::left);
        cout << array[i] << "  your list: " << *it << endl;
    }
    for( ;i<sz;i++){
        cout << "correct item: ";
        cout.width(20);
        cout.setf(ios::left);
        cout << array[i] << "  your list: <past end of list>" <<  endl;
    }	
    for( ;it!=list.cend();it++){
        cout << "correct item: ";
        cout.width(20);
        cout.setf(ios::left);
        cout << "<past end of list>"  << "  your list: " <<  *it << endl;
    }
    cout << endl;

}
//returns iterator to the idx'th node in the list
template <typename T>
typename RecentList<T>::iterator setIterator(RecentList<T>& list, int idx){
    typename RecentList<T>::iterator it=list.begin();
    for(int i=0;i<idx;i++){
        it++;
    }
    return it;
}


template <typename T>
void moveItem(T arr[],int fromIdx, int toIdx, int sz){
    T tmp=arr[fromIdx];
    removeItem(arr,fromIdx,sz);
    add(tmp,toIdx,arr,sz-1);

}




