XML xml;
int time;
int last_time;
int fill_color;

/* store the current unread counts */
int inbox, special1, special2, special3;

/* store the new unread counts */
int new_inbox, new_special1, new_special2, new_special3;

void setup() {
  size(displayWidth, displayHeight);
  background(0);
  
  /* get the initial email counts */
  check_mailboxes();
  inbox = new_inbox;
  special1 = new_special1;
  special2 = new_special2;
  special3 = new_special3;
}

void draw() {
  background(fill_color);

  /* STEP 1 – tick and get the new data from the mailboxes */
  time = millis();
  if (time - last_time > 5 * 1000) {
    check_mailboxes();    
    last_time = time;
  }

  /* STEP 2 – compare a mailbox */
  if (special2 != new_special2) {
    println("WOW A NEW EMAIL");
    fill_color = 255;
  }

  fill_color -= 5;
  if (fill_color < 0) {
    fill_color = 0;
  }

  /* STEP 3 – update all inbox counts */
  inbox = new_inbox;
  special1 = new_special1;
  special2 = new_special2;
  special3 = new_special3;
}

void check_mailboxes() {
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

