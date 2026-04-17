.set LOCALID_ATTENDANT_SINGLES, 1
.set LOCALID_ATTENDANT_DOUBLES, 6

BattleFrontier_BattleFactoryLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleFactoryLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleFactoryLobby_OnWarp
	.byte 0

BattleFrontier_BattleFactoryLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleFactoryLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	factory_setswapped
	factory_set FACTORY_DATA_WIN_STREAK_SWAPS, 0
	factory_set FACTORY_DATA_WIN_STREAK, 0
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins, MSGBOX_DEFAULT
	waitmessage
	goto BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints

BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead::
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead, MSGBOX_DEFAULT
	waitmessage
BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave
	waitmessage
	frontier_checkairshow
	special LoadPlayerParty
	factory_save 0
	playse SE_SAVE
	waitse
	goto BattleFrontier_BattleFactoryLobby_EventScript_AskRecordBattle
	end

BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattleFactoryLobby_Text_ReturnMonsSaveResults
	waitmessage
	frontier_checkairshow
	special LoadPlayerParty
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
	factory_save 0
	playse SE_SAVE
	waitse

BattleFrontier_BattleFactoryLobby_EventScript_AskRecordBattle::
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle
	message BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle

BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge::
	lockall
	message BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume
	waitmessage
	factory_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	setvar VAR_0x8006, 2
	goto BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge

BattleFrontier_BattleFactoryLobby_EventScript_SinglesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant
	end

BattleFrontier_BattleFactoryLobby_EventScript_DoublesAttendant::
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant
	end

BattleFrontier_BattleFactoryLobby_EventScript_Attendant::
	special SavePlayerParty
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle
BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	factory_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallengeSaveFailed
	setvar VAR_0x8006, 0
BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	msgbox BattleFrontier_BattleFactoryLobby_Text_StepThisWay, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor
	waitmovement 0
	warp MAP_BATTLE_FRONTIER_BATTLE_FACTORY_PRE_BATTLE_ROOM, 8, 13
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_ATTENDANT_SINGLES
	return

BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_ATTENDANT_DOUBLES
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge
	goto BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge

BattleFrontier_BattleFactoryLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor:
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge
	return

BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_ShowSinglesResults::
	lockall
	frontier_results FRONTIER_FACILITY_FACTORY, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_ShowDoublesResults::
	lockall
	frontier_results FRONTIER_FACILITY_FACTORY, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_Woman::
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_Camper::
	msgbox BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_Picnicker::
	lock
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleFactoryLobby_EventScript_FatMan::
	msgbox BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattleFactoryLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 0, MULTI_BATTLE_FACTORY_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber
	case 3, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes
	case 4, BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv
	case 5, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle:
	.string "Εκεί που η ευφυΐα των TRAINERS\n"
	.string "δοκιμάζεται με τον καλύτερο τρόπο!\p"
	.string "Καλώς ήρθες στο BATTLE FACTORY!\p"
	.string "Είμαι ο οδηγός σου για το Battle Swap\n"
	.string "Single Tournament.$"

BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge:
	.string "Θα ήθελες να πάρεις μέρος στο Battle\n"
	.string "Swap Single challenge;$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge:
	.string "Το Battle Swap Single Tournament\n"
	.string "είναι ένας SINGLE BATTLE διαγωνισμός με\l"
	.string "χρήση μόνο ενοικιαζόμενων POKéMON.\p"
	.string "Αρχικά, θα δανειστείς τρία\n"
	.string "POKéMON ειδικά για αυτό το event.\p"
	.string "Με τα ενοικιαζόμενα αυτά POKéMON,\n"
	.string "πρέπει να συμμετέχεις σε SINGLE BATTLE.\p"
	.string "Αν νικήσεις, σου επιτρέπεται να\n"
	.string "ανταλλάξεις ένα ενοικιαζόμενο POKéMON.\p"
	.string "Επανέλαβε αυτόν τον κύκλο συνεχώς--\n"
	.string "αν νικήσεις επτά φορές στη σειρά,\l"
	.string "θα κερδίσεις Battle Points.\p"
	.string "Αν θέλεις να διακόψεις το\n"
	.string "challenge σου, παρακαλώ κάνε save.\p"
	.string "Αν δεν κάνεις save, θα\n"
	.string "αποβληθείς από το τρέχον challenge.$"

BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit:
	.string "Ανυπομονούμε για την επόμενη επίσκεψη.$"

BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode:
	.string "Σε ποιο Level θες να διαγωνιστείς;\n"
	.string "Σε Level 50 ή Open Level;$"

BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge:
	.string "Πριν ξεκινήσεις το challenge,\n"
	.string "πρέπει να κάνω save. Είναι εντάξει;$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_WillHoldMonsForSafekeeping:
	.string "Ωραία, θα κρατήσω τα POKéMON σου για\n"
	.string "ασφάλεια όσο διαγωνίζεσαι.$"

BattleFrontier_BattleFactoryLobby_Text_StepThisWay:
	.string "Παρακαλώ πέρνα από εδώ.$"

BattleFrontier_BattleFactoryLobby_Text_ReturnMonsSaveResults:
	.string "Ευχαριστούμε για τη συμμετοχή!\p"
	.string "Θα επιστρέψω τα δικά σου POKéMON και θα\n"
	.string "πάρω τα ενοικιαζόμενα POKéMON μας.\p"
	.string "Πρέπει επίσης να κάνω save.\n"
	.string "Παρακαλώ περίμενε.$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_ReturnMons:
	.string "Θα επιστρέψω τα δικά σου POKéMON και θα\n"
	.string "πάρω τα ενοικιαζόμενα POKéMON μας.$"

BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins:
	.string "Συγχαρητήρια! Πέτυχες εφτά σερί νίκες\n"
	.string "στους αγώνες σου στο Battle Swap!$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_AwardBattlePointsForStreak:
	.string "Ως αναγνώριση των 7 σερί νικών,\n"
	.string "σου δίνουμε αυτούς τους πόντους.$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_MaxBattlePoints:
	.string "Ω, ω, ω!\p"
	.string "Οι Battle Points σου έφτασαν στο max.\p"
	.string "Παρακαλώ επέστρεψε μόνο αφού\n"
	.string "ξοδέψεις κάποιους Battle Points.$"

BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume:
	.string "Σε περιμέναμε πολλή ώρα!\p"
	.string "Πριν συνεχίσουμε το challenge,\n"
	.string "πρέπει να κάνω save.$"

BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting:
	.string "Λυπάμαι που το λέω, αλλά δεν έκανες\n"
	.string "save την τελευταία φορά που έπαιξες.\p"
	.string "Φυσικά, ως αποτέλεσμα, αποβάλλεσαι\n"
	.string "από το τωρινό σου challenge.$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_WellReturnMons:
	.string "Θα επιστρέψουμε τα POKéMON σου.$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_ReceivedPrizeItem:
	.string "Το άτομο {PLAYER} έλαβε το βραβείο\n"
	.string "{STR_VAR_1}.$"

BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle:
	.string "Εκεί που η ευφυΐα των TRAINERS\n"
	.string "δοκιμάζεται με τον καλύτερο τρόπο!\p"
	.string "Καλώς ήρθες στο BATTLE FACTORY!\p"
	.string "Είμαι ο οδηγός σου για το Battle Swap\n"
	.string "Double Tournament.$"

BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge:
	.string "Θα ήθελες να πάρεις μέρος στο Battle\n"
	.string "Swap Double challenge;$"

BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge:
	.string "Το Battle Swap Double Tournament\n"
	.string "είναι ένας DOUBLE BATTLE διαγωνισμός με\l"
	.string "χρήση μόνο ενοικιαζόμενων POKéMON.\p"
	.string "Αρχικά, θα δανειστείς τρία\n"
	.string "POKéMON ειδικά για αυτό το event.\p"
	.string "Με τα ενοικιαζόμενα αυτά POKéMON,\n"
	.string "πρέπει να συμμετέχεις σε DOUBLE BATTLE.\p"
	.string "Αν νικήσεις, σου επιτρέπεται να\n"
	.string "ανταλλάξεις ένα ενοικιαζόμενο POKéMON.\p"
	.string "Επανέλαβε αυτόν τον κύκλο συνεχώς--\n"
	.string "αν νικήσεις επτά φορές στη σειρά,\l"
	.string "θα κερδίσεις Battle Points.\p"
	.string "Αν θέλεις να διακόψεις το\n"
	.string "challenge σου, παρακαλώ κάνε save.\p"
	.string "Αν δεν κάνεις save, θα\n"
	.string "αποβληθείς από το τρέχον challenge.$"

BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead:
	.string "Συγχαρητήρια για την επιτυχία σου να\n"
	.string "νικήσεις τον FACTORY HEAD και να πάρεις\l"
	.string "εφτά νίκες στη σειρά!$"

BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints:
	.string "Ως αναγνώριση των πλούσιων γνώσεων\n"
	.string "και της οξυδέρκειάς σου,\l"
	.string "σου δίνουμε αυτούς τους πόντους.$"

BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave:
	.string "Ας ανταλλάξω τα δικά σου POKéMON\n"
	.string "με τα ενοικιαζόμενά μας POKéMON.\p"
	.string "Πρέπει να κάνω save τα δεδομένα\n"
	.string "της μάχης, οπότε παρακαλώ περίμενε.$"

BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch:
	.string "Θα ήθελες να καταγράψεις τον τελευταίο\n"
	.string "σου αγώνα στο BATTLE FACTORY\l"
	.string "στο FRONTIER PASS σου;$"

BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves:
	.string "Γεια!\n"
	.string "Εσύ, εκεί!\p"
	.string "Νομίζεις ότι τα events εδώ \n"
	.string "είναι εύκολα αφού δεν χρειάζεσαι \l"
	.string "μία γυμνασμένη ομάδα POKéMON;\p"
	.string "Μην είσαι και τόσο σίγουρος ότι θα\n"
	.string "νικήσεις τόσο εύκολα.\p"
	.string "Αν δεν έχεις βαθιά γνώση γύρω\n"
	.string "από τα POKéMON και τις κινήσεις τους,\l"
	.string "θα είναι δύσκολο να συνεχίσεις να νικάς.$"

BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon:
	.string "Αντάλλαξα για ένα αδύναμο POKéMON…\n"
	.string "Νόμιζα ότι θα ήταν καλό να το έχω…\p"
	.string "Μας έκαναν σκόνη…$"

BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons:
	.string "Τα πράγματα δεν πάνε καθόλου καλά\n"
	.string "για εμένα.\p"
	.string "Πρέπει να ελέγχεις τα POKéMON του\n"
	.string "αντιπάλου κατά τη διάρκεια της μάχης\l"
	.string "μήπως και είναι καθόλου καλά.$"

BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints:
	.string "Ξέρεις πώς το προσωπικό εδώ σου δίνει\n"
	.string "στοιχεία για τον επόμενο αντίπαλό σου;\p"
	.string "Λοιπόν, εγώ, ως ενήλικας, δυσκολεύομαι\n"
	.string "να καταλάβω κάποια από αυτά.$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_RentalMonsAreVaried:
	.string "Ξέρεις, έχω δύναμη, αλλά βαριέμαι\n"
	.string "πολύ εύκολα, οπότε απλά συνέχισα\l"
	.string "τις μάχες και τις ανταλλαγές.\p"
	.string "Τέλος πάντων, όταν συνέχισα να μπαίνω\n"
	.string "στα Battle Swap, παρατήρησα ότι\l"
	.string "άλλαζαν τα ενοικιαζόμενα POKéMON.$"

BattleFrontier_BattleFactoryLobby_Text_RulesAreListed:
	.string "Έχει τους κανόνες του Battle Swap.$"

BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading:
	.string "Ποια επικεφαλίδα θες να διαβάσεις;$"

BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules:
	.string "Σε ένα event στο Battle Swap, μπορείς\n"
	.string "να χρησιμοποιήσεις μόνο τρία POKéMON.\p"
	.string "Είτε ενοικιάζεις είτε ανταλλάσσεις,\n"
	.string "η ομάδα σου δεν επιτρέπεται να έχει δύο\l"
	.string "ή παραπάνω ολόιδια POKéMON.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules:
	.string "Μπορείς να ανταλλάξεις POKéMON μόνο με\n"
	.string "τον TRAINER που μόλις νίκησες.\p"
	.string "Μπορείς να ανταλλάξεις μόνο για τα \n"
	.string "POKéMON που είχε ο ηττημένος TRAINER.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules:
	.string "Μετά από κάθε μάχη που κερδίζεις,\n"
	.string "μπορείς να ανταλλάξεις ένα από τα\l"
	.string "ηττημένα POKéMON του αντιπάλου.\p"
	.string "Δεν μπορείς να ανταλλάξεις POKéMON \n"
	.string "με τον έβδομο TRAINER στο event.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules:
	.string "Υπάρχουν δύο βασικά σημεία που πρέπει\n"
	.string "να προσέχεις στις ανταλλαγές POKéMON.\p"
	.string "Πρώτον, όταν ανταλλάσσεις δεν μπορείς\n"
	.string "να δεις τα stats του POKéMON που\l"
	.string "πρόκειται να λάβεις.\p"
	.string "Δεύτερον, τα POKéMON στην ομάδα σου\n"
	.string "μπαίνουν σε σειρά, ανάλογα με τη\l"
	.string "σειρά που τα ενοικίασες αρχικά.\p"
	.string "Αυτή η σειρά παραμένει αμετάβλητη\n"
	.string "ακόμα και όταν γίνονται ανταλλαγές.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules:
	.string "Στο Open Level, τα ενοικιαζόμενα POKéMON\n"
	.string "και τα POKéMON των αντίπαλων TRAINERS\l"
	.string "είναι όλα στο Level 100.$"

