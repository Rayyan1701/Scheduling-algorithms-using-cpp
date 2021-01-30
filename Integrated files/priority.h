#include<iostream>
using namespace std;
int priority_n;
int i,j;
class priority
{
   
    int bt[20],p[20],wt[20],tat[20],pr[20];
    static float avg_tat;
    static float avg_wt;
        public:
        friend void readmain();
        void calculate_CT();
        void display();
        void get_process();
        
         
        friend ostream& operator<<(ostream &out,priority obj);
        friend istream& operator>>(istream &in,priority obj);
        friend void claculatemain();
        friend void calculatebestmain();
        friend void randinputmain();
     
};
float priority::avg_tat=0;
float priority::avg_wt=0;

void priority_swap(int *x,int *y)
{
    int temp=*x;
    *x=*y;
    *y=temp;
}
void priority::calculate_CT()
{
    int pos,temp;
    for(i=0;i<priority_n-1;i++)
    {
        for(j=0;j<priority_n-i-1;j++)
        {
            if(pr[j]>pr[j+1])
            {
                priority_swap(&pr[j],&pr[j+1]);
                priority_swap(&bt[j],&bt[j+1]);
                priority_swap(&p[j],&p[j+1]);
            }
        }
    }
    wt[0]=0;     
}
void priority::get_process()
{
    cout<<"\nEnter Burst Time and Priority\n";
    for(i=0;i<priority_n;i++)
    {
        cout<<"\nP["<<i+1<<"]\n";
        cout<<"Burst Time:";
        cin>>bt[i];
        cout<<"Priority:";
        cin>>pr[i];
        p[i]=i+1;           
    }
}




/*void priority::display()
{
    float avg_wt,avg_tat,total;
    for(i=1;i<priority_n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]=wt[i]+bt[j];
 
        total=total+wt[i];
    }
    avg_wt=total/priority_n;      
    total=0;
    cout<<"\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
    for(i=0;i<priority_n;i++)
    {
        tat[i]=bt[i]+wt[i];     
        total=total+tat[i];
        cout<<"\nP["<<p[i]<<"]\t\t  "<<bt[i]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
    }
 
    avg_tat=total/priority_n;     
    cout<<"\n\nAverage Waiting Time="<<avg_wt;
    cout<<"\nAverage Turnaround Time="<<avg_tat;
}*/
ostream &operator<<(ostream &out,priority obj)
{
    float total=0;
    for(i=1;i<priority_n;i++)
    {
        obj.wt[i]=0;
        for(j=0;j<i;j++)
            obj.wt[i]=obj.wt[i]+obj.bt[j];
 
        total=total+obj.wt[i];
    }
    priority::avg_wt=total/priority_n;      
    total=0;
    cout<<"\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
    for(i=0;i<priority_n;i++)
    {
        obj.tat[i]=obj.bt[i]+obj.wt[i];     
        total=total+obj.tat[i];
        cout<<"\nP["<<obj.p[i]<<"]\t\t  "<<obj.bt[i]<<"\t\t    "<<obj.wt[i]<<"\t\t\t"<<obj.tat[i];
    }
 
    priority::avg_tat=total/priority_n;     

    cout<<"\n\nAverage Waiting Time="<<priority::avg_wt;
    cout<<"\nAverage Turnaround Time="<<priority::avg_tat;
    return out;
}