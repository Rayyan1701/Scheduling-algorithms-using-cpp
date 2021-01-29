#include<iostream>
using namespace std;
class process
{
    int mat[10][6];
    public:
        void arrange_arrival(int num,int mat[][6]);
        void completion_time(int num,int mat[][6]);
        void get_process(int num);
        void display(int num);
};
void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
void process::arrange_arrival(int num,int mat[][6])
{ 
    for(int i=0; i<num; i++) 
    { 
        for(int j=0; j<num-i-1; j++) 
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
void process::completion_time(int num, int mat[][6]) 
{ 
    int temp, val; 
    mat[0][3] = mat[0][1] + mat[0][2]; 
    mat[0][5] = mat[0][3] - mat[0][1]; 
    mat[0][4] = mat[0][5] - mat[0][2]; 
      
    for(int i=1; i<num; i++) 
    { 
        temp = mat[i-1][3]; 
        int low = mat[i][2]; 
        for(int j=i; j<num; j++) 
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
void process::get_process(int num)
{
    cout<<"...Enter the process ID...\n"; 
    for(int i=0; i<num; i++) 
    { 
        cout<<"...Process "<<i+1<<"...\n"; 
        cout<<"Enter Process Id: "; 
        cin>>mat[i][0]; 
        cout<<"Enter Arrival Time: "; 
        cin>>mat[i][1]; 
        cout<<"Enter Burst Time: "; 
        cin>>mat[i][2]; 
    } 
      
    cout<<"Before Arrange...\n"; 
    cout<<"Process ID\tArrival Time\tBurst Time\n"; 
    for(int i=0; i<num; i++) 
    { 
        cout<<mat[i][0]<<"\t\t"<<mat[i][1]<<"\t\t"<<mat[i][2]<<"\n"; 
    } 
    this->arrange_arrival(num,mat);
    this->completion_time(num,mat);
}
void process::display(int num)
{
    cout<<"Final Result...\n"; 
    cout<<"Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n"; 
    for(int i=0; i<num; i++) 
    { 
        cout<<mat[i][0]<<"\t\t"<<mat[i][1]<<"\t\t"<<mat[i][2]<<"\t\t"<<mat[i][4]<<"\t\t"<<mat[i][5]<<"\n"; 
    } 
}
int main()
{
    process obj;
    int num;
    cout<<"Enter the number of processes\t";
    cin>>num;
    obj.get_process(num);
    obj.display(num);
    return 0;
}