/*********************************************************/
/*                                                       */
/*   Written by: Catherine Leung                         */
/*   Version 1.0                                         */
/*                                                       */
/*   A reminder that all template code must be placed in */
/*   header file. You will have trouble compiling and    */
/*   linking otherwise.                                  */
/*                                                       */
/*   This program uses a text file with a list of        */
/*   words and creates the tables using the words as     */
/*   keys.                                               */
/*   You will need the file: dictionary.txt (in repo)    */
/*                                                       */
/*                                                       */
/*   To compile this program:                            */
/*          g++ a2tester.cpp timer.cpp -std=c++0x        */
/*                                                       */
/*********************************************************/

#include "table.h"
#include "timer.h"
#include <string>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>


using namespace std;
const int NUMTESTS=13;
const int MAX=200000;

const char* filename="dictionary.txt";

//A struct to simplify error recording process.
struct Error{
    char msg_[150];
    int passed_;
    Error(const char* msg, int p){
        strcpy(msg_,msg);
        passed_=p;
    }
    void set(const char* msg, int p){
        strcpy(msg_,msg);
        passed_=p;
    }
};


void cleanWordList(char* wordlist[]);
void setData(int data[],int sz);
void printTiming(double timing[],int numrec, int numover);

int main(int argc, char* argv[]){

    FILE* fp=fopen(filename,"r");

    int testnumber=0;
    if(!fp){
        cout << "could not open file " << filename << ".  Make sure it is in the" << endl;
        cout << "same directory as this program and try again" << endl;
        return 0;
    }
    char curr[50];          //used to read in words from text file
    string* wordlist;        //list of test cases. 

    bool oprc;              //return value from an operation

    int reccount;     //the count value in the record.  the ones that were removed and added should 
                      //be 1 the ones that were never removed should be 2

    int numremoved=0;   //number of words removed from the table;

    int* data;
    int currValue;
    Timer t;
    double timing[10];
    try{
        data=new int[MAX];
        wordlist= new string[MAX];
        for(int i=0;i<MAX;i++){
            fscanf(fp,"%s\n",curr);                 //read in a word from data file
            wordlist[i]=curr;                       //record it
         }/*end for:  populate table*/
        setData(data,MAX);

        cout << "* * * * * * * * * * * * Testing HashTable Table* * * * * * * * * * * * * * * *"<< endl;
        cout << "Test 1: initialization and update" << endl;
        int hashtableCapacity=MAX;
        bool expandHash=true;
        double lambda = 0.65;
        int hashtableMax = hashtableCapacity*lambda;
        LPTable<int> hashtable(hashtableCapacity,lambda);
        Timer t2;
        double hashTiming[10];


        t2.reset();
        for(int i=0;i<hashtableMax;i++){
            t2.start();
            oprc=hashtable.update(wordlist[i],data[i]);             
            t2.stop();
            if(!oprc){                              //check return code (should be true)
                throw Error("hashtabletable::update is returning false when table is not full",testnumber);
            }
        }/*end for:  populate table*/
        hashTiming[0]=t2.currtime();
        testnumber++;

        cout << "Test 2: Add some more records (more than table can hold)" << endl;
        t2.reset();
        for(int i=0;i<MAX-hashtableMax;i++){
            t2.start();
            oprc=hashtable.update(wordlist[hashtableMax+i],data[hashtableMax+i]);              
            t2.stop();
            if(oprc){                             
                throw Error("hashtabletable::update is returning true when table is full.",testnumber);
            }
        }/*end*/
        hashTiming[1]=t2.currtime();
        testnumber++;


        cout << "Test 3: Checking hashtableTable::find() and that records were properly recorded..." << endl;
        t2.reset();
        for(int i=0;i<hashtableMax;i++){
            int currValue;
            t2.start();
            oprc=hashtable.find(wordlist[i],currValue);                
            t2.stop();
            if(!oprc){                                          //check return code (should be true)
                throw Error("hashtable::find is returning false for a word that should be in the table",testnumber);
            }
            if(currValue!=data[i]){
                cout << "search key:" << wordlist[i] << endl;
                cout << "correct value: "<< data[i] << endl;
                cout << "your record's value: " << currValue << endl;
                throw Error("hashtable::find is not passing back the correct data",testnumber);
            }
        }
        hashTiming[2]=t2.currtime();
        testnumber++;


        cout << "Test 4: Change some records in hashtable table and see if it still works" << endl;
        t2.reset();
        for(int i=0;i<hashtableMax;i++){
            data[i]+=1;                                              //modify the data (but key is same)
            t2.start();
            oprc=hashtable.update(wordlist[i],data[i]);                          //put it back in the table
            t2.stop();
            if(!oprc){
                throw Error("hashtable::update is returning false for updating an existing record",testnumber);
            }
        }
        hashTiming[3]=t2.currtime();
        testnumber++;

        cout << "Test 5: Checking hashtable::find() and whether or not records were properly updated..." << endl;
        t2.reset();
        for(int i=0;i<hashtableMax;i++){
            t2.start();
            oprc=hashtable.find(wordlist[i],currValue);                //search the linear probing table
            t2.stop();
            if(!oprc){                                          //check return code (should be true)
                throw Error("hashtable::find is returning false for a word that should be in the table",testnumber);
            }
            if(data[i]!=currValue){
                cout << "search key:" << wordlist[i] << endl;
                cout << "correct value: "<< data[i] << endl;
                cout << "your record's value: " << currValue << endl;
                throw Error("hashtable::find is not passing back the correct data",testnumber);
            }
        }
        hashTiming[2]+=t2.currtime();
        testnumber++;

        cout << "Test 6: Create a table using copy constructor" << endl;
        t2.reset();
        t2.start();
        LPTable<int> hashtableCopy=hashtable;
        t2.stop();
        hashTiming[4]=t2.currtime();
        t2.reset();
        for(int i=0;i<hashtableMax;i++){
            t2.start();
            oprc=hashtableCopy.find(wordlist[i],currValue);                //search the linear probing table
            t2.stop();
            if(!oprc){                                          //check return code (should be true)
                throw Error("hashtableCopy.find is returning false for a word that should be in the table",testnumber);
            }
            if(data[i]!=currValue){
                cout << "search key:" << wordlist[i] << endl;
                cout << "correct value: "<< data[i] << endl;
                cout << "your record's value: " << currValue << endl;
                throw Error("hashtableCopy.find is not passing back the correct data",testnumber);
            }
        }
        hashTiming[2]+=t2.currtime();
        testnumber++;


        cout << "Test 7: Remove some records that exist from hashtable table..." << endl;
        numremoved=0;
        t2.reset();
        for(int i=0;i<hashtableMax;i+=10){
            t2.start();
            oprc=hashtable.remove(wordlist[i]);                          //put it back in the table
            t2.stop();
            numremoved++;
            if(!oprc){
                throw Error("hashtable::remove is returning false for removing an existing record",testnumber);
            }
        }
        hashTiming[5]=t2.currtime();
        testnumber++;


        cout << "Test 8: Check that removed records are gone and others are unaffected in hashtable table..." << endl;
        t2.reset();
        for(int i=0;i<hashtableMax;i++){
            t2.start();
            oprc=hashtable.find(wordlist[i],currValue);                          //put it back in the table
            t2.stop();
            if(i%10){
                if(!oprc){
                    throw Error("hashtable::find() could not find record that was not removed",testnumber);
                }
                if(data[i]!=currValue){
                    cout << "search key:" << wordlist[i] << endl;
                    cout << "correct value: "<< data[i] << endl;
                    cout << "your record's value: " << currValue << endl;
                    throw Error("hashtable::find is not passing back the correct data",testnumber);
                } 
            }
            else{
                if(oprc){
                    throw Error("hashtable::find() found a record that was removed",testnumber);
                }
            }
        }
        hashTiming[2]+=t2.currtime();
        testnumber++;

        cout << "Test 9: Attempt to remove some records that do not exist from the table" << endl;
        t2.reset();
        for(int i=0;i<hashtableMax;i+=10){
            t2.start();
            oprc=hashtable.remove(wordlist[i]);                          //put it back in the table
            t2.stop();
            if(oprc){
                throw Error("hashtable::remove is returning true for removing non-existing record",testnumber);
            }
        }
        hashTiming[6]=t2.currtime();
        testnumber++;


        cout << "Test 10: Checking hashtableCopy to see that it was unaffected by removing from hashtable" << endl;
        t2.reset();
        for(int i=0;i<hashtableMax;i++){
            t2.start();
            oprc=hashtableCopy.find(wordlist[i],currValue);                //search the linear probing table
            t2.stop();
            if(!oprc){                                          //check return code (should be true)
                throw Error("hashtableCopy.find is returning false for a word that should be in the table",testnumber);
            }
            if(data[i]!=currValue){
                cout << "search key:" << wordlist[i] << endl;
                cout << "correct value: "<< data[i] << endl;
                cout << "your record's value: " << currValue << endl;
                throw Error("hashtableCopy.find is not passing back the correct data",testnumber);
            }
        }
        hashTiming[2]+=t2.currtime();
        testnumber++;

        cout << "Test 11: Test assignment operator" << endl;
        t2.reset();
        t2.start();
        hashtableCopy = hashtable;
        t2.stop();
        hashTiming[7]=t2.currtime();
        t2.reset();
        for(int i=0;i<hashtableMax;i++){
            t2.start();
            oprc=hashtableCopy.find(wordlist[i],currValue);                          //put it back in the table
            t2.stop();
            if(i%10){
                if(!oprc){
                    throw Error("table made with = operator did not find word that should have been in table",testnumber);
                }
                if(data[i]!=currValue){
                    cout << "search key:" << wordlist[i] << endl;
                    cout << "correct value: "<< data[i] << endl;
                    cout << "your record's value: " << currValue << endl;
                    throw Error("hashtableCopy.find() is not passing back the correct data",testnumber);
                } 
            }
            else{
                if(oprc){
                    throw Error("hashtablecopy.find() found a record that should not be in table",testnumber);
                }
            }
        }
        hashTiming[2]+=t2.currtime();
        testnumber++;


        cout << "Test 12: Add the removed items back to hashtable table..." << endl;
        for(int i=0;i<hashtableMax;i+=10){
            data[i]-=1;
            oprc=hashtable.update(wordlist[i],data[i]);          //put it in the chaining table
            if(!oprc){                             //check return code (should be true)
                throw Error("hashtable::update is returning false when table is not full",testnumber);
            }
        }/*end for*/
        testnumber++;


        cout << "Test 13: Checking that everything in hashtable was properly updated adding adding removed records back" << endl;
        t2.reset();
        for(int i=0;i<hashtableMax;i++){
            t2.start();
            oprc=hashtable.find(wordlist[i],currValue);                        
            t2.stop();
            if(!oprc){
                throw Error("hashtable::find() could not find record that should be there",testnumber);
            }
            if(data[i]!=currValue){
                cout << "search key:" << wordlist[i] << endl;
                cout << "correct value: "<< data[i] << endl;
                cout << "your record's value: " << currValue << endl;
                throw Error("hashtable::find is not passing back the correct data",testnumber);
            }    
        }
        hashTiming[2]+=t2.currtime();
        testnumber++;
        cout << testnumber << " out of " << NUMTESTS << " tests passed." << endl;

        if(testnumber == NUMTESTS){
            cout << "Congratulations, looks like your assignment is completed" << endl;
        }
        else{
            cout << "Looks like your assigment still needs some work." << endl;
        }        

        cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"<< endl;
        cout << endl;

        cout << "Timing summary: Hash Table" << endl;
        printTiming(hashTiming,hashtableMax,hashtableCapacity);
        cout << endl;

        fclose(fp);
    }
    catch(Error e){
        cout << e.msg_ << endl;
        cout << e.passed_ << " tests of "<< NUMTESTS <<" passed" << endl;
    }
}


void printTiming(double timing[],int numrec, int capacity){
    cout << endl;
    cout << "Number of records: " << numrec << endl;
    cout << "Capacity: " << capacity << endl << endl;
    cout << "     Operation                        |    Time     " << endl;
    cout << "--------------------------------------|-------------" << endl;
    cout << " update, new record                   |  " << timing[0] << endl;
    cout << " update, new rec not added            |  " << timing[1] << endl;
    cout << " update, modify record                |  " << timing[3] << endl;
    cout << " find                                 |  " << timing[2] << endl;
    cout << " remove  (item in list)               |  " << timing[5] << endl;
    cout << " remove  (item not in list)           |  " << timing[6] << endl;
    cout << " copy constructor                     |  " << timing[4] << endl;
    cout << " assignment operator                  |  " << timing[7] << endl;


}

void setData(int data[],int sz){
    for(int i=0;i<sz;i++){
        data[i]=rand()%100;
    }
}

