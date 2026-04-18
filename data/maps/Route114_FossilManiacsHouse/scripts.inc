Route114_FossilManiacsHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsHouse_OnTransition
	.byte 0

Route114_FossilManiacsHouse_OnTransition:
	setflag FLAG_LANDMARK_FOSSIL_MANIACS_HOUSE
	end

Route114_FossilManiacsHouse_EventScript_FossilManiacsBrother::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_DIG, Route114_FossilManiacsHouse_EventScript_ReceivedDig
	msgbox Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother, MSGBOX_DEFAULT
	giveitem ITEM_TM_DIG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_DIG
	release
	end

Route114_FossilManiacsHouse_EventScript_ReceivedDig::
	msgbox Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsHouse_EventScript_RockDisplay::
	msgbox Route114_FossilManiacsHouse_Text_RocksFillDisplayCase, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_EventScript_Bookshelf::
	msgbox Route114_FossilManiacsHouse_Text_CrammedWithBooks, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother:
	.string "Ο μεγάλος αδερφός μου είναι\n"
	.string "ο FOSSIL MANIAC…\l"
	.string "Είναι ένα καλό παιδί που \l"
	.string "αγαπά τα FOSSILS…\p"
	.string "Του αρέσει να σκάβει τρύπες,\n"
	.string "επίσης…\l"
	.string "Έσκαψε αυτήν την τρύπα μόνος\l"
	.string "του…\p"
	.string "Μπορείς να το έχεις αυτό, ώστε να\n"
	.string "κάνεις DIG τρύπες όπως ο\l"
	.string "μεγάλος μου αδερφός…$"

Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance:
	.string "Αν βάλεις ένα POKéMON να κάνει\n"
	.string "DIG μέσα σε μια σπηλιά,\l"
	.string "επιστρέφεις στην είσοδο…$"

Route114_FossilManiacsHouse_Text_RocksFillDisplayCase:
	.string "Βράχοι σε περίεργα σχήματα\n"
	.string "γεμίζουν τη βιτρίνα…$"

Route114_FossilManiacsHouse_Text_CrammedWithBooks:
	.string "Η ΣΥΝΘΕΣΗ ΤΩΝ ΣΤΡΩΜΑΤΩΝ…\n"
	.string "ΠΩΣ Η ΒΡΟΧΗ ΔΙΑΜΟΡΦΩΝΕΙ ΤΗ ΓΗ…\l"
	.string "ΠΕΤΡΕΣ, ΧΩΜΑ ΚΑΙ ΒΡΑΧΟΣ…\p"
	.string "Είναι γεμάτο από βιβλία.$"

