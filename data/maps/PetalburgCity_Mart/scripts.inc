PetalburgCity_Mart_MapScripts::
	.byte 0

PetalburgCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_PETALBURG_MART_EXPANDED_ITEMS, PetalburgCity_Mart_EventScript_ExpandedItems
	pokemart PetalburgCity_Mart_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
PetalburgCity_Mart_Pokemart_Basic:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_ORANGE_MAIL
	.2byte ITEM_NONE
	release
	end

PetalburgCity_Mart_EventScript_ExpandedItems::
	pokemart PetalburgCity_Mart_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
PetalburgCity_Mart_Pokemart_Expanded:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_ORANGE_MAIL
	.2byte ITEM_NONE
	release
	end

PetalburgCity_Mart_EventScript_Woman::
	msgbox PetalburgCity_Mart_Text_WeakWillGrowStronger, MSGBOX_NPC
	end

PetalburgCity_Mart_EventScript_Boy::
	msgbox PetalburgCity_Mart_Text_RepelIsUseful, MSGBOX_NPC
	end

PetalburgCity_Mart_EventScript_Man::
	msgbox PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou, MSGBOX_NPC
	end

PetalburgCity_Mart_Text_WeakWillGrowStronger:
	.string "Ακόμα κι αν ένα POKéMON είναι\n"
	.string "αδύναμο τώρα, θα γίνει δυνατό.\p"
	.string "Το πιο σημαντικό είναι η αγάπη!\n"
	.string "Αγάπη για τα POKéMON σου!$"

PetalburgCity_Mart_Text_RepelIsUseful:
	.string "Χρησιμοποιείς REPEL;\n"
	.string "Κρατάει μακριά τα POKéMON, \l"
	.string "άρα είναι χρήσιμο όταν βιάζεσαι.$"

PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou:
	.string "Έχεις καθόλου ANTIDOTES μαζί σου;\p"
	.string "Αν περπατάς με ένα δηλητηριασμένο\n"
	.string "POKéMON, θα χάνει HP μέχρι να\l"
	.string "λιποθυμήσει.\l"
	.string "Πάρε μερικά ANTIDOTES μαζί σου.$"

