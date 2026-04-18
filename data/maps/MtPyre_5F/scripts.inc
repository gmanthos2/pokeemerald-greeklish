MtPyre_5F_MapScripts::
	.byte 0

@ Seems like the scripts for the 4F and 5F were swapped

MtPyre_4F_EventScript_Tasha::
	trainerbattle_single TRAINER_TASHA, MtPyre_4F_Text_TashaIntro, MtPyre_4F_Text_TashaDefeat
	msgbox MtPyre_4F_Text_TashaPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_4F_Text_TashaIntro:
	.string "Λατρεύω οτιδήποτε τρομακτικό… \n"
	.string "Είναι σαν αρρώστια…\p"
	.string "Όταν είμαι εδώ…\n"
	.string "Τρέμω από τον φόβο…$"

MtPyre_4F_Text_TashaDefeat:
	.string "Το να χάνω μου είναι δυσάρεστο…$"

MtPyre_4F_Text_TashaPostBattle:
	.string "Θέλω να βλέπω φρικτά πράγματα… \n"
	.string "Δεν μπορώ να φύγω…\p"
	.string "Μείνε…\n"
	.string "Θέλεις να μείνεις μαζί μου;$"

