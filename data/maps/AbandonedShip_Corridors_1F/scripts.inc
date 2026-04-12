AbandonedShip_Corridors_1F_MapScripts::
	.byte 0

AbandonedShip_Corridors_1F_EventScript_Youngster::
	msgbox AbandonedShip_Corridors_1F_Text_IsntItFunHere, MSGBOX_NPC
	end

AbandonedShip_Corridors_1F_EventScript_Charlie::
	trainerbattle_single TRAINER_CHARLIE, AbandonedShip_Corridors_1F_Text_CharlieIntro, AbandonedShip_Corridors_1F_Text_CharlieDefeat
	msgbox AbandonedShip_Corridors_1F_Text_CharliePostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Corridors_1F_Text_CharlieIntro:
	.string "Τι το αστείο έχει το να έχω την\n"
	.string "σαμπρέλα μου πάνω στο πλοίο;$"

AbandonedShip_Corridors_1F_Text_CharlieDefeat:
	.string "Ουάου, με κατατρόπωσες!$"

AbandonedShip_Corridors_1F_Text_CharliePostBattle:
	.string "Δεν είναι εύκολο να πετάς POKé BALLS\n"
	.string "ενώ κρατιέσαι από ένα σωσίβιο!$"

AbandonedShip_Corridors_1F_Text_IsntItFunHere:
	.string "Δεν είναι διασκεδαστικά εδώ;\n"
	.string "Ενθουσιάζομαι απλά που είμαι εδώ!$"
