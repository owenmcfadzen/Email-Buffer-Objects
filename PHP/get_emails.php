<?php

/* change the type of document a browser treats this files as */
header('Content-Type:text/xml');

echo '<xml>';

/* connect to gmail */
$hostname = '{imap.gmail.com:993/imap/ssl}INBOX';
$username = '[YOUR EMAIL ADDRESS]';
$password = '[YOUR EMAIL PASSWORD]';

/* choose the mailboxes to examine (created in Gmail using filters and labels) */
$mailboxes = array('LABEL 1', 'LABEL 2', 'LABEL 3');

/* try to connect to INBOX */
$mbox = imap_open($hostname, $username, $password) 
	or die('Cannot connect to Gmail: ' . imap_last_error());

/* use our special function to get the number of unread emails */
$inbox_count = num_unread_messages($mbox);

/* remember to count ALL special emails */
$special_count = 0;

/* Loop through all our filter labels and count the unread emails */
foreach ($mailboxes as $mailbox) {
	/* try to connect to a mailbox */
	$connected = imap_reopen($mbox, '{imap.gmail.com:993/imap/ssl}' . $mailbox) 
		or die('Cannot connect to Gmail: ' . imap_last_error());
	
	if ($connected) {
		/* use our special function to get the number of unread emails */
		$count = num_unread_messages($mbox);
		$special_count += $count;
		echo "<mailbox unread=\"$count\">$mailbox</mailbox>";
	}
}

echo $special_count;

/* Because the INBOX includes all specials too,
we must first subtract them from the INBOX total */
$inbox_count = $inbox_count - $special_count;

echo "<mailbox unread=\"$inbox_count\">INBOX</mailbox>";

echo '</xml>';







function num_unread_messages($p_mbox) {	
	/* count ALL the messages in the mailbox (to loop through) */
	$num_messages = imap_num_msg($p_mbox);
	
	/* create a variable to count how many unread emails there are */
	$unread_messages = 0;

	/* loop through ALL the messages in the mailbox */
	for ($i = 1; $i <= $num_messages; $i++) {
		
		/* get the headerinfo object which tells us all about the email */
		$email_headerinfo = imap_headerinfo($p_mbox, $i);
	
		if ($email_headerinfo->Unseen == 'U') {
			/* the message hasn't been read yet = increase counter */
			$unread_messages++;
		}
	}
	
	/* return the counter of how many unread messages there are */
	return $unread_messages;
}

?>