#include <bits/stdc++.h>
#include <string>

using namespace std;

int main() {

    string fname = "a_example";
    
    ifstream cin("input/" + fname + ".in");
    ofstream cout("output/" + fname + ".out");

    int n, t2, t3, t4;   
    cin >> n >> t2 >> t3 >> t4;
    cout << "No. of pizza :" << n << endl;
    cout << "No. of 2 member team :" << t2 << endl;
    cout << "No. of 3 member team :" << t3 << endl;
    cout << "No. of 4 member team :" << t4 << endl;
}