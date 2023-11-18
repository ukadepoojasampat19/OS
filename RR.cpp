#include<iostream>
#include <queue>
using namespace std;

struct Process{
	int id;
	int at;
	int bt;
	int wt;
	int tat;
};

/*    p1 p2 p3 
   at 5  4  7
   bt 0  4  5 
*/
int main(){
	int n , tq;
	int i = 0;
	int count = 0;
	Process p[10];
	
	
	cout<<"enter number of processes"<<endl;
	cin>>n;
	cout<<"enter time quantum"<<endl;
	cin>>tq;
	for(int j = 0; j<n ; j++){
		p[j].id = j;
		cout<<"enter arrival time of processes"<<endl;
		cin>>p[j].at;
		cout<<"enter burst time of process"<<endl;
		cin>>p[j].bt;
	}
	queue<Process> q;
	q.push(p[i]);
	
	while(!q.empty()){
		Process exe = q.front();
		if(exe.bt > tq){
			exe.bt-=tq;
			count+= tq;
		}else{
			count+= exe.bt;
			exe.bt= 0;
			for(int j = 0; j < n ; j++){
				if(p[j].id==exe.id){
					p[j].wt = count - p[j].at - p[j].bt;
					p[j].tat = p[j].wt + p[j].bt;
				}
			}
			cout<<"process "<<exe.id<<" ended at : "<<count<<endl;
		}
		if(p[i+1].at <= count){
			for(int x = i+1 ; x < n ; x++){
				if(p[x].at<=count){
					q.push(p[x]);
					i++;
				}
			}
		}
		if(exe.bt>0){
			q.push(exe);
			q.pop();
		}else{
			q.pop();
		}
	
		
	}
	cout<<"pid\tat\tbt\twt\ttat"<<endl;
	float avgWt = 0;
	float avgTat = 0;
	for(int j = 0 ; j < n ; j++){
		Process pr = p[j];
		cout<<pr.id<<"\t"<<pr.at<<"\t"<<pr.bt<<"\t"<<pr.wt<<"\t"<<pr.tat<<endl;
		avgWt += pr.wt;
		avgTat+= pr.tat;
	}
	avgWt = avgWt/n;
	avgTat = avgTat/n;
	cout<<"average waiting time : "<<avgWt<<endl;
	cout<<"average turn around time : "<<avgTat<<endl;
	
	
	
	
	return 0;
	
}


/*
 ./a.out
enter number of processes
5
enter time quantum
4
enter arrival time of processes
0
enter burst time of process
3
enter arrival time of processes
2
enter burst time of process
6
enter arrival time of processes
4
enter burst time of process
4
enter arrival time of processes
6
enter burst time of process
5
enter arrival time of processes
8
enter burst time of process
2
process 0ended at : 3
process 2ended at : 11
process 1ended at : 17
process 4ended at : 19
process 3ended at : 20
pid     at      bt      wt      tat
0       0       3       0       3
1       2       6       9       15
2       4       4       3       7
3       6       5       9       14
4       8       2       9       11
average waiting time : 6
average turn around time : 10
*/
