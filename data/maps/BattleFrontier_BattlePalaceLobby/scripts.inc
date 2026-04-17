.set LOCALID_ATTENDANT_SINGLES, 1
.set LOCALID_ATTENDANT_DOUBLES, 6

BattleFrontier_BattlePalaceLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePalaceLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePalaceLobby_OnWarp
	.byte 0

BattleFrontier_BattlePalaceLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePalaceLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattlePalaceLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePalaceLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePalaceLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePalaceLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePalaceLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePalaceLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePalaceLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattlePalaceLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattlePalaceLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattlePalaceLobby_Text_FailedToSaveBeforeEndingChallenge, MSGBOX_DEFAULT
	closemessage
	palace_set PALACE_DATA_WIN_STREAK, 0
	palace_set PALACE_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePalaceLobby_EventScript_DefeatedMaven
	msgbox BattleFrontier_BattlePalaceLobby_Text_FirmTrueBondsFor7WinStreak, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_GiveBattlePoints

BattleFrontier_BattlePalaceLobby_EventScript_DefeatedMaven::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ToDefeatMavenAnd7Trainers, MSGBOX_DEFAULT
BattleFrontier_BattlePalaceLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattlePalaceLobby_Text_PresentYouWithBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattlePalaceLobby_Text_FeatWillBeRecorded
	waitmessage
	call BattleFrontier_BattlePalaceLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattlePalaceLobby_Text_ResultsWillBeRecorded
	waitmessage
	palace_set PALACE_DATA_WIN_STREAK_ACTIVE, FALSE
	call BattleFrontier_BattlePalaceLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_SaveAfterChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	special HealPlayerParty
	palace_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge
	message BattleFrontier_BattlePalaceLobby_Text_LikeToRecordMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge
	case 0, BattleFrontier_BattlePalaceLobby_EventScript_RecordMatch
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge

BattleFrontier_BattlePalaceLobby_EventScript_RecordMatch::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge::
	return

BattleFrontier_BattlePalaceLobby_EventScript_ResumeChallenge::
	lockall
	msgbox BattleFrontier_BattlePalaceLobby_Text_WeHaveBeenWaiting, MSGBOX_DEFAULT
	message BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge
	waitmessage
	palace_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto BattleFrontier_BattlePalaceLobby_EventScript_EnterChallenge

BattleFrontier_BattlePalaceLobby_EventScript_SinglesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PALACE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleFrontier_BattlePalaceLobby_EventScript_Attendant
	end

BattleFrontier_BattlePalaceLobby_EventScript_DoublesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PALACE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleFrontier_BattlePalaceLobby_EventScript_Attendant
	end

BattleFrontier_BattlePalaceLobby_EventScript_Attendant::
	palace_get PALACE_DATA_PRIZE
	goto_if_ne VAR_RESULT, ITEM_NONE, BattleFrontier_BattlePalaceLobby_EventScript_WonChallenge
	special SavePlayerParty
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForSingleBattle
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForDoubleBattle
BattleFrontier_BattlePalaceLobby_EventScript_AskTakeChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_AskTakeSingleBattleChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_AskTakeDoubleBattleChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePalaceLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattlePalaceLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattlePalaceLobby_Text_WhichChallenge
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePalaceLobby_Text_NowSelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge2, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattlePalaceLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	palace_init
	palace_set PALACE_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattlePalaceLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePalaceLobby_Text_FollowMe, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_BattlePalaceLobby_EventScript_WalkToDoor
	warp MAP_BATTLE_FRONTIER_BATTLE_PALACE_CORRIDOR, 8, 13
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattlePalaceLobby_EventScript_ExplainChallenge::
	goto_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_ExplainDoublesChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainSingleBattleChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePalaceLobby_EventScript_ExplainDoublesChallenge::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainDoubleBattleChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified, MSGBOX_DEFAULT
BattleFrontier_BattlePalaceLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForSingleBattle::
	msgbox BattleFrontier_BattlePalaceLobby_Text_WelcomeForSingleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForDoubleBattle::
	msgbox BattleFrontier_BattlePalaceLobby_Text_WelcomeForDoubleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceLobby_EventScript_AskTakeSingleBattleChallenge::
	message BattleFrontier_BattlePalaceLobby_Text_TakeSingleBattleChallenge
	return

BattleFrontier_BattlePalaceLobby_EventScript_AskTakeDoubleBattleChallenge::
	message BattleFrontier_BattlePalaceLobby_Text_TakeDoubleBattleChallenge
	return

BattleFrontier_BattlePalaceLobby_EventScript_WalkToDoor::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_TalkedToSinglesAttendant
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_TalkedToDoublesAttendant
	applymovement VAR_LAST_TALKED, BattleFrontier_BattlePalaceLobby_Movement_WalkToDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePalaceLobby_Movement_WalkToDoor
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_OpenSinglesHallDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_OpenDoublesHallDoor
	waitdooranim
	applymovement VAR_LAST_TALKED, BattleFrontier_BattlePalaceLobby_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePalaceLobby_Movement_PlayerEnterDoor
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_CloseSinglesHallDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_CloseDoublesHallDoor
	waitdooranim
	return

BattleFrontier_BattlePalaceLobby_EventScript_TalkedToSinglesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_ATTENDANT_SINGLES
	return

BattleFrontier_BattlePalaceLobby_EventScript_TalkedToDoublesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_ATTENDANT_DOUBLES
	return

BattleFrontier_BattlePalaceLobby_EventScript_OpenSinglesHallDoor::
	opendoor 5, 4
	return

BattleFrontier_BattlePalaceLobby_EventScript_OpenDoublesHallDoor::
	opendoor 19, 4
	return

BattleFrontier_BattlePalaceLobby_EventScript_CloseSinglesHallDoor::
	closedoor 5, 4
	return

BattleFrontier_BattlePalaceLobby_EventScript_CloseDoublesHallDoor::
	closedoor 19, 4
	return

BattleFrontier_BattlePalaceLobby_Movement_WalkToDoor:
	walk_up
	step_end

BattleFrontier_BattlePalaceLobby_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePalaceLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePalaceLobby_EventScript_ShowSinglesResults::
	lockall
	frontier_results FRONTIER_FACILITY_PALACE, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_ShowDoublesResults::
	lockall
	frontier_results FRONTIER_FACILITY_PALACE, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_BlackBelt::
	msgbox BattleFrontier_BattlePalaceLobby_Text_LadyCanTellWhatMonsThink, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_Man::
	msgbox BattleFrontier_BattlePalaceLobby_Text_NatureAndMovesKeyHere, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_Beauty::
	msgbox BattleFrontier_BattlePalaceLobby_Text_MonDocileButTransforms, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_Maniac::
	msgbox BattleFrontier_BattlePalaceLobby_Text_WhatNatureFavorsChippingAway, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattlePalaceLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattlePalaceLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 16, 0, MULTI_BATTLE_PALACE_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePalaceLobby_EventScript_RulesBasics
	case 1, BattleFrontier_BattlePalaceLobby_EventScript_RulesNature
	case 2, BattleFrontier_BattlePalaceLobby_EventScript_RulesMoves
	case 3, BattleFrontier_BattlePalaceLobby_EventScript_RulesUnderpowered
	case 4, BattleFrontier_BattlePalaceLobby_EventScript_RulesWhenInDanger
	case 5, BattleFrontier_BattlePalaceLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_ExitRules
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesBasics::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesBasics, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesNature::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesNature, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesMoves::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesMoves, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesUnderpowered::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesUnderpowered, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesWhenInDanger::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesWhenInDanger, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattlePalaceLobby_Text_WelcomeForSingleBattle:
	.string "Εκεί που οι καρδιές των TRAINERS\n"
	.string "δοκιμάζονται σκληρά.\p"
	.string "Σε καλωσορίζω στο BATTLE PALACE.\p"
	.string "Αποδέχομαι challenges για τα\n"
	.string "SINGLE BATTLE HALLS.$"

BattleFrontier_BattlePalaceLobby_Text_TakeSingleBattleChallenge:
	.string "Επιθυμείς να πάρεις μέρος στο\n"
	.string "SINGLE BATTLE HALL challenge;$"

BattleFrontier_BattlePalaceLobby_Text_ExplainSingleBattleChallenge:
	.string "Στο BATTLE PALACE, υπάρχουν πολλές\n"
	.string "αίθουσες για SINGLE BATTLES\l"
	.string "που ονομάζονται SINGLE BATTLE HALLS.\p"
	.string "Tα SINGLE BATTLES διεξάγονται με\n"
	.string "τον συνήθη τρόπο, με έναν μόνο κρίσιμο\l"
	.string "κανόνα που πρέπει να τηρηθεί.\p"
	.string "Οι TRAINERS μπορούν μόνο να βάζουν\n"
	.string "και να βγάζουν τα POKéMON τους.\p"
	.string "Κατά τα άλλα, απαγορεύεται στους\n"
	.string "TRAINERS να δίνουν εντολές.\p"
	.string "Τα POKéMON συμπεριφέρονται ανάλογα με\n"
	.string "τη nature τους και μάχονται μόνα τους.\p"
	.string "Πρέπει να εμπιστευτείς τα POKéMON\n"
	.string "σου και να τα παρακολουθείς.\p"
	.string "Αν πετύχεις την τιμή να νικήσεις\n"
	.string "επτά TRAINERS στη σειρά,\l"
	.string "θα σου δώσουμε Battle Points.\p"
	.string "Αν θέλεις να διακόψεις το\n"
	.string "challenge, τότε πρέπει να κάνεις save.\p"
	.string "Αν δεν κάνεις save πριν διακόψεις,\n"
	.string "φυσικά και θα αποβληθείς από αυτό.$"

BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified:
	.string "Όταν θωρακίσεις την καρδιά\n"
	.string "και τα POKéMON σου, πρέπει να γυρίσεις.$"

BattleFrontier_BattlePalaceLobby_Text_WhichChallenge:
	.string "Υπάρχουν δύο BATTLE HALLS,\n"
	.string "το Level 50 και το Open Level.\l"
	.string "Ποιο θα επιλέξεις για το challenge σου;$"

BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLv50:
	.string "Αχ…\p"
	.string "Δεν έχεις τα τρία POKéMON\n"
	.string "που απαιτούνται για το challenge.\p"
	.string "Για να μπεις, πρέπει να παρέχεις τρία\n"
	.string "διαφορετικά είδη POKéMON.\p"
	.string "Αυτά τα POKéMON πρέπει όλα να είναι στο\n"
	.string "Level 50 ή χαμηλότερα.\p"
	.string "Επίσης, δεν πρέπει να κρατάνε\n"
	.string "το ίδιο είδος αντικειμένων.\p"
	.string "Τα EGGS{STR_VAR_1} δεν επιτρέπονται.\p"
	.string "Έλα πάλι όταν έχεις κάνει\n"
	.string "όλες τις προετοιμασίες σου.$"

BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLvOpen:
	.string "Αχ…\p"
	.string "Δεν έχεις τα τρία POKéMON\n"
	.string "που απαιτούνται για το challenge.\p"
	.string "Για να μπεις, πρέπει να παρέχεις τρία\n"
	.string "διαφορετικά είδη POKéMON.\p"
	.string "Επίσης, δεν πρέπει να κρατάνε\n"
	.string "το ίδιο είδος αντικειμένων.\p"
	.string "Τα EGGS{STR_VAR_1} δεν επιτρέπονται.\p"
	.string "Έλα πάλι όταν έχεις κάνει\n"
	.string "όλες τις προετοιμασίες σου.$"

BattleFrontier_BattlePalaceLobby_Text_NowSelectThreeMons:
	.string "Ωραία. Τώρα, πρέπει να επιλέξεις τα\n"
	.string "τρία σου POKéMON.$"

BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge2:
	.string "Πρέπει να κάνω save πριν σου δείξω το\n"
	.string "BATTLE HALL. Είναι εντάξει αυτό;$"

BattleFrontier_BattlePalaceLobby_Text_FollowMe:
	.string "Ωραία.\n"
	.string "Τώρα άκολούθησέ με.$"

BattleFrontier_BattlePalaceLobby_Text_ResultsWillBeRecorded:
	.string "Νιώθω προνόμιο που είδα\n"
	.string "τα κατορθώματα των POKéMON σου.\p"
	.string "Τα αποτελέσματα θα καταγραφούν.\n"
	.string "Πρέπει να σου ζητήσω να περιμένεις λίγο.$"

BattleFrontier_BattlePalaceLobby_Text_FirmTrueBondsFor7WinStreak:
	.string "Το να πετύχεις σερί 7 νικών…\p"
	.string "Οι δεσμοί που δένουν την καρδιά σου με\n"
	.string "τα POKéMON σου φαίνονται αληθινοί.$"

BattleFrontier_BattlePalaceLobby_Text_FeatWillBeRecorded:
	.string "Ο άθλος σου θα καταγραφεί.\n"
	.string "Πρέπει να σου ζητήσω να περιμένεις λίγο.$"

@ Unused
BattleFrontier_BattlePalaceLobby_Text_BattlePointsFor7WinStreak:
	.string "Για τον άθλο του σερί 7 νικών σου,\n"
	.string "σου προσφέρουμε αυτούς τους πόντους.$"

BattleFrontier_BattlePalaceLobby_Text_NoSpaceForPrize:
	.string "Φαίνεται ότι δεν έχεις χώρο για\n"
	.string "το βραβείο μας.\p"
	.string "Θα πρέπει να επιστρέψεις όταν έχεις\n"
	.string "τακτοποιήσει το BAG σου.$"

BattleFrontier_BattlePalaceLobby_Text_WeHaveBeenWaiting:
	.string "Σε περιμέναμε…$"

BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge:
	.string "Πρέπει να κάνω save πριν σου δείξω το\n"
	.string "BATTLE HALL. Είναι εντάξει αυτό;$"

BattleFrontier_BattlePalaceLobby_Text_FailedToSaveBeforeEndingChallenge:
	.string "Αχ…\p"
	.string "Δεν έκανες save την προηγούμενη\n"
	.string "φορά πριν κλείσεις το παιχνίδι.\p"
	.string "Ως αποτέλεσμα, έχεις αποβληθεί από\n"
	.string "το τρέχον challenge σου. Πολύ κρίμα.$"

@ Unused
BattleFrontier_BattlePalaceLobby_Text_ReceivedPrize:
	.string "Το άτομο {PLAYER} έλαβε το βραβείο\n"
	.string "{STR_VAR_1}.$"

BattleFrontier_BattlePalaceLobby_Text_LadyCanTellWhatMonsThink:
	.string "Για ένα δυνατό άτομο σαν κι εμένα,\n"
	.string "τα δυνατά POKéMON είναι τα καλύτερα.\p"
	.string "Η επίθεση είναι η καλύτερη άμυνα!\n"
	.string "Μια ανελέητη επίθεση είναι το βέλτιστο!\p"
	.string "Αλλά δεν ήθελα να μιλήσω\n"
	.string "για αυτό.\p"
	.string "Πού και πού περνάει από εδώ μια\n"
	.string "πολύ χαριτωμένη κοπέλα.\p"
	.string "Λέει ότι μπορεί να καταλάβει τι\n"
	.string "σκέφτονται τα POKéMON.\p"
	.string "Δεν ξέρω για αυτό το κομμάτι,\n"
	.string "αλλά είναι πολύ χαριτωμένη.\p"
	.string "Ε;\n"
	.string "Γιατί με κοιτάς έτσι;$"

BattleFrontier_BattlePalaceLobby_Text_NatureAndMovesKeyHere:
	.string "Χμμ…\p"
	.string "Φαίνεται ότι η nature των POKéMON\n"
	.string "και οι κινήσεις που έχουν διδαχθεί\l"
	.string "αποτελούν το κλειδί στη μάχη εδώ.\p"
	.string "Πιο συγκεκριμένα, πόσο καλά\n"
	.string "ταιριάζουν οι κινήσεις με την nature\l"
	.string "του POKéMON.\p"
	.string "Αν το POKéMON σου έχει πρόβλημα και δεν\n"
	.string "μπορεί να αποδώσει στα μέγιστα,\l"
	.string "μπορεί να χρειαστεί να εξετάσεις αν οι\l"
	.string "κινήσεις του ταιριάζουν με τη nature του.$"

BattleFrontier_BattlePalaceLobby_Text_MonDocileButTransforms:
	.string "Το POKéMON μου είναι πολύ υπάκουο.\p"
	.string "Αλλά όταν είναι σε BATTLE HALL,\n"
	.string "μερικές φορές φαίνεται να\l"
	.string "μεταμορφώνεται σε κάτι κακό!\p"
	.string "Γίνεται απόλυτα τρομακτικό.\n"
	.string "Είναι κάπως σοκαριστικό.$"

BattleFrontier_BattlePalaceLobby_Text_WhatNatureFavorsChippingAway:
	.string "Αναρωτιέμαι τι nature θα είχε ένα\n"
	.string "POKéMON αν του άρεσε να αποδυναμώνει\l"
	.string "τους αντιπάλους του σιγά σιγά.\p"
	.string "Θα εντυπωσιαζόμουν, αν ήταν η LAX.\p"
	.string "Αλλά, μπα, δεν μπορεί να είναι αυτό.$"

BattleFrontier_BattlePalaceLobby_Text_WelcomeForDoubleBattle:
	.string "Εκεί που οι καρδιές των TRAINERS\n"
	.string "δοκιμάζονται σκληρά.\p"
	.string "Σε καλωσορίζω στο BATTLE PALACE.\p"
	.string "Αποδέχομαι challenges για τα\n"
	.string "DOUBLE BATTLE HALLS.$"

BattleFrontier_BattlePalaceLobby_Text_TakeDoubleBattleChallenge:
	.string "Επιθυμείς να πάρεις μέρος στο\n"
	.string "DOUBLE BATTLE HALL challenge;$"

BattleFrontier_BattlePalaceLobby_Text_ExplainDoubleBattleChallenge:
	.string "Στο BATTLE PALACE, υπάρχουν πολλές\n"
	.string "αίθουσες για DOUBLE BATTLES\l"
	.string "που ονομάζονται DOUBLE BATTLE HALLS.\p"
	.string "Tα DOUBLE BATTLES διεξάγονται με\n"
	.string "τον συνήθη τρόπο, με έναν μόνο κρίσιμο\l"
	.string "κανόνα που πρέπει να τηρηθεί.\p"
	.string "Οι TRAINERS μπορούν μόνο να βάζουν\n"
	.string "και να βγάζουν τα POKéMON τους.\p"
	.string "Κατά τα άλλα, απαγορεύεται στους\n"
	.string "TRAINERS να δίνουν εντολές.\p"
	.string "Τα POKéMON συμπεριφέρονται ανάλογα με\n"
	.string "τη nature τους και μάχονται μόνα τους.\p"
	.string "Πρέπει να εμπιστευτείς τα POKéMON\n"
	.string "σου και να τα παρακολουθείς.\p"
	.string "Αν πετύχεις την τιμή να νικήσεις\n"
	.string "επτά TRAINERS στη σειρά,\l"
	.string "θα σου δώσουμε Battle Points.\p"
	.string "Αν θέλεις να διακόψεις το\n"
	.string "challenge, τότε πρέπει να κάνεις save.\p"
	.string "Αν δεν κάνεις save πριν διακόψεις,\n"
	.string "φυσικά και θα αποβληθείς από αυτό.$"

BattleFrontier_BattlePalaceLobby_Text_ToDefeatMavenAnd7Trainers:
	.string "Το να νικήσεις τον PALACE MAVEN\n"
	.string "και επτά TRAINERS στη σειρά…$"

BattleFrontier_BattlePalaceLobby_Text_PresentYouWithBattlePoints:
	.string "Προς τιμήν του δεσμού που έχεις με\n"
	.string "τα POKéMON σου, σου δίνουμε\l"
	.string "αυτούς τους πόντους Battle Point.$"

BattleFrontier_BattlePalaceLobby_Text_LikeToRecordMatch:
	.string "Θα ήθελες να καταγράψεις την τελευταία\n"
	.string "σου μάχη στο BATTLE PALACE στο\l"
	.string "FRONTIER PASS σου;$"

BattleFrontier_BattlePalaceLobby_Text_RulesAreListed:
	.string "Έχει τους κανόνες του BATTLE HALL.$"

BattleFrontier_BattlePalaceLobby_Text_ReadWhichHeading:
	.string "Ποια επικεφαλίδα θες να διαβάσεις;$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesBasics:
	.string "Εδώ, τα POKéMON πρέπει να σκεφτούν\n"
	.string "και να πολεμήσουν μόνα τους.\p"
	.string "Σε αντίθεση με τη φύση, τα POKéMON που\n"
	.string "ζουν με ανθρώπους συμπεριφέρονται\l"
	.string "διαφορετικά ανάλογα με τη nature τους.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesNature:
	.string "Ανάλογα με τη nature, ένα POKéMON\n"
	.string "ίσως προτιμάει να επιτίθεται συνεχώς.\p"
	.string "Κάποιο άλλο ίσως προτιμάει να\n"
	.string "προστατεύεται από μια επίθεση.\p"
	.string "Άλλα μπορεί να απολαμβάνουν να\n"
	.string "μπερδεύουν τους αντιπάλους τους.\p"
	.string "Λόγω της nature, ένα POKéMON θα έχει\n"
	.string "τις αγαπημένες του κινήσεις τις οποίες\l"
	.string "μπορεί να χρησιμοποιεί καλά.\p"
	.string "Μπορεί επίσης να αντιπαθεί κινήσεις με\n"
	.string "τις οποίες δυσκολεύεται.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesMoves:
	.string "Υπάρχουν επιθετικές κινήσεις που\n"
	.string "προκαλούν άμεση ζημιά στον εχθρό.\p"
	.string "Υπάρχουν αμυντικές κινήσεις που\n"
	.string "χρησιμοποιούνται για την αντιμετώπιση\l"
	.string "εχθρικών επιθέσεων, για heal κλπ.\p"
	.string "Υπάρχουν και άλλες περίεργες\n"
	.string "κινήσεις που αποδυναμώνουν τους\l"
	.string "εχθρούς με προβλήματα όπως\l"
	.string "δηλητηρίαση και παράλυση.\p"
	.string "Τα POKéMON θα σκεφτούν να \n"
	.string "χρησιμοποιήσουν κινήσεις από αυτές \l"
	.string "τις τρεις κατηγορίες.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesUnderpowered:
	.string "Όταν ένα POKéMON δεν παίρνει εντολές,\n"
	.string "ίσως να μην μπορεί να χρησιμοποιήσει\l"
	.string "αποτελεσματικά κάποιες κινήσεις.\p"
	.string "Ένα POKéMON δεν είναι καλό στη\n"
	.string "χρήση κινήσεων που αντιπαθεί.\p"
	.string "Αν ένα POKéMON ξέρει μόνο κινήσεις που\n"
	.string "δεν ταιριάζουν στη nature του, συχνά\l"
	.string "δεν θα μπορεί να αποδώσει στα μέγιστα.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesWhenInDanger:
	.string "Ανάλογα με τη nature, το POKéMON μπορεί\n"
	.string "να κάνει κινήσεις που δεν ταιριάζουν με\l"
	.string "τη nature του όταν είναι σε δύσκολη θέση.\p"
	.string "Αν ένα POKéMON αρχίσει να\n"
	.string "συμπεριφέρεται περίεργα, πρόσεξέ το.$"

