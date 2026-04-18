MagmaHideout_2F_1R_MapScripts::
	.byte 0

MagmaHideout_2F_1R_EventScript_Grunt14::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_14, MagmaHideout_2F_1R_Text_Grunt14Intro, MagmaHideout_2F_1R_Text_Grunt14Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt14PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_3, MagmaHideout_2F_1R_Text_Grunt3Intro, MagmaHideout_2F_1R_Text_Grunt3Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_4, MagmaHideout_2F_1R_Text_Grunt4Intro, MagmaHideout_2F_1R_Text_Grunt4Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_5, MagmaHideout_2F_1R_Text_Grunt5Intro, MagmaHideout_2F_1R_Text_Grunt5Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_Text_Grunt14Intro:
	.string "Τι, τι, τι;\p"
	.string "Μόνο τα μέλη της TEAM MAGMA \n"
	.string "υποτίθεται ότι βρίσκονται \l"
	.string "εδώ μέσα!\p"
	.string "Αλλά δεν φοράς τη \n"
	.string "στολή της TEAM MAGMA…\p"
	.string "Μου κινείς τις υποψίες!\n"
	.string "Πάλεψε μαζί μου!$"

MagmaHideout_2F_1R_Text_Grunt14Defeat:
	.string "Αγιιγιιι…\n"
	.string "Η περηφάνια μου ως μέλος \l"
	.string "της TEAM MAGMA…$"

MagmaHideout_2F_1R_Text_Grunt14PostBattle:
	.string "Αν υποφέρεις από ρίγη,\n"
	.string "πρέπει να μπεις στην TEAM MAGMA.$"

MagmaHideout_2F_1R_Text_Grunt3Intro:
	.string "Ακίνητος!\p"
	.string "Ελπίζω να μην περιμένεις να \n"
	.string "κρατήσω το στόμα μου κλειστό \l"
	.string "και να σ' αφήσω να περάσεις.$"

MagmaHideout_2F_1R_Text_Grunt3Defeat:
	.string "Ουάου!\n"
	.string "Συμφωνώ!$"

MagmaHideout_2F_1R_Text_Grunt3PostBattle:
	.string "Ίσως θα ήταν καλύτερα \n"
	.string "αν σε άφηνα να φύγεις χωρίς \l"
	.string "να πω τίποτα…$"

MagmaHideout_2F_1R_Text_Grunt4Intro:
	.string "Αχά!\n"
	.string "Ένας εισβολέας!$"

MagmaHideout_2F_1R_Text_Grunt4Defeat:
	.string "Γκράαα!$"

MagmaHideout_2F_1R_Text_Grunt4PostBattle:
	.string "Έχω ήδη χάσει.\p"
	.string "Πρέπει πραγματικά να \n"
	.string "συνεχίσω να τρέχω γύρω γύρω;$"

MagmaHideout_2F_1R_Text_Grunt5Intro:
	.string "Ω, ω!\n"
	.string "Ένας εισβολέας!$"

MagmaHideout_2F_1R_Text_Grunt5Defeat:
	.string "Μουρμουρητό…$"

MagmaHideout_2F_1R_Text_Grunt5PostBattle:
	.string "Βασικά, δεν είμαι καθόλου \n"
	.string "ειδικός στις μάχες…$"

