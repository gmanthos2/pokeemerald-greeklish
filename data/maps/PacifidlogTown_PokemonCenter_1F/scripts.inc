.set LOCALID_NURSE, 1

PacifidlogTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

PacifidlogTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_PACIFIDLOG_TOWN
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Girl::
	msgbox PacifidlogTown_PokemonCenter_1F_Text_WhatColorTrainerCard, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Woman::
	msgbox PacifidlogTown_PokemonCenter_1F_Text_OnColonyOfCorsola, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_EventScript_OldMan::
	msgbox PacifidlogTown_PokemonCenter_1F_Text_AncestorsLivedOnBoats, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_Text_WhatColorTrainerCard:
	.string "Τι χρώμα είναι η TRAINER CARD σου;\n"
	.string "Η δική μου είναι χάλκινη!$"

PacifidlogTown_PokemonCenter_1F_Text_OnColonyOfCorsola:
	.string "Η PACIFIDLOG TOWN επιπλέει πάνω από\n"
	.string "μια αποικία CORSOLA.\p"
	.string "Αν σου το έλεγα αυτό, θα με\n"
	.string "πίστευες;$"

PacifidlogTown_PokemonCenter_1F_Text_AncestorsLivedOnBoats:
	.string "Οι πρόγονοι των ανθρώπων στην\n"
	.string "PACIFIDLOG λέγεται ότι γεννήθηκαν\l"
	.string "σε βάρκες και μετά έζησαν και\l"
	.string "πέθαναν πάνω σε αυτές.\p"
	.string "Καταλαβαίνω ότι ζούσαν έτσι επειδή\n"
	.string "έψαχναν για κάτι.$"

