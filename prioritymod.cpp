#include<iostream>
using namespace std;
int n,i,j;
class priority
{
    int bt[20],p[20],wt[20],tat[20],pr[20];
    public:
        void calc();
        void display();
        void get_process();
};
void priority::calc()
{
    int pos,temp;
    for(i=0;i<n;i++)
    {
        pos=i; 
        for(j=i+1;j<n;j++)
        {
            if(pr[j]<pr[pos])
                pos=j;
        }
 
        temp=pr[i];
        pr[i]=pr[pos];
        pr[pos]=temp;
 
        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;
 
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
    wt[0]=0;     
}
void priority::get_process()
{
    cout<<"\nEnter Burst Time and Priority\n";
    for(i=0;i<n;i++)
    {
        cout<<"\nP["<<i+1<<"]\n";
        cout<<"Burst Time:";
        cin>>bt[i];
        cout<<"Priority:";
        cin>>pr[i];
        p[i]=i+1;           
    }
}
void priority::display()
{
    float avg_wt,avg_tat,total;
    
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]=wt[i]+bt[j];
 
        total=total+wt[i];
    }
    avg_wt=total/n;      
    total=0;
    cout<<"\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];     
        total=total+tat[i];
        cout<<"\nP["<<p[i]<<"]\t\t  "<<bt[i]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
    }
 
    avg_tat=total/n;     
    cout<<"\n\nAverage Waiting Time="<<avg_wt;
    cout<<"\nAverage Turnaround Time="<<avg_tat;
}
int main()
{
    priority obj;
    cout<<"Enter the number of processes\t";
    cin>>n;
    obj.get_process();
    obj.calc();
    obj.display();
    return 0;
}