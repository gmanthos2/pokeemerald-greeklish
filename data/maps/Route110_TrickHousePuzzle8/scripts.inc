Route110_TrickHousePuzzle8_MapScripts::
	.byte 0

Route110_TrickHousePuzzle8_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_8_STATE, 0, Route110_TrickHousePuzzle8_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle8_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_8_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle8_EventScript_Vincent::
	trainerbattle_single TRAINER_VINCENT, Route110_TrickHousePuzzle8_Text_VincentIntro, Route110_TrickHousePuzzle8_Text_VincentDefeat
	msgbox Route110_TrickHousePuzzle8_Text_VincentPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Keira::
	trainerbattle_single TRAINER_KEIRA, Route110_TrickHousePuzzle8_Text_KeiraIntro, Route110_TrickHousePuzzle8_Text_KeiraDefeat
	msgbox Route110_TrickHousePuzzle8_Text_KeiraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Leroy::
	trainerbattle_single TRAINER_LEROY, Route110_TrickHousePuzzle8_Text_LeroyIntro, Route110_TrickHousePuzzle8_Text_LeroyDefeat
	msgbox Route110_TrickHousePuzzle8_Text_LeroyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_Text_WroteSecretCodeLockOpened::
	.string "Το {PLAYER} έγραψε τον μυστικό\n"
	.string "κωδικό στην πόρτα.\p"
	.string "“Αγαπώ τον TRICK MASTER.”\n"
	.string "… … … … … … … …\p"
	.string "Η κλειδαριά άνοιξε!$"

Route110_TrickHousePuzzle8_Text_VincentIntro:
	.string "Όχι πολλοί TRAINERS έχουν φτάσει\n"
	.string "μέχρι εδώ.$"

Route110_TrickHousePuzzle8_Text_VincentDefeat:
	.string "Αυτό σημαίνει ότι είσαι και\n"
	.string "εσύ σκληρό…$"

Route110_TrickHousePuzzle8_Text_VincentPostBattle:
	.string "Έχεις νικήσει τον CHAMPION\n"
	.string "του POKéMON LEAGUE; Είναι πάρα\l"
	.string "πολύ!$"

Route110_TrickHousePuzzle8_Text_KeiraIntro:
	.string "Να θεωρείς τον εαυτό σου \n"
	.string "τυχερό που παλεύεις μαζί μου!$"

Route110_TrickHousePuzzle8_Text_KeiraDefeat:
	.string "Αυτό δεν είναι σωστό!\n"
	.string "Δεν μπορώ να χάσω!$"

Route110_TrickHousePuzzle8_Text_KeiraPostBattle:
	.string "Είναι θαύμα που με κέρδισες.\n"
	.string "Μπορείς να το καυχιέσαι.$"

Route110_TrickHousePuzzle8_Text_LeroyIntro:
	.string "Έχεις περάσει με κόπο και\n"
	.string "εσύ από την πρόκληση του\l"
	.string "TRICK HOUSE.$"

Route110_TrickHousePuzzle8_Text_LeroyDefeat:
	.string "Καταλαβαίνω…\n"
	.string "Έχεις ένα εξαιρετικό στυλ.$"

Route110_TrickHousePuzzle8_Text_LeroyPostBattle:
	.string "Το να βλέπεις κάποιο σαν\n"
	.string "εσένα πρέπει να ικανοποιεί τον\l"
	.string "TRICK MASTER.$"

