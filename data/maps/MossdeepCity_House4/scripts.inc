MossdeepCity_House4_MapScripts::
	.byte 0

MossdeepCity_House4_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, MossdeepCity_House4_EventScript_CanBattleAtSecretBases
	msgbox MossdeepCity_House4_Text_BrotherLikesToFindBases, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_CanBattleAtSecretBases::
	msgbox MossdeepCity_House4_Text_BrotherLikesToVisitBasesAndBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_NinjaBoy::
	lock
	faceplayer
	special CheckPlayerHasSecretBase
	goto_if_eq VAR_RESULT, FALSE, MossdeepCity_House4_EventScript_NoSecretBase
	special GetSecretBaseNearbyMapName
	msgbox MossdeepCity_House4_Text_YouMadeSecretBaseNearX, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_NoSecretBase::
	msgbox MossdeepCity_House4_Text_MakeSecretBase, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox MossdeepCity_House4_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

MossdeepCity_House4_Text_BrotherLikesToFindBases:
	.string "Ο μικρός μου αδερφός λέει ότι του \n"
	.string "αρέσει να βρίσκει τα SECRET BASES \l"
	.string "άλλων ανθρώπων.$"

MossdeepCity_House4_Text_BrotherLikesToVisitBasesAndBattle:
	.string "Ο μικρός μου αδερφός λέει ότι του \n"
	.string "αρέσει να επισκέπτεται τα SECRET \l"
	.string "BASES άλλων και να κάνει μάχες \l"
	.string "POKéMON.$"

MossdeepCity_House4_Text_YouMadeSecretBaseNearX:
	.string "Εσύ ήσουν που έφτιαξες ένα SECRET \n"
	.string "BASE κοντά στο {STR_VAR_1};$"

MossdeepCity_House4_Text_MakeSecretBase:
	.string "Θα έπρεπε να φτιάξεις ένα SECRET \n"
	.string "BASE κάπου. Θα πάω να το βρω!$"

MossdeepCity_House4_Text_Skitty:
	.string "SKITTY: Miyaan?$"

