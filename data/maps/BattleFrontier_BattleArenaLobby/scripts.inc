.set LOCALID_ATTENDANT, 1

BattleFrontier_BattleArenaLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleArenaLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleArenaLobby_OnWarp
	.byte 0

BattleFrontier_BattleArenaLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleArenaLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleArenaLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleArenaLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown, MSGBOX_DEFAULT
	closemessage
	arena_set ARENA_DATA_WIN_STREAK, 0
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints

BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon::
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleArenaLobby_Text_RecordAchievement
	waitmessage
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave
	waitmessage
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	special HealPlayerParty
	arena_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge
	message BattleFrontier_BattleArenaLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge
	case 0, BattleFrontier_BattleArenaLobby_EventScript_RecordMatch
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge

BattleFrontier_BattleArenaLobby_EventScript_RecordMatch::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge::
	return

BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame
	waitmessage
	arena_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge

BattleFrontier_BattleArenaLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_ARENA
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattleArenaLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleArenaLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_OkayToSave, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	arena_init
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleArenaLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattleArenaLobby_Text_GuideYouToArena, MSGBOX_DEFAULT
	closemessage
	frontier_get FRONTIER_DATA_LVL_MODE
	call_if_eq VAR_RESULT, FRONTIER_LVL_50, BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50
	call_if_eq VAR_RESULT, FRONTIER_LVL_OPEN, BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen
	warp MAP_BATTLE_FRONTIER_BATTLE_ARENA_CORRIDOR, 9, 13
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50::
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor
	waitmovement 0
	opendoor 2, 2
	waitdooranim
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor:
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

BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen::
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor
	waitmovement 0
	opendoor 11, 2
	waitdooranim
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 11, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

BattleFrontier_BattleArenaLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_ARENA
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_Youngster::
	msgbox BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Man::
	msgbox BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Camper::
	msgbox BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Woman::
	msgbox BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 2, MULTI_BATTLE_ARENA_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_BattleRules
	case 1, BattleFrontier_BattleArenaLobby_EventScript_MindRules
	case 2, BattleFrontier_BattleArenaLobby_EventScript_SkillRules
	case 3, BattleFrontier_BattleArenaLobby_EventScript_BodyRules
	case 4, BattleFrontier_BattleArenaLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_ExitRules
	end

BattleFrontier_BattleArenaLobby_EventScript_BattleRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_MindRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainMindRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_SkillRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_BodyRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena:
	.string "Εκεί που το μαχητικό πνεύμα των\n"
	.string "TRAINERS δοκιμάζεται!\p"
	.string "Σε καλωσορίζω στην BATTLE ARENA!\p"
	.string "Είμαι ο οδηγός σου στο Set KO Tourney!$"

BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge:
	.string "Τώρα, επιθυμείς να πάρεις μέρος στην\n"
	.string "πρόκληση της BATTLE ARENA;$"

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge:
	.string "Περιμένουμε την πρόκλησή σου σε μία\n"
	.string "άλλη ευκαιρία!$"

BattleFrontier_BattleArenaLobby_Text_ExplainChallenge:
	.string "Στην BATTLE ARENA, αναλαμβάνουμε\n"
	.string "το Set KO Tourney.\p"
	.string "Όλοι οι συμμετέχοντες μπαίνουν με\n"
	.string "μία ομάδα τριών POKéMON.\p"
	.string "Τα τρία POKéMON πρέπει να βρίσκονται\n"
	.string "στη σειρά που πρόκειται να αγωνιστούν.\p"
	.string "Κατά τη μάχη, τα POKéMON εμφανίζονται\n"
	.string "ένα τη φορά με την αρχική σας σειρά.\p"
	.string "Μόλις ένα POKéMON μπει στη μάχη, πρέπει\n"
	.string "να μείνει μέχρι να κριθεί ο αγώνας.\p"
	.string "Αν ένας αγώνας μείνει χωρίς νικητή σε\n"
	.string "τρεις γύρους, πάει σε judging.\p"
	.string "Αν θες να διακόψεις την πρόκλησή σου,\n"
	.string "παρακαλώ κάνε save το παιχνίδι.\p"
	.string "Αν δεν κάνεις save, δεν θα μπορέσεις\n"
	.string "να συνεχίσεις με την πρόκλησή σου.\p"
	.string "Αν καταφέρεις να νικήσεις επτά TRAINERS\n"
	.string "στη σειρά, θα σε επιβραβεύσουμε με\l"
	.string "μερικά Battle Points.$"

BattleFrontier_BattleArenaLobby_Text_OkayToSave:
	.string "Πριν σε πάω στην BATTLE ARENA,\n"
	.string "πρέπει να κάνεις save. Είναι εντάξει;$"

BattleFrontier_BattleArenaLobby_Text_WhichLevelMode:
	.string "Η BATTLE ARENA προσφέρει δύο επίπεδα\n"
	.string "πρόκλησης, Level 50 και Open Level.\l"
	.string "Ποια είναι η επιλογή σου;$"

BattleFrontier_BattleArenaLobby_Text_SelectThreeMons:
	.string "Πολύ καλά, τώρα επίλεξε τα τρία\n"
	.string "POKéMON σου, παρακαλώ.$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen:
	.string "Αγαπητέ μου διεκδικητή!\p"
	.string "Δεν έχεις τα τρία POKéMON\n"
	.string "που απαιτούνται για να μπεις.\p"
	.string "Για να μπεις, πρέπει να φέρεις τρία\n"
	.string "διαφορετικά είδη POKéMON.\p"
	.string "Επίσης, δεν πρέπει να κρατάνε το ίδιο\n"
	.string "είδος items.\p"
	.string "Τα EGGS{STR_VAR_1} δεν επιτρέπονται.\p"
	.string "Όταν κάνεις τις προετοιμασίες σου,\n"
	.string "σε παρακαλώ επέστρεψε ξανά.$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50:
	.string "Αγαπητέ μου διεκδικητή!\p"
	.string "Δεν έχεις τα τρία POKéMON\n"
	.string "που απαιτούνται για να μπεις.\p"
	.string "Για να μπεις, πρέπει να φέρεις τρία\n"
	.string "διαφορετικά είδη POKéMON.\p"
	.string "Τα τρία διαφορετικά POKéMON πρέπει\n"
	.string "να είναι όλα Level 50 ή λιγότερο.\p"
	.string "Επίσης, δεν πρέπει να κρατάνε το ίδιο\n"
	.string "είδος items.\p"
	.string "Τα EGGS{STR_VAR_1} δεν επιτρέπονται.\p"
	.string "Όταν κάνεις τις προετοιμασίες σου,\n"
	.string "σε παρακαλώ επέστρεψε ξανά.$"

BattleFrontier_BattleArenaLobby_Text_GuideYouToArena:
	.string "Τώρα θα σε οδηγήσω στην\n"
	.string "BATTLE ARENA.$"

BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown:
	.string "Αγαπητέ μου διεκδικητή!\p"
	.string "Δεν έκανες save το παιχνίδι πριν\n"
	.string "να το κλείσεις, σωστά;\p"
	.string "Είναι κρίμα, αλλά αυτό είχε ως\n"
	.string "αποτέλεσμα τον αποκλεισμό σου\l"
	.string "από την πρόκλησή σου.\p"
	.string "Μπορείς, φυσικά, να ξεκινήσεις μια\n"
	.string "εντελώς νέα πρόκληση.$"

BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins:
	.string "Σε συγχαίρουμε για το εκπληκτικό\n"
	.string "σερί νικών έναντι επτά TRAINERS!$"

BattleFrontier_BattleArenaLobby_Text_RecordAchievement:
	.string "Το επίτευγμά σου θα καταγραφεί.\n"
	.string "Παρακαλώ περίμενε όσο κάνω save.$"

@ Unused
BattleFrontier_BattleArenaLobby_Text_PresentYouWithPrize:
	.string "Σε επέτειο του σερί 7 νικών σου,\n"
	.string "σου δίνουμε αυτό το βραβείο.$"

@ Unused
BattleFrontier_BattleArenaLobby_Text_ReceivedPrize:
	.string "Το άτομο {PLAYER} έλαβε το βραβείο\n"
	.string "{STR_VAR_1}.$"

@ Unused
BattleFrontier_BattleArenaLobby_Text_BagFullReturnForPrize:
	.string "Οχ;\n"
	.string "Η BAG σου φαίνεται να είναι γεμάτη.\p"
	.string "Σε προτρέπω να αδειάσεις λίγο χώρο\n"
	.string "και να επιστρέψεις για το βραβείο σου.$"

BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave:
	.string "Σε ευχαριστούμε πολύ για τη συμμετοχή!\p"
	.string "Παρακαλώ περίμενε όσο κάνω save.$"

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2:
	.string "Περιμένουμε την πρόκλησή σου σε μία\n"
	.string "άλλη ευκαιρία!$"

BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame:
	.string "Ανυπομονούσαμε για την άφιξή σου.\p"
	.string "Πριν σε πάω στην BATTLE ARENA, πρέπει\n"
	.string "να κάνω save το παιχνίδι.\l"
	.string "Παρακαλώ περίμενε.$"

BattleFrontier_BattleArenaLobby_Text_RecordLastMatch:
	.string "Να καταγράψω την τελευταία σου μάχη\n"
	.string "στην BATTLE ARENA στο FRONTIER PASS;$"

BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack:
	.string "Έχασα λόγω απόφασης του REFEREE…\p"
	.string "Δεν νομίζω ότι ήταν καλή ιδέα να\n"
	.string "χρησιμοποιώ μόνο αμυντικές επιθέσεις\l"
	.string "και να μην επιτίθεμαι καθόλου…$"

BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked:
	.string "Νίκησα στο judging!\p"
	.string "Το να χτυπάω με συνέπεια τα POKéMON του\n"
	.string "αντιπάλου, φαίνεται πως λειτούργησε!$"

BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw:
	.string "Ο αγώνας μας κηρύχθηκε ισοπαλία.\p"
	.string "Όταν ξεμείναμε από χρόνο, το POKéMON\n"
	.string "μου, αλλά και του αντιπάλου είχαν ίδιο\l"
	.string "ποσό HP περίπου.$"

BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant:
	.string "Στην BATTLE ARENA, η σειρά με την οποία\n"
	.string "βάζεις τα POKéMON είναι σημαντική.\p"
	.string "Αν, για παράδειγμα, το πρώτο POKéMON\n"
	.string "έχει κάποια μειονεκτήματα,\l"
	.string "προσπάθησε να κάνεις το δεύτερο\l"
	.string "POKéMON κάποιο με επιθέσεις που\l"
	.string "είναι αποτελεσματικές ενάντια στο πρώτο.\p"
	.string "Πιστεύω πως αυτός είναι ένας καλός\n"
	.string "τρόπος για να φτιάξεις δυνατή ομάδα.$"

BattleFrontier_BattleArenaLobby_Text_RulesAreListed:
	.string "Οι κανόνες του Set KO Tourney είναι\n"
	.string "γραμμένοι εδώ.$"

BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading:
	.string "Ποιον τίτλο θέλεις να διαβάσεις;$"

BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules:
	.string "Το Set KO Tourney έχει ειδικούς\n"
	.string "κανόνες, όχι σαν τις απλές μάχες.\p"
	.string "Αρχικά, η μάχη διαρκεί μόνο τρεις\n"
	.string "γύρους.\p"
	.string "Αν δεν υπάρξει αποτέλεσμα μετά από τρεις\n"
	.string "γύρους, πάει σε judging.\p"
	.string "Ο REFEREE θα διαλέξει τον νικητή\n"
	.string "ανάλογα με το πώς μάχονταν τα POKéMON.\p"
	.string "Επίσης, ένα POKéMON δεν μπορεί να βγει\n"
	.string "μέχρι να κριθεί το αποτέλεσμά της.$"

BattleFrontier_BattleArenaLobby_Text_ExplainMindRules:
	.string "Ο πρώτος παράγοντας κρίσης είναι ο\n"
	.string "“Mind” (Νους). Αυτό το κριτήριο βλέπει\l"
	.string "το πόσο επιθετικοί ήταν οι TRAINERS.\p"
	.string "Η κρίση βασίζεται στο πόσο συχνά\n"
	.string "οι TRAINERS χρησιμοποιούσαν επιθετικές\l"
	.string "κινήσεις.$"

BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules:
	.string "Ο δεύτερος παράγοντας είναι ο\n"
	.string "“Skill” (Δεξιότητα). Αυτό το κριτήριο\l"
	.string "βλέπει το πόσο καλά χρησιμοποιήθηκαν οι\l"
	.string "κινήσεις των POKéMON.\p"
	.string "Αν μια κίνηση πέτυχε,\n"
	.string "το Skill ανεβαίνει.\p"
	.string "Αν απέτυχε, το Skill\n"
	.string "πέφτει.\p"
	.string "Αν ήταν επίθεση, το Skill\n"
	.string "ανεβαίνει αν ήταν “super effective” και\l"
	.string "κατεβαίνει αν ήταν “not very\l"
	.string "effective”.\p"
	.string "Το Skill δεν ανεβαίνει αν χρησιμοποιείς\n"
	.string "κινήσεις όπως PROTECT και DETECT.\p"
	.string "Αν ο αντίπαλος χρησιμοποιούσε PROTECT ή\n"
	.string "DETECT, και το POKéMON σου έχανε,\l"
	.string "το δικό σου Skill rating δεν θα\l"
	.string "κατεβεί.$"

BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules:
	.string "Ο τελευταίος παράγοντας κρίσης είναι ο\n"
	.string "“Body” (Σώμα). Αυτό το κριτήριο\l"
	.string "κρίνεται από το HP που έμεινε στο τέλος\l"
	.string "της μάχης.\p"
	.string "Η κρίση ελέγχει το πόσο HP\n"
	.string "είχε ένα POKéMON στην αρχή της μάχης,\l"
	.string "σε σχέση με αυτό που έμεινε στο τέλος.$"

BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon:
	.string "Μία νίκη κλεμμένη από τον ARENA\n"
	.string "TYCOON, και ένα σερί επτά TRAINERS!\p"
	.string "Σε συγχαίρουμε για αυτήν την\n"
	.string "εντυπωσιακή συλλογή νικών!$"

BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints:
	.string "Αγαπητέ μου διεκδικητή, εις μνήμην του\n"
	.string "ακούραστου πνεύματός σου,\l"
	.string "παρακαλώ δέξου αυτά τα Battle Points.$"
