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

unordered_map<int, vector<pair<int, Street>>> streets;
unordered_map<string, pair<int, int>> street_names;	// street_names[name] = a to b
vector<string> paths[VMX];

int main(){
	int D, I, S, V, F;
	cin>>D>>I>>S>>V>>F;
	unordered_map<int, pair<int, queue<int>>> in_cars;	// i-th car maps to streets left to take
	vector<pair<int, pair<int, int>>> in_transit;	// <time, <i-th car, to_intersection>>
	vector<pair<int, pair<string, int>>> ans;

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
		in_cars[street_names[paths[i][0]].second].first = street_names[paths[i][0]].first;
		in_cars[street_names[paths[i][0]].second].second.push(i);
	}

	// run simulation
	for (int t=0; t<D; ++t) {

		for (int i=0; i<in_transit.size(); ++i) {
			// move car from street to intersection queue if transit time complete
			if (in_transit[i].first==1){
				in_cars[street_names[paths[in_transit[i].second.second][0]].second].second.push(in_transit[i].second.first);
				in_transit.erase(in_transit.begin() + i);
				--i;
			}
			// else reduce transit time
			else {
				--in_transit[i].first;
			}
		}

		for (int i=0; i<I; ++i)
	}
	return (0);
}
