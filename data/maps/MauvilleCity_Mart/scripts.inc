MauvilleCity_Mart_MapScripts::
	.byte 0

MauvilleCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MauvilleCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MauvilleCity_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_X_ACCURACY
	.2byte ITEM_NONE
	release
	end

MauvilleCity_Mart_EventScript_ExpertM::
	msgbox MauvilleCity_Mart_Text_ItemsToTemporarilyElevateStats, MSGBOX_NPC
	end

MauvilleCity_Mart_EventScript_Man::
	msgbox MauvilleCity_Mart_Text_DecisionsDetermineBattle, MSGBOX_NPC
	end

MauvilleCity_Mart_Text_ItemsToTemporarilyElevateStats:
	.string "Υπάρχουν αντικείμενα που ανεβάζουν\n"
	.string "προσωρινά τα στατιστικά των POKéMON.\p"
	.string "Αυτά που ξέρω ότι \n"
	.string "χρησιμοποιείς στη μάχη \l"
	.string "είναι τα X ATTACK και X DEFEND…\p"
	.string "Πιστεύω ότι υπάρχουν \n"
	.string "κι άλλα παρόμοια.$"

MauvilleCity_Mart_Text_DecisionsDetermineBattle:
	.string "Αν θα χρησιμοποιήσεις μια \n"
	.string "κίνηση, ή ένα αντικείμενο…\p"
	.string "Οι αποφάσεις του TRAINER καθορίζουν \n"
	.string "πώς θα εξελιχθεί η μάχη, νομίζω.$"

