#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define Fill(a, b) memset(a, b, sizeof(a))

struct Street {  
	int L;
	string name;

	void readl() {
		cin>>name>>L;
	}
};

int main(){
	int D, I, S, V, F;
	cin>>D>>I>>S>>V>>F;

	unordered_map<int, vector<vector<int, Street>>> street;
	unordered_map<string, pair<int, int>> street_names;
	priority_queue<pair<int, pair<int, vector<string>>>> paths; // len of path, path no., path
	vector<pair<int, pair<string, int>>> ans;

	for (int i=0; i<S; ++i) {
		int b, e;
		cin>>b>>e;
		Street s;
		s.readl();
		street[b].emplace_back({e, s});
		street_names[s.name] = make_pair(b, e);
	}

	for (int i=0; i<V; ++i) {
		int p;
		cin>>p;
		vector<string> temp(p);
		for (auto &it: temp) {
			cin>>it;
		}
		paths.push(make_pair(p, make_pair(i, temp)));
	}

	int n = paths.size();
	vector<int> d(V, D);
	for (int i=0; i<n; ++i) {
		pair<int, vector<string>> path = paths.top().second;
		paths.pop();
		for (string e: path.second) {
			ans.push_back();
		}
	}

	cout<<ans.size()<<endl;
	for (auto e: ans) {
		cout<<e.first<<endl;
		cout<<e.second.first<<" "<<e.second.second<<endl;
	}
	return (0);
}
