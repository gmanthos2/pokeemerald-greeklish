PacifidlogTown_House3_MapScripts::
	.byte 0

PacifidlogTown_House3_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED, PacifidlogTown_House3_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_HORSEA
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox PacifidlogTown_House3_Text_WillingToTradeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PacifidlogTown_House3_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, PacifidlogTown_House3_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, PacifidlogTown_House3_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou, MSGBOX_DEFAULT
	setflag FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED
	release
	end

PacifidlogTown_House3_EventScript_DeclineTrade::
	msgbox PacifidlogTown_House3_Text_NotDesperateOrAnything, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_TradeCompleted::
	msgbox PacifidlogTown_House3_Text_ReallyWantedToGetBagon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_Girl::
	msgbox PacifidlogTown_House3_Text_IsThatAPokedex, MSGBOX_NPC
	end

PacifidlogTown_House3_Text_WillingToTradeIt:
	.string "Κοίτα αυτό το {STR_VAR_2}!\p"
	.string "Είναι το {STR_VAR_2} που έπιασα χθες \n"
	.string "για να γιορτάσω τα γενέθλιά μου!\p"
	.string "Ω, βλέπω ότι το θέλεις!\n"
	.string "Εξάλλου, είναι ανεκτίμητο!\p"
	.string "Θα σου πω τι θα γίνει. Ίσως \n"
	.string "να το αντάλλαζα με ένα {STR_VAR_1}.$"

PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou:
	.string "Ω, οπότε αυτό είναι ένα {STR_VAR_1};\p"
	.string "Μοιάζει κάπως με {STR_VAR_2}, κι όμως \n"
	.string "είναι ελαφρώς διαφορετικό.\p"
	.string "Σε ευχαριστώ!$"

PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon:
	.string "Όχι, όχι, όχι! Δεν δέχομαι \n"
	.string "τίποτα λιγότερο από ένα \l"
	.string "πραγματικό {STR_VAR_1}!$"

PacifidlogTown_House3_Text_NotDesperateOrAnything:
	.string "Ω, οπότε δεν θα το προχωρήσεις;\p"
	.string "Εντάξει. Δεν καίγομαι κιόλας να \n"
	.string "κάνω ανταλλαγή.$"

PacifidlogTown_House3_Text_ReallyWantedToGetBagon:
	.string "Ξέρω ότι θα μπορούσα να ψάξω \n"
	.string "ένα μόνος μου, αλλά…\p"
	.string "Αλλά ήθελα πραγματικά να πάρω \n"
	.string "ένα BAGON που έπιασε κάποιος \l"
	.string "άλλος TRAINER…$"

PacifidlogTown_House3_Text_IsThatAPokedex:
	.string "Αυτό είναι ένα POKéDEX;\p"
	.string "Συνάντησες πολλά διαφορετικά \n"
	.string "POKéMON;\p"
	.string "Μακάρι να ήμουν σαν εσένα.$"

