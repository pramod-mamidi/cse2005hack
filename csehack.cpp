#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>
#include<string.h>
#define DAY 1
#define MONTH 1
#define YEAR 2018
using namespace std;
struct waiting_times
{
 char s[50];
 float wt;
}fwt[4];
struct process
{
int at,bt,pr,pno;
};
struct Date
{
 int d, m, y;
};
const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int countLeapYears(Date d)
{
 int years = d.y;
 if (d.m <= 2)
 years--;
 return years / 4 - years / 100 + years / 400;
}
bool isLeap(int y)
{
 if (y%100 != 0 && y%4 == 0 || y %400 == 0)
 return true;
 return false;
}
int offsetDays(int d, int m, int y)
{
 int offset = d;
 switch (m - 1)
 {
 case 11:
 offset += 30;
 case 10:
 offset += 31;
 case 9:
 offset += 30;
 case 8:
 offset += 31;
 case 7:
 offset += 31;
 case 6:
 offset += 30;
 case 5:
 offset += 31;
 case 4:
 offset += 30;
 case 3:
 offset += 31;
 case 2:
 offset += 28;
 case 1:
 offset += 31;
 }
 if (isLeap(y) && m > 2)
 offset += 1;
 return offset;
}
void revoffsetDays(int offset, int y, int *d, int *m)
{
 int month[13] = { 0, 31, 59, 90, 120, 151, 181,
 212, 243, 273, 304, 334, 365 };
 if (isLeap(y))
 month[2] = 29;
 int i;
 for (i = 1; i <= 12; i++)
 {
 if (offset <= month[i])
 break;
 offset = offset - month[i];
 }
 *d = offset;
 *m = i;
}
int getDifference(Date dt1, Date dt2)
{
 long int n1 = dt1.y*365 + dt1.d;
 for (int i=0; i<dt1.m - 1; i++)
 n1 += monthDays[i];
 n1 += countLeapYears(dt1);
 long int n2 = dt2.y*365 + dt2.d;
 for (int i=0; i<dt2.m - 1; i++)
 n2 += monthDays[i];
 n2 += countLeapYears(dt2);
 return (n2 - n1);
}
int date_days(Date dt2)
{
 Date dt1={1, 1, 2018};
 return getDifference(dt1, dt2);
}
void days_date(int x)
{
 int offset1 = offsetDays(DAY, MONTH, YEAR);
 int remDays = isLeap(YEAR)?(366-offset1):(365-offset1);
 int y2, offset2=offset1;
 if (x <= remDays)
 {
 y2 = YEAR;
 offset2 += x;
 }
 else
 {
 x -= remDays;
 y2 = YEAR + 1;
 int y2days = isLeap(y2)?366:365;
 while (x >= y2days)
 {
 x -= y2days;
 y2++;
 y2days = isLeap(y2)?366:365;
 }
 offset2 = x;
 }
 int m2, d2;
 revoffsetDays(offset2, y2, &d2, &m2);
 cout <<d2<<":"<<m2<<":"<<y2;
}
//FCFS
void F_findWaitingTime(int processes[], int n, int bt[], int wt[], int at[])
{
 int service_time[n];
 service_time[0] = 0;
 wt[0] = 0;
 for (int i = 1; i < n ; i++)
 {
 service_time[i] = service_time[i-1] + bt[i-1];
 wt[i] = service_time[i] - at[i];
 if (wt[i] < 0)
 wt[i] = 0;
 }
}
void F_findTurnAroundTime(int processes[], int n, int bt[], int wt[],
 int tat[])
{
 for (int i = 0; i < n ; i++)
 tat[i] = bt[i] + wt[i];
}
void F_findavgTime(int processes[], int n, int bt[], int at[])
{
 int wt[n], tat[n], compl_time[n];
 F_findWaitingTime(processes, n, bt, wt, at);
 // Display processes along with all details
 cout << "Trip " << " Trip Time " << " Start Date "<<
 " Completion Date " << " Waiting Time \n";
 int total_wt = 0;
 for (int i = 0 ; i < n ; i++)
 {
 total_wt = total_wt + wt[i];
 cout << " " << i+1 << " \t " << bt[i]<<"\t ";
 days_date(at[i]+wt[i]);
 cout<<" \t ";
 days_date(wt[i]+bt[i]+at[i]);
 cout<<"\t " << wt[i] << "\t ";
 cout<< endl;
 }
 cout << "\nAverage waiting time = "
 << (float)total_wt / (float)n;
 strcpy(fwt[0].s,"First Come First Serve");
 fwt[0].wt= (float)total_wt / (float)n;
 cout<<"\n\n";
}
//SJF
void Snew_findavgTime(int at[], int bt[], int n)
{
 int i,p[10]={1,2,3,4,5,6,7,8,9,10},min,k=1,btime=0;
 int temp,j,wt[10],tt[10],ta=0,sum=0;
 float wavg=0,tavg=0,tsum=0,wsum=0;
 for(i=0;i<n;i++)
 {
 for(j=0;j<n;j++)
 {
 if(at[i]<at[j])
 {
 temp=p[j];
 p[j]=p[i];
 p[i]=temp;
 temp=at[j];
 at[j]=at[i];
 at[i]=temp;
 temp=bt[j];
 bt[j]=bt[i];
 bt[i]=temp;
 }
 }
 }
 for(j=0;j<n;j++)
 {
 btime=btime+bt[j];
 min=bt[k];
 for(i=k;i<n;i++)
 {
 if (btime>=at[i] && bt[i]<min)
 {
 temp=p[k];
 p[k]=p[i];
 p[i]=temp;
 temp=at[k];
 at[k]=at[i];
 at[i]=temp;
 temp=bt[k];
 bt[k]=bt[i];
 bt[i]=temp;
 }
 }
 k++;
 }
 wt[0]=0;
 for(i=1;i<n;i++)
 {
 sum=sum+bt[i-1];
 wt[i]=sum-at[i];
 wsum=wsum+wt[i];
 }
 wavg=(wsum/n);
 for(i=0;i<n;i++)
 {
 ta=ta+bt[i];
 tt[i]=ta-at[i];
 tsum=tsum+tt[i];
 }
 tavg=(tsum/n);
 cout << "Trip " << " Trip Time " << " Start Date "<<
 " Completion Date " << " Waiting Time \n";
 for (int i = 0 ; i < n ; i++)
 {
 cout << " " << p[i] << " \t " << bt[i] << "\t ";
 days_date(at[i]+wt[i]);
 cout<<" \t ";
 days_date(bt[i]+wt[i]);
 cout<<"\t " << wt[i] << "\t ";
 cout<< endl;
 }
 cout << "\nAverage waiting time = "<< wavg <<endl;
 strcpy(fwt[1].s,"Shortest Job First");
 fwt[1].wt=wavg;
 cout<<"\n\n";
}
//Priority
bool comp(process a,process b)
{
if(a.at == b.at)
{
return a.pr<b.pr;
}
else
{
 return a.at<b.at;
}
}
// Using FCFS Algorithm to find Waiting time
void get_wt_time(process proc[], int wt[], int totalprocess)
{
 int service[50];
 service[0]=0;
 wt[0]=0;
 for(int i=1;i<totalprocess;i++)
 {
 service[i]=proc[i-1].bt+service[i-1];
 wt[i]=service[i]-proc[i].at+1;
 if(wt[i]<0)
 {
 wt[i]=0;
 }
 }
}
void get_tat_time(process proc[], int tat[],int wt[], int totalprocess)
{
for(int i=0;i<totalprocess;i++)
{
 tat[i]=proc[i].bt+wt[i];
}
}
void P_findavgTime(process proc[], int totalprocess, int choice)
{
//Declare waiting time and turnaround time array
int wt[50],tat[50];
double wavg=0,tavg=0;
get_wt_time(proc, wt, totalprocess);
get_tat_time(proc, tat,wt, totalprocess);
int stime[50],ctime[50];
stime[0]=0;
ctime[0]=stime[0]+tat[0];
// calculating starting and ending time
for(int i=1;i<totalprocess;i++)
 {
 stime[i]=ctime[i-1];
 ctime[i]=proc[i].at+proc[i].bt+wt[i];
 }
cout << "Trip " << " Trip Time " <<"Priority"<< " Start Date "<<
 " Completion Date " << " Waiting Time \n";
for(int i=0;i<totalprocess;i++)
 {
 wavg += wt[i];
 cout<<" "<<proc[i].pno<<" \t "<<proc[i].bt<<" \t "<<
 proc[i].pr<<" ";
 days_date(stime[i]);
 cout<<"\t ";
 days_date(ctime[i]);
 cout<<"\t "<<wt[i]<<"\n"<<endl;
 }
 cout<<"Average waiting time is : ";
 cout<<wavg/(float)totalprocess<<endl;
 if(!choice)
 {
 strcpy(fwt[2].s,"Priority Scheduling");
 fwt[2].wt=wavg/(float)totalprocess;
 }
 else
 {
 strcpy(fwt[3].s,"Random Scheduling");
 fwt[3].wt=wavg/(float)totalprocess;
 }
 cout<<"\t\t"<<endl;
 }
 int main()
 {
 srand(time(0));
 int number;
 printf("Welcome to Smart Scheduling System\n\n");
 printf("Enter the number of trips you want to schedule : ");
 scanf("%d", &number );
 cout<<"\n";
 int choice, m, i, tr_time[number], processes[number],
 burst_time[number];
 Date dt[number];
 for(m=0; m<number; m++)
 {
 cout<<"Trip"<<m+1<<"\n"<<endl;
 printf("Enter the Booking Date (dd-mm-year) : ");
 scanf("%d-%d-%d", &dt[m].d, &dt[m].m, &dt[m].y);
 cout<<"Enter the Travel time of your trip : ";
 cin>>tr_time[m];
 cout<<"\n\n";
 }
 do
 {
 cout<<"***********************************************"<<endl;
 cout<<"\nSCHEDULE TYPE"<<endl;
 cout<<"Press 1 : First come first Serve"<<endl;
 cout<<"Press 2 : Shortest Job first"<<endl;
 cout<<"Press 3 : Priority"<<endl;
 cout<<"Press 4 : Random"<<endl;
 cout<<"Press 5 : Compare Wait times"<<endl;
 cout<<"Press 6 : Exit "<<endl;
 cout<<"Enter your choice : ";
 cin>>choice;
 cout<<"\n";
 switch(choice)
 {
 case 1://FCFS
 {
 cout<< "First Come First Serve\n"<<endl;
 int farrival_time[number];
 for(i=0; i<number; i++)
 {
 processes[i]=i;
 burst_time[i]=tr_time[i];
 farrival_time[i]=date_days(dt[i]);
 }
 F_findavgTime(processes, number, burst_time, farrival_time);
 break;
 }
 case 2://SJF
 {
 cout<<" Shortest Job First\n\n"<<endl;
 int snbt[number], snat[number];
 for(i=0; i<number; i++)
 {
 snat[i]=date_days(dt[i]);
 snbt[i]=tr_time[i];
 }
 Snew_findavgTime(snat, snbt, number);
 break;
 }
 case 3://Priority
 {
 cout<<"Priority Scheduling\n"<<endl;
 process proc[number];
 for(i=0; i<number; i++)
 {
 proc[i].at=date_days(dt[i]);
 proc[i].bt=tr_time[i];
 cout<<"Enter the Priority of Process "<<i+1<<" : ";
 cin>>proc[i].pr;
 proc[i].pno=i+1;
 }
 sort(proc,proc+number,comp);
 P_findavgTime(proc, number,0);
 break;
 }
 case 4://Random Scheduling
 {
 cout<<"Random Scheduling\n"<<endl;
 process pproc[number];
 int ppriority[number];
 for(i=0; i<number; i++)
 ppriority[i]=i+1;
 for(i=0; i<number; i++)
 {
 pproc[i].at=date_days(dt[i]);
 pproc[i].bt=tr_time[i];
 cout<<"Random entry of Priorities\n\n ";
 pproc[i].pr=(ppriority)[rand() % number];
 pproc[i].pno=i+1;
 }
 sort(pproc,pproc+ number,comp);
 P_findavgTime(pproc,number,1);
 break;
 }
 case 5:
 {
 cout<<"\tAlgorithm\t\t"<<"Waiting Time\n";
 for(i=0;i<4;i++)
 {
 cout<<fwt[i].s<<"\t ";
 cout<<fwt[i].wt;
 cout<<"\n";
 }
 break;
 }
 case 6:
 exit(1);
 }
 }while(choice < 5);
}
