import processing.serial.*;

Serial port;

XML xml;

int time;
int previousTime;
int interval = 5000;
int inbox, special1, special2, special3;
int newInbox, newSpecial1, newSpecial2, newSpecial3;
int mail_color;

int counter = 1;

void setup() {
  size(240, 160);
  background(0);
  
  port = new Serial(this, Serial.list()[4], 9600);
}

void draw() {
  
  background(mail_color);

  time = millis();

  if (time - previousTime > interval) {
     port.write("A");
    port.write(floor(random(0, 7)));
     mail_color = 255;
//    check_mailboxes();
    previousTime = time;
  }
  
  
  if(inbox!=newInbox) {
    port.write("A");
    port.write(123);
    /*port.Write("B");
    port.Write(1);*/
    mail_color = 255;
  }
  
  mail_color-=5;

  if(mail_color<0) mail_color=0;
    
  // compare inboxes
  inbox = newInbox;
  special1 = newSpecial1;
  special2 = newSpecial2;
  special3 = newSpecial3;

}

void check_mailboxes() {
  xml = loadXML("http://www.nckn.dk/emails/index-2.php");
  XML[] children = xml.getChildren("mailbox");

  for (int i = 0; i < children.length; i++) {
    int unread = children[i].getInt("unread");
    String name = children[i].getContent();

    if (name.equals("INBOX")) {
      newInbox = unread;
    }
    else if (name.equals("Special#1")) {
      newSpecial1 = unread;
    }
    else if (name.equals("Special#2")) {
      newSpecial2 = unread;
    }
    else if (name.equals("Special#3")) {
      newSpecial3 = unread;
    }
  }
  
 
}



