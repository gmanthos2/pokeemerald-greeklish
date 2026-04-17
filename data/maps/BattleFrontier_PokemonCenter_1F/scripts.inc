.set LOCALID_NURSE, 1

BattleFrontier_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

BattleFrontier_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST
	end

BattleFrontier_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_PokemonCenter_1F_EventScript_SchoolKid::
	msgbox BattleFrontier_PokemonCenter_1F_Text_NeverSeenPokemon, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Man::
	msgbox BattleFrontier_PokemonCenter_1F_Text_NextStopBattleArena, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Picnicker::
	msgbox BattleFrontier_PokemonCenter_1F_Text_GoingThroughEveryChallenge, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox BattleFrontier_PokemonCenter_1F_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_PokemonCenter_1F_Text_NeverSeenPokemon:
	.string "Υπήρχε κάποιος εδώ που χρησιμοποιούσε\n"
	.string "ένα POKéMON που δεν έχω ξαναδεί.\p"
	.string "Δεν το είχα διδαχτεί ποτέ στο\n"
	.string "TRAINER'S SCHOOL, αυτό είναι σίγουρο.\p"
	.string "Αναρωτιέμαι πού μπορείς να πιάσεις\n"
	.string "τέτοια POKéMON.$"

BattleFrontier_PokemonCenter_1F_Text_NextStopBattleArena:
	.string "Τέλεια! Επόμενη στάση, η BATTLE ARENA!\n"
	.string "Καλύτερα να πάρω τα σωστά POKéMON\l"
	.string "από το PC Storage System.$"

BattleFrontier_PokemonCenter_1F_Text_GoingThroughEveryChallenge:
	.string "Χιχι… Θα περάσω από κάθε πρόκληση\n"
	.string "μονάχα με αυτό το μωρό!$"

BattleFrontier_PokemonCenter_1F_Text_Skitty:
	.string "SKITTY: Μια μιαααου!$"

