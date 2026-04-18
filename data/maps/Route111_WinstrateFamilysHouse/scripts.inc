.set LOCALID_VIVI, 1
.set LOCALID_VICTOR, 2
.set LOCALID_VICTORIA, 3
.set LOCALID_VICKY, 4

Route111_WinstrateFamilysHouse_MapScripts::
	.byte 0

Route111_WinstrateFamilysHouse_EventScript_Victor::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VICTOR
	msgbox Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Victoria::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VICTORIA
	goto_if_set FLAG_RECEIVED_MACHO_BRACE, Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace
	msgbox Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace, MSGBOX_DEFAULT
	giveitem ITEM_MACHO_BRACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MACHO_BRACE
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace::
	msgbox Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vivi::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VIVI
	msgbox Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vicky::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VICKY
	goto_if_set FLAG_TEMP_4, Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrong, MSGBOX_DEFAULT
	setflag FLAG_TEMP_4
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo::
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_0x8008, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou:
	.string "Είσαι το πρώτο TRAINER που βλέπω\n"
	.string "που χρησιμοποιεί τα POKéMON του\l"
	.string "με τόση μαεστρία.\p"
	.string "Αλλά, θα 'πρεπε να σου πω--ο γιος\n"
	.string "μου είναι πιο δυνατός από σένα.\p"
	.string "Πήρε ακόμα και την πρόκληση του\n"
	.string "POKéMON LEAGUE, να ξέρεις.$"

Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace:
	.string "Χρησιμοποιούμε αυτό το MACHO\n"
	.string "BRACE για να δυναμώνουμε πιο\l"
	.string "πολύ τα POKéMON μας\l"
	.string "στην προπόνηση.\p"
	.string "Επειδή μας νίκησες όλους εδώ,\n"
	.string "δεν ξέρω αν το χρειάζεσαι,\l"
	.string "αλλά θα θέλαμε να έχεις το\l"
	.string "MACHO BRACE μας.$"

Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles:
	.string "Όσον αφορά τις μάχες POKéMON,\n"
	.string "τείνουμε να είμαστε αρκετά\l"
	.string "παθιασμένοι.$"

Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers:
	.string "H μαμά είναι πιο δυνατή από τον\n"
	.string "μπαμπά.\p"
	.string "Είμαι πιο δυνατή από τη μαμά.\p"
	.string "Και η γιαγιά πιο δυνατή από μένα!\p"
	.string "Αλλά ο μεγάλος αδερφός μου\n"
	.string "είναι ακόμα πιο δυνατός από\l"
	.string "τη γιαγιά.$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrong:
	.string "Δεν υπάρχει αμφιβολία ότι\n"
	.string "είσαι δυνατό.\p"
	.string "Αλλά αν πάλευες με τον εγγονό\n"
	.string "μου, θα κατέληγες να\l"
	.string "κλαις από απογοήτευση.\p"
	.string "Είναι πολύ πιο δυνατός από κάθε\n"
	.string "TRAINER που ξέρει η\l"
	.string "οικογένειά μας.\p"
	.string "Σίγουρα προκαλεί τον\n"
	.string "CHAMPION του POKéMON LEAGUE\l"
	.string "μέχρι τώρα.\p"
	.string "Γνωρίζοντας τον εγγονό μου,\n"
	.string "μπορεί να είναι ήδη o\l"
	.string "CHAMPION!$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort:
	.string "Ο εγγονός μου σίγουρα προκαλεί\n"
	.string "τον CHAMPION του POKéMON\l"
	.string "LEAGUE μέχρι τώρα.\p"
	.string "Γνωρίζοντας τον εγγονό μου,\n"
	.string "μπορεί να είναι ήδη o\l"
	.string "CHAMPION!$"

