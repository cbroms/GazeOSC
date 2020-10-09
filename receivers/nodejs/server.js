const express = require("express");
const app = express();
const osc = require("osc");
const http = require("http").createServer(app);
const io = require("socket.io")(http);

//when a client connects serve the static files in the public directory
app.use(express.static("static"));

// the rate the server updates all the clients
const TICK = 1000 / 30;

const socketPort = 3000;
const oscPort = 57121;

const state = {};

// socketio client connections
io.on("connection", (socket) => {
  console.log("A user connected");
});

// send the client the new state 30 times per second
setInterval(() => {
  io.emit("state", state);
}, TICK);

// listen to the port
http.listen(socketPort, () => {
  console.log(
    `listening for client connections on http://localhost:${socketPort}`
  );
});

// create an OSC UDP Port listening on port 57121
var udpPort = new osc.UDPPort({
  localAddress: "0.0.0.0",
  localPort: oscPort,
  metadata: true,
});

// listen for incoming OSC messages from GazeOSC
udpPort.on("message", (oscMsg, timeTag, info) => {
  // update the state with the new data
  state[oscMsg.address] = oscMsg.args[0].value;
});

// open the socket
udpPort.open();
console.log(`listening for osc messages on 127.0.0.1:${oscPort}`);
