#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

float A[3][6];
float factorm;
int MD[6]={84,74,66,59,56,54};
int DM[6]={8,6,6,5,4,3};

int main(){
       int i,j;
       A[0][5]=240;
       A[1][5]=82;
       A[2][5]=42;
	
	for(i=0;i<6;i++){
	  cout<<setw(2)<<"R"<<i+1<<"("<<MD[i]<<","<<DM[i]<<") \n";
	}
      
	for(j=0;j<3;j++){
	cout<<"\n";
	for(i=0;i<6;i++){
		factorm=1+0.4*((float)(DM[i]-DM[5])/(float)DM[5])+ 0.6*((float)(MD[i]-MD[5])/(float)MD[5]);
		//cout<<"["<<factorm<<"]";
		cout<<setw(10)<<A[j][5]*factorm<<"\n";
		}
	} 	    

	cout<<"\n";
	return 0;
}
