FortreeCity_House1_MapScripts::
	.byte 0

FortreeCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_FORTREE_NPC_TRADE_COMPLETED, FortreeCity_House1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_PLUSLE
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox FortreeCity_House1_Text_YouWillTradeWontYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FortreeCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FortreeCity_House1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, FortreeCity_House1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox FortreeCity_House1_Text_MonYouTakeCare, MSGBOX_DEFAULT
	setflag FLAG_FORTREE_NPC_TRADE_COMPLETED
	release
	end

FortreeCity_House1_EventScript_DeclineTrade::
	msgbox FortreeCity_House1_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox FortreeCity_House1_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_TradeCompleted::
	msgbox FortreeCity_House1_Text_GoingToMakeVolbeatStrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_ExpertF::
	msgbox FortreeCity_House1_Text_TradingMemoriesWithOthers, MSGBOX_NPC
	end

FortreeCity_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox FortreeCity_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House1_Text_YouWillTradeWontYou:
	.string "Ουααα! Το χρειάζομαι!\n"
	.string "Πρέπει να πάρω ένα {STR_VAR_1}!\l"
	.string "Θα κάνω τα πάντα για αυτό!\p"
	.string "…Εχ… Το άκουσες αυτό;\n"
	.string "Την κραυγή μου από τα βάθη\l"
	.string "της καρδιάς;\p"
	.string "Ακούγοντάς την, θα ανταλλάξεις\n"
	.string "το {STR_VAR_1} σου με το {STR_VAR_2} μου,\l"
	.string "έτσι δεν είναι;$"

FortreeCity_House1_Text_MonYouTakeCare:
	.string "Φοβερό!\p"
	.string "{STR_VAR_1}, καλωσήρθες!\n"
	.string "{STR_VAR_2}, να προσέχεις!$"

FortreeCity_House1_Text_ThisIsntAMon:
	.string "Ηχ, όχι, δεν νομίζω.\n"
	.string "Αυτό δεν είναι ένα {STR_VAR_1}.$"

FortreeCity_House1_Text_YouWontTradeMe:
	.string "Όχι; Δεν θα κάνεις την ανταλλαγή!\n"
	.string "Ακόμα και αφού σου άνοιξα \l"
	.string "την καρδιά μου;$"

FortreeCity_House1_Text_GoingToMakeVolbeatStrong:
	.string "Θα κάνω το VOLBEAT φοβερά δυνατό \n"
	.string "από εδώ και πέρα!\p"
	.string "Ελπίζω να κάνεις το ίδιο με \n"
	.string "το PLUSLE!$"

FortreeCity_House1_Text_TradingMemoriesWithOthers:
	.string "Η ανταλλαγή POKéMON με άλλους…\p"
	.string "Είναι σαν να ανταλλάσσεις τις δικές\n"
	.string "σου αναμνήσεις με άλλους ανθρώπους.$"

FortreeCity_House1_Text_Zigzagoon:
	.string "ZIGZAGOON: Gumomoh;$"

