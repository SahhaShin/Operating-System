//201734923 SHIN SANHA
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

void *cntPrime(void* start_num);
int count=0;
int num_10;
int main(int argc, char *argv[]){
	
	struct timespec tspec;
	int num=atoi(argv[1]);
	num_10=num/10;
	int thread_id;
	int status;
	
	//num
	int first_num=1;
	int second_num=num/10+1;
	int third_num=num/10*2+1;
	int fourth_num=num/10*3+1;
	int fifth_num=num/10*4+1;
	int sixth_num=num/10*5+1;
	int seventh_num=num/10*6+1;
	int eight_num=num/10*7+1;
	int nineth_num=num/10*8+1;
	int ten_num=num/10*9+1;
	
	//thread create

	pthread_t thread_a[10];
	
	sleep(1);
	
	double elapsed;
	
	
	clock_gettime(CLOCK_REALTIME,&tspec);
	elapsed=tspec.tv_sec;

	
	thread_id=pthread_create(&thread_a[0],NULL, cntPrime,(void*)&first_num);
	
	if(thread_id<0){
		perror("1 thread create error\n");
		exit(0);
	}
	

	
	
	thread_id=pthread_create(&thread_a[1],NULL, cntPrime,(void*)&second_num);
	if(thread_id<0){
		perror("2 thread create error\n");
		exit(0);
	}
		

	
	
	thread_id=pthread_create(&thread_a[2],NULL, cntPrime,(void*)&third_num);
	if(thread_id<0){
		perror("3 thread create error\n");
		exit(0);
	}
	
	
	
	
	thread_id=pthread_create(&thread_a[3],NULL, cntPrime,(void*)&fourth_num);
	if(thread_id<0){
		perror("4 thread create error\n");
		exit(0);
	}
	
	
	
	
	thread_id=pthread_create(&thread_a[4],NULL, cntPrime,(void*)&fifth_num);
	if(thread_id<0){
		perror("5 thread create error\n");
		exit(0);
	}
	

	
	
	thread_id=pthread_create(&thread_a[5],NULL, cntPrime,(void*)&sixth_num);
	if(thread_id<0){
		perror("6 thread create error\n");
		exit(0);
	}
	

	
	
	thread_id=pthread_create(&thread_a[6],NULL, cntPrime,(void*)&seventh_num);
	if(thread_id<0){
		perror("7 thread create error\n");
		exit(0);
	}
	
	
	
	
	thread_id=pthread_create(&thread_a[7],NULL, cntPrime,(void*)&eight_num);
	if(thread_id<0){
		perror("8 thread create error\n");
		exit(0);
	}
	

	
	
	thread_id=pthread_create(&thread_a[8],NULL, cntPrime,(void*)&nineth_num);
	if(thread_id<0){
		perror("9 thread create error\n");
		exit(0);
	}
	

	
	
	thread_id=pthread_create(&thread_a[9],NULL, cntPrime,(void*)&ten_num);
	if(thread_id<0){
		perror("10 thread create error\n");
		exit(0);
	}
	
	pthread_join(thread_a[0], NULL);
	pthread_join(thread_a[1], NULL);
	pthread_join(thread_a[2], NULL);
	pthread_join(thread_a[3], NULL);
	pthread_join(thread_a[4], NULL);
	pthread_join(thread_a[5], NULL);
	pthread_join(thread_a[6], NULL);
	pthread_join(thread_a[7], NULL);
	pthread_join(thread_a[8], NULL);
	pthread_join(thread_a[9], NULL);

	clock_gettime(CLOCK_REALTIME,&tspec);
	
	elapsed=tspec.tv_sec-elapsed;

	printf("elapsed time: %lf sec\n",elapsed);

	printf("The number of prime numbers %d~%d is %d\n",1,num,count);
	return 0;
}

void *cntPrime(void* num_start)
{
    int cnt = 0;
    int i;
    int j;
    int num_end=*(int *)num_start+num_10;
    
    

    for(j=*(int *)num_start;j<num_end;j++){
	

	if (j < 2) continue;
    	for (i=1; i*i<j; i++) {
        	if (j%i == 0) cnt++;
    	}
    	if (i*i == j) cnt++;
    	if (cnt == 1){
		count++;
                
		
	}
	cnt=0;
    	
    }
    	
    
}


