/*-----------------------------------------------------------------------------------
Description: Displays two buttons that allow the LED of the GT-511C3 finger print
               scanner to be switched on and off.

  Purpose:     Demonstrates how to send packets to the GT-511C3 and displays the
               response packet in the Processing console window. Uses hard-coded
               packets for learning purposes. Can also be used to test the finger
               print scanner.

  Hardware:    Arduino Uno or similar, GT-511C3, interface resistors

  Software:    Load the FPS2processing sketch on the Arduino

  Date:        3 July 2015   Author:   W.A. Smith, http://startingelectronics.org

------------------------------------------------------------------------------------*/

import processing.serial.*;

Serial serial_port;

Button btnOn  = new Button("On", 30, 50, 140, 40);
Button btnOff = new Button("Off", 30, 120, 140, 40);

void setup() {
 size(200, 200);

 println(Serial.list());
 serial_port = new Serial(this, Serial.list()[0], 9600);
}

// called when mouse button is clicked
void mousePressed()
{
 if (btnOn.MouseIsOver()) {
   FpsTxLedOn();
 }
 if (btnOff.MouseIsOver()) {
   FpsTxLedOff();
 }
}

// switch the fingerprint scanner LED on
void FpsTxLedOn()
{
 byte[] tx_cmd = { 0x55, -86,               // packet header (-86 == 0xAA)
                   0x01, 0x00,              // device ID
                   0x01, 0x00, 0x00, 0x00,  // input parameter
                   0x12, 0x00,              // command code
                   0x13, 0x01 };            // checksum

 for (int i = 0; i < 12; i++) {
   serial_port.write(tx_cmd[i]);
 }
}

// switch the fingerprint scanner LED off
void FpsTxLedOff()
{
 byte[] tx_cmd = { 0x55, -86,               // packet header (-86 == 0xAA)
                   0x01, 0x00,              // device ID
                   0x00, 0x00, 0x00, 0x00,  // input parameter
                   0x12, 0x00,              // command code
                   0x12, 0x01 };            // checksum

 for (int i = 0; i < 12; i++) {
   serial_port.write(tx_cmd[i]);
 }
}

// serial port event handler
void serialEvent(Serial p)
{
 byte rx_byte;

 while (p.available() > 0) {
   // get a single character from the serial port
   rx_byte = (byte)serial_port.readChar();
   println(hex(rx_byte));
 }
}

void draw() {
   btnOn.Draw();
   btnOff.Draw();
}

// button class used for the on and off buttons
class Button {
 String label;
 float x;    // top left corner x position
 float y;    // top left corner y position
 float w;    // width of button
 float h;    // height of button

 // constructor
 Button(String labelB, float xpos, float ypos, float widthB, float heightB) {
   label = labelB;
   x = xpos;
   y = ypos;
   w = widthB;
   h = heightB;
 }

 // draw the button in the window
 void Draw() {
   fill(218);
   stroke(141);
   rect(x, y, w, h, 10);
   textAlign(CENTER, CENTER);
   fill(0);
   text(label, x + (w / 2), y + (h / 2));
 }

 // returns true if the mouse cursor is over the button
 boolean MouseIsOver() {
   if (mouseX > x && mouseX < (x + w) && mouseY > y && mouseY < (y + h)) {
     return true;
   }
   return false;
 }
}
