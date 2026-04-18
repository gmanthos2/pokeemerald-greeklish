MagmaHideout_2F_2R_MapScripts::
	.byte 0

MagmaHideout_2F_2R_EventScript_Grunt15::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_15, MagmaHideout_2F_2R_Text_Grunt15Intro, MagmaHideout_2F_2R_Text_Grunt15Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt15PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_6, MagmaHideout_2F_2R_Text_Grunt6Intro, MagmaHideout_2F_2R_Text_Grunt6Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt7::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_7, MagmaHideout_2F_2R_Text_Grunt7Intro, MagmaHideout_2F_2R_Text_Grunt7Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt7PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_8, MagmaHideout_2F_2R_Text_Grunt8Intro, MagmaHideout_2F_2R_Text_Grunt8Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_Text_Grunt15Intro:
	.string "Δεν έχω προηγούμενα μαζί σου.\n"
	.string "Απλώς ακολουθώ διαταγές!$"

MagmaHideout_2F_2R_Text_Grunt15Defeat:
	.string "Μπορεί να έχασα, αλλά…$"

MagmaHideout_2F_2R_Text_Grunt15PostBattle:
	.string "Ξεθάψαμε κάτι το απίστευτο!\n"
	.string "Και μετά πήραμε το BLUE ORB!\p"
	.string "Το μόνο που μένει είναι ο \n"
	.string "αρχηγός μας να…\l"
	.string "Φουφουφου… Φουαχαχαχα!$"

MagmaHideout_2F_2R_Text_Grunt6Intro:
	.string "Δεν αντέχω τη ζέστη.\n"
	.string "Ίσως θα έπρεπε να είχα μπει \l"
	.string "στην TEAM AQUA τελικά…$"

MagmaHideout_2F_2R_Text_Grunt6Defeat:
	.string "Ναι, μάλλον δεν είμαι φτιαγμένος \n"
	.string "για την TEAM MAGMA…$"

MagmaHideout_2F_2R_Text_Grunt6PostBattle:
	.string "Δεν νιώθεις μοναξιά για τη θάλασσα\n"
	.string "όντας σε ένα τέτοιο μέρος;$"

MagmaHideout_2F_2R_Text_Grunt7Intro:
	.string "Μπορείς να ακούσεις δονήσεις εδώ\n"
	.string "μερικές φορές.\p"
	.string "Θα μπορούσε να τρέμει το \n"
	.string "ηφαίστειο; Ή μήπως είναι ο GROU…\p"
	.string "Ουπς!\n"
	.string "Όχι, όχι, ξέχασέ το!$"

MagmaHideout_2F_2R_Text_Grunt7Defeat:
	.string "Είσαι φλογερός στη μάχη.\n"
	.string "Σαν ένα ηφαίστειο!$"

MagmaHideout_2F_2R_Text_Grunt7PostBattle:
	.string "Έτυχε να κερδίσεις αυτή \n"
	.string "τη φορά, αλλά δεν πειράζει.\p"
	.string "Ο στόχος της TEAM MAGMA \n"
	.string "είναι έτοιμος να επιτευχθεί!$"

MagmaHideout_2F_2R_Text_Grunt8Intro:
	.string "Ένας από τους δικούς μας \n"
	.string "φρίκαρε επειδή έχασε το \l"
	.string "MAGMA EMBLEM του…\p"
	.string "Μισό λεπτό!\n"
	.string "Εσύ το βρήκες;$"

MagmaHideout_2F_2R_Text_Grunt8Defeat:
	.string "Δυσκολεύομαι να το πιστέψω αυτό…$"

MagmaHideout_2F_2R_Text_Grunt8PostBattle:
	.string "Έχω την αίσθηση ότι το σχέδιό μας\n"
	.string "εν τέλει θα αποτύχει…$"

