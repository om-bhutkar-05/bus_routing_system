const express = require('express');
const fs = require('fs');
const app = express();
const port = 3000;

app.get('/submit-location', (req, res) => {
    const { startingPoint, destination } = req.query;

    // Format the data
    const data = `Starting Point: ${startingPoint}\nDestination: ${destination}\n`;

    // Write the data to the file (clear existing data)
    fs.writeFile('data.txt', data, (err) => {
        if (err) {
            console.error('Error writing to file:', err);
            res.status(500).send('Error saving data');
            return;
        }
        console.log('Data has been written to the file');
        const { exec } = require('child_process');
const fs = require('fs');

// Read the contents of data.txt
fs.readFile('data.txt', 'utf8', (err, data) => {
  if (err) {
    console.error(`Error reading file: ${err}`);
    return;
  }

  // Modify the C++ program to read data from data.txt
  const cppProgram = `
    #include <iostream>
    #include "functions.cpp"

    using namespace std;

    int main() {
        Graph graph(297);
        graph.populateFromJSON("assets/routes2.json");

        string p1 = "${startingPoint}";
        string p2 = "${destination}";

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
  `;

  // Save the modified C++ program to a temporary file
  fs.writeFile('main.cpp', cppProgram, (err) => {
    if (err) {
      console.error(`Error writing temporary file: ${err}`);
      return;
    }

    // Compile and execute the modified C++ program
    exec(' g++ main.cpp -o main && main.exe', (error, stdout, stderr) => {
      if (error) {
        console.error(`Error: ${error.message}`);
        return;
      }
      if (stderr) {
        console.error(`Error: ${stderr}`);
        return;
      }
      console.log(`Output: ${stdout}`);
    });
  });
});

        res.redirect('http://127.0.0.1:5500/a.html' + '?' + startingPoint + '?' + destination);
        // Send a response to the client
        // res.status(200).send('Data saved successfully!');
    });
});

app.listen(port, () => {
    console.log(`Server is running on http://localhost:${port}`);
});
