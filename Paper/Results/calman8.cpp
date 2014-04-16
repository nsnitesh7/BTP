#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<cmath>
using namespace std;


int X[8],Y[8];

int CalMD(string F){
	
    int i,j;
    int MD;

    ifstream R(F.c_str());
    for(i=0;i<8;i++) R>>X[i]>>Y[i];	
    
    MD=0;
    for(i=0;i<8;i++){
      for(j=i+1;j<8;j++){
		MD=MD+abs(float(X[i]-X[j]))+abs(float(Y[i]-Y[j]));
	}
    } 
    return MD;		
}

int main(){
	
    cout<<"SMD of R1="<<CalMD("R1")<<endl;
    cout<<"SMD of R2="<<CalMD("R2")<<endl;
    cout<<"SMD of R3="<<CalMD("R3")<<endl;
    cout<<"SMD of R4="<<CalMD("R4")<<endl;
    cout<<"SMD of R5="<<CalMD("R5")<<endl;
    cout<<"SMD of R6="<<CalMD("R6")<<endl;

    return 0;		
}
