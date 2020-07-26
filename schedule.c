//201734923_SHINSANHA
#include<stdio.h>


struct PCB{

	int pid;
   	int begin_tick;
   	int burst_tick;
   	int end_tick;
	int remain_tick;//use SRTF
	
};

int data=0;
int select;

struct PCB pcb[100];
int first_wait_tick[100];
int response[100];//enter fit begin_tick?



//////////////////////////////////////////////cal_end_tick()////////////////////////////////////////////////////////////
void cal_end_tick(){
	int stack_burst_time=pcb[0].begin_tick;
	if(select==1||select==2){
		//end_tick calulate - nonpreemptive
   		for(int i=0;i<data;i++){
			if((i!=0)&&(pcb[i].begin_tick-pcb[i-1].end_tick>1)){	
				pcb[i].end_tick=stack_burst_time+pcb[i].burst_tick+(pcb[i].begin_tick-pcb[i-1].end_tick);
				stack_burst_time=pcb[i].end_tick;
				
			}
			else{
      				pcb[i].end_tick=stack_burst_time+pcb[i].burst_tick;
      				stack_burst_time=pcb[i].end_tick;
      			}
   		}
	}
	
	else if(select==3){
		//end_tick calulate - preemptive
   		for(int i=0;i<data;i++){
			if((i!=0)&&(pcb[i].begin_tick-pcb[i-1].end_tick>1)){	
				pcb[i].end_tick=stack_burst_time+pcb[i].remain_tick+(pcb[i].begin_tick-pcb[i-1].end_tick);
				stack_burst_time=pcb[i].end_tick;
				
			}
			else{
      				pcb[i].end_tick=stack_burst_time+pcb[i].remain_tick;
      				stack_burst_time=pcb[i].end_tick;
      			}
   		}
	}

}


//////////////////////////////////////////////do_FCFS////////////////////////////////////////////////////////////
void do_FCFS(){

   	struct PCB temp;
   	
   	for(int i=0;i<data;i++){
      		for(int j=0;j<data-i-1;j++){
         			if(pcb[j].begin_tick>pcb[j+1].begin_tick){
            				temp=pcb[j];
            				pcb[j]=pcb[j+1];
            				pcb[j+1]=temp;
         			}
      		}
   	}
   	

}



//////////////////////////////////////////////do_SJF////////////////////////////////////////////////////////////
void do_SJF(){
   	struct PCB temp;
   
   	int k=0;
   	int check_order=0;
   	
   	//0 vs someone
   	for(int i=1;i<data;i++){
      		if(pcb[0].begin_tick+pcb[0].burst_tick<pcb[i].begin_tick){
         		check_order=i;//less than begin check
         		break;
      		}
   	}
   	//burst_tick~
   	for(int i=1;i<check_order;i++){
      		for(int j=1;j<check_order-i+1;j++){
         		if(pcb[j].burst_tick>pcb[j+1].burst_tick){
            			temp=pcb[j];
            			pcb[j]=pcb[j+1];
            			pcb[j+1]=temp;
         		}
      		}
   	}

   	for(int i=1;i<data-check_order-1;i++){
      		for(int j=check_order+1;j<data-i;j++){
         		if(pcb[j].burst_tick>pcb[j+1].burst_tick){
            			temp=pcb[j];
            			pcb[j]=pcb[j+1];
            			pcb[j+1]=temp;
         		}
      		}
   	}

}

//////////////////////////////////////////////do_SRTF////////////////////////////////////////////////////////////
void do_SRTF(){
   	struct PCB temp;
   
   	int k=0;
   	int check_order=0;
   	
   	//check_order-less than begin_tick
   	for(int i=1;i<data;i++){
      		if(pcb[0].begin_tick+pcb[0].remain_tick<pcb[i].begin_tick){
         		check_order=i;//less than begin_tick(OUT begin_tick)
         		break;
      		}
   	}
   	//burst_tick~ (IN begin_tick)
   	for(int i=1;i<check_order;i++){
      		for(int j=1;j<check_order-i+1;j++){
         		if(pcb[j].remain_tick>pcb[j+1].remain_tick){
            			temp=pcb[j];
            			pcb[j]=pcb[j+1];
            			pcb[j+1]=temp;
         		}
      		}
   	}
	
	//burst_tick~ (OUT begin_tick)
   	for(int i=1;i<data-check_order-1;i++){
      		for(int j=check_order+1;j<data-i;j++){
         		if(pcb[j].remain_tick>pcb[j+1].remain_tick){
            			temp=pcb[j];
            			pcb[j]=pcb[j+1];
            			pcb[j+1]=temp;
         		}
      		}
   	}

}


//////////////////////////////////////////////read_proc_list////////////////////////////////////////////////////////////
void read_proc_list(const char* file_name){

   	FILE* file=fopen(file_name,"r");

   	if(file==NULL)
      		printf("error open file\n");
   	else{
      		fscanf(file, "%d",&data);
      		
      		for(int i=0;i<data;i++){
         
         		fscanf(file, "%d %d %d",&pcb[i].pid,&pcb[i].begin_tick,&pcb[i].burst_tick);
			pcb[i].remain_tick=pcb[i].burst_tick;
      		}
      		if(select==1){
         		do_FCFS();
			cal_end_tick();
         	}
      
      		else if(select==2){
			do_FCFS();
         		do_SJF();
			cal_end_tick();
		}
      
      		else if(select==3){
			do_FCFS();
			
         		
			cal_end_tick();
         	}
         
   	}
      
}


//////////////////////////////////////////////set_schedule////////////////////////////////////////////////////////////
void set_schedule(int method){
   	//begin_tick
   	if(method==1){
      
      		select=1;
   	}
   	else if(method==2){     
      		select=2;
   	}  
   	else if(method==3){
      		select=3;
   	}        
}


//////////////////////////////////////////////do_schedule////////////////////////////////////////////////////////////
int do_schedule(int tick){
	
   	struct PCB temp;
	if(select==1||select==2){
		for(int i=0;i<data;i++){
      			if(pcb[i].begin_tick==tick){
				response[pcb[i].pid-1]=1;
				
         			return pcb[i].pid;
      			}
			else if((i!=data-1)&&(pcb[i].end_tick<=tick&&pcb[i+1].begin_tick>tick)){
				return 0;
			}
      			else if((pcb[i].end_tick-1>=tick)){
         			return pcb[i].pid;
			}
			
			
		}
      
   	}
	else if(select==3){
		for(int i=0;i<data;i++){
      			if(pcb[i].begin_tick==tick){
				
				response[pcb[i].pid-1]=1;
         			return pcb[i].pid;
      			}
			else if((i!=data-1)&&(pcb[i].end_tick<=tick&&pcb[i+1].begin_tick>tick)){
				return 0;
			}
      			else if(pcb[i].end_tick-1>=tick){
				//intercenpt other pcb
				if((tick==pcb[i+1].begin_tick)&&(pcb[i].end_tick-pcb[i+1].begin_tick>pcb[i+1].remain_tick)){
					if(first_wait_tick[pcb[i].pid]==0)first_wait_tick[pcb[i].pid]=tick;
					
					pcb[i].remain_tick=pcb[i].end_tick-pcb[i+1].begin_tick;
					temp=pcb[i];
            				pcb[i]=pcb[i+1];
            				pcb[i+1]=temp;
					do_SRTF(select);//re_order burst_tick~
					cal_end_tick();//re_calulation end_tick
										
				}
				
				if(pcb[i].begin_tick==tick){
					
					response[(pcb[i].pid)-1]=1;
					
				}
         			return pcb[i].pid;
			}
			
		}
		
	}
  	return -1; //all process terminate

}


//////////////////////////////////////////////print_performance////////////////////////////////////////////////////////////
void print_performance(){

   	float turn_total=0.0;
   	float wait_total=0.0;
   	float response_total=0.0;
	int response_each[100]={0,};
	
   	printf("\n\n=================================================================================================================\n");
   	printf("  PID\t  begin\t  finish\t  Turn around time\t  Waiting time\t  Response time  \n");
   	printf("=================================================================================================================\n");

	//////////////////////////////////////////////select==1,2 printf////////////////////////////////////////////////////////////
	if(select==1||select==2){
   		for(int i=0;i<data;i++){
      			if(i==0){
				
         			turn_total+=pcb[i].end_tick-pcb[i].begin_tick;
         			wait_total+=pcb[i].end_tick-pcb[i].begin_tick-pcb[i].burst_tick;
         			response_total+=pcb[i].begin_tick-pcb[i].begin_tick;
				response_each[pcb[i].pid-1]=pcb[i].begin_tick-pcb[i].begin_tick;
      			}
      			else{
				if(response[i]==1){
					response_total+=pcb[i].begin_tick-pcb[i].begin_tick;
					response_each[pcb[i].pid-1]=pcb[i].begin_tick-pcb[i].begin_tick;
					
				}
				else{
					response_total+=pcb[i-1].end_tick-pcb[i].begin_tick;
					response_each[pcb[i].pid-1]=pcb[i-1].end_tick-pcb[i].begin_tick;
				}	
         			turn_total+=pcb[i].end_tick-pcb[i].begin_tick;
         			wait_total+=pcb[i].end_tick-pcb[i].begin_tick-pcb[i].burst_tick;
         			

      			}

   		}
		do_FCFS();
		for(int i=0;i<data;i++){
      							
         		printf("   %d\t    %d\t    %d\t\t\t  %d\t\t     %d\t\t\t  %d\t  \n",pcb[i].pid,pcb[i].begin_tick,pcb[i].end_tick,pcb[i].end_tick-pcb[i].begin_tick,pcb[i].end_tick-pcb[i].begin_tick-pcb[i].burst_tick,response_each[i]);
      			

   		}
		
				
	}
	//////////////////////////////////////////////select==3 printf////////////////////////////////////////////////////////////
	else if(select==3){
		do_FCFS();
		for(int i=0;i<data;i++){
			if(i==0||response[i]==1){
				
				turn_total+=pcb[i].end_tick-pcb[i].begin_tick;
				wait_total+=pcb[i].end_tick-pcb[i].begin_tick-pcb[i].burst_tick;
				response_total+=pcb[i].begin_tick-pcb[i].begin_tick;
				
				printf("   %d\t    %d\t    %d\t\t\t  %d\t\t      %d\t\t\t  %d\t  \n",pcb[i].pid,pcb[i].begin_tick,pcb[i].end_tick,pcb[i].end_tick-pcb[i].begin_tick,pcb[i].end_tick-pcb[i].begin_tick-pcb[i].burst_tick,pcb[i].begin_tick-pcb[i].begin_tick);
			}
			else{
				
				turn_total+=pcb[i].end_tick-pcb[i].begin_tick;
				wait_total+=pcb[i].end_tick-pcb[i].begin_tick-pcb[i].burst_tick;
				
				response_total+=pcb[i].end_tick-pcb[i].burst_tick-pcb[i].begin_tick;
				
				printf("   %d\t    %d\t    %d\t\t\t  %d\t\t      %d\t\t\t  %d\t  \n",pcb[i].pid,pcb[i].begin_tick,pcb[i].end_tick,pcb[i].end_tick-pcb[i].begin_tick,pcb[i].end_tick-pcb[i].begin_tick-pcb[i].burst_tick,pcb[i].end_tick-pcb[i].burst_tick-pcb[i].begin_tick);
			}
		}
	}

   	printf("-----------------------------------------------------------------------------------------------------------------\n");
   	printf(" average:  \t  \t  \t  \t  %.2f\t\t      %.2f\t          %.2f\n",turn_total/data,wait_total/data,response_total/data);
   	printf("=================================================================================================================\n");


}
