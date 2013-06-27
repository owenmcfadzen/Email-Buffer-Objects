import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class get_unread_emails extends PApplet {

XML xml;
int time;
int last_time;
int fill_color;

/* store the current unread counts */
int inbox, special1, special2, special3;

/* store the new unread counts */
int new_inbox, new_special1, new_special2, new_special3;

public void setup() {
  size(displayWidth, displayHeight);
  background(0);
  
  /* get the initial email counts */
  check_mailboxes();
  inbox = new_inbox;
  special1 = new_special1;
  special2 = new_special2;
  special3 = new_special3;
}

public void draw() {
  background(fill_color);

  /* STEP 1 \u2013 tick and get the new data from the mailboxes */
  time = millis();
  if (time - last_time > 5 * 1000) {
    check_mailboxes();    
    last_time = time;
  }

  /* STEP 2 \u2013 compare a mailbox */
  if (special2 != new_special2) {
    println("WOW A NEW EMAIL");
    fill_color = 255;
  }

  fill_color -= 5;
  if (fill_color < 0) {
    fill_color = 0;
  }

  /* STEP 3 \u2013 update all inbox counts */
  inbox = new_inbox;
  special1 = new_special1;
  special2 = new_special2;
  special3 = new_special3;
}

public void check_mailboxes() {
  xml = loadXML("http://thisishomemade.co.uk/ciid_emails/index2.php");
  XML[] children = xml.getChildren("mailbox");

  for (int i = 0; i < children.length; i++) {
    int unread = children[i].getInt("unread");
    String name = children[i].getContent();

    // check each label and save the unread values
    if (name.equals("INBOX")) {
      new_inbox = unread;
    } else if (name.equals("Special#1")) {
      new_special1 = unread;
    } else if (name.equals("Special#2")) {
      new_special2 = unread;
    } else if (name.equals("Special#3")) {
      new_special3 = unread;
    }
  }
}

  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "--full-screen", "--bgcolor=#666666", "--hide-stop", "get_unread_emails" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
