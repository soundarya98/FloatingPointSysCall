#ifndef __ADD_WRAPPER_H_
#define __ADD_WRAPPER_H_
#define add_syscall(inum1,inum2) syscall(434,inum1,inum2)
#endif

float cwrapperfunc(float num1, float num2);
