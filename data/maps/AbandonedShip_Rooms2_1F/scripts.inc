AbandonedShip_Rooms2_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms2_1F_EventScript_Dan::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanIntro, AbandonedShip_Rooms2_1F_Text_DanDefeat, AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterDan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms2_1F_EventScript_DanRematch
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterDan::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT  @ Kira speaks for both when registering KiraAndDan
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_DanRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanRematchIntro, AbandonedShip_Rooms2_1F_Text_DanRematchDefeat, AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Kira::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraIntro, AbandonedShip_Rooms2_1F_Text_KiraDefeat, AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterKira
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms2_1F_EventScript_KiraRematch
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterKira::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_KiraRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraRematchIntro, AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat, AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Jani::
	trainerbattle_single TRAINER_JANI, AbandonedShip_Rooms2_1F_Text_JaniIntro, AbandonedShip_Rooms2_1F_Text_JaniDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_JaniPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Garrison::
	trainerbattle_single TRAINER_GARRISON, AbandonedShip_Rooms2_1F_Text_GarrisonIntro, AbandonedShip_Rooms2_1F_Text_GarrisonDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_Text_DanIntro:
	.string "DAN: Ενώ ψάχναμε για θησαυρούς,\n"
	.string "ανακαλύψαμε έναν TRAINER!$"

AbandonedShip_Rooms2_1F_Text_DanDefeat:
	.string "DAN: Δεν μπορέσαμε να κερδίσουμε,\n"
	.string "αν και δουλέψαμε μαζί…$"

AbandonedShip_Rooms2_1F_Text_DanPostBattle:
	.string "DAN: Δε βρίσκουμε κανένα θησαυρό…\n"
	.string "Λες να τους πήρε ήδη κάποιος;$"

AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons:
	.string "DAN: Δεν έχεις καν δύο POKéMON.\n"
	.string "Είναι αδύνατο να μας νικήσεις έτσι.$"

AbandonedShip_Rooms2_1F_Text_KiraIntro:
	.string "KIRA: Ω;\n"
	.string "Ψάχναμε για κάτι θησαυρούς.\l"
	.string "Μα τελικά βρήκαμε TRAINER!$"

AbandonedShip_Rooms2_1F_Text_KiraDefeat:
	.string "KIRA: Ουάου, τόση δύναμη!$"

AbandonedShip_Rooms2_1F_Text_KiraPostBattle:
	.string "KIRA: Πού να είναι οι θησαυροί;\p"
	.string "Έχω ήδη αποφασίσει τι θα αγοράσω\n"
	.string "όταν τους βρούμε!$"

AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons:
	.string "KIRA: Ω, δεν έχεις δύο POKéMON;\n"
	.string "Θα παλέψουμε κάποια άλλη φορά!$"

AbandonedShip_Rooms2_1F_Text_KiraRegister:
	.string "KIRA: Αχ, με νευριάζεις τόσο πολύ!\n"
	.string "Θα σε καταχωρήσω γι' αυτό!$"

AbandonedShip_Rooms2_1F_Text_DanRematchIntro:
	.string "DAN: Ψάχναμε για θησαυρούς\n"
	.string "όλο αυτό τον καιρό.\p"
	.string "Τα POKéMON μας δυνάμωσαν κιόλας.\n"
	.string "Ας σου δείξουμε, εντάξει;$"

AbandonedShip_Rooms2_1F_Text_DanRematchDefeat:
	.string "DAN: Έχεις δύναμη, ως συνήθως!$"

AbandonedShip_Rooms2_1F_Text_DanPostRematch:
	.string "DAN: Δε βρίσκουμε θησαυρούς,\n"
	.string "χάνουμε στα POKéMON…\p"
	.string "Θέλω να πάω σπίτι… Αλλά αν το πω,\n"
	.string "αυτή θυμώνει μαζί μου…$"

AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons:
	.string "DAN: Δεν έχεις καν δύο POKéMON.\n"
	.string "Είναι αδύνατο να μας νικήσεις έτσι.$"

AbandonedShip_Rooms2_1F_Text_KiraRematchIntro:
	.string "KIRA: Ω; Συναντιόμαστε πάλι!\p"
	.string "Όπως κι εμείς, ακόμα ελπίζεις\n"
	.string "να βρεις θησαυρούς, σωστά;\p"
	.string "Θες ο χαμένος απλά\n"
	.string "να σταματήσει το ψάξιμο;$"

AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat:
	.string "KIRA: Ωχ, πάλι χάσαμε…$"

AbandonedShip_Rooms2_1F_Text_KiraPostRematch:
	.string "KIRA: Δε φεύγουμε αν δεν δυναμώσουμε\n"
	.string "κι άλλο τα POKéMON μας και αν\l"
	.string "δε βρούμε τους θησαυρούς!$"

AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons:
	.string "KIRA: Ω, δεν έχεις δύο POKéMON;\n"
	.string "Θα παλέψουμε κάποια άλλη φορά!$"

AbandonedShip_Rooms2_1F_Text_JaniIntro:
	.string "Δεν κολυμπάω πολύ καλά,\n"
	.string "αλλά δίνω γερές μάχες!$"

AbandonedShip_Rooms2_1F_Text_JaniDefeat:
	.string "Ουπς.\n"
	.string "Αυτό δεν πήγε και πολύ καλά.$"

AbandonedShip_Rooms2_1F_Text_JaniPostBattle:
	.string "Το να περπατάς με γυμνά πόδια\n"
	.string "στο πλοίο είναι κάπως αηδιαστικό.$"

AbandonedShip_Rooms2_1F_Text_GarrisonIntro:
	.string "Δύναμη και συμπόνια…\n"
	.string "Αυτοί είναι οι θησαυροί ενός TRAINER!$"

AbandonedShip_Rooms2_1F_Text_GarrisonDefeat:
	.string "Α, υπάρχει κάτι πάνω σου\n"
	.string "που πραγματικά λάμπει.$"

AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle:
	.string "Σε μια καμπίνα κάπου στο πλοίο,\n"
	.string "είδα κάτι να λάμπει.$"
