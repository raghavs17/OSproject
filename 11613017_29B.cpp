#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
struct requests
{
       int p,arrival,burst,waiting,turnaround,remaining;
};


void sortarrival(struct requests a[],int pro)
{
       int i,j;
       struct requests temp;
       for(i=0;i<pro;i++)
       {
              for(j=i+1;j<pro;j++)
              {
                     if(a[i].arrival > a[j].arrival)
                     {
                           temp = a[i];
                           a[i] = a[j];
                           a[j] = temp;
                     }
              }
       }
       return;
}
int roundr(struct requests x[],int pros)
{
	int i,j,time,remains,flag=0,ts;
       float avgwait=0,avgturn=0;
	pros=pros+1;
       remains=pros;
       sortarrival(x,pros);
       printf("Enter Time Slice Number : ");
       scanf("%d",&ts);
       printf("\n***************************************\n");
       printf("             Gantt Chart\n");
       printf("\n***************************************\n");
       printf("0");
       for(time=0,i=0;remains!=0;)
       {
              if(x[i].remaining<=ts && x[i].remaining>0)
              {
                     time = time + x[i].remaining;
                     printf(" -> [P%d] <- %d",x[i].p,time);
                     x[i].remaining=0;
                     flag=1;
              }
              else if(x[i].remaining > 0)
              {
                     x[i].remaining = x[i].remaining - ts;
                     time = time + ts;
                     printf(" -> [P%d] <- %d",x[i].p,time);
              }
              if(x[i].remaining==0 && flag==1)
              {
                     remains--;
                     x[i].turnaround = time-x[i].arrival;
                     x[i].waiting = time-x[i].arrival-x[i].burst;
                     avgwait = avgwait + time-x[i].arrival-x[i].burst;
                     avgturn = avgturn + time-x[i].arrival;
                     flag=0;
              }
              if(i==pros-1)
                     i=0;
              else if(x[i+1].arrival <= time)
                     i++;
              else
                     i=0;
       }
       printf("\n\n");
       printf("*****************************************\n");
       printf("Proc   Arrival  Burst   TAround   Waiting\n");
       printf("*****************************************\n");
       for(i=0;i<pros;i++)
       {
              printf("P%d\t%d\t%d\t%d\t%d\n",x[i].p,x[i].arrival,x[i].burst,x[i].turnaround,x[i].waiting);
       }
       printf("*****************************************\n");
       avgwait = avgwait/pros;
       avgturn = avgturn/pros;
       printf("Average Waiting Time : %.2f\n",avgwait);
       printf("Average Turnaround Time : %.2f\n",avgturn);
}
int main()
{
	SYSTEMTIME st = {0}, str_t = {0};
	GetSystemTime(&st);
	SystemTimeToTzSpecificLocalTime(NULL, &st, &str_t);
	if(str_t.wHour==10)
	{
		system("cls");
       int i,j,time,remain,flag=0,ts;
       struct requests student[100],faculty[100];
       float avgwait=0,avgturn=0;
       int pros=-1,prof=-1,id;
       ch:
    {	system("cls");
		printf("Enter Mode (0 for Student And 1 for Faculty):");
    	scanf("%d",&id);
    	if(id==0)
    	{pros++;
    	printf("Enter Arrival Time and Burst Time of the Request: S%d : \n",pros+1);
    	scanf("%d%d",&student[pros].arrival,&student[pros].burst);
    	student[pros].p = pros;
        student[pros].remaining = student[pros].burst;
        if(student[pros].arrival>120 ||student[pros].burst<=0 ||student[pros].arrival<0 )
        {pros--;}
		}
		else if(id==1)
		{prof++;
    	printf("Enter Arrival Time and Burst Time of the Request: P%d : \n",prof+1);
    	scanf("%d%d",&faculty[prof].arrival,&faculty[prof].burst);
    	faculty[prof].p = prof;
        faculty[prof].remaining = faculty[prof].burst;
        if(faculty[prof].arrival>120 ||faculty[prof].burst<=0 ||faculty[prof].arrival<0)
        {prof--;}
		}
		else
		{printf("Wrong Input. Please Try Again.\n");goto ch;}
       mh:
       	{
       printf("Select an Option:\n");
       printf("1. Enter Another Request.\n");
       printf("2. Proceed to Round Robin.\n");
       int y;
       scanf("%d",&y);
		   switch(y)
	       {
	       	case 1:
	       		{goto ch;}
	       	case 2:
	       		{goto ch1;}
			default:
				{printf("Wrong Input. Please Try Again.\n");goto mh;}
		   }
   		}
   	}
      ch1:{
      	if(pros>1)
	{printf("Student\n");
	roundr(student,pros);}
	      else
		{printf("No. of processes is less than 2");}
	if(prof>1)
	{printf("Faaculty\n");
	roundr(faculty,prof);}
	      else
		{printf("No. of processes is less than 2");}
      	}
      }
    else
    {printf("This System Can Only be Used Between 10am-12noon.\n Please Try Again Later.");
	}
}


