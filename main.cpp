#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>
#include <limits.h>

using namespace std;

typedef size_t uint;

template <class T,class V>
class pair_first_comp
{
public:
	T operand;
	bool operator()(pair<T,V> value)
	{
		return operand==value.first;
	}
};


template<class T>
class graf
{
private:
	vector<T> data;
	vector<list<pair <uint,int> > > links;
	uint edgeCount;
public:
	graf( const vector<T>& _data)
	{
		data=_data;
		uint n=_data.size();
		for(uint i=0;i<n;i++)
		{
			list<pair <uint,int> > temp;
			links.push_back(temp);
		}
	}
	int addLink(uint from, uint to, int weight)
	{
		if(links.size()>from && links.size()>to)
		{
			links[from].push_back(pair<uint,int>(to,weight));
			return 0;
		}else{
			return -1;
		}
		edgeCount++;
	}
	void addNode(const T& element)
	{
		data.push_back(element);
		list<pair <uint,int> > temp;
		links.push_back(temp);
	}
	void printGraf()
	{
		for(uint i=0;i<links.size();i++)
		{
			cout<<data[i]<<endl;
			list<pair<uint,int> >::iterator it=links[i].begin();
			while(it!=links[i].end())
			{
				cout<<data[i]<<" ->"<<data[(*it).first]<<" [ label = \""<<(*it).second<<"\"]"<<endl;
				it++;
			}
		}
	}
	pair<bool,int> isDirectWay(uint from,uint to)
	{
		pair_first_comp<uint,int> cmp;
		cmp.operand=to;
		list<pair<uint,int> >::iterator it=find_if(links[from].begin(),links[from].end(),cmp);
		if(links[from].end()==it)
		{
			return pair<bool,int>(false,0);
		}else{
			return pair<bool,int>(true,it->second);
		}
	}
	pair<bool,int> Dijkstra(uint from,uint to)// O(N^2)
	{//using array
		vector< pair<bool,int> > dist(data.size(), pair<bool,int>(0,-1));// array of lenght (bool=0 => unexplored)
		vector<int> prev (data.size(),-1);//array of previous vertexes in the way
		dist[from]=pair<bool,int>(1,0);
		uint curr=from;
		bool complete=false;
		while(!complete)
		{
			list<pair<uint,int> >::iterator it=links[curr].begin();
			while(it!=links[curr].end())
			{
				if(!dist[it->first].first)
				{
					if(dist[it->first].second!=-1)
					{
						dist[it->first].second=min(dist[it->first].second, dist[curr].second + it->second);
					}else{
						dist[it->first].second= dist[curr].second + it->second;
					}
				}
				it++;
			}
			int min=INT_MAX; //magic
			int imin=-1;
			for(uint i=0;i<dist.size();i++)
			{
				if(dist[i].first==0 && dist[i].second!=-1)
				{
					if(dist[i].second<min)
					{
						min=dist[i].second;
						imin=i;
					}
				}
			}
			if(-1==imin)
			{
				complete=true;
			}else{
				curr=imin;
				dist[imin].first=true;
			}
			
		}
		return dist[to];
	}
	
	
	pair<bool,int> shortestWay(uint from,uint to)
	{//Bellman-Ford alhorithm
		 vector< pair<bool,int> > dist(data.size(), pair<bool,int>(0,0));// array of lenght (bool=0 => infinite)
		 vector<int> prev (data.size(),-1);//array of previous vertexes in the way
		 dist[from]=pair<bool,int>(1,0);
		 for(uint i=0;i<data.size()-1;i++)
		 {
			 for(uint j=0;j<data.size();j++)
			 {
				 if(dist[j].first)
				 {
					 list<pair<uint,int> >::iterator it=links[j].begin();
					 while(it!=links[j].end())
					 {
						 if(dist[it->first].first)
						 {
							 //not inf
							 if(dist[it->first].second>(dist[j].second+it->second))
							 {
								 dist[it->first].second=dist[j].second+it->second;
								 prev[it->first]=j;
							 }
						 }else{
							 //inf
							 dist[it->first]=pair<bool,int>(1,dist[j].second+it->second);
							 prev[it->first]=j;
						 }
						 it++;
					 }
				 }
			 }
		 }
		 
		/*
		 cout<<data[to]<<"<-";
		 int p=prev[to];
		 while(p!=-1)
		 {
			 cout<<data[p]<<"<-";
			 p=prev[p];
		 }
		 cout<<endl;
		 */
		 return dist[to];
	}
};


int main()
{
	vector<int> arr;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);
	arr.push_back(4);
	arr.push_back(5);
	graf<int> g(arr);
	
	
	g.addLink(0,1,3);
	g.addLink(0,3,2);
	g.addLink(1,4,2);
	g.addLink(2,4,1);
	g.addLink(3,2,1);
	g.addLink(3,4,4);
	/*
	g.addLink(0,1,5);
	g.addLink(0,3,10);
	g.addLink(1,2,5);
	g.addLink(1,4,1);
	g.addLink(2,4,1);
	g.addLink(3,2,-7);
	g.addLink(3,4,-4);
	
	cout<<"shortest way: "<<g.shortestWay(0,4).second<<endl;
	*/
	cout<<"dijkstra: "<<g.Dijkstra(0,4).second<<endl;
	
	g.printGraf();
	cout<<"way: "<<g.isDirectWay(0,2).second<<endl;
	return 0;
}