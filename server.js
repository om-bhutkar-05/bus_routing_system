const express = require('express');
const { exec } = require('child_process');
const app = express();
const port = 3000;

app.get('/run-cpp', (req, res) => {
    exec('./main', (error, stdout, stderr) => {
        if (error) {
            console.error(`Error executing main: ${error}`);
            return res.status(500).send(`Error executing main: ${error.message}`);
        }
        res.send(stdout);
    });
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
