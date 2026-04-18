MtPyre_4F_MapScripts::
	.byte 0

@ Seems like the scripts for the 4F and 5F were swapped

MtPyre_5F_EventScript_Atsushi::
	trainerbattle_single TRAINER_ATSUSHI, MtPyre_5F_Text_AtsushiIntro, MtPyre_5F_Text_AtsushiDefeat
	msgbox MtPyre_5F_Text_AtsushiPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_5F_Text_AtsushiIntro:
	.string "Δάσκαλε…\n"
	.string "Σε παρακαλώ, δες την πρόοδό μου!$"

MtPyre_5F_Text_AtsushiDefeat:
	.string "Δάσκαλε…\n"
	.string "Σε παρακαλώ, συγχώρεσέ με!$"

MtPyre_5F_Text_AtsushiPostBattle:
	.string "Μέχρι να βελτιωθώ, ο δάσκαλός μου, \n"
	.string "που αναπαύεται εδώ, δεν θα βρει \l"
	.string "ποτέ πραγματική γαλήνη…$"

