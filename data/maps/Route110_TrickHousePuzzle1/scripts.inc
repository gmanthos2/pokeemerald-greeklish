Route110_TrickHousePuzzle1_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Route110_TrickHousePuzzle1_OnLoad
	.byte 0

Route110_TrickHousePuzzle1_OnLoad:
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_1_STATE, 2, Route110_TrickHousePuzzle1_EventScript_OpenDoor
	end

Route110_TrickHousePuzzle1_EventScript_OpenDoor::
	setmetatile 13, 1, METATILE_TrickHousePuzzle_Stairs_Down, FALSE
	end

Route110_TrickHousePuzzle1_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_1_STATE, 0, Route110_TrickHousePuzzle1_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle1_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_1_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle1_EventScript_Sally::
	trainerbattle_single TRAINER_SALLY, Route110_TrickHousePuzzle1_Text_SallyIntro, Route110_TrickHousePuzzle1_Text_SallyDefeat
	msgbox Route110_TrickHousePuzzle1_Text_SallyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_EventScript_Eddie::
	trainerbattle_single TRAINER_EDDIE, Route110_TrickHousePuzzle1_Text_EddieIntro, Route110_TrickHousePuzzle1_Text_EddieDefeat
	msgbox Route110_TrickHousePuzzle1_Text_EddiePostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_EventScript_Robin::
	trainerbattle_single TRAINER_ROBIN, Route110_TrickHousePuzzle1_Text_RobinIntro, Route110_TrickHousePuzzle1_Text_RobinDefeat
	msgbox Route110_TrickHousePuzzle1_Text_RobinPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_Text_WroteSecretCodeLockOpened::
	.string "Το {PLAYER} έγραψε τον μυστικό\n"
	.string "κωδικό στην πόρτα.\p"
	.string "“O TRICK MASTER είναι υπέροχος.”\n"
	.string "… … … … … … … …\p"
	.string "Η κλειδαριά άνοιξε!$"

Route110_TrickHousePuzzle1_Text_SallyIntro:
	.string "Θα κόψω το δρόμο μου προς τη\n"
	.string "νίκη με το CUT που μόλις έμαθα!$"

Route110_TrickHousePuzzle1_Text_SallyDefeat:
	.string "Γιατί είσαι τόσο σοβαρό;$"

Route110_TrickHousePuzzle1_Text_SallyPostBattle:
	.string "Ποτέ δεν κουράζομαι να\n"
	.string "κόβω και να πετσοκόβω!$"

Route110_TrickHousePuzzle1_Text_EddieIntro:
	.string "Περιπλανήθηκα σε αυτό το\n"
	.string "περίεργο σπίτι κατά λάθος…$"

Route110_TrickHousePuzzle1_Text_EddieDefeat:
	.string "Και τώρα έχασα…$"

Route110_TrickHousePuzzle1_Text_EddiePostBattle:
	.string "Έχασα το δρόμο μου, έχασα μια\n"
	.string "μάχη, και τώρα είμαι ακόμα πιο\l"
	.string "χαμένος… Δεν μπορώ να βγω…$"

Route110_TrickHousePuzzle1_Text_RobinIntro:
	.string "Ποιος είναι επιτέλους ο\n"
	.string "TRICK MASTER;$"

Route110_TrickHousePuzzle1_Text_RobinDefeat:
	.string "Έχασα, επειδή είχα χαθεί σε\n"
	.string "σκέψεις!$"

Route110_TrickHousePuzzle1_Text_RobinPostBattle:
	.string "Είσαι δυνατό!\n"
	.string "Ποιο είσαι επιτέλους;$"

