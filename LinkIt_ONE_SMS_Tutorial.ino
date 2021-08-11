#include <LGSM.h>                                                 // Include Linkit ONE GSM library
String startBuffer;                                               // Stores data entered to start the Send SMS program
String messageConfirm = "What do you want to send?";              // Asks user for input and stores it in the messageConfirm variable
String message;                                                   // Variable to store message to be sent
String confirmSend = "Do you want to send the SMS (Yes or No)?";  // Stores confirmation for the SMS to be sent
String confirmReply;                                              // Variable to store users input to confirm sending SMS

void setup() {
  
  // put your setup code here, to run once:

  Serial.begin(115200);                 // Initializes serial port at 115200 bauds
  
  while (Serial.available() == 0) {}    // Wait until user inputs data and start the program when data is received
  startBuffer = Serial.readString();    // Save the users input in startBuffer variable

  Serial.println("Starting Send SMS!"); // Start the Send SMS program
  
  while (!LSMS.ready())                 // Wait for the sim to initialize
  {
    delay(1000);                        // Wait for a second and then try again
  }
  
  Serial.println("Sim initialized");    // When SIM is started, print "Sim initialized" in the serial port

  LSMS.beginSMS("0123456789");          // Saves the number where user wants to send SMS. To be changed before uploading sketch

}

void loop() {
  
  // Put your main code here, to run repeatedly:

  Serial.println(messageConfirm);       // Prompt user to input data to send in the message
  while (Serial.available() == 0) {}    // Wait until user inputs data
  message = Serial.readString();        // Save user input in the message variable

  LSMS.print(message);                  // Prepare message variable to be sent by LSMS

  Serial.println(confirmSend);          // Prompt user to confirm sending the SMS
  while (Serial.available() == 0) {}    // Wait until user inputs data
  confirmReply = Serial.readString();   // Save user input in confirmReply variable

  if (confirmReply == "Yes") {          // Checks if confirmReply is "Yes"
    if (LSMS.endSMS())                  // If so, send the SMS
    {
      Serial.println("SMS sent");    // Print "SMS sent" in serial port if sending is successful
    }
    else
    {
      Serial.println("SMS is not sent");// Else print "SMS is not sent"
    }
  }
  else {
    Serial.println("SMS sending cancelled by user");  //If user inputs anything other than "Yes", print "SMS sending cancelled by user" in serial port
  }
  Serial.println(""); //Prints an empty line just for good formatting, to start again
}
