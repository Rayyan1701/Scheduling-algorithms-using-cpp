#include<iostream>

using namespace std;

#include "FCFS.cpp"
#include "sjfmodnew.cpp"
#include "prioritymodnew.cpp"
#include "rounrobinnew.cpp"

int id,at,bt,pr;

class process
{
    public:
    virtual void calculate_CT()=0;
    virtual void arrange_arrival()=0;
    virtual void calculate_TAT_WT()=0;
    virtual void display()=0;


    void read(process **p)
{
    
    FCFS_Process fcfs[10];
    rr_process rr[10];
    sjf_process sjf;
    priority prio;
      for (int i = 0; i < n; i++)
      {
            cout << "Enter Process ID   :";
        cin >> id;
        sjf.mat[i][0]=id;
        rr[i].process_id=id;
        fcfs[i].FCFS_process_id=id;
        prio.p[i]=i+1;
       
        cout << "Enter Arrival time :";
        cin >> at;
        fcfs[i].arrival_time=at;
        rr[i].arrival_time=at;
        sjf.mat[i][1]=at;
        
        
        cout << "Enter Burst time   :";
        cin >> bt;
        fcfs[i].burst_time=bt;
        rr[i].burst_time=bt;
        sjf.mat[i][2]=bt;
        prio.bt[i]=bt;
       
        cout<<"Enter priority  :";
        cin>>prio.pr[i];
        

      }
      
        
       p[0]=fcfs;
    p[1]=rr;
    p[2]=&sjf;
    p[3]=&prio;
       
        
       


}
    
};


int main()
{

}

