FortreeCity_House2_MapScripts::
	.byte 0

FortreeCity_House2_EventScript_HiddenPowerGiver::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_HIDDEN_POWER, FortreeCity_House2_EventScript_ExplainHiddenPower
	call_if_unset FLAG_MET_HIDDEN_POWER_GIVER, FortreeCity_House2_EventScript_Greeting
	msgbox FortreeCity_House2_Text_CoinInWhichHand, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 1, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_CorrectTryAgainWhichHand, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 1, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_CorrectTryAgainWhichHand2, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 0, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_YourHiddenPowerHasAwoken, MSGBOX_DEFAULT
	giveitem ITEM_TM_HIDDEN_POWER
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_HIDDEN_POWER
	msgbox FortreeCity_House2_Text_ExplainHiddenPower, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_Greeting::
	msgbox FortreeCity_House2_Text_HiddenPowersArousedByNature, MSGBOX_DEFAULT
	setflag FLAG_MET_HIDDEN_POWER_GIVER
	return

FortreeCity_House2_EventScript_ExplainHiddenPower::
	msgbox FortreeCity_House2_Text_ExplainHiddenPower, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_WrongGuess::
	msgbox FortreeCity_House2_Text_YouGuessedWrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_Text_HiddenPowersArousedByNature:
	.string "Άνθρωποι… POKéMON…\p"
	.string "Οι κρυφές τους δυνάμεις ξυπνούν\n"
	.string "ζώντας στο φυσικό περιβάλλον…$"

FortreeCity_House2_Text_CoinInWhichHand:
	.string "Άσε αυτή τη γριά να δει αν η κρυφή \n"
	.string "σου δύναμη έχει ξυπνήσει…\p"
	.string "Κρατάω ένα νόμισμα στο χέρι μου.\p"
	.string "Πες μου, το έχω στο δεξί μου χέρι; \n"
	.string "Ή στο αριστερό;$"

FortreeCity_House2_Text_CorrectTryAgainWhichHand:
	.string "Ω! Ναι, σωστά!\p"
	.string "Θα δοκιμάσουμε ξανά.\p"
	.string "Σε ποιο χέρι έχω το νόμισμα;\n"
	.string "Στο δεξί ή στο αριστερό;$"

FortreeCity_House2_Text_CorrectTryAgainWhichHand2:
	.string "Ω! Ναι, σωστά!\p"
	.string "Θα δοκιμάσουμε ξανά.\p"
	.string "Σε ποιο χέρι έχω το νόμισμα;\n"
	.string "Στο δεξί ή στο αριστερό;$"

FortreeCity_House2_Text_YourHiddenPowerHasAwoken:
	.string "Ω! Υπέροχα!\n"
	.string "Η κρυφή σου δύναμη ξύπνησε!\p"
	.string "Ορίστε, πάρε αυτό και ξύπνησε την \n"
	.string "κρυφή δύναμη των POKéMON σου.$"

FortreeCity_House2_Text_ExplainHiddenPower:
	.string "Το HIDDEN POWER είναι μια κίνηση που \n"
	.string "αλλάζει ανάλογα με το POKéMON.$"

FortreeCity_House2_Text_YouGuessedWrong:
	.string "Όχι, κρίμα.\n"
	.string "Μάντεψες λάθος.$"

