.set LOCALID_SS_TIDAL, 2
.set LOCALID_FERRY_ATTENDANT, 3
.set LOCALID_MANIAC_1, 9
.set LOCALID_MANIAC_2, 10
.set LOCALID_GIRL, 12
.set LOCALID_CAMPER, 14
.set LOCALID_FISHERMAN_2, 18
.set LOCALID_MAN_4, 23

BattleFrontier_OutsideWest_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideWest_OnTransition
	.byte 0

BattleFrontier_OutsideWest_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	end

BattleFrontier_OutsideWest_EventScript_FerryAttendant::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_MayISeeYourTicket, MSGBOX_DEFAULT
	checkitem ITEM_SS_TICKET
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_OutsideWest_EventScript_NoSSTicket
	message BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination::
	multichoicedefault 18, 6, MULTI_SSTIDAL_BATTLE_FRONTIER, 2, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_OutsideWest_EventScript_FerryToSlateport
	case 1, BattleFrontier_OutsideWest_EventScript_FerryToLilycove
	case 2, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	case MULTI_B_PRESSED, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	end

BattleFrontier_OutsideWest_EventScript_NoSSTicket::
	msgbox BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToSlateport::
	msgbox BattleFrontier_OutsideWest_Text_SlateportItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_SLATEPORT_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToLilycove::
	msgbox BattleFrontier_OutsideWest_Text_LilycoveItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_LILYCOVE_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination::
	message BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_BoardFerry::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_FERRY_ATTENDANT, MAP_BATTLE_FRONTIER_OUTSIDE_WEST
	setvar VAR_0x8004, LOCALID_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	return

BattleFrontier_OutsideWest_EventScript_CancelFerrySelect::
	msgbox BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_BattleDomeSign::
	msgbox BattleFrontier_OutsideWest_Text_BattleDomeSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattleFactorySign::
	msgbox BattleFrontier_OutsideWest_Text_BattleFactorySign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattlePikeSign::
	msgbox BattleFrontier_OutsideWest_Text_BattlePikeSign, MSGBOX_SIGN
	end

@ Unused. Of note, Battle Tower is in the East section in the final release
BattleFrontier_OutsideWest_EventScript_UnusedNPC1::
	msgbox BattleFrontier_OutsideWest_Text_ThisIsBattleTower, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC2::
	msgbox BattleFrontier_OutsideWest_Text_CantFindBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Boy1::
	msgbox BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Fisherman2::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere
	waitmessage
	applymovement LOCALID_FISHERMAN_2, Common_Movement_FaceAwayPlayer
	waitmovement 0
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_Man1::
	msgbox BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Maniac1::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_Maniac2::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk::
	applymovement LOCALID_MANIAC_1, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons, MSGBOX_DEFAULT
	applymovement LOCALID_MANIAC_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons, MSGBOX_DEFAULT
	closemessage
	delay 25
	applymovement LOCALID_MANIAC_1, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_MANIAC_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_Camper::
	lock
	faceplayer
	delay 20
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	msgbox BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_CamperFaceFactory::
	applymovement LOCALID_CAMPER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory::
	return

BattleFrontier_OutsideWest_EventScript_Girl::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper
	waitmessage
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_GirlShudderNorth
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_GirlShudderSouth
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_GirlShudderWest
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_GirlShudderEast
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_GirlShudderNorth::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderNorth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderSouth::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderSouth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderWest::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderWest
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderEast::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderEast
	waitmovement 0
	return

BattleFrontier_OutsideWest_Movement_GirlShudderNorth:
	walk_in_place_faster_down
	walk_in_place_faster_down
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderSouth:
	walk_in_place_faster_up
	walk_in_place_faster_up
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderWest:
	walk_in_place_faster_right
	walk_in_place_faster_right
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderEast:
	walk_in_place_faster_left
	walk_in_place_faster_left
	step_end

BattleFrontier_OutsideWest_EventScript_Woman2::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors, MSGBOX_DEFAULT
	random 2
	goto_if_eq VAR_RESULT, 1, BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors
	goto BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors
	end

BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Fisherman1::
	msgbox BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC3::
	msgbox BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Lass::
	msgbox BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_ExpertM::
	msgbox BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man2::
	msgbox BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman1::
	msgbox BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan1::
	msgbox BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan2::
	msgbox BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Boy2::
	lock
	msgbox BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_OldMan::
	msgbox BattleFrontier_OutsideWest_Text_DomeAceIsMine, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man4::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAN_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_PokefanF::
	msgbox BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Text_BattleDomeSign:
	.string "Αυτό είναι το BATTLE DOME!\n"
	.string "Ο δρόμος σου για την κορυφή!$"

BattleFrontier_OutsideWest_Text_BattleFactorySign:
	.string "Αυτό είναι το BATTLE FACTORY!\n"
	.string "Αναζήτησε τα πιο δυνατά POKéMON!$"

BattleFrontier_OutsideWest_Text_BattlePikeSign:
	.string "Αυτό είναι το BATTLE PIKE!\n"
	.string "Διάλεξε ένα από τα τρία μονοπάτια!$"

BattleFrontier_OutsideWest_Text_ThisIsBattleTower:
	.string "Αυτό είναι το BATTLE TOWER.\p"
	.string "Άτομα TRAINERS φέρνουν τα POKéMON τους\n"
	.string "για αγώνες αποκλεισμού.$"

BattleFrontier_OutsideWest_Text_MayISeeYourTicket:
	.string "Γεια σας, είστε εδώ για το πλοίο;\n"
	.string "Μπορώ να δω το TICKET σας;$"

BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard:
	.string "Το άτομο {PLAYER} δεν έχει το TICKET…\p"
	.string "Λυπάμαι πολύ.\p"
	.string "Πρέπει να έχεις TICKET για\n"
	.string "να επιβιβαστείς.$"

BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo:
	.string "Το άτομο {PLAYER} έδειξε το TICKET.\p"
	.string "Τέλεια! Αυτό είναι το μόνο που\n"
	.string "χρειάζεσαι! Και πού θες να πας;$"

BattleFrontier_OutsideWest_Text_SlateportItIs:
	.string "Στην SLATEPORT CITY, λοιπόν!$"

BattleFrontier_OutsideWest_Text_LilycoveItIs:
	.string "Στην LILYCOVE CITY, λοιπόν!$"

BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime:
	.string "Παρακαλούμε ταξίδεψε μαζί μας\n"
	.string "άλλη φορά!$"

BattleFrontier_OutsideWest_Text_PleaseBoardFerry:
	.string "Παρακαλώ επιβιβάσου και περίμενε\n"
	.string "την αναχώρηση.$"

BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo:
	.string "Τότε, πού θα ήθελες να πας;$"

BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends:
	.string "Είμαι το καλύτερο άτομο απ' την παρέα\n"
	.string "μου. Αλλά εδώ… είμαι άχρηστο!$"

BattleFrontier_OutsideWest_Text_CantFindBattleTower:
	.string "Θέλω να πάω στο BATTLE TOWER,\n"
	.string "αλλά δεν το βρίσκω παρόλο που έχω\l"
	.string "το χάρτη του BATTLE FRONTIER.\p"
	.string "Αυτό το μέρος είναι πολύ μεγάλο!$"

BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere:
	.string "Ήθελα να πάρω μέρος σε challenge με το\n"
	.string "που θα έφτανα εδώ.\p"
	.string "Αλλά στο δρόμο, ζαλίστηκα…\n"
	.string "Ουρρρπ…$"

BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere:
	.string "Δεν μπορεί να έρθει ο οποιοσδήποτε\n"
	.string "εδώ, το ξέρεις;\p"
	.string "Μόνο άτομα TRAINERS που έχουν\n"
	.string "αναγνωριστεί ως δυνατά, έρχονται εδώ.\p"
	.string "Γι' αυτό πολλοί TRAINERS δεν ξέρουν\n"
	.string "καν για το BATTLE FRONTIER.$"

BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons:
	.string "Έι, φίλε…\p"
	.string "Είσαι σίγουρος ότι μπορούμε να\n"
	.string "κάνουμε match χωρίς να έχουμε POKéMON;$"

BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons:
	.string "Εχμ…\n"
	.string "Είμαι σίγουρος ότι όλα θα πάνε καλά.\p"
	.string "Δηλαδή, νομίζω…\p"
	.string "Αλλά θυμάσαι εκείνον τον τεράστιο\n"
	.string "τύπο; Είπε, “Θα σου δανείσω POKéMON!”$"

BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons:
	.string "Εκεί είναι το BATTLE FACTORY.\n"
	.string "Μπορείς να δανειστείς δυνατά POKéMON.\p"
	.string "Αλλά με βάζει σε σκέψεις.\n"
	.string "Ποιο άτομο μεγαλώνει τα ενοικιαζόμενα;$"

BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper:
	.string "Φοβάμαι να μπω στο BATTLE PIKE\n"
	.string "λόγω του SEVIPER…\p"
	.string "Μ-μα ήρθα μέχρι εδώ, οπότε θα\n"
	.string "προσπαθήσω να κατακτήσω τα πάντα!\l"
	.string "…Τρέμω…$"

BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors:
	.string "Ας παίξουμε πέτρα, ψαλίδι, χαρτί!\n"
	.string "Ένα, δύο, τρία!\p"
	.string "… … … … … …$"

BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge:
	.string "Γιούπι! Κέρδισα!\n"
	.string "Θα πάρω το BATTLE PIKE challenge!$"

BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge:
	.string "Ω, όχι…\n"
	.string "Έχασα.\p"
	.string "Μάλλον δεν είμαι πολύ τυχερό άτομο\n"
	.string "σήμερα. Θα αναβάλω το BATTLE PIKE\l"
	.string "challenge μου για αύριο.$"

BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling:
	.string "Πιστεύω ότι είμαι το μόνο άτομο εδώ που,\n"
	.string "για κάποιο λόγο, θα διάλεγε\l"
	.string "το ψάρεμα από τις μάχες.\p"
	.string "Ε; Δεν μπορείς να πιάσεις τίποτα εδώ;\n"
	.string "Αυτό είναι απογοητευτικό…$"

BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol:
	.string "Σήμερα, θα συνεχίσω να πολεμάω, \n"
	.string "μέχρι να πάρω ένα Symbol.$"

BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome:
	.string "Ω; Πας να προκαλέσεις στο\n"
	.string "BATTLE DOME;\p"
	.string "Σου εύχομαι καλή τύχη.\n"
	.string "Ας ανεβούμε και τα δυο μας στην κορυφή\l"
	.string "και ας συναντηθούμε σε challenges.$"

BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa:
	.string "Παππού, εδώ!\n"
	.string "Το BATTLE DOME είναι εδώ!\l"
	.string "Πήγαινε φάτους, Παππού!$"

BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe:
	.string "Α, οπότε αυτό εδώ είναι το BATTLE DOME;\n"
	.string "Δεν θα αφήσω GENTLEMEN να με νικήσουν!\p"
	.string "Αλλά πού είναι η είσοδος;$"

BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo:
	.string "Δεν υπήρχε τίποτα εδώ πριν από\n"
	.string "λίγο καιρό.\p"
	.string "Αλλά, τώρα κοίτα αυτό το μέρος! Τέλειο!\n"
	.string "Θα φέρω τη μητέρα μου να το δει.$"

BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier:
	.string "Επιτέλους έφτασα στο BATTLE\n"
	.string "FRONTIER!\p"
	.string "Είμαι σίγουρη ότι θα τραβήξω την\n"
	.string "προσοχή με την εμφάνιση και την τέχνη!$"

BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople:
	.string "Μαμ, μαμ…\p"
	.string "Φαίνεται ότι αυτή η πλατεία είναι\n"
	.string "γεμάτη με σκληρά άτομα.\p"
	.string "Μαμ, μαμ…$"

BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike:
	.string "Κρατς, μαμ…\p"
	.string "Πριν από λίγο καιρό, γνώρισα μία\n"
	.string "κοπέλα στο BATTLE PIKE.\p"
	.string "Είχε κάτι μάτια που ήταν\n"
	.string "τρομακτικά.\p"
	.string "Κρατς, μαμ…\p"
	.string "Ήταν έξαλλη: “Θα σταματήσεις\n"
	.string "να τρως;!” Και μετά μου έδωσε μία.\p"
	.string "Ήταν μια ανατριχιαστική τρομακτική\n"
	.string "εμπειρία, σίγουρα.\p"
	.string "Κρατς, μαμ…$"

BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet:
	.string "Ε; Τι λες;\n"
	.string "Αυτό δεν είναι τίποτα!\p"
	.string "Κοίτα, την τελευταία φορά που τον\n"
	.string "ζητωκραύγαζα, τα μάτια μας\l"
	.string "συναντήθηκαν και πετάχτηκαν σπίθες!$"

BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering:
	.string "Τιιιιι;!\n"
	.string "Πφφτ!\p"
	.string "Αυτό συνέβη μόνο επειδή\n"
	.string "έτυχε να κάθομαι δίπλα σου!\p"
	.string "Ο DOME ACE κοίταξε προς το μέρος μας\n"
	.string "επειδή οι ζητωκραυγές μου ήταν δυνατές!$"

BattleFrontier_OutsideWest_Text_DomeAceIsMine:
	.string "Ω, σώπα!\n"
	.string "Μη κάνεις τόσο θόρυβο!\p"
	.string "Εσείς οι καιροσκόποι οπαδοί θα έπρεπε\n"
	.string "να φωνάζετε μόνο για έναν GYM LEADER!\p"
	.string "Ο DOME ACE είναι δικός μου!\n"
	.string "Το μόνο είδωλο για μένα!$"

BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers:
	.string "Δες τα άτομα που τσακώνονται εκεί…\p"
	.string "Είναι δύσκολο να το πιστέψεις, αλλά\n"
	.string "ήταν TRAINERS, και μάλιστα καλοί.\p"
	.string "Ήταν απίστευτα δυνατοί,\n"
	.string "και ήταν διάσημοι, επίσης.\p"
	.string "Αλλά κατατροπώθηκαν από το\n"
	.string "συγκεκριμένο άτομο σε ένα τουρνουά.\p"
	.string "Xτυπήθηκαν τόσο άσχημα,\n"
	.string "που τους έγινε εμμονή το άτομο αυτό.\p"
	.string "Τώρα είναι απλώς θαυμαστές του TRAINER.\n"
	.string "Πάνε να χειροκροτήσουν το είδωλό τους \l"
	.string "στο BATTLE DOME κάθε μέρα πλέον.$"

BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier:
	.string "Άκουσα μια φήμη ότι κάποιο άτομο\n"
	.string "είδε ένα POKéMON με τεράστια ουρά\l"
	.string "στο BATTLE FRONTIER.\p"
	.string "Πρέπει να είναι αξιολάτρευτο. Είμαι σίγουρη…\p"
	.string "Ω, τα παιχνίδια μπορούν να περιμένουν.\n"
	.string "Νιώθω την ανάγκη να βρω αυτό το τέλειο\l"
	.string "πλάσμα!$"

