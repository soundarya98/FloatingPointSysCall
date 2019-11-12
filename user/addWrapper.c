#include "addWrapper.h"
float cwrapperfunc(float num1, float num2)
{

	int inum1  = *(int*)&num1;
	int inum2  = *(int*)&num2;

	/*
	* PART 1: FOR INPUTS
	*/


	//1. Negative
	if(inum1<0 | inum2<0)
	{
		printf("Negative number entered\n");
		return -1;
	}

	int mantissa1=inum1&0x7fffff;
	int mantissa2=inum2&0x7fffff;

	int exponent1=(inum1>>23);
	int exponent2=(inum2>>23);

	//2. Infinite
	if(exponent1==0xff && mantissa1==0)
	{
		printf("First number is infinite\n");
		return -2;
	}

	if(exponent2==0xff && mantissa2==0)
	{
		printf("Second number is infinite\n");
		return -2;
	}

	//3. NaN
	if(exponent1==0xff && mantissa1!=0)
	{
		printf("First number is NaN\n");
		return -3;
	}

	if(exponent2==0xff && mantissa2!=0)
	{
		printf("Second number is NaN\n");
		return -3;
	}
	
	int tmp= add_syscall(inum1,inum2);

	/*
	* PART 2: FOR OUTPUTS
	*/
	
	//1. If sum is infinite
	if(tmp==0x7f800000)
	{
		printf("\nAnswer is out of bounds");
		return -4;
	}


	float tmp2=*(float*)&tmp;
	return tmp2;
}