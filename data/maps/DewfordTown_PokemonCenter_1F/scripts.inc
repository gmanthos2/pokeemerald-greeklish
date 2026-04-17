.set LOCALID_NURSE, 1

DewfordTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

DewfordTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_DEWFORD_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

DewfordTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

DewfordTown_PokemonCenter_1F_EventScript_PokefanF::
	msgbox DewfordTown_PokemonCenter_1F_Text_StoneCavern, MSGBOX_NPC
	end

DewfordTown_PokemonCenter_1F_EventScript_Man::
	msgbox DewfordTown_PokemonCenter_1F_Text_FaintedMonCanUseHM, MSGBOX_NPC
	end

DewfordTown_PokemonCenter_1F_Text_StoneCavern:
	.string "Υπάρχει ένα πέτρινο σπήλαιο \n"
	.string "στην άκρη της πόλης.\p"
	.string "Έχω ακούσει ότι μπορείς να βρεις \n"
	.string "σπάνιες πέτρες εκεί.$"

DewfordTown_PokemonCenter_1F_Text_FaintedMonCanUseHM:
	.string "Ακόμα κι αν ένα POKéMON λιποθυμήσει\n"
	.string "και δεν μπορεί να πολεμήσει,\l"
	.string "ικανό να χρησιμοποιήσει κίνηση που\l"
	.string "έμαθε από HIDDEN MACHINE (HM).$"

