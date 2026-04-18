.set LOCALID_NURSE, 1

LavaridgeTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

LavaridgeTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_LAVARIDGE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Youngster::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_HotSpringCanInvigorate, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Woman::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_TrainersPokemonSpendTimeTogether, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_TrainersShouldRestToo, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_Text_TrainersPokemonSpendTimeTogether:
	.string "Νομίζω πως τα POKéMON έρχονται πιο \n"
	.string "κοντά στους TRAINERS τους αν περνούν \l"
	.string "χρόνο μαζί.\p"
	.string "Όσο περισσότερο τόσο το καλύτερο.\n"
	.string "Αυτό νομίζω.$"

LavaridgeTown_PokemonCenter_1F_Text_HotSpringCanInvigorate:
	.string "Είναι κάπως μαγικό πώς \n"
	.string "μόνο και μόνο το να κάθεσαι \l"
	.string "σε μια πισίνα με θερμές πηγές μπορεί \l"
	.string "να σε αναζωογονήσει.\p"
	.string "Μακάρι να μπορούσα να αφήσω και\n"
	.string "το POKéMON μου.$"

LavaridgeTown_PokemonCenter_1F_Text_TrainersShouldRestToo:
	.string "Χοχοχο! Έι, παιδί, μπορείς να φτάσεις\n"
	.string "τις θερμές πηγές από εδώ.\p"
	.string "Αν τα POKéMON ξεκουράζονται, το\n"
	.string "ίδιο πρέπει να κάνουν και οι TRAINERS.$"

