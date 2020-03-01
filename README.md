# GazeOSC

An OSC wrapper for the Tobii Eye Tracker 4C, written in openFrameworks with the [ofxTobiiEyeX](https://github.com/TatsuyaOGth/ofxTobiiEyeX) extension.

Stream eye position data to programs running on different machines on your network.

![](/docs/demo.gif)

_The GazeOSC program on the left (on a Windows machine), sending data to a Processing receiver on the right (on a macOS machine)_

## Install

### Requirements

-   [Tobii Eye Tracker 4C](https://gaming.tobii.com/tobii-eye-tracker-4c/)
-   [Tobii Eye Tracking Core Software](https://gaming.tobii.com/getstarted/) (tested with v2.16.5)
-   Windows 10

Ensure the Tobii Core software has been installed and configured. Turn it on and calibrate through Tobii's interface.

Download the pre-built executable, then run.

### Configure OSC Settings

![](/docs/settings.png)

#### Data

There are three categories of data that you can send from GazeOSC.

1. Eye position data. _(Green circles in GazeOSC.)_ This is the location of your eyes relative to the screen. There are X and Y coordinates for left and right eyes. Note that sometimes one or the other eye may not be detected, like when they're closed or you are looking to the side. In this case, the program sends an X and Y of -1 for that eye.

```
/eye/left/x
/eye/left/y
/eye/right/x
/eye/right/y
```

2. Gaze data. _(White circle in GazeOSC.)_ The estimation of where you're looking on the screen, as an X/Y coordinate. This stream includes movements between areas you fixate on.

```
/gaze/x
/gaze/y
```

3. Fixation data. _(Red circle in GazeOSC.)_ The estimation of where you're fixating on the screen, as an X/Y coordinate. This stream is just areas that you fixate on, and does not include movements between points.

```
/fixation/x
/fixation/y
```

#### OSC Port & Host

Set the host and port number for the OSC stream. Hit **enter/return** or **r** to update the changes you make.

#### Transform Coordinates

By default, all X and Y coordinates are relative to the screen that the eye tracker is running on. You can transform the coordinates so they're relative to the size of your receiver's screen with these options. Change the height and width, and ensure `Transform Coordinates` is checked. Hit **enter/return** or **r** to update the changes you make.
