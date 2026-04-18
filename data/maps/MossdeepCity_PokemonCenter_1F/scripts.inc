.set LOCALID_NURSE, 1

MossdeepCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

MossdeepCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_MOSSDEEP_CITY
	end

MossdeepCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

MossdeepCity_PokemonCenter_1F_EventScript_Woman::
	msgbox MossdeepCity_PokemonCenter_1F_Text_GymLeaderDuoFormidable, MSGBOX_NPC
	end

MossdeepCity_PokemonCenter_1F_EventScript_Girl::
	msgbox MossdeepCity_PokemonCenter_1F_Text_AbilitiesMightChangeMoves, MSGBOX_NPC
	end

MossdeepCity_PokemonCenter_1F_Text_GymLeaderDuoFormidable:
	.string "Οι GYM LEADERS σε αυτή την πόλη \n"
	.string "είναι ένα τρομερό δίδυμο.\p"
	.string "Οι συνδυαστικές επιθέσεις τους \n"
	.string "είναι, ας πούμε, εξαιρετικές \l"
	.string "και ουάου!$"

MossdeepCity_PokemonCenter_1F_Text_AbilitiesMightChangeMoves:
	.string "Ανάλογα με τις ειδικές ικανότητες \n"
	.string "ενός POKéMON, κάποιες κινήσεις \l"
	.string "μπορεί να αλλάξουν ή \l"
	.string "να μην λειτουργήσουν καθόλου.$"

