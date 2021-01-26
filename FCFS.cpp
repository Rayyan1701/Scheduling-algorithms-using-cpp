#include<iostream>
using namespace std;

class Process
{
	int process_id;
	int arrival_time;
	int burst_time;
	int completion_time;
	int TAT;
	int wait_time;
	static float Avg_TAT;
	static float Avg_WT;
	public:
	Process(){process_id=0;
    burst_time=0;
	completion_time=0;
	TAT=0;
	wait_time=0;}
	~Process(){}
	void arrange_arrival(int size)
	{
		for(int i=0;i<size-1;i++)
		{
			for(int j=0;j<size-i-1;j++)
			{Process temp;
				if(this[j].arrival_time>this[j+1].arrival_time)
				{
				    temp=this[j];
					this[j]=this[j+1];
					this[j+1]=temp;
				}
			}
		}
		
	}
	void calculate_CT(int n)
	{
		for(int i=0;i<n;i++)
		{
			if(i==0)
			{
				this[i].completion_time=this[i].arrival_time+this[i].burst_time;
			}
			else
			{
				if(this[i].arrival_time<=this[i-1].completion_time)
				{
					this[i].completion_time=this[i-1].completion_time+this[i].burst_time;
				}
				else
				{
					this[i].completion_time=this[i].arrival_time+this[i].burst_time;
					
				}
				
			}
		}
		
	}
	void calculate_TAT_WT(int n)
	{
		for(int i=0;i<n;i++)
		{
			this[i].TAT=this[i].completion_time-this[i].arrival_time;
			Avg_TAT+=this[i].TAT;
		}
		Avg_TAT=Avg_TAT/n;
		
		for(int i=0;i<n;i++)
		{
			this[i].wait_time=this[i].TAT-this[i].burst_time;
			Avg_WT+=this[i].wait_time;
		}
		Avg_WT=Avg_WT/n;
		
		
		
	}
	
	
	
	
	
	void read()
	{
		cout<<"Enter Process ID   :"; cin>>process_id;
		cout<<"Enter Arrival time :"; cin>>arrival_time;
		cout<<"Enter Burst time   :"; cin>>burst_time;
		
	}
	
	Process operator=(const Process &obj)
	{
		process_id=obj.process_id;
        burst_time=obj.burst_time;
	    completion_time=obj.completion_time;
    	TAT=obj.TAT;
    	wait_time=obj.wait_time;
	    return *this;
	}
	
	
	void display(int n)
	{
		cout<<"Process ID"<<"\t"<<"Arrival"<<"\t\t"<<"Burst time"<<"\t"<<"completion time"<<"\t\t"<<"Turn around time"<<"\t"<<"Wait time"<<endl;
		for(int i=0;i<n;i++)
	{
		
		cout<<this[i].process_id<<"\t\t"<<this[i].arrival_time<<"\t\t"<<this[i].burst_time<<"\t\t"<<this[i].completion_time<<"\t\t\t"<<this[i].TAT<<"\t\t\t"<<this[i].wait_time<<endl;
		
		
	}
		
	}
	
	static void FCFS_display_average_TAT_WT(int n)
	{
		cout<<"Average Turn around time :"<<Avg_TAT<<endl;
		cout<<"Average Wait time        :"<<Avg_WT<<endl;
	}
	
};

float Process::Avg_TAT=0;
float Process::Avg_WT=0;



int main()
{
	Process obj[10];
	int n;
	cout<<"Enter number of processes"<<endl;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"Process "<<i+1<<":"<<endl;
		obj[i].read();
	}
	obj[0].arrange_arrival(n);
	obj[0].calculate_CT(n);
	obj[0].calculate_TAT_WT(n);
		
	obj[0].display(n);
	
	Process::FCFS_display_average_TAT_WT(n);
	
	
	
	
}
