BattleFrontier_Lounge3_MapScripts::
	.byte 0

	.set BET_AMOUNT_5,  5
	.set BET_AMOUNT_10, 10
	.set BET_AMOUNT_15, 15

BattleFrontier_Lounge3_EventScript_Gambler::
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_GAMBLER, BattleFrontier_Lounge3_EventScript_AlreadyMetGambler
	call BattleFrontier_Lounge3_EventScript_CountSilverSymbols
	goto_if_le VAR_0x8004, 2, BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols
	setflag FLAG_MET_BATTLE_FRONTIER_GAMBLER
	msgbox BattleFrontier_Lounge3_Text_YouLookToughExplainGambling, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge
	end

BattleFrontier_Lounge3_EventScript_AskToEnterChallenge::
	special ShowFrontierGamblerLookingMessage
	waitmessage
	waitbuttonpress
	msgbox BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge
	msgbox BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	special ShowBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_ChooseBetAmount::
	multichoice 20, 4, MULTI_FRONTIER_GAMBLER_BET, FALSE
	copyvar VAR_FRONTIER_GAMBLER_AMOUNT_BET, VAR_RESULT
	switch VAR_RESULT
	case FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_Bet5
	case FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_Bet10
	case FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_Bet15
	case FRONTIER_GAMBLER_BET_CANCEL, BattleFrontier_Lounge3_EventScript_CancelBet
	case MULTI_B_PRESSED, BattleFrontier_Lounge3_EventScript_CancelBet
	end

BattleFrontier_Lounge3_EventScript_Bet5::
	setvar VAR_0x8008, BET_AMOUNT_5
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet10::
	setvar VAR_0x8008, BET_AMOUNT_10
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet15::
	setvar VAR_0x8008, BET_AMOUNT_15
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_TryPlaceBet::
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_Lounge3_EventScript_PlaceBet
	msgbox BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints, MSGBOX_DEFAULT
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_PlaceBet::
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox BattleFrontier_Lounge3_Text_ThanksOffYouGo, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FinishBet
	end

BattleFrontier_Lounge3_EventScript_FinishBet::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	special CloseBattlePointsWindow
	release
	end

BattleFrontier_Lounge3_EventScript_CountSilverSymbols::
	setvar VAR_0x8004, 0
	call_if_set FLAG_SYS_TOWER_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_DOME_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PALACE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_ARENA_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_FACTORY_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PIKE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PYRAMID_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	return

BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount::
	addvar VAR_0x8004, 1
	return

BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols::
	msgbox BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_AlreadyMetGambler::
	msgbox BattleFrontier_Lounge3_Text_Oh, MSGBOX_DEFAULT
	goto_if_ge VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_CheckBetResults
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge
	end

BattleFrontier_Lounge3_EventScript_CheckBetResults::
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WON, BattleFrontier_Lounge3_EventScript_WonChallenge
	goto BattleFrontier_Lounge3_EventScript_LostChallenge
	end

BattleFrontier_Lounge3_EventScript_WonChallenge::
	msgbox BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints, MSGBOX_DEFAULT
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_RewardBet5
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_RewardBet10
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_RewardBet15
	msgbox BattleFrontier_Lounge3_Text_ObtainedBattlePoints, MSGBOX_GETPOINTS
	special GiveFrontierBattlePoints
	msgbox BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_LostChallenge::
	msgbox BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_RewardBet5::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_5 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_5 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet10::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_10 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_10 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet15::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_15 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_15 * 2)
	return

BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge3_EventScript_DeclineChallenge::
	msgbox BattleFrontier_Lounge3_Text_NotInterested, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge3_EventScript_CancelBet::
	special CloseBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_DeclineChallenge
	end

BattleFrontier_Lounge3_EventScript_Man::
	msgbox BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges, MSGBOX_NPC
	end

BattleFrontier_Lounge3_EventScript_Woman::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_BackedWrongTrainer, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_PokefanF::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FatMan::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_TrainerGoodButRattled, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere::
	.string "…Τι είναι αυτό που θέλεις;\p"
	.string "Δε βλέπεις ότι είμαστε λίγο \n"
	.string "απασχολημένοι εδώ;\l"
	.string "Δεν μπορεί να περιμένει για μετά;$"

BattleFrontier_Lounge3_Text_YouLookToughExplainGambling::
	.string "…Ε;\n"
	.string "Μου φαίνεσαι σκληρός TRAINER.\p"
	.string "Χεχε…\n"
	.string "Άκου, έχω αυτήν την πρόταση.\p"
	.string "Έχουμε μια μικρή παρέα εδώ, και \n"
	.string "παίζουμε ένα παιχνιδάκι με το τι \l"
	.string "γίνεται στο BATTLE FRONTIER.\p"
	.string "Οι κανόνες είναι πάρα πολύ απλοί.\p"
	.string "Αρχικά, διαλέγουμε μία από τις\n"
	.string "εγκαταστάσεις του BATTLE FRONTIER.\p"
	.string "Στη συνέχεια, διαλέγουμε όλοι έναν \n"
	.string "διαφορετικό TRAINER που αναλαμβάνει\l"
	.string "αυτήν την πρόκληση και ποντάρουμε με τα\l"
	.string "Battle Points μας.\p"
	.string "Ο τύπος που πόνταρε στον TRAINER με \n"
	.string "το καλύτερο ρεκόρ, παίρνει όλα τα\l"
	.string "Battle Points του ταμείου.\p"
	.string "Ακούγεται απλό, ε;\n"
	.string "Τέλος πάντων…$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerSingle::
	.string "Αυτό που ψάχνω είναι ένας TRAINER\n"
	.string "που θα αμφισβητήσει τα SINGLE\l"
	.string "BATTLE ROOMS του BATTLE TOWER.\p"
	.string "Αλλά μέχρι στιγμής, δεν έχω δει \n"
	.string "κανέναν με τέτοια ποιότητα νικητή.$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerDouble::
	.string "Αυτό που ψάχνω είναι ένας TRAINER\n"
	.string "που θα αμφισβητήσει τα DOUBLE\l"
	.string "BATTLE ROOMS του BATTLE TOWER.\p"
	.string "Αλλά μέχρι στιγμής, δεν έχω δει \n"
	.string "κανέναν με τέτοια ποιότητα νικητή.$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerMulti::
	.string "Αυτό που ψάχνω είναι ένας TRAINER\n"
	.string "που θα αμφισβητήσει τα MULTI\l"
	.string "BATTLE ROOMS του BATTLE TOWER.\p"
	.string "Αλλά μέχρι στιγμής, δεν έχω δει \n"
	.string "κανέναν με τέτοια ποιότητα νικητή.$"

BattleFrontier_Lounge3_Text_ChallengeBattleDomeSingle::
	.string "Αυτό που ψάχνω είναι ένας TRAINER\n"
	.string "που θα μπει στο SINGLE BATTLE\l"
	.string "Τουρνουά του BATTLE DOME.\p"
	.string "Αλλά μέχρι στιγμής, δεν έχω δει \n"
	.string "κανέναν με τέτοια ποιότητα νικητή.$"

BattleFrontier_Lounge3_Text_ChallengeBattleDomeDouble::
	.string "Αυτό που ψάχνω είναι ένας TRAINER\n"
	.string "που θα μπει στο DOUBLE BATTLE\l"
	.string "Τουρνουά του BATTLE DOME.\p"
	.string "Αλλά μέχρι στιγμής, δεν έχω δει \n"
	.string "κανέναν με τέτοια ποιότητα νικητή.$"

BattleFrontier_Lounge3_Text_ChallengeBattleFactorySingle::
	.string "Αυτό που ψάχνω είναι ένας TRAINER\n"
	.string "που θα μπει στο Battle Swap Single\l"
	.string "Tourney του BATTLE FACTORY.\p"
	.string "Αλλά μέχρι στιγμής, δεν έχω δει \n"
	.string "κανέναν με τέτοια ποιότητα νικητή.$"

BattleFrontier_Lounge3_Text_ChallengeBattleFactoryDouble::
	.string "Αυτό που ψάχνω είναι ένας TRAINER\n"
	.string "που θα μπει στο Battle Swap Double\l"
	.string "Tourney του BATTLE FACTORY.\p"
	.string "Αλλά μέχρι στιγμής, δεν έχω δει \n"
	.string "κανέναν με τέτοια ποιότητα νικητή.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceSingle::
	.string "Αυτό που ψάχνω είναι ένας TRAINER\n"
	.string "που θα αμφισβητήσει τα SINGLE BATTLE\l"
	.string "HALLS του BATTLE PALACE.\p"
	.string "Αλλά μέχρι στιγμής, δεν έχω δει \n"
	.string "κανέναν με τέτοια ποιότητα νικητή.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceDouble::
	.string "Αυτό που ψάχνω είναι ένας TRAINER\n"
	.string "που θα αμφισβητήσει τα DOUBLE BATTLE\l"
	.string "HALLS του BATTLE PALACE.\p"
	.string "Αλλά μέχρι στιγμής, δεν έχω δει \n"
	.string "κανέναν με τέτοια ποιότητα νικητή.$"

BattleFrontier_Lounge3_Text_ChallengeBattleArena::
	.string "Αυτό που ψάχνω είναι ένας TRAINER\n"
	.string "που θα μπει στο Τουρνουά Set KO\l"
	.string "του BATTLE ARENA.\p"
	.string "Αλλά μέχρι στιγμής, δεν έχω δει \n"
	.string "κανέναν με τέτοια ποιότητα νικητή.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePike::
	.string "Αυτό που ψάχνω είναι ένας TRAINER\n"
	.string "που θα μπει στο Battle Choice \l"
	.string "του BATTLE PIKE.\p"
	.string "Αλλά μέχρι στιγμής, δεν έχω δει \n"
	.string "κανέναν με τέτοια ποιότητα νικητή.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePyramid::
	.string "Αυτό που ψάχνω είναι ένας TRAINER\n"
	.string "που θα μπει στο Battle Quest\l"
	.string "του BATTLE PYRAMID.\p"
	.string "Αλλά μέχρι στιγμής, δεν έχω δει \n"
	.string "κανέναν με τέτοια ποιότητα νικητή.$"

BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe::
	.string "Θα φροντίσω να επωφεληθείς κι εσύ.\n"
	.string "Λοιπόν, πώς σου φαίνεται;\l"
	.string "Τι λες να μπεις σε αυτό για μένα;$"

BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints::
	.string "Εντάξει, αυτό είναι τέλειο.\n"
	.string "Οπότε, εε… Τι θα έλεγες να μου δώσεις\l"
	.string "μερικά από τα Battle Points σου;\p"
	.string "Εμπιστεύσου με, θα σου δείξω μετά\n"
	.string "την ευγνωμοσύνη μου.$"

BattleFrontier_Lounge3_Text_HowMuchCanYouSpot::
	.string "Τέλεια, τέλεια!\n"
	.string "Λοιπόν, πόσα μπορείς να μου δώσεις;$"

BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints::
	.string "Ω, όχι, όχι, όχι!\n"
	.string "Δεν έχεις αρκετά Battle Points!\p"
	.string "Μη χασομεράς και σπαταλάς το χρόνο\n"
	.string "όλων μας!$"

BattleFrontier_Lounge3_Text_ThanksOffYouGo::
	.string "Χεχε! Ευχαριστώ πολύ!\n"
	.string "Λοιπόν, πήγαινε!$"

BattleFrontier_Lounge3_Text_GetToBattleTowerSingle::
	.string "Πήγαινε γρήγορα στα SINGLE BATTLE\n"
	.string "ROOMS του BATTLE TOWER!\p"
	.string "Πρέπει να κερδίσεις οπωσδήποτε!\n"
	.string "Μην χάσεις την ευκαιρία σου!\l"
	.string "Τα μέλλοντά μας εξαρτώνται από εσένα!$"

BattleFrontier_Lounge3_Text_GetToBattleTowerDouble::
	.string "Πήγαινε γρήγορα στα DOUBLE BATTLE\n"
	.string "ROOMS του BATTLE TOWER!\p"
	.string "Πρέπει να κερδίσεις οπωσδήποτε!\n"
	.string "Μην χάσεις την ευκαιρία σου!\l"
	.string "Τα μέλλοντά μας εξαρτώνται από εσένα!$"

BattleFrontier_Lounge3_Text_GetToBattleTowerMulti::
	.string "Πήγαινε γρήγορα στα MULTI BATTLE\n"
	.string "ROOMS του BATTLE TOWER!\p"
	.string "Πρέπει να κερδίσεις οπωσδήποτε!\n"
	.string "Μην χάσεις την ευκαιρία σου!\l"
	.string "Τα μέλλοντά μας εξαρτώνται από εσένα!$"

BattleFrontier_Lounge3_Text_GetToBattleDomeSingle::
	.string "Πήγαινε γρήγορα στο SINGLE BATTLE \n"
	.string "Τουρνουά του BATTLE DOME!\p"
	.string "Πρέπει να κερδίσεις οπωσδήποτε!\n"
	.string "Μην χάσεις την ευκαιρία σου!\l"
	.string "Τα μέλλοντά μας εξαρτώνται από εσένα!$"

BattleFrontier_Lounge3_Text_GetToBattleDomeDouble::
	.string "Πήγαινε γρήγορα στο DOUBLE BATTLE \n"
	.string "Τουρνουά του BATTLE DOME!\p"
	.string "Πρέπει να κερδίσεις οπωσδήποτε!\n"
	.string "Μην χάσεις την ευκαιρία σου!\l"
	.string "Τα μέλλοντά μας εξαρτώνται από εσένα!$"

BattleFrontier_Lounge3_Text_GetToBattleFactorySingle::
	.string "Στο Battle Swap Single Tourney του\n"
	.string "BATTLE FACTORY αμέσως!\p"
	.string "Πρέπει να κερδίσεις οπωσδήποτε!\n"
	.string "Μην χάσεις την ευκαιρία σου!\l"
	.string "Τα μέλλοντά μας εξαρτώνται από εσένα!$"

BattleFrontier_Lounge3_Text_GetToBattleFactoryDouble::
	.string "Στο Battle Swap Double Tourney του\n"
	.string "BATTLE FACTORY αμέσως!\p"
	.string "Πρέπει να κερδίσεις οπωσδήποτε!\n"
	.string "Μην χάσεις την ευκαιρία σου!\l"
	.string "Τα μέλλοντά μας εξαρτώνται από εσένα!$"

BattleFrontier_Lounge3_Text_GetToBattlePalaceSingle::
	.string "Πήγαινε γρήγορα στα SINGLE BATTLE \n"
	.string "HALLS του BATTLE PALACE!\p"
	.string "Πρέπει να κερδίσεις οπωσδήποτε!\n"
	.string "Μην χάσεις την ευκαιρία σου!\l"
	.string "Τα μέλλοντά μας εξαρτώνται από εσένα!$"

BattleFrontier_Lounge3_Text_GetToBattlePalaceDouble::
	.string "Πήγαινε γρήγορα στα DOUBLE BATTLE \n"
	.string "HALLS του BATTLE PALACE!\p"
	.string "Πρέπει να κερδίσεις οπωσδήποτε!\n"
	.string "Μην χάσεις την ευκαιρία σου!\l"
	.string "Τα μέλλοντά μας εξαρτώνται από εσένα!$"

BattleFrontier_Lounge3_Text_GetToBattleArena::
	.string "Πήγαινε γρήγορα στο Τουρνουά Set KO\n"
	.string "του BATTLE ARENA!\p"
	.string "Πρέπει να κερδίσεις οπωσδήποτε!\n"
	.string "Μην χάσεις την ευκαιρία σου!\l"
	.string "Τα μέλλοντά μας εξαρτώνται από εσένα!$"

BattleFrontier_Lounge3_Text_GetToBattlePike::
	.string "Πήγαινε γρήγορα στο Battle Choice\n"
	.string "του BATTLE PIKE!\p"
	.string "Πρέπει να κερδίσεις οπωσδήποτε!\n"
	.string "Μην χάσεις την ευκαιρία σου!\l"
	.string "Τα μέλλοντά μας εξαρτώνται από εσένα!$"

BattleFrontier_Lounge3_Text_GetToBattlePyramid::
	.string "Πήγαινε γρήγορα στο Battle Quest\n"
	.string "του BATTLE PYRAMID!\p"
	.string "Πρέπει να κερδίσεις οπωσδήποτε!\n"
	.string "Μην χάσεις την ευκαιρία σου!\l"
	.string "Τα μέλλοντά μας εξαρτώνται από εσένα!$"

BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints::
	.string "Ω, είσαι εσύ…\n"
	.string "Καλή προσπάθεια…\p"
	.string "Λυπάμαι, αλλά δεν μπορώ να σου \n"
	.string "δώσω πίσω τα Battle Points σου…\p"
	.string "Ας το αφήσουμε να μας παρακινήσει \n"
	.string "να προσπαθήσουμε παραπάνω την \l"
	.string "επόμενη φορά!$"

BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints::
	.string "Ω ναι!\n"
	.string "Γεια σου πρωταθλητή!\p"
	.string "Ήξερα ότι μπορούσες!\n"
	.string "Ήξερα ότι θα το έκανες!\l"
	.string "Είμαστε μεγάλοι νικητές!\p"
	.string "Θα σου επιστρέψω τα Battle Points σου\n"
	.string "και κάτι παραπάνω από εμένα!$"

BattleFrontier_Lounge3_Text_ObtainedBattlePoints::
	.string "Το {PLAYER} πήρε\n"
	.string "{STR_VAR_1} Battle Points.$"

BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge::
	.string "Αν είσαι έτοιμος για νέα πρόκληση,\n"
	.string "σε παρακαλώ να με σκεφτείς!$"

BattleFrontier_Lounge3_Text_NotInterested::
	.string "Δεν ενδιαφέρεσαι; Δεν πρέπει να \n"
	.string "φοβάσαι τόσο να ρισκάρεις!$"

BattleFrontier_Lounge3_Text_Oh::
	.string "Ω…$"

BattleFrontier_Lounge3_Text_BackedWrongTrainer::
	.string "Υποστήριξα λάθος TRAINER πάλι!\p"
	.string "Ίσως θα έπρεπε να παλευω κανονικά\n"
	.string "όπως όλοι οι άλλοι…$"

BattleFrontier_Lounge3_Text_TrainerGoodButRattled::
	.string "Εκείνος ο TRAINER…\p"
	.string "Είναι καλός, αλλά τα χάνει εύκολα \n"
	.string "για να επιβιώσει στο BATTLE DOME…$"

BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne::
	.string "Χα!\n"
	.string "Ξέρω έναν νικητή όταν τον βλέπω!$"

BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges::
	.string "Αυτοί οι TRAINERS…\n"
	.string "Τι κάνουν;\l"
	.string "Θα έπρεπε να δέχονται προκλήσεις.$"
