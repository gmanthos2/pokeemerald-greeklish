Route110_SeasideCyclingRoadSouthEntrance_MapScripts::
	.byte 0

Route110_SeasideCyclingRoadSouthEntrance_EventScript_Clerk::
	lock
	faceplayer
	msgbox Route110_SeasideCyclingRoadSouthEntrance_Text_GoAllOutOnCyclingRoad, MSGBOX_DEFAULT
	release
	end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_BikeCheck::
	lockall
	specialvar VAR_RESULT, GetPlayerAvatarBike
	goto_if_eq VAR_RESULT, 0, Route110_SeasideCyclingRoadSouthEntrance_EventScript_NoBike
	setflag FLAG_SYS_CYCLING_ROAD
	setvar VAR_TEMP_1, 1
	releaseall
	end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_NoBike::
	msgbox Route110_SeasideCyclingRoadSouthEntrance_Text_TooDangerousToWalk, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route110_SeasideCyclingRoadSouthEntrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

Route110_SeasideCyclingRoadSouthEntrance_Movement_PushPlayerBackFromCounter:
	walk_left
	step_end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_ClearCyclingRoad::
	lockall
	clearflag FLAG_SYS_CYCLING_ROAD
	setvar VAR_TEMP_1, 0
	releaseall
	end

Route110_SeasideCyclingRoadSouthEntrance_Text_GoAllOutOnCyclingRoad:
	.string "Στον CYCLING ROAD, μπορείς να\n"
	.string "τρέξεις όσο γρήγορα θέλεις.\p"
	.string "Είναι ωραίο να τρέχεις, αλλά \n"
	.string "προσπάθησε να μην τρακάρεις!$"

Route110_SeasideCyclingRoadSouthEntrance_Text_TooDangerousToWalk:
	.string "Συγγνώμη, δεν μπορείς να \n"
	.string "περπατήσεις στον CYCLING ROAD.\l"
	.string "Είναι πολύ επικίνδυνο.\p"
	.string "Σε παρακαλώ, έλα με ένα BIKE.$"

