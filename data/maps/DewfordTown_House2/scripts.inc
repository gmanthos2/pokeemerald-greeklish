DewfordTown_House2_MapScripts::
	.byte 0

DewfordTown_House2_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SILK_SCARF, DewfordTown_House2_EventScript_ExplainSilkScarf
	msgbox DewfordTown_House2_Text_WantYouToHaveSilkScarf, MSGBOX_DEFAULT
	giveitem ITEM_SILK_SCARF
	goto_if_eq VAR_RESULT, FALSE, DewfordTown_House2_EventScript_NoRoomForScarf
	setflag FLAG_RECEIVED_SILK_SCARF
	release
	end

DewfordTown_House2_EventScript_NoRoomForScarf::
	msgbox DewfordTown_House2_Text_NoRoom, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_ExplainSilkScarf::
	msgbox DewfordTown_House2_Text_ExplainSilkScarf, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_Boy::
	msgbox DewfordTown_House2_Text_BrawlySoCool, MSGBOX_NPC
	end

DewfordTown_House2_Text_WantYouToHaveSilkScarf:
	.string "Χορτάστε να βλέπετε αυτό!\p"
	.string "Είναι ένα SILK SCARF. Είναι στην\n"
	.string "αιχμή της μόδας, ναι!\p"
	.string "Ω, βλέπω τα μάτια σου να λάμπουν!\n"
	.string "Εκτιμάς το εκπληκτικό μου στυλ!\p"
	.string "Ω, είσαι μια σκέτη οπτασία!\n"
	.string "Ορίστε. Θέλω να το έχεις!$"

DewfordTown_House2_Text_NoRoom:
	.string "Ω, δεν έχεις χώρο;\p"
	.string "Ακουσε καλά, αυτό το SCARF είναι κάτι\n"
	.string "που πρέπει να έχεις! Θα πούλαγα όλα\l"
	.string "μου τα items για να το αποκτήσω!$"

DewfordTown_House2_Text_ExplainSilkScarf:
	.string "Το SILK SCARF αυξάνει τη δύναμη των\n"
	.string "κινήσεων NORMAL-τύπου.\p"
	.string "Είναι ένα καταπληκτικό SCARF που\n"
	.string "θα ταιριάζει με σχεδόν όλα τα POKéMON!$"

DewfordTown_House2_Text_BrawlySoCool:
	.string "Ουάου, μπήκες στον κόπο να περάσεις τη \n"
	.string "θάλασσα για να έρθεις στη DEWFORD;\p"
	.string "Μήπως ήρθες εδώ επειδή άκουσες\n"
	.string "για τον BRAWLY;\p"
	.string "Είναι τόσο κουλ…\n"
	.string "Όλοι τον θαυμάζουν.$"

