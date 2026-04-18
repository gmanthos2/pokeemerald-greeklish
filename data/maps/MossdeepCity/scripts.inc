.set LOCALID_GRUNT_1, 10
.set LOCALID_GRUNT_2, 11
.set LOCALID_GRUNT_3, 12
.set LOCALID_GRUNT_4, 13
.set LOCALID_MAXIE, 14
.set LOCALID_SCOTT, 16

MossdeepCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_OnTransition
	.byte 0

MossdeepCity_OnTransition:
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	end

MossdeepCity_EventScript_PokefanF::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_PokefanFMagmaGone
	msgbox MossdeepCity_Text_SpaceCenterReceivedLetter, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_PokefanFMagmaGone::
	msgbox MossdeepCity_Text_SpaceCenterLaunchingRockets, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_Sailor::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_SailorMagmaGone
	msgbox MossdeepCity_Text_MossdeepTargetedByMagma, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_SailorMagmaGone::
	msgbox MossdeepCity_Text_FeelReliefOnLand, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_NinjaBoy::
	msgbox MossdeepCity_Text_WailmerWatching, MSGBOX_NPC
	end

MossdeepCity_EventScript_ExpertM::
	msgbox MossdeepCity_Text_LifeNeedsSeaToLive, MSGBOX_NPC
	end

MossdeepCity_EventScript_Girl::
	msgbox MossdeepCity_Text_NiceIfWorldCoveredByFlowers, MSGBOX_NPC
	end

MossdeepCity_EventScript_Woman::
	msgbox MossdeepCity_Text_SpecialSpaceCenterRock, MSGBOX_NPC
	end

MossdeepCity_EventScript_WhiteRock::
	msgbox MossdeepCity_Text_ItsAWhiteRock, MSGBOX_SIGN
	end

MossdeepCity_EventScript_GymSign::
	msgbox MossdeepCity_Text_GymSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_CitySign::
	msgbox MossdeepCity_Text_CitySign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_SpaceCenterSign::
	msgbox MossdeepCity_Text_SpaceCenterSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_VisitedMossdeep::
	setflag FLAG_VISITED_MOSSDEEP_CITY
	setvar VAR_TEMP_1, 1
	end

MossdeepCity_EventScript_TeamMagmaEnterSpaceCenter::
	lockall
	applymovement LOCALID_MAXIE, MossdeepCity_Movement_MaxieGestureToSpaceCenter
	waitmovement 0
	applymovement LOCALID_GRUNT_1, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_2, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_3, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_4, MossdeepCity_Movement_GruntFaceSpaceCenter
	waitmovement 0
	applymovement LOCALID_MAXIE, MossdeepCity_Movement_MaxieEnterSpaceCenter
	applymovement LOCALID_GRUNT_1, MossdeepCity_Movement_Grunt1EnterSpaceCenter
	applymovement LOCALID_GRUNT_2, MossdeepCity_Movement_Grunt2EnterSpaceCenter
	applymovement LOCALID_GRUNT_3, MossdeepCity_Movement_Grunt3EnterSpaceCenter
	applymovement LOCALID_GRUNT_4, MossdeepCity_Movement_Grunt4EnterSpaceCenter
	waitmovement 0
	removeobject LOCALID_MAXIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_GRUNT_4
	delay 30
	setvar VAR_MOSSDEEP_CITY_STATE, 2
	setflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	releaseall
	end

MossdeepCity_Movement_MaxieGestureToSpaceCenter:
	delay_16
	face_right
	delay_16
	delay_16
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_GruntFaceSpaceCenter:
	face_right
	delay_16
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_MaxieEnterSpaceCenter:
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt1EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt2EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt3EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt4EnterSpaceCenter:
	delay_16
	delay_8
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_EventScript_Man::
	lock
	faceplayer
	msgbox MossdeepCity_Text_SurfExhilarating, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_EventScript_KingsRockBoy::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_KINGS_ROCK, MossdeepCity_EventScript_ReceivedKingsRock
	msgbox MossdeepCity_Text_WantKingsRockStevenGaveMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_EventScript_DeclineKingsRock
	msgbox MossdeepCity_Text_YouCanKeepIt, MSGBOX_DEFAULT
	giveitem ITEM_KINGS_ROCK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_KINGS_ROCK
	release
	end

MossdeepCity_EventScript_ReceivedKingsRock::
	msgbox MossdeepCity_Text_StevensHouseOverThere, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_DeclineKingsRock::
	msgbox MossdeepCity_Text_WhatToDoWithWeirdRock, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_BlackBelt::
	msgbox MossdeepCity_Text_SootopolisNewGymLeader, MSGBOX_NPC
	end

MossdeepCity_EventScript_Scott::
	lock
	faceplayer
	msgbox MossdeepCity_Text_ScottSomethingWrongWithTown, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, MossdeepCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MossdeepCity_EventScript_ScottExitEast
	addvar VAR_SCOTT_STATE, 1
	removeobject LOCALID_SCOTT
	release
	end

MossdeepCity_EventScript_ScottExitNorth::
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, MossdeepCity_Movement_ScottExitNorth
	waitmovement 0
	return

MossdeepCity_EventScript_ScottExitEast::
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, MossdeepCity_Movement_ScottExitEast
	waitmovement 0
	return

MossdeepCity_Movement_PlayerWatchScottExit:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MossdeepCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Text_WantKingsRockStevenGaveMe:
	.string "Το πήρα από τον STEVEN, αλλά δεν \n"
	.string "ξέρω σε τι χρησιμεύει.\p"
	.string "Νομίζω λέγεται KING'S ROCK.\n"
	.string "Το θέλεις;$"

MossdeepCity_Text_YouCanKeepIt:
	.string "Γιατί να το θέλεις;\n"
	.string "Είσαι περίεργος τύπος.\p"
	.string "Μπορείς να το κρατήσεις, αλλά κράτα \n"
	.string "το μυστικό από τον STEVEN.$"

MossdeepCity_Text_StevensHouseOverThere:
	.string "Tο σπίτι του STEVEN είναι \n"
	.string "ακριβώς εκεί!$"

MossdeepCity_Text_WhatToDoWithWeirdRock:
	.string "Ναι, το ίδιο νομίζεις κι εσύ! Τι να \n"
	.string "κάνεις μια τόσο περίεργη πέτρα;$"

MossdeepCity_Text_WailmerWatching:
	.string "Γύρω από το MOSSDEEP, μπορείς \n"
	.string "να δεις άγρια WAILMER.\p"
	.string "Λέγεται, ε…\n"
	.string "Πώς το έλεγαν…\p"
	.string "WAI, WAI, WAI…\p"
	.string "WAILMER watching!$"

MossdeepCity_Text_SpaceCenterReceivedLetter:
	.string "To SPACE CENTER του νησιού \n"
	.string "εκτοξεύει τεράστιους πυραύλους.\p"
	.string "Υπάρχει μια αναστάτωση για ένα \n"
	.string "γράμμα που έλαβαν πρόσφατα.$"

MossdeepCity_Text_SpaceCenterLaunchingRockets:
	.string "To SPACE CENTER του νησιού \n"
	.string "εκτοξεύει τεράστιους πυραύλους.$"

MossdeepCity_Text_MossdeepTargetedByMagma:
	.string "Άκουσα από έναν φίλο SAILOR ότι η \n"
	.string "TEAM AQUA εγκαταστάθηκε στο LILYCOVE.\p"
	.string "Άκουσα επίσης ότι κάποιος τους \n"
	.string "νίκησε για τα καλά!\p"
	.string "Αλλά το MOSSDEEP εδώ έχει μπει \n"
	.string "στο στόχαστρο της TEAM MAGMA.\p"
	.string "Αν θες να μάθεις τι σχεδιάζουν, \n"
	.string "πήγαινε στο SPACE CENTER.$"

MossdeepCity_Text_FeelReliefOnLand:
	.string "Είμαι SAILOR, οπότε η θάλασσα \n"
	.string "είναι προφανώς πιο σημαντική για μένα.\p"
	.string "Αλλά ξέρεις; Όταν επιστρέφω στη \n"
	.string "στεριά μετά από ένα ταξίδι, \l"
	.string "νιώθω ανακούφιση!$"

MossdeepCity_Text_NiceIfWorldCoveredByFlowers:
	.string "Δεν θα ήταν ωραία;\p"
	.string "Αν όλος ο κόσμος ήταν καλυμμένος \n"
	.string "με φυτά και λουλούδια όπως αυτό \l"
	.string "το νησί;$"

MossdeepCity_Text_LifeNeedsSeaToLive:
	.string "Κάθε ζωή χρειάζεται τη θάλασσα \n"
	.string "για να ζήσει, παρόλο που κατοικεί \l"
	.string "στη στεριά.\p"
	.string "Η ζωή, έχοντας διανύσει την πορεία \n"
	.string "της, γίνεται χώμα και επιστρέφει \l"
	.string "στη γη.\p"
	.string "Και η θάλασσα είναι πάντα \n"
	.string "συνδεδεμένη με τη στεριά.\p"
	.string "Ναι, όπως ακριβώς αυτή η ακτή.$"

MossdeepCity_Text_SurfExhilarating:
	.string "Ένα ταξίδι με πλοίο είναι καλό.\p"
	.string "Αλλά το να διασχίζεις τη θάλασσα \n"
	.string "με POKéMON χρησιμοποιώντας SURF…\p"
	.string "Αυτό είναι ένα συναρπαστικό ταξίδι!\n"
	.string "Δεν συμφωνείς, νεαρέ;$"

MossdeepCity_Text_SpecialSpaceCenterRock:
	.string "Αυτή η πέτρα έχει ιδιαίτερη σημασία \n"
	.string "για τους ανθρώπους στο SPACE CENTER.\p"
	.string "Την έβαλαν εδώ ως ευχή για να \n"
	.string "πετούν οι πύραυλοί τους με ασφάλεια.\p"
	.string "Όταν κάνεις μια ευχή, τι \n"
	.string "χρησιμοποιείς; Εύχεσαι σε ένα αστέρι;\p"
	.string "Εγώ χρησιμοποιώ μια ετικέτα \n"
	.string "ευχών για να το πραγματοποιήσω.\p"
	.string "Αυτό κάνω εγώ.$"

MossdeepCity_Text_ItsAWhiteRock:
	.string "Είναι μια λευκή πέτρα.$"

MossdeepCity_Text_GymSign:
	.string "MOSSDEEP CITY POKéMON GYM\n"
	.string "GYM LEADERS: LIZA & TATE\p"
	.string "“Ο μυστικιστικός συνδυασμός!”$"

MossdeepCity_Text_CitySign:
	.string "MOSSDEEP CITY\n"
	.string "“Το σύνθημά μας: \l"
	.string "Να αγαπάτε τα POKéMON!”$"

MossdeepCity_Text_SpaceCenterSign:
	.string "MOSSDEEP SPACE CENTER\n"
	.string "“Το κοντινότερο μέρος \l"
	.string "στο διάστημα.”$"

MossdeepCity_Text_ScottSomethingWrongWithTown:
	.string "SCOTT: {PLAYER}, νιώθεις καλά;\n"
	.string "Εγώ είμαι υπέροχα!\p"
	.string "Άκουσα ότι οι GYM LEADERS του \n"
	.string "MOSSDEEP είναι αρκετά δυνατοί, \l"
	.string "οπότε αποφάσισα να έρθω να δω \l"
	.string "ο ίδιος.\p"
	.string "Αλλά κάτι δεν πάει καλά με \n"
	.string "αυτή την πόλη.\p"
	.string "Ο κόσμος μιλάει για ένα \n"
	.string "προειδοποιητικό γράμμα και \l"
	.string "το SPACE CENTER…\p"
	.string "Δεν νομίζω ότι με αφορά \n"
	.string "με κάποιο τρόπο, όμως.$"

MossdeepCity_Text_SootopolisNewGymLeader:
	.string "Αχ… Είναι υπέροχο να αφήνεις τα \n"
	.string "κύματα να ξεπλένουν τα πόδια σου…\p"
	.string "Μιλώντας για κύματα, ξέρεις \n"
	.string "εκείνη την πόλη-νησί SOOTOPOLIS;\p"
	.string "Νομίζω ότι το GYM εκεί απέκτησε \n"
	.string "νέο GYM LEADER.\p"
	.string "Λένε ότι ο νέος GYM LEADER \n"
	.string "ήταν κάποτε μέντορας του WALLACE.$"

