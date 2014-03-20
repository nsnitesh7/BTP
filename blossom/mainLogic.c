#include <bits/stdc++.h>
#define maxWeight 100000
#define DEBUG true
using namespace std;

struct edge
{
	int start;
	int end;
};

struct cnt
{
	int index;
	int counter;
};

static bool cmprator(cnt c1,cnt c2)
{
	return c1.counter<c2.counter;
}

int calculateWeight(int **schedulingOutput,int i,int j,int phasesCount)
{
	int avgI;	//find average of i'th column
	int sumI=0;
	for(int k=0;k<phasesCount;k++)
	{
		sumI+=schedulingOutput[k][i];
	}
	avgI=sumI/phasesCount;
	
	int avgJ;	//find average of j'th column
	int sumJ=0;
	for(int k=0;k<phasesCount;k++)
	{
		sumJ+=schedulingOutput[k][j];
	}
	avgJ=sumJ/phasesCount;
	
	int weight=0;
	
	for(int k=0;k<phasesCount;k++)
	{
		weight+=(schedulingOutput[k][i]-avgI)*(schedulingOutput[k][j]-avgJ);
	}
	
	return weight;
}

int findNextFree(int **output,int row,int maxAvailProcessors)
{
	for(int i=0;i<maxAvailProcessors;i++)
	{
		if(output[row][i]==-1)
			return i;
	}
}

//returns the cell entropy in a bind
inline int cell_entropy(int **bind,int i, int j,int phase,int reg)
{
	int counter = 0;
	if(i>=0 && j>=0 && i<phase && j<reg)
	{
		if(bind[i][j] == 0)
			return 0;
				
		if( j+1 < reg && bind[i][j] != bind[i][j+1] && bind[i][j+1]!=0)
		{
			counter++;
			//cout <<" Right ";
		}
		if( j-1 >= 0 && bind[i][j] != bind[i][j-1] && bind[i][j-1]!=0)
		{
			counter++;
			//cout <<" Left ";
		}
		if( i+1 < phase && bind[i][j] != bind[i+1][j] && bind[i+1][j]!=0)
		{
			counter++;
			//cout <<" Bottom ";
		}
		if( i-1 >= 0 && bind[i][j] != bind[i-1][j] && bind[i-1][j]!=0)
		{
			counter++;
			//cout <<" UP ";
		}
	}
	return counter;
}

//returns the total entropy of the bind
int total_entropy(int **bind,int phase,int reg)
{
	int counter = 0;
	for(int i=0; i<phase; i++)
	{
		for(int j=0; j<reg; j++)
		{
			counter += cell_entropy(bind,i, j,phase,reg);
		}
	}
	return counter;
}

int findEntropy(int **Output,int phasesCount,int maxAvailProcessors)
{
	return total_entropy(Output,phasesCount,maxAvailProcessors);
/*
	int totalEntropy=0;
	int localEntropy;

	//row entropy
	for(int i=0;i<phasesCount;i++)
	{
		localEntropy=0;
		int j=0;
		while(j<maxAvailProcessors && Output[i][j]==-1)
		{
			j++;
		}
		
		if(j<maxAvailProcessors)
			localEntropy=1;
		
		for(;j<maxAvailProcessors;j++)
		{
			if(Output[i][j]==-1)
				continue;
			
		}
		totalEntropy+=localEntropy;
	}
	
	//col entropy
	for(int i=0;i<maxAvailProcessors;i++)
	{
		localEntropy=0;
		for(int j=0;j<phasesCount;j++)
		{
			
		}
		totalEntropy+=localEntropy;
	}
*/
}

vector<int> findSequence(string s)
{
	vector<int> ret;
	char * str = new char[s.size() + 1];
	std::copy(s.begin(), s.end(), str);
	str[s.size()] = '\0';

	char *pch;
	pch = strtok(str,",");
	while (pch != NULL)
	{
//		printf ("%s\n",pch);
		ret.push_back(atoi(pch));
		pch = strtok (NULL, " ,.-");
	}
	return ret;
}

int findFreeCol(int **output,int row,bool blackListCols[],int totalProcessors)
{
	for(int i=0;i<totalProcessors;i++)
	{
		if(!blackListCols[i] && output[row][i]==-1)
			return i;
	}
}

void printOutput(int **output,int phasesCount,int maxAvailProcessors)
{
	for(int i=0;i<phasesCount;i++)
	{
		for(int j=0;j<maxAvailProcessors;j++)
		{
			cout<<output[i][j]<<"  ";
		}
		cout<<endl;
	}
}

int main()
{
	int test=20;
	while(test--)
	{
		int in;
		cin>>in;
		int applicationsCount,phasesCount,maxAvailProcessors;
		cin>>maxAvailProcessors>>phasesCount>>applicationsCount;
		int **schedulingOutput=new int*[phasesCount];
	
		for(int i=0;i<phasesCount;i++)
			schedulingOutput[i]=new int[applicationsCount];

		int **orischeduling=new int*[phasesCount];
	
		for(int i=0;i<phasesCount;i++)
			orischeduling[i]=new int[applicationsCount];
		
		for(int i=0;i<phasesCount;i++)
		{
			for(int j=0;j<applicationsCount;j++)
			{
				cin>>schedulingOutput[i][j];
			}
		}
	
		orischeduling=schedulingOutput;

		int no_of_nodes=applicationsCount;

		bool flag;

		char buffer[10];

		int maxProcessorReq[applicationsCount];

		string *order=new string[applicationsCount];
		for(int i=0;i<applicationsCount;i++)
		{
			sprintf(buffer,"%d",i);
			order[i]=buffer;
	//		cout<<order[i]<<endl;
			maxProcessorReq[i]=-1;
			for(int j=0;j<phasesCount;j++)
			{
				maxProcessorReq[i]=max(maxProcessorReq[i],schedulingOutput[j][i]);
			}
		}

		bool odd=false;
		int oddApplication=-1;
	
		if(applicationsCount%2==1)
			odd=true;
	
		bool oddFlag=true;

		//do this in loop
		while(no_of_nodes!=1)
		{
			flag=false;
		
			int no_of_edges=((no_of_nodes)*(no_of_nodes-1))/2;

			edge edges[no_of_edges];
			int weight[no_of_edges];
	
			//Calculate weights
	
			int e=0;
	
			for(int i=0;i<no_of_nodes-1;i++)
			{
				for(int j=i+1;j<no_of_nodes;j++)
				{
					weight[e]=calculateWeight(schedulingOutput,i,j,phasesCount);
	//				cout<<weight[e]<<endl;
					edges[e].start=i;
					edges[e].end=j;
					e++;
				}
			}
	
	//		cout<<e<<"\t"<<no_of_edges<<endl;
	
			ofstream myfile;
			myfile.open ("GRAPH.TXT");
	
			if(no_of_nodes%2==1)
			{
				myfile<<no_of_nodes+1<<" "<<no_of_edges+no_of_nodes<<endl;
				flag=true;
			}
			else
			{
				myfile<<no_of_nodes<<" "<<no_of_edges<<endl;
			}
	
			for(int e=0;e<no_of_edges;e++)
			{
				myfile<<edges[e].start<<" "<<edges[e].end<<" "<<weight[e]<<endl;
			}
	
			if(no_of_nodes%2==1)
			{
				for(int n=0;n<no_of_nodes;n++)
				{
					myfile<<no_of_nodes<<" "<<n<<" "<<maxWeight<<endl;
				}
			}
	
			myfile.close();
	
	
			system("./blossom5 -e GRAPH.TXT");
	
			//read from edges.txt
			ifstream myfile1("edges.txt");
	
			int a,b;
	
			//cout<<no_of_nodes<<endl;
		
			no_of_nodes=ceil(no_of_nodes/2.0);
		
			int **modifiedScheduling=new int*[phasesCount];
	
			for(int i=0;i<phasesCount;i++)
				modifiedScheduling[i]=new int[no_of_nodes];
			
			string *modifiedOrder=new string[no_of_nodes];
		
			if(DEBUG)
				cout<<"\n\n\n";
	
			for(int i=0;i<no_of_nodes;i++)
			{
				myfile1>>a>>b;
				if(flag && i==no_of_nodes-1)
				{
					modifiedOrder[i]=order[b];
					if(oddFlag)
						oddApplication=atoi(order[b].c_str());
					for(int j=0;j<phasesCount;j++)
						modifiedScheduling[j][i]=schedulingOutput[j][b];	
				}
				else
				{
					modifiedOrder[i]=order[a]+","+order[b];
					for(int j=0;j<phasesCount;j++)
						modifiedScheduling[j][i]=schedulingOutput[j][a]+schedulingOutput[j][b];
				}
				if(DEBUG)
					cout<<a<<"\t,\t"<<b<<"\t=>\t"<<i<<endl;
			}
			if(DEBUG)
				cout<<"\n\n\n";
	
			//fclose(fp);
			myfile1.close();
		
			//getchar();
		
			order=modifiedOrder;
			schedulingOutput=modifiedScheduling;
		
	//		no_of_nodes=no_of_nodes/2;

			oddFlag=false;

			for(int i=0;i<phasesCount;i++)
				delete[] modifiedScheduling[i];
	
		}
	
		if(DEBUG)
			cout<<endl<<endl<<order[0]<<endl<<endl;
	
		vector<int> sequence=findSequence(order[0]);
	
		if(DEBUG)
		{
			for(int i=0;i<sequence.size();i++)
			{
				cout<<sequence[i]<<"\t";
			}
		}
	
		//make phases X processor grid
	//	int output[phasesCount][maxAvailProcessors];
	
		int **output=new int*[phasesCount];
	
		int AllmaxProcessorReq=0;
		for(int i=0;i<applicationsCount;i++)
			AllmaxProcessorReq+=maxProcessorReq[i];
	
		for(int i=0;i<phasesCount;i++)
			output[i]=new int[AllmaxProcessorReq];
	
	
		for(int i=0;i<phasesCount;i++)
		{
			for(int j=0;j<AllmaxProcessorReq;j++)
			{
				output[i][j]=-1;
			}
		}
	
		//binding
		if(DEBUG)
			cout<<endl<<AllmaxProcessorReq<<"\t"<<oddFlag<<"\t"<<oddApplication<<endl;
	
		bool blackListCols[AllmaxProcessorReq];
	
		for(int i=0;i<AllmaxProcessorReq;i++)
			blackListCols[i]=false;
	
		int startCol=0;
		int endCol;
		int curCol;
	
		for(int i=0;i<applicationsCount;)
		{
			if(sequence[i]==oddApplication)
			{
				if(DEBUG)
					cout<<maxProcessorReq[sequence[i]]<<"\t"<<"sequence : "<<sequence[i]<<endl;
				//bind it from next empty column
				endCol=startCol+maxProcessorReq[sequence[i]];
				curCol=sequence[i];
				for(int j=0;j<phasesCount;j++)
				{
					while(orischeduling[j][curCol]--)
					{
						output[j][startCol++]=sequence[i];
					}
				}
				i=i+1;
			}
			else
			{
			
				//bind both applications together
				int max2Cols=-1;
				for(int j=0;j<phasesCount;j++)
				{
					//cout<<orischeduling[j][sequence[i]]<<"\t"<<orischeduling[j][sequence[i+1]]<<endl;
					max2Cols=max(max2Cols,orischeduling[j][sequence[i]]+orischeduling[j][sequence[i+1]]);
				}
				//exit(1);
				endCol=startCol+max2Cols;
				if(DEBUG)
					cout<<max2Cols<<"\t"<<"sequence : "<<sequence[i]<<"\t"<<sequence[i+1]<<endl;
				//curCol=sequence[i];
				for(int j=0;j<phasesCount;j++)
				{
					int endColBackup=endCol-1;
					int startColBackup=startCol;
					while(orischeduling[j][sequence[i]]--)
					{
						output[j][startColBackup++]=sequence[i];
					}
					while(orischeduling[j][sequence[i+1]]--)
					{
						output[j][endColBackup--]=sequence[i+1];
					}
				}
				i=i+2;
			}
			startCol=endCol;
			if(DEBUG)
			{
				cout<<endl;
	
				printOutput(output,phasesCount,AllmaxProcessorReq);
			
				cout<<endl;
			}
		}
	
		int extraCols=AllmaxProcessorReq-maxAvailProcessors;
	
		if(DEBUG)
			cout<<"extraCols : "<<extraCols<<endl;
	
		if(extraCols>0)
		{
			if(DEBUG)
			{
				cout<<endl;
	
				printOutput(output,phasesCount,AllmaxProcessorReq);
	
				cout<<endl;
			}
			cnt count[AllmaxProcessorReq];
		
			for(int i=0;i<AllmaxProcessorReq;i++)
			{
				count[i].index=i;
				count[i].counter=0;
				for(int j=0;j<phasesCount;j++)
				{
					if(output[j][i]!=-1)
						count[i].counter++;
				}
			}
	/*		
			for(int i=0;i<AllmaxProcessorReq;i++)
			{
				cout<<count[i].index<<"\t";
				cout<<count[i].counter<<"\n";
			}
			exit(1);
	*/

	//		vector<cnt> myV(count,count+AllmaxProcessorReq);
	//		nth_element(myV.begin(),myV.begin()+1,myV.end(),cmprator);
			sort(count,count+AllmaxProcessorReq,cmprator);
		
			vector<int> blacklistedCols;
		
			for(int i=0;i<extraCols;i++)
			{
				blacklistedCols.push_back(count[i].index);
				blackListCols[count[i].index]=true;
			}
		
			for(int k=0;k<blacklistedCols.size();k++)
			{
				int col=blacklistedCols[k];
				for(int j=0;j<phasesCount;j++)
				{
					if(output[j][col]!=-1)
					{
						int freeCol=findFreeCol(output,j,blackListCols,AllmaxProcessorReq);
						output[j][freeCol]=output[j][col];
					}
				}
			}
		
			//cout<<endl;
		
			int **modifiedOutput=new int*[phasesCount];
	
			for(int i=0;i<phasesCount;i++)
				modifiedOutput[i]=new int[maxAvailProcessors];
		
			int k=0;
		
			for(int i=0;i<AllmaxProcessorReq;i++)
			{
				if(blackListCols[i])
					continue;
				for(int j=0;j<phasesCount;j++)
				{
					modifiedOutput[j][k]=output[j][i];
				}
				k++;
			}
	//		cout<<k<<endl;
	//		exit(1);
			cout<<endl;

			printOutput(modifiedOutput,phasesCount,maxAvailProcessors);
		
			cout<<"Entropy : "<<findEntropy(modifiedOutput,phasesCount,maxAvailProcessors)<<endl;
		
		
			ofstream ofs;
			  ofs.open ("result.txt", std::ofstream::out | std::ofstream::app);

			  ofs << findEntropy(modifiedOutput,phasesCount,maxAvailProcessors)<<endl;

			  ofs.close();

			cout<<endl;
		}
		else
		{
			cout<<endl;

			printOutput(output,phasesCount,maxAvailProcessors);
		
			cout<<"Entropy : "<<findEntropy(output,phasesCount,maxAvailProcessors)<<endl;

			ofstream ofs;
			  ofs.open ("result.txt", std::ofstream::out | std::ofstream::app);

			  ofs << findEntropy(output,phasesCount,maxAvailProcessors)<<endl;

			  ofs.close();

			cout<<endl;
		}
		/*
		int processorToUse;
	
		int startCol=0;
	
		for(int i=0;i<applicationsCount;i++)
		{
			int curCol=sequence[i];
			for(int j=0;j<phasesCount;j++)
			{
				cout<<orischeduling[j][curCol]<<"\t"<<j<<"\t"<<curCol<<"\t";
				if(orischeduling[j][curCol]>avgProcessorReq[curCol])
				{
					processorToUse=avgProcessorReq[curCol];
					orischeduling[j][curCol]=orischeduling[j][curCol]-avgProcessorReq[curCol];
				}
				else
				{
					processorToUse=orischeduling[j][curCol];
					orischeduling[j][curCol]=0;
				}
	//			cout<<processorToUse<<endl;
	//			getchar();
				for(int k=startCol;k<startCol+processorToUse;k++)
				{
					output[j][k]=curCol;
				}
				for(int k=startCol+processorToUse;k<startCol+avgProcessorReq[curCol];k++)
				{
					output[j][k]=-1;
				}
			}
			startCol+=avgProcessorReq[curCol];
		}
	
		cout<<endl;
	
		printOutput(output,phasesCount,maxAvailProcessors);
	
		cout<<endl;
	
		for(int i=0;i<applicationsCount;i++)
			cout<<avgProcessorReq[i]<<" ";
		cout<<endl;
	
		exit(1);
		for(int i=0;i<applicationsCount;i++)
		{
			int curCol=sequence[i];
			for(int j=0;j<phasesCount;j++)
			{
				if(orischeduling[j][curCol]>0)
				{
					while(orischeduling[j][curCol])
					{
						int col=findNextFree(output,j,maxAvailProcessors);
						output[j][col]=curCol;
						orischeduling[j][curCol]--;
					}
				}
			}
		}
	
		*/
	
	}
	
	return 0;
}
