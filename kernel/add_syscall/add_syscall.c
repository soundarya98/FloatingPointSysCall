#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/syscalls.h>
#include "add_syscall.h"

SYSCALL_DEFINE2(add_syscall, int, num1, int, num2)
{

/* 
* Preconditions are already checked in the wrapper file. The following file adds 2 valid positive * integers and returns INF in case of overflow.
*/


	//If both numbers are zero, then no need to add
	if(num1==0 && num2==0)
		return 0;

	//Swapping numbers if the second number is smaller than the first number
	if(num1<num2)
	{
		num1=num1^num2;
		num2=num1^num2;
		num1=num1^num2;
	}

	//Splitting exponents and subracted bias for clarity
	int exp1=(num1>>23)-127;
	int exp2=(num2>>23)-127;

	//Splitting mantissas and adding the implicit 1 before the decimal
	int mantissa1=num1&(0x007fffff);
	mantissa1=(1<<23)|mantissa1;
	int mantissa2=num2&(0x007fffff);
	mantissa2=(1<<23)|mantissa2;

	//2^exp1*mantissa1 + 2^exp2*mantissa2 = 2^exp1(mantissa1+ 2^(exp2-exp1)*mantissa2)
	int diff=exp1-exp2;
	mantissa2=mantissa2>>diff;

	int ans=mantissa1+mantissa2;
	int manans;


	//Exponent needs to be shifted when the 25th bit is set. After this, we remove the implicit 1
	if((ans & (1<<24))!=0)
	{
		exp1++;
		ans=ans>>1;
		manans=ans&(0x7fffff);
	}

	else
	{
		manans=ans&(0x7fffff);
	}

	
	//Adding back the bias
	int expans=exp1+127;

	//If sum overflows, then we return INF
	if(expans>=255)
		return 0x7f800000;		

	//Constructing back the float in IEEE format
	int finalans=(expans<<23)|(manans);


	return finalans;
}				
