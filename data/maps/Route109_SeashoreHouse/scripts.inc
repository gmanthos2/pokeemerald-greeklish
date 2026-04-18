Route109_SeashoreHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route109_SeashoreHouse_OnTransition
	.byte 0

Route109_SeashoreHouse_OnTransition:
	setflag FLAG_LANDMARK_SEASHORE_HOUSE
	end

Route109_SeashoreHouse_EventScript_Owner::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_6_SODA_POP, Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop
	goto_if_set FLAG_DEFEATED_SEASHORE_HOUSE, Route109_SeashoreHouse_EventScript_DefeatedTrainers
	goto_if_set FLAG_TEMP_2, Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction
	msgbox Route109_SeashoreHouse_Text_SeashoreHouseIntro, MSGBOX_DEFAULT
	setflag FLAG_TEMP_2
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction::
	msgbox Route109_SeashoreHouse_Text_ShowMeSomeHotMatches, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_DefeatedTrainers::
	msgbox Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles, MSGBOX_DEFAULT
	giveitem ITEM_SODA_POP, 6
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_BagFull
	setflag FLAG_RECEIVED_6_SODA_POP
	release
	end

Route109_SeashoreHouse_EventScript_BagFull::
	msgbox Route109_SeashoreHouse_Text_BagFull, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop::
	showmoneybox 0, 0
	msgbox Route109_SeashoreHouse_Text_WantToBuySodaPop, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route109_SeashoreHouse_EventScript_BuySodaPop
	msgbox Route109_SeashoreHouse_Text_ThatsTooBad, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_BuySodaPop::
	checkmoney 300
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughMoney
	checkitemspace ITEM_SODA_POP
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughSpace
	msgbox Route109_SeashoreHouse_Text_HereYouGo, MSGBOX_DEFAULT
	removemoney 300
	updatemoneybox
	giveitem ITEM_SODA_POP
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughMoney::
	msgbox Route109_SeashoreHouse_Text_NotEnoughMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughSpace::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_Dwayne::
	trainerbattle_single TRAINER_DWAYNE, Route109_SeashoreHouse_Text_DwayneIntro, Route109_SeashoreHouse_Text_DwayneDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_DwaynePostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Johanna::
	trainerbattle_single TRAINER_JOHANNA, Route109_SeashoreHouse_Text_JohannaIntro, Route109_SeashoreHouse_Text_JohannaDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_JohannaPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Simon::
	trainerbattle_single TRAINER_SIMON, Route109_SeashoreHouse_Text_SimonIntro, Route109_SeashoreHouse_Text_SimonDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_SimonPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_CheckTrainersCompletion::
	goto_if_not_defeated TRAINER_DWAYNE, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_JOHANNA, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_SIMON, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	setflag FLAG_DEFEATED_SEASHORE_HOUSE
	release
	end

Route109_SeashoreHouse_EventScript_TrainersNotCompleted::
	release
	end

Route109_SeashoreHouse_Text_SeashoreHouseIntro:
	.string "Είμαι ο ιδιοκτήτης του SEASHORE \n"
	.string "HOUSE. Αλλά πες με MR. SEA!\p"
	.string "Αυτό που αγαπώ πάνω απ' όλα είναι \n"
	.string "να βλέπω καυτές μάχες POKéMON.\p"
	.string "Άσε με να δω αν η καρδιά σου \n"
	.string "καίει!\p"
	.string "Αν μπορείς να νικήσεις όλους τους \n"
	.string "TRAINERS εδώ, θα σε ανταμείψω.$"

Route109_SeashoreHouse_Text_ShowMeSomeHotMatches:
	.string "Δείξε μου μερικές καυτές μάχες!\p"
	.string "Διευθύνω αυτό το SEASHORE HOUSE \n"
	.string "μόνο για αυτόν τον λόγο!$"

Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles:
	.string "Είσαι καυτός!\n"
	.string "Αυτές οι μάχες έβγαζαν φλόγες!\l"
	.string "Είμαι κάτι παραπάνω από \l"
	.string "ικανοποιημένος!\p"
	.string "Ως ευχαριστώ που μου έδειξες το \n"
	.string "σερί σου, θέλω να τα πάρεις αυτά.\p"
	.string "Είναι μισή ντουζίνα μπουκάλια \n"
	.string "SODA POP!$"

Route109_SeashoreHouse_Text_BagFull:
	.string "Ω, αλλά η ΤΣΑΝΤΑ σου είναι γεμάτη.\n"
	.string "Θα τα κρατήσω εγώ για σένα.$"

Route109_SeashoreHouse_Text_WantToBuySodaPop:
	.string "Θέλεις να αγοράσεις SODA POP;\n"
	.string "Τα POKéMON το λατρεύουν!\p"
	.string "Μόνο ¥300 το μπουκάλι!\n"
	.string "Αγόρασε μερικά!$"

Route109_SeashoreHouse_Text_HereYouGo:
	.string "Ορίστε!$"

Route109_SeashoreHouse_Text_NotEnoughMoney:
	.string "Δεν έχεις τα χρήματα.$"

Route109_SeashoreHouse_Text_ThatsTooBad:
	.string "Όχι;\n"
	.string "Κρίμα.$"

Route109_SeashoreHouse_Text_DwayneIntro:
	.string "Αν ψάχνεις για μάχη στο \n"
	.string "SEASHORE HOUSE, δεν θα βρεις πιο \l"
	.string "καυτό TRAINER από εμένα, φίλε!$"

Route109_SeashoreHouse_Text_DwayneDefeated:
	.string "Αυτή ήταν μια καυτή μάχη!\n"
	.string "Μπορώ να δεχτώ αυτή την ήττα!$"

Route109_SeashoreHouse_Text_DwaynePostBattle:
	.string "Όταν είμαι στη SLATEPORT, μου \n"
	.string "αρέσουν οι καυτές μάχες και \l"
	.string "οι παγωμένες SODA POP!$"

Route109_SeashoreHouse_Text_JohannaIntro:
	.string "Οι βαρετές μάχες δεν αξίζουν \n"
	.string "τον κόπο.\p"
	.string "Οι καυτές μάχες σκληραγωγούν \n"
	.string "τους TRAINERS και τα POKéMON!$"

Route109_SeashoreHouse_Text_JohannaDefeated:
	.string "Αυτό ήταν καυτό!$"

Route109_SeashoreHouse_Text_JohannaPostBattle:
	.string "Ουφ, δίψασα.\n"
	.string "Μάλλον θα πιω μια SODA POP.$"

Route109_SeashoreHouse_Text_SimonIntro:
	.string "Θα σου δείξω πόσο σπουδαία είναι \n"
	.string "τα POKéMON μου, αλλά μην κλάψεις!$"

Route109_SeashoreHouse_Text_SimonDefeated:
	.string "…Έχασα, αλλά δεν θα κλάψω…$"

Route109_SeashoreHouse_Text_SimonPostBattle:
	.string "Αν ένα POKéMON μου ήξερε την \n"
	.string "κίνηση για να με κουβαλάει στο νερό \l"
	.string "στην πλάτη του, θα μπορούσα να \l"
	.string "ξεφορτωθώ αυτό το σωσίβιο.$"

