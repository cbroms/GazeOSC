const express = require("express");
const app = express();
const osc = require("osc");
const http = require("http").createServer(app);
const io = require("socket.io")(http);

const colors = require("colors");

//when a client connects serve the static files in the public directory
app.use(express.static("static"));

// the rate the server updates all the clients
const TICK = 1000 / 20;

const socketPort = 5000;
const oscPort = 57121;

const state = {};

let gotData = { lastTick: false, thisTick: false, numMissing: 0 };

// socketio client connections
io.on("connection", (socket) => {
  console.log("A user connected");
});

// send the client the new state 30 times per second
setInterval(() => {
  // print the connection status
  if (
    !gotData.lastTick &&
    !gotData.thisTick &&
    gotData.numMissing % 1000 === 0
  ) {
    console.log(
      `Have not received data from GazeOSC for ${gotData.numMissing / 1000}s...`
        .red
    );
  } else if (!gotData.lastTick && gotData.thisTick) {
    console.log("Successfully receiving data from GazeOSC...".green);
  }
  // send the state
  io.emit("state", state);

  // reset the connection status
  gotData.lastTick = gotData.thisTick;
  gotData.thisTick = false;
  gotData.numMissing += TICK;
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

  // mark that we received some data from the tracker
  gotData.thisTick = true;
  gotData.numMissing = 0;
});

// open the socket
udpPort.open();
console.log(`listening for osc messages on 127.0.0.1:${oscPort}`);
