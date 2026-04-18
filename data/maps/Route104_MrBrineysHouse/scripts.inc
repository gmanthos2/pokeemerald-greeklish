.set LOCALID_BRINEY, 1
.set LOCALID_PEEKO, 2

Route104_MrBrineysHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route104_MrBrineysHouse_OnTransition
	.byte 0

Route104_MrBrineysHouse_OnTransition:
	setflag FLAG_LANDMARK_MR_BRINEY_HOUSE
	call_if_eq VAR_BRINEY_HOUSE_STATE, 1, Route104_MrBrineysHouse_EventScript_SetBrineyPeekoPos
	call_if_set FLAG_RECEIVED_POKENAV, Route104_MrBrineysHouse_EventScript_HideRustboroRival
	end

Route104_MrBrineysHouse_EventScript_HideRustboroRival::
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	return

Route104_MrBrineysHouse_EventScript_SetBrineyPeekoPos::
	setobjectxyperm LOCALID_BRINEY, 9, 3
	setobjectmovementtype LOCALID_BRINEY, MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT
	setobjectxyperm LOCALID_PEEKO, 9, 6
	setobjectmovementtype LOCALID_PEEKO, MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN
	return

Route104_MrBrineysHouse_EventScript_Briney::
	lock
	faceplayer
	call_if_unset FLAG_MR_BRINEY_SAILING_INTRO, Route104_MrBrineysHouse_EventScript_SailingIntro
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, Route104_MrBrineysHouse_EventScript_SailBothDeliveries
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, Route104_MrBrineysHouse_EventScript_SailDeliverPackage
	goto Route104_MrBrineysHouse_EventScript_WhereAreWeBound
	end

Route104_MrBrineysHouse_EventScript_SailingIntro::
	setflag FLAG_MR_BRINEY_SAILING_INTRO
	msgbox Route104_MrBrineysHouse_Text_WaitUpPeeko, MSGBOX_DEFAULT
	msgbox Route104_MrBrineysHouse_Text_ItsYouLetsSailToDewford, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
	end

Route104_MrBrineysHouse_EventScript_WhereAreWeBound::
	message Route104_MrBrineysHouse_Text_WhereAreWeBound
	waitmessage
	multichoicedefault 20, 8, MULTI_BRINEY_OFF_DEWFORD, 1, FALSE
	switch VAR_RESULT
	case 0, Route104_MrBrineysHouse_EventScript_SailToDewford
	case 1, Route104_MrBrineysHouse_EventScript_DeclineSailing
	case MULTI_B_PRESSED, Route104_MrBrineysHouse_EventScript_DeclineSailing
	end

Route104_MrBrineysHouse_EventScript_SailBothDeliveries::
	msgbox Route104_MrBrineysHouse_Text_NeedToMakeDeliveriesSailToDewford, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
	end

Route104_MrBrineysHouse_EventScript_SailDeliverPackage::
	msgbox Route104_MrBrineysHouse_Text_NeedToDeliverPackageSailToDewford, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
	end

Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing::
	msgbox Route104_MrBrineysHouse_Text_DeclineDeliverySail, MSGBOX_DEFAULT
	release
	end

Route104_MrBrineysHouse_EventScript_DeclineSailing::
	msgbox Route104_MrBrineysHouse_Text_TellMeWheneverYouWantToSail, MSGBOX_DEFAULT
	release
	end

Route104_MrBrineysHouse_EventScript_SailToDewford::
	msgbox Route104_MrBrineysHouse_Text_SetSailForDewford, MSGBOX_DEFAULT
	call EventScript_BackupMrBrineyLocation
	setvar VAR_BOARD_BRINEY_BOAT_STATE, 1
	clearflag FLAG_HIDE_ROUTE_104_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setvar VAR_RUSTBORO_CITY_STATE, 8
	setvar VAR_ROUTE104_STATE, 2
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setflag FLAG_HIDE_ROUTE_104_RIVAL
	warp MAP_ROUTE104, 13, 51
	waitstate
	releaseall
	end

Route104_MrBrineysHouse_EventScript_Peeko::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	msgbox Route104_MrBrineysHouse_Text_Peeko, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route104_MrBrineysHouse_Text_WaitUpPeeko:
	.string "MR. BRINEY: Περίμενε, μικρή!\n"
	.string "Περίμενε, PEEKO!$"

Route104_MrBrineysHouse_Text_ItsYouLetsSailToDewford:
	.string "Χμ; Είσαι {PLAYER}{KUN}!\n"
	.string "Έσωσες την αγαπημένη μου PEEKO!\l"
	.string "Σου χρωστάμε τόσα πολλά!\p"
	.string "Τι είναι αυτό;\n"
	.string "Θέλεις να σαλπάρεις μαζί μου;\p"
	.string "Χμχμ…\p"
	.string "Έχεις ένα ΓΡΑΜΜΑ για την DEWFORD\n"
	.string "και ένα δέμα για την SLATEPORT, ε;\p"
	.string "Έχεις πολυάσχολη ζωή λοιπόν!\p"
	.string "Αλλά, βεβαίως, αυτό που ζητάς\n"
	.string "δεν είναι καθόλου πρόβλημα.\p"
	.string "Ήρθες στον σωστό άνθρωπο!\n"
	.string "Θα σαλπάρουμε για τη DEWFORD.$"

Route104_MrBrineysHouse_Text_SetSailForDewford:
	.string "MR. BRINEY: DEWFORD λοιπόν!\p"
	.string "Βίρα τις άγκυρες!\n"
	.string "PEEKO, σαλπάρουμε, αγάπη μου!$"

Route104_MrBrineysHouse_Text_DeclineDeliverySail:
	.string "MR. BRINEY: Αλήθεια;\n"
	.string "Οι παραδόσεις σου μπορούν να περιμένουν;\p"
	.string "Συνέχισε και πες μου όποτε \n"
	.string "θελήσεις να σαλπάρουμε!$"

Route104_MrBrineysHouse_Text_NeedToMakeDeliveriesSailToDewford:
	.string "MR. BRINEY: Ωέο!\n"
	.string "Ξέρω ακριβώς τι θες να πεις!\p"
	.string "Έχεις να παραδώσεις ένα ΓΡΑΜΜΑ στην\n"
	.string "DEWFORD και ένα δέμα στην SLATEPORT.\p"
	.string "Αυτό που χρειάζεσαι από εμένα δεν \n"
	.string "είναι πρόβλημα, είμαι ο άνθρωπός σου!\p"
	.string "Πρώτα, θα σαλπάρουμε για την \n"
	.string "DEWFORD.$"

Route104_MrBrineysHouse_Text_NeedToDeliverPackageSailToDewford:
	.string "MR. BRINEY: Ωέο!\n"
	.string "Ξέρω ακριβώς τι θες να πεις!\p"
	.string "Πρόκειται να παραδώσεις ένα δέμα\n"
	.string "στον CAPT. STERN στη SLATEPORT.\p"
	.string "Αυτό που χρειάζεσαι από εμένα δεν \n"
	.string "είναι πρόβλημα, είμαι ο άνθρωπός σου!\p"
	.string "Πρώτα, θα σαλπάρουμε για την \n"
	.string "DEWFORD.$"

Route104_MrBrineysHouse_Text_WhereAreWeBound:
	.string "MR. BRINEY: Ωέο!\n"
	.string "Για σένα, θα βγω στη θάλασσα \l"
	.string "οποιαδήποτε στιγμή!\p"
	.string "Τώρα, φίλε μου, για πού το βάλαμε;$"

Route104_MrBrineysHouse_Text_TellMeWheneverYouWantToSail:
	.string "MR. BRINEY: Έτσι είναι;\n"
	.string "Λοιπόν, η PEEKO σου χρωστάει \l"
	.string "τη ζωή της.\p"
	.string "Απλά πες μου όποτε \n"
	.string "θελήσεις να σαλπάρουμε!$"

Route104_MrBrineysHouse_Text_Peeko:
	.string "PEEKO: Πιιι πιιχιορο!$"

