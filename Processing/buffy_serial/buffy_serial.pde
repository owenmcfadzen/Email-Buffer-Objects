import processing.serial.*;

Serial port;
XML xml;

int current_time;
int previous_time;
int inbox, special1, special2, special3;
int newInbox, newSpecial1, newSpecial2, newSpecial3;
int bgcolor;
boolean checking_email = false;

void setup() {
  size(240, 160);
  background(0);

  port = new Serial(this, Serial.list()[4], 9600);
  check_mailboxes();
}

void draw() {

  background(bgcolor);

  // compare each mailbox and set a new data flag
  if (newInbox != inbox) {
    // this mailbox has a new email
    println("new inbox");
    port.write('A');
    port.write('K');
    port.write('A');
    port.write(inbox);
    bgcolor = 255;
    inbox = newInbox;
  } else if (newSpecial1 != special1) {
    // this mailbox has a new email
    println("new Special#1");
    port.write('B');
    port.write('K');
    port.write('B');
    port.write(special1);
    bgcolor = 255;
    special1 = newSpecial1;
  } else if (newSpecial2 != special2) {
    // this mailbox has a new email
    println("new Special#2");
    port.write('C');
    port.write('K');
    port.write('C');
    port.write(special2);
    bgcolor = 255;
    special2 = newSpecial2;
  } else if (newSpecial3 != special3) {
    // this mailbox has a new email
    println("new Special#3");
    port.write('D');
    port.write('K');
    port.write('D');
    port.write(special3);
    bgcolor = 255;
    special3 = newSpecial3;
  }

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
  debug_txt += "Special#3: " + special3 + "\n";
  text(debug_txt, 10, 20);

  // Fade down the background colour
  bgcolor -= 5;
  if (bgcolor < 0) {
    bgcolor = 0;
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
      } else if (name.equals("Special#3")) {
        newSpecial3 = unread;
      }
    }

    println("finished");

    // Now the data has been loaded so we can load again
    checking_email = false;
  }
}

