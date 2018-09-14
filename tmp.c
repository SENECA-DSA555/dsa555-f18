#include <stdio.h>
int main(void){
	int num;
	char ch;
	printf("enter number: ");
	scanf("%d",&num);
	printf("enter character");
	scanf("%c",&ch);
	printf("char was: %c, num was %d",ch,num);
}