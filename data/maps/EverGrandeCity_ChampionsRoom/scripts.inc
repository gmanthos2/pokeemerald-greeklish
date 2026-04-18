.set LOCALID_WALLACE, 1
.set LOCALID_RIVAL, 2
.set LOCALID_BIRCH, 3

EverGrandeCity_ChampionsRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_ChampionsRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_ChampionsRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_ChampionsRoom_OnFrame
	.byte 0

EverGrandeCity_ChampionsRoom_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	end

EverGrandeCity_ChampionsRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_ChampionsRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_EnterRoom
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_EnterRoom::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp4
	waitmovement 0
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace
	waitmovement 0
	setvar VAR_TEMP_1, 1
	goto EverGrandeCity_ChampionsRoom_EventScript_Wallace
	releaseall
	end

EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_EventScript_Wallace::
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox EverGrandeCity_ChampionsRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLACE, EverGrandeCity_ChampionsRoom_Text_Defeat
	goto EverGrandeCity_ChampionsRoom_EventScript_Defeated
	end

EverGrandeCity_ChampionsRoom_EventScript_Defeated::
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, FALSE
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic
	addobject LOCALID_RIVAL
	call EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayAdvice
	goto_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice
	end

EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_MayAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF::
	closemessage
	addobject LOCALID_BIRCH
	applymovement LOCALID_BIRCH, EverGrandeCity_ChampionsRoom_Movement_BirchArrives
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex, MSGBOX_DEFAULT
	call ProfBirch_EventScript_RatePokedex
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchCongratulations, MSGBOX_DEFAULT
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalFollows
	waitmovement 0
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside, MSGBOX_DEFAULT
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations
	closemessage
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExit
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_GYM_GREETER
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer::
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth::
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_PlayerExit:
	walk_up
	delay_16
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_in_place_faster_right
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth:
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_up
	delay_8
	walk_in_place_faster_right
	delay_16
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalFollows:
	walk_right
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart:
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExit:
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_BirchArrives:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_in_place_faster_left
	step_end

EverGrandeCity_ChampionsRoom_Text_IntroSpeech:
	.string "WALLACE: Καλώς ήρθες, {PLAYER}{KUN}.\p"
	.string "Εκείνο το περιστατικό στη \n"
	.string "SOOTOPOLIS CITY… Έκανες εξαιρετική \l"
	.string "δουλειά, έδωσες τέλος στην κρίση!\p"
	.string "Ουπς!\p"
	.string "Δεν θα ήταν δίκαιο να πω ότι μόνο \n"
	.string "εσύ τερμάτισες την κρίση.\p"
	.string "Ξεπέρασες αυτή τη δύσκολη κατάσταση\n"
	.string "δουλεύοντας μαζί με τα POKéMON σου.\p"
	.string "Οι TRAINERS μεγαλώνουμε τα POKéMON \n"
	.string "μας δίνοντάς τους αντικείμενα και \l"
	.string "μαθαίνοντάς τους νέες κινήσεις.\p"
	.string "Αλλά κι εμείς οι ίδιοι μαθαίνουμε \n"
	.string "πολλά πράγματα από τα POKéMON.\p"
	.string "Και εδώ είναι που τα επιτεύγματά σου\n"
	.string "δοκιμάζονται απέναντι σε όσα\l"
	.string "έχουν καταφέρει άλλοι σαν εσένα.\p"
	.string "Τώρα!\p"
	.string "Ποιος μπορεί να χορέψει πιο κομψά με\n"
	.string "τα POKéMON του στο HOENN;\p"
	.string "Δείξε μου εδώ και τώρα!$"

EverGrandeCity_ChampionsRoom_Text_Defeat:
	.string "Εγώ, ο CHAMPION, πέφτω ηττημένος…\p"
	.string "Ήταν υπέροχη δουλειά.\n"
	.string "Η κομψότητά σου ήταν εκνευριστική.\l"
	.string "Κι όμως ήταν απολύτως ένδοξο!\p"
	.string "Εύγε, {PLAYER}{KUN}!\p"
	.string "Είσαι ένας πραγματικά ευγενής\n"
	.string "POKéMON TRAINER!$"

EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech:
	.string "WALLACE: Τα POKéMON που έστειλες στη\n"
	.string "μάχη…\p"
	.string "Άλλες φορές χόρευαν σαν ανοιξιάτικο \n"
	.string "αεράκι, και άλλες χτυπούσαν \l"
	.string "σαν κεραυνός.\p"
	.string "Ήταν με ανάλαφρη, αλλά σταθερή\n"
	.string "κομψότητα που οδήγησες τα POKéMON σου.\p"
	.string "Ακόμα κι εγώ θαμπώθηκα από την \n"
	.string "αριστοτεχνική σου απόδοση!\p"
	.string "Τώρα στέκεσαι στην ένδοξη κορυφή\n"
	.string "του POKéMON LEAGUE.\p"
	.string "Σε ανακηρύσσω CHAMPION της\n"
	.string "περιοχής HOENN…$"

EverGrandeCity_ChampionsRoom_Text_MayAdvice:
	.string "MAY: {PLAYER}{KUN}!\p"
	.string "Να μερικές συμβουλές πριν \n"
	.string "προκαλέσεις τον CHAMPION…$"

EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver:
	.string "MAY: Ε;\n"
	.string "Τι, τι, τι;\p"
	.string "{PLAYER}{KUN}…\n"
	.string "Θα μπορούσε άραγε…\l"
	.string "Να έχει ήδη τελειώσει;$"

EverGrandeCity_ChampionsRoom_Text_BrendanAdvice:
	.string "BRENDAN: {PLAYER}!\p"
	.string "Θα ήθελες μερικές συμβουλές πριν\n"
	.string "προκαλέσεις τον CHAMPION;…$"

EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon:
	.string "BRENDAN: {PLAYER}…\p"
	.string "Προσπαθείς να μου πεις ότι…\n"
	.string "έχεις νικήσει τον CHAMPION;$"

EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex:
	.string "PROF. BIRCH: Είδες;\n"
	.string "Τι σου έλεγα, {RIVAL};\p"
	.string "Δεν σου είπα ότι δεν χρειάζεται\n"
	.string "να ανησυχείς για το {PLAYER}{KUN};\p"
	.string "… … … … … … … …\n"
	.string "{PLAYER}{KUN}, τα κατάφερες επιτέλους.\p"
	.string "Όταν άκουσα ότι νίκησες τον πατέρα\n"
	.string "σου στο PETALBURG GYM,\l"
	.string "σκέφτηκα ότι ίσως είχες μια ευκαιρία…\p"
	.string "Αλλά το να γίνεις και CHAMPION!\p"
	.string "Α, ναι!\p"
	.string "Τι απέγινε το POKéDEX σου;\n"
	.string "Φέρε να δω.$"

EverGrandeCity_ChampionsRoom_Text_BirchCongratulations:
	.string "PROF. BIRCH: Τέλος πάντων,\n"
	.string "συγχαρητήρια!\p"
	.string "Τώρα, προχώρα περήφανα στο \n"
	.string "τελικό δωμάτιο!$"

EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe:
	.string "WALLACE: {PLAYER}{KUN}…\p"
	.string "Όχι, ας το θέσω σωστά.\p"
	.string "CHAMPION!\p"
	.string "Έλα μαζί μου.$"

EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside:
	.string "WALLACE: Λυπάμαι, αλλά…\p"
	.string "Από εδώ και πέρα, μόνο οι TRAINERS που \n"
	.string "έχουν γίνει CHAMPIONS μπορούν να μπουν.\p"
	.string "Αν θες περίμενε έξω με \n"
	.string "τον PROF. BIRCH.$"

EverGrandeCity_ChampionsRoom_Text_MayCongratulations:
	.string "MAY: Ουφ…\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "Αστειεύομαι! Δεν πειράζει!\n"
	.string "Αυτοί είναι οι κανόνες!\p"
	.string "{PLAYER}{KUN}!\n"
	.string "Ειλικρινά, συγχαρητήρια!$"

EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations:
	.string "BRENDAN: Τιιιιιιιιιι;! … … … … …\n"
	.string "… … … … … … … …\p"
	.string "Τι να κάνουμε, αφού αυτός είναι ο\n"
	.string "κανόνας.\p"
	.string "{PLAYER}, μπράβο!\n"
	.string "Συγχαρητήρια!$"

