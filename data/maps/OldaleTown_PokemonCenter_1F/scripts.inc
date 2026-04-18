.set LOCALID_NURSE, 1

OldaleTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

OldaleTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_OLDALE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

OldaleTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Boy::
	msgbox OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEDEX_GET, OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable
	msgbox OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable::
	msgbox OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC:
	.string "Αυτό το PC στη γωνία είναι για \n"
	.string "κάθε POKéMON TRAINER.\p"
	.string "Φυσικά, αυτό σημαίνει ότι είσαι \n"
	.string "ευπρόσδεκτος να το χρησιμοποιήσεις \l"
	.string "κι εσύ.$"

OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat:
	.string "Τα POKéMON CENTERS είναι \n"
	.string "υπέροχα!\p"
	.string "Μπορείς να χρησιμοποιείς τις \n"
	.string "υπηρεσίες τους όσο θέλεις, και \l"
	.string "είναι όλα δωρεάν. Δεν χρειάζεται \l"
	.string "ποτέ να ανησυχείς!$"

OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable:
	.string "Το POKéMON WIRELESS CLUB στον \n"
	.string "δεύτερο όροφο χτίστηκε πρόσφατα.\p"
	.string "Αλλά λένε ότι ακόμα κάνουν \n"
	.string "ρυθμίσεις.$"

OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub:
	.string "Το POKéMON WIRELESS CLUB στον \n"
	.string "δεύτερο όροφο χτίστηκε πρόσφατα.\p"
	.string "Αντάλλαξα POKéMON αμέσως.$"

