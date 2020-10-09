let socket = io({
    autoConnect: true,
});

let localState = {};

socket.on("connect", () => {
    console.log("Connected to the server");
});

socket.on("disconnect", () => {
    console.log("Disconnected from the server");
});

// update the locally stored state when we get an update from the server
socket.on("state", (stateUpdate) => {
    localState = stateUpdate;
});

function setup() {
    createCanvas(window.innerWidth, window.innerHeight);
    frameRate(60);
}

function draw() {
    background(255);

    fill(0);
    noStroke();
    // draw the circle at the current gaze position, scaling by the width and
    // height of the canvas, since we're assuming all data points are
    // transformed to be 0 and 1
    circle(
        localState["/gaze/x"] * window.innerWidth,
        localState["/gaze/y"] * window.innerHeight,
        45
    );
}
