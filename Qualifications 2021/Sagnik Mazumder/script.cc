#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define pii pair<int, int>
#define MAXN 100100

int D, I, S, V, F;

map<string,int> streetIds;
vector<string> streetNames;

struct Street {
	int B, E, L;
	string name;
	int id;

	void read() {
		cin>>B>>E>>name>>L;
		id = streetIds.size();
    	streetIds[name] = id;
    	streetNames[id] = name;
	}
};

struct Car {
  	vi path;

  	void read() {
    	int n;
    	cin>>n;
    	path.resize(n);
	    for (int i = 0; i < n; ++i) {
			string s;
			cin>>s;
    		path[i] = streetIds[s];
    	}
  	}
};

vector<pii> adj[MAXN];
vector<pii> adji[MAXN];

vector<Street> streets;
vector<Car> cars;

bool used[MAXN];

vector<vi> simulate() {
	vector<vi> X(I);
	for (int i = 0; i < I; ++i) {
    	int cnt = 0;
		for (pii v : adji[i]) {
			if (used[v.second])
        		cnt++;
    	}
    	X[i].resize(cnt, -1);
  	}
  	vi Xi(S, -1);

  	// queue for each intersections
  	vector<queue<int>> q(S);

	// events is "releasing a car from an intersection queue"
  	// events[t] = queue<street id to process>
  	vector<queue<int>> events(D+1);

  	// qevents is "a car entering an intersection queue"
  	// qevents[t] = queue<street id, car id>
  	vector<queue<pii>> qevents(D+1);

  	// events are triggered by:
  	// - a car entering a queue

  	// at t = 0, initialize all cars at the end of the streets
  	vi p(V); // index of car path
  	for (int i = 0; i < V; ++i) {
    	int streetId = cars[i].path[p[i]];
    	qevents[0].emplace(streetId, i);
  	}

  	vi arrival(V, -1);

  	for (int t = 0; t <= D; ++t) {
    	// insert cars into queue
    	while (!qevents[t].empty()) {
      		pii front = qevents[t].front();
      		qevents[t].pop();

      		int streetId = front.first;
      		int carId = front.second;
      		if (q[streetId].empty()) {
        		events[t].push(streetId);
    		}
      		q[streetId].push(carId);
    	}

    	while (!events[t].empty()) {
      		int id = events[t].front();
      		events[t].pop();

      		queue<int>& qs = q[id];
	      	assert(!qs.empty());

    		int iid = streets[id].E;
    		int _t = t;
    		int cycle = X[iid].size();
    		int mod = t % cycle;
      		// check if id is assigned
      		if (Xi[id] != -1) {
        		int cycle = X[iid].size();
        		_t = cycle * (t / cycle) + Xi[id];
        		if (_t < t) {
          			_t += cycle;
        		}
      		}
			else if (X[iid][mod] == -1) {
        		// assign it right away
        		X[iid][mod] = id;
        		Xi[id] = mod;
      		}
			else {
        		// defer to t+1
        		_t = t + 1;
      		}

      		if (t != _t) {
        		if (_t <= D) {
          			events[_t].push(id);
        		}
      		}
      		else {
        		// take single car in the queue
        		int c = qs.front(); qs.pop();
        		p[c]++;
        		assert(p[c] < cars[c].path.size());
        		int snext = cars[c].path[p[c]];
        		int inext = streets[snext].E;
        		int tnext = t + streets[snext].L;

        		if (tnext <= D) {
          		// arrive
        			if (p[c] == cars[c].path.size() - 1) {
            			arrival[c] = tnext;
          			}
          			else {
            			qevents[tnext].emplace(snext, c);
          			}
        		}

        		// reinsert self into events if queue is still not empty
        		if (!qs.empty() && t < D) {
          			events[t + 1].push(id);
        		}
      		}
    	}
  	}

  	// assign what's left randomly
  	int maxslots = 0;
  	for (int i = 0; i < I; ++i) {
    	vi slots;
    	for (int j = 0; j < X[i].size(); ++j) {
      		if (X[i][j] == -1) {
        		slots.push_back(j);
      		}
    	}
    	maxslots = max(maxslots, (int)slots.size());

    	for (pii v : adji[i]) {
      		if (used[v.second] && Xi[v.second] == -1) {
        		Xi[v.second] = slots.back();
        		X[i][slots.back()] = v.second;
        		slots.pop_back();
      		}
    	}
  	}
  	int score = 0;
  	for (int c = 0; c < V; ++c) {
    	if (arrival[c] == -1) continue;
    	assert(arrival[c] <= D);
    	score += F + D - arrival[c];
  	}

  	for (int i = 0; i < I; ++i) {
    	for (int j = 0; j < X[i].size(); ++j) {
      		assert(X[i][j] != -1);
    	}
  	}

  	return X;
}

int main() {
  	cin>>D>>I>>S>>V>>F;

  	streets.resize(S);
  	streetNames.resize(S);
  	for (int i = 0; i < S; ++i) {
    	streets[i].read();
    	adj[streets[i].B].emplace_back(streets[i].E, streets[i].id);
    	adji[streets[i].E].emplace_back(streets[i].B, streets[i].id);
  	}

  	cars.resize(V);
  	for (int i = 0; i < V; ++i) {
    	cars[i].read();
    	for (int s : cars[i].path) {
      		used[s] = true;
    	}
  	}

  	vector<vi> X = simulate();

  	vector<vector<pii>> ans;

  	for (int v = 0; v < I; ++v) {
    	vector<pii> schedule;
    	for (int x : X[v]) {
      		schedule.emplace_back(x, 1);
    	}
    	ans.emplace_back(schedule);
  	}
  	assert(ans.size() == I);

  	int nans = 0;
  	for (int v = 0; v < I; ++v) {
    	if (ans[v].size()) {
      		nans++;
    	}
  	}
  	printf("%d\n", nans);
  	for (int v = 0; v < I; ++v) {
    	if (!ans[v].size()) continue;
    	printf("%d\n%d\n", v, (int)ans[v].size());
    	for (pii y : ans[v]) {
      		printf("%s %d\n", streetNames[y.first].c_str(), y.second);
    	}
  	}

  	return 0;
}