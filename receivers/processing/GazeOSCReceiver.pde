import oscP5.*;

OscP5 oscP5;
PVector gazePos = new PVector(0, 0);
PVector fixationPos = new PVector(0, 0);

void setup() {
  
  size(1200, 800);
  frameRate(30);
  noStroke();
  
  oscP5 = new OscP5(this, 8888);
  oscP5.plug(this, "gazeX", "/gaze/x");
  oscP5.plug(this, "gazeY", "/gaze/y");
  oscP5.plug(this, "fixationX", "/fixation/x");
  oscP5.plug(this, "fixationY", "/fixation/y");
}

void draw() {
  background(10);
  fill(255);
  ellipse(gazePos.x, gazePos.y, 20, 20);
  fill(255, 0, 0);
  ellipse(fixationPos.x, fixationPos.y, 10, 10);
}

void gazeX(float x) {
   gazePos.x = x;
}

void gazeY(float y) {
  gazePos.y = y;
}

void fixationX(float x) {
  fixationPos.x = x;
}

void fixationY(float y) {
  fixationPos.y = y;
}
