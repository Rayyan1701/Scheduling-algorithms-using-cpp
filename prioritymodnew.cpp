#include<iostream>
using namespace std;
int n;
int i,j;
class priority: public process
{
    int bt[20],p[20],wt[20],tat[20],pr[20];
    public:
        void calculate_CT();
        void display();
        void get_process();
        // void arrange_arrival()
        // {

        // }

        friend ostream& operator<<(ostream &out,priority obj);
        friend istream& operator>>(istream &in,priority obj);
};
void swap(int *x,int *y)
{
    int temp=*x;
    *x=*y;
    *y=temp;
}
void priority::calculate_CT()
{
    int pos,temp;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(pr[j]>pr[j+1])
            {
                swap(&pr[j],&pr[j+1]);
                swap(&bt[j],&bt[j+1]);
                swap(&p[j],&p[j+1]);
            }
        }
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




/*void priority::display()
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
}*/
ostream &operator<<(ostream &out,priority obj)
{
    float avg_wt,avg_tat,total;
    for(i=1;i<n;i++)
    {
        obj.wt[i]=0;
        for(j=0;j<i;j++)
            obj.wt[i]=obj.wt[i]+obj.bt[j];
 
        total=total+obj.wt[i];
    }
    avg_wt=total/n;      
    total=0;
    cout<<"\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
    for(i=0;i<n;i++)
    {
        obj.tat[i]=obj.bt[i]+obj.wt[i];     
        total=total+obj.tat[i];
        cout<<"\nP["<<obj.p[i]<<"]\t\t  "<<obj.bt[i]<<"\t\t    "<<obj.wt[i]<<"\t\t\t"<<obj.tat[i];
    }
 
    avg_tat=total/n;     
    cout<<"\n\nAverage Waiting Time="<<avg_wt;
    cout<<"\nAverage Turnaround Time="<<avg_tat;
    return out;
}
int main()
{
    priority obj;
    cout<<"Enter the number of processes\t";
    cin>>n;
    obj.get_process();
    obj.calculate_CT();
    cout<<obj;
    return 0;
}