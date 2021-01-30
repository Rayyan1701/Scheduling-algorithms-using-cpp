#include <iostream>
#include <queue>
using namespace std;

int id, at, bt, pr;

class process
{
public:
     virtual void calculate_CT() = 0;
     virtual void arrange_arrival()=0;
     virtual void calculate_TAT_WT()=0;
     virtual void display()=0;

    friend void readmain(process **p);
};
int n;

int fcfs_n;

class FCFS_Process : public process
{

    int FCFS_process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int TAT;
    int wait_time;
    static float Avg_TAT;
    static float Avg_WT;

public:
    FCFS_Process(int id = 0, int bt = 0, int at = 0, int ct = 0, int tat = 0, int wt = 0)
    {
        FCFS_process_id = id;
        arrival_time = at;
        burst_time = bt;
        completion_time = ct;
        TAT = tat;
        wait_time = wt;
    }
    ~FCFS_Process() {}
    friend void claculatemain();
    friend void calculatebestmain();
    void arrange_arrival();
    void calculate_CT();
    void calculate_TAT_WT();
    void read();
    void display();
    FCFS_Process operator=(const FCFS_Process &obj);

    friend void readmain(process **p);
    friend void randinputmain(process **p);

    static void FCFS_display_average_TAT_WT()
    {
        cout << "Average Turn around time :" << Avg_TAT << endl;
        cout << "Average Wait time        :" << Avg_WT << endl;
    }

    friend ostream &operator<<(ostream &out, FCFS_Process *obj);
    friend istream &operator>>(istream &in, FCFS_Process obj);
};

float FCFS_Process::Avg_TAT = 0;
float FCFS_Process::Avg_WT = 0;

void FCFS_Process::arrange_arrival()
{
    for (int i = 0; i < fcfs_n - 1; i++)
    {
        for (int j = 0; j < fcfs_n - i - 1; j++)
        {
            FCFS_Process temp;
            if (this[j].arrival_time > this[j + 1].arrival_time)
            {
                temp = this[j];
                this[j] = this[j + 1];
                this[j + 1] = temp;
            }
        }
    }
}

void FCFS_Process::calculate_CT()
{
    for (int i = 0; i < fcfs_n; i++)
    {
        if (i == 0)
        {
            this[i].completion_time = this[i].arrival_time + this[i].burst_time;
        }
        else
        {

            if (this[i].arrival_time <= this[i - 1].completion_time)
            {
                this[i].completion_time = this[i - 1].completion_time + this[i].burst_time;
            }
            else
            {
                this[i].completion_time = this[i].arrival_time + this[i].burst_time;
            }
        }
    }
}

void FCFS_Process::calculate_TAT_WT()
{
    for (int i = 0; i < fcfs_n; i++)
    {
        this[i].TAT = this[i].completion_time - this[i].arrival_time;
        Avg_TAT += this[i].TAT;
    }
    Avg_TAT = Avg_TAT / fcfs_n;

    for (int i = 0; i < fcfs_n; i++)
    {
        this[i].wait_time = this[i].TAT - this[i].burst_time;
        Avg_WT += this[i].wait_time;
    }
    Avg_WT = Avg_WT / fcfs_n;
}

void FCFS_Process::read()
{
    cout << "Enter FCFS_Process ID   :";
    cin >> FCFS_process_id;
    cout << "Enter Arrival time :";
    cin >> arrival_time;
    cout << "Enter Burst time   :";
    cin >> burst_time;
}
ostream &operator<<(ostream &out, FCFS_Process *obj)
{
    cout << "FCFS_Process ID"
         << "\t"
         << "Arrival"
         << "\t\t"
         << "Burst time"
         << "\t"
         << "completion time"
         << "\t\t"
         << "Turn around time"
         << "\t"
         << "Wait time" << endl;
    for (int i = 0; i < fcfs_n; i++)
    {

        cout << obj[i].FCFS_process_id << "\t\t" << obj[i].arrival_time << "\t\t" << obj[i].burst_time << "\t\t" << obj[i].completion_time << "\t\t\t" << obj[i].TAT << "\t\t\t" << obj[i].wait_time << endl;
    }

    return out;
}
FCFS_Process FCFS_Process::operator=(const FCFS_Process &obj)
{
    FCFS_process_id = obj.FCFS_process_id;
    burst_time = obj.burst_time;
    completion_time = obj.completion_time;
    TAT = obj.TAT;
    arrival_time = obj.arrival_time;
    wait_time = obj.wait_time;
    return *this;
}

void FCFS_Process::display()
{
    cout<<"FCFS Process:-  "<<endl;
    cout << "FCFS_Process ID"
         << "\t"
         << "Arrival"
         << "\t\t"
         << "Burst time"
         << "\t"
         << "completion time"
         << "\t\t"
         << "Turn around time"
         << "\t"
         << "Wait time" << endl;
    for (int i = 0; i < fcfs_n; i++)
    {

        cout << this[i].FCFS_process_id << "\t\t" << this[i].arrival_time << "\t\t" << this[i].burst_time << "\t\t" << this[i].completion_time << "\t\t\t" << this[i].TAT << "\t\t\t" << this[i].wait_time << endl;
    }
    FCFS_Process::FCFS_display_average_TAT_WT();
    cout<<"\n\n"<<endl;
}

istream &operator>>(istream &in, FCFS_Process obj)
{
    cout << "Enter FCFS_Process ID   :";
    cin >> obj.FCFS_process_id;
    cout << "Enter Arrival time :";
    cin >> obj.arrival_time;
    cout << "Enter Burst time   :";
    cin >> obj.burst_time;

    return in;
}

//round robin
int rr_n;
int q;
class rr_process : public process
{

    int process_id;
    int arrival_time;
    int burst_time;
    int dup_BT;
    int completion_time;
    int TAT;
    int wait_time;
    static float Avg_TAT;
    static float Avg_WT;
    rr_process *next;

public:
    rr_process()
    {
        process_id = 0;
        burst_time = 0;
        arrival_time = 0;
        dup_BT = 0;
        completion_time = 0;
        TAT = 0;
        wait_time = 0;
        next = NULL;
    }
    ~rr_process() {}

    rr_process operator=(const rr_process &obj);

    void read();

    friend void claculatemain();
    friend void calculatebestmain();
    friend void randinputmain(process **p);

    void arrange_arrival();

    bool completed()
    {
        int y = 0;
        for (int i = 0; i < rr_n; i++)
        {
            if (this[i].dup_BT != 0)
            {
                y = 1;
            }
        }
        if (y == 1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void calculate_CT()
    {
        queue<rr_process> ready_queue;
        int sum = 0, j = 0, k;
        ready_queue.push(this[0]);

        // while (!this[0].completed(n)) //for some gaps in-between
        //    {
        sum = ready_queue.front().arrival_time;

        while (!ready_queue.empty()) //actual code starts from here
        {

            rr_process r = ready_queue.front();

            for (int i = 0; i < rr_n; i++)
            {
                if (this[i].process_id == r.process_id)
                {
                    k = i;
                    break;
                }
            }

            rr_process &p = this[k];
            
            if (p.dup_BT <= q && p.dup_BT > 0)
            {
                sum += p.dup_BT;
                p.dup_BT = 0;
                p.completion_time = sum;
                
                ready_queue.pop();
                if (sum <= this[rr_n - 1].arrival_time && ready_queue.empty()) //for gaps in gant chart
                {
                    
                    sum = this[k + 1].arrival_time;
                    ready_queue.push(this[k + 1]);
                }
            }
            else if (p.dup_BT > q)
            {
                sum += q;
                p.dup_BT -= q;

                //      if (this[n - 1].arrival_time >= sum) //only used until sum<=largest arrival time
                //     {

                for (int i = 0; i < rr_n; i++)
                {
                    if (this[i].arrival_time <= sum && this[i].process_id != p.process_id && this[i].arrival_time >= p.arrival_time && i > j)
                    {

                        ready_queue.push(this[i]);

                        j++;
                    }
                }

                //   }

                if (p.dup_BT > 0)
                {
                    ready_queue.push(p);
                }

                ready_queue.pop();
            }
        }
        // }
    }

    void calculate_TAT_WT()
    {
        for (int i = 0; i < rr_n; i++)
        {
            this[i].TAT = this[i].completion_time - this[i].arrival_time;
            Avg_TAT += this[i].TAT;
        }
        Avg_TAT = Avg_TAT / rr_n;

        for (int i = 0; i < rr_n; i++)
        {
            this[i].wait_time = this[i].TAT - this[i].burst_time;
            Avg_WT += this[i].wait_time;
        }
        Avg_WT = Avg_WT / rr_n;
    }

    void display()
    {
        cout<<"\n\nRound robin :-"<<endl;
        cout << "Process ID"
             << "\t"
             << "Arrival"
             << "\t\t"
             << "Burst time"
             << "\t"
             << "completion time"
             << "\t\t"
             << "Turn around time"
             << "\t"
             << "Wait time" << endl;
        for (int i = 0; i < rr_n; i++)
        {

            cout << this[i].process_id << "\t\t" << this[i].arrival_time << "\t\t" << this[i].burst_time << "\t\t" << this[i].completion_time << "\t\t\t" << this[i].TAT << "\t\t\t" << this[i].wait_time << endl;
        }
        cout<<"\n"<<endl;
        rr_process::roundrobin_display_average_TAT_WT();
        cout<<"\n\n"<<endl;
    }

    static void roundrobin_display_average_TAT_WT()
    {
        cout << "Average Turn around time :" << Avg_TAT << endl;
        cout << "Average Wait time        :" << Avg_WT << endl;
    }

    friend ostream &operator<<(ostream &out, rr_process *q);
    friend void readmain(process **p);
};
ostream &operator<<(ostream &out, rr_process *q)
{
    cout << "Process ID"
         << "\t"
         << "Arrival"
         << "\t\t"
         << "Burst time"
         << "\t"
         << "completion time"
         << "\t\t"
         << "Turn around time"
         << "\t"
         << "Wait time" << endl;
    for (int i = 0; i < rr_n; i++)
    {

        cout << q[i].process_id << "\t\t" << q[i].arrival_time << "\t\t" << q[i].burst_time << "\t\t" << q[i].completion_time << "\t\t\t" << q[i].TAT << "\t\t\t" << q[i].wait_time << endl;
    }

    return out;
}

rr_process rr_process::operator=(const rr_process &obj)
{
    process_id = obj.process_id;
    burst_time = obj.burst_time;
    arrival_time = obj.arrival_time;
    completion_time = obj.completion_time;
    TAT = obj.TAT;
    wait_time = obj.wait_time;
    dup_BT = obj.dup_BT;

    return *this;
}

void rr_process::read()
{
    cout << "Enter Process ID   :";
    cin >> process_id;
    cout << "Enter Arrival time :";
    cin >> arrival_time;
    cout << "Enter Burst time   :";
    cin >> burst_time;
    dup_BT = burst_time;
}

void rr_process::arrange_arrival()
{
    for (int i = 0; i < rr_n - 1; i++)
    {
        for (int j = 0; j < rr_n - i - 1; j++)
        {
            rr_process temp;
            if (this[j].arrival_time > this[j + 1].arrival_time)
            {
                temp = this[j];
                this[j] = this[j + 1];
                this[j + 1] = temp;
            }
        }
    }
}

float rr_process::Avg_TAT = 0;
float rr_process::Avg_WT = 0;

//sjf
int sjf_n;
class sjf_process : public process
{
    int mat[10][6];
    static float avg_tat;
    static float avg_wt;

public:
    void arrange_arrival();
    void calculate_CT();
    void get_sjf_process();
    //void display();
    friend ostream &operator<<(ostream &out, sjf_process obj);
    friend void readmain(process **p);
    void calculate_TAT_WT()
    {

    }
    void display();

    friend void claculatemain();
    friend void calculatebestmain();
    friend void randinputmain(process **p);
};
float sjf_process::avg_tat = 0;
float sjf_process::avg_wt = 0;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void sjf_process::arrange_arrival()
{
    for (int i = 0; i < sjf_n; i++)
    {
        for (int j = 0; j < sjf_n - i - 1; j++)
        {
            if (mat[j][1] > mat[j + 1][1])
            {
                for (int k = 0; k < 5; k++)
                {
                    swap(mat[j][k], mat[j + 1][k]);
                }
            }
        }
    }
}
void sjf_process::calculate_CT()
{
    int temp, val;
    mat[0][3] = mat[0][1] + mat[0][2];
    mat[0][5] = mat[0][3] - mat[0][1];
    mat[0][4] = mat[0][5] - mat[0][2];

    for (int i = 1; i < sjf_n; i++)
    {
        temp = mat[i - 1][3];
        int low = mat[i][2];
        for (int j = i; j < sjf_n; j++)
        {
            if (temp >= mat[j][1] && low >= mat[j][2])
            {
                low = mat[j][2];
                val = j;
            }
        }
        mat[val][3] = temp + mat[val][2];
        mat[val][5] = mat[val][3] - mat[val][1];
        mat[val][4] = mat[val][5] - mat[val][2];
        for (int k = 0; k < 6; k++)
        {
            swap(mat[val][k], mat[i][k]);
        }
    }
}
void sjf_process::get_sjf_process()
{
    cout << "...Enter the sjf_process ID...\n";
    for (int i = 0; i < sjf_n; i++)
    {
        cout << "...sjf_Process " << i + 1 << "...\n";
        cout << "Enter sjf_Process Id: ";
        cin >> mat[i][0];
        cout << "Enter Arrival Time: ";
        cin >> mat[i][1];
        cout << "Enter Burst Time: ";
        cin >> mat[i][2];
    }

    cout << "Before Arrange...\n";
    cout << "sjf_Process ID\tArrival Time\tBurst Time\n";
    for (int i = 0; i < sjf_n; i++)
    {
        cout << mat[i][0] << "\t\t" << mat[i][1] << "\t\t" << mat[i][2] << "\n";
    }
    // this->arrange_arrival(mat);
    // this->completion_time(mat);
}
void sjf_process::display()
{
    int l = 0, m = 0;
    cout<<"\n\nShortest Job first :-"<<endl;
    cout << "Final Result...\n";
    cout << "sjf_Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < sjf_n; i++)
    {
        cout << mat[i][0] << "\t\t" << mat[i][1] << "\t\t" << mat[i][2] << "\t\t" << mat[i][4] << "\t\t" << mat[i][5] << "\n";
    }

    for (int i = 0; i < sjf_n; i++)
    {
        l +=mat[i][4];
        m +=mat[i][5];
    }
    sjf_process::avg_tat = m / sjf_n;
    sjf_process::avg_wt = l / sjf_n;
    cout << "Average Turn around time :" << sjf_process::avg_tat << endl;
    cout << "Average Wait time        :" << sjf_process::avg_wt << endl;
}
ostream &operator<<(ostream &out, sjf_process obj)
{
    int l = 0, m = 0;
    cout << "Final Result...\n";
    cout << "sjf_Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < sjf_n; i++)
    {
        cout << obj.mat[i][0] << "\t\t" << obj.mat[i][1] << "\t\t" << obj.mat[i][2] << "\t\t" << obj.mat[i][4] << "\t\t" << obj.mat[i][5] << "\n";
    }
    for (int i = 0; i < sjf_n; i++)
    {
        l += obj.mat[i][4];
        m += obj.mat[i][5];
    }
    sjf_process::avg_tat = m / sjf_n;
    sjf_process::avg_wt = l / sjf_n;
    cout << "Average Turn around time :" << sjf_process::avg_tat << endl;
    cout << "Average Wait time        :" << sjf_process::avg_wt << endl;

    return out;
}

//priority
int priority_n;
int i, j;
class priority : public process
{

    int bt[20], p[20], wt[20], tat[20], pr[20];
    static float avg_tat;
    static float avg_wt;

public:
    friend void readmain(process **p);
    void calculate_CT();
    void display();
    void get_process();

    friend ostream &operator<<(ostream &out, priority obj);
    friend istream &operator>>(istream &in, priority obj);
    friend void claculatemain();
    friend void calculatebestmain();
    friend void randinputmain(process **p);

    void arrange_arrival()
    {

    }

     void calculate_TAT_WT()
    {

    }

};
float priority::avg_tat = 0;
float priority::avg_wt = 0;

void priority_swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
void priority::calculate_CT()
{
    int pos, temp;
    for (i = 0; i < priority_n - 1; i++)
    {
        for (j = 0; j < priority_n - i - 1; j++)
        {
            if (pr[j] > pr[j + 1])
            {
                priority_swap(&pr[j], &pr[j + 1]);
                priority_swap(&bt[j], &bt[j + 1]);
                priority_swap(&p[j], &p[j + 1]);
            }
        }
    }
    wt[0] = 0;
}
void priority::get_process()
{
    cout << "\nEnter Burst Time and Priority\n";
    for (i = 0; i < priority_n; i++)
    {
        cout << "\nP[" << i + 1 << "]\n";
        cout << "Burst Time:";
        cin >> bt[i];
        cout << "Priority:";
        cin >> pr[i];
        p[i] = i + 1;
    }
}

void priority::display()
{
    cout<<"\n\nPriority :-"<<endl;
    float total=0;
    for(i=1;i<priority_n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]=wt[i]+bt[j];
 
        total=total+wt[i];
    }
    priority::avg_wt=total/priority_n;      
    total=0;
    cout<<"\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
    for(i=0;i<priority_n;i++)
    {
        tat[i]=bt[i]+wt[i];     
        total=total+tat[i];
        cout<<"\nP["<<p[i]<<"]\t\t  "<<bt[i]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
    }
 
    priority::avg_tat=total/priority_n;     
    cout<<"\n\nAverage Waiting Time="<<priority::avg_wt;
    cout<<"\nAverage Turnaround Time="<<priority::avg_tat<<endl;
}
ostream &operator<<(ostream &out, priority obj)
{
    float total = 0;
    for (i = 1; i < priority_n; i++)
    {
        obj.wt[i] = 0;
        for (j = 0; j < i; j++)
            obj.wt[i] = obj.wt[i] + obj.bt[j];

        total = total + obj.wt[i];
    }
    priority::avg_wt = total / priority_n;
    total = 0;
    cout << "\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
    for (i = 0; i < priority_n; i++)
    {
        obj.tat[i] = obj.bt[i] + obj.wt[i];
        total = total + obj.tat[i];
        cout << "\nP[" << obj.p[i] << "]\t\t  " << obj.bt[i] << "\t\t    " << obj.wt[i] << "\t\t\t" << obj.tat[i];
    }

    priority::avg_tat = total / priority_n;

    cout << "\n\nAverage Waiting Time=" << priority::avg_wt;
    cout << "\nAverage Turnaround Time=" << priority::avg_tat;
    return out;
}

FCFS_Process fcfs[10];
rr_process rr[10];
sjf_process sjf;
priority prio;

void readmain(process **p)
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

    p[0] = fcfs;
    p[1] = rr;
    p[2] = &sjf;
    p[3] = &prio;
}

void calculatebestmain()
{
    int a,b,c,d;

    a=FCFS_Process::Avg_WT;
    b=rr_process::Avg_WT;
    c=sjf_process::avg_wt;
    d=priority::avg_wt;

    if (a<=b&&a<=c&&a<=d)
    {
        cout<<"\nFCFS is the most efficient algorithm for these processes "<<endl;
        cout<<"with Average wait time :"<<a<<"\n"<<endl;
    }
    else if (b<=a&&b<=c&&b<=d)
    {
        cout<<"\nRound robin is the most efficient algorithm for these processes"<<endl;
         cout<<"with Average wait time :"<<b<<"\n"<<endl;
    }
    else if (c<=b&&c<=a&&c<=d)
    {
        cout<<"\nShortest job first is the most efficient algorithm for these processes"<<endl;
         cout<<"with Average wait time :"<<c<<"\n"<<endl;
    }
    else if (d<=b&&d<=c&&d<=a)
    {
        cout<<"\nPriority scheduling is the most efficient algorithm for these processes"<<endl;
         cout<<"with Average wait time :"<<d<<"\n"<<endl;
    }
    

}

void randinputmain(process **p)
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

     p[0] = fcfs;
    p[1] = rr;
    p[2] = &sjf;
    p[3] = &prio;

}


int main()
{
    process *p[4];
    int b=1;
    cout << "Enter the number of processes" << endl;
    cin >> n;
    fcfs_n = n;
    rr_n = n;
    priority_n = n;
    sjf_n = n;

    cout << "Enter the time quantumn for Round robin algorithm" << endl;
    cin >> q;

    //readmain(p);
     randinputmain(p);
    for (int i = 0; i < 4; i++)
    {
        p[i]->arrange_arrival();
    }

    for (int i = 0; i < 4; i++)
    {
        p[i]->calculate_CT();
    }

    for (int i = 0; i < 4; i++)
    {
        p[i]->calculate_TAT_WT();
    }

    
    
    


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
            case 1:
                    p[0]->display();
                   
                    
                    break;

            case 2:
                   p[1]->display();
                   
                    
                   break;

            case 3:
                   p[2]->display();
                   cout<<"\n"<<endl; 
                   break;

            case 4:
                   p[3]->display();
                   cout<<"\n"<<endl; 
                   break;

            case 5: calculatebestmain();
                    break;


        }



        cout<<"Enter 1 if you want to continue"<<endl;
        cin>>b;
    }
    
}
