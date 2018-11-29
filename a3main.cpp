/****************************************/
/*                                      */
/*   This is the official tester for    */
/*   assignment 3                       */
/*                                      */
/*   version 1.1: fixed bug in test 6   */
/*                                      */
/*   To compile on matrix:              */
/*   g++ a3main.cpp -std=c++0x          */
/*                                      */
/****************************************/
#include "threadedtree.h"
#include <cstring>
#include <iostream>
#include <cstdlib>
using namespace std;
//The next line allows extra output
//when things go wrong
//change it to 1 to show a the list content (and what it should be)
//or a number more than 1 for a lot of output (not recommended... too much)
#define VERBOSE 0

struct Record{
	char word_[30];
	int count_;

};
ostream& operator<<(ostream& os, const Record rec){
	os << rec.word_;
	return os;
}
bool operator<(const Record& lhs, const Record& rhs){
	bool rc=false;
	if(strcmp(lhs.word_,rhs.word_) < 0){
		rc=true;
	}
	return rc;
}
bool operator>(const Record& lhs, const Record& rhs){
	bool rc=false;
	if(strcmp(lhs.word_,rhs.word_) > 0){
		rc=true;
	}
	return rc;
}
bool operator==(const Record& lhs, const Record& rhs){
	bool rc=false;
	if(strcmp(lhs.word_,rhs.word_)==0){
		rc=true;

	}
	return rc;
}
bool operator!=(const Record& lhs, const Record& rhs){
	bool rc=false;
	if(strcmp(lhs.word_,rhs.word_)!=0){
		rc=true;
	}
	return rc;
}

template <typename T>
void mix(T arr[],int size);

int main(void){
	bool passtest=true;
	int numPassed=0;
	const int numLarge = 20000;

	//this array will create the exact tree shown in the diagram for the assignment
	int exampleData[9]={20,30,10,15,5,25,27,18,16};
	//the ordered (sorted) version of example recordData.  Used to test iterators
	int exampleOrdered[9]={5,10,15,16,18,20,25,27,30};


	Record orderedRecords[20]={
		{"Calvin",1},
		{"Hobbes",2},
		{"and",3},
		{"brown ",4},
		{"captain",5},
		{"carrot",6},
		{"coffee",7},
		{"dog",8},
		{"fox",9},
		{"jumped",10},
		{"lavender",11},
		{"lazy",12},
		{"lilac",13},
		{"lily",14},
		{"night",15},
		{"over",16},
		{"quick",17},
		{"tea",18},
		{"the",19},
		{"watch",20}
	};

	
	Record recordData[20];
	int largeData[numLarge];
	int largeDataOrdered[numLarge];
	int recCap=20;
	ThreadedTree<Record>::iterator recIterator1;
	ThreadedTree<Record>::iterator recIterator2;
	ThreadedTree<Record>::const_iterator crecIterator1;
	ThreadedTree<Record>::const_iterator crecIterator2;
	ThreadedTree<int>::iterator intIterator1;
	ThreadedTree<int>::iterator intIterator2;
	ThreadedTree<int>::const_iterator cintIterator1;
	ThreadedTree<int>::const_iterator cintIterator2;
	bool isGood=true;
	for(int i=0;i<recCap;i++){
		recordData[i]=orderedRecords[i];
	}
	largeData[0]=1;
	largeDataOrdered[0]=1;

	for(int i=1;i<numLarge;i++){
		largeData[i]=largeData[i-1]+(rand()%100) + 1;
		largeDataOrdered[i]=largeData[i];
	}
	//do a number of swaps with data in array to mix up the data so that its not sorted.
	mix(recordData,20);
	mix(largeData,numLarge);


	/* Test constructors*/
	cout << "Test 1: create empty trees, check (c)begin()/(c)end(), == and != operator for (const_)iterators" << endl;
	ThreadedTree<int> exampleTree;
	ThreadedTree<Record> recordTree;
	ThreadedTree<int> largeDataTree;
	if((recordTree.begin() != recordTree.end()) || (largeDataTree.begin() != largeDataTree.end()) || exampleTree.begin() != exampleTree.end() ||
		!(recordTree.cbegin()==recordTree.cend()) || !(largeDataTree.cbegin() == largeDataTree.cend()) || !(exampleTree.begin() == exampleTree.end())){
		cout << "Error 1: check your constructor, begin()/cbegin() and end()/cend(), == and != functions" << endl;
		passtest=false;
	}
	if(passtest){
		numPassed++;
		cout << "Test 2: Test insert() and find() functions" << endl;
		for(int i=0;i<9;i++){
			exampleTree.insert(exampleData[i]);
		}
		for(int i=0;i<recCap;i++){
			recordTree.insert(recordData[i]);
		}
		for(int i=0;i<numLarge;i++){
			largeDataTree.insert(largeData[i]);
		}

		for(int i=0;isGood && i < 9;i++){
			intIterator1=exampleTree.find(exampleData[i]);
			cintIterator1=exampleTree.find(exampleData[i]);
			if(intIterator1==exampleTree.end() || *intIterator1 != exampleData[i]){
				isGood=false;
				cout << "Error:  The iterator returned when searching for a value that should be in tree is not correct" << endl;
				cout << "Was searching for : " << exampleData[i] << " in exampleTree."   << endl;
				if(intIterator1 == exampleTree.end()){
					cout << "Function returned end() when it should have returned iterator to the node"  << endl;
				}
				else{
					cout << "the node returned by your iterator contains: " << *intIterator1 << endl;
				}
			}
			if(cintIterator1==exampleTree.cend() || *cintIterator1 != exampleData[i]){
				isGood=false;
				cout << "Error:  The iterator returned when searching for a value that should be in tree is not correct" << endl;
				cout << "Was searching for : " << exampleData[i] << " in exampleTree."   << endl;
				if(cintIterator1 == exampleTree.cend()){
					cout << "Function returned end() when it should have returned iterator to the node"  << endl;
				}
				else{
					cout << "the node returned by your iterator contains: " << *cintIterator1 << endl;
				}
			}
		}
		for(int i=0;isGood && i < 20;i++){
			recIterator1=recordTree.find(recordData[i]);
			crecIterator1=recordTree.find(recordData[i]);
			if(recIterator1==recordTree.end() || *recIterator1 != recordData[i]){
				isGood=false;
				cout << "Error:  The iterator returned when searching for a value that should be in tree is not correct" << endl;
				cout << "Was searching for : " << recordData[i] << " in recordTree."   << endl;
				if(recIterator1 == recordTree.end()){
					cout << "Function returned end() when it should have returned iterator to the node"  << endl;
				}
				else{
					cout << "the node returned by your iterator contains: " << *recIterator1 << endl;
				}
			}
			if(crecIterator1==recordTree.cend() || *crecIterator1 != recordData[i]){
				isGood=false;
				cout << "Error:  The iterator returned when searching for a value that should be in tree is not correct" << endl;
				cout << "Was searching for : " << recordData[i] << " in recordTree."   << endl;
				if(crecIterator1 == recordTree.cend()){
					cout << "Function returned end() when it should have returned iterator to the node"  << endl;
				}
				else{
					cout << "the node returned by your iterator contains: " << *crecIterator1 << endl;
				}
			}
		}
		for(int i=0;isGood && i < numLarge;i++){
			intIterator1=largeDataTree.find(largeData[i]);
			cintIterator1=largeDataTree.find(largeData[i]);
			if(intIterator1==largeDataTree.end() || *intIterator1 != largeData[i]){
				isGood=false;
				cout << "Error:  The iterator returned when searching for a value that should be in tree is not correct" << endl;
				cout << "Was searching for : " << largeData[i] << " in largeDataTree."   << endl;
				if(intIterator1 == largeDataTree.end()){
					cout << "Function returned end() when it should have returned iterator to the node"  << endl;
				}
				else{
					cout << "the node returned by your iterator contains: " << *intIterator1 << endl;
				}
			}
			if(cintIterator1==largeDataTree.cend() || *cintIterator1 != largeData[i]){
				isGood=false;
				cout << "Error:  The iterator returned when searching for a value that should be in tree is not correct" << endl;
				cout << "Was searching for : " << largeData[i] << " in largeDataTree."   << endl;
				if(cintIterator1 == largeDataTree.cend()){
					cout << "Function returned end() when it should have returned iterator to the node"  << endl;
				}
				else{
					cout << "the node returned by your iterator contains: " << *cintIterator1 << endl;
				}
			}
		}
		if(!isGood){
			passtest=false;
		}
		else{
			numPassed++;
		}
	}

	if(passtest){
		cout << "Test 3: Test (const_)iterator postfix ++ operator"  << endl;

		cintIterator1=exampleTree.cbegin();
		intIterator1=exampleTree.begin();
		int i=0;
		while(isGood && i < 9){
			if(*intIterator1 != exampleOrdered[i]){
				isGood=false;
				cout << "Error 3a: iterator is not going through your tree correct" << endl;
	
				#if VERBOSE >= 1
				auto it=exampleTree.begin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j< 9 && it!= exampleTree.end();j++,it++){
					cout << *it << " ---> " << exampleOrdered[j] << endl;
				}
				#endif
	
			}
			if(*cintIterator1 != exampleOrdered[i]){
				isGood=false;
				cout << "Error 3b: const_iterator is not going through your tree correct" << endl;
				#if VERBOSE >= 1
				auto it=exampleTree.cbegin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j< 9 && it!= exampleTree.cend();j++,it++){
					cout << *it << " ---> " << exampleOrdered[j] << endl;
				}
				#endif
			}		
			cintIterator2=cintIterator1++;
			intIterator2=intIterator1++;
			if(*intIterator2 != exampleOrdered[i]){
				isGood=false;
				cout << "Error 3c: Your postfix ++ operator is not returning the correct value" << endl;
			}
			if(*cintIterator2 != exampleOrdered[i]){
				isGood=false;
				cout << "Error 3d: Your postfix ++ operator is not returning the correct value" << endl;
			}
			i++;
		}
		if(isGood){
			if(cintIterator1 != exampleTree.cend() || intIterator1 != exampleTree.end()){
				cout << "Error 3e: (const_)iterator is not going through your tree correct" << endl;
				cout << "(const_)iterator should be end()/cend()"  << endl;
				isGood=false;
			}
		}



		crecIterator1=recordTree.cbegin();
		recIterator1=recordTree.begin();
		i=0;
		while(isGood && i < 20){
			if(*recIterator1 != orderedRecords[i]){
				isGood=false;
				cout << "Error 3f: iterator is not going through your tree correct" << endl;

				#if VERBOSE >= 1
				auto it=recordTree.begin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<20 && it!= recordTree.end();j++,it++){
					cout << *it << " ---> " << orderedRecords[j] << endl;
				}
				#endif

			}
			if(*crecIterator1 != orderedRecords[i]){
				isGood=false;
				cout << "Error 3g: const_iterator is not going through your tree correct" << endl;
				#if VERBOSE >= 1
				auto it=recordTree.cbegin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<20 && it!= recordTree.cend();j++,it++){
					cout << *it << " ---> " << orderedRecords[j] << endl;
				}
				#endif
			}		
			crecIterator2=crecIterator1++;
			recIterator2=recIterator1++;
			if(*recIterator2 != orderedRecords[i]){
				isGood=false;
				cout << "Error 3h: Your postfix ++ operator is not returning the correct value" << endl;
			}
			if(*crecIterator2 != orderedRecords[i]){
				isGood=false;
				cout << "Error 3i: Your postfix ++ operator is not returning the correct value" << endl;
			}
			i++;
		}

		if(isGood){
			if(crecIterator1 != recordTree.cend() || recIterator1 != recordTree.end()){
				cout << "Error 3j: (const_)iterator is not going through your tree correct" << endl;
				cout << "(const_)iterator should be end()/cend()"  << endl;
				isGood=false;
			}
		}
		cintIterator1=largeDataTree.cbegin();
		intIterator1=largeDataTree.begin();
		i=0;
		while(isGood && i < numLarge){
			if(*intIterator1 != largeDataOrdered[i]){
				isGood=false;
				cout << "Error 3k: iterator is not going through your tree correct" << endl;

				#if VERBOSE > 1
				auto it=largeDataTree.begin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<numLarge && it!= largeDataTree.end();j++,it++){
					cout << *it << " ---> " << largeDataOrdered[j] << endl;
				}
				#endif

			}
			if(*cintIterator1 != largeDataOrdered[i]){
				isGood=false;
				cout << "Error 3l: const_iterator is not going through your tree correct" << endl;
				#if VERBOSE > 1
				auto it=largeDataTree.cbegin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<numLarge && it!= largeDataTree.cend();j++,it++){
					cout << *it << " ---> " << largeDataOrdered[j] << endl;
				}
				#endif
			}		
			cintIterator2=cintIterator1++;
			intIterator2=intIterator1++;
			if(*intIterator2 != largeDataOrdered[i]){
				isGood=false;
				cout << "Error 3m: Your postfix ++ operator is not returning the correct value" << endl;
			}
			if(*cintIterator2 != largeDataOrdered[i]){
				isGood=false;
				cout << "Error 3n: Your postfix ++ operator is not returning the correct value" << endl;
			}
			i++;
		}

		if(isGood){
			if(cintIterator1 != largeDataTree.cend() || intIterator1 != largeDataTree.end()){
				cout << "Error 3o: (const_)iterator is not going through your tree correct" << endl;
				cout << "(const_)iterator should be end()/cend()"  << endl;
				isGood=false;
			}
		}

		if(isGood){
			numPassed++;
		}
		else{
			passtest=false;

		}
	}


	if(passtest){
		cout << "Test 4: Test (const_)iterator prefix ++ operator"  << endl;

		cintIterator1=exampleTree.cbegin();
		intIterator1=exampleTree.begin();
		cintIterator2=cintIterator1;
		intIterator2=intIterator1;
		int i=0;
		while(isGood && i < 9){
			if(*intIterator1 != exampleOrdered[i]){
				isGood=false;
				cout << "Error 4a: iterator is not going through your tree correct" << endl;
	
				#if VERBOSE >= 1
				auto it=exampleTree.begin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j< 9 && it!= exampleTree.end();j++,it++){
					cout << *it << " ---> " << exampleOrdered[j] << endl;
				}
				#endif
	
			}
			if(*cintIterator1 != exampleOrdered[i]){
				isGood=false;
				cout << "Error 4b: const_iterator is not going through your tree correct" << endl;
				#if VERBOSE >= 1
				auto it=exampleTree.cbegin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j< 9 && it!= exampleTree.cend();j++,it++){
					cout << *it << " ---> " << exampleOrdered[j] << endl;
				}
				#endif
			}		

			if(*intIterator2 != exampleOrdered[i]){
				isGood=false;
				cout << "Error 4c: Your prefix ++ operator is not returning the correct value" << endl;
			}
			if(*cintIterator2 != exampleOrdered[i]){
				isGood=false;
				cout << "Error 4d: Your prefix ++ operator is not returning the correct value" << endl;
			}
			i++;
			cintIterator2=++cintIterator1;
			intIterator2=++intIterator1;
		}
		if(isGood){
			if(cintIterator1 != exampleTree.cend() || intIterator1 != exampleTree.end()){
				cout << "Error 4e: (const_)iterator is not going through your tree correct" << endl;
				cout << "(const_)iterator should be end()/cend()"  << endl;
				isGood=false;
			}
		}



		crecIterator1=recordTree.cbegin();
		recIterator1=recordTree.begin();
		crecIterator2=crecIterator1;
		recIterator2=recIterator1;
		i=0;
		while(isGood && i < 20){
			if(*recIterator1 != orderedRecords[i]){
				isGood=false;
				cout << "Error 4f: iterator is not going through your tree correct" << endl;

				#if VERBOSE >= 1
				auto it=recordTree.begin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<20 && it!= recordTree.end();j++,it++){
					cout << *it << " ---> " << orderedRecords[j] << endl;
				}
				#endif

			}
			if(*crecIterator1 != orderedRecords[i]){
				isGood=false;
				cout << "Error 4g: const_iterator is not going through your tree correct" << endl;
				#if VERBOSE >= 1
				auto it=recordTree.cbegin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<20 && it!= recordTree.cend();j++,it++){
					cout << *it << " ---> " << orderedRecords[j] << endl;
				}
				#endif
			}		

			if(*recIterator2 != orderedRecords[i]){
				isGood=false;
				cout << "Error 4h: Your prefix ++ operator is not returning the correct value" << endl;
			}
			if(*crecIterator2 != orderedRecords[i]){
				isGood=false;
				cout << "Error 4i: Your prefix ++ operator is not returning the correct value" << endl;
			}
			crecIterator2=++crecIterator1;
			recIterator2=++recIterator1;
			i++;
		}

		if(isGood){
			if(crecIterator1 != recordTree.cend() || recIterator1 != recordTree.end()){
				cout << "Error 4j: (const_)iterator is not going through your tree correct" << endl;
				cout << "(const_)iterator should be end()/cend()"  << endl;
				isGood=false;
			}
		}
		cintIterator1=largeDataTree.cbegin();
		intIterator1=largeDataTree.begin();
		cintIterator2=cintIterator1;
		intIterator2=intIterator1;
		i=0;
		while(isGood && i < numLarge){
			if(*intIterator1 != largeDataOrdered[i]){
				isGood=false;
				cout << "Error 4k: iterator is not going through your tree correct" << endl;

				#if VERBOSE > 1
				auto it=largeDataTree.begin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<numLarge && it!= largeDataTree.end();j++,it++){
					cout << *it << " ---> " << largeDataOrdered[j] << endl;
				}
				#endif

			}
			if(*cintIterator1 != largeDataOrdered[i]){
				isGood=false;
				cout << "Error 4l: const_iterator is not going through your tree correct" << endl;
				#if VERBOSE > 1
				auto it=largeDataTree.cbegin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<numLarge && it!= largeDataTree.cend();j++,it++){
					cout << *it << " ---> " << largeDataOrdered[j] << endl;
				}
				#endif
			}		

			if(*intIterator2 != largeDataOrdered[i]){
				isGood=false;
				cout << "Error 4m: Your prefix ++ operator is not returning the correct value" << endl;
			}
			if(*cintIterator2 != largeDataOrdered[i]){
				isGood=false;
				cout << "Error 4n: Your prefix ++ operator is not returning the correct value" << endl;
			}
			cintIterator2=++cintIterator1;
			intIterator2=++intIterator1;
			i++;
		}

		if(isGood){
			if(cintIterator1 != largeDataTree.cend() || intIterator1 != largeDataTree.end()){
				cout << "Error 4o: (const_)iterator is not going through your tree correct" << endl;
				cout << "(const_)iterator should be end()/cend()"  << endl;
				isGood=false;
			}
		}

		if(isGood){
			numPassed++;
		}
		else{
			passtest=false;

		}

	}



	if(passtest){
		cout << "Test 5: Test (const_)iterator prefix -- operator"  << endl;

		cintIterator1=exampleTree.cend();
		intIterator1=exampleTree.end();
		int i=9;
		while(isGood && i > 0){
			cintIterator2=--cintIterator1;
			intIterator2=--intIterator1;
			i--;
			if(*intIterator1 != exampleOrdered[i]){
				isGood=false;
				cout << "Error 5a: prefix -- operator is not going through your tree correct" << endl;
	
				#if VERBOSE >= 1
				auto it=exampleTree.begin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j< 9 && it!= exampleTree.end();j++,it++){
					cout << *it << " ---> " << exampleOrdered[j] << endl;
				}
				#endif
	
			}
			if(*cintIterator1 != exampleOrdered[i]){
				isGood=false;
				cout << "Error 5b: prefix -- operator is not going through your tree correct" << endl;
				#if VERBOSE >= 1
				auto it=exampleTree.cbegin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j< 9 && it!= exampleTree.cend();j++,it++){
					cout << *it << " ---> " << exampleOrdered[j] << endl;
				}
				#endif
			}		

			if(*intIterator2 != exampleOrdered[i]){
				isGood=false;
				cout << "Error 5c: Your prefix -- operator is not returning the correct value" << endl;
			}
			if(*cintIterator2 != exampleOrdered[i]){
				isGood=false;
				cout << "Error 5d: Your prefix -- operator is not returning the correct value" << endl;
			}

		}
		if(isGood){
			if(cintIterator1 != exampleTree.begin() || intIterator1 != exampleTree.begin()){
				cout << "Error 5e: (const_)iterator is not going through your tree correct" << endl;
				cout << "(const_)iterator should be begin()/cbegin()"  << endl;
				isGood=false;
			}
		}



		crecIterator1=recordTree.cend();
		recIterator1=recordTree.end();
		i=20;
		while(isGood && i >0){
			crecIterator2=--crecIterator1;
			recIterator2=--recIterator1;
			i--;
			if(*recIterator1 != orderedRecords[i]){
				isGood=false;
				cout << "Error 5f: iterator is not going through your tree correct" << endl;

				#if VERBOSE >= 1
				auto it=recordTree.begin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<20 && it!= recordTree.end();j++,it++){
					cout << *it << " ---> " << orderedRecords[j] << endl;
				}
				#endif

			}
			if(*crecIterator1 != orderedRecords[i]){
				isGood=false;
				cout << "Error 5g: const_iterator is not going through your tree correct" << endl;
				#if VERBOSE >= 1
				auto it=recordTree.cbegin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<20 && it!= recordTree.cend();j++,it++){
					cout << *it << " ---> " << orderedRecords[j] << endl;
				}
				#endif
			}		

			if(*recIterator2 != orderedRecords[i]){
				isGood=false;
				cout << "Error 5h: Your prefix -- operator is not returning the correct value" << endl;
			}
			if(*crecIterator2 != orderedRecords[i]){
				isGood=false;
				cout << "Error 5i: Your prefix -- operator is not returning the correct value" << endl;
			}

		}

		if(isGood){
			if(crecIterator1 != recordTree.cbegin() || recIterator1 != recordTree.begin()){
				cout << "Error 5j: (const_)iterator is not going through your tree correct" << endl;
				cout << "(const_)iterator should be begin()/cbegin()"  << endl;
				isGood=false;
			}
		}



		cintIterator1=largeDataTree.cend();
		intIterator1=largeDataTree.end();
		i=numLarge;
		while(isGood && i > 0){
			cintIterator2=--cintIterator1;
			intIterator2=--intIterator1;
			i--;
			if(*intIterator1 != largeDataOrdered[i]){
				isGood=false;
				cout << "Error 5k: iterator is not going through your tree correct" << endl;

				#if VERBOSE > 1
				auto it=largeDataTree.end();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<numLarge && it!= largeDataTree.end();j++,it++){
					cout << *it << " ---> " << largeDataOrdered[j] << endl;
				}
				#endif

			}
			if(*cintIterator1 != largeDataOrdered[i]){
				isGood=false;
				cout << "Error 5l: const_iterator is not going through your tree correct" << endl;
				#if VERBOSE > 1
				auto it=largeDataTree.cend();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<numLarge && it!= largeDataTree.cend();j++,it++){
					cout << *it << " ---> " << largeDataOrdered[j] << endl;
				}
				#endif
			}		

			if(*intIterator2 != largeDataOrdered[i]){
				isGood=false;
				cout << "Error 5m: Your prefix -- operator is not returning the correct value" << endl;
			}
			if(*cintIterator2 != largeDataOrdered[i]){
				isGood=false;
				cout << "Error 5n: Your prefix -- operator is not returning the correct value" << endl;
			}

		}

		if(isGood){
			if(cintIterator1 != largeDataTree.cbegin() || intIterator1 != largeDataTree.begin()){
				cout << "Error 5o: (const_)iterator is not going through your tree correct" << endl;
				cout << "(const_)iterator should be begin()/cbegin()"  << endl;
				isGood=false;
			}
		}

		if(isGood){
			numPassed++;
		}
		else{
			passtest=false;

		}
	}


	if(passtest){
		cout << "Test 6: Test (const_)iterator postfix -- operator"  << endl;

		cintIterator1=exampleTree.cend();
		intIterator1=exampleTree.end();
		int i=9;
		while(isGood && i > 0){
			cintIterator2=cintIterator1--;
			intIterator2=intIterator1--;
			i--;
			if(*intIterator1 != exampleOrdered[i]){
				isGood=false;
				cout << "Error 6a: postfix -- operator is not going through your tree correct" << endl;
	
				#if VERBOSE >= 1
				auto it=exampleTree.begin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j< 9 && it!= exampleTree.end();j++,it++){
					cout << *it << " ---> " << exampleOrdered[j] << endl;
				}
				#endif
	
			}
			if(*cintIterator1 != exampleOrdered[i]){
				isGood=false;
				cout << "Error 6b: postfix -- operator is not going through your tree correct" << endl;
				#if VERBOSE >= 1
				auto it=exampleTree.cbegin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j< 9 && it!= exampleTree.cend();j++,it++){
					cout << *it << " ---> " << exampleOrdered[j] << endl;
				}
				#endif
			}		
			if(i < 8){
				if(*intIterator2 != exampleOrdered[i+1]){
					isGood=false;
					cout << "Error 6c: Your postfix -- operator is not returning the correct value" << endl;
				}
				if(*cintIterator2 != exampleOrdered[i+1]){
					isGood=false;
					cout << "Error 6d: Your postfix -- operator is not returning the correct value" << endl;
				}
			}
			else{
				if(intIterator2 != exampleTree.end()){
					isGood=false;
					cout << "Error 6c: Your postfix -- operator is not returning the correct value" << endl;
				}
				if(cintIterator2 != exampleTree.cend()){
					isGood=false;
					cout << "Error 6d: Your postfix -- operator is not returning the correct value" << endl;
				}
			}

		}
		if(isGood){
			if(cintIterator1 != exampleTree.begin() || intIterator1 != exampleTree.begin()){
				cout << "Error 6e: (const_)iterator is not going through your tree correct" << endl;
				cout << "(const_)iterator should be begin()/cbegin()"  << endl;
				isGood=false;
			}
		}



		crecIterator1=recordTree.cend();
		recIterator1=recordTree.end();
		i=20;
		while(isGood && i >0){
			crecIterator2=crecIterator1--;
			recIterator2=recIterator1--;
			i--;
			if(*recIterator1 != orderedRecords[i]){
				isGood=false;
				cout << "Error 6f: iterator is not going through your tree correct" << endl;

				#if VERBOSE >= 1
				auto it=recordTree.begin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<20 && it!= recordTree.end();j++,it++){
					cout << *it << " ---> " << orderedRecords[j] << endl;
				}
				#endif

			}
			if(*crecIterator1 != orderedRecords[i]){
				isGood=false;
				cout << "Error 6g: const_iterator is not going through your tree correct" << endl;
				#if VERBOSE >= 1
				auto it=recordTree.cbegin();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<20 && it!= recordTree.cend();j++,it++){
					cout << *it << " ---> " << orderedRecords[j] << endl;
				}
				#endif
			}		
			if(i < recCap-1){
				if(*recIterator2 != orderedRecords[i+1]){
					isGood=false;
					cout << "Error 6h: Your postfix -- operator is not returning the correct value" << endl;
				}
				if(*crecIterator2 != orderedRecords[i+1]){
					isGood=false;
					cout << "Error 6i: Your postfix -- operator is not returning the correct value" << endl;
				}
			}
			else{
				if(recIterator2 != recordTree.end()){
					isGood=false;
					cout << "Error 6h: Your postfix -- operator is not returning the correct value" << endl;
				}
				if(crecIterator2 != recordTree.cend()){
					isGood=false;
					cout << "Error 6i: Your postfix -- operator is not returning the correct value" << endl;
				}
			}

		}

		if(isGood){
			if(crecIterator1 != recordTree.cbegin() || recIterator1 != recordTree.begin()){
				cout << "Error 6j: (const_)iterator is not going through your tree correct" << endl;
				cout << "(const_)iterator should be begin()/cbegin()"  << endl;
				isGood=false;
			}
		}


		cintIterator1=largeDataTree.cend();
		intIterator1=largeDataTree.end();
		i=numLarge;
		while(isGood && i > 0){
			cintIterator2=cintIterator1--;
			intIterator2=intIterator1--;
			i--;
			if(*intIterator1 != largeDataOrdered[i]){
				isGood=false;
				cout << "Error 6k: iterator is not going through your tree correct" << endl;

				#if VERBOSE > 1
				auto it=largeDataTree.end();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<numLarge && it!= largeDataTree.end();j++,it++){
					cout << *it << " ---> " << largeDataOrdered[j] << endl;
				}
				#endif

			}
			if(*cintIterator1 != largeDataOrdered[i]){
				isGood=false;
				cout << "Error 6l: const_iterator is not going through your tree correct" << endl;
				#if VERBOSE > 1
				auto it=largeDataTree.cend();
				cout << "The following is a listing of your tree vs correct" << endl;
				cout << "your tree  --->   correct value"  << endl;
				for(int j=0;j<numLarge && it!= largeDataTree.cend();j++,it++){
					cout << *it << " ---> " << largeDataOrdered[j] << endl;
				}
				#endif
			}		

			if(i < numLarge-1){
				if(*intIterator2 != largeDataOrdered[i+1]){
					isGood=false;
					cout << "Error 6c: Your postfix -- operator is not returning the correct value" << endl;
				}
				if(*cintIterator2 != largeDataOrdered[i+1]){
					isGood=false;
					cout << "Error 6d: Your postfix -- operator is not returning the correct value" << endl;
				}
			}
			else{
				if(intIterator2 != largeDataTree.end()){
					isGood=false;
					cout << "Error 6c: Your postfix -- operator is not returning the correct value" << endl;
				}
				if(cintIterator2 != largeDataTree.cend()){
					isGood=false;
					cout << "Error 6d: Your postfix -- operator is not returning the correct value" << endl;
				}
			}

		}

		if(isGood){
			if(cintIterator1 != largeDataTree.cbegin() || intIterator1 != largeDataTree.begin()){
				cout << "Error 6o: (const_)iterator is not going through your tree correct" << endl;
				cout << "(const_)iterator should be begin()/cbegin()"  << endl;
				isGood=false;
			}
		}

		if(isGood){
			numPassed++;
		}
		else{
			passtest=false;

		}
	}


 	if(numPassed == 6){
	 	cout << "Testing for Assignment 3 completed successfully" << endl;
	}
	else{
		cout << numPassed << " / 6 tests passed.  Looks like you still" << endl;
		cout << "have some work to do" << endl;
	}
	return 0;
}


template <typename T>
void mix(T arr[],int size){
	int idx1,idx2;
	for(int i=0;i<size*5;i++){
		idx1=rand()%size;
		idx2=rand()%size;
		while(idx1==idx2){
			idx2=rand()%size;
		}
		std::swap(arr[idx1],arr[idx2]);
	}
}
