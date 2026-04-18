.set LOCALID_TRICK_MASTER, 1

Route110_TrickHouseEnd_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Route110_TrickHouseEnd_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_TrickHouseEnd_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route110_TrickHouseEnd_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route110_TrickHouseEnd_OnWarp
	.byte 0

Route110_TrickHouseEnd_OnResume:
	call_if_eq VAR_TEMP_1, 1, Route110_TrickHouseEnd_EventScript_SetDoorClosedMetatile
	end

Route110_TrickHouseEnd_OnTransition:
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	special SetTrickHouseNuggetFlag
	end

Route110_TrickHouseEnd_OnWarp:
	map_script_2 VAR_TEMP_2, 0, Route110_TrickHouseEnd_EventScript_SetTrickMasterPos
	.2byte 0

Route110_TrickHouseEnd_EventScript_SetTrickMasterPos::
	addobject LOCALID_TRICK_MASTER
	showobjectat LOCALID_TRICK_MASTER, MAP_ROUTE110_TRICK_HOUSE_END
	turnobject LOCALID_TRICK_MASTER, DIR_EAST
	end

Route110_TrickHouseEnd_OnFrame:
	map_script_2 VAR_TEMP_1, 0, Route110_TrickHouseEnd_EventScript_CloseDoor
	.2byte 0

Route110_TrickHouseEnd_EventScript_CloseDoor::
	setvar VAR_TEMP_1, 1
	call Route110_TrickHouseEnd_EventScript_SetDoorClosedMetatile
	special DrawWholeMapView
	end

Route110_TrickHouseEnd_EventScript_SetDoorClosedMetatile::
	setmetatile 10, 1, METATILE_GenericBuilding_TrickHouse_Door_Closed, TRUE
	return

Route110_TrickHouseEnd_EventScript_TrickMaster::
	lock
	faceplayer
	msgbox Route110_TrickHouseEnd_Text_YouveMadeItToMe, MSGBOX_DEFAULT
	setvar VAR_TEMP_2, 1
	switch VAR_TRICK_HOUSE_LEVEL
	case 0, Route110_TrickHouseEnd_EventScript_CompletedPuzzle1
	case 1, Route110_TrickHouseEnd_EventScript_CompletedPuzzle2
	case 2, Route110_TrickHouseEnd_EventScript_CompletedPuzzle3
	case 3, Route110_TrickHouseEnd_EventScript_CompletedPuzzle4
	case 4, Route110_TrickHouseEnd_EventScript_CompletedPuzzle5
	case 5, Route110_TrickHouseEnd_EventScript_CompletedPuzzle6
	case 6, Route110_TrickHouseEnd_EventScript_CompletedPuzzle7
	case 7, Route110_TrickHouseEnd_EventScript_CompletedPuzzle8
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle1::
	msgbox Route110_TrickHouseEnd_Text_AllNightToPlantTrees, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_RARE_CANDY
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle2::
	msgbox Route110_TrickHouseEnd_Text_AllNightToMakeMaze, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_TIMER_BALL
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle3::
	msgbox Route110_TrickHouseEnd_Text_AllNightToPreparePanels, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_HARD_STONE
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle4::
	msgbox Route110_TrickHouseEnd_Text_AllNightToShoveBoulders, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_SMOKE_BALL
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle5::
	msgbox Route110_TrickHouseEnd_Text_AllNightToMakeMechadolls, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_TM_TAUNT
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle6::
	msgbox Route110_TrickHouseEnd_Text_AllNightToInstallDoors, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_MAGNET
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle7::
	msgbox Route110_TrickHouseEnd_Text_AllNightSettingUpArrows, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_PP_MAX
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle8::
	msgbox Route110_TrickHouseEnd_Text_AllNightPolishingFloors, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_SOUTH, Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwaySouth
	call_if_eq VAR_FACING, DIR_NORTH, Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayNorth
	call_if_eq VAR_FACING, DIR_WEST, Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayWest
	call_if_eq VAR_FACING, DIR_EAST, Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayEast
	delay 30
	msgbox Route110_TrickHouseEnd_Text_FountainOfIdeasRunDry, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TRICK_MASTER, Common_Movement_FacePlayer
	waitmovement 0
	delay 30
	msgbox Route110_TrickHouseEnd_Text_DefeatedMePreferWhichTent, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	call Route110_TrickHouseEnd_EventScript_ChooseTent
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_NoRoomForTent
	msgbox Route110_TrickHouseEnd_Text_LeavingOnJourney, MSGBOX_DEFAULT
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	special ResetTrickHouseNuggetFlag
	release
	end

Route110_TrickHouseEnd_EventScript_ChooseTent::
	multichoice 0, 0, MULTI_TENT, TRUE
	switch VAR_RESULT
	case 0, Route110_TrickHouseEnd_EventScript_GiveRedTent
	goto Route110_TrickHouseEnd_EventScript_GiveBlueTent

Route110_TrickHouseEnd_EventScript_GiveRedTent::
	givedecoration DECOR_RED_TENT
	return

Route110_TrickHouseEnd_EventScript_GiveBlueTent::
	givedecoration DECOR_BLUE_TENT
	return

Route110_TrickHouseEnd_EventScript_TrickMasterExit::
	applymovement LOCALID_TRICK_MASTER, Route110_TrickHouse_Movement_TrickMasterSpin
	waitmovement 0
	playse SE_M_EXPLOSION
	applymovement LOCALID_TRICK_MASTER, Route110_TrickHouse_Movement_TrickMasterJumpAway
	waitmovement 0
	removeobject LOCALID_TRICK_MASTER
	addvar VAR_TRICK_HOUSE_LEVEL, 1
	return

Route110_TrickHouseEnd_EventScript_BagFull::
	call Common_EventScript_BagIsFull
	msgbox Route110_TrickHouseEnd_Text_NoRoomForThis, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 1
	return

Route110_TrickHouseEnd_EventScript_NoRoomForTent::
	call Common_EventScript_NoRoomForDecor
	msgbox Route110_TrickHouseEnd_Text_NoRoomInPC, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 1
	return

Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwaySouth::
	applymovement LOCALID_TRICK_MASTER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayNorth::
	applymovement LOCALID_TRICK_MASTER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayWest::
	applymovement LOCALID_TRICK_MASTER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayEast::
	applymovement LOCALID_TRICK_MASTER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

Route110_TrickHouseEnd_EventScript_TrickMasterExitTrigger::
	lockall
	turnobject LOCALID_TRICK_MASTER, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_TRICK_MASTER, Common_Movement_ExclamationMark
	waitmovement 0
	delay 20
	applymovement LOCALID_TRICK_MASTER, Route110_TrickHouseEnd_Movement_TrickMasterSurprise
	waitmovement 0
	playse SE_M_EXPLOSION
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox Route110_TrickHouseEnd_Text_YoureIgnoringMe, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route110_TrickHouseEnd_Movement_KeepPlayerInRoom
	waitmovement 0
	delay 4
	turnobject LOCALID_TRICK_MASTER, DIR_EAST
	releaseall
	end

Route110_TrickHouseEnd_Movement_KeepPlayerInRoom:
	walk_down
	step_end

Route110_TrickHouseEnd_Movement_TrickMasterSurprise:
	jump_in_place_left
	step_end

Route110_TrickHouseEnd_Text_YouveMadeItToMe:
	.string "Ααακ!\n"
	.string "Τα κατάφερες μέχρι εδώ;\l"
	.string "Χμμμ… Είσαι έξυπνο!$"

Route110_TrickHouseEnd_Text_AllNightToPlantTrees:
	.string "Μου πήρε όλη τη νύχτα να \n"
	.string "φυτέψω όλα αυτά τα δέντρα…\p"
	.string "Είσαι σχεδόν ίσο με το μεγαλείο\n"
	.string "μου, κατά ένα, δύο, τρία,\l"
	.string "τέσσερα, πέντε, έξι επίπεδα!$"

Route110_TrickHouseEnd_Text_AllNightToMakeMaze:
	.string "Μου πήρε όλη τη νύχτα να\n"
	.string "φτιάξω το λαβύρινθο…\p"
	.string "Είσαι σχεδόν ίσο με το \n"
	.string "μεγαλείο μου, κατά ένα, δύο, \l"
	.string "τρία, τέσσερα, πέντε επίπεδα!$"

Route110_TrickHouseEnd_Text_AllNightToPreparePanels:
	.string "Μου πήρε όλη τη νύχτα να\n"
	.string "ετοιμάσω τους τοίχους…\p"
	.string "Είσαι σχεδόν ίσο με το \n"
	.string "μεγαλείο μου, κατά ένα, δύο, \l"
	.string "τρία, τέσσερα επίπεδα!$"

Route110_TrickHouseEnd_Text_AllNightToShoveBoulders:
	.string "Μου πήρε όλη τη νύχτα να \n"
	.string "βγάλω αυτούς τους βράχους…\p"
	.string "Είσαι σχεδόν ίσο με το \n"
	.string "μεγαλείο μου, κατά ένα, δύο, \l"
	.string "τρία επίπεδα!$"

Route110_TrickHouseEnd_Text_AllNightToMakeMechadolls:
	.string "Μου πήρε όλη τη νύχτα να\n"
	.string "κάνω τα MECHADOLLS και\l"
	.string "να βρω το τεστ…\p"
	.string "Είσαι σχεδόν ίσο με το \n"
	.string "μεγαλείο μου, κατά ένα, δύο \l"
	.string "επίπεδα!$"

Route110_TrickHouseEnd_Text_AllNightToInstallDoors:
	.string "Μου πήρε όλη νύχτα να\n"
	.string "εγκαταστήσω τις πόρτες…\p"
	.string "Είσαι σχεδόν ίσο με το\n"
	.string "μεγαλείο μου!$"

Route110_TrickHouseEnd_Text_AllNightSettingUpArrows:
	.string "Μου πήρε όλη τη νύχτα να \n"
	.string "στήσω τα βέλη…\p"
	.string "Είσαι το ίδιο σπουδαίο με\n"
	.string "εμένα!$"

Route110_TrickHouseEnd_Text_AllNightPolishingFloors:
	.string "Μου πήρε όλη τη νύχτα να \n"
	.string "καθαρίζω πατώματα…\p"
	.string "Είσαι πάνω από εμένα σε\n"
	.string "μεγαλείο!\l"
	.string "Ίσως…$"

Route110_TrickHouseEnd_Text_FountainOfIdeasRunDry:
	.string "Τι-τι να κάνω;\n"
	.string "Η πηγή ιδεών μου για\l"
	.string "τεχνάσματα στέρεψε…\p"
	.string "Ίσως είναι καιρός να \n"
	.string "κάνω μια περιοδεία \l"
	.string "στη χώρα για νέες ιδέες…$"

Route110_TrickHouseEnd_Text_DefeatedMePreferWhichTent:
	.string "Μισώ να παραδέχομαι την\n"
	.string "ήττα, αλλά με νίκησες!\p"
	.string "Βέβαια, πρέπει να σε \n"
	.string "μάγεψε το χάρισμά μου για\l"
	.string "να έρχεσαι ξανά. \l"
	.string "Ναι, αυτό πρέπει να είναι!\p"
	.string "Αλλά αυτό δεν έχει καμία \n"
	.string "σχέση με την ήττα μου!\p"
	.string "Σε αναγνώριση της φιλίας\n"
	.string "σου με την ιδιοφυΐα \l"
	.string "μου, σου ζητώ να \l"
	.string "πάρεις αυτό το δώρο!\p"
	.string "Βασικά υπάρχουν δύο--\n"
	.string "μια RED TENT και μια \l"
	.string "BLUE TENT.\l"
	.string "Ποια προτιμάς;$"

Route110_TrickHouseEnd_Text_NoRoomInPC:
	.string "Τι; Δεν έχεις χώρο στο PC;\n"
	.string "Τι υποτίθεται να \l"
	.string "κάνω τώρα;\p"
	.string "Μακάρι να μπορούσα να το \n"
	.string "πω αυτό, αλλά είμαι πολύ\l"
	.string "καλός, έλα αργότερα!$"

Route110_TrickHouseEnd_Text_LeavingOnJourney:
	.string "… … … … … …\p"
	.string "Φεύγω σε ένα ταξίδι \n"
	.string "ανακάλυψης. \l"
	.string "Για την αναζήτηση νέων \l"
	.string "κόλπων.\p"
	.string "Ελπίζω ότι μια μέρα θα με\n"
	.string "επισκεφτείς ξανά.\p"
	.string "Και τώρα, αντίο!$"

Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward:
	.string "Καλά!\n"
	.string "Κέρδισες αυτή την ανταμοιβή!$"

Route110_TrickHouseEnd_Text_NoRoomForThis:
	.string "Τι; Δεν έχεις χώρο γι' αυτό;\n"
	.string "Τι είδους αντικείμενα \l"
	.string "κουβαλάς;\p"
	.string "Αλλά εντάξει, αφού έφτασες \n"
	.string "στο τέλος, η ανταμοιβή \l"
	.string "σου θα είναι μαζί μου \l"
	.string "για αργότερα.$"

Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou:
	.string "Σβήσε αυτό το \n"
	.string "χαμόγελο από το πρόσωπό\l"
	.string "σου! Δεν κέρδισες ακόμα!\p"
	.string "Θα φτιάξω νέα κόλπα \n"
	.string "για να σε μπερδέψω, θα\l"
	.string "το κάνω.\l"
	.string "Μπορείς να με κοροϊδέψεις \l"
	.string "μόνο όταν τελειώσεις.\p"
	.string "Έλα πάλι για το επόμενο\n"
	.string "συναρπαστικό επεισόδιο!$"

Route110_TrickHouseEnd_Text_YoureIgnoringMe:
	.string "Τώρα με αγνοείς;\n"
	.string "Αυτό, το θεωρώ τραγικό!$"

