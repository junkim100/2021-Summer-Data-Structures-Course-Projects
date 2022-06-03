#ifndef __DIGRAPH_H
#define __DIGRAPH_H

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class DigraphMatrix{
private:
    //Vertices are stored here when first read from input file
    vector<int> file;

    //Vertices in file is stored here as an edge list
	map<int, vector<int> > edgeList;

    //keeps track of whether vectors are discovered/explored or not
	map<int, bool> discovered;
	map<int, bool> explored;

    //This is where vertices are added in DFS(v)
	list<int> order;

    //This is the reverse of order which will be returned from topologicalSort()
    vector<int> reverse;

    //cycleTrack is used to track the vertices that we have visited
    vector<int> cycleTrack;
    
public:
    //Constructor
	DigraphMatrix(const string& filename);

    vector<int> topologicalSort();

    //DFS-Recursive(v)
	void DFS(int v);
};
#endif