MtPyre_6F_MapScripts::
	.byte 0

MtPyre_6F_EventScript_Valerie::
	trainerbattle_single TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieIntro, MtPyre_6F_Text_ValerieDefeat, MtPyre_6F_EventScript_RegisterValerie
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_6F_EventScript_RematchValerie
	msgbox MtPyre_6F_Text_ValeriePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_6F_EventScript_RegisterValerie::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_6F_Text_ValerieRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_VALERIE_1
	release
	end

MtPyre_6F_EventScript_RematchValerie::
	trainerbattle_rematch TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieRematchIntro, MtPyre_6F_Text_ValerieRematchDefeat
	msgbox MtPyre_6F_Text_ValeriePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_EventScript_Cedric::
	trainerbattle_single TRAINER_CEDRIC, MtPyre_6F_Text_CedricIntro, MtPyre_6F_Text_CedricDefeat
	msgbox MtPyre_6F_Text_CedricPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_Text_ValerieIntro:
	.string "Όταν είμαι εδώ…\n"
	.string "Μια περίεργη δύναμη ρέει μέσα μου…$"

MtPyre_6F_Text_ValerieDefeat:
	.string "Η δύναμη χάνεται…$"

MtPyre_6F_Text_ValeriePostBattle:
	.string "Ίσως η δύναμη προέρχεται από τα \n"
	.string "πνεύματα των POKéMON που \l"
	.string "αναπαύονται ανήσυχα εδώ…$"

MtPyre_6F_Text_ValerieRegister:
	.string "Φουφουφου… Έχασα τη μάχη, αλλά… \n"
	.string "Έχω αυτή τη μικρή ικανότητα…\p"
	.string "Χωρίς καν να ακουμπήσω το \n"
	.string "POKéNAV σου… Χιγιά!$"

MtPyre_6F_Text_ValerieRematchIntro:
	.string "Πίσω σου…\n"
	.string "Τι είναι αυτό…$"

MtPyre_6F_Text_ValerieRematchDefeat:
	.string "Κάτι έσβησε…$"

MtPyre_6F_Text_ValeriePostRematch:
	.string "Τα POKéMON που αναπαύονται εδώ… \n"
	.string "Μερικές φορές, παίζουν…$"

MtPyre_6F_Text_CedricIntro:
	.string "Έχεις χάσει τον προσανατολισμό σου; \n"
	.string "Μη φοβάσαι, γιατί είμαι εδώ εγώ!$"

MtPyre_6F_Text_CedricDefeat:
	.string "Δεν είχες χαθεί;$"

MtPyre_6F_Text_CedricPostBattle:
	.string "Είχα την εντύπωση ότι ένας χαμένος \n"
	.string "TRAINER θα πανικοβαλλόταν και θα \l"
	.string "νικιόταν εύκολα.\p"
	.string "Ήταν βρώμικο και δεν θα το \n"
	.string "ξαναδοκιμάσω…$"

