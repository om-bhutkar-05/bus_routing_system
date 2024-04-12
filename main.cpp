
  
   
  #include <iostream>
  #include "functions.cpp"

  using namespace std;
int main() {
    Graph graph(297);
    graph.populateFromJSON("assets/routes2.json");

    string p1 = "pimple gurav";
    string p2 = "swargate";

    p1 = rm(p1);
    p2 = rm(p2);

    int source = graph.getNodeID(p1);
    int destination = graph.getNodeID(p2);
    pair<vector<int>, double> result = graph.dijkstraWithPath(source, destination);
    vector<int> path = result.first;
    double totalWeight = result.second;

    cout << "Shortest path from node " << source << " to node " << destination << ": ";
    for (int node : path) {
        cout << "->" << node ;
    }
    cout << endl;

    cout << "Total weight of edges in the path: " << totalWeight << endl;

    vector<Node> nodes = graph.getNodes();
    writeLatLongToFile(nodes, path); 

    return 0;
}

  