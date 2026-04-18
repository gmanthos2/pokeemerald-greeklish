.set LOCALID_NURSE, 1
.set LOCALID_LANETTE, 4

FallarborTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FallarborTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_FALLARBOR_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

FallarborTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FallarborTown_PokemonCenter_1F_EventScript_Girl::
	msgbox FallarborTown_PokemonCenter_1F_Text_FossilManiacEdgeOfTown, MSGBOX_NPC
	end

FallarborTown_PokemonCenter_1F_EventScript_ExpertM::
	msgbox FallarborTown_PokemonCenter_1F_Text_PlantHardyTrees, MSGBOX_NPC
	end

FallarborTown_PokemonCenter_1F_EventScript_Lanette::
	lock
	faceplayer
	msgbox FallarborTown_PokemonCenter_1F_Text_LanetteGreeting, MSGBOX_DEFAULT
	closemessage
	switch VAR_FACING
	case DIR_NORTH, FallarborTown_PokemonCenter_1F_EventScript_LanetteExitNorth
	case DIR_WEST, FallarborTown_PokemonCenter_1F_EventScript_LanetteExitWest
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExitNorth::
	applymovement LOCALID_LANETTE, FallarborTown_PokemonCenter_1F_Movement_LanetteExitNorth
	waitmovement 0
	goto FallarborTown_PokemonCenter_1F_EventScript_LanetteExited
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExitWest::
	applymovement LOCALID_LANETTE, FallarborTown_PokemonCenter_1F_Movement_LanetteExitWest
	waitmovement 0
	goto FallarborTown_PokemonCenter_1F_EventScript_LanetteExited
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExited::
	playse SE_SLIDING_DOOR
	removeobject LOCALID_LANETTE
	clearflag FLAG_HIDE_LANETTES_HOUSE_LANETTE
	release
	end

FallarborTown_PokemonCenter_1F_Movement_LanetteExitNorth:
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

FallarborTown_PokemonCenter_1F_Movement_LanetteExitWest:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

FallarborTown_PokemonCenter_1F_Text_LanetteGreeting:
	.string "Α, γεια.\n"
	.string "Και εσύ είσαι…;\p"
	.string "Α, σε λένε {PLAYER}{KUN}.\n"
	.string "Βλέπω ότι είσαι TRAINER.\p"
	.string "Αυτό σημαίνει ότι χρησιμοποιείς το\n"
	.string "POKéMON Storage System που έφτιαξα.\p"
	.string "Το πώς έφτασα σε αυτό το συμπέρασμα\n"
	.string "είναι μια απλή παραγωγική διαδικασία.\p"
	.string "Μου μίλησες γιατί ήθελες να\n"
	.string "χρησιμοποιήσεις αυτό το PC.\p"
	.string "Α, συγγνώμη. Είμαι η LANETTE.\p"
	.string "Ειλικρινά, χαίρομαι που σε γνωρίζω--\n"
	.string "είναι υπέροχο που χρησιμοποιείς\l"
	.string "το Storage System.\p"
	.string "Αν μπορείς, έλα να με επισκεφτείς\n"
	.string "στο σπίτι μου.\l"
	.string "Το σπίτι μου είναι στην ROUTE 114.$"

FallarborTown_PokemonCenter_1F_Text_FossilManiacEdgeOfTown:
	.string "Αναρωτιέμαι πώς έμοιαζαν τα POKéMON\n"
	.string "πριν από πολύ, πολύ καιρό;\p"
	.string "Ίσως ο FOSSIL MANIAC στην άκρη της\n"
	.string "πόλης να ξέρει.$"

FallarborTown_PokemonCenter_1F_Text_PlantHardyTrees:
	.string "Στα χωράφια του FALLARBOR, φυτεύουμε\n"
	.string "δενδρύλλια ανθεκτικών δέντρων που \l"
	.string "ευδοκιμούν ακόμα και στην ηφαιστειακή\l"
	.string "στάχτη.$"

