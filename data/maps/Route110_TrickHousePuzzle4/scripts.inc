Route110_TrickHousePuzzle4_MapScripts::
	.byte 0

Route110_TrickHousePuzzle4_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_4_STATE, 0, Route110_TrickHousePuzzle4_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle4_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_4_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle4_EventScript_Cora::
	trainerbattle_single TRAINER_CORA, Route110_TrickHousePuzzle4_Text_CoraIntro, Route110_TrickHousePuzzle4_Text_CoraDefeat
	msgbox Route110_TrickHousePuzzle4_Text_CoraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Yuji::
	trainerbattle_single TRAINER_YUJI, Route110_TrickHousePuzzle4_Text_YujiIntro, Route110_TrickHousePuzzle4_Text_YujiDefeat
	msgbox Route110_TrickHousePuzzle4_Text_YujiPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Paula::
	trainerbattle_single TRAINER_PAULA, Route110_TrickHousePuzzle4_Text_PaulaIntro, Route110_TrickHousePuzzle4_Text_PaulaDefeat
	msgbox Route110_TrickHousePuzzle4_Text_PaulaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_Text_WroteSecretCodeLockOpened:
	.string "Το {PLAYER} έγραψε τον μυστικό\n"
	.string "κωδικό στην πόρτα.\p"
	.string "“O TRICK MASTER είναι τέλειος.”\n"
	.string "… … … … … … … …\p"
	.string "Η κλειδαριά άνοιξε!$"

Route110_TrickHousePuzzle4_Text_CoraIntro:
	.string "Βαριέμαι πολύ να το σκεφτώ.\n"
	.string "Το μόνο που ήθελα ήταν μάχη!$"

Route110_TrickHousePuzzle4_Text_CoraDefeat:
	.string "Ακόμα κι αν έχασα, ακόμα μου\n"
	.string "αρέσει η μάχη πιο πολύ!$"

Route110_TrickHousePuzzle4_Text_CoraPostBattle:
	.string "Δεν συμφωνείς; Θα πήγαινες\n"
	.string "παντού αν υπήρχαν TRAINERS\l"
	.string "εκεί.$"

Route110_TrickHousePuzzle4_Text_YujiIntro:
	.string "Χε! Τέτοιους ογκόλιθους μπορώ\n"
	.string "να τους παραμερίσω με\l"
	.string "ένα δάχτυλο!$"

Route110_TrickHousePuzzle4_Text_YujiDefeat:
	.string "Μπορώ να σπρώξω ογκόλιθους,\n"
	.string "αλλά δεν μπορώ να λύσω...\l"
	.string "τον γρίφο…$"

Route110_TrickHousePuzzle4_Text_YujiPostBattle:
	.string "Δεν είναι αρκετό να είσαι\n"
	.string "δυνατός…\l"
	.string "Πρέπει να χρησιμοποιήσεις \l"
	.string "το κεφάλι σου. Γίνε έξυπνος!$"

Route110_TrickHousePuzzle4_Text_PaulaIntro:
	.string "Το TRICK HOUSE γίνεται πιο\n"
	.string "δύσκολο, έτσι;$"

Route110_TrickHousePuzzle4_Text_PaulaDefeat:
	.string "Ααακ!$"

Route110_TrickHousePuzzle4_Text_PaulaPostBattle:
	.string "Τα έχει καταφέρει κανείς\n"
	.string "μέχρι το τέλος;$"

