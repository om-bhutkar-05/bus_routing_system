#include <iostream>
#include <fstream>
#include "functions.cpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main() {
    // Read data from routes2.json
    ifstream file(("./assets/routes2.json"));
    json data;
    file >> data;
    file.close();

    // Create a graph
    Graph graph;

    // Add vertices from JSON data
    for (const auto& place : data["places"]) {
        graph.addVertex(place["id"], place["place_name"], stod(place["latitude"].get<string>()), stod(place["longitude"].get<string>()));
    }

    // Add edges from JSON data
    for (const auto& connection : data["connections"]) {
        graph.addEdge(connection["source"], connection["destination"], stod(connection["weight"].get<string>()));
    }

    // Take input from the user for source and destination names
    string sourceName, destinationName;
    cout << "Enter source place name: ";
    getline(cin, sourceName);
    cout << "Enter destination place name: ";
    getline(cin, destinationName);

    // Get corresponding vertex IDs
    string sourceId = graph.getVertexIdByPlaceName(sourceName);
    string destinationId = graph.getVertexIdByPlaceName(destinationName);

    // Check if both source and destination IDs are valid
    if (sourceId.empty() || destinationId.empty()) {
        cout << "Invalid place names." << endl;
        return 1;
    }

    // Find the shortest path
    list<string> path = graph.shortestPath(sourceId, destinationId);

    // Output the distance of the shortest path
    if (!path.empty()) {
        double distance = graph.getVertex(destinationId)->distance;
        cout << "Distance of shortest path: " << distance << endl;

        // Display the shortest path
        cout << "Shortest path from " << sourceName << " to " << destinationName << ":" << endl;
        for (const auto& vertex : path) {
            cout << graph.getVertex(vertex)->place_name << " -> ";
        }
        cout << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
