#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define Fill(a, b) memset(a, b, sizeof(a))
#define IMX 100000
#define VMX 1000

struct Street {
	int L;
	string name;

	void readl() {
		cin>>name>>L;
	}
};

vector<pair<int, Street>> streets[IMX];
map<string, pair<int, int>> street_names;
vector<string> paths[VMX];


int main(){
	int D, I, S, V, F;
	cin>>D>>I>>S>>V>>F;

	// input streets
	for (int i=0; i<S; ++i) {
		int b, e;
		cin>>b>>e;
		Street s;
		s.readl();
		streets[b].emplace_back(make_pair(e, s));
		street_names[s.name] = make_pair(b, e);
	}

	// input car paths
	for (int i=0; i<V; ++i) {
		int p;
		cin>>p;
		for (int j=0; j<p; ++j) {
			string s;
			cin>>s;
			paths[i].emplace_back(s);
		}
	}
	return (0);
}
