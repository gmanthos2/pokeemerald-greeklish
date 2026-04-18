Route111_OldLadysRestStop_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route111_OldLadysRestStop_OnTransition
	.byte 0

Route111_OldLadysRestStop_OnTransition:
	setflag FLAG_LANDMARK_OLD_LADY_REST_SHOP
	end

Route111_OldLadysRestStop_EventScript_OldLady::
	lock
	faceplayer
	msgbox Route111_OldLadysRestStop_Text_RestUpHere, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_OldLadysRestStop_EventScript_Rest
	goto_if_eq VAR_RESULT, NO, Route111_OldLadysRestStop_EventScript_DeclineRest
	end

Route111_OldLadysRestStop_EventScript_Rest::
	msgbox Route111_OldLadysRestStop_Text_TakeYourTimeRestUp, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox Route111_OldLadysRestStop_Text_StillTiredTakeAnotherRest, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_OldLadysRestStop_EventScript_Rest
	goto_if_eq VAR_RESULT, NO, Route111_OldLadysRestStop_EventScript_DeclineRest
	end

Route111_OldLadysRestStop_EventScript_DeclineRest::
	msgbox Route111_OldLadysRestStop_Text_DontNeedToBeShy, MSGBOX_DEFAULT
	release
	end

Route111_OldLadysRestStop_Text_RestUpHere:
	.string "Ω, χρυσό μου.\n"
	.string "Δεν είναι εξαντλημένα τα POKéMON\l"
	.string "σου;\p"
	.string "Αν θες, ξεκουράσου εδώ.\n"
	.string "Αυτή είναι μια καλή ιδέα!\l"
	.string "Πρέπει να το κάνεις αυτό.$"

Route111_OldLadysRestStop_Text_TakeYourTimeRestUp:
	.string "Έτσι μπράβο.\n"
	.string "Κανόνισε το χρόνο σου και\l"
	.string "ξεκουράσου!$"

Route111_OldLadysRestStop_Text_StillTiredTakeAnotherRest:
	.string "Ω, χρυσό μου.\n"
	.string "Είναι τα POKéMON σου ακόμα\l"
	.string "κουρασμένα;\p"
	.string "Θα πρέπει να ξεκουραστείς κι άλλο\n"
	.string "εδώ.\l"
	.string "Αυτή είναι μια καλή ιδέα.\l"
	.string "Πρέπει να το κάνεις αυτό.$"

Route111_OldLadysRestStop_Text_DontNeedToBeShy:
	.string "Έτσι είναι;\n"
	.string "Δεν χρειάζεται να ντρέπεσαι γι'\l"
	.string "αυτό.$"

