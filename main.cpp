
    #include <iostream>
    #include "functions.cpp"

    using namespace std;

    int main() {
        Graph graph(297);
        graph.populateFromJSON("assets/routes2.json");

        string p1 = "hinjawadimaanphase3";
        string p2 = "swargate";

        p1 = rm(p1);
        p2 = rm(p2);

        int source = graph.getNodeID(p1);
        int destination = graph.getNodeID(p2);
        vector<double> shortestDistances = graph.dijkstra(source);
        vector<Node> nodes = graph.getNodes();
        writeLatLongToFile(nodes, source, destination);
        if (shortestDistances[destination - 1] == numeric_limits<double>::infinity()) {
            cout << "No path exists between the source and destination nodes." << endl;
        } else {
            cout << "Shortest distance from node " << source << " to node " << destination << ": ";
            cout << shortestDistances[destination - 1] << endl;
        }

        return 0;
    }
  