.set LOCALID_WALLACE, 1

CaveOfOrigin_B1F_MapScripts::
	.byte 0

CaveOfOrigin_B1F_EventScript_Wallace::
	lock
	faceplayer
	msgbox CaveOfOrigin_B1F_Text_WallaceStory, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	playse SE_PIN
	applymovement LOCALID_WALLACE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLACE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	applymovement LOCALID_WALLACE, Common_Movement_FacePlayer
	waitmovement 0
	message CaveOfOrigin_B1F_Text_WhereIsRayquaza
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_WheresRayquaza::
	multichoice 0, 0, MULTI_WHERES_RAYQUAZA, FALSE
	switch VAR_RESULT
	case 0, CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin
	case 1, CaveOfOrigin_B1F_EventScript_AtMtPyre
	case 2, CaveOfOrigin_B1F_EventScript_AtSkyPillar
	case 3, CaveOfOrigin_B1F_EventScript_DontRemember
	goto CaveOfOrigin_B1F_EventScript_DontRemember
	end

CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin::
	message CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtMtPyre::
	message CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_DontRemember::
	message CaveOfOrigin_B1F_Text_CantYouRememberSomehow
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtSkyPillar::
	msgbox CaveOfOrigin_B1F_Text_WellHeadToSkyPillar, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	fadescreenspeed FADE_TO_BLACK, 4
	setflag FLAG_WALLACE_GOES_TO_SKY_PILLAR
	setvar VAR_SOOTOPOLIS_CITY_STATE, 3
	removeobject LOCALID_WALLACE
	clearflag FLAG_HIDE_SKY_PILLAR_WALLACE
	fadescreen FADE_FROM_BLACK
	release
	end

CaveOfOrigin_B1F_Text_WallaceStory:
	.string "Α, οπότε εσύ είσαι, {PLAYER}{KUN};\n"
	.string "Έχω ακούσει κι εγώ για τα κατορθώματά \l"
	.string "σου.\p"
	.string "Ονομάζομαι WALLACE.\p"
	.string "Ήμουν κάποτε GYM LEADER της\n"
	.string "SOOTOPOLIS, αλλά κάτι προέκυψε.\p"
	.string "Έτσι τώρα, εμπιστεύτηκα τον μέντορα μου\n"
	.string "JUAN για τη λειτουργία του GYM.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Τα GROUDON και KYOGRE, τα δύο POKéMON\n"
	.string "που προκαλούν χάος εδώ, θεωρούνται \l"
	.string "υπερ-αρχαία POKéMON.\p"
	.string "Αλλά δεν υπάρχουν μόνο δύο υπερ-αρχαία\n"
	.string "POKéMON.\p"
	.string "Υπάρχει ένα ακόμα κάπου.\p"
	.string "Κάπου, υπάρχει ένα υπερ-αρχαίο POKéMON\n"
	.string "που ονομάζεται RAYQUAZA.\p"
	.string "Λένε ότι ήταν το RAYQUAZA που ηρέμησε\n"
	.string "τους δύο πολεμιστές στο μακρινό\l"
	.string "παρελθόν.\p"
	.string "Αλλά ούτε εγώ έχω ιδέα στο\n"
	.string "πού μπορεί να βρίσκεται το RAYQUAZA…$"

CaveOfOrigin_B1F_Text_WhereIsRayquaza:
	.string "WALLACE: {PLAYER}{KUN}, μήπως ξέρεις\n"
	.string "πού είναι το RAYQUAZA τώρα;\p"
	.string "Αν ναι, σε παρακαλώ πες μου.$"

CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin:
	.string "WALLACE: Η CAVE OF ORIGIN;\p"
	.string "Μα αυτή είναι ακριβώς εδώ!\n"
	.string "Πρέπει να σκεφτείς κάτι καλύτερο!\p"
	.string "Σε παρακαλώ, χρειάζομαι τη βοήθεια σου\n"
	.string "στο πού μπορεί να είναι το RAYQUAZA.$"

CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat:
	.string "WALLACE: Το MT. PYRE;\p"
	.string "Αλλά όταν συνάντησα τη γιαγιάκα \n"
	.string "εκεί πριν, δεν ανέφερε κάτι τέτοιο.\p"
	.string "Αμφιβάλλω πολύ ότι η γιαγιάκα\n"
	.string "θα προσπαθούσε να μου κρύψει κάτι…\p"
	.string "{PLAYER}{KUN}, θα μπορούσες να το \n"
	.string "σκεφτείς πιο προσεκτικά για μένα;$"

CaveOfOrigin_B1F_Text_CantYouRememberSomehow:
	.string "WALLACE: Ε; Δεν θυμάσαι;\n"
	.string "Χμμ… Αυτό είναι πρόβλημα…\p"
	.string "Δεν μπορείς να θυμηθείς κάπως;$"

CaveOfOrigin_B1F_Text_WellHeadToSkyPillar:
	.string "WALLACE: Το SKY PILLAR;\p"
	.string "Αυτό είναι!\n"
	.string "Πρέπει να είναι το SKY PILLAR!\p"
	.string "{PLAYER}{KUN}, δεν πρέπει να χάσουμε\n"
	.string "ούτε λεπτό!\p"
	.string "Φεύγουμε για το SKY PILLAR αμέσως!$"

