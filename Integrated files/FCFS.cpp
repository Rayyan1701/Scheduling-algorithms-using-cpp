#include <iostream>
using namespace std;
int n;

class FCFS_Process
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
	FCFS_Process()
	{
		FCFS_process_id = 0;
		burst_time = 0;
		completion_time = 0;
		TAT = 0;
		wait_time = 0;
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

int main()
{
	FCFS_Process obj[10];
	
	cout << "Enter number of FCFS_processes" << endl;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "FCFS_Process " << i + 1 << ":" << endl;
		obj[i].read();
		//cin>>obj[i];
	}
	obj[0].arrange_arrival();
	obj[0].calculate_CT();
	obj[0].calculate_TAT_WT();

	 //obj[0].display();
	cout<<obj;

	FCFS_Process::FCFS_display_average_TAT_WT();
}
