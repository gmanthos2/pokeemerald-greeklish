MagmaHideout_3F_1R_MapScripts::
	.byte 0

MagmaHideout_3F_1R_EventScript_Grunt9::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_9, MagmaHideout_3F_1R_Text_Grunt9Intro, MagmaHideout_3F_1R_Text_Grunt9Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt9PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_EventScript_Grunt16::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_16, MagmaHideout_3F_1R_Text_Grunt16Intro, MagmaHideout_3F_1R_Text_Grunt16Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt16PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_Text_Grunt9Intro:
	.string "Τι έκανα για να αξίζω \n"
	.string "αυτήν τη σκοπιά;\p"
	.string "Το αριστερό μου αυτί καίγεται!$"

MagmaHideout_3F_1R_Text_Grunt9Defeat:
	.string "Παθαίνω θερμοπληξία…$"

MagmaHideout_3F_1R_Text_Grunt9PostBattle:
	.string "Πιστεύεις ότι είναι περίεργο που\n"
	.string "φοράμε κουκούλες σε αυτό \l"
	.string "το γεμάτο μάγμα ηφαίστειο;$"

MagmaHideout_3F_1R_Text_Grunt16Intro:
	.string "Μπήκαμε για να βοηθήσουμε τον αρχηγό\n"
	.string "μας να πετύχει το\l"
	.string "φανταστικό του όραμα.\p"
	.string "Δεν με νοιάζει αν είσαι με την\n"
	.string "TEAM AQUA ή απλά ένα \l"
	.string "παιδί που περνάει.\p"
	.string "Κανείς δεν μας εμποδίζει και \n"
	.string "να τη γλιτώνει έτσι απλά!$"

MagmaHideout_3F_1R_Text_Grunt16Defeat:
	.string "Ω, όχι!\n"
	.string "Δεν πρέπει να σε εμπιστεύομαι!$"

MagmaHideout_3F_1R_Text_Grunt16PostBattle:
	.string "Άκουσέ με.\n"
	.string "H TEAM MAGMA έχει δίκιο!\p"
	.string "Μην ακούς την TEAM AQUA.\n"
	.string "Μην πιστεύεις τα ψέματά τους!$"

