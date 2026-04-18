FortreeCity_Mart_MapScripts::
	.byte 0

FortreeCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FortreeCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FortreeCity_Mart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_REVIVE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_WOOD_MAIL
	.2byte ITEM_NONE
	release
	end

FortreeCity_Mart_EventScript_Woman::
	msgbox FortreeCity_Mart_Text_SuperRepelBetter, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Girl::
	msgbox FortreeCity_Mart_Text_StockUpOnItems, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Boy::
	msgbox FortreeCity_Mart_Text_RareCandyMakesMonGrow, MSGBOX_NPC
	end

FortreeCity_Mart_Text_SuperRepelBetter:
	.string "Το SUPER REPEL κρατάει πολύ ώρα, \n"
	.string "και την κάνει τη δουλειά του.\p"
	.string "Είναι πολύ καλύτερο από ένα \n"
	.string "συνηθισμένο REPEL.$"

FortreeCity_Mart_Text_StockUpOnItems:
	.string "Πάντα προμηθεύομαι περισσότερα \n"
	.string "αντικείμενα απ' όσα θα χρειαστώ.\p"
	.string "Ποτέ δεν ξέρεις τι μπορεί να συμβεί.\n"
	.string "Κάλιο γαϊδουρόδενε παρά γαϊδουρογύρευε!$"

FortreeCity_Mart_Text_RareCandyMakesMonGrow:
	.string "Ένα RARE CANDY κάνει ένα POKéMON να \n"
	.string "μεγαλώνει αμέσως κατά ένα επίπεδο.$"

