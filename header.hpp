

#include <vector>
#include <iostream>
#include <limits>
#include <string>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct Node {
    int id;
    string name;
};

class Graph {
private:
    int V;
    vector<Node> nodes;
    vector<vector<double>> adjMatrix;

public:
vector<Node> getNodes() const { return nodes; }
    Graph(int vertices);
    void addEdge(int source, int destination, double weight);
    void populateFromJSON(const string& filename);
    void printMatrix();
    vector<double> dijkstra(int source);
};


