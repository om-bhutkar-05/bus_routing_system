#include <iostream>
#include "functions.cpp"

using namespace std;

int main() {
    Graph graph(297);
    graph.populateFromJSON("assets/routes2.json");
    graph.printMatrix();
    vector<double> shortestDistances = graph.dijkstra(1);
    cout << "\nShortest Distances from Node 1:" << endl;
    vector<Node> nodes = graph.getNodes();
for (int i = 0; i < nodes.size(); ++i) {
    cout << "To " << nodes[i].name << ": " << shortestDistances[i] << endl;
}
    return 0;
}
