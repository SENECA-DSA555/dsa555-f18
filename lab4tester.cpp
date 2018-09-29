#include <string>
#include <iostream>

bool bracketCheck(const std::string& s);
int main(void){
	std::string tests[5]={
		"a(b)c[d]ef",
		"aa[bcd(efg{hij}k[lm]no)p]qrs",
		"a(b)c]d",
		"[[]",
		"aa(bb{cc)dd}ee"
	};
	bool results[5]={true,true,false,false,false};

	for(int i=0;i<5;i++){
		if(bracketCheck(tests[i])==results[i]){
			std::cout << "Test "<< i+1 << " passed" << std::endl;
		}
		else{
			std::cout << "Test "<< i+1 << " error" << std::endl;
		}
	}
	return 0;
}