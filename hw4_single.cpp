//201734923 SHIN SANHA
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

bool cntPrime(int num);

int main(int argc, char *argv[]){
	
	struct timespec tspec;
	int num=atoi(argv[1]);
	
	
	double elapsed;
	
	
	int count=0;
	int i=1;
	
	clock_gettime(CLOCK_REALTIME,&tspec);
	elapsed=tspec.tv_sec;
	
	
	while(i!=num+1){
		
		if(cntPrime(i)){

			count++;
			i++;
			
			continue;
		}
		i++;
	}
	
	clock_gettime(CLOCK_REALTIME,&tspec);
	
	elapsed=tspec.tv_sec-elapsed;
	

	printf("elapsed time: %lf sec\n",elapsed); 

	printf("The number of prime numbers %d~%d is %d\n",1,num,count);
	return 0;


}
bool cntPrime(int num)
{
    int cnt = 0;
    int i;
    if (num < 2) return false;

    for (i=1; i*i<num; i++) {
        if (num%i == 0) cnt++;
    }
    if (i*i == num) cnt++;
    if (cnt == 1) return true;
    else return false;
}


