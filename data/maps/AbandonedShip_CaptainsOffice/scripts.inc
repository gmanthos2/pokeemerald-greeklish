AbandonedShip_CaptainsOffice_MapScripts::
	.byte 0

AbandonedShip_CaptainsOffice_EventScript_CaptSternAide::
	lock
	faceplayer
	goto_if_set FLAG_EXCHANGED_SCANNER, AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus
	checkitem ITEM_SCANNER
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_CaptainsOffice_EventScript_CanYouDeliverScanner
	goto_if_set FLAG_ITEM_ABANDONED_SHIP_HIDDEN_FLOOR_ROOM_2_SCANNER, AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus
	msgbox AbandonedShip_CaptainsOffice_Text_NoSuccessFindingScanner, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_EventScript_CanYouDeliverScanner::
	msgbox AbandonedShip_CaptainsOffice_Text_OhCanYouDeliverScanner, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus::
	msgbox AbandonedShip_CaptainsOffice_Text_ThisIsSSCactus, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_Text_NoSuccessFindingScanner:
	.string "Ερευνώ αυτό το πλοίο για λογαριασμό\n"
	.string "του CAPT. STERN.\p"
	.string "Μου ζήτησε επίσης να βρω έναν SCANNER,\n"
	.string "αλλά δεν είχα καμία επιτυχία…$"

AbandonedShip_CaptainsOffice_Text_OhCanYouDeliverScanner:
	.string "Ω! Αυτό είναι ένα SCANNER!\p"
	.string "Άκου, μπορείς να μου το παραδώσεις\n"
	.string "στον CAPT. STERN;\p"
	.string "Θέλω να ερευνήσω αυτό το πλοίο\n"
	.string "λίγο περισσότερο.$"

AbandonedShip_CaptainsOffice_Text_ThisIsSSCactus:
	.string "Αυτό το πλοίο λέγεται S.S. CACTUS.\n"
	.string "Φαίνεται να είναι από παλαιότερη εποχή.$"

