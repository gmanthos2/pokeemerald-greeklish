.set LOCALID_CHALLENGE_BIKER, 21
.set LOCALID_RIVAL, 28
.set LOCALID_RIVAL_ON_BIKE, 29
.set LOCALID_BIRCH, 36

Route110_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Route110_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route110_OnFrame
	.byte 0

Route110_OnResume:
	special UpdateCyclingRoadState
	end

Route110_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	call_if_eq VAR_CYCLING_CHALLENGE_STATE, 1, Route110_EventScript_SaveCyclingMusic
	end

Route110_EventScript_SaveCyclingMusic::
	savebgm MUS_CYCLING
	return

Route110_OnFrame:
	map_script_2 VAR_CYCLING_CHALLENGE_STATE, 1, Route110_EventScript_BeginCylcingRoadChallenge
	.2byte 0

Route110_EventScript_BeginCylcingRoadChallenge::
	special Special_BeginCyclingRoadChallenge
	setvar VAR_CYCLING_CHALLENGE_STATE, 2
	return

Route110_EventScript_AquaGrunt1::
	lock
	faceplayer
	msgbox Route110_Text_WeCantTalkAboutAquaActivities, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_AquaGrunt2::
	lock
	faceplayer
	msgbox Route110_Text_KickUpARuckus, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_AquaGrunt3::
	lock
	faceplayer
	msgbox Route110_Text_MyFirstJobInAqua, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_AquaGrunt4::
	lock
	faceplayer
	msgbox Route110_Text_AquaActionsBringSmiles, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_Boy1::
	msgbox Route110_Text_RideBikeAtFullSpeed, MSGBOX_NPC
	end

Route110_EventScript_CyclingGirl1::
	msgbox Route110_Text_HairStreamsBehindMe, MSGBOX_NPC
	end

Route110_EventScript_CyclingGuy1::
	msgbox Route110_Text_YouGotBikeFromRydel, MSGBOX_NPC
	end

Route110_EventScript_OldMan::
	msgbox Route110_Text_TwoRoads, MSGBOX_NPC
	end

Route110_EventScript_OldWoman::
	msgbox Route110_Text_WalkOnTheLowRoad, MSGBOX_NPC
	end

Route110_EventScript_CyclingGuy2::
	msgbox Route110_Text_BikeTechniques, MSGBOX_NPC
	end

Route110_EventScript_Boy2::
	msgbox Route110_Text_WhichShouldIChoose, MSGBOX_NPC
	end

Route110_EventScript_SlateportCitySign::
	msgbox Route110_Text_SlateportCitySign, MSGBOX_SIGN
	end

Route110_EventScript_CyclingRoadSign::
	msgbox Route110_Text_CyclingRoadSign, MSGBOX_SIGN
	end

Route110_EventScript_VandalizedSign::
	msgbox Route110_Text_AquaWasHere, MSGBOX_SIGN
	end

Route110_EventScript_Route103Sign::
	msgbox Route110_Text_Route103Sign, MSGBOX_SIGN
	end

Route110_EventScript_SeasideParkingSign::
	msgbox Route110_Text_SeasideParkingSign, MSGBOX_SIGN
	end

Route110_EventScript_MauvilleCitySign::
	msgbox Route110_Text_MauvilleCitySign, MSGBOX_SIGN
	end

Route110_EventScript_TrainerTipsPrlzSleep::
	msgbox Route110_Text_TrainerTipsPrlzSleep, MSGBOX_SIGN
	end

Route110_EventScript_TrainerTipsRegisterItems::
	msgbox Route110_Text_TrainerTipsRegisterItems, MSGBOX_SIGN
	end

Route110_EventScript_TrickHouseSign::
	msgbox Route110_Text_TrickHouseSign, MSGBOX_SIGN
	end

Route110_EventScript_CyclingRoadResultsSign::
	lockall
	specialvar VAR_RESULT, GetRecordedCyclingRoadResults
	goto_if_eq VAR_RESULT, FALSE, Route110_EventScript_NoRecordSet
	msgbox Route110_Text_BestRecord, MSGBOX_DEFAULT
	releaseall
	end

Route110_EventScript_NoRecordSet::
	msgbox Route110_Text_ThereIsNoRecord, MSGBOX_DEFAULT
	releaseall
	end

Route110_EventScript_ChallengeGuy::
	lock
	faceplayer
	specialvar VAR_RESULT, GetPlayerAvatarBike
	goto_if_eq VAR_RESULT, 1, Route110_EventScript_PlayerRidingAcroBike
	goto_if_eq VAR_CYCLING_CHALLENGE_STATE, 0, Route110_EventScript_PlayerNotRidingBike
	msgbox Route110_Text_AlwaysAimHigher, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_PlayerNotRidingBike::
	msgbox Route110_Text_RatedForNumberOfCollisions, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_PlayerRidingAcroBike::
	msgbox Route110_Text_AcroBikesDoNotQualify, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_Edward::
	trainerbattle_single TRAINER_EDWARD, Route110_Text_EdwardIntro, Route110_Text_EdwardDefeated
	msgbox Route110_Text_EdwardPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Jaclyn::
	trainerbattle_single TRAINER_JACLYN, Route110_Text_JaclynIntro, Route110_Text_JaclynDefeated
	msgbox Route110_Text_JaclynPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Edwin::
	trainerbattle_single TRAINER_EDWIN_1, Route110_Text_EdwinIntro, Route110_Text_EdwinDefeated, Route110_EventScript_EdwinRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route110_EventScript_EdwinRematch
	msgbox Route110_Text_EdwinPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_EdwinRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_EdwinRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_EDWIN_1
	release
	end

Route110_EventScript_EdwinRematch::
	trainerbattle_rematch TRAINER_EDWIN_1, Route110_Text_EdwinRematchIntro, Route110_Text_EdwinRematchDefeated
	msgbox Route110_Text_EdwinRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Dale::
	trainerbattle_single TRAINER_DALE, Route110_Text_DaleIntro, Route110_Text_DaleDefeated
	msgbox Route110_Text_DalePostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Jacob::
	trainerbattle_single TRAINER_JACOB, Route110_Text_JacobIntro, Route110_Text_JacobDefeated
	msgbox Route110_Text_JacobPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Anthony::
	trainerbattle_single TRAINER_ANTHONY, Route110_Text_AnthonyIntro, Route110_Text_AnthonyDefeated
	msgbox Route110_Text_AnthonyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Benjamin::
	trainerbattle_single TRAINER_BENJAMIN_1, Route110_Text_BenjaminIntro, Route110_Text_BenjaminDefeated, Route110_EventScript_BenjaminRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route110_EventScript_BenjaminRematch
	msgbox Route110_Text_BenjaminPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_BenjaminRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_BenjaminRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_BENJAMIN_1
	release
	end

Route110_EventScript_BenjaminRematch::
	trainerbattle_rematch TRAINER_BENJAMIN_1, Route110_Text_BenjaminRematchIntro, Route110_Text_BenjaminRematchDefeated
	msgbox Route110_Text_BenjaminRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Jasmine::
	trainerbattle_single TRAINER_JASMINE, Route110_Text_JasmineIntro, Route110_Text_JasmineDefeated
	msgbox Route110_Text_JasminePostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Abigail::
	trainerbattle_single TRAINER_ABIGAIL_1, Route110_Text_AbigailIntro, Route110_Text_AbigailDefeated, Route110_EventScript_AbigailRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route110_EventScript_AbigailRematch
	msgbox Route110_Text_AbigailPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_AbigailRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_AbigailRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ABIGAIL_1
	release
	end

Route110_EventScript_AbigailRematch::
	trainerbattle_rematch TRAINER_ABIGAIL_1, Route110_Text_AbigailRematchIntro, Route110_Text_AbigailRematchDefeated
	msgbox Route110_Text_AbigailRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Isabel::
	trainerbattle_single TRAINER_ISABEL_1, Route110_Text_IsabelIntro, Route110_Text_IsabelDefeated, Route110_EventScript_IsabelRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route110_EventScript_IsabelRematch
	msgbox Route110_Text_IsabelPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_IsabelRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_IsabelRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ISABEL_1
	release
	end

Route110_EventScript_IsabelRematch::
	trainerbattle_rematch TRAINER_ISABEL_1, Route110_Text_IsabelRematchIntro, Route110_Text_IsabelRematchDefeated
	msgbox Route110_Text_IsabelRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Timmy::
	trainerbattle_single TRAINER_TIMMY, Route110_Text_TimmyIntro, Route110_Text_TimmyDefeated
	msgbox Route110_Text_TimmyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Unused::
	end

Route110_EventScript_Kaleb::
	trainerbattle_single TRAINER_KALEB, Route110_Text_KalebIntro, Route110_Text_KalebDefeated
	msgbox Route110_Text_KalebPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Joseph::
	trainerbattle_single TRAINER_JOSEPH, Route110_Text_JosephIntro, Route110_Text_JosephDefeated
	msgbox Route110_Text_JosephPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Alyssa::
	trainerbattle_single TRAINER_ALYSSA, Route110_Text_AlyssaIntro, Route110_Text_AlyssaDefeated
	msgbox Route110_Text_AlyssaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_CyclingChallengeEnd::
	lockall
	applymovement LOCALID_CHALLENGE_BIKER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	call Route110_EventScript_CyclingChallengeResults
	releaseall
	end

Route110_EventScript_CyclingChallengeResults::
	special FinishCyclingRoadChallenge
	msgbox Route110_Text_CyclingChallengeResultSummary, MSGBOX_DEFAULT
	switch VAR_RESULT
	case 10, Route110_EventScript_ChallengeReactionBest
	case 9, Route110_EventScript_ChallengeReactionGood
	case 8, Route110_EventScript_ChallengeReactionGood
	case 7, Route110_EventScript_ChallengeReactionGood
	case 6, Route110_EventScript_ChallengeReactionOk
	case 5, Route110_EventScript_ChallengeReactionOk
	case 4, Route110_EventScript_ChallengeReactionOk
	case 3, Route110_EventScript_ChallengeReactionBad
	case 2, Route110_EventScript_ChallengeReactionBad
	case 1, Route110_EventScript_ChallengeReactionBad
	case 0, Route110_EventScript_ChallengeReactionWorst
	end

Route110_EventScript_ChallengeReactionBest::
	msgbox Route110_Text_ChallengeReactionBest, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route110_EventScript_ChallengeReactionGood::
	msgbox Route110_Text_ChallengeReactionGood, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route110_EventScript_ChallengeReactionOk::
	msgbox Route110_Text_ChallengeReactionOk, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route110_EventScript_ChallengeReactionBad::
	msgbox Route110_Text_ChallengeReactionBad, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route110_EventScript_ChallengeReactionWorst::
	msgbox Route110_Text_ChallengeReactionWorst, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route110_EventScript_EndChallenge::
	setvar VAR_CYCLING_CHALLENGE_STATE, 3
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

Route110_EventScript_RivalTrigger1::
	setvar VAR_0x8008, 1
	goto Route110_EventScript_RivalScene
	end

Route110_EventScript_RivalTrigger2::
	setvar VAR_0x8008, 2
	goto Route110_EventScript_RivalScene
	end

Route110_EventScript_RivalTrigger3::
	setvar VAR_0x8008, 3
	goto Route110_EventScript_RivalScene
	end

Route110_EventScript_RivalScene::
	lockall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Route110_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, Route110_EventScript_PlayBrendanMusic
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	delay 30
	call_if_eq VAR_0x8008, 1, Route110_EventScript_RivalApproachPlayer1
	call_if_eq VAR_0x8008, 2, Route110_EventScript_RivalApproachPlayer2
	call_if_eq VAR_0x8008, 3, Route110_EventScript_RivalApproachPlayer3
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route110_EventScript_MayBattle
	goto_if_eq VAR_RESULT, FEMALE, Route110_EventScript_BrendanBattle
	releaseall
	end

Route110_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

Route110_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

Route110_EventScript_MayBattle::
	msgbox Route110_Text_MayLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route110_EventScript_MayBattleTreecko
	case 1, Route110_EventScript_MayBattleTorchic
	case 2, Route110_EventScript_MayBattleMudkip
	end

Route110_EventScript_MayBattleTreecko::
	trainerbattle_no_intro TRAINER_MAY_ROUTE_110_TREECKO, Route110_Text_MayDefeated
	goto Route110_EventScript_MayDefeated
	end

Route110_EventScript_MayBattleTorchic::
	trainerbattle_no_intro TRAINER_MAY_ROUTE_110_TORCHIC, Route110_Text_MayDefeated
	goto Route110_EventScript_MayDefeated
	end

Route110_EventScript_MayBattleMudkip::
	trainerbattle_no_intro TRAINER_MAY_ROUTE_110_MUDKIP, Route110_Text_MayDefeated
	goto Route110_EventScript_MayDefeated
	end

Route110_EventScript_MayDefeated::
	msgbox Route110_Text_MayTakeThis, MSGBOX_DEFAULT
	call Route110_EventScript_GiveItemfinder
	msgbox Route110_Text_MayExplainItemfinder, MSGBOX_DEFAULT
	goto Route110_EventScript_RivalExit
	end

Route110_EventScript_BrendanBattle::
	msgbox Route110_Text_BrendanLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route110_EventScript_BrendanBattleTreecko
	case 1, Route110_EventScript_BrendanBattleTorchic
	case 2, Route110_EventScript_BrendanBattleMudkip
	end

Route110_EventScript_BrendanBattleTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_110_TREECKO, Route110_Text_BrendanDefeated
	goto Route110_EventScript_BrendanDefeated
	end

Route110_EventScript_BrendanBattleTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_110_TORCHIC, Route110_Text_BrendanDefeated
	goto Route110_EventScript_BrendanDefeated
	end

Route110_EventScript_BrendanBattleMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_110_MUDKIP, Route110_Text_BrendanDefeated
	goto Route110_EventScript_BrendanDefeated
	end

Route110_EventScript_BrendanDefeated::
	msgbox Route110_Text_BrendanTakeThis, MSGBOX_DEFAULT
	call Route110_EventScript_GiveItemfinder
	msgbox Route110_Text_BrendanExplainItemfinder, MSGBOX_DEFAULT
	goto Route110_EventScript_RivalExit
	end

Route110_EventScript_GiveItemfinder::
	giveitem ITEM_ITEMFINDER
	return

Route110_EventScript_RivalExit::
	closemessage
	call_if_eq VAR_0x8008, 1, Route110_EventScript_MoveRival1
	call_if_eq VAR_0x8008, 2, Route110_EventScript_MoveRival2
	call_if_eq VAR_0x8008, 3, Route110_EventScript_MoveRival3
	setobjectmovementtype LOCALID_RIVAL, MOVEMENT_TYPE_FACE_RIGHT
	setobjectmovementtype LOCALID_RIVAL_ON_BIKE, MOVEMENT_TYPE_FACE_RIGHT
	removeobject LOCALID_RIVAL
	addobject LOCALID_RIVAL_ON_BIKE
	delay 45
	call_if_eq VAR_0x8008, 1, Route110_EventScript_RivalExit1
	call_if_eq VAR_0x8008, 2, Route110_EventScript_RivalExit2
	call_if_eq VAR_0x8008, 3, Route110_EventScript_RivalExit3
	removeobject LOCALID_RIVAL_ON_BIKE
	setvar VAR_ROUTE110_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

Route110_EventScript_RivalApproachPlayer1::
	applymovement LOCALID_RIVAL, Route110_Movement_RivalApproachPlayer1
	waitmovement 0
	return

Route110_EventScript_RivalApproachPlayer2::
	applymovement LOCALID_RIVAL, Route110_Movement_RivalApproachPlayer2
	waitmovement 0
	return

Route110_EventScript_RivalApproachPlayer3::
	applymovement LOCALID_RIVAL, Route110_Movement_RivalApproachPlayer3
	waitmovement 0
	return

Route110_EventScript_RivalExit1::
	applymovement LOCALID_RIVAL_ON_BIKE, Route110_Movement_RivalExit1
	waitmovement 0
	return

Route110_EventScript_RivalExit2::
	applymovement LOCALID_RIVAL_ON_BIKE, Route110_Movement_RivalExit2
	waitmovement 0
	return

Route110_EventScript_RivalExit3::
	applymovement LOCALID_RIVAL_ON_BIKE, Route110_Movement_RivalExit3
	waitmovement 0
	return

Route110_EventScript_MoveRival1::
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 33, 55
	return

Route110_EventScript_MoveRival2::
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 34, 55
	return

Route110_EventScript_MoveRival3::
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 35, 55
	return

Route110_Movement_RivalApproachPlayer1:
	walk_down
	walk_left
	walk_in_place_faster_down
	step_end

Route110_Movement_RivalApproachPlayer2:
	walk_down
	step_end

Route110_Movement_RivalApproachPlayer3:
	walk_down
	walk_right
	walk_in_place_faster_down
	step_end

Route110_Movement_RivalExit1:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route110_Movement_RivalExit2:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_down
	step_end

Route110_Movement_RivalExit3:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route110_EventScript_BirchScene1::
	lockall
	setvar VAR_0x8008, 1
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene2::
	lockall
	setvar VAR_0x8008, 2
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene3::
	lockall
	setvar VAR_0x8008, 3
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene4::
	lockall
	setvar VAR_0x8008, 4
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene::
	addobject LOCALID_BIRCH
	applymovement LOCALID_BIRCH, Route110_Movement_BirchEntrance
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_BIRCH, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_BIRCH, Common_Movement_Delay48
	waitmovement 0
	call_if_eq VAR_0x8008, 1, Route110_EventScript_BirchApproachPlayer1
	call_if_eq VAR_0x8008, 2, Route110_EventScript_BirchApproachPlayer2
	call_if_eq VAR_0x8008, 3, Route110_EventScript_BirchApproachPlayer3
	call_if_eq VAR_0x8008, 4, Route110_EventScript_BirchApproachPlayer4
	msgbox Route110_Text_ImagineSeeingYouHere, MSGBOX_DEFAULT
	closemessage
	delay 20
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 10
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 20
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	msgbox Route110_Text_HeardYouInstallMatchCall, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route110_Text_RegisteredBirchInPokenav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
	msgbox Route110_Text_KeepAnEyeOutForRival, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 1, Route110_EventScript_BirchExit1
	call_if_eq VAR_0x8008, 2, Route110_EventScript_BirchExit2
	call_if_eq VAR_0x8008, 3, Route110_EventScript_BirchExit3
	call_if_eq VAR_0x8008, 4, Route110_EventScript_BirchExit4
	removeobject LOCALID_BIRCH
	setvar VAR_REGISTER_BIRCH_STATE, 2
	releaseall
	end

Route110_EventScript_BirchApproachPlayer1::
	applymovement LOCALID_BIRCH, Route110_Movement_BirchApproachPlayer1
	waitmovement 0
	return

Route110_EventScript_BirchApproachPlayer2::
	applymovement LOCALID_BIRCH, Route110_Movement_BirchApproachPlayer2
	waitmovement 0
	return

Route110_EventScript_BirchApproachPlayer3::
	applymovement LOCALID_BIRCH, Route110_Movement_BirchApproachPlayer3
	waitmovement 0
	return

Route110_EventScript_BirchApproachPlayer4::
	applymovement LOCALID_BIRCH, Route110_Movement_BirchApproachPlayer4
	waitmovement 0
	return

Route110_EventScript_BirchExit1::
	applymovement LOCALID_BIRCH, Route110_Movement_BirchExit1
	waitmovement 0
	return

Route110_EventScript_BirchExit2::
	applymovement LOCALID_BIRCH, Route110_Movement_BirchExit2
	waitmovement 0
	return

Route110_EventScript_BirchExit3::
	applymovement LOCALID_BIRCH, Route110_Movement_BirchExit3
	waitmovement 0
	return

Route110_EventScript_BirchExit4::
	applymovement LOCALID_BIRCH, Route110_Movement_BirchExit4
	waitmovement 0
	return

Route110_Movement_BirchEntrance:
	walk_down
	walk_down
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer1:
	walk_down
	walk_left
	walk_left
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer2:
	walk_down
	walk_left
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer3:
	walk_down
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer4:
	walk_down
	walk_right
	walk_down
	step_end

Route110_Movement_BirchExit1:
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

Route110_Movement_BirchExit2:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route110_Movement_BirchExit3:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route110_Movement_BirchExit4:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route110_Text_WeCantTalkAboutAquaActivities:
	.string "Οι δραστηριότητες της TEAM AQUA…\n"
	.string "Δεν μπορούμε να μιλήσουμε \l"
	.string "για αυτές ακόμα.$"

Route110_Text_KickUpARuckus:
	.string "Θέλω να πάω στη SLATEPORT και\n"
	.string "να κάνω χαμό!$"

Route110_Text_MyFirstJobInAqua:
	.string "Αυτή είναι η πρώτη μου δουλειά\n"
	.string "αφού μπήκα στην TEAM AQUA. \l"
	.string "Είναι λίγο τρομακτικό.$"

Route110_Text_AquaActionsBringSmiles:
	.string "Οι δράσεις της TEAM AQUA πρέπει\n"
	.string "να φέρνουν χαμόγελα στα \l"
	.string "πρόσωπα των ανθρώπων!$"

Route110_Text_MayLetsBattle:
	.string "MAY: Γεια, {PLAYER}{KUN}, καιρό\n"
	.string "έχουμε να τα πούμε!\p"
	.string "Όσο έψαχνα για άλλα POKéMON, τα\n"
	.string "POKéMON μου δυνάμωσαν.\p"
	.string "Οπότε…\n"
	.string "Τι θα έλεγες για μια μικρή\l"
	.string "μάχη;$"

Route110_Text_MayDefeated:
	.string "Ουπς!\n"
	.string "Είσαι καλύτερη απ' ό,τι περίμενα!$"

Route110_Text_MayTakeThis:
	.string "MAY: {PLAYER}{KUN}, ήσουν\n"
	.string "απασχολημένο με προπόνηση, \l"
	.string "έτσι δεν είναι;\p"
	.string "Νομίζω ότι αξίζεις μια\n"
	.string "ανταμοιβή! \l"
	.string "Αυτό είναι από εμένα!$"

Route110_Text_MayExplainItemfinder:
	.string "MAY: Αυτό είναι ένα ITEMFINDER.\p"
	.string "Δοκίμασέ το. Αν υπάρχει κάποιο\n"
	.string "αντικείμενο που δεν είναι ορατό,\l"
	.string "βγάζει έναν ήχο.\p"
	.string "Εντάξει, {PLAYER}{KUN}, ας\n"
	.string "συναντηθούμε ξανά!\p"
	.string "Ξέρω ότι ακούγεται λίγο ανόητο\n"
	.string "από εμένα, αλλά νομίζω ότι\l"
	.string "πρέπει να προπονηθείς πολύ\l"
	.string "περισσότερο για την επόμενη\l"
	.string "φορά.$"

Route110_Text_BrendanLetsBattle:
	.string "BRENDAN: Γεια σου, {PLAYER}.\n"
	.string "Ώστε εδώ ήσουν.\l"
	.string "Πώς πάει;\p"
	.string "Μεγαλώνεις τα POKéMON σου;\n"
	.string "Θα το ελέγξω για σένα.$"

Route110_Text_BrendanDefeated:
	.string "Χμμ…\n"
	.string "Είσαι αρκετά καλό.$"

Route110_Text_BrendanTakeThis:
	.string "BRENDAN: {PLAYER}, προπονήθηκες\n"
	.string "χωρίς να το καταλάβω…\p"
	.string "Αρκετά καλά!\n"
	.string "Ορίστε, πάρε αυτό.$"

Route110_Text_BrendanExplainItemfinder:
	.string "BRENDAN: Αυτό είναι ένα\n"
	.string "ITEMFINDER.\p"
	.string "Χρησιμοποίησέ το για να\n"
	.string "ψάξεις για αντικείμενα που\l"
	.string "δεν είναι ορατά.\p"
	.string "Αν νιώσει κάτι, βγάζει\n"
	.string "έναν ήχο.\p"
	.string "Τέλος πάντων, πάω να ψάξω για\n"
	.string "νέα POKéMON.$"

Route110_Text_RideBikeAtFullSpeed:
	.string "Δεν θα ήταν υπέροχο να\n"
	.string "οδηγείς ένα BIKE με πλήρη\l"
	.string "ταχύτητα στον CYCLING ROAD;$"

Route110_Text_HairStreamsBehindMe:
	.string "Πώς σου φαίνεται ο τρόπος που\n"
	.string "τα μαύρα σαν κοράκι μαλλιά μου\l"
	.string "ανεμίζουν πίσω μου;\p"
	.string "Μάκρυνα τα μαλλιά μου μόνο για\n"
	.string "αυτό.$"

Route110_Text_YouGotBikeFromRydel:
	.string "Ω, γεια, έχεις πάρει αυτό το\n"
	.string "BIKE από τον RYDEL!\p"
	.string "Ω, είναι προφανές.\n"
	.string "Το γράφει πάνω στο ποδήλατό σου…\p"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\n"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\p"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\n"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\p"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\n"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\p"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\n"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\p"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL…\n"
	.string "Αυτό το όνομα είναι παντού.\p"
	.string "Πρέπει να το κυκλοφορείς \n"
	.string "παντού--είναι καλή διαφήμιση!$"

Route110_Text_TwoRoads:
	.string "Οι δύο δρόμοι, ένας πάνω, ένας\n"
	.string "κάτω…\p"
	.string "Ένας δρόμος για ανθρώπους και\n"
	.string "ένας για POKéMON. Ίσως αυτό να\l"
	.string "είναι σωστό και δίκαιο.$"

Route110_Text_WalkOnTheLowRoad:
	.string "Δεν έχω BIKE, οπότε θα κάνω\n"
	.string "μια χαλαρή βόλτα στον κάτω\l"
	.string "δρόμο.$"

Route110_Text_BikeTechniques:
	.string "Μαθαίνοντας τεχνικές θα κάνεις.\n"
	.string "την οδήγηση του BIKE πιο\l"
	.string "διασκεδαστική\p"
	.string "Υπάρχουν μερικά μέρη που\n"
	.string "μπορείς να φτάσεις μόνο\l"
	.string "χρησιμοποιώντας μια τεχνική\l"
	.string "BIKE.$"

Route110_Text_WhichShouldIChoose:
	.string "Ποιο να διαλέξω;\p"
	.string "Να πάω κατευθείαν στη MAUVILLE \n"
	.string "μέσω του CYCLING ROAD, ή να \l"
	.string "πάρω τον κάτω δρόμο και να \l"
	.string "ψάξω POKéMON;$"

Route110_Text_CyclingChallengeResultSummary:
	.string "Αριθμός συγκρούσεων:\n"
	.string "… … {STR_VAR_1}!\p"
	.string "Συνολικός χρόνος:\n"
	.string "… … {STR_VAR_2}!$"

Route110_Text_ChallengeReactionBest:
	.string "Μπράβο! Υπέροχη επίδειξη!\p"
	.string "Η αγάπη σου για την ποδηλασία\n"
	.string "προέρχεται βαθιά από την καρδιά \l"
	.string "σου.\l"
	.string "Με συγκλόνισες!$"

Route110_Text_ChallengeReactionGood:
	.string "Η τεχνική σου είναι\n"
	.string "αξιοσημείωτη.\p"
	.string "Σου προτείνω να επιταχύνεις\n"
	.string "λίγο, αποφεύγοντας παράλληλα τις\l"
	.string "συγκρούσεις.$"

Route110_Text_ChallengeReactionOk:
	.string "Θα σε θεωρούσα ένα έργο υπό\n"
	.string "εξέλιξη.\p"
	.string "Ωστόσο, ελπίζω να μην\n"
	.string "ξεχάσεις την απόλυτη ευχαρίστηση\l"
	.string "της ποδηλασίας.$"

Route110_Text_ChallengeReactionBad:
	.string "Καλέ μου… Οι ικανότητές\n"
	.string "σου στην ποδηλασία\l"
	.string "είναι τρομακτικές.\p"
	.string "Σίγουρα, χρειάζεσαι πολύ\n"
	.string "περισσότερη εξάσκηση.$"

Route110_Text_ChallengeReactionWorst:
	.string "…Είμαι άφωνος…\p"
	.string "Ίσως να μην είσαι\n"
	.string "έτοιμο για αυτή την\l"
	.string "ατυχή ποδηλασία.\p"
	.string "Είναι καλύτερα να\n"
	.string "επιστρέψεις αυτό το BIKE\l"
	.string "στον RYDEL.$"

Route110_Text_RatedForNumberOfCollisions:
	.string "Αυτός είναι ο CYCLING ROAD.\p"
	.string "Αν οδηγούσες από MAUVILLE για\n"
	.string "SLATEPORT σε ένα MACH BIKE,\l"
	.string "θα βαθμολογούσουν \l"
	.string "για τον αριθμό\l"
	.string "συγκρούσεων\l"
	.string "και το συνολικό χρόνο σου.$"

Route110_Text_AlwaysAimHigher:
	.string "Ανεξάρτητα από τα αποτελέσματα,\n"
	.string "βασίζομαι στο να δω \l"
	.string "περισσότερες προσπάθειες. \l"
	.string "Να στοχεύεις ψηλότερα!$"

Route110_Text_AcroBikesDoNotQualify:
	.string "Σε αυτόν τον CYCLING ROAD,\n"
	.string "αυτοί που οδηγούν MACH BIKES.\l"
	.string "βαθμολογούνται για τις συγκρούσεις\l"
	.string "και τους χρόνους τους.\p"
	.string "Οι ACRO BIKES δεν βαθμολογούνται.\n"
	.string "Είναι εύκολες στο στρίψιμο, οπότε \l"
	.string "δεν είναι δίκαιο.$"

Route110_Text_SlateportCitySign:
	.string "ROUTE 110\n"
	.string "{DOWN_ARROW} SLATEPORT CITY$"

Route110_Text_CyclingRoadSign:
	.string "SEASIDE CYCLING ROAD$"

Route110_Text_AquaWasHere:
	.string "“TEAM AQUA ήταν εδώ!”\p"
	.string "Κάποιος το έγραψε στην πινακίδα,\n"
	.string "αλλά κάποιος άλλος έγραψε από\l"
	.string "πάνω του.\p"
	.string "“TEAM MAGMA είναι οι καλύτεροι!” \n"
	.string "λέει τώρα.$"

Route110_Text_Route103Sign:
	.string "ROUTE 110\n"
	.string "{LEFT_ARROW} ROUTE 103$"

Route110_Text_SeasideParkingSign:
	.string "SEASIDE PARKING$"

Route110_Text_MauvilleCitySign:
	.string "ROUTE 110\n"
	.string "{UP_ARROW} MAUVILLE CITY$"

Route110_Text_TrainerTipsPrlzSleep:
	.string "ΣΥΜΒΟΥΛΕΣ TRAINER\p"
	.string "Ο αντίπαλος μπορεί να\n"
	.string "καταστεί ανυπεράσπιστος αν\l"
	.string "παραλύσει ή κοιμηθεί.\p"
	.string "Είναι μια σημαντική τεχνική\n"
	.string "για τις μάχες POKéMON.$"

Route110_Text_TrainerTipsRegisterItems:
	.string "ΣΥΜΒΟΥΛΕΣ TRAINER\p"
	.string "Τα αντικείμενα στo BAG\n"
	.string "μπορούν να αναδιοργανωθούν\l"
	.string "πατώντας το κουμπί SELECT.$"

Route110_Text_TrickHouseSign:
	.string "“Τρία βήματα {RIGHT_ARROW} και δύο {UP_ARROW}\n"
	.string "για στο θαυμαστό TRICK HOUSE.”$"

Route110_Text_BestRecord:
	.string "ΤΟ ΚΑΛΥΤΕΡΟ ΡΕΚΟΡ ΩΣ ΤΩΡΑ…\p"
	.string "Αρ. συγκρούσεων: {STR_VAR_1}\p"
	.string "Χρόνος που πέρασε: {STR_VAR_2}$"

Route110_Text_ThereIsNoRecord:
	.string "ΤΟ ΚΑΛΥΤΕΡΟ ΡΕΚΟΡ ΕΩΣ ΤΩΡΑ…\p"
	.string "Κανείς δεν φαίνεται να έχει\n"
	.string "δοκιμάσει. \l"
	.string "Δεν υπάρχει ρεκόρ…$"

Route110_Text_ImagineSeeingYouHere:
	.string "PROF. BIRCH: Ω, {PLAYER}{KUN}!\n"
	.string "Τι έκπληξη να σε βλέπω εδώ!\p"
	.string "Και πού μπορεί να είναι το\n"
	.string "{RIVAL} μου;$"

Route110_Text_HeardYouInstallMatchCall:
	.string "Α, κατάλαβα!\n"
	.string "Είστε χωριστά.\l"
	.string "Εντάξει, δεν πειράζει.\p"
	.string "Α, ναι, άκουσα ότι στο POKéNAV\n"
	.string "σου εγκαταστάθηκε το  σύστημα\l"
	.string "MATCH CALL.\p"
	.string "Λοιπόν, πρέπει να στο\n"
	.string "καταχωρήσω και στο δικό \l"
	.string "μου POKéNAV.\p"
	.string "Έτσι, ακόμα κι όταν \n"
	.string "είμαστε χώρια, θα \n"
	.string "ελέγχω το POKéDEX σου \l"
	.string "όποτε θες.\p"
	.string "… … … … … …$"

Route110_Text_RegisteredBirchInPokenav:
	.string "Καταχωρίστηκε ο \n"
	.string "PROF. BIRCH στο POKéNAV.$"

Route110_Text_KeepAnEyeOutForRival:
	.string "PROF. BIRCH: {PLAYER}{KUN}…\p"
	.string "Σε παρακαλώ, να ρίχνεις\n"
	.string "μια ματιά στο {RIVAL}.\n"
	.string "… … … … … …\p"
	.string "Λοιπόν, πρέπει να φύγω τώρα.\n"
	.string "Τα λέμε,\l"
	.string "{PLAYER}{KUN}!$"

