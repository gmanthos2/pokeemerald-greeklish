AbandonedShip_Rooms_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms_1F_EventScript_Gentleman::
	msgbox AbandonedShip_Rooms_1F_Text_TakingALookAround, MSGBOX_NPC
	end

AbandonedShip_Rooms_1F_EventScript_Demetrius::
	trainerbattle_single TRAINER_DEMETRIUS, AbandonedShip_Rooms_1F_Text_DemetriusIntro, AbandonedShip_Rooms_1F_Text_DemetriusDefeat
	msgbox AbandonedShip_Rooms_1F_Text_DemetriusPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_EventScript_Thalia::
	trainerbattle_single TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaIntro, AbandonedShip_Rooms_1F_Text_ThaliaDefeat, AbandonedShip_Rooms_1F_EventScript_RegisterThalia
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms_1F_EventScript_ThaliaRematch
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms_1F_EventScript_RegisterThalia::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_THALIA_1
	release
	end

AbandonedShip_Rooms_1F_EventScript_ThaliaRematch::
	trainerbattle_rematch TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro, AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_Text_TakingALookAround:
	.string "Τέτοια πλοία είναι σπάνια, οπότε\n"
	.string "ρίχνω μια ματιά τριγύρω.\p"
	.string "Χμχμ…\n"
	.string "Φαίνεται να υπάρχουν κι άλλες καμπίνες…$"

AbandonedShip_Rooms_1F_Text_ThaliaIntro:
	.string "Τι στο καλό σε έκανε να έρθεις εδώ;\n"
	.string "Πρέπει να έχεις πολλή περιέργεια!$"

AbandonedShip_Rooms_1F_Text_ThaliaDefeat:
	.string "Όχι μόνο περιέργεια, αλλά και δύναμη…$"

AbandonedShip_Rooms_1F_Text_ThaliaPostBattle:
	.string "Ο άντρας της διπλανής πόρτας…\p"
	.string "Λέει πως απλά κάνει περιήγηση,\n"
	.string "δεν το πολυπιστεύω όμως αυτό.$"

AbandonedShip_Rooms_1F_Text_ThaliaRegister:
	.string "Έχεις πολλή δύναμη ως TRAINER!\n"
	.string "Ας σε καταχωρήσω ως αναμνηστικό!$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro:
	.string "Τι στο καλό σε έκανε να επιστρέψεις;\n"
	.string "Πρέπει να έχεις πολλή περιέργεια!$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat:
	.string "Μήπως έχεις υπερβολική δύναμη;$"

AbandonedShip_Rooms_1F_Text_ThaliaPostRematch:
	.string "Σίγουρα αυτός ο άντρας κάτι σκαρώνει!\n"
	.string "Συμπεριφέρεται τόσο ύποπτα!$"

AbandonedShip_Rooms_1F_Text_DemetriusIntro:
	.string "Ουάαα!\n"
	.string "Με βρήκανε! …Ε;$"

AbandonedShip_Rooms_1F_Text_DemetriusDefeat:
	.string "Αχ, δεν είσαι η μαμά μου.$"

AbandonedShip_Rooms_1F_Text_DemetriusPostBattle:
	.string "Τσακώθηκα με τη μαμά μου, κι έφυγα.\n"
	.string "Μην πεις σε κανέναν πού βρίσκομαι!$"

