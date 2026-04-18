LavaridgeTown_HerbShop_MapScripts::
	.byte 0

LavaridgeTown_HerbShop_EventScript_Clerk::
	lock
	faceplayer
	message LavaridgeTown_HerbShop_Text_WelcomeToHerbShop
	waitmessage
	pokemart LavaridgeTown_HerbShop_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LavaridgeTown_HerbShop_Pokemart:
	.2byte ITEM_ENERGY_POWDER
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_HEAL_POWDER
	.2byte ITEM_REVIVAL_HERB
	.2byte ITEM_NONE
	release
	end

LavaridgeTown_HerbShop_EventScript_ExpertM::
	msgbox LavaridgeTown_HerbShop_Text_HerbalMedicineWorksButMonWillDislike, MSGBOX_NPC
	end

LavaridgeTown_HerbShop_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CHARCOAL, LavaridgeTown_HerbShop_EventScript_ExplainCharcoal
	msgbox LavaridgeTown_HerbShop_Text_YouveComeToLookAtHerbalMedicine, MSGBOX_DEFAULT
	giveitem ITEM_CHARCOAL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CHARCOAL
	release
	end

LavaridgeTown_HerbShop_EventScript_ExplainCharcoal::
	msgbox LavaridgeTown_HerbShop_Text_ExplainCharcoal, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_HerbShop_Text_WelcomeToHerbShop:
	.string "Καλωσήρθες στο HERB SHOP, το σπίτι των\n"
	.string "αποτελεσματικών και φθηνών φαρμάκων!$"

LavaridgeTown_HerbShop_Text_YouveComeToLookAtHerbalMedicine:
	.string "Ήρθες να δεις τα βότανα\n"
	.string "στο LAVARIDGE;\p"
	.string "Αυτό είναι αρκετά αξιέπαινο.\p"
	.string "Μου αρέσεις! Πάρε αυτό!$"

LavaridgeTown_HerbShop_Text_ExplainCharcoal:
	.string "Αυτό το CHARCOAL που σου έδωσα,\n"
	.string "χρησιμοποιείται για να φτιάχνεις \l"
	.string "βότανα.\p"
	.string "Επίσης κάνει θαύματα όταν κρατιέται \n"
	.string "από ένα POKéMON.\p"
	.string "Ενισχύει τη δύναμη των κινήσεων\n"
	.string "τύπου FIRE.$"

LavaridgeTown_HerbShop_Text_HerbalMedicineWorksButMonWillDislike:
	.string "Τα βότανα δουλεύουν εντυπωσιακά καλά.\n"
	.string "Αλλά το POKéMON σου θα σε αντιπαθήσει \l"
	.string "γι' αυτό. Πρέπει να είναι \l"
	.string "απαίσια πικρά!$"

