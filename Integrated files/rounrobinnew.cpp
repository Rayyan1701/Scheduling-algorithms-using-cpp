#include <iostream>
#include <queue>
using namespace std;
int n;
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

    rr_process operator=(const rr_process &obj)
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

    void read()
    {
        cout << "Enter Process ID   :";
        cin >> process_id;
        cout << "Enter Arrival time :";
        cin >> arrival_time;
        cout << "Enter Burst time   :";
        cin >> burst_time;
        dup_BT = burst_time;
    }
    void arrange_arrival()
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
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

    bool completed()
    {
        int y = 0;
        for (int i = 0; i < n; i++)
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

            for (int i = 0; i < n; i++)
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
            }
            else if (p.dup_BT > q)
            {
                sum += q;
                p.dup_BT -= q;

                //      if (this[n - 1].arrival_time >= sum) //only used until sum<=largest arrival time
                //     {

                for (int i = 0; i < n; i++)
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
        for (int i = 0; i < n; i++)
        {
            this[i].TAT = this[i].completion_time - this[i].arrival_time;
            Avg_TAT+=this[i].TAT;
        }
         Avg_TAT=Avg_TAT/n;

        for (int i = 0; i < n; i++)
        {
            this[i].wait_time = this[i].TAT - this[i].burst_time;
            Avg_WT+=this[i].wait_time;
        }
        Avg_WT=Avg_WT/n;
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
        for (int i = 0; i < n; i++)
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
        for (int i = 0; i < n; i++)
        {

            cout << q[i].process_id << "\t\t" << q[i].arrival_time << "\t\t" << q[i].burst_time << "\t\t" << q[i].completion_time << "\t\t\t" << q[i].TAT << "\t\t\t" << q[i].wait_time << endl;
        }
    
    return out;
}




float rr_process::Avg_TAT=0;
float rr_process::Avg_WT=0;


int main()
{

    // rr_process *first = NULL, *last = NULL;
    rr_process obj[10];
    
    cout << "Enter number of processes" << endl;
    cin >> n;
    cout << "Enter time quantumn" << endl;
    cin >> q;
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << i + 1 << ":" << endl;
        obj[i].read();
    }

    obj[0].arrange_arrival();
    obj[0].calculate_CT();
    obj[0].calculate_TAT_WT();
    cout<<obj;
    //obj[0].display(n);
    rr_process::roundrobin_display_average_TAT_WT();
}
