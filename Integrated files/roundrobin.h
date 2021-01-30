
#include <iostream>
#include <queue>
using namespace std;
int rr_n;
int  q;
class rr_process
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

    rr_process  operator=(const rr_process &obj);
    

    void read();

    friend void claculatemain();
    friend void calculatebestmain();
    friend void randinputmain();
    
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
                if(sum<=this[rr_n-1].arrival_time && ready_queue.empty())//for gaps in gant chart
                {
                     
                     sum=this[k+1].arrival_time;
                     ready_queue.push(this[k+1]);
                      
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
            Avg_TAT+=this[i].TAT;
        }
         Avg_TAT=Avg_TAT/rr_n;

        for (int i = 0; i < rr_n; i++)
        {
            this[i].wait_time = this[i].TAT - this[i].burst_time;
            Avg_WT+=this[i].wait_time;
        }
        Avg_WT=Avg_WT/rr_n;
    }

    void display()
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

            cout << this[i].process_id << "\t\t" << this[i].arrival_time << "\t\t" << this[i].burst_time << "\t\t" << this[i].completion_time << "\t\t\t" << this[i].TAT << "\t\t\t" << this[i].wait_time << endl;
        }
        
        
        
        
        
    }
    
    static void roundrobin_display_average_TAT_WT()
	{
		cout<<"Average Turn around time :"<<Avg_TAT<<endl;
		cout<<"Average Wait time        :"<<Avg_WT<<endl;
	}
    
    

    friend ostream &operator<<(ostream &out, rr_process* q);
    friend void readmain();
};
ostream &operator<<(ostream &out, rr_process* q)
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

rr_process rr_process:: operator=(const rr_process &obj)
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

    void rr_process:: read()
    {
        cout << "Enter Process ID   :";
        cin >> process_id;
        cout << "Enter Arrival time :";
        cin >> arrival_time;
        cout << "Enter Burst time   :";
        cin >> burst_time;
        dup_BT = burst_time;
    }


    void rr_process::  arrange_arrival()
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


float rr_process::Avg_TAT=0;
float rr_process::Avg_WT=0;
