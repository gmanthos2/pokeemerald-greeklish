Route114_LanettesHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_LanettesHouse_OnTransition
	.byte 0

Route114_LanettesHouse_OnTransition:
	setflag FLAG_LANDMARK_LANETTES_HOUSE
	end

Route114_LanettesHouse_EventScript_Lanette::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_DOLL_LANETTE, Route114_LanettesHouse_EventScript_OfferAdvice
	setflag FLAG_SYS_PC_LANETTE
	msgbox Route114_LanettesHouse_Text_EverythingClutteredKeepThis, MSGBOX_DEFAULT
	givedecoration DECOR_LOTAD_DOLL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowNoRoomForDecor
	setflag FLAG_RECEIVED_DOLL_LANETTE
	release
	end

Route114_LanettesHouse_EventScript_OfferAdvice::
	msgbox Route114_LanettesHouse_Text_OrganizeYourBoxes, MSGBOX_DEFAULT
	release
	end

Route114_LanettesHouse_EventScript_Notebook::
	lockall
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage2
	msgbox Route114_LanettesHouse_Text_ClosedTheNotebook, MSGBOX_DEFAULT
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage2::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage2, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage3
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage3::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage3, MSGBOX_DEFAULT
	return

Route114_LanettesHouse_EventScript_PC::
	msgbox Route114_LanettesHouse_Text_EmailFromBill, MSGBOX_SIGN
	end

Route114_LanettesHouse_Text_EverythingClutteredKeepThis:
	.string "LANETTE: Ω! {PLAYER}{KUN}!\p"
	.string "Λυπάμαι που είναι όλα τόσο\n"
	.string "ακατάστατα…\l"
	.string "Όταν απορροφώμαι στην έρευνα,\l"
	.string "τα πράγματα καταλήγουν έτσι…\p"
	.string "Είναι ντροπιαστικό… Σε παρακαλώ\n"
	.string "κράτα το μυστικό με αντάλλαγμα\l"
	.string "αυτό.$"

Route114_LanettesHouse_Text_OrganizeYourBoxes:
	.string "Μπορώ να δώσω μια συμβουλή\n"
	.string "για το POKéMON Storage System\l"
	.string "μου;\p"
	.string "Θα έπρεπε να οργανώνεις τα\n"
	.string "BOXES σου, ώστε να καταλαβαίνεις\l"
	.string "ποια POKéMON είναι μέσα.$"

Route114_LanettesHouse_Text_ResearchNotesPage1:
	.string "Είναι οι σημειώσεις έρευνας\n"
	.string "της LANETTE.\l"
	.string "Υπάρχουν πληροφορίες για τα\n"
	.string "BOXES.\p"
	.string "Ο σχεδιασμός των BOXES είναι για\n"
	.string "να χωρούν 30 POKéMON το καθένα.\p"
	.string "Κάθε TRAINER θα έπρεπε να μπορεί\n"
	.string "να αποθηκεύει 420 POKéMON\l"
	.string "στο PC.\p"
	.string "Να συνεχίσω να διαβάζω;$"

Route114_LanettesHouse_Text_ResearchNotesPage2:
	.string "Ένα σύστημα σήμανσης θα έπρεπε\n"
	.string "να προστεθεί για να είναι η\l"
	.string "οργάνωση ευκολότερη.\p"
	.string "Το όνομα και η ταπετσαρία\n"
	.string "κάθε BOX θα μπορούν να αλλάζουν\l"
	.string "για να ευχαριστούν τα POKéMON.\p"
	.string "Να συνεχίσω να διαβάζω;$"

Route114_LanettesHouse_Text_ResearchNotesPage3:
	.string "Κατά την αποθήκευση, το\n"
	.string "POKéMON θα πρέπει να στέλνεται\l"
	.string "στο BOX που ελέγχθηκε τελευταίο.\p"
	.string "Αν το BOX είναι γεμάτο, το\n"
	.string "POKéMON θα αποθηκεύεται\l"
	.string "στο επόμενο BOX.\p"
	.string "Με άλλα λόγια, όταν ένα BOX\n"
	.string "εξετάζεται, επιλέγεται\l"
	.string "αυτόματα ως το BOX όπου\l"
	.string "θα στέλνονται τα POKéMON.$"

Route114_LanettesHouse_Text_ClosedTheNotebook:
	.string "Το {PLAYER} έκλεισε το τετράδιο.$"

Route114_LanettesHouse_Text_EmailFromBill:
	.string "Υπάρχει ένα e-mail από κάποιον\n"
	.string "στο PC.\p"
	.string "“… … … … … … …\p"
	.string "“Το δικό σου Storage System\n"
	.string "προσφέρει περισσότερη ευκολία\l"
	.string "από το δικό μου.\p"
	.string "“Έχει πολλά φιλικά προς τον χρήστη\n"
	.string "χαρακτηριστικά που το κάνουν\l"
	.string "διασκεδαστικό και χρήσιμο.\p"
	.string "“Με κάνει περήφανο που έπαιξα\n"
	.string "ρόλο στην ανάπτυξή του.\p"
	.string "“Ελπίζω ότι θα συνεχίσεις την\n"
	.string "έρευνα για τα Storage Systems.\p"
	.string "“Από τον BILL\n"
	.string "… … … … … … … …”$"

