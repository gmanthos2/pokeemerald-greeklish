.set LOCALID_NURSE, 1

FortreeCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FortreeCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_FORTREE_CITY
	end

FortreeCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FortreeCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox FortreeCity_PokemonCenter_1F_Text_GoToSafariZone, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Man::
	msgbox FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Boy::
	msgbox FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_Text_GoToSafariZone:
	.string "Άκου, παιδί μου, δουλεύεις \n"
	.string "πάνω σε ένα POKéDEX;\p"
	.string "Χμμ… Πήγαινε στο SAFARI ZONE.\n"
	.string "Αυτή είναι η συμβουλή μου.$"

FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat:
	.string "Έχεις κάνει τίποτα στο \n"
	.string "RECORD CORNER;\p"
	.string "Είναι αρκετά ωραίο. Ανακατεύει τα \n"
	.string "ρεκόρ των TRAINERS.\p"
	.string "Δεν ξέρω ακριβώς πώς δουλεύει, \n"
	.string "αλλά είναι κουλ. Είναι και συναρπαστικό!$"

FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav:
	.string "Πω πω, έχεις POKéNAV!\n"
	.string "Και είναι ακριβώς σαν το δικό μου!\p"
	.string "Ξέρεις για το σύστημα \n"
	.string "MATCH CALL του POKéNAV;\p"
	.string "Άνοιξέ το, και μπορείς να μιλάς με \n"
	.string "καταχωρημένους TRAINERS ανά πάσα στιγμή.\p"
	.string "Σου δείχνει επίσης ποιοι TRAINERS \n"
	.string "θέλουν ρεβάνς μαζί σου.\p"
	.string "Είναι πραγματικά πανέξυπνο! Αυτοί \n"
	.string "οι τύποι της DEVON ξέρουν \l"
	.string "τι κάνουν!$"

