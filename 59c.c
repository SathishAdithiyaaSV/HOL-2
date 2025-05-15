/* Program Number: 59c
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program catches SIGFPE (Floating Point Exception) signal using signal system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int signum)
{
    printf("Caught SIGFPE (Floating Point Exception) signal!\n");
}

int main()
{
    signal(SIGFPE, handler);
    
    int a = 1;
    int b = 0;
    
    // This will cause a floating point exception (division by zero)
    printf("Result: %d\n", a / b);
    
    return 0;
}
