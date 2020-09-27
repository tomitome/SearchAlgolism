#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>

int main(){
	struct timeval s;
	gettimeofday(&s,NULL);
    printf("%lf\n",(s.tv_sec) + (s.tv_usec)*1.0E-6);

}