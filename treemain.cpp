#include <iostream>
#include "bst.h"

int main(void){
	using namespace std;
	BST<int> tree;
	int data[20]={8,3,15,1,6,12,20,2, 5, 7, 13, 17, 25, 4,26};
	for(int i=0;i<15;i++){
		tree.insertRecursive(data[i]);
	}
	tree.printPreOrder();
}