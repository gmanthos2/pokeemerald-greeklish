GraniteCave_1F_MapScripts::
	.byte 0

GraniteCave_1F_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_ReceivedFlash::
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_Text_GetsDarkAheadHereYouGo:
	.string "Έι, εσύ.\n"
	.string "Σκοτεινιάζει πολύ εκεί μπροστά.\l"
	.string "Θα είναι δύσκολο να εξερευνήσεις.\p"
	.string "Εκείνος ο τύπος που πέρασε πιο πριν…\n"
	.string "STEVEN νομίζω λεγόταν.\p"
	.string "Ήξερε πώς να χρησιμοποιεί FLASH, οπότε\n"
	.string "πρέπει να είναι εντάξει, αλλά…\p"
	.string "Λοιπόν, για μας τους HIKERS, το να\n"
	.string "βοηθάμε όσους συναντάμε είναι το\l"
	.string "μότο μας.\p"
	.string "Ορίστε, θα σου το δώσω αυτό.$"

GraniteCave_1F_Text_ExplainFlash:
	.string "Δίδαξε αυτήν την κρυφή κίνηση FLASH σε\n"
	.string "ένα POKéMON και χρησιμοποίησέ την.\p"
	.string "Φωτίζει ακόμα και το απόλυτο σκοτάδι\n"
	.string "των σπηλαίων.\p"
	.string "Αλλά, για να τη χρησιμοποιήσεις, θες\n"
	.string "το GYM BADGE από το POKéMON GYM\l"
	.string "του DEWFORD.$"

