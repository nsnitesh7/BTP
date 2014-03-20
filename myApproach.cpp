#include <bits/stdc++.h>
using namespace std;

int main()
{
	for(int test=0;test<20;test++)
	{
		int index;
		int applicationsCount,phasesCount,maxAvailProcessors;
		cin>>index>>maxAvailProcessors>>phasesCount>>applicationsCount;
		int phase;
		int schedulingOutput[phasesCount][applicationsCount];
		for(int i=0;i<phasesCount;i++)
		{
			//cin>>phase;
			for(int j=0;j<applicationsCount;j++)
			{
				cin>>schedulingOutput[i][j];
			}
		}
	
		vector<int> applications;
		for(int i=0;i<applicationsCount;i++)
			applications.push_back(i);
	
		int tryBinding[phasesCount][maxAvailProcessors];
		int optimalBinding[phasesCount][maxAvailProcessors];
		int optimalApplicationsOrder[applicationsCount];
		int colConversions[maxAvailProcessors];
		int rowConversions[phasesCount];
		int sumAllConversions;
		int minConversions=INT_MAX;
		int minRowConversions=0;
		int minColConversions=0;
	
		do
		{
			//arrange applications in matrix as in this permutation of application vector
			for(int i=0;i<phasesCount;i++)
			{
				int k=0;
				for(int j=0;j<applicationsCount;j++)
				{
					for(int l=0;l<schedulingOutput[i][applications[j]];l++)
						tryBinding[i][k++]=applications[j];
				}
				if(k<maxAvailProcessors)
				{
					while(k<maxAvailProcessors)
						tryBinding[i][k++]=-1;
				}
			}
		
			sumAllConversions=0;
			for(int i=0;i<phasesCount;i++)
			{
				int count=0;
				for(int j=1;j<maxAvailProcessors;j++)
				{
					if(tryBinding[i][j-1]!=tryBinding[i][j])
						count++;
				}
				sumAllConversions+=count;
				rowConversions[i]=count;
			}
			for(int i=0;i<maxAvailProcessors;i++)
			{
				int count=0;
				for(int j=1;j<phasesCount;j++)
				{
					if(tryBinding[j-1][i]!=tryBinding[j][i])
						count++;
				}
				sumAllConversions+=count;
				colConversions[i]=count;
			}
		
			if(sumAllConversions<minConversions)
			{
				minConversions=sumAllConversions;
				minRowConversions=0;
				minColConversions=0;
				for(int i=0;i<phasesCount;i++)
					minRowConversions+=rowConversions[i];
				
				for(int i=0;i<maxAvailProcessors;i++)
					minColConversions+=colConversions[i];
				for(int i=0;i<phasesCount;i++)
				{
					for(int j=0;j<maxAvailProcessors;j++)
					{
						optimalBinding[i][j]=tryBinding[i][j];
					}
				}
				for(int i=0;i<applicationsCount;i++)
					optimalApplicationsOrder[i]=applications[i];
			}
		}while (next_permutation(applications.begin(),applications.end()));
		
		cout<<index<<" "<<minRowConversions<<" "<<minColConversions<<" "<<minConversions<<endl;
//		cout<<"optimalApplicationsOrder : \t";
//		for(int i=0;i<applicationsCount;i++)
//			cout<<optimalApplicationsOrder[i]+1<<"\t";
//		cout<<endl;
		for(int i=0;i<phasesCount;i++)
		{
//			cout<<"Phase : "<<i<<" :\t";
			for(int j=0;j<maxAvailProcessors;j++)
			{
				if(optimalBinding[i][j]!=-1)
					cout<<optimalBinding[i][j]+1<<" ";
				else
					cout<<optimalBinding[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
}
