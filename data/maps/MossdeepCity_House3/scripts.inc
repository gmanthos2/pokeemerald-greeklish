MossdeepCity_House3_MapScripts::
	.byte 0

MossdeepCity_House3_EventScript_SuperRodFisherman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SUPER_ROD, MossdeepCity_House3_EventScript_ReceivedSuperRod
	msgbox MossdeepCity_House3_Text_YouWantSuperRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_House3_EventScript_DeclineSuperRod
	msgbox MossdeepCity_House3_Text_SuperRodIsSuper, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_ROD
	setflag FLAG_RECEIVED_SUPER_ROD
	msgbox MossdeepCity_House3_Text_TryDroppingRodInWater, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_ReceivedSuperRod::
	msgbox MossdeepCity_House3_Text_GoAfterSeafloorPokemon, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_DeclineSuperRod::
	msgbox MossdeepCity_House3_Text_DontYouLikeToFish, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_Text_YouWantSuperRod:
	.string "Γεια σου, TRAINER!\n"
	.string "Το SUPER ROD είναι όντως σούπερ!\p"
	.string "Πες ό,τι θες, αλλά αυτό το \n"
	.string "εργαλείο μπορεί να πιάσει POKéMON \l"
	.string "από τον βυθό της θάλασσας!\p"
	.string "Τι λες;\n"
	.string "Το θέλεις, έτσι δεν είναι;$"

MossdeepCity_House3_Text_SuperRodIsSuper:
	.string "Σίγουρα, σίγουρα!\n"
	.string "Εξάλλου, το SUPER ROD είναι \l"
	.string "πραγματικά σούπερ!$"

MossdeepCity_House3_Text_TryDroppingRodInWater:
	.string "Αν υπάρχει νερό, δοκίμασε να \n"
	.string "ρίξεις το ROD σου και δες τι \l"
	.string "θα τσιμπήσει!$"

MossdeepCity_House3_Text_DontYouLikeToFish:
	.string "Ε;\n"
	.string "Δεν σου αρέσει το ψάρεμα;$"

MossdeepCity_House3_Text_GoAfterSeafloorPokemon:
	.string "Κυνήγησε POKéMON του βυθού με \n"
	.string "το SUPER ROD σου.$"

