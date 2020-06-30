#include <stdio.h>
#include <stdlib.h>
int cnt=0;// keeps the count of array level
int count_act;
struct pro
{
 float burst;
 float burst_cpy;
 int pro_no;
 float waiting_time;
};
int add(struct pro *point_arr,int count)
{
 printf("\nEnter 1 to add new hardware interrupts and 0 to continue: ");
 int choice, new_p,n,higher=0,lower =0;// new_p -> number of new process
 float new_higher[3], new_lower[3];
 float new_pro;
 int choice_prior;
 scanf("%d",&choice);
 switch(choice) // default choice is set to continue
 {
 case 0:
 new_p=0;
 break;
 case 1:
 printf("Enter the number of process to add: ");
 scanf("%d",&new_p);
 int n;
 for(n=0;n<new_p;n++)
 {
 printf("Enter the burst time of process%d: ",n+1);
 scanf("%f",&new_pro);
 printf("Enter the priority: "); // zero for low priority and 1 for high
 scanf("%d",&choice_prior);
 switch(choice_prior)// default choice is set to lower priority
 {
 case 0:
 new_lower[lower]= new_pro;
 lower++;
 break;
 case 1:
 new_higher[higher]= new_pro;
 higher++;
 break;
 default:
 new_lower[lower]= new_pro;
 lower++;
 break;
 }
 }
 break;
 default:
 new_p=0;
 break;
 }
 for (n=0;n<higher;n++)
 {
 ((point_arr+40*cnt+n)->burst)= new_higher[n];
 ((point_arr+40*cnt+n)->burst_cpy)=new_higher[n];
 ((point_arr+40*cnt+n)->pro_no)= n+count;
 ((point_arr+40*cnt+n)->waiting_time)=0;
 }
 for(n=0;n<count_act-1;n++)
 {
 ((point_arr+40*cnt+higher+n)->burst)=((point_arr+40*(cnt-1)+n+1)-
>burst);
 ((point_arr+40*cnt+higher+n)->burst_cpy)=((point_arr+40*(cnt-1)+n+1)-
>burst_cpy);
 ((point_arr+40*cnt+higher+n)->pro_no)= ((point_arr+40*(cnt-1)+n+1)-
>pro_no);
 ((point_arr+40*cnt+higher+n)->waiting_time)=((point_arr+40*(cnt1)+n+1)->waiting_time);
 }
 for(n=0;n<=lower;n++)
 {
 ((point_arr+40*cnt+count-1+higher+n)->burst)=new_lower[n];
 ((point_arr+40*cnt+count-1+higher+n)->burst_cpy)=new_lower[n];
 ((point_arr+40*cnt+count-1+higher+n)->pro_no)= count+higher+n;
 ((point_arr+40*cnt+count-1+higher+n)->waiting_time)=0;
 }
 for(n=count_act;n<count;n++)
 {
 ((point_arr+40*cnt+higher+lower+n)->burst)=((point_arr+40*(cnt-1)+n)-
>burst);
 ((point_arr+40*cnt+higher+lower+n)->burst_cpy)=((point_arr+40*(cnt1)+n)->burst_cpy);
 ((point_arr+40*cnt+higher+lower+n)->pro_no)=((point_arr+40*(cnt1)+n)->pro_no);
 ((point_arr+40*cnt+higher+lower+n)-
>waiting_time)=((point_arr+40*(cnt-1)+n)->waiting_time);
 }
 /*for(n=count_act;n<count;n++)
 {
 ((point_arr+40*cnt+higher+lower+n)->burst)=((point_arr+40*(cnt1)+count-count_act+n-1)->burst);
 ((point_arr+40*cnt+higher+lower+n)->burst_cpy)=((point_arr+40*(cnt1)+count-count_act+n-1)->burst_cpy);
 ((point_arr+40*cnt+higher+lower+n)->pro_no)=((point_arr+40*(cnt-
1)+count-count_act+n-1)->pro_no);
 ((point_arr+40*cnt+higher+lower+n)-
>waiting_time)=((point_arr+40*(cnt-1)+count-count_act+n-1)->waiting_time);
 }*/
 if (((point_arr+40*(cnt-1))->burst)!=0)
 {
 ((point_arr+40*cnt+higher+lower+count_act-1)->burst)=
((point_arr+40*(cnt-1))->burst);
 ((point_arr+40*cnt+higher+lower+count_act-1)-
>burst_cpy)=((point_arr+40*(cnt-1))->burst_cpy);
 ((point_arr+40*cnt+higher+lower+count_act-1)-
>pro_no)=((point_arr+40*(cnt-1))->pro_no);
 ((point_arr+40*cnt+count_act-1+higher+lower)-
>waiting_time)=((point_arr+40*(cnt-1))->waiting_time);
 count_act = count_act +new_p;
 }
 else
 {
 ((point_arr+40*cnt+higher+lower+count_act-1)->burst)=
((point_arr+40*(cnt-1))->burst);
 ((point_arr+40*cnt+higher+lower+count_act-1)-
>burst_cpy)=((point_arr+40*(cnt-1))->burst_cpy);
 ((point_arr+40*cnt+higher+lower+count_act-1)-
>pro_no)=((point_arr+40*(cnt-1))->pro_no);
 ((point_arr+40*cnt+count_act-1+higher+lower)-
>waiting_time)=((point_arr+40*(cnt-1))->waiting_time);
 count_act = count_act +new_p-1;
 }
 count+=new_p;
 return(count);
}
float tq (struct pro *point_arr, int count)//function to calculate time quantum
{
 int n;
 float tm_q=0;
 for(n=0;n<count;n++)
 {
 tm_q += ((point_arr+40*cnt+n)->burst);
 }
 tm_q = tm_q/count_act;
 return(tm_q);
}
int check(struct pro *point_arr, int count)
{
 int n,p;
 for(n=0;n<count;n++)
 {
 if(((point_arr+40*cnt+n)->burst)==0)
 {
 p=1;
 continue;
 }
 else
 {
 p=0;
 break;
 }
 }
 return(p);
}
int main()
{
 struct pro arr[40][40]; // array containing the process info
 struct pro *point_arr = &arr[0][0]; // pointer to the first element of the array
 int np; // initial number of process
 printf("Enter the number of initial processes: ");
 scanf("%d",&np);
 int n;
 for(n=0;n<np;n++)
 {
 printf("Enter the burst time of Process%d: ",n+1);
 scanf("%f",&arr[0][n].burst);
 arr[0][n].burst_cpy= arr[0][n].burst;
 arr[0][n].pro_no = n;
 arr[0][n].waiting_time = 0;
 }
 float tmq;// time- quantum
 int flag=0;
 int count = np;
 count_act= count;
 while (flag==0)
 {
 tmq = tq(point_arr,count);
 printf("\nTime quantum is %f",tmq);
 if(tmq<=((point_arr+40*cnt)->burst))
 {
 ((point_arr+40*cnt)->burst) = ((point_arr+40*cnt)->burst)-tmq;
 printf("\nProcess executed is Process%d",((point_arr+40*cnt)-
>pro_no)+1);
 //((point_arr+40*cnt)->waitnig_time)=((point_arr+40*cnt)-
>waitnig_time)+tmq;
 for(n=1;n<count;n++)
 {
 //printf("\n%f",((point_arr+40*cnt+n)->burst));
 if(((point_arr+40*cnt+n)->burst)!=0)
 {
 ((point_arr+40*cnt+n)->waiting_time)=(((point_arr+40*cnt+n)-
>waiting_time)+tmq) ;
 // printf("\n%f",((point_arr+40*cnt+n)->waiting_time));
 }
 }
 }
 else
 {
 ((point_arr+40*cnt)->burst)=0;
 printf("\nProcess%d went into starvation",((point_arr+40*cnt)-
>pro_no)+1);
 }
 cnt++;
 count = add(point_arr,count);
 flag = check(point_arr,count);
 }
 float twt,ttat;//total waitng time, totl turn around time
 //printf("count max = %d",cnt_max);
 printf("\n|Process|Burst Time |Waiting Time\t|T.A.T\t\t|");
 printf("\n---------------------------------------------------------");
 for(n=0;n<count;n++)
 {
 printf("\n|P%d\t| %f\t| %f\t| %f\t|",(((point_arr+40*cnt+n)-
>pro_no)+1),((point_arr+40*cnt+n)->burst_cpy),((point_arr+40*cnt+n)-
>waiting_time),(((point_arr+40*cnt+n)->waiting_time)+((point_arr+40*cnt+n)-
>burst_cpy)));
 twt+=((point_arr+40*cnt+n)->waiting_time);
 ttat+=((point_arr+40*cnt+n)->waiting_time)+((point_arr+40*cnt+n)-
>burst_cpy);
 }
 printf("\n---------------------------------------------------------");
 printf("\n|Total |\t\t|%f\t|%f\t|",twt,ttat);
 printf("\n\nAverage waiting time is: %f",twt/count);
 printf("\nAverage turn around time is: %f",ttat/count);
 printf("\n");
 return 0;
}
