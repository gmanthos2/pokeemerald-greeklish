.set LOCALID_NURSE, 1

PetalburgCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

PetalburgCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_PETALBURG_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

PetalburgCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_FatMan::
	msgbox PetalburgCity_PokemonCenter_1F_Text_PCStorageSystem, MSGBOX_NPC
	end

PetalburgCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox PetalburgCity_PokemonCenter_1F_Text_OranBerryRegainedHP, MSGBOX_NPC
	end

PetalburgCity_PokemonCenter_1F_EventScript_Woman::
	lock
	faceplayer
	msgbox PetalburgCity_PokemonCenter_1F_Text_ManyTypesOfPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, IsStarterInParty
	goto_if_eq VAR_RESULT, TRUE, PetalburgCity_PokemonCenter_1F_EventScript_SayStarterTypeInfo
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_SayStarterTypeInfo::
	call_if_eq VAR_STARTER_MON, 0, PetalburgCity_PokemonCenter_1F_EventScript_SayTreeckoType
	call_if_eq VAR_STARTER_MON, 1, PetalburgCity_PokemonCenter_1F_EventScript_SayTorchicType
	call_if_eq VAR_STARTER_MON, 2, PetalburgCity_PokemonCenter_1F_EventScript_SayMudkipType
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_SayTreeckoType::
	msgbox PetalburgCity_PokemonCenter_1F_Text_TreeckoIsGrassType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_EventScript_SayTorchicType::
	msgbox PetalburgCity_PokemonCenter_1F_Text_TorchicIsFireType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_EventScript_SayMudkipType::
	msgbox PetalburgCity_PokemonCenter_1F_Text_MudkipIsWaterType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_Text_PCStorageSystem:
	.string "Αυτό το Σύστημα Αποθήκευσης \n"
	.string "POKéMON μέσω PC…\p"
	.string "Όποιος κι αν το έφτιαξε, πρέπει να \n"
	.string "είναι κάποιος επιστήμονας μάγος!$"

PetalburgCity_PokemonCenter_1F_Text_OranBerryRegainedHP:
	.string "Όταν το POKéMON μου έφαγε ένα\n"
	.string "ORAN BERRY, ανέκτησε HP!$"

PetalburgCity_PokemonCenter_1F_Text_ManyTypesOfPokemon:
	.string "Υπάρχουν πολλοί τύποι POKéMON.\p"
	.string "Όλοι οι τύποι έχουν τα δυνατά και \n"
	.string "τα αδύνατα σημεία τους απέναντι \l"
	.string "σε άλλους τύπους.\p"
	.string "Ανάλογα με τους τύπους των POKéMON,\n"
	.string "μια μάχη μπορεί να είναι εύκολη\l"
	.string "ή δύσκολη.$"

PetalburgCity_PokemonCenter_1F_Text_TreeckoIsGrassType:
	.string "Για παράδειγμα, το TREECKO σου\n"
	.string "είναι τύπου GRASS.\p"
	.string "Είναι δυνατό απέναντι σε τύπους \n"
	.string "WATER και GROUND.\p"
	.string "Αλλά, είναι αδύναμο απέναντι \n"
	.string "σε FIRE-type POKéMON.$"

PetalburgCity_PokemonCenter_1F_Text_TorchicIsFireType:
	.string "Για παράδειγμα, το TORCHIC σου\n"
	.string "είναι τύπου FIRE.\p"
	.string "Είναι δυνατό απέναντι σε τύπους \n"
	.string "GRASS και BUG.\p"
	.string "Αλλά, είναι αδύναμο απέναντι \n"
	.string "σε WATER-type POKéMON.$"

PetalburgCity_PokemonCenter_1F_Text_MudkipIsWaterType:
	.string "Για παράδειγμα, το MUDKIP σου\n"
	.string "είναι τύπου WATER.\p"
	.string "Είναι δυνατό απέναντι σε τύπους \n"
	.string "FIRE.\p"
	.string "Αλλά, είναι αδύναμο απέναντι σε\n"
	.string "GRASS-type και ELECTRIC-type POKéMON.$"

