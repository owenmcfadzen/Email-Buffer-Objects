import processing.serial.*;

Serial port;
XML xml;

int current_time;
int previous_time;
int inbox, special1, special2;
int mailThreshold = 50;
char[] ledNumbers = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};
int newInbox, newSpecial1, newSpecial2;
int bgcolor;
boolean checking_email = false;

void setup() {
  size(240, 160);
  background(0);

  port = new Serial(this, Serial.list()[4], 9600);
  check_mailboxes();
}

void draw() {

  //    while( port.available()>0) { // this is the part to print out what arduino recived
  //      print((char) port.read()); // this too 
  //    }
  background(bgcolor);


  // check mailboxes again
  if (!checking_email) {
    current_time = millis();
    if (current_time - previous_time > 10 * 1000) {
      check_mailboxes();
      previous_time = current_time;
    }
  }

  // Show a number for debugging
  String debug_txt = "INBOX: " + inbox + "\n";
  debug_txt += "Special#1: " + special1 + "\n";
  debug_txt += "Special#2: " + special2 + "\n";
  text(debug_txt, 10, 20);

  // Fade down the background colour
  bgcolor -= 5;
  if (bgcolor < 0) {
    bgcolor = 0;
  }

  // compare each mailbox and set a new data flag
  if (newInbox != inbox) {
    inbox = newInbox;
    // this mailbox has a new email
    //    port.write('A');
    //    port.write('K');
    port.write('A');
    // if the mailbox is not empty then send a number
    int aMail = (inbox > 0) ? constrain(floor(map(inbox, 0, mailThreshold, 0, 8)), 0, 8) : 0;
    port.write(ledNumbers[aMail]);
    print("A:INBOX = " + aMail);
    bgcolor = 255;
  } else if (newSpecial1 != special1) {
    // this mailbox has a new email
    special1 = newSpecial1;                  
    //    port.write('B');
    //    port.write('K');
    port.write('B');
    // if the mailbox is not empty then send a number
    int bMail = (special1 > 0) ? constrain(floor(map(special1, 0, mailThreshold, 0, 8)), 0, 8) : 0;
    port.write(ledNumbers[bMail]);
    print(", B:Special#1 = " + bMail);
    bgcolor = 255;
  } else if (newSpecial2 != special2) {
    // this mailbox has a new email
    special2 = newSpecial2;
    //    port.write('C');
    //    port.write('K');
    port.write('C');
    // if the mailbox is not empty then send a number
    int cMail = (special2 > 0) ? constrain(floor(map(special2, 0, mailThreshold, 0, 8)), 0, 8) : 0;
    port.write(ledNumbers[cMail]);
    println(", C:Special#3 = " + cMail);
    bgcolor = 255;
  }
}

void check_mailboxes() {
  if (!checking_email) {

    // set the checking_email flag so this function cannot be called
    // again until the new data has been loaded from PHP
    checking_email = true;

    print("check_mailboxes...");

    xml = loadXML("http://www.nckn.dk/emails/index-2.php");
    XML[] children = xml.getChildren("mailbox");

    for (int i = 0; i < children.length; i++) {
      int unread = children[i].getInt("unread");
      String name = children[i].getContent();

      /* FIRST – capture each mailbox */
      if (name.equals("INBOX")) {
        newInbox = unread;
      } else if (name.equals("Special#1")) {
        newSpecial1 = unread;
      } else if (name.equals("Special#2")) {
        newSpecial2 = unread;
      }
    }

    println("finished");

    // Now the data has been loaded so we can load again
    checking_email = false;
  }
}

void mousePressed() {
  print("DEBUG >> ");
  // send the values to the Serial port
  int aMail = (inbox > 0) ? constrain(floor(map(inbox, 0, mailThreshold, 0, 8)), 0, 8) : 0;
  port.write('A');
  port.write('K');
  port.write('A');
  port.write(ledNumbers[aMail]);
  print("A:INBOX = " + aMail);
  //
  int bMail = (special1 > 0) ? constrain(floor(map(special1, 0, mailThreshold, 0, 8)), 0, 8) : 0;
  port.write('B');
  port.write('K');
  port.write('B');
  port.write(ledNumbers[bMail]);
  print(", B:Special#1 = " + bMail);
  //
  int cMail = (special2 > 0) ? constrain(floor(map(special2, 0, mailThreshold, 0, 8)), 0, 8) : 0;
  port.write('C');
  port.write('K');
  port.write('C');
  port.write(ledNumbers[cMail]);
  println(", C:Special#3 = " + cMail);
  bgcolor = 255;
}

