EverGrandeCity_DrakesRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_DrakesRoom_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_DrakesRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_SidneysRoom_OnWarp
	.byte 0

@ Unused, Drake uses Sidneys identical OnWarp for some reason
EverGrandeCity_DrakesRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_DrakesRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_DrakesRoom_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_DrakesRoom_OnFrame:
	map_script_2 VAR_ELITE_4_STATE, 3, EverGrandeCity_DrakesRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_DrakesRoom_EventScript_WalkInCloseDoor::
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 4
	releaseall
	end

EverGrandeCity_DrakesRoom_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_DRAKE, EverGrandeCity_DrakesRoom_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_ELITE_4_STATE, 4, EverGrandeCity_DrakesRoom_EventScript_CloseDoor
	end

EverGrandeCity_DrakesRoom_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_DrakesRoom_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_DrakesRoom_EventScript_Drake::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_DRAKE, EverGrandeCity_DrakesRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_DrakesRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_DRAKE, EverGrandeCity_DrakesRoom_Text_Defeat
	goto EverGrandeCity_DrakesRoom_EventScript_Defeated
	end

EverGrandeCity_DrakesRoom_EventScript_PostBattleSpeech::
	msgbox EverGrandeCity_DrakesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_DrakesRoom_EventScript_Defeated::
	setvar VAR_0x8004, FANCOUNTER_DEFEATED_DRAKE
	special Script_TryGainNewFanFromCounter
	setflag FLAG_DEFEATED_ELITE_4_DRAKE
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_DrakesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_DrakesRoom_Text_IntroSpeech:
	.string "Είμαι ο τελευταίος της POKéMON LEAGUE\n"
	.string "ELITE FOUR, ο DRAKE o DRAGON master!\p"
	.string "Στη φυσική τους κατάσταση, τα POKéMON\n"
	.string "είναι άγρια ζωντανά όντα. Είναι ελεύθερα.\p"
	.string "Μερικές φορές μας δυσκολεύουν.\n"
	.string "Μερικές φορές μας βοηθούν.\p"
	.string "Για να παλέψουμε με τα POKéMON ως\n"
	.string "σύντροφοι, ξέρεις τι χρειάζεται;\p"
	.string "Ξέρεις τι είναι απαραίτητο;\p"
	.string "Αν δεν ξέρεις, τότε δεν θα\n"
	.string "επικρατήσεις ποτέ εναντίον μου!$"

EverGrandeCity_DrakesRoom_Text_Defeat:
	.string "Θαυμάσιο, πρέπει να ομολογήσω.$"

EverGrandeCity_DrakesRoom_Text_PostBattleSpeech:
	.string "Σου αξίζουν συγχαρητήρια που έφτασες\n"
	.string "μέχρι εδώ ως TRAINER των POKéMON.\p"
	.string "Φαίνεται πως ξέρεις τι χρειάζεται.\p"
	.string "Ναι, αυτό που χρειάζεται ένας TRAINER\n"
	.string "είναι μια ενάρετη καρδιά.\p"
	.string "Τα POKéMON αγγίζουν τις καλές καρδιές\n"
	.string "των TRAINERS και μαθαίνουν το σωστό.\p"
	.string "Αγγίζουν τις καλές καρδιές των\n"
	.string "TRAINERS και γίνονται δυνατά.\p"
	.string "Πήγαινε! Προχώρα μπροστά!\n"
	.string "Ο CHAMPION περιμένει!$"

