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
    string lat;
    string lon;
};

class Graph {
private:
    int V;
    vector<Node> nodes;
    vector<vector<double>> adjMatrix;

public:
 int getNodeID(const string& placeName) const;
vector<Node> getNodes() const { return nodes; }
    Graph(int vertices);
    void addEdge(int source, int destination, double weight);
    void populateFromJSON(const string& filename);
    void printMatrix();
    vector<double> dijkstra(int source);
};


