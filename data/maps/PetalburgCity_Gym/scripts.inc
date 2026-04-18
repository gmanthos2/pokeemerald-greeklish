.set LOCALID_NORMAN, 1
.set LOCALID_WALLY, 10
.set LOCALID_WALLYS_DAD, 11

PetalburgCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PetalburgCity_Gym_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgCity_Gym_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_Gym_OnFrame
	.byte 0

PetalburgCity_Gym_OnLoad:
	goto_if_eq VAR_PETALBURG_GYM_STATE, 6, PetalburgCity_Gym_EventScript_OpenUnlockedDoors
	call_if_ge VAR_PETALBURG_GYM_STATE, 7, PetalburgCity_Gym_EventScript_UnlockAllDoors
	end

@ NOTE: Strength and OHKO rooms are misleading. Both are more accurately Critical-Hit
PetalburgCity_Gym_EventScript_OpenUnlockedDoors::
	setvar VAR_0x8005, 1
	call PetalburgCity_Gym_EventScript_OpenGymEntranceDoors
	call_if_defeated TRAINER_RANDALL, PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors
	call_if_defeated TRAINER_MARY, PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors
	call_if_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors
	call_if_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors
	call_if_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors
	call_if_defeated TRAINER_JODY, PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors
	call_if_defeated TRAINER_BERKE, PetalburgCity_Gym_EventScript_OpenOHKORoomDoors
	end

PetalburgCity_Gym_EventScript_UnlockAllDoors::
	setvar VAR_0x8005, 1
	call PetalburgCity_Gym_EventScript_OpenGymEntranceDoors
	call PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors
	call PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors
	call PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors
	call PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors
	call PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors
	call PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors
	call PetalburgCity_Gym_EventScript_OpenOHKORoomDoors
	return

PetalburgCity_Gym_OnTransition:
	call_if_eq VAR_PETALBURG_GYM_STATE, 1, PetalburgCity_Gym_EventScript_MoveWallyToEntrance
	call_if_lt VAR_PETALBURG_GYM_STATE, 6, PetalburgCity_Gym_EventScript_MoveNormanToEntrance
	call_if_set FLAG_SYS_GAME_CLEAR, PetalburgCity_Gym_EventScript_CheckNormanForRematch
	end

PetalburgCity_Gym_EventScript_MoveWallyToEntrance::
	setobjectxyperm LOCALID_WALLY, 5, 108
	return

PetalburgCity_Gym_EventScript_MoveNormanToEntrance::
	setobjectxyperm LOCALID_NORMAN, 4, 107
	return

PetalburgCity_Gym_EventScript_CheckNormanForRematch::
	setorcopyvar VAR_TRAINER_BATTLE_OPPONENT_A, TRAINER_NORMAN_1
	specialvar VAR_RESULT, IsTrainerReadyForRematch
	goto_if_eq VAR_RESULT, TRUE, PetalburgCity_Gym_EventScript_DontMoveNormanToFront
	goto_if_eq VAR_PETALBURG_GYM_STATE, 8, PetalburgCity_Gym_EventScript_DontMoveNormanToFront
	setobjectxyperm LOCALID_NORMAN, 4, 107
	return

PetalburgCity_Gym_EventScript_DontMoveNormanToFront::
	setvar VAR_PETALBURG_GYM_STATE, 8
	end

PetalburgCity_Gym_OnWarp:
	map_script_2 VAR_PETALBURG_GYM_STATE, 1, PetalburgCity_Gym_EventScript_TurnPlayerNorth
	.2byte 0

PetalburgCity_Gym_EventScript_TurnPlayerNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

PetalburgCity_Gym_OnFrame:
	map_script_2 VAR_PETALBURG_GYM_STATE, 1, PetalburgCity_Gym_EventScript_ReturnFromWallyTutorial
	.2byte 0

PetalburgCity_Gym_EventScript_ReturnFromWallyTutorial::
	lockall
	msgbox PetalburgCity_Gym_Text_DadSoDidItWorkOut, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_WallyThankYouBye, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyExitGym
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_WALLY
	setflag FLAG_HIDE_PETALBURG_CITY_WALLY
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgCity_Gym_Text_DadGoCollectBadges, MSGBOX_DEFAULT
	setvar VAR_PETALBURG_GYM_STATE, 2
	releaseall
	end

PetalburgCity_Gym_Movement_WallyExitGym:
	walk_down
	walk_down
	walk_down
	delay_16
	step_end

PetalburgCity_Gym_EventScript_Norman::
	lock
	faceplayer
	switch VAR_PETALBURG_GYM_STATE
	case 2, PetalburgCity_Gym_EventScript_NormanNoBadges
	case 3, PetalburgCity_Gym_EventScript_NormanOneBadge
	case 4, PetalburgCity_Gym_EventScript_NormanTwoBadges
	case 5, PetalburgCity_Gym_EventScript_NormanThreeBadges
	case 6, PetalburgCity_Gym_EventScript_NormanBattle
	case 7, PetalburgCity_Gym_EventScript_NormanPostBattle
	case 8, PetalburgCity_Gym_EventScript_NormanRematch
	msgbox PetalburgCity_Gym_Text_DadYoureHereWithYourPokemon, MSGBOX_DEFAULT
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, PetalburgCity_Gym_EventScript_BeginWallyTutorialSouth
	case DIR_NORTH, PetalburgCity_Gym_EventScript_BeginWallyTutorialNorth
	case DIR_WEST, PetalburgCity_Gym_EventScript_BeginWallyTutorialWest
	case DIR_EAST, PetalburgCity_Gym_EventScript_BeginWallyTutorialEast
	end

PetalburgCity_Gym_EventScript_BeginWallyTutorialSouth::
	setvar VAR_0x8008, 0
	goto PetalburgCity_Gym_EventScript_BeginWallyTutorial
	end

PetalburgCity_Gym_EventScript_BeginWallyTutorialNorth::
	setvar VAR_0x8008, 1
	goto PetalburgCity_Gym_EventScript_BeginWallyTutorial
	end

PetalburgCity_Gym_EventScript_BeginWallyTutorialWest::
	setvar VAR_0x8008, 2
	goto PetalburgCity_Gym_EventScript_BeginWallyTutorial
	end

PetalburgCity_Gym_EventScript_BeginWallyTutorialEast::
	setvar VAR_0x8008, 3
	goto PetalburgCity_Gym_EventScript_BeginWallyTutorial
	end

PetalburgCity_Gym_EventScript_BeginWallyTutorial::
	addobject LOCALID_WALLY
	playse SE_DOOR
	call_if_eq VAR_0x8008, 0, PetalburgCity_Gym_EventScript_WallyArriveSouth
	call_if_eq VAR_0x8008, 1, PetalburgCity_Gym_EventScript_WallyArriveNorth
	call_if_eq VAR_0x8008, 2, PetalburgCity_Gym_EventScript_WallyArriveWestEast
	call_if_eq VAR_0x8008, 3, PetalburgCity_Gym_EventScript_WallyArriveWestEast
	msgbox PetalburgCity_Gym_Text_WallyIdLikeAPokemon, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_DadOhYoureWallyRight, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_WallyIveNeverCaughtAPokemon, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_DadHmISee, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, 0, PetalburgCity_Gym_EventScript_NormanAddressPlayerSouth
	call_if_eq VAR_0x8008, 1, PetalburgCity_Gym_EventScript_NormanAddressPlayerNorth
	call_if_eq VAR_0x8008, 2, PetalburgCity_Gym_EventScript_NormanAddressPlayerWest
	call_if_eq VAR_0x8008, 3, PetalburgCity_Gym_EventScript_NormanAddressPlayerEast
	msgbox PetalburgCity_Gym_Text_DadPlayerGoWithWally, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, 0, PetalburgCity_Gym_EventScript_NormanAddressWallySouth
	call_if_eq VAR_0x8008, 1, PetalburgCity_Gym_EventScript_NormanAddressWallyNorth
	call_if_eq VAR_0x8008, 2, PetalburgCity_Gym_EventScript_NormanAddressWallyWest
	call_if_eq VAR_0x8008, 3, PetalburgCity_Gym_EventScript_NormanAddressWallyEast
	msgbox PetalburgCity_Gym_Text_IllLoanYouMyZigzagoon, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_WallyThankYouAndDadGivesPokeBall, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_WallyOhWowThankYou, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, 0, PetalburgCity_Gym_EventScript_NormanFaceDoorSouth
	call_if_eq VAR_0x8008, 1, PetalburgCity_Gym_EventScript_NormanFaceDoorNorth
	call_if_eq VAR_0x8008, 2, PetalburgCity_Gym_EventScript_NormanFaceDoorWest
	call_if_eq VAR_0x8008, 3, PetalburgCity_Gym_EventScript_NormanFaceDoorEast
	call_if_eq VAR_0x8008, 0, PetalburgCity_Gym_EventScript_WallyFacePlayer
	call_if_eq VAR_0x8008, 1, PetalburgCity_Gym_EventScript_WallyFaceDown
	call_if_eq VAR_0x8008, 2, PetalburgCity_Gym_EventScript_WallyFacePlayer
	call_if_eq VAR_0x8008, 3, PetalburgCity_Gym_EventScript_WallyFacePlayer
	msgbox PetalburgCity_Gym_Text_WouldYouReallyComeWithMe, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_DONT_TRANSITION_MUSIC
	playbgm MUS_FOLLOW_ME, FALSE
	call_if_eq VAR_0x8008, 0, PetalburgCity_Gym_EventScript_ExitGymWithWallySouth
	call_if_eq VAR_0x8008, 1, PetalburgCity_Gym_EventScript_ExitGymWithWallyNorth
	call_if_eq VAR_0x8008, 2, PetalburgCity_Gym_EventScript_ExitGymWithWallyWest
	call_if_eq VAR_0x8008, 3, PetalburgCity_Gym_EventScript_ExitGymWithWallyEast
	removeobject LOCALID_WALLY
	setflag FLAG_HIDE_PETALBURG_CITY_WALLYS_MOM
	setvar VAR_PETALBURG_GYM_STATE, 1
	setvar VAR_PETALBURG_CITY_STATE, 2
	clearflag FLAG_HIDE_PETALBURG_CITY_WALLY
	clearflag FLAG_HIDE_PETALBURG_GYM_WALLY
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	special InitBirchState
	warp MAP_PETALBURG_CITY, 15, 8
	waitstate
	release
	end

PetalburgCity_Gym_EventScript_WallyArriveSouth::
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyArrive
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallyArriveNorth::
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyArriveNorth
	waitmovement 0
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallyArriveWestEast::
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterDown
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyArrive
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallySouth::
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyExitSouthWest
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallySouth
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallyNorth::
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyExitNorth
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallyNorth
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallyWest::
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyExitSouthWest
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallyWest
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallyEast::
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyExitEast
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallyEast
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressPlayerSouth::
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressPlayerNorth::
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterDown
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressPlayerWest::
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressPlayerEast::
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterLeft
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressWallySouth::
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressWallyNorth::
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressWallyWest::
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressWallyEast::
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallyFacePlayer::
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallyFaceDown::
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanNoBadges::
	msgbox PetalburgCity_Gym_Text_NormanGoToRustboro, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_NormanOneBadge::
	msgbox PetalburgCity_Gym_Text_NormanGoToDewford, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_NormanTwoBadges::
	msgbox PetalburgCity_Gym_Text_YouHaveGottenStronger, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_NormanThreeBadges::
	msgbox PetalburgCity_Gym_Text_YouHaveGottenStronger, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_NormanFaceDoorSouth::
	return

@ For all other NormanFaceDoorX, Norman is already facing the door from NormanAddressWallyX
PetalburgCity_Gym_EventScript_NormanFaceDoorNorth::
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanFaceDoorWest::
	return

PetalburgCity_Gym_EventScript_NormanFaceDoorEast::
	return

PetalburgCity_Gym_EventScript_NormanPostBattle::
	call PetalburgCity_Gym_EventScript_ShouldGiveEnigmaBerry
	goto_if_eq VAR_RESULT, TRUE, PetalburgCity_Gym_EventScript_GiveEnigmaBerry
	goto_if_unset FLAG_RECEIVED_TM_FACADE, PetalburgCity_Gym_EventScript_GiveFacade2
	goto_if_set FLAG_SYS_GAME_CLEAR, PetalburgCity_Gym_EventScript_NoAmountOfTrainingIsEnough
	msgbox PetalburgCity_Gym_Text_DadGoingToKeepTraining, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_GiveFacade2::
	call PetalburgCity_Gym_EventScript_GiveFacade
	release
	end

PetalburgCity_Gym_EventScript_NormanRematch::
	trainerbattle_rematch_double TRAINER_NORMAN_1, PetalburgCity_Gym_Text_NormanPreRematch, PetalburgCity_Gym_Text_NormanRematchDefeat, PetalburgCity_Gym_Text_NormanRematchNeedTwoMons
	msgbox PetalburgCity_Gym_Text_NormanPostRematch, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_ShouldGiveEnigmaBerry::
	specialvar VAR_RESULT, IsEnigmaBerryValid
	goto_if_eq VAR_RESULT, FALSE, PetalburgCity_Gym_EventScript_DontGiveEnigmaBerry
	checkitem ITEM_ENIGMA_BERRY
	goto_if_eq VAR_RESULT, TRUE, PetalburgCity_Gym_EventScript_DontGiveEnigmaBerry
	checkpcitem ITEM_ENIGMA_BERRY
	goto_if_eq VAR_RESULT, TRUE, PetalburgCity_Gym_EventScript_DontGiveEnigmaBerry
	goto_if_eq VAR_ENIGMA_BERRY_AVAILABLE, 0, PetalburgCity_Gym_EventScript_DontGiveEnigmaBerry
	msgbox PetalburgCity_Gym_Text_GiveEnigmaBerry, MSGBOX_DEFAULT
	setvar VAR_RESULT, TRUE
	return

PetalburgCity_Gym_EventScript_DontGiveEnigmaBerry::
	setvar VAR_RESULT, FALSE
	return

PetalburgCity_Gym_EventScript_GiveEnigmaBerry::
	giveitem ITEM_ENIGMA_BERRY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_ENIGMA_BERRY_AVAILABLE, 0
	release
	end

PetalburgCity_Gym_EventScript_NormanBattle::
	msgbox PetalburgCity_Gym_Text_NormanIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_NORMAN_1, PetalburgCity_Gym_Text_NormanDefeat
	message PetalburgCity_Gym_Text_ReceivedBalanceBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox PetalburgCity_Gym_Text_ExplainBalanceBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_PETALBURG_GYM
	setvar VAR_PETALBURG_GYM_STATE, 7
	setflag FLAG_BADGE05_GET
	special ResetHealLocationFromDewford
	call EventScript_HideMrBriney
	setflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	clearflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setvar VAR_0x8008, 5
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_DEWFORD_HALL_SLUDGE_BOMB_MAN
	call PetalburgCity_Gym_EventScript_UnlockAllDoors
	special DrawWholeMapView
	call PetalburgCity_Gym_EventScript_GiveFacade
	delay 30
	msgbox PetalburgCity_Gym_Text_DadHappyAndSad, MSGBOX_DEFAULT
	closemessage
	delay 40
	playse SE_DOOR
	delay 10
	addobject LOCALID_WALLYS_DAD
	switch VAR_FACING
	case DIR_NORTH, PetalburgCity_Gym_EventScript_WallysDadArrivesNorth
	case DIR_WEST, PetalburgCity_Gym_EventScript_WallysDadArrivesWest
	case DIR_EAST, PetalburgCity_Gym_EventScript_WallysDadArrivesEast
	end

PetalburgCity_Gym_EventScript_GiveFacade::
	giveitem ITEM_TM_FACADE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	setflag FLAG_RECEIVED_TM_FACADE
	msgbox PetalburgCity_Gym_Text_ExplainFacade, MSGBOX_DEFAULT
	return

PetalburgCity_Gym_EventScript_WallysDadArrivesNorth::
	setvar VAR_0x8008, 1
	goto PetalburgCity_Gym_EventScript_WallysDadArrives

PetalburgCity_Gym_EventScript_WallysDadArrivesEast::
	setvar VAR_0x8008, 2
	goto PetalburgCity_Gym_EventScript_WallysDadArrives

PetalburgCity_Gym_EventScript_WallysDadArrivesWest::
	setvar VAR_0x8008, 3
	goto PetalburgCity_Gym_EventScript_WallysDadArrives

PetalburgCity_Gym_EventScript_WallysDadArrives::
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Gym_Movement_WallysDadEnterGym
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WALLYS_DAD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLYS_DAD, Common_Movement_Delay48
	waitmovement 0
	delay 10
	call_if_eq VAR_0x8008, 1, PetalburgCity_Gym_EventScript_WallysDadApproachPlayerNorth
	call_if_eq VAR_0x8008, 2, PetalburgCity_Gym_EventScript_WallysDadApproachPlayerEast
	call_if_eq VAR_0x8008, 3, PetalburgCity_Gym_EventScript_WallysDadApproachPlayerWest
	msgbox PetalburgCity_Gym_Text_PleaseComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 20
	call_if_eq VAR_0x8008, 1, PetalburgCity_Gym_EventScript_WallysDadFaceNormanNorth
	call_if_eq VAR_0x8008, 2, PetalburgCity_Gym_EventScript_WallysDadFaceNormanEast
	call_if_eq VAR_0x8008, 3, PetalburgCity_Gym_EventScript_WallysDadFaceNormanWest
	msgbox PetalburgCity_Gym_Text_LetMeBorrowPlayer, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_DONT_TRANSITION_MUSIC
	playbgm MUS_FOLLOW_ME, FALSE
	call_if_eq VAR_0x8008, 1, PetalburgCity_Gym_EventScript_ExitGymWithWallysDadNorth
	call_if_eq VAR_0x8008, 2, PetalburgCity_Gym_EventScript_ExitGymWithWallysDadEast
	call_if_eq VAR_0x8008, 3, PetalburgCity_Gym_EventScript_ExitGymWithWallysDadWest
	removeobject LOCALID_WALLYS_DAD
	setvar VAR_PETALBURG_CITY_STATE, 4
	clearflag FLAG_HIDE_PETALBURG_CITY_WALLYS_DAD
	warp MAP_PETALBURG_CITY, 15, 8
	waitstate
	release
	end

PetalburgCity_Gym_EventScript_WallysDadFaceNormanNorth::
	applymovement LOCALID_WALLYS_DAD, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallysDadFaceNormanEast::
	applymovement LOCALID_WALLYS_DAD, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallysDadFaceNormanWest::
	applymovement LOCALID_WALLYS_DAD, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallysDadApproachPlayerNorth::
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Gym_Movement_WallysDadApproachPlayerNorth
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallysDadApproachPlayerEast::
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Gym_Movement_WallysDadApproachPlayerEast
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallysDadApproachPlayerWest::
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Gym_Movement_WallysDadApproachPlayerWest
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallysDadNorth::
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Gym_Movement_WallysDadExitNorth
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFasterDown
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallysDadNorth
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallysDadEast::
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Gym_Movement_WallysDadExitEast
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallysDadEast
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallysDadWest::
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Gym_Movement_WallysDadExitWest
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallysDadWest
	waitmovement 0
	return

PetalburgCity_Gym_Movement_WallysDadExitNorth:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_faster_up
	delay_8
	walk_in_place_down
	set_invisible
	step_end

PetalburgCity_Gym_Movement_WallysDadExitEast:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_faster_up
	delay_8
	walk_in_place_down
	set_invisible
	step_end

PetalburgCity_Gym_Movement_WallysDadExitWest:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_faster_up
	delay_8
	walk_in_place_down
	set_invisible
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallysDadNorth:
	delay_16
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallysDadEast:
	delay_16
	walk_down
	walk_down
	walk_left
	walk_down
	walk_down
	walk_down
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallysDadWest:
	delay_16
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

PetalburgCity_Gym_Movement_WallysDadEnterGym:
	walk_up
	delay_8
	walk_in_place_faster_right
	delay_8
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_up
	step_end

PetalburgCity_Gym_Movement_WallysDadApproachPlayerNorth:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

PetalburgCity_Gym_Movement_WallysDadApproachPlayerEast:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

PetalburgCity_Gym_Movement_WallysDadApproachPlayerWest:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	step_end

PetalburgCity_Gym_Movement_Unused:
	walk_in_place_faster_up
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_down
	step_end

PetalburgCity_Gym_Movement_WallyArriveNorth:
	delay_16
	walk_up
	delay_16
	delay_8
	walk_up
	walk_right
	walk_up
	walk_up
	walk_in_place_faster_left
	step_end

PetalburgCity_Gym_Movement_WallyArrive:
	delay_16
	walk_up
	delay_16
	delay_8
	walk_up
	walk_up
	step_end

PetalburgCity_Gym_Movement_WallyExitNorth:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_up
	delay_16
	walk_in_place_down
	step_end

PetalburgCity_Gym_Movement_WallyExitEast:
	walk_down
	walk_down
	walk_right
	walk_down
	walk_in_place_faster_up
	delay_16
	walk_in_place_down
	step_end

PetalburgCity_Gym_Movement_WallyExitSouthWest:
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_up
	delay_16
	walk_in_place_down
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallyNorth:
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallySouth:
	delay_16
	delay_16
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallyWest:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallyEast:
	walk_in_place_faster_down
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_right
	walk_down
	delay_8
	step_end

PetalburgCity_Gym_EventScript_NoAmountOfTrainingIsEnough::
	msgbox PetalburgCity_Gym_Text_DadNoAmountOfTrainingIsEnough, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_SpeedRoomDoor::
	lockall
	goto_if_lt VAR_PETALBURG_GYM_STATE, 6, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 85
	msgbox PetalburgCity_Gym_Text_EnterSpeedRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_EnterRoom::
	closemessage
	delay 30
	warpdoor MAP_PETALBURG_CITY_GYM, VAR_0x8008, VAR_0x8009
	waitstate
	releaseall
	end

PetalburgCity_Gym_EventScript_DontEnterRoom::
	releaseall
	end

PetalburgCity_Gym_EventScript_DoorLocked::
	msgbox PetalburgCity_Gym_Text_DoorAppearsLocked, MSGBOX_DEFAULT
	releaseall
	end

@ VAR_0x8008 and VAR_0x8009 below are the x and y coordinates of the warp
PetalburgCity_Gym_EventScript_AccuracyRoomDoor::
	lockall
	goto_if_lt VAR_PETALBURG_GYM_STATE, 6, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 98
	msgbox PetalburgCity_Gym_Text_EnterAccuracyRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_ConfusionRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_RANDALL, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 46
	msgbox PetalburgCity_Gym_Text_EnterConfusionRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftDefenseRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_RANDALL, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 59
	msgbox PetalburgCity_Gym_Text_EnterDefenseRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightDefenseRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_MARY, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 59
	msgbox PetalburgCity_Gym_Text_EnterDefenseRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RecoveryRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_MARY, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 72
	msgbox PetalburgCity_Gym_Text_EnterRecoveryRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftStrengthRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 20
	msgbox PetalburgCity_Gym_Text_EnterStrengthRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightStrengthRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 20
	msgbox PetalburgCity_Gym_Text_EnterStrengthRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftOHKORoomDoor::
	lockall
	goto_if_not_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 33
	msgbox PetalburgCity_Gym_Text_EnterOHKORoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightOHKORoomDoor::
	lockall
	goto_if_not_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 33
	msgbox PetalburgCity_Gym_Text_EnterOHKORoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftGymLeadersRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_JODY, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 7
	msgbox PetalburgCity_Gym_Text_EnterGymLeadersRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightGymLeadersRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_BERKE, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 7
	msgbox PetalburgCity_Gym_Text_EnterGymLeadersRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_Randall::
	trainerbattle_single TRAINER_RANDALL, PetalburgCity_Gym_Text_RandallIntro, PetalburgCity_Gym_Text_RandallDefeat, PetalburgCity_Gym_EventScript_SlideOpenSpeedRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_RandallPostBadge
	msgbox PetalburgCity_Gym_Text_RandallPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenSpeedRoomDoors::
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_RandallPostBadge::
	msgbox PetalburgCity_Gym_Text_RandallPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Parker::
	trainerbattle_single TRAINER_PARKER, PetalburgCity_Gym_Text_ParkerIntro, PetalburgCity_Gym_Text_ParkerDefeat, PetalburgCity_Gym_EventScript_SlideOpenConfusionRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_ParkerPostBadge
	msgbox PetalburgCity_Gym_Text_ParkerPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenConfusionRoomDoors::
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_ParkerPostBadge::
	msgbox PetalburgCity_Gym_Text_ParkerPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_George::
	trainerbattle_single TRAINER_GEORGE, PetalburgCity_Gym_Text_GeorgeIntro, PetalburgCity_Gym_Text_GeorgeDefeat, PetalburgCity_Gym_EventScript_SlideOpenRecoveryRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_GeorgePostBadge
	msgbox PetalburgCity_Gym_Text_GeorgePostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenRecoveryRoomDoors::
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_GeorgePostBadge::
	msgbox PetalburgCity_Gym_Text_GeorgePostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Berke::
	trainerbattle_single TRAINER_BERKE, PetalburgCity_Gym_Text_BerkeIntro, PetalburgCity_Gym_Text_BerkeDefeat, PetalburgCity_Gym_EventScript_SlideOpenOHKORoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_BerkePostBadge
	msgbox PetalburgCity_Gym_Text_BerkePostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenOHKORoomDoors::
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenOHKORoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_BerkePostBadge::
	msgbox PetalburgCity_Gym_Text_BerkePostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Mary::
	trainerbattle_single TRAINER_MARY, PetalburgCity_Gym_Text_MaryIntro, PetalburgCity_Gym_Text_MaryDefeat, PetalburgCity_Gym_EventScript_SlideOpenAccuracyRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_MaryPostBadge
	msgbox PetalburgCity_Gym_Text_MaryPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenAccuracyRoomDoors::
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_MaryPostBadge::
	msgbox PetalburgCity_Gym_Text_MaryPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Alexia::
	trainerbattle_single TRAINER_ALEXIA, PetalburgCity_Gym_Text_AlexiaIntro, PetalburgCity_Gym_Text_AlexiaDefeat, PetalburgCity_Gym_EventScript_SlideOpenDefenseRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_AlexiaPostBadge
	msgbox PetalburgCity_Gym_Text_AlexiaPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenDefenseRoomDoors::
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_AlexiaPostBadge::
	msgbox PetalburgCity_Gym_Text_AlexiaPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Jody::
	trainerbattle_single TRAINER_JODY, PetalburgCity_Gym_Text_JodyIntro, PetalburgCity_Gym_Text_JodyDefeat, PetalburgCity_Gym_EventScript_SlideOpenStrengthRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_JodyPostBadge
	msgbox PetalburgCity_Gym_Text_JodyPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenStrengthRoomDoors::
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_JodyPostBadge::
	msgbox PetalburgCity_Gym_Text_JodyPostBadge, MSGBOX_NPC
	end

@ VAR_0x8004 below is the room number
@ VAR_0x8005 below is 0 when the door should be slid open and 1 when it should be unlocked immediately
PetalburgCity_Gym_EventScript_OpenGymEntranceDoors::
	setvar VAR_0x8004, 1
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetEntranceRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors::
	setvar VAR_0x8004, 2
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetSpeedRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors::
	setvar VAR_0x8004, 3
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetAccuracyRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors::
	setvar VAR_0x8004, 4
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetConfusionRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors::
	setvar VAR_0x8004, 5
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetDefenseRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors::
	setvar VAR_0x8004, 6
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetRecoveryRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors::
	setvar VAR_0x8004, 7
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetStrengthRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenOHKORoomDoors::
	setvar VAR_0x8004, 8
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetOHKORoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_SetEntranceRoomDoorMetatiles::
	setmetatile 6, 85, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 85, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	setmetatile 1, 98, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 98, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SetSpeedRoomDoorMetatiles::
	setmetatile 6, 46, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 46, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	setmetatile 1, 59, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 59, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SetAccuracyRoomDoorMetatiles::
	setmetatile 6, 59, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 59, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	setmetatile 1, 72, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 72, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SetConfusionRoomDoorMetatiles::
	setmetatile 1, 20, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 20, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SetDefenseRoomDoorMetatiles::
	setmetatile 6, 20, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 20, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	setmetatile 1, 33, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 33, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SetRecoveryRoomDoorMetatiles::
	setmetatile 6, 33, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 33, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SetStrengthRoomDoorMetatiles::
	setmetatile 1, 7, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 7, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SetOHKORoomDoorMetatiles::
	setmetatile 6, 7, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 7, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SlideOpenRoomDoors::
	special PetalburgGymSlideOpenRoomDoors
	waitstate
	return

PetalburgCity_Gym_EventScript_UnlockRoomDoors::
	special PetalburgGymUnlockRoomDoors
	return

PetalburgCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_GymGuidePostVictory
	msgbox PetalburgCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_GymGuidePostVictory::
	msgbox PetalburgCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE05_GET, PetalburgCity_Gym_EventScript_GymStatueCertified
	goto PetalburgCity_Gym_EventScript_GymStatue
	end

PetalburgCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE05_GET, PetalburgCity_Gym_EventScript_GymStatueCertified
	goto PetalburgCity_Gym_EventScript_GymStatue
	end

PetalburgCity_Gym_EventScript_GymStatueCertified::
	msgbox PetalburgCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

PetalburgCity_Gym_EventScript_GymStatue::
	msgbox PetalburgCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

PetalburgCity_Gym_Text_DadYoureHereWithYourPokemon:
	.string "DAD: Χμ;\p"
	.string "Μα κοίτα να δεις, {PLAYER}!\n"
	.string "Τελειώσατε με τη μετακόμιση;\p"
	.string "Μου κάνει εντύπωση που κατάφερες \n"
	.string "να έρθεις εδώ χωρίς βοήθεια.\p"
	.string "Α, κατάλαβα.\n"
	.string "Είσαι μαζί με τα POKéMON σου.\p"
	.string "Χμ… Τότε μάλλον πρόκειται να\n"
	.string "γίνεις TRAINER σαν εμένα, {PLAYER}.\p"
	.string "Αυτά είναι υπέροχα νέα!\n"
	.string "Ανυπομονώ γι' αυτό!$"

PetalburgCity_Gym_Text_WallyIdLikeAPokemon:
	.string "Εμ… Εγώ…\n"
	.string "Θα ήθελα ένα POKéMON, παρακαλώ…$"

PetalburgCity_Gym_Text_DadOhYoureWallyRight:
	.string "DAD: Χμ; Είσαι… Εε… Α, σωστά.\n"
	.string "Είσαι ο WALLY, σωστά;$"

PetalburgCity_Gym_Text_WallyIveNeverCaughtAPokemon:
	.string "WALLY: Θα πάω να μείνω με τους\n"
	.string "συγγενείς μου στη VERDANTURF TOWN.\p"
	.string "Σκέφτηκα ότι θα ήμουν μόνος μου,\n"
	.string "οπότε ήθελα να πάρω ένα POKéMON.\p"
	.string "Αλλά δεν έχω πιάσει POKéMON πριν.\n"
	.string "Και δεν ξέρω το πώς…$"

PetalburgCity_Gym_Text_DadHmISee:
	.string "DAD: Χμ. Καταλαβαίνω.$"

PetalburgCity_Gym_Text_DadPlayerGoWithWally:
	.string "DAD: {PLAYER}, το άκουσες αυτό,\n"
	.string "σωστά;\p"
	.string "Πήγαινε με τον WALLY και σιγουρέψου\n"
	.string "πως θα πιάσει ένα POKéMON.$"

PetalburgCity_Gym_Text_IllLoanYouMyZigzagoon:
	.string "WALLY, ορίστε, θα σου δανείσω\n"
	.string "το POKéMON μου.\p"
	.string "Ο WALLY έλαβε ένα ZIGZAGOON!$"

PetalburgCity_Gym_Text_WallyThankYouAndDadGivesPokeBall:
	.string "WALLY: Ω, ουάου!\n"
	.string "Ένα POKéMON!\p"
	.string "DAD: Χμ. Θα σου δώσω και ένα\n"
	.string "POKé BALL. Προχώρα!\p"
	.string "Ο WALLY έλαβε ένα POKé BALL!$"

PetalburgCity_Gym_Text_WallyOhWowThankYou:
	.string "WALLY: Ω, ουάου!\n"
	.string "Σε ευχαριστώ!$"

PetalburgCity_Gym_Text_WouldYouReallyComeWithMe:
	.string "{PLAYER}… Θα ερχόσουν πραγματικά\n"
	.string "μαζί μου;$"

PetalburgCity_Gym_Text_DadSoDidItWorkOut:
	.string "DAD: Λοιπόν, πώς πήγε;$"

PetalburgCity_Gym_Text_WallyThankYouBye:
	.string "WALLY: Σας ευχαριστώ, ναι, πήγε.\n"
	.string "Ορίστε το POKéMON σας πίσω.\p"
	.string "{PLAYER}, σε ευχαριστώ που ήρθες\n"
	.string "μαζί μου.\p"
	.string "Χάρη σε εσάς τους δύο μπόρεσα\n"
	.string "να πιάσω το POKéMON μου.\p"
	.string "Υπόσχομαι ότι θα το φροντίζω\n"
	.string "πάρα πολύ καλά.\p"
	.string "Ω! Η μαμά μου με περιμένει,\n"
	.string "οπότε πρέπει να φύγω!\p"
	.string "Γεια σου, {PLAYER}!$"

PetalburgCity_Gym_Text_DadGoCollectBadges:
	.string "DAD: Τώρα…\p"
	.string "{PLAYER}, αν θέλεις να γίνεις ένας\n"
	.string "δυνατός TRAINER, ορίστε η συμβουλή μου.\p"
	.string "Κατευθύνσου προς τη RUSTBORO CITY\n"
	.string "πέρα από αυτή την πόλη.\p"
	.string "Εκεί, θα πρέπει να προκαλέσεις\n"
	.string "τη GYM LEADER, ROXANNE.\p"
	.string "Μετά από αυτήν, πήγαινε σε άλλα \n"
	.string "POKéMON GYMS και νίκησε τους LEADERS.\p"
	.string "Μάζεψε BADGES από αυτούς,\n"
	.string "κατάλαβες;\p"
	.string "Φυσικά, είμαι κι εγώ GYM LEADER.\n"
	.string "Θα παλέψουμε μια μέρα, {PLAYER}.\p"
	.string "Αλλά αυτό μόνο αφού γίνεις\n"
	.string "πιο δυνατός.$"

PetalburgCity_Gym_Text_NormanGoToRustboro:
	.string "DAD: Χμ; Δεν πας στο\n"
	.string "POKéMON GYM στη RUSTBORO CITY;\p"
	.string "Δεν είναι πρόκληση για μένα να\n"
	.string "παλέψω με έναν αρχάριο TRAINER.\p"
	.string "{PLAYER}, θέλω να με προκαλέσεις\n"
	.string "όταν γίνεις πολύ πιο δυνατός.\p"
	.string "Θα παλέψω μαζί σου, {PLAYER}, όταν \n"
	.string "μπορέσεις να μου δείξεις τέσσερα \l"
	.string "GYM BADGES, εντάξει;$"

PetalburgCity_Gym_Text_NormanGoToDewford:
	.string "DAD: Καταλαβαίνω… Οπότε, νίκησες\n"
	.string "τη GYM LEADER στη RUSTBORO CITY.\p"
	.string "Αλλά υπάρχουν πολλοί περισσότεροι \n"
	.string "TRAINERS που είναι πιο δυνατοί \l"
	.string "από σένα, {PLAYER}.\p"
	.string "Πέρα από τη θάλασσα στη DEWFORD TOWN \n"
	.string "είναι ένας GYM LEADER ονόματι BRAWLY.\p"
	.string "Θα πρέπει να πας να τον προκαλέσεις.$"

PetalburgCity_Gym_Text_YouHaveGottenStronger:
	.string "DAD: Χμ… {PLAYER}, έχεις γίνει \n"
	.string "πιο δυνατός.\p"
	.string "Το καταλαβαίνω από τον αριθμό των \n"
	.string "BADGES που έχεις κερδίσει.$"

PetalburgCity_Gym_Text_NormanIntro:
	.string "DAD: Χμ…\n"
	.string "Οπότε, πήρες τέσσερα GYM BADGES.\p"
	.string "Ωραία, όπως υποσχέθηκα, θα έχουμε \n"
	.string "μια POKéMON μάχη.\p"
	.string "{PLAYER}…\p"
	.string "Είμαι τόσο χαρούμενος που μπορώ \n"
	.string "να έχω μια πραγματική μάχη με το \l"
	.string "ίδιο μου το παιδί.\p"
	.string "Αλλά, μια μάχη είναι μια μάχη!\p"
	.string "Θα κάνω ό,τι περνάει από το χέρι \n"
	.string "μου ως GYM LEADER για να νικήσω.\p"
	.string "{PLAYER}, καλύτερα να δώσεις κι \n"
	.string "εσύ τον καλύτερό σου εαυτό!$"

PetalburgCity_Gym_Text_NormanDefeat:
	.string "…\p"
	.string "Εγώ… Δεν μπορώ…\p"
	.string "Δεν μπορώ να το πιστέψω. {PLAYER}…\p"
	.string "Έχασα από το παιδί μου;\p"
	.string "Αλλά, οι κανόνες είναι κανόνες!\n"
	.string "Ορίστε, πάρε αυτό.$"

PetalburgCity_Gym_Text_ReceivedBalanceBadge:
	.string "Ο {PLAYER} έλαβε το BALANCE BADGE\n"
	.string "από τον DAD!$"

PetalburgCity_Gym_Text_ExplainBalanceBadgeTakeThis:
	.string "DAD: Με αυτό το BADGE, η DEFENSE\n"
	.string "όλων των POKéMON σου θα αυξηθεί.\p"
	.string "Τα POKéMON που ξέρουν την HM κίνηση \n"
	.string "SURF θα μπορούν να ταξιδεύουν \l"
	.string "πάνω στο νερό.\p"
	.string "Αυτό είναι το δώρο μου για σένα. \n"
	.string "{PLAYER}, είμαι βέβαιος ότι μπορείς \l"
	.string "να το χρησιμοποιήσεις σωστά.$"

PetalburgCity_Gym_Text_ExplainFacade:
	.string "DAD: Το TM42 περιέχει την FACADE.\p"
	.string "Διπλασιάζει τη δύναμη των κινήσεων \n"
	.string "αν το POKéMON είναι δηλητηριασμένο, \l"
	.string "παράλυτο ή καμένο.\p"
	.string "Μπορεί να μετατρέψει μια δύσκολη \n"
	.string "κατάσταση σε πλεονέκτημα.$"

PetalburgCity_Gym_Text_DadHappyAndSad:
	.string "DAD: Ως GYM LEADER, δεν μπορώ \n"
	.string "να περιγράψω πόσο αναστατωμένος \l"
	.string "είμαι…\p"
	.string "Αλλά ως πατέρας, με κάνει ταυτόχρονα \n"
	.string "χαρούμενο και λίγο λυπημένο. \l"
	.string "Είναι περίεργο…$"

PetalburgCity_Gym_Text_PleaseComeWithMe:
	.string "Α, εδώ είσαι, {PLAYER}!\p"
	.string "Σε παρακαλώ, έλα μαζί μου.\n"
	.string "Έχω κάτι που θέλω να σου δώσω.$"

PetalburgCity_Gym_Text_LetMeBorrowPlayer:
	.string "NORMAN, δεν σε πειράζει, έτσι;\p"
	.string "Άσε με να δανειστώ τον {PLAYER} για \n"
	.string "ένα δυο λεπτά.$"

PetalburgCity_Gym_Text_DadGoingToKeepTraining:
	.string "DAD: {PLAYER}, θα πρέπει να \n"
	.string "επισκέπτεσαι τη μητέρα σου κάθε \l"
	.string "τόσο.\p"
	.string "Εγώ θα μείνω εδώ και θα εντείνω \n"
	.string "την εκπαίδευσή μου.\p"
	.string "Θα με ενοχλούσε ως TRAINER να \n"
	.string "μην πάρω εκδίκηση για την ήττα \l"
	.string "μου από εσένα, {PLAYER}!$"

PetalburgCity_Gym_Text_DadNoAmountOfTrainingIsEnough:
	.string "DAD: {PLAYER}, πώς πάνε τα πράγματα;\p"
	.string "Ο κόσμος των POKéMON είναι βαθύς.\p"
	.string "Ειλικρινά πιστεύω ότι καμία \n"
	.string "ποσότητα εκπαίδευσης δεν θα \l"
	.string "ήταν ποτέ αρκετή.$"

PetalburgCity_Gym_Text_GymGuideAdvice:
	.string "Γεια, πώς πάει, μελλοντικέ \n"
	.string "CHAMPION {PLAYER};\p"
	.string "Οι πόρτες σε αυτό το GYM ανοίγουν \n"
	.string "όταν νικήσεις τους TRAINERS.\p"
	.string "Ωχ! Οι πόρτες σε αυτό το δωμάτιο \n"
	.string "είναι ήδη ανοιχτές!\p"
	.string "Οι TRAINERS του PETALBURG GYM \n"
	.string "χρησιμοποιούν κάθε είδους \l"
	.string "αντικείμενα.\p"
	.string "Η πόρτα αριστερά οδηγεί στο \n"
	.string "SPEED ROOM.\p"
	.string "Η πόρτα δεξιά οδηγεί στο \n"
	.string "ACCURACY ROOM.\p"
	.string "Το όνομα του δωματίου είναι στην \n"
	.string "πόρτα, οπότε διάλεξε προσεκτικά.\p"
	.string "Μόλις διαλέξεις την πόρτα…\n"
	.string "Ε, λοιπόν, προχώρα!$"

PetalburgCity_Gym_Text_GymGuidePostVictory:
	.string "{PLAYER}! Πω πω! Ξεπέρασες ακόμα \n"
	.string "και τον ίδιο σου τον πατέρα!\p"
	.string "Πω πω!\n"
	.string "Τι εκπληκτική τροπή των γεγονότων!$"

PetalburgCity_Gym_Text_RandallIntro:
	.string "Η ικανότητα να επιτίθεσαι πριν \n"
	.string "από τον αντίπαλο…\p"
	.string "Αυτό και μόνο με βάζει σε μεγάλο \n"
	.string "πλεονέκτημα, δεν συμφωνείς;$"

PetalburgCity_Gym_Text_RandallDefeat:
	.string "Αυτή ήταν μια μεγαλειώδης μάχη!$"

PetalburgCity_Gym_Text_RandallPostBattle:
	.string "Συνέχισε στο επόμενο δωμάτιο όπου \n"
	.string "μια νέα πρόκληση σε περιμένει.\p"
	.string "Αριστερά είναι το CONFUSION ROOM.\p"
	.string "Η δεξιά πόρτα οδηγεί στο \n"
	.string "DEFENSE ROOM.$"

PetalburgCity_Gym_Text_RandallPostBadge:
	.string "Όποιον κι αν νικήσεις, και από \n"
	.string "όποιον κι αν χάσεις, ποτέ μην \l"
	.string "σταματήσεις να εκπαιδεύεις τον \l"
	.string "εαυτό σου και τα POKéMON σου.\p"
	.string "Αυτό πιστεύω ότι σημαίνει το να \n"
	.string "είσαι GYM LEADER.$"

PetalburgCity_Gym_Text_ParkerIntro:
	.string "Αυτό είναι το CONFUSION ROOM.\p"
	.string "Για να δω πόσο καλά δεμένος είσαι \n"
	.string "με τα POKéMON σου!$"

PetalburgCity_Gym_Text_ParkerDefeat:
	.string "Δεν μπόρεσα να μπερδέψω την ομάδα \n"
	.string "σου αρκετά… Έχετε έναν ισχυρό \l"
	.string "δεσμό μαζί.$"

PetalburgCity_Gym_Text_ParkerPostBattle:
	.string "Το επόμενο δωμάτιο είναι το \n"
	.string "STRENGTH ROOM. Μπορείς να \l"
	.string "αντέξεις την ωμή βία;$"

PetalburgCity_Gym_Text_ParkerPostBadge:
	.string "Αφού νίκησες τον LEADER μας, η \n"
	.string "εκπαίδευση έγινε πολύ πιο σκληρή.$"

PetalburgCity_Gym_Text_GeorgeIntro:
	.string "Εκεί που νομίζεις ότι θα νικήσεις, \n"
	.string "ο αντίπαλος αναπληρώνει HP…\p"
	.string "Μπορείς να φανταστείς πόσο \n"
	.string "απαίσια πρέπει να νιώθεις;\p"
	.string "Θα σου δείξω ακριβώς πόσο \n"
	.string "απαίσια είναι!$"

PetalburgCity_Gym_Text_GeorgeDefeat:
	.string "Δεν μπόρεσα να αναπληρώσω αρκετό \n"
	.string "HP… Τι δύναμη ATTACK…$"

PetalburgCity_Gym_Text_GeorgePostBattle:
	.string "Δεν θα έπρεπε να περιμένω τίποτα \n"
	.string "λιγότερο από το παιδί του \l"
	.string "LEADER μας.\p"
	.string "Όχι, περίμενε! Οι ικανότητες ενός \n"
	.string "TRAINER κερδίζονται μόνο με \l"
	.string "προσπάθεια.\p"
	.string "Έχασα επειδή οι δικές μου \n"
	.string "προσπάθειες δεν ήταν αρκετές.\p"
	.string "Προχώρα! Το ONE-HIT KO ROOM είναι \n"
	.string "το επόμενο.$"

PetalburgCity_Gym_Text_GeorgePostBadge:
	.string "Θα συνεχίσω να εκπαιδεύομαι στα \n"
	.string "GYMS. Μια μέρα, θα γίνω LEADER.$"

PetalburgCity_Gym_Text_BerkeIntro:
	.string "Δεν πρόκειται να σε λυπηθώ απλά \n"
	.string "επειδή είσαι το παιδί του \l"
	.string "LEADER μας.\p"
	.string "Θα σου δείξω πόσο φρικτό είναι για \n"
	.string "ένα POKéMON να δέχεται ένα \l"
	.string "critical hit!$"

PetalburgCity_Gym_Text_BerkeDefeat:
	.string "Η δύναμή σου…\n"
	.string "Είσαι σπουδαίος TRAINER.$"

PetalburgCity_Gym_Text_BerkePostBattle:
	.string "Ο πατέρας σου είναι πραγματικά \n"
	.string "δυνατός. Είναι ένας TRAINER που \l"
	.string "αξίζει τον σεβασμό μου.\p"
	.string "Και διαισθάνομαι την ίδια λάμψη \n"
	.string "να βγαίνει από σένα όπως και από \l"
	.string "τον πατέρα σου.\p"
	.string "Ελπίζω να δώσεις μια τρομερή \n"
	.string "μάχη με τον πατέρα σου!$"

PetalburgCity_Gym_Text_BerkePostBadge:
	.string "Από τότε που ο μπαμπάς σου έγινε \n"
	.string "ο LEADER, οι TRAINERS της \l"
	.string "PETALBURG CITY έχουν γίνει \l"
	.string "πολύ πιο σκληροί.$"

PetalburgCity_Gym_Text_MaryIntro:
	.string "Χιχι…\n"
	.string "Αυτό είναι το ACCURACY ROOM.\p"
	.string "Είναι αρκετά δυσάρεστο όταν κάθε \n"
	.string "επίθεση πετυχαίνει χωρίς \l"
	.string "εξαίρεση.$"

PetalburgCity_Gym_Text_MaryDefeat:
	.string "Ήσουν ένα επίπεδο πάνω από μένα…$"

PetalburgCity_Gym_Text_MaryPostBattle:
	.string "Υπάρχουν μερικοί ακόμα πιο \n"
	.string "δυνατοί TRAINERS που σε \l"
	.string "περιμένουν.\p"
	.string "Αριστερά είναι το DEFENSE ROOM, \n"
	.string "και δεξιά είναι το \l"
	.string "RECOVERY ROOM.\p"
	.string "Η δύναμη ATTACK των POKéMON σου \n"
	.string "θα δοκιμαστεί και στις δύο \l"
	.string "περιπτώσεις.$"

PetalburgCity_Gym_Text_MaryPostBadge:
	.string "Ξέρεις τι προσπαθούμε να \n"
	.string "πετύχουμε ως TRAINERS;\p"
	.string "Πασχίζουμε να γίνουμε αδελφές \n"
	.string "ψυχές με τα POKéMON μας.$"

PetalburgCity_Gym_Text_AlexiaIntro:
	.string "Όσο υψηλότερη είναι η DEFENSE, \n"
	.string "τόσο πιο ριψοκίνδυνη μπορώ να \l"
	.string "είμαι στην επίθεση.$"

PetalburgCity_Gym_Text_AlexiaDefeat:
	.string "Οι άμυνές μας δεν ήταν αρκετές…$"

PetalburgCity_Gym_Text_AlexiaPostBattle:
	.string "Νομίζω ότι μου έδωσες ένα \n"
	.string "πολύτιμο μάθημα εδώ.\p"
	.string "Τώρα, προχώρα! Η αριστερή πόρτα \n"
	.string "πηγαίνει στο STRENGTH ROOM.\p"
	.string "Η δεξιά πόρτα ανοίγει για το \n"
	.string "ONE-HIT KO ROOM.\p"
	.string "Και τα δύο έχουν TRAINERS που \n"
	.string "είναι ειδικοί στην επίθεση.$"

PetalburgCity_Gym_Text_AlexiaPostBadge:
	.string "Γεια! Δοκίμασες να \n"
	.string "χρησιμοποιήσεις το SURF;$"

PetalburgCity_Gym_Text_JodyIntro:
	.string "Ο GYM LEADER μας μας είπε να \n"
	.string "τα δώσουμε όλα και να σε \l"
	.string "νικήσουμε.\p"
	.string "Ακόμα κι αν τυχαίνει να είσαι το \n"
	.string "παιδί του LEADER!$"

PetalburgCity_Gym_Text_JodyDefeat:
	.string "Αλλά… Τα έδωσα όλα!$"

PetalburgCity_Gym_Text_JodyPostBattle:
	.string "Ο τρόπος που χρησιμοποιείς τα \n"
	.string "POKéMON σου… Μοιάζει με το στυλ \l"
	.string "του πατέρα σου.\p"
	.string "Πέρνα μέσα! Ο GYM LEADER, ο \n"
	.string "πατέρας σου, σε περιμένει!$"

PetalburgCity_Gym_Text_JodyPostBadge:
	.string "Βέβαια, είναι καλό να κάνεις τα \n"
	.string "POKéMON σου πιο δυνατά.\p"
	.string "Αλλά τι καθορίζει τον νικητή;\p"
	.string "Μα φυσικά, είναι τα συναισθήματα \n"
	.string "που έχουν οι TRAINERS για τα \l"
	.string "POKéMON τους.$"

PetalburgCity_Gym_Text_DoorAppearsLocked:
	.string "Αυτή η πόρτα φαίνεται να είναι\n"
	.string "κλειδωμένη αυτή τη στιγμή…$"

PetalburgCity_Gym_Text_EnterSpeedRoom:
	.string "“SPEED ROOM,” γράφει η ταμπέλα.\p"
	.string "Θέλεις να περάσεις;$"

@ Unused
PetalburgCity_Gym_Text_DoorAppearsLocked2:
	.string "Αυτή η πόρτα φαίνεται να είναι\n"
	.string "κλειδωμένη αυτή τη στιγμή…$"

PetalburgCity_Gym_Text_EnterAccuracyRoom:
	.string "“ACCURACY ROOM,” γράφει η ταμπέλα.\p"
	.string "Θέλεις να περάσεις;$"

PetalburgCity_Gym_Text_EnterConfusionRoom:
	.string "“CONFUSION ROOM,” γράφει η ταμπέλα.\p"
	.string "Θέλεις να περάσεις;$"

PetalburgCity_Gym_Text_EnterDefenseRoom:
	.string "“DEFENSE ROOM,” γράφει η ταμπέλα.\p"
	.string "Θέλεις να περάσεις;$"

PetalburgCity_Gym_Text_EnterRecoveryRoom:
	.string "“RECOVERY ROOM,” γράφει η ταμπέλα.\p"
	.string "Θέλεις να περάσεις;$"

PetalburgCity_Gym_Text_EnterStrengthRoom:
	.string "“STRENGTH ROOM,” γράφει η ταμπέλα.\p"
	.string "Θέλεις να περάσεις;$"

PetalburgCity_Gym_Text_EnterOHKORoom:
	.string "“ONE-HIT KO ROOM,” γράφει η ταμπέλα.\p"
	.string "Θέλεις να περάσεις;$"

PetalburgCity_Gym_Text_EnterGymLeadersRoom:
	.string "“GYM LEADER'S ROOM\p"
	.string "“Δες από κοντά ποια POKéMON σε\n"
	.string "περιμένουν!” γράφει η ταμπέλα.\p"
	.string "Θέλεις να περάσεις;$"

PetalburgCity_Gym_Text_GymStatue:
	.string "PETALBURG CITY POKéMON GYM$"

PetalburgCity_Gym_Text_GymStatueCertified:
	.string "PETALBURG CITY POKéMON GYM\p"
	.string "ΠΙΣΤΟΠΟΙΗΜΕΝΟΙ TRAINERS ΤΟΥ NORMAN:\n"
	.string "{PLAYER}$"

PetalburgCity_Gym_Text_NormanPreRematch:
	.string "DAD: {PLAYER}…\n"
	.string "Είχα ένα προαίσθημα ότι θα έρθεις.\p"
	.string "Δεν θα αρνιόμουν ποτέ να \n"
	.string "δεχτώ μια πρόκληση από εσένα.\p"
	.string "Το καταλαβαίνεις, έτσι δεν είναι;\p"
	.string "Μέσα σε ένα GYM, δεν έχει σημασία\n"
	.string "ότι είμαστε γονιός και παιδί.\p"
	.string "…Όχι, ακριβώς επειδή είμαστε γονιός \n"
	.string "και παιδί, οφείλουμε ο ένας στον \l"
	.string "άλλον να βάλουμε τα δυνατά μας.\l"
	.string "Έτσι δεν είναι, {PLAYER};$"

PetalburgCity_Gym_Text_NormanRematchDefeat:
	.string "Εχ… Χαχα…\n"
	.string "Μάλλον το παράκανα λιγάκι…$"

PetalburgCity_Gym_Text_NormanPostRematch:
	.string "DAD: {PLAYER}…\n"
	.string "Ποιο είναι το όνειρό σου;\p"
	.string "Το όνειρό μου…\n"
	.string "Χαχαχα…\l"
	.string "Βασικά, έχει ήδη γίνει πραγματικότητα.$"

PetalburgCity_Gym_Text_NormanRematchNeedTwoMons:
	.string "DAD: {PLAYER}…\n"
	.string "Είχα ένα προαίσθημα ότι θα έρθεις.\p"
	.string "Δεν θα αρνιόμουν ποτέ να\n"
	.string "δεχτώ μια πρόκληση από εσένα.\p"
	.string "Το καταλαβαίνεις, έτσι δεν είναι;\p"
	.string "Μέσα σε ένα GYM, δεν έχει σημασία\n"
	.string "ότι είμαστε γονιός και παιδί.\p"
	.string "Χμ; Μισό λεπτό, {PLAYER}.\p"
	.string "Έχεις μόνο ένα POKéMON που είναι\n"
	.string "ικανό για μάχη;\p"
	.string "Συγγνώμη, αλλά θα πρέπει να έρθεις\n"
	.string "ξανά με τουλάχιστον δύο POKéMON.$"

