#include <iostream>
#include <queue>
using namespace std;
int n;

class process
{
    public:
    virtual void calculate_CT()=0;
    virtual void arrange_arrival()=0;
    virtual void calculate_TAT_WT()=0;
    virtual void display()=0;
    
};




//FCFS

class FCFS_Process: public process
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
    FCFS_Process(int id=0,int bt=0,int ct=0,int tat=0,int wt=0)
	{
		FCFS_process_id = id;
		burst_time = bt;
		completion_time = ct;
		TAT = tat;
		wait_time = wt;
	}
	~FCFS_Process() {}
	void arrange_arrival()
	{
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
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
	void calculate_CT()
	{
		for (int i = 0; i < n; i++)
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
	void calculate_TAT_WT()
	{
		for (int i = 0; i < n; i++)
		{
			this[i].TAT = this[i].completion_time - this[i].arrival_time;
			Avg_TAT += this[i].TAT;
		}
		Avg_TAT = Avg_TAT / n;

		for (int i = 0; i < n; i++)
		{
			this[i].wait_time = this[i].TAT - this[i].burst_time;
			Avg_WT += this[i].wait_time;
		}
		Avg_WT = Avg_WT / n;
	}

	void read()
	{
		cout << "Enter FCFS_Process ID   :";
		cin >> FCFS_process_id;
		cout << "Enter Arrival time :";
		cin >> arrival_time;
		cout << "Enter Burst time   :";
		cin >> burst_time;
	}

	FCFS_Process operator=(const FCFS_Process &obj)
	{
		FCFS_process_id = obj.FCFS_process_id;
		burst_time = obj.burst_time;
		completion_time = obj.completion_time;
		TAT = obj.TAT;
		arrival_time = obj.arrival_time;
		wait_time = obj.wait_time;
		return *this;
	}

	void display()
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
		for (int i = 0; i < n; i++)
		{

			cout << this[i].FCFS_process_id << "\t\t" << this[i].arrival_time << "\t\t" << this[i].burst_time << "\t\t" << this[i].completion_time << "\t\t\t" << this[i].TAT << "\t\t\t" << this[i].wait_time << endl;
		}
	}

	static void FCFS_display_average_TAT_WT()
	{
		cout << "Average Turn around time :" << Avg_TAT << endl;
		cout << "Average Wait time        :" << Avg_WT << endl;
	}

    friend ostream& operator<<(ostream& out, FCFS_Process* obj);
	friend istream& operator>>(istream& in, FCFS_Process obj);
     friend void read(process **p);
};

float FCFS_Process::Avg_TAT = 0;
float FCFS_Process::Avg_WT = 0;


ostream& operator<<(ostream& out, FCFS_Process* obj)
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
		for (int i = 0; i < n; i++)
		{

			cout << obj[i].FCFS_process_id << "\t\t" << obj[i].arrival_time << "\t\t" << obj[i].burst_time << "\t\t" << obj[i].completion_time << "\t\t\t" << obj[i].TAT << "\t\t\t" << obj[i].wait_time << endl;
		}

		return out;

}


istream& operator>>(istream& in, FCFS_Process obj)
{
   cout << "Enter FCFS_Process ID   :";
		cin >> obj.FCFS_process_id;
		cout << "Enter Arrival time :";
		cin >> obj.arrival_time;
		cout << "Enter Burst time   :";
		cin >> obj.burst_time;

	return in;
}


//ROUND ROBIN

int  q;
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
    friend void read(process **p);
    
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


//SJF

class sjf_process: public process
{
    int mat[10][6];
    public:
        void arrange_arrival();
        void calculate_CT();
        void get_sjf_process();
        void calculate_TAT_WT()
        {

        }

        void display();
        friend ostream &operator<<(ostream &out,sjf_process obj);
        friend void read(process **p);
};

void sjf_process::arrange_arrival()
{ 
    for(int i=0; i<n; i++) 
    { 
        for(int j=0; j<n-i-1; j++) 
        { 
            if(mat[j][1] > mat[j+1][1]) 
            { 
                for(int k=0; k<5; k++) 
                { 
                    swap(mat[j][k], mat[j+1][k]); 
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
      
    for(int i=1; i<n; i++) 
    { 
        temp = mat[i-1][3]; 
        int low = mat[i][2]; 
        for(int j=i; j<n; j++) 
        { 
            if(temp >= mat[j][1] && low >= mat[j][2]) 
            { 
                low = mat[j][2]; 
                val = j; 
            } 
        } 
        mat[val][3] = temp + mat[val][2]; 
        mat[val][5] = mat[val][3] - mat[val][1]; 
        mat[val][4] = mat[val][5] - mat[val][2]; 
        for(int k=0; k<6; k++) 
        { 
            swap(mat[val][k], mat[i][k]); 
        } 
    } 
} 
void sjf_process::get_sjf_process()
{
    cout<<"...Enter the sjf_process ID...\n"; 
    for(int i=0; i<n; i++) 
    { 
        cout<<"...sjf_Process "<<i+1<<"...\n"; 
        cout<<"Enter sjf_Process Id: "; 
        cin>>mat[i][0]; 
        cout<<"Enter Arrival Time: "; 
        cin>>mat[i][1]; 
        cout<<"Enter Burst Time: "; 
        cin>>mat[i][2]; 
    } 
      
    cout<<"Before Arrange...\n"; 
    cout<<"sjf_Process ID\tArrival Time\tBurst Time\n"; 
    for(int i=0; i<n; i++) 
    { 
        cout<<mat[i][0]<<"\t\t"<<mat[i][1]<<"\t\t"<<mat[i][2]<<"\n"; 
    } 
    // this->arrange_arrival(mat);
    // this->completion_time(mat);
}
void sjf_process::display()
{
    cout<<"Final Result...\n"; 
    cout<<"sjf_Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n"; 
    for(int i=0; i<n; i++) 
    { 
        cout<<mat[i][0]<<"\t\t"<<mat[i][1]<<"\t\t"<<mat[i][2]<<"\t\t"<<mat[i][4]<<"\t\t"<<mat[i][5]<<"\n"; 
    } 
}
ostream &operator<<(ostream &out,sjf_process obj)
{
    cout<<"Final Result...\n"; 
    cout<<"sjf_Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n"; 
    for(int i=0; i<n; i++) 
    { 
        cout<<obj.mat[i][0]<<"\t\t"<<obj.mat[i][1]<<"\t\t"<<obj.mat[i][2]<<"\t\t"<<obj.mat[i][4]<<"\t\t"<<obj.mat[i][5]<<"\n"; 
    }
    return out; 
}


//priority

int i,j;
class priority: public process
{
    int bt[20],p[20],wt[20],tat[20],pr[20];
    public:
        void calculate_CT();
        void display();
        void get_process();

        friend ostream& operator<<(ostream &out,priority obj);
        friend istream& operator>>(istream &in,priority obj);
        friend void read(process **p);
        void arrange_arrival()
        {

        }
        void calculate_TAT_WT()
        {
            
        }
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

int id,at,bt,pr;
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





int main()
{
    process *p[4];
    

    

    cout<<"Enter the number of processes"<<endl;
    cin>>n;

    cout<<"Enter the time quantumn for Round robin algorithm"<<endl;
    cin>>q;

    cout<<"Enter the process parameters "<<endl;

    read(p);

   for (int i = 0; i < n; i++)
   {
        p[i]->arrange_arrival();
   }

   for (int i = 0; i < n; i++)
   {
        p[i]->calculate_CT();
   }

   for (int i = 0; i < 2; i++)
   {
       p[i]->calculate_TAT_WT();
   }
   cout<<"The final results are:-"<<endl;
   for (int i = 0; i < n; i++)
   {
       p[i]->display();
   }
 
}


