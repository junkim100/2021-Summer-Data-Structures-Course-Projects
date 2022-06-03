#include "digraph.h"
using namespace std;

//Constructor
DigraphMatrix::DigraphMatrix(const string& filename) {
    ifstream in(filename);
    string line;
    istringstream iss;
    int temp;

    //Read from the input file and save them into file
    while (!in.eof()) {
        getline(in, line);
        iss.str(line);
        while (iss >> temp)
            file.push_back(temp);
        iss.clear();
    }

    //Turn file into an edge list form and store it into edgeList
    for (int i = 0; i < file.size(); i+=2)
        edgeList[file[i]].push_back(file[i+1]);
}

vector<int> DigraphMatrix::topologicalSort() {
    //While vertices undiscovered
	for (auto i : edgeList) {
		int v = i.first;
		if (!discovered[v]) {
            //Push v into cycleTrack
            //cycleTrack is used to track the vertices that we have visited
			cycleTrack.push_back(v);
            //DFS-Recursive(v)
			DFS(v);
		}
	}

    //Reverse vector and return
	for(auto v : order)
		reverse.push_back(v);
	return reverse;
}

//DFS-Recursive(v)
void DigraphMatrix::DFS(int v){
    //Mark v discovered
	discovered[v] = true;

    //for i in neighbors, DFS-Recursive(v)
	for(auto i : edgeList[v]){
        //If neighbor is undiscovered
		if(!discovered[i]) {
            //Push v into cycleTrack
            //cycleTrack is used to track the vertices that we have visited
			cycleTrack.push_back(i);
            //DFS-Recursive(v)
			DFS(i);
		} 

        //Skip if neighbor is already explored
        else if (explored[i]) {
			continue;
		}
        
        //Check for cycle
        else {
            //Go through the vertices that we visited and compare
			for (auto j : cycleTrack) {
                //This is the case where there are no neighbors
                //ex) 8 8 from sample-graph2.txt
				if (j == v) {
					break;
				} 
                //This is when we encounter a cycle
                else if (j == i) {
					throw exception();
				}
			}
		}
	}

    //Mark v explored
	explored[v] = true;

    //Add v to order
	order.push_front(v);
}
