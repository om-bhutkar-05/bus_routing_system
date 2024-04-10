#include <iostream>
#include "functions.cpp"

using namespace std;

int main() {
    Graph graph(297);
    graph.populateFromJSON("assets/routes2.json");
     
    string p1,p2;
    int source, destination;
   cout << "Enter source node: ";
    getline(cin, p1); 
    cout << "Enter destination node: ";
    getline(cin, p2);

    p1 = rm(p1);
    p2 = rm(p2);

    source = graph.getNodeID(p1);
    destination = graph.getNodeID(p2);
    vector<double> shortestDistances = graph.dijkstra(source);
    vector<Node> nodes = graph.getNodes();

    if (shortestDistances[destination - 1] == numeric_limits<double>::infinity()) {
        cout << "No path exists between the source and destination nodes." << endl;
    } else {
        cout << "Shortest distance from node " << source << " to node " << destination << ": ";
        cout << shortestDistances[destination - 1] << endl;
    }

    return 0;
}