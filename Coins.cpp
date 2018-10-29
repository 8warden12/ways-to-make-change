#include <stdio.h>
#include <vector>
#include <set>
#include <map>
using namespace std;

int N = 0;
int numpc = 5;
int posmon[5] = {2,3,5,6,0};

struct change{
	int sum = 0;
	bool legal = false;
	set<multiset<int>> ar;
};

vector<change*> cs;

bool inCS(int n)
{
	for(int i = 0; i<cs.size(); ++i)
	{
		if(cs[i]->legal && cs[i]->sum == n)
		return true;	
	}
	return false;
}

int CSINDEX(int n)
{
	for(int i = 0; i<cs.size(); ++i)
	{
		if(cs[i]->legal && cs[i]->sum == n)
		return i;	
	}
}

bool inPM(int n)
{
	for(int i = 0; i<numpc; ++i)
	{
		if(posmon[i] == n)
		return true;
	}
	return false;
}

int PMINDEX(int n)
{
	for(int i = 0; i<numpc; ++i)
	{
		if(posmon[i] == n)
		return i;
	}
}


bool itExists(int n)
{
	return (inPM(n) || inCS(n));
}

map<int,int> getSumPairs(int n)
{
	map<int,int> m;
	for(int i = 0; i<=n/2; ++i)
	{
		if(itExists(i) && itExists(n-i))
		m.insert(make_pair(i,n-i));
	}
	return m;
}

void process(int n)
{
	change *c = new change;
	c->sum = n;
	map<int,int> mk = getSumPairs(n);
	
	set<multiset<int>> fi;
	set<multiset<int>> se;
	
	for(auto i = mk.begin(); i != mk.end(); ++i)
	{
		fi.clear();
		se.clear();
		if(inCS(i->first))
		{
			fi = cs[CSINDEX(i->first)]->ar;
		}else if(inPM(i->first))
		{
			fi.insert(multiset<int> ({i->first}));
		}
		
		if(inCS(i->second))
		{
			se = cs[CSINDEX(i->second)]->ar;
		}else if(inPM(i->second))
		{
			se.insert(multiset<int> ({i->second}));
		}
		
		for(auto u = fi.begin(); u != fi.end(); ++u)
		{
			for(auto j = se.begin(); j != se.end(); ++j)
			{
				multiset<int> v1;
				v1.insert((*u).begin(), (*u).end());
				v1.insert((*j).begin(), (*j).end());
				c->ar.insert(v1);
			}			
		}
		
		
	}
	printf("N: %d\n",n);
	for(auto x = c->ar.begin(); x != c->ar.end(); ++x)
	{
		for(auto j = (*x).begin(); j != (*x).end(); ++j)
		{
			printf("%d ",*j);
		}
		printf("\n");
	}
	
	printf("\n");
	c->legal = true;
	cs.push_back(c);
}



int main()
{
	
	
	for(int i = 1; i<50; ++i)
	{
		process(i);
	}
	
}
