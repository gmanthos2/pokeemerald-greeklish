.set LOCALID_WALLY, 6
.set LOCALID_WALLYS_UNCLE, 7
.set LOCALID_SCOTT, 11

MauvilleCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_OnTransition
	.byte 0

MauvilleCity_OnTransition:
	setflag FLAG_VISITED_MAUVILLE_CITY
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	clearflag FLAG_HIDE_SLATEPORT_MUSEUM_POPULATION
	setflag FLAG_SYS_TV_START
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	setvar VAR_MAUVILLE_GYM_STATE, 0
	call_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_MoveWattsonBackToGym
	end

MauvilleCity_EventScript_MoveWattsonBackToGym::
	clearflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	setflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setflag FLAG_WATTSON_REMATCH_AVAILABLE
	return

MauvilleCity_EventScript_Boy::
	msgbox MauvilleCity_Text_NurseHurtMonBackToHealth, MSGBOX_NPC
	end

MauvilleCity_EventScript_Maniac::
	msgbox MauvilleCity_Text_AllSortsOfPeopleComeThrough, MSGBOX_NPC
	end

MauvilleCity_EventScript_Woman::
	msgbox MauvilleCity_Text_RydelVeryGenerous, MSGBOX_NPC
	end

MauvilleCity_EventScript_RichBoy::
	msgbox MauvilleCity_Text_PokemonCanJumpYouOnBike, MSGBOX_NPC
	end

MauvilleCity_EventScript_CitySign::
	msgbox MauvilleCity_Text_CitySign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GymSign::
	msgbox MauvilleCity_Text_GymSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_BikeShopSign::
	msgbox MauvilleCity_Text_BikeShopSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GameCornerSign::
	msgbox MauvilleCity_Text_GameCornerSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_SchoolKidM::
	lock
	faceplayer
	goto_if_set FLAG_TV_EXPLAINED, MauvilleCity_EventScript_TVExplained
	msgbox MauvilleCity_Text_ExplainTV, MSGBOX_DEFAULT
	setflag FLAG_TV_EXPLAINED
	release
	end

MauvilleCity_EventScript_TVExplained::
	msgbox MauvilleCity_Text_BeenCheckingOutTV, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_UncleAskPlayerToBattleWally
	msgbox MauvilleCity_Text_UncleHesTooPeppy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_UncleAskPlayerToBattleWally::
	msgbox MauvilleCity_Text_UncleCanYouBattleWally, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_Wally::
	lockall
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_WallyRequestBattleAgain
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWantToChallengeGym, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_UncleYourePushingIt, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_WallyWeCanBeatAnyone, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WALLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWillYouBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_EventScript_BattleWallyPrompt::
	call_if_eq VAR_RESULT, YES, MauvilleCity_EventScript_BattleWally
	goto_if_eq VAR_RESULT, NO, MauvilleCity_EventScript_DeclineWallyBattle
	closemessage
	switch VAR_FACING
	case DIR_NORTH, MauvilleCity_EventScript_WallyAndUncleExitNorth
	case DIR_EAST, MauvilleCity_EventScript_WallyAndUncleExitEast
	end

MauvilleCity_EventScript_WallyAndUncleExitNorth::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth1
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitNorth1
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth1
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerFaceUncleNorth
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerNorth
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth2
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth2
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitNorth2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_WallyAndUncleExitEast::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast1
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitEast1
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast1
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerEast
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast2
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast2
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitEast2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_DefeatedWally::
	removeobject LOCALID_WALLY
	removeobject LOCALID_WALLYS_UNCLE
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLYS_UNCLE
	setflag FLAG_DEFEATED_WALLY_MAUVILLE
	setvar VAR_WALLY_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottApproachPlayerNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottApproachPlayerEast
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox MauvilleCity_Text_ScottYouDidntHoldBack, MSGBOX_DEFAULT
	closemessage
	addvar VAR_SCOTT_STATE, 1
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottExitEast
	removeobject LOCALID_SCOTT
	releaseall
	end

MauvilleCity_EventScript_ScottApproachPlayerNorth::
	addobject LOCALID_SCOTT
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottApproachPlayerNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottApproachPlayerEast::
	setobjectxyperm LOCALID_SCOTT, 12, 13
	addobject LOCALID_SCOTT
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottApproachPlayerEast
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitNorth::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitNorth
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottExitNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitEast::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitEast
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottExitEast
	waitmovement 0
	return

MauvilleCity_EventScript_BattleWally::
	msgbox MauvilleCity_Text_WallyHereICome, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_MAUVILLE, MauvilleCity_Text_WallyDefeat
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyIllGoBackToVerdanturf, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_ThankYouNotEnoughToBattle, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_UncleNoNeedToBeDown, MSGBOX_DEFAULT
	return

MauvilleCity_EventScript_DeclineWallyBattle::
	setflag FLAG_DECLINED_WALLY_BATTLE_MAUVILLE
	msgbox MauvilleCity_Text_WallyMyUncleWontKnowImStrong, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallyRequestBattleAgain::
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_WallyPleaseBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_Movement_WallyExitNorth1:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	step_end

MauvilleCity_Movement_WallyExitEast1:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallyExitNorth2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_WallyExitEast2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast2:
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitNorth:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitEast:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast1:
	delay_16
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth1:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_WallysUncleExitNorth1:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

MauvilleCity_Movement_WallysUncleExitEast1:
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_PlayerFaceUncleNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerNorth:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerEast:
	walk_right
	walk_up
	step_end

MauvilleCity_Movement_WallysUncleExitNorth2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallysUncleExitEast2:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_ScottApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

MauvilleCity_Movement_ScottExitNorth:
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

MauvilleCity_Movement_ScottExitEast:
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

MauvilleCity_EventScript_Wattson::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_ReceivedThunderbolt
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, MauvilleCity_EventScript_CompletedNewMauville
	goto_if_set FLAG_GOT_BASEMENT_KEY_FROM_WATTSON, MauvilleCity_EventScript_BegunNewMauville
	msgbox MauvilleCity_Text_WattsonNeedFavorTakeKey, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	setflag FLAG_GOT_BASEMENT_KEY_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_BegunNewMauville::
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CompletedNewMauville::
	msgbox MauvilleCity_Text_WattsonThanksTakeTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_THUNDERBOLT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_ReceivedThunderbolt::
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_RegisterWallyCall::
	lockall
	pokenavcall MauvilleCity_Text_WallyPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Text_RegisteredWally, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WALLY_MATCH_CALL
	clearflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	releaseall
	end

MauvilleCity_Text_UncleHesTooPeppy:
	.string "UNCLE: Εξαιτίας των POKéMON, o μικρός \n"
	.string "έχει περισσότερη ενέργεια, υποθέτω…\l"
	.string "Αλλά έχει γίνει υπερβολικά ζωηρός…$"

MauvilleCity_Text_WallyWantToChallengeGym:
	.string "WALLY: Αχ, UNCLE, σε παρακαλώ;\p"
	.string "Θέλω να προκαλέσω αυτό το GYM και \n"
	.string "να δω πόσο καλύτερος έχω γίνει.\p"
	.string "Σε παρακαλώ; Μπορώ, σε παρακαλώ;$"

MauvilleCity_Text_UncleYourePushingIt:
	.string "UNCLE: Τώρα στάσου, WALLY.\p"
	.string "Από τότε που άρχισες να ζεις με τα \n"
	.string "POKéMON, έχεις γίνει πολύ δυνατός.\p"
	.string "Αλλά δεν νομίζεις ότι το παρακάνεις\n"
	.string "να προκαλέσεις ξαφνικά ένα GYM;$"

MauvilleCity_Text_WallyWeCanBeatAnyone:
	.string "WALLY: Δεν το παρακάνω.\p"
	.string "Αν ενώσω τις δυνάμεις μου με το \n"
	.string "RALTS, μπορούμε να νικήσουμε τους\l"
	.string "πάντες!$"

MauvilleCity_Text_WallyWillYouBattleMe:
	.string "WALLY: Α! Γεια σου, {PLAYER}!\p"
	.string "Έχω δυναμώσει πολύ από τότε \n"
	.string "που γνωριστήκαμε.\p"
	.string "{PLAYER}, θέλω εσύ και ο UNCLE μου \n"
	.string "να το καταλάβετε.\p"
	.string "{PLAYER}, σε παρακαλώ, \n"
	.string "θα κάνεις μια μάχη μαζί μου;$"

MauvilleCity_Text_WallyMyUncleWontKnowImStrong:
	.string "WALLY: Αχ… Αν δεν με πολεμήσεις,\n"
	.string "{PLAYER}, ο UNCLE μου δεν θα ξέρει ότι \l"
	.string "έχω γίνει πραγματικά δυνατός.$"

MauvilleCity_Text_UncleCanYouBattleWally:
	.string "UNCLE: Αλήθεια, {PLAYER}{KUN};\n"
	.string "Εκ μέρους του WALLY, μπορώ να σου \l"
	.string "ζητήσω να πολεμήσεις \l"
	.string "μαζί του έστω και για αυτή τη φορά;\p"
	.string "Δεν νομίζω ότι πρόκειται να ακούσει \n"
	.string "τίποτα έτσι όπως είναι τώρα.$"

MauvilleCity_Text_WallyPleaseBattleMe:
	.string "WALLY: {PLAYER}, σε παρακαλώ!\n"
	.string "Μάχη μαζί μου, σε παρακαλώ.$"

MauvilleCity_Text_WallyHereICome:
	.string "WALLY: {PLAYER}, σε ευχαριστώ.\p"
	.string "ΟΚ… Έρχομαι!$"

MauvilleCity_Text_WallyDefeat:
	.string "WALLY: … … … … … … …\p"
	.string "… … … … … … … …\p"
	.string "Έχασα…$"

MauvilleCity_Text_WallyIllGoBackToVerdanturf:
	.string "WALLY: UNCLE…\n"
	.string "Θα επιστρέψω στο VERDANTURF…$"

MauvilleCity_Text_ThankYouNotEnoughToBattle:
	.string "{PLAYER}, σε ευχαριστώ.\n"
	.string "Το να είσαι TRAINER είναι\l"
	.string "δύσκολο, έτσι δεν είναι;\p"
	.string "Δεν αρκεί μόνο να έχεις POKéMON και\n"
	.string "να τα βάζεις σε μάχες. \l"
	.string "Το να είσαι πραγματικός \l"
	.string "TRAINER δεν είναι μόνο αυτό.$"

MauvilleCity_Text_UncleNoNeedToBeDown:
	.string "UNCLE: WALLY, δεν χρειάζεται να \n"
	.string "απογοητεύεσαι τόσο πολύ.\p"
	.string "Τι σε εμποδίζει να γίνεσαι \n"
	.string "όλο και πιο δυνατός;\p"
	.string "Έλα, πάμε σπίτι.\n"
	.string "Όλοι σε περιμένουν.$"

MauvilleCity_Text_UncleVisitUsSometime:
	.string "UNCLE: {PLAYER}{KUN}, μόλις συνειδητοποίησα\n"
	.string "ότι πρέπει να είσαι ο TRAINER που \l"
	.string "πρόσεχε τον WALLY όταν\l"
	.string "έπιασε τα POKéMON του.\p"
	.string "Γιατί δεν μας επισκέπτεσαι\n"
	.string "κάποια στιγμή στο VERDANTURF;\l"
	.string "Είμαι σίγουρος ότι \l"
	.string "ο WALLY θα το απολάμβανε.$"


MauvilleCity_Text_WallyPokenavCall:
	.string "… … … … … …\n"
	.string "… … … … … Μπιπ!\p"
	.string "WALLY: Α, γεια σου, {PLAYER}!\p"
	.string "Απλώς ήθελα να σου πω ότι\n"
	.string "ο UNCLE μου, μου αγόρασε ένα POKéNAV!\p"
	.string "Τώρα μπορώ να επικοινωνήσω μαζί σου\n"
	.string "οποιαδήποτε στιγμή, {PLAYER}!\p"
	.string "… … … … … …\n"
	.string "… … … … … Κλικ!$"

MauvilleCity_Text_RegisteredWally:
	.string "Καταχωρήθηκε ο WALLY\n"
	.string "στο POKéNAV.$"

MauvilleCity_Text_ScottYouDidntHoldBack:
	.string "SCOTT: Χεχε…\n"
	.string "Έβλεπα αυτόν τον αγώνα!\p"
	.string "Είσαι φίλος με εκείνο το αγόρι τον \n"
	.string "WALLY, έτσι δεν είναι;\p"
	.string "Αλλά δεν κρατήθηκες και τον νίκησες\n"
	.string "εντυπωσιακά.\p"
	.string "Ναι! Αυτό είναι το νόημα μιας\n"
	.string "πραγματικής μάχης POKéMON!\p"
	.string "Λατρεύω τους TRAINERS σαν κι εσένα!\p"
	.string "… … … … … …\n"
	.string "Θα σε επευφημώ!$"

MauvilleCity_Text_WattsonNeedFavorTakeKey:
	.string "WATTSON: Α, {PLAYER}{KUN}!\n"
	.string "Φαίνεσαι να έχεις πολλή ενέργεια!\l"
	.string "Αυτό είναι καλό, χαχαχαχαχα!\p"
	.string "Καλά! Αποφάσισα!\n"
	.string "Θέλω μια χάρη, {PLAYER}{KUN}!\p"
	.string "Το MAUVILLE CITY έχει έναν υπόγειο\n"
	.string "τομέα που λέγεται NEW MAUVILLE.\p"
	.string "{PLAYER}{KUN}, θα ήθελα να πας εκεί και\n"
	.string "να απενεργοποιήσεις τον \l"
	.string "GENERATOR.\p"
	.string "Ο GENERATOR λειτουργεί λίγο\n"
	.string "ασταθώς. Γίνεται επικίνδυνος.\p"
	.string "Ορίστε, αυτό είναι το KEY \n"
	.string "για να μπεις στο NEW MAUVILLE.$"

MauvilleCity_Text_WattsonWontBeChallenge:
	.string "WATTSON: Μην ανησυχείς για αυτό.\n"
	.string "Δεν θα είναι πρόκληση για σένα.\p"
	.string "Η είσοδος στο NEW MAUVILLE απέχει \n"
	.string "μόνο λίγο SURF από το ROUTE 110.\p"
	.string "Aυτό είναι λοιπόν, \n"
	.string "έχεις την εμπιστοσύνη μου!\l"
	.string "Χαχαχαχαχα!$"

MauvilleCity_Text_WattsonThanksTakeTM:
	.string "WATTSON: Χαχαχαχαχα!\p"
	.string "Το ήξερα, {PLAYER}{KUN}! Ήξερα ότι έκανα\n"
	.string "τη σωστή επιλογή να στο ζητήσω!\p"
	.string "Αυτές είναι οι ευχαριστίες μου-ένα \n"
	.string "TM που περιέχει το THUNDERBOLT!\p"
	.string "Προχώρα, το κέρδισες!$"

MauvilleCity_Text_WattsonYoungTakeCharge:
	.string "WATTSON: Χαχαχαχαχα!\p"
	.string "Με ευχαριστεί αφάνταστα να βλέπω \n"
	.string "νέους να αναλαμβάνουν δράση!$"

MauvilleCity_Text_NurseHurtMonBackToHealth:
	.string "Ξέρεις, είναι ωραίο να κάνεις μάχες\n"
	.string "POKéMON και τα λοιπά…\p"
	.string "Αλλά αν το POKéMON σου τραυματιστεί,\n"
	.string "πρέπει να το κάνεις ξανά καλά.$"

MauvilleCity_Text_AllSortsOfPeopleComeThrough:
	.string "Οι δρόμοι αυτής της πόλης απλώνονται \n"
	.string "βόρεια, νότια, ανατολικά και δυτικά.\p"
	.string "Εξαιτίας αυτού, έρχονται άνθρωποι από\n"
	.string "όλες τις μεριές.$"

MauvilleCity_Text_RydelVeryGenerous:
	.string "Πήγες ακόμα στο RYDEL'S CYCLES;\p"
	.string "O RYDEL, ο ιδιοκτήτης, \n"
	.string "είναι πολύ γενναιόδωρος.$"

MauvilleCity_Text_PokemonCanJumpYouOnBike:
	.string "Ακόμη και αν κάνεις βόλτα με \n"
	.string "ένα BIKE, μπορεί να σου επιτεθούν\l"
	.string "άγρια POKéMON.$"

MauvilleCity_Text_CitySign:
	.string "MAUVILLE CITY\n"
	.string "Η λαμπερή πόλη της διασκέδασης!$"

MauvilleCity_Text_GymSign:
	.string "MAUVILLE CITY POKéMON GYM\n"
	.string "LEADER: WATTSON\l"
	.string "Ο χαρούμενος και\l"
	.string "ηλεκτρισμένος άνδρας!$"

MauvilleCity_Text_BikeShopSign:
	.string "Οδήγησε στο χαλίκι και \n"
	.string "ανατάραξε την ψυχή σου!\l"
	.string "RYDEL'S CYCLES$"

MauvilleCity_Text_GameCornerSign:
	.string "Το σημείο παιχνιδιού για όλους!\n"
	.string "MAUVILLE GAME CORNER$"

MauvilleCity_Text_ExplainTV:
	.string "Γεια, βλέπεις καθόλου τηλεόραση;\p"
	.string "Προστέθηκαν πρόσφατα ένα\n"
	.string "σωρό νέες εκπομπές.\p"
	.string "Η τηλεόραση είναι τόσο κουλ.\n"
	.string "Έχω δει έτσι ξαφνικά τους \l"
	.string "φίλους μου σε αυτήν.\p"
	.string "Και, μερικές φορές, σε \n"
	.string "βάζουν ακόμα και \l"
	.string "χωρίς να στο πουν.\p"
	.string "Μακάρι να έβγαινα κάποια \n"
	.string "στιγμή στην τηλεόραση.\p"
	.string "Γι' αυτό νομίζω ότι πρέπει \n"
	.string "να βλέπεις τηλεόραση \l"
	.string "όποτε μπορείς.$"

MauvilleCity_Text_BeenCheckingOutTV:
	.string "Γεια, παρακολουθείς τηλεόραση;$"
