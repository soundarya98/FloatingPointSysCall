#include <stdio.h>
#include <unistd.h>
#include "addWrapper.h" 
/*
* The following function is in the user space and
* returns the sum of 2 floats using a system call.
* The preconditions are checked in the wrapper file,
* and the addWrapper.h file makes sure th user doesn't
* need to remember the system call number.
*/
int main(int argc, char *argv[])
{
	float fnum1, fnum2, floatres_wrapper;
	int num1, num2, intres_wrapper;

	//Taking float input from user
	printf("Enter Number 1 and Number 2\n");
	scanf("%f %f", &fnum1, &fnum2);

	//Taking result from wrapper
	floatres_wrapper=cwrapperfunc(fnum1,fnum2);

	//If negative result, then there must have been an error.
	//This is taken care of by the wrapper function
	if(floatres_wrapper>=0)
		printf("Result of wrapper call : %f\n", floatres_wrapper);

return 0;
}