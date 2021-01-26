#include <iostream>
#include <queue>
using namespace std;

class process_queue
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
    process_queue *next;

public:
    process_queue()
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
    ~process_queue() {}

    process_queue operator=(const process_queue &obj)
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
    void arrange_arrival(int size)
    {
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - i - 1; j++)
            {
                process_queue temp;
                if (this[j].arrival_time > this[j + 1].arrival_time)
                {
                    temp = this[j];
                    this[j] = this[j + 1];
                    this[j + 1] = temp;
                }
            }
        }
    }

    bool completed(int n)
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

    void calculate_CT(int n, int q, process_queue *first, process_queue *end)
    {
        queue<process_queue> ready_queue;
        int sum = 0, j = 0, k;
        ready_queue.push(this[0]);

        // while (!this[0].completed(n)) //for some gaps in-between
        //    {
        sum = ready_queue.front().arrival_time;

        while (!ready_queue.empty()) //actual code starts from here
        {
            process_queue r = ready_queue.front();

            for (int i = 0; i < n; i++)
            {
                if (this[i].process_id == r.process_id)
                {
                    k = i;
                    break;
                }
            }

            process_queue &p = this[k];

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
                    if (this[i].arrival_time <= sum && this[i].process_id != p.process_id && this[i].arrival_time > p.arrival_time && i > j)
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

    void calculate_TAT_WT(int n)
    {
        for (int i = 0; i < n; i++)
        {
            this[i].TAT = this[i].completion_time - this[i].arrival_time;
        }

        for (int i = 0; i < n; i++)
        {
            this[i].wait_time = this[i].TAT - this[i].burst_time;
        }
    }

    void display(int n)
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

    friend ostream &operator<<(ostream &out, process_queue q);
    friend void showq(queue<process_queue> gq);
};
ostream &operator<<(ostream &out, process_queue q)
{
    out << q.process_id << "\t\t" << q.arrival_time << "\t\t" << q.burst_time << "\t\t" << q.completion_time << "\t\t\t" << q.TAT << "\t\t\t" << q.wait_time << endl;
    return out;
}

void showq(queue<process_queue> gq)
{
    queue<process_queue> g = gq;
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

    while (!g.empty())
    {
        cout << g.front();
        g.pop();
    }
    cout << '\n';
}

int main()
{

    process_queue *first = NULL, *last = NULL;
    process_queue obj[10];
    int n, q;
    cout << "Enter number of processes" << endl;
    cin >> n;
    cout << "Enter time quantumn" << endl;
    cin >> q;
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << i + 1 << ":" << endl;
        obj[i].read();
    }

    obj[0].arrange_arrival(n);
    obj[0].calculate_CT(n, q, first, last);
    obj[0].calculate_TAT_WT(n);

    obj[0].display(n);
}
