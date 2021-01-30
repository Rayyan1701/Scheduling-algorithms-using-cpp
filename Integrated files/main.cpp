#include <iostream>
using namespace std;
#include<cstdlib>
#include "FCFS.h"
#include "priority.h"
#include "roundrobin.h"
#include "sjf.h"
int n;
// class process
// {
//     public:
//     virtual void calculate_CT()=0;
//     virtual void arrange_arrival()=0;
//     virtual void calculate_TAT_WT()=0;
//     virtual void display()=0;
//     friend void read(process **p);
// };
int id, at, bt, pr;
FCFS_Process fcfs[10];
rr_process rr[10];
sjf_process sjf;
priority prio;
void readmain()
{

    for (int i = 0; i < n; i++)
    {
        cout << "Enter Process ID   :";
        cin >> id;
        sjf.mat[i][0] = id;
        rr[i].process_id = id;
        fcfs[i].FCFS_process_id = id;
        prio.p[i] = i + 1;

        cout << "Enter Arrival time :";
        cin >> at;
        fcfs[i].arrival_time = at;
        rr[i].arrival_time = at;
        sjf.mat[i][1] = at;

        cout << "Enter Burst time   :";
        cin >> bt;
        fcfs[i].burst_time = bt;
        rr[i].burst_time = bt; rr[i].dup_BT=bt;
        sjf.mat[i][2] = bt;
        prio.bt[i] = bt;

        cout << "Enter priority  :";
        cin >> prio.pr[i];
    }
}

void calculatemain()
{
    fcfs[0].arrange_arrival();
    rr[0].arrange_arrival();
    sjf.arrange_arrival();
    

    fcfs[0].calculate_CT();
    rr[0].calculate_CT();
    
    sjf.calculate_CT();
    prio.calculate_CT();

    fcfs[0].calculate_TAT_WT();
    rr[0].calculate_TAT_WT();

}

void calculatebestmain()
{
    int a,b,c,d;

    a=FCFS_Process::Avg_WT;
    b=rr_process::Avg_WT;
    c=sjf_process::avg_wt;
    d=priority::avg_wt;

    if (a>=b&&a>=c&&a>=d)
    {
        cout<<"\nFCFS is the most efficient algorithm for these processes "<<endl;
        cout<<"with Average wait time :"<<a<<"\n"<<endl;
    }
    else if (b>=a&&b>=c&&b>=d)
    {
        cout<<"\nRound robin is the most efficient algorithm for these processes"<<endl;
         cout<<"with Average wait time :"<<b<<"\n"<<endl;
    }
    else if (c>=b&&c>=a&&c>=d)
    {
        cout<<"\nShortest job first is the most efficient algorithm for these processes"<<endl;
         cout<<"with Average wait time :"<<c<<"\n"<<endl;
    }
    else if (d>=b&&d>=c&&d>=a)
    {
        cout<<"\nPriority scheduling is the most efficient algorithm for these processes"<<endl;
         cout<<"with Average wait time :"<<d<<"\n"<<endl;
    }
    

}

void randinputmain()
{
     for (int i = 0; i < n; i++)
    {
        id=i+1;
        sjf.mat[i][0] = id;
        rr[i].process_id = id;
        fcfs[i].FCFS_process_id = id;
        prio.p[i] = i + 1;

        at=rand()%n;
        fcfs[i].arrival_time = at;
        rr[i].arrival_time = at;
        sjf.mat[i][1] = at;

        bt=rand()%20;
        fcfs[i].burst_time = bt;
        rr[i].burst_time = bt; rr[i].dup_BT=bt;
        sjf.mat[i][2] = bt;
        prio.bt[i] = bt;

         prio.pr[i]=rand()%n;
    }
}


int main()
{
    int b=1;
    cout << "Enter the number of processes" << endl;
    cin >> n;
    fcfs_n=n;
    rr_n=n;
    priority_n=n;
    sjf_n=n;


    cout << "Enter the time quantumn for Round robin algorithm" << endl;
    cin >> q;

    cout << "Enter the process parameters " << endl;

    //readmain();
     randinputmain();
    calculatemain();



    // cout<<"FCFS process"<<endl;
    // cout << fcfs;
    // FCFS_Process::FCFS_display_average_TAT_WT();
    // cout<<"\n\n"<<endl;

    // cout<<"Round robin process"<<endl;
    // cout << rr;
    //  rr_process::roundrobin_display_average_TAT_WT();
    // cout<<"\n\n"<<endl; 

    // cout<<"Shortest job first process"<<endl;
    // cout <<sjf;
    // cout<<"\n\n"<<endl;

    // cout<<"Priority scheduling process"<<endl;
    // cout<<prio;
    // cout<<"\n\n"<<endl;


    while (b!=0)
    {
        cout<<"Enter 1 if you want to display results of FCFS algorithm"<<endl;
        cout<<"Enter 2 if you want to display results of Round robin algorithm"<<endl;
        cout<<"Enter 3 if you want to display results of Shortest job first algorithm"<<endl;
        cout<<"Enter 4 if you want to display results of Priority scheduling algorithm"<<endl;
        cout<<"Enter 5 to find the best suitable algorithm for these processes"<<endl;
        cin>>b;
        switch(b)
        {
            case 1: cout<<"FCFS process"<<endl;
                    cout << fcfs;
                    FCFS_Process::FCFS_display_average_TAT_WT();
                    cout<<"\n\n"<<endl;
                    break;

            case 2:cout<<"Round robin process"<<endl;
                   cout << rr;
                   rr_process::roundrobin_display_average_TAT_WT();
                   cout<<"\n\n"<<endl; 
                   break;

            case 3:cout<<"Shortest job first process"<<endl;
                   cout <<sjf;
                   cout<<"\n\n"<<endl;
                   break;

            case 4:cout<<"Priority scheduling process"<<endl;
                   cout<<prio;
                   cout<<"\n\n"<<endl;
                   break;

            case 5: calculatebestmain();
                    break;


        }



        cout<<"Enter 1 if you want to continue"<<endl;
        cin>>b;
    }
    
}
