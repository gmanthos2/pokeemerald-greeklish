LavaridgeTown_Mart_MapScripts::
	.byte 0

LavaridgeTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LavaridgeTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LavaridgeTown_Mart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_NONE
	release
	end

LavaridgeTown_Mart_EventScript_ExpertM::
	msgbox LavaridgeTown_Mart_Text_XSpeedFirstStrike, MSGBOX_NPC
	end

LavaridgeTown_Mart_EventScript_OldWoman::
	msgbox LavaridgeTown_Mart_Text_LocalSpecialtyOnMtChimney, MSGBOX_NPC
	end

LavaridgeTown_Mart_Text_XSpeedFirstStrike:
	.string "Χρησιμοποίησε X SPEED για να αυξήσεις \n"
	.string "το SPEED του POKéMON στη μάχη.\p"
	.string "Αυτό θα το βοηθήσει να χτυπήσει \n"
	.string "πρώτο--ένα αποφασιστικό πλεονέκτημα!$"

LavaridgeTown_Mart_Text_LocalSpecialtyOnMtChimney:
	.string "Στην κορυφή του MT. CHIMNEY, υπάρχει \n"
	.string "μια τοπική σπεσιαλιτέ που μπορείς \l"
	.string "να αγοράσεις μόνο εκεί.\p"
	.string "Δώσ' τη σε ένα POKéMON--θα πετάξει \n"
	.string "από τη χαρά του.$"

