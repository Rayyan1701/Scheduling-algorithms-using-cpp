#include<iostream>
using namespace std;
int n;
class sjf_process
{
    int mat[10][6];
    static float avg_tat;
    static float avg_wt;
    public:
        void arrange_arrival();
        void calculate_CT();
        void get_sjf_process();
        //void display();
        friend ostream &operator<<(ostream &out,sjf_process obj);
};
float sjf_process::avg_tat=0;
float sjf_process::avg_wt=0;

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
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
/*void sjf_process::display()
{
    cout<<"Final Result...\n"; 
    cout<<"sjf_Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n"; 
    for(int i=0; i<n; i++) 
    { 
        cout<<mat[i][0]<<"\t\t"<<mat[i][1]<<"\t\t"<<mat[i][2]<<"\t\t"<<mat[i][4]<<"\t\t"<<mat[i][5]<<"\n"; 
    } 
}*/
ostream &operator<<(ostream &out,sjf_process obj)
{
    int l=0,m=0;
    cout<<"Final Result...\n"; 
    cout<<"sjf_Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n"; 
    for(int i=0; i<n; i++) 
    { 
        cout<<obj.mat[i][0]<<"\t\t"<<obj.mat[i][1]<<"\t\t"<<obj.mat[i][2]<<"\t\t"<<obj.mat[i][4]<<"\t\t"<<obj.mat[i][5]<<"\n"; 
    }
    for (int i = 0; i < n; i++)
    {
        l+=obj.mat[i][4];
        m+=obj.mat[i][5];
    }
    sjf_process::avg_wt=l/n;
    sjf_process::avg_tat=m/n;
    return out; 
}
int main()
{
    sjf_process obj;
    cout<<"Enter the number of sjf_processes\t";
    cin>>n;
    obj.get_sjf_process();
     obj.arrange_arrival();
    obj.calculate_CT();
    cout<<obj;

    return 0;
}