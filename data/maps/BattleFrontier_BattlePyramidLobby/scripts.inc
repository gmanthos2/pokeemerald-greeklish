.set LOCALID_ATTENDANT, 1
.set LOCALID_HINT_GIVER, 2

BattleFrontier_BattlePyramidLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleDomeLobby_OnWarp
	.byte 0

@ Unused. Pyramid uses Dome's OnWarp (presumably by mistake). Their effects are identical
BattleFrontier_BattlePyramidLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth:
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePyramidLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving::
	lockall
	message BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	closemessage
	pyramid_set PYRAMID_DATA_WIN_STREAK, 0
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints

BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing::
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints::
	special DoBattlePyramidMonsHaveHeldItem
	call_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag
	clearflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
	frontier_checkairshow
	special LoadPlayerParty
	pyramid_clearhelditems
	special HealPlayerParty
	message BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept
	waitmessage
	playse SE_EXP_MAX
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait
	waitmessage
	pyramid_setprize
	pyramid_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	pyramid_clearhelditems
	special HealPlayerParty
	lockall
	message BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait
	waitmessage
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, FALSE
	pyramid_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge::
	goto BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge

BattleFrontier_BattlePyramidLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PYRAMID
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	pyramid_init
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	pyramid_seedfloor
	pyramid_settrainers
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_RESULT, 0
	special HealPlayerParty
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR, 1, 1
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattlePyramidLobby_EventScript_HintGiver::
	lockall
	applymovement LOCALID_HINT_GIVER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait, MSGBOX_DEFAULT
	call BattleFrontier_BattlePyramidLobby_EventScript_GiveHint
	msgbox BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot, MSGBOX_DEFAULT
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_GiveHint::
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLvOpen
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePyramidLobby_EventScript_NoHint
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_NoHint
	return

@ Shouldnt occur
BattleFrontier_BattlePyramidLobby_EventScript_NoHint::
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLv50::
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_50
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLv50Streak
	setvar VAR_RESULT, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLv50Streak::
	pyramid_get PYRAMID_DATA_WIN_STREAK_50
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLvOpen::
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_OPEN
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLvOpenStreak
	setvar VAR_RESULT, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLvOpenStreak::
	pyramid_get PYRAMID_DATA_WIN_STREAK_OPEN
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment::
	copyvar VAR_0x8004, VAR_RESULT
	special GetBattlePyramidHint
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_HintPoison
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_HintBurn
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate
	case 5, BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility
	case 6, BattleFrontier_BattlePyramidLobby_EventScript_HintIce
	case 7, BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion
	case 8, BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic
	case 9, BattleFrontier_BattlePyramidLobby_EventScript_HintRock
	case 10, BattleFrontier_BattlePyramidLobby_EventScript_HintFighting
	case 11, BattleFrontier_BattlePyramidLobby_EventScript_HintWeather
	case 12, BattleFrontier_BattlePyramidLobby_EventScript_HintBug
	case 13, BattleFrontier_BattlePyramidLobby_EventScript_HintDark
	case 14, BattleFrontier_BattlePyramidLobby_EventScript_HintWater
	case 15, BattleFrontier_BattlePyramidLobby_EventScript_HintGhost
	case 16, BattleFrontier_BattlePyramidLobby_EventScript_HintSteel
	case 17, BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon
	case 18, BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve
	case 19, BattleFrontier_BattlePyramidLobby_EventScript_HintNormal
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintParalysis, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPoison::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPoison, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintBurn::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBurn, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPPWaste, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintLevitate, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintIce::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintIce, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintExplosion, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPsychic, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintRock::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintRock, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintFighting::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFighting, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintWeather::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWeather, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintBug::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBug, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintDark::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintDark, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintWater::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWater, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintGhost::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintGhost, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintSteel::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintSteel, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintNormal::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintNormal, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_PYRAMID
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag::
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag

BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag::
	message BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel
	waitmovement 0
	return

BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_down
	step_end

BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside:
	walk_right
	face_left
	step_end

BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel:
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake, MSGBOX_DEFAULT
	setflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
	special TryStoreHeldItemsInPyramidBag
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag
	message BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag, MSGBOX_DEFAULT
	return

@ When exiting Battle Pyramid with a full pyramid bag and held items the player must select to keep/toss party held items and make room for any kept items by tossing from the pyramid bag
BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep::
	multichoice 17, 6, MULTI_FRONTIER_ITEM_CHOOSE, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems
	end

BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag::
	special ChooseItemsToTossFromPyramidBag
	waitstate
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty::
	special BattlePyramidChooseMonHeldItems
	waitstate
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems::
	special DoBattlePyramidMonsHaveHeldItem
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems
	return

BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems::
	msgbox BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem, MSGBOX_DEFAULT
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_Woman::
	msgbox BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning, MSGBOX_NPC
	end

BattleFrontier_BattlePyramidLobby_EventScript_FatMan::
	msgbox BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems, MSGBOX_NPC
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattlePyramidLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 15, 2, MULTI_BATTLE_PYRAMID_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_RulesBag
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid:
	.string "Εκεί που το θάρρος των TRAINERS\n"
	.string "δοκιμάζεται!\p"
	.string "Καλώς ήρθες στο BATTLE PYRAMID!\p"
	.string "Είμαι ο οδηγός σου για\n"
	.string "το Battle Quest.$"

BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge:
	.string "Έχεις το θάρρος να ξεκινήσεις το\n"
	.string "Battle Quest challenge σου;$"

BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge:
	.string "Περιμένουμε την πρόκλησή σου\n"
	.string "στο μέλλον!$"

BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid:
	.string "Το Battle Quest είναι ένα event μαχών\n"
	.string "στο οποίο πρέπει να εξερευνήσεις\l"
	.string "την PYRAMID για να φτάσεις στην κορυφή.\p"
	.string "Στην PYRAMID υπάρχουν εφτά όροφοι\n"
	.string "με λαβύρινθους, γεμάτοι όχι μόνο από\l"
	.string "έμπειρα TRAINER άτομα αλλά και POKéMON.\p"
	.string "Πρέπει να μπεις με 3 POKéMON, και\n"
	.string "κανένα να μην κρατάει κάποιο item.\p"
	.string "Κατά την άνοδο, θα σου δοθεί\n"
	.string "μια BATTLE BAG για τα items σου.\p"
	.string "Αν αποτύχεις στο challenge σου, όποιο\n"
	.string "item μπήκε στην BATTLE BAG εξαφανίζεται.\p"
	.string "Αν θες να διακόψεις το challenge σου,\n"
	.string "επίλεξε “REST” (ΞΕΚΟΥΡΑΣΗ)\l"
	.string "και κάνε save το παιχνίδι.\p"
	.string "Αν δεν κάνεις save πριν διακόψεις,\n"
	.string "τότε θα αποκλειστείς.$"

BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode:
	.string "Η PYRAMID προσφέρει δύο επίπεδα,\n"
	.string "το Level 50 και το Open Level.\l"
	.string "Σε ποιο θα μπεις;$"

BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons:
	.string "Πολύ καλά. Τώρα, επίλεξε 3 POKéMON\n"
	.string "που θες να σε συνοδεύσουν.$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen:
	.string "Ένα μικρό πρόβλημα!\p"
	.string "Φαίνεται να μην έχεις 3 POKéMON με τα\n"
	.string "απαραίτητα προσόντα για το challenge.\p"
	.string "Σε παρακαλώ, μην ξεχάσεις να πάρεις\n"
	.string "όλα τα items από τα POKéMON σου.\p"
	.string "Τα EGGS{STR_VAR_1} δεν επιτρέπονται.\p"
	.string "Όταν είσαι έτοιμο, έλα να μου μιλήσεις.$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50:
	.string "Ένα μικρό πρόβλημα!\p"
	.string "Φαίνεται να μην έχεις 3 POKéMON με τα\n"
	.string "απαραίτητα προσόντα για το challenge.\p"
	.string "Τα 3 POKéMON σου πρέπει να διαφέρουν\n"
	.string "και να είναι μέχρι το Level 50.\p"
	.string "Σε παρακαλώ, μην ξεχάσεις να πάρεις\n"
	.string "όλα τα items από τα POKéMON σου.\p"
	.string "Τα EGGS{STR_VAR_1} δεν επιτρέπονται.\p"
	.string "Όταν είσαι έτοιμο, έλα να μου μιλήσεις.$"

BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge:
	.string "Πριν μπεις στο BATTLE PYRAMID,\n"
	.string "το παιχνίδι πρέπει να γίνει save. OΚ;$"

BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid:
	.string "Πολύ καλά. Θα σε περάσω τώρα μέσα\n"
	.string "στο BATTLE PYRAMID.$"

BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping:
	.string "Θα κρατήσουμε το BAG σου για ασφάλεια,\n"
	.string "{PLAYER}, ενώ εσύ θα εξερευνάς.$"

BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag:
	.string "Σε αντάλλαγμα, πάρε αυτό το BATTLE\n"
	.string "BAG, αυτό που χρησιμοποίησες πριν.$"

BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag:
	.string "Σε αντάλλαγμα,\n"
	.string "πάρε αυτό το BATTLE BAG.$"

BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag:
	.string "Το {PLAYER} αντάλλαξε το BAG με το\n"
	.string "BATTLE BAG.$"

BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel:
	.string "Πατώντας αυτό το πάνελ στο πάτωμα,\n"
	.string "θα μεταφερθείς σε έναν ψηλότερο\l"
	.string "όροφο της PYRAMID.\p"
	.string "Ελπίζω για χάρη σου να πάει το\n"
	.string "quest σου με ασφάλεια!$"

BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag:
	.string "Ένα μεγάλο πρόβλημα, explorer!\p"
	.string "Δεν είχες κάνει save πριν τελειώσεις\n"
	.string "το challenge σου την τελευταία φορά.\p"
	.string "Οπότε, το challenge σου μόλις ακυρώθηκε,\n"
	.string "λυπάμαι που το λέω.\p"
	.string "Ορίστε το BAG που κρατούσαμε\n"
	.string "για σένα.\p"
	.string "Το {PLAYER} πήρε πίσω το BAG.$"

BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid:
	.string "Τέλεια που σε βλέπω πίσω!\p"
	.string "Έχεις κατακτήσει την PYRAMID!\n"
	.string "Τι υπέροχο!$"

BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake:
	.string "Αχ, ένα μικρό πρόβλημα.\p"
	.string "Τουλάχιστον ένα POKéMON κρατάει\n"
	.string "ένα item.\p"
	.string "Λυπάμαι, τα items που παίρνεις στην\n"
	.string "PYRAMID δεν μπορούν να βγουν έξω.$"

BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag:
	.string "Όλα τα items που κρατούν τα POKéMON σου\n"
	.string "θα μπουν στο BATTLE BAG, {PLAYER}.$"

BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep:
	.string "Το BATTLE BAG δεν χωράει όλα τα items\n"
	.string "σου, λυπάμαι που το λέω.\p"
	.string "Σε παρακαλώ, διάλεξε τα items που θα\n"
	.string "κρατήσεις σε BATTLE BAG & στα POKéMON.$"

BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem:
	.string "Τουλάχιστον ένα POKéMON κρατάει\n"
	.string "ακόμα ένα item.$"

BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep:
	.string "Σε παρακαλώ, διάλεξε τα items που θα\n"
	.string "κρατήσεις σε BATTLE BAG & στα POKéMON.$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ReturnedEverythingMonsHeld:
	.string "Το {PLAYER} επέστρεψε ό,τι κρατούσαν\n"
	.string "τα POKéMON.$"

BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept:
	.string "To BATTLE BAG που χρησιμοποίησες θα\n"
	.string "κρατηθεί για το επόμενο challenge σου.\p"
	.string "Το {PLAYER} έδωσε το BATTLE BAG\n"
	.string "για να πάρει πίσω το BAG.$"

BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait:
	.string "Πρέπει να καταγράψω τα αποτελέσματά σου.\n"
	.string "Παρακαλώ περίμενε.$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ForConqueringPyramidTakeThis:
	.string "Ως αναμνηστικό της κατάκτησης του\n"
	.string "BATTLE PYRAMID, πάρε αυτό.$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ReceivedPrizeItem:
	.string "Το {PLAYER} έλαβε το βραβείο\n"
	.string "{STR_VAR_1}.$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_BagIsFull:
	.string "…Αχ…\n"
	.string "Tο BAG σου φαίνεται να είναι γεμάτο.\p"
	.string "Παρακαλώ επίστρεψε αφού οργανώσεις\n"
	.string "το περιεχόμενο του BAG σου.$"

BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag:
	.string "Τι απογοητευτικό για εσένα…\p"
	.string "Ορίστε το BAG που κρατούσαμε\n"
	.string "για σένα.\p"
	.string "Το {PLAYER} πήρε πίσω το BAG.$"

BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge:
	.string "Περιμένουμε με ανυπομονησία το\n"
	.string "επόμενο challenge σου!$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_HereIsPrize:
	.string "Περιμέναμε την άφιξή σου!\p"
	.string "Ορίστε το βραβείο σου για την\n"
	.string "κατάκτηση της PYRAMID.$"

BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait:
	.string "Καλώς ήρθες…\p"
	.string "Θα χαρώ να σου πω τι ατυχίες\n"
	.string "σε περιμένουν στην PYRAMID…$"

BattleFrontier_BattlePyramidLobby_Text_Aah:
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "… … … … … …\n"
	.string "Ααα!$"

BattleFrontier_BattlePyramidLobby_Text_HintParalysis:
	.string "Βλέπω μια βροχή από σπίθες…\p"
	.string "…Και μέσα σε αυτή, βλέπω τα POKéMON σου\n"
	.string "να παλεύουν με το paralysis…$"

BattleFrontier_BattlePyramidLobby_Text_HintPoison:
	.string "Βλέπω δηλητήριο…\p"
	.string "…Και βλέπω τα POKéMON σου να υποφέρουν\n"
	.string "από τις επιδράσεις του poison…$"

BattleFrontier_BattlePyramidLobby_Text_HintBurn:
	.string "Βλέπω λαμπερές κόκκινες φλόγες…\p"
	.string "…Και βλέπω τα POKéMON σου να υποφέρουν\n"
	.string "από burns…$"

BattleFrontier_BattlePyramidLobby_Text_HintPPWaste:
	.string "Νιώθω την τεράστια πίεση ενός\n"
	.string "ανεκπλήρωτου θυμού…\p"
	.string "Είναι μια κατάρα…\p"
	.string "…Και βλέπω τα POKéMON σου να ξεμένουν\n"
	.string "από Power Points και να μην έχουν άλλη\l"
	.string "επιλογή από το να κάνουν STRUGGLE…$"

BattleFrontier_BattlePyramidLobby_Text_HintLevitate:
	.string "Βλέπω POKéMON να πετούν περήφανα…\p"
	.string "…Και βλέπω πως τα POKéMON σου θυμώνουν\n"
	.string "από άχρηστες GROUND-type κινήσεις…$"

BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility:
	.string "Νιώθω φοβερή ενέργεια να υψώνεται από\n"
	.string "το έδαφος…\p"
	.string "…Και βλέπω τα POKéMON σου ανίκανα να\n"
	.string "ξεφύγουν από αυτήν τη δύναμη…$"

BattleFrontier_BattlePyramidLobby_Text_HintIce:
	.string "Βλέπω ICE-type POKéMON…\p"
	.string "…Και βλέπω τα POKéMON σου να παλεύουν\n"
	.string "το πάγωμα που προκαλούν…$"

BattleFrontier_BattlePyramidLobby_Text_HintExplosion:
	.string "Βλέπω έναν καταιγισμό κινήσεων που\n"
	.string "θέτουν σε κίνδυνο τον χρήστη τους…\p"
	.string "…Και βλέπω τα POKéMON σου να πέφτουν\n"
	.string "από αυτές…$"

BattleFrontier_BattlePyramidLobby_Text_HintPsychic:
	.string "Βλέπω PSYCHIC-type POKéMON…\p"
	.string "…Και βλέπω τα POKéMON σου να υποφέρουν\n"
	.string "από PSYCHIC κινήσεις…$"

BattleFrontier_BattlePyramidLobby_Text_HintRock:
	.string "Βλέπω ROCK-type POKéMON…\p"
	.string "…Και βλέπω τα POKéMON σου να υποφέρουν\n"
	.string "από ROCK κινήσεις…$"

BattleFrontier_BattlePyramidLobby_Text_HintFighting:
	.string "Βλέπω FIGHTING-type POKéMON…\p"
	.string "…Και βλέπω τα POKéMON σου να δέχονται\n"
	.string "πολλά χτυπήματα από FIGHTING κινήσεις…$"

BattleFrontier_BattlePyramidLobby_Text_HintWeather:
	.string "RAIN DANCE… SUNNY DAY…\n"
	.string "SANDSTORM… HAIL…\p"
	.string "Βλέπω POKéMON που γίνονται\n"
	.string "δυνατότερα με τον καιρό…\p"
	.string "…Και βλέπω πως τα POKéMON σου τα\n"
	.string "έχουν χαμένα από διάφορες κινήσεις…$"

BattleFrontier_BattlePyramidLobby_Text_HintBug:
	.string "Βλέπω BUG-type POKéMON…\p"
	.string "…Και βλέπω τα POKéMON σου να υποφέρουν\n"
	.string "από διάφορα είδη επιθέσεων…$"

BattleFrontier_BattlePyramidLobby_Text_HintDark:
	.string "Βλέπω DARK-type POKéMON…\p"
	.string "…Και βλέπω τα POKéMON σου να υποφέρουν\n"
	.string "από DARK-type κινήσεις…$"

BattleFrontier_BattlePyramidLobby_Text_HintWater:
	.string "Βλέπω WATER-type POKéMON…\p"
	.string "…Και βλέπω τα POKéMON σου να υποφέρουν\n"
	.string "από WATER-type κινήσεις…$"

BattleFrontier_BattlePyramidLobby_Text_HintGhost:
	.string "Βλέπω GHOST-type POKéMON…\p"
	.string "…Και βλέπω τα POKéMON σου να υποφέρουν\n"
	.string "από GHOST-type κινήσεις…$"

BattleFrontier_BattlePyramidLobby_Text_HintSteel:
	.string "Βλέπω STEEL-type POKéMON…\p"
	.string "…Και βλέπω τα POKéMON σου να υποφέρουν\n"
	.string "από εξαιρετικά δυνατές κινήσεις…$"

BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon:
	.string "Βλέπω POKéMON να πετούν…\p"
	.string "…Και βλέπω τα POKéMON σου να υποφέρουν\n"
	.string "από εξαιρετικά δυνατές κινήσεις…$"

BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve:
	.string "Βλέπω αυτά που εξέλιξε η δύναμη\n"
	.string "από κάποιες πέτρες…\p"
	.string "Νιώθω επίσης φωτιά, νερό,\n"
	.string "και ηλεκτρισμό…\p"
	.string "…Και βλέπω τα POKéMON σου να υποφέρουν\n"
	.string "από αυτές τις τρεις δυνάμεις…$"

BattleFrontier_BattlePyramidLobby_Text_HintNormal:
	.string "Βλέπω NORMAL-type POKéMON…\p"
	.string "…Και βλέπω τα POKéMON σου να υποφέρουν\n"
	.string "από εξαιρετικά δυνατές κινήσεις…$"

BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot:
	.string "Αν θα πιστέψεις τις προβλέψεις μου\n"
	.string "ή όχι, η επιλογή είναι δική σου…\p"
	.string "Το μέλλον αλλάζει ανά πάσα στιγμή…\n"
	.string "Σου εύχομαι ασφαλή πορεία…$"

BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning:
	.string "Το ήξερες;\p"
	.string "Αν τρέχεις γρήγορα, τα TRAINER άτομα\n"
	.string "θα σε δουν και θα έρθουν για μάχη.\p"
	.string "Οπότε, αν θες να αποφύγεις τα TRAINERS,\n"
	.string "μην πέσεις πάνω τους, αλλά πέρνα\l"
	.string "κρυφά, προσεκτικά και ήσυχα από δίπλα.$"

BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems:
	.string "Αααααααργκ!\p"
	.string "Είχα ένα σωρό items, αλλά τα έχασα\n"
	.string "όλα όταν έχασα στο challenge!\p"
	.string "Αααααααργκ!$"

BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing:
	.string "Καλώς ήρθες πίσω!\n"
	.string "Έκανες το ακατόρθωτο!\p"
	.string "Νίκησες τον PYRAMID KING\n"
	.string "και κατέκτησες το BATTLE PYRAMID!$"

BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints:
	.string "Explorer!\n"
	.string "Ως έπαινο για το θάρρος σου,\l"
	.string "σου δίνουμε αυτά τα Battle Point(s)!$"

BattleFrontier_BattlePyramidLobby_Text_RulesAreListed:
	.string "Αναγράφονται οι κανόνες του Quest.$"

BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading:
	.string "Ποια επικεφαλίδα θέλεις να διαβάσεις;$"

BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules:
	.string "Όταν κατακτιέται η PYRAMID, τα άγρια\n"
	.string "POKéMON που εμφανίζονται μέσα σε αυτήν\l"
	.string "αντικαθίστανται από διαφορετικά είδη.\p"
	.string "Εξερεύνησε, παρατήρησε και μάθε ποια\n"
	.string "άγρια POKéMON μπορεί να συναντήσεις.$"

BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules:
	.string "Μερικά TRAINER άτομα είναι κρυμμένα\n"
	.string "και σε περιμένουν μέσα στην PYRAMID.\p"
	.string "Σε κάθε όροφο, υπάρχουν έως και\n"
	.string "οκτώ TRAINERS.\p"
	.string "Όταν νικάς ένα TRAINER άτομο, θα\n"
	.string "παίρνεις ένα hint για την περιπέτεια!$"

BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules:
	.string "Οι λαβύρινθοι της PYRAMID αλλάζουν\n"
	.string "διαρρύθμιση κάθε φορά που μπαίνεις.\p"
	.string "Οι λαβύρινθοι έχουν κακό φωτισμό.\n"
	.string "Πρέπει να προχωράς με προσοχή.\p"
	.string "Το φως γίνεται πιο δυνατό όποτε νικάς\n"
	.string "ένα άγριο POKéMON ή ένα TRAINER άτομο.$"

BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules:
	.string "Το BATTLE BAG λειτουργεί ως το BAG\n"
	.string "σου, όσο βρίσκεσαι μέσα στην PYRAMID.\p"
	.string "Υπάρχουν δύο ξεχωριστά BATTLE BAGS--\n"
	.string "ένα για το Level 50 και ένα για τις\l"
	.string "Open Level περιπέτειες.\p"
	.string "Kάθε ένα χωράει μέχρι και 99 κομμάτια\n"
	.string "από δέκα είδη items.\p"
	.string "Τα περιεχόμενα του BATTLE BAG\n"
	.string "χάνονται αν αποτύχεις στο quest σου.$"

