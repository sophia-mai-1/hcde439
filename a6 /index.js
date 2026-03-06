const BAUD_RATE = 9600; // This should match the baud rate in your Arduino sketch

let port, connectBtn, serial, inData; // Declare global variables
let shapeFraction = 0;
let buttonColor = 0;
let motionColor = 0;
let buttonFade = 50;
let motionFade = 25;


function setup() {
  setupSerial(); // Run our serial setup function (below)

  // Create a canvas that is the size of our browser window.
  // windowWidth and windowHeight are p5 variables
  createCanvas(windowWidth, windowHeight);
  

}


function draw() {
  const portIsOpen = checkPort(); // Check whether the port is open (see checkPort function below)
  if (!portIsOpen) return; // If the port is not open, exit the draw loop

  let str = port.readUntil("\n"); // Read from the port until the newline
  if (str.length == 0) return; // If we didn't read anything, return.

  let arr = str.trim().split(","); // Trim whitespace and split on commas

  // Convert each element to a number and map it to the desired range
  console.log(arr);
  let x = arr[0];
  let y = arr[1];

  console.log("button " + buttonColor);
  console.log("motion " + motionColor);

  let circleColor = color(buttonColor, motionColor, 255);


  background("black");
  noStroke(); // turn off outline
  fill(circleColor); // white circle

  // Get x,y center of drawing Canvas
  let xCenter = width / 2;
  let yCenter = height / 2;
  
  const maxDi = min(width, height);
  let shapeFraction = mouseX / width;
  // console.log("sf " + shapeFraction);
  let circleDiameter = maxDi * shapeFraction;
  circle(xCenter, yCenter, circleDiameter);

  if (x == 1) {
    if (buttonColor <= 0 || buttonColor >= 255) {
      buttonFade = -buttonFade;
    }
    buttonColor = constrain(buttonColor + buttonFade, 0, 255); // ✅ only updates when button is pressed
  }

  if (y == 1) {
    if (motionColor <= 0 || motionColor >= 255) {
      motionFade = -motionFade;
    }
    motionColor = constrain(motionColor + motionFade, 0, 255); // ✅ only updates when motion detected
  }

  // buttonColor = buttonColor + buttonFade;
  // motionColor = motionColor + motionFade;
}
  

 // Three helper functions for managing the serial connection.

function setupSerial() {
  port = createSerial();

  // Check to see if there are any ports we have used previously
  let usedPorts = usedSerialPorts();
  if (usedPorts.length > 0) {
    // If there are ports we've used, open the first one
    port.open(usedPorts[0], BAUD_RATE);
  }

  connectBtn = createButton("Connect to Arduino");
  connectBtn.position(5, 5); // Position the button in the top left of the screen.
  connectBtn.mouseClicked(onConnectButtonClicked); // When the button is clicked, run the onConnectButtonClicked function
}

function checkPort() {
  if (!port.opened()) {
    // If the port is not open, change button text
    connectBtn.html("Connect to Arduino");
    // Set background to gray
    background("black");
    return false;
  } else {
    // Otherwise we are connected
    connectBtn.html("Disconnect");

    return true;
  }
}

function onConnectButtonClicked() {
  // When the connect button is clicked
  if (!port.opened()) {
    // If the port is not opened, we open it
    port.open(BAUD_RATE);
  } else {
    // Otherwise, we close it!
    port.close();
  }
}
