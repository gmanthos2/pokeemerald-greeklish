.set LOCALID_WINGULL, 3

FortreeCity_House4_MapScripts::
	.byte 0

FortreeCity_House4_EventScript_Woman::
	msgbox FortreeCity_House4_Text_BringsWorldCloserTogether, MSGBOX_NPC
	end

FortreeCity_House4_EventScript_Boy::
	lockall
	goto_if_set FLAG_RECEIVED_MENTAL_HERB, FortreeCity_House4_EventScript_ReceivedMentalHerb
	goto_if_set FLAG_WINGULL_DELIVERED_MAIL, FortreeCity_House4_EventScript_WingullReturned
	goto_if_set FLAG_WINGULL_SENT_ON_ERRAND, FortreeCity_House4_EventScript_WingullOnErrand
	msgbox FortreeCity_House4_Text_GoBirdPokemon, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_WINGULL_SENT_ON_ERRAND
	clearflag FLAG_HIDE_MOSSDEEP_CITY_HOUSE_2_WINGULL
	applymovement LOCALID_WINGULL, FortreeCity_House4_Movement_WingullExit
	waitmovement 0
	removeobject LOCALID_WINGULL
	releaseall
	end

FortreeCity_House4_EventScript_WingullOnErrand::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FortreeCity_House4_Text_AskedWingullToRunErrand, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_House4_EventScript_WingullReturned::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FortreeCity_House4_Text_WelcomeWingullTakeMentalHerb, MSGBOX_DEFAULT
	giveitem ITEM_MENTAL_HERB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MENTAL_HERB
	releaseall
	end

FortreeCity_House4_EventScript_ReceivedMentalHerb::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FortreeCity_House4_Text_FriendsFarAwayThanksToWingull, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_House4_Movement_WingullExit:
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_in_place_faster_down
	delay_8
	step_end

FortreeCity_House4_EventScript_Wingull::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	msgbox FortreeCity_House4_Text_Wingull, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House4_Text_BringsWorldCloserTogether:
	.string "Ζώντας μαζί με τα POKéMON, \n"
	.string "οι άνθρωποι κάνουν όλο και πιο \l"
	.string "πολλούς φίλους.\p"
	.string "Και αυτό φέρνει τον κόσμο \n"
	.string "πιο κοντά. Είναι υπέροχο!$"

FortreeCity_House4_Text_GoBirdPokemon:
	.string "Εκεί!\n"
	.string "Εμπρός, BIRD POKéMON!$"

FortreeCity_House4_Text_AskedWingullToRunErrand:
	.string "Χεχέ, ζήτησα από το WINGULL μου \n"
	.string "να μου κάνει μια δουλειά.$"

FortreeCity_House4_Text_WelcomeWingullTakeMentalHerb:
	.string "Ωραία!\n"
	.string "Καλωσήρθες πίσω, WINGULL!\p"
	.string "Ε; Τι είναι αυτό;\n"
	.string "Τι κρατάει;\p"
	.string "Ένα MENTAL HERB;\n"
	.string "Θα το βρήκε κάπου.\p"
	.string "Αλλά δεν είμαι TRAINER, οπότε \n"
	.string "μπορείς να το πάρεις εσύ.$"

FortreeCity_House4_Text_FriendsFarAwayThanksToWingull:
	.string "Χάρη στο WINGULL μου, έχω φίλους \n"
	.string "που μένουν πολύ μακριά.$"

FortreeCity_House4_Text_Wingull:
	.string "WINGULL: Pihyoh!$"

