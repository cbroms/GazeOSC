# GazeOSC

An OSC wrapper for the [Tobii Eye Tracker 4C](https://gaming.tobii.com/tobii-eye-tracker-4c/), written in openFrameworks with the [ofxOsc](https://openframeworks.cc/documentation/ofxOsc/) and [ofxTobiiEyeX](https://github.com/TatsuyaOGth/ofxTobiiEyeX) addons.

Stream eye position data to programs running on different machines on your network.

![](/docs/demo.gif)

_The GazeOSC program on the left (on a Windows machine), sending data to a Processing receiver on the right (on a macOS machine)_

## Install

### Requirements

-   [Tobii Eye Tracker 4C](https://gaming.tobii.com/tobii-eye-tracker-4c/)
-   [Tobii Eye Tracking Core Software](https://gaming.tobii.com/getstarted/) (tested with v2.16.5)
-   Windows 10

Ensure the Tobii Core software has been installed and configured. Turn it on and calibrate through Tobii's interface.

Download the pre-built zipped executable, `gazeOSC_release_v1.0.zip` from the [releases page](https://github.com/cbroms/GazeOSC/releases/). Unzip the folder, then run the application (gazeOSC.exe).

## Configure OSC Settings and Usage

Press **f** to toggle fullscreen. The program will detect eye location regardless of if it's in fullscreen mode.

![](/docs/settings.png)

### Data

There are three categories of data that you can send from GazeOSC.

1. Eye position data. _(Green circles in GazeOSC.)_ This is the location of your eyes relative to the screen. There are X, Y, and Z coordinates for left and right eyes. Note that sometimes one or the other eye may not be detected, like when they're closed or you are looking to the side. In this case, the program sends an X, Y, and Z of -1 for that eye.

```
/eye/left/x
/eye/left/y
/eye/left/z
/eye/right/x
/eye/right/y
/eye/right/z
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

### OSC Port & Host

Set the host and port number for the OSC stream. Hit **enter/return** or **r** to update the changes you make.

### Transform Coordinates

By default, all X and Y coordinates are relative to the screen that the eye tracker is running on. You can transform the coordinates so they're relative to the size of your receiver's screen with these options. Change the height and width, and ensure `Transform Coordinates` is checked. Hit **enter/return** or **r** to update the changes you make.

## Development

To edit the GazeOSC source code, you'll need Visual Studio 2017 on a Windows machine.

1. Install the [ofxTobiiEyeX](https://github.com/TatsuyaOGth/ofxTobiiEyeX) extension to your openFrameworks directory.
2. Copy `[youOpenFrameworksDir]/addons/ofxTobiiEyeX/libs/TobiiEyeXSdk/lib/x64/Tobii.EyeX.Client.dll` to `gazeOSC/bin/`.
3. Set the build settings to `Debug` and `x64`.
4. In your Visual Studio solution explorer, right click on `gazeOSC` and go to Properties > Configuration Properties > Linker > General > Additional Library Directories > Add, then add two lines:

```
[youOpenFrameworksDir]\addons\ofxTobiiEyeX\libs\TobiiEyeXSdk\include
[youOpenFrameworksDir]\addons\ofxTobiiEyeX\libs\TobiiEyeXSdk\lib\x64
```

Now you should be able to build and run the program.

![](/docs/full_demo.gif)
