.set LOCALID_STEVEN, 1

MeteorFalls_StevensCave_MapScripts::
	.byte 0

MeteorFalls_StevensCave_EventScript_Steven::
	lock
	goto_if_set FLAG_DEFEATED_METEOR_FALLS_STEVEN, MeteorFalls_StevensCave_EventScript_Defeated
	waitse
	playse SE_PIN
	applymovement LOCALID_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN, MeteorFalls_StevensCave_Text_StevenDefeat
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_METEOR_FALLS_STEVEN
	release
	end

MeteorFalls_StevensCave_EventScript_Defeated::
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst:
	.string "STEVEN: Ω, ουάου, {PLAYER}.\n"
	.string "Εκπλήσσομαι που ήξερες πού να με \l"
	.string "βρεις.\p"
	.string "Mήπως, ε… με θεωρείς απλώς \n"
	.string "έναν μανιακό με τις πέτρες;\p"
	.string "Όχι, αυτό δεν μπορεί να είναι σωστό.\p"
	.string "Πολεμήσαμε δίπλα-δίπλα στο \n"
	.string "SPACE CENTER της SOOTOPOLIS.\p"
	.string "Θα πρέπει να έχεις μια πολύ καλή \n"
	.string "ιδέα για το πόσο καλός είμαι.\p"
	.string "Εντάξει, {PLAYER}, αν πρόκειται να \n"
	.string "θέσεις μια σοβαρή πρόκληση, \l"
	.string "να περιμένεις τα χειρότερα!$"

MeteorFalls_StevensCave_Text_StevenDefeat:
	.string "Eσύ…\n"
	.string "Δεν είχα ιδέα ότι θα γινόσουν \l"
	.string "τόσο δυνατός…$"

MeteorFalls_StevensCave_Text_MyPredictionCameTrue:
	.string "STEVEN: Αν το καλοσκεφτείς, από \n"
	.string "τότε που οι δρόμοι μας \l"
	.string "διασταυρώθηκαν στο GRANITE CAVE \l"
	.string "στο DEWFORD, είχα αυτό το συναίσθημα.\p"
	.string "Πίστευα ότι τελικά θα γινόσουν \n"
	.string "o CHAMPION.\p"
	.string "Οι προβλέψεις μου συνήθως \n"
	.string "βγαίνουν αληθινές.\p"
	.string "Και πού θα πας από εδώ;\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Φουφουφού, ούτε εγώ δεν θα \n"
	.string "μπορούσα να σου το πω αυτό.$"

