MagmaHideout_3F_2R_MapScripts::
	.byte 0

MagmaHideout_3F_2R_EventScript_Grunt10::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_10, MagmaHideout_3F_2R_Text_Grunt10Intro, MagmaHideout_3F_2R_Text_Grunt10Defeat
	msgbox MagmaHideout_3F_2R_Text_Grunt10PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_2R_Text_Grunt10Intro:
	.string "Καταλαβαίνω όλα όσα \n"
	.string "λέει ο αρχηγός μας.\l"
	.string "Αλλά ξέρεις κάτι;\p"
	.string "Να κάνουμε πράγματα όπως \n"
	.string "το να ξεθάβουμε ένα \l"
	.string "υπέρ-αρχαίο POKéMON και \l"
	.string "να κλέβουμε τον METEORITE κάποιου…\p"
	.string "Νομίζω ότι το παρατραβάμε λίγο.\n"
	.string "Εσύ τι νομίζεις;$"

MagmaHideout_3F_2R_Text_Grunt10Defeat:
	.string "Ναι, νομίζω ότι κάνουμε κάτι\n"
	.string "λάθος κατά κάποιο τρόπο.$"

MagmaHideout_3F_2R_Text_Grunt10PostBattle:
	.string "Να ξέρεις, η ήττα μου από εσένα\n"
	.string "καθάρισε το μυαλό μου.\p"
	.string "Την επόμενη φορά που θα \n"
	.string "δω τον αρχηγό μας, \l"
	.string "θα τον ρωτήσω για \l"
	.string "το τι κάνουμε.$"

