MauvilleCity_BikeShop_MapScripts::
	.byte 0

MauvilleCity_BikeShop_EventScript_Rydel::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BIKE, MauvilleCity_BikeShop_EventScript_AskSwitchBikes
	goto_if_set FLAG_DECLINED_BIKE, MauvilleCity_BikeShop_EventScript_SkipGreeting
	msgbox MauvilleCity_BikeShop_Text_RydelGreeting, MSGBOX_DEFAULT
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_SkipGreeting::
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_ChooseBike::
	message MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne
	waitmessage
	multichoice 21, 8, MULTI_BIKE, TRUE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_GetMachBike
	case 1, MauvilleCity_BikeShop_EventScript_GetAcroBike
	end

MauvilleCity_BikeShop_EventScript_NotFar::
	setflag FLAG_DECLINED_BIKE
	msgbox MauvilleCity_BikeShop_Text_GuessYouDontNeedBike, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_YesFar::
	setflag FLAG_RECEIVED_BIKE
	goto MauvilleCity_BikeShop_EventScript_ChooseBike
	end

MauvilleCity_BikeShop_EventScript_GetMachBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseMachBike, MSGBOX_DEFAULT
	giveitem ITEM_MACH_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_GetAcroBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseAcroBike, MSGBOX_DEFAULT
	giveitem ITEM_ACRO_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes, MSGBOX_DEFAULT
	special SwapRegisteredBike
	release
	end

MauvilleCity_BikeShop_EventScript_AskSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_WantToSwitchBikes, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_SwitchBikes
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_KeepBike
	end

@ If the player does not have a bike on them Rydel assumes its stored in the PC
MauvilleCity_BikeShop_EventScript_SwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_IllSwitchBikes, MSGBOX_DEFAULT
	checkitem ITEM_ACRO_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchAcroForMach
	checkitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchMachForAcro
	msgbox MauvilleCity_BikeShop_Text_OhYourBikeIsInPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_KeepBike::
	msgbox MauvilleCity_BikeShop_Text_HappyYouLikeIt, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_SwitchAcroForMach::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedAcroForMach, MSGBOX_DEFAULT
	removeitem ITEM_ACRO_BIKE
	giveitem ITEM_MACH_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_SwitchMachForAcro::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedMachForAcro, MSGBOX_DEFAULT
	removeitem ITEM_MACH_BIKE
	giveitem ITEM_ACRO_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_Assistant::
	msgbox MauvilleCity_BikeShop_Text_HandbooksAreInBack, MSGBOX_NPC
	end

MauvilleCity_BikeShop_EventScript_MachBikeHandbook::
	message MauvilleCity_BikeShop_Text_MachHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage::
	multichoice 0, 0, MULTI_MACH_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_HowToRide
	case 1, MauvilleCity_BikeShop_EventScript_HowToTurn
	case 2, MauvilleCity_BikeShop_EventScript_SandySlopes
	case 3, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	end

MauvilleCity_BikeShop_EventScript_HowToRide::
	message MauvilleCity_BikeShop_Text_HowToRideMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_HowToTurn::
	message MauvilleCity_BikeShop_Text_HowToTurnMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_SandySlopes::
	message MauvilleCity_BikeShop_Text_SandySlopes
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitMachHandbook::
	release
	end

MauvilleCity_BikeShop_EventScript_AcroBikeHandbook::
	message MauvilleCity_BikeShop_Text_AcroHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage::
	multichoice 0, 0, MULTI_ACRO_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_Wheelies
	case 1, MauvilleCity_BikeShop_EventScript_BunnyHops
	case 2, MauvilleCity_BikeShop_EventScript_Jumps
	case 3, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	end

MauvilleCity_BikeShop_EventScript_Wheelies::
	message MauvilleCity_BikeShop_Text_Wheelies
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_BunnyHops::
	message MauvilleCity_BikeShop_Text_BunnyHops
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_Jumps::
	message MauvilleCity_BikeShop_Text_Jumps
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitAcroHandbook::
	release
	end

MauvilleCity_BikeShop_Text_RydelGreeting:
	.string "Λοιπόν, λοιπόν, τι έχουμε εδώ;\n"
	.string "Ένα πολύ ενεργητικό πελάτη!\p"
	.string "Εγώ; Μπορείς να με φωνάζεις RYDEL.\n"
	.string "Είμαι ο ιδιοκτήτης του μαγαζιού.$"

MauvilleCity_BikeShop_Text_DidYouComeFromFarAway:
	.string "RYDEL: Τα RUNNING SHOES σου…\n"
	.string "Είναι τρομερά βρώμικα.\p"
	.string "Ήρθες από πολύ μακριά;$"

MauvilleCity_BikeShop_Text_GuessYouDontNeedBike:
	.string "RYDEL: Αλήθεια;\p"
	.string "Τότε, υποθέτω ότι δεν έχεις ανάγκη \n"
	.string "κανένα από τα BIKES μου.$"

MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne:
	.string "RYDEL: Χμ, χμ… … … … …\p"
	.string "Μου λες ότι ήρθες σε όλη αυτή\n"
	.string "τη διαδρομή από το LITTLEROOT;\p"
	.string "Θεέ μου!\n"
	.string "Απέχει γελοία πολύ!\p"
	.string "Αν είχες ένα από τα BIKES μου, \n"
	.string "θα μπορούσες να πας οπουδήποτε \l"
	.string "εύκολα νιώθοντας το \l"
	.string "απαλό χάδι του ανέμου!\p"
	.string "Θα σου πω εγώ!\n"
	.string "Θα σου δώσω ένα BIKE!\p"
	.string "Α, μισό λεπτό!\p"
	.string "Ξέχασα να σου πω ότι υπάρχουν\n"
	.string "δύο είδη BIKES!\p"
	.string "Είναι το MACH BIKE και\n"
	.string "το ACRO BIKE!\p"
	.string "Το MACH BIKE είναι για ποδηλάτες που\n"
	.string "θέλουν να νιώσουν τον αέρα!\p"
	.string "Και ένα ACRO BIKE είναι για αυτούς \n"
	.string "που προτιμούν τεχνικές βόλτες!\p"
	.string "Είμαι πολύ καλόκαρδος, οπότε μπορείς\n"
	.string "να πάρεις όποιο σου αρέσει!\p"
	.string "Ποιο θα επιλέξεις;$"

MauvilleCity_BikeShop_Text_ChoseMachBike:
	.string "Το {PLAYER} επέλεξε το MACH BIKE.$"

MauvilleCity_BikeShop_Text_ChoseAcroBike:
	.string "Το {PLAYER} επέλεξε το ACRO BIKE.$"

MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes:
	.string "RYDEL: Εάν σου έρθει η επιθυμία να \n"
	.string "αλλάξεις BIKES, απλώς έλα να με δεις!$"

MauvilleCity_BikeShop_Text_WantToSwitchBikes:
	.string "RYDEL: Α; Σκεφτόσουν\n"
	.string "να αλλάξεις BIKES;$"

MauvilleCity_BikeShop_Text_IllSwitchBikes:
	.string "RYDEL: Εντάξει, κανένα πρόβλημα!\n"
	.string "Θα αλλάξω BIKES για σένα!$"

MauvilleCity_BikeShop_Text_ExchangedMachForAcro:
	.string "Το {PLAYER} αντάλλαξε το MACH BIKE\n"
	.string "με ένα ACRO BIKE.$"

MauvilleCity_BikeShop_Text_ExchangedAcroForMach:
	.string "Το {PLAYER} αντάλλαξε το ACRO BIKE\n"
	.string "με ένα MACH BIKE.$"

MauvilleCity_BikeShop_Text_HappyYouLikeIt:
	.string "RYDEL: Ωραία, ωραία!\n"
	.string "Χαίρομαι που σου αρέσει!$"

MauvilleCity_BikeShop_Text_OhYourBikeIsInPC:
	.string "Α; Τι απέγινε το BIKE\n"
	.string "που σου έδωσα;\p"
	.string "Α, κατάλαβα, το αποθήκευσες \n"
	.string "χρησιμοποιώντας το PC σου.\p"
	.string "Λοιπόν, βγάλτο από τον χώρο \n"
	.string "αποθήκευσης του PC,\l"
	.string "και θα χαρώ να το ανταλλάξω!\p"
	.string "Είθε ο άνεμος να είναι πάντα στην πλάτη\n"
	.string "σου στην περιπέτειά σου!$"

MauvilleCity_BikeShop_Text_HandbooksAreInBack:
	.string "Μαθαίνω για τα BIKES καθώς\n"
	.string "δουλεύω εδώ.\p"
	.string "Αν χρειάζεσαι συμβουλές πώς να \n"
	.string "οδηγείς το BIKE σου, υπάρχουν \l"
	.string "μερικά εγχειρίδια στο πίσω μέρος.$"

MauvilleCity_BikeShop_Text_MachHandbookWhichPage:
	.string "Είναι ένα εγχειρίδιο για το MACH BIKE.\p"
	.string "Ποια σελίδα θέλεις να διαβάσεις;$"

MauvilleCity_BikeShop_Text_HowToRideMachBike:
	.string "Ένα BIKE κινείται προς την κατεύθυνση\n"
	.string "του κουμπιού + Control Pad.\p"
	.string "Θα επιταχύνει μόλις πάρει μπρος.\p"
	.string "Για να σταματήσεις, άφησε το \n"
	.string "+ Control Pad.\l"
	.string "Το BIKE θα επιβραδύνει μέχρι \l"
	.string "να σταματήσει.\p"
	.string "Θέλεις να διαβάσεις μια \n"
	.string "καινουρια σελίδα;$"

MauvilleCity_BikeShop_Text_HowToTurnMachBike:
	.string "Το MACH BIKE είναι γρήγορο, αλλά δεν\n"
	.string "μπορεί να σταματήσει πολύ γρήγορα.\p"
	.string "Γίνεται λίγο δύσκολο να στρίψεις\n"
	.string "σε μια γωνία.\p"
	.string "Άφησε το + Control Pad λίγο\n"
	.string "πριν τη γωνία και επιβράδυνε.\p"
	.string "Θέλεις να διαβάσεις \n"
	.string "μια άλλη σελίδα;$"

MauvilleCity_BikeShop_Text_SandySlopes:
	.string "Υπάρχουν μικρές αμμώδεις πλαγιές\n"
	.string "σε όλη την περιοχή HOENN.\p"
	.string "Η χαλαρή άμμος καθιστά αδύνατη \n"
	.string "την κανονική ανάβαση.\p"
	.string "Αλλά αν έχεις ένα MACH BIKE, \n"
	.string "μπορείς να την ανέβεις.\p"
	.string "Θέλεις να διαβάσεις \n"
	.string "μια άλλη σελίδα;$"

MauvilleCity_BikeShop_Text_AcroHandbookWhichPage:
	.string "Είναι ένα εγχειρίδιο για το ACRO BIKE.\p"
	.string "Ποια σελίδα θέλεις να διαβάσεις;$"

MauvilleCity_BikeShop_Text_Wheelies:
	.string "Πάτησε το κουμπί Β κατά την οδήγηση, \n"
	.string "και ο μπροστινός τροχός σηκώνεται.\p"
	.string "Μπορείς να τριγυρίζεις με τον μπροστινό\n"
	.string "τροχό σηκωμένο με το + Control Pad.\p"
	.string "Αυτή η τεχνική ονομάζεται σούζα.\p"
	.string "Θέλεις να διαβάσεις \n"
	.string "μια άλλη σελίδα;$"

MauvilleCity_BikeShop_Text_BunnyHops:
	.string "Κρατώντας πατημένο \n"
	.string "το κουμπί B, \l"
	.string "το BIKE μπορεί να χοροπηδά.\p"
	.string "Αυτή η τεχνική ονομάζεται bunny hop.\p"
	.string "Μπορείς να οδηγείς ενώ πηδάς, επίσης.\p"
	.string "Θέλεις να διαβάσεις \n"
	.string "μια άλλη σελίδα;$"

MauvilleCity_BikeShop_Text_Jumps:
	.string "Πάτα το B και το + Control Pad \n"
	.string "ταυτόχρονα για να πηδήξεις.\p"
	.string "Πάτα το + Control Pad προς \n"
	.string "το πλάι για να πηδήξεις λοξά.\p"
	.string "Πάτα το προς τα πίσω για να \n"
	.string "κάνεις το BIKE να αλλάξει \l"
	.string "κατευθύνσεις κατά το άλμα.\p"
	.string "Θέλεις να διαβάσεις \n"
	.string "μια άλλη σελίδα;$"

