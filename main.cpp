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

    // Display the graph
    graph.display();

    return 0;
}
