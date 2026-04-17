BattleFrontier_Lounge6_MapScripts::
	.byte 0

BattleFrontier_Lounge6_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_BATTLE_FRONTIER_TRADE_DONE, BattleFrontier_Lounge6_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_MEOWTH
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox BattleFrontier_Lounge6_Text_WouldYouLikeToTrade, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge6_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge6_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, BattleFrontier_Lounge6_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt, MSGBOX_DEFAULT
	setflag FLAG_BATTLE_FRONTIER_TRADE_DONE
	release
	end

BattleFrontier_Lounge6_EventScript_DeclineTrade::
	msgbox BattleFrontier_Lounge6_Text_WellThatsFineToo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_TradeCompleted::
	msgbox BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_Text_WouldYouLikeToTrade:
	.string "Το POKéMON μου είναι ένα {STR_VAR_2}.\n"
	.string "Το ξέρεις;\l"
	.string "Είναι αρκετά χαριτωμένο και καλό.\p"
	.string "Αυτό το μικρό, θα το αντάλλαζα με\n"
	.string "περηφάνια!\p"
	.string "Θα ήθελες να ανταλλάξεις ένα {STR_VAR_1}\n"
	.string "για το {STR_VAR_2} μου;$"

BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt:
	.string "Ω, είναι αξιολάτρευτο!\n"
	.string "Σε ευχαριστώ!\l"
	.string "Υπόσχομαι ότι θα του φέρομαι καλά!\p"
	.string "Ω! Ελπίζω να φέρεσαι και στο δικό\n"
	.string "μου {STR_VAR_2} καλά επίσης!$"

BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon:
	.string "Ω, λυπάμαι!\n"
	.string "Δεν σκοπεύω να το ανταλλάξω για \l"
	.string "οτιδήποτε άλλο εκτός από {STR_VAR_1}.$"

BattleFrontier_Lounge6_Text_WellThatsFineToo:
	.string "Ω, δεν θέλεις;\n"
	.string "Λοιπόν, κανένα πρόβλημα.\l"
	.string "Σε παρακαλώ έλα να μας ξαναδείς.$"

BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined:
	.string "Χα!\n"
	.string "Ένα SKITTY είναι πολύ πιο χαριτωμένο\l"
	.string "από ό,τι φανταζόμουν. Είμαι χαρούμενη!$"
