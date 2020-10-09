# GazeOSC Node.js Receiver

This receiver makes it possible to stream eye tracker data to the browser. A node.js server listens for OSC data, converts it to JSON, then sends it to a browser client over socketio websockets.

## Run it

### GazeOSC setup

Set these parameters in the GazeOSC options, then press `r` on your keyboard.

```
Host: 127.0.0.1
Port: 57121
Transform Coodinates: true
Height: 1
Width: 1
```

This sets the proper location to send the data and adjusts all data that's sent to be between 0 and 1, so we can rescale it correctly on the browser.

### Run the receiver

To setup the server, first install the dependencies:

```
npm install
```

Then, run the server:

```
npm run start
```

This should print:

```
listening for osc messages on 127.0.0.1:57121
listening for client connections on http://localhost:3000
```

Verify that GazeOSC is sending to the proper address (i.e. that the green address in GazeOSC matches the first address printed out by the node server). If it's not correct, adjust your GazeOSC settings to fit the host and port printed (ensuring you hit `r` to reload the program).

Now you can navigate to `http://localhost:3000` in your browser and you should see your gaze rendered onscreen. In order to get the most accurate mapping, set the browser to fullscreen mode (usually f11).
