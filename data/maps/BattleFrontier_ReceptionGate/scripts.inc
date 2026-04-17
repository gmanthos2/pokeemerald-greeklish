.set LOCALID_GREETER, 1
.set LOCALID_GUIDE, 2
.set LOCALID_SCOTT, 4

BattleFrontier_ReceptionGate_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_ReceptionGate_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_ReceptionGate_OnTransition
	.byte 0

BattleFrontier_ReceptionGate_OnTransition:
	setflag FLAG_LANDMARK_BATTLE_FRONTIER
	end

BattleFrontier_ReceptionGate_OnFrame:
	map_script_2 VAR_HAS_ENTERED_BATTLE_FRONTIER, 0, BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering
	.2byte 0

BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering::
	lockall
	setvar VAR_HAS_ENTERED_BATTLE_FRONTIER, 1
	playse SE_PIN
	applymovement LOCALID_GREETER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_GREETER, Common_Movement_Delay48
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter
	waitmovement 0
	goto BattleFrontier_ReceptionGate_EventScript_ScottScene
	end

BattleFrontier_ReceptionGate_EventScript_ScottScene::
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IssueFrontierPass, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass
	waitfanfare
	waitmessage
	msgbox BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass, MSGBOX_DEFAULT
	setflag FLAG_SYS_FRONTIER_PASS
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GREETER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_GUIDE, Common_Movement_WalkInPlaceFasterUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_GREETER, Common_Movement_ExclamationMark
	applymovement LOCALID_GUIDE, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GREETER, BattleFrontier_ReceptionGate_Movement_GreeterFaceScott
	applymovement LOCALID_GUIDE, BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerFaceScott
	applymovement LOCALID_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottEnter
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_SCOTT
	releaseall
	end

BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter:
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_PlayerFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

@ Unused
BattleFrontier_ReceptionGate_Movement_WalkDown:
	walk_down
	walk_down
	step_end

BattleFrontier_ReceptionGate_Movement_ScottEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_ScottExit:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_ReceptionGate_Movement_GreeterFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

BattleFrontier_ReceptionGate_EventScript_Greeter::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FacilityGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFacilities, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich2
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BF_RECEPTIONIST
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_BattleTower
	case 1, BattleFrontier_ReceptionGate_EventScript_BattleDome
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePalace
	case 3, BattleFrontier_ReceptionGate_EventScript_BattleArena
	case 4, BattleFrontier_ReceptionGate_EventScript_BattleFactory
	case 5, BattleFrontier_ReceptionGate_EventScript_BattlePike
	case 6, BattleFrontier_ReceptionGate_EventScript_BattlePyramid
	case 7, BattleFrontier_ReceptionGate_EventScript_RankingHall
	case 8, BattleFrontier_ReceptionGate_EventScript_ExchangeCorner
	case 9, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	end

BattleFrontier_ReceptionGate_EventScript_BattleTower::
	msgbox BattleFrontier_ReceptionGate_Text_BattleTowerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleDome::
	msgbox BattleFrontier_ReceptionGate_Text_BattleDomeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePalace::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePalaceInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleArena::
	msgbox BattleFrontier_ReceptionGate_Text_BattleArenaInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleFactory::
	msgbox BattleFrontier_ReceptionGate_Text_BattleFactoryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePike::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePikeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePyramid::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePyramidInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RankingHall::
	msgbox BattleFrontier_ReceptionGate_Text_RankingHallInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExchangeCorner::
	msgbox BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_RulesGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToRules, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhat
	waitmessage
	multichoice 15, 0, MULTI_FRONTIER_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_LevelMode
	case 1, BattleFrontier_ReceptionGate_EventScript_Level50
	case 2, BattleFrontier_ReceptionGate_EventScript_OpenLevel
	case 3, BattleFrontier_ReceptionGate_EventScript_MonEntry
	case 4, BattleFrontier_ReceptionGate_EventScript_HoldItems
	case 5, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	end

BattleFrontier_ReceptionGate_EventScript_LevelMode::
	msgbox BattleFrontier_ReceptionGate_Text_LevelModeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_Level50::
	msgbox BattleFrontier_ReceptionGate_Text_Level50Info, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_OpenLevel::
	msgbox BattleFrontier_ReceptionGate_Text_OpenLevelInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_MonEntry::
	msgbox BattleFrontier_ReceptionGate_Text_MonEntryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_HoldItems::
	msgbox BattleFrontier_ReceptionGate_Text_HoldItemsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FrontierPassGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich1
	waitmessage
	multichoice 16, 4, MULTI_FRONTIER_PASS_INFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_Symbols
	case 1, BattleFrontier_ReceptionGate_EventScript_RecordBattle
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePoints
	case 3, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	end

BattleFrontier_ReceptionGate_EventScript_Symbols::
	msgbox BattleFrontier_ReceptionGate_Text_SymbolsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RecordBattle::
	msgbox BattleFrontier_ReceptionGate_Text_RecordedBattleInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePoints::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePointsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay:
	.string "Είναι η πρώτη σου φορά εδώ;\n"
	.string "Παρακαλώ, πέρνα από εδώ!$"

BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier:
	.string "Οι πρώτες γραμμές των POKéMON μαχών!\n"
	.string "Καλώς ήρθες στο BATTLE FRONTIER!$"

BattleFrontier_ReceptionGate_Text_IssueFrontierPass:
	.string "Για όσους έρχονται για πρώτη φορά,\n"
	.string "εκδίδουμε το FRONTIER PASS.\p"
	.string "Χρησιμοποιείται σε όλες τις \n"
	.string "εγκαταστάσεις του BATTLE FRONTIER.\p"
	.string "Ορίστε!$"

BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass:
	.string "Το {PLAYER} πήρε\n"
	.string "το FRONTIER PASS.$"

BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass:
	.string "Το {PLAYER} έβαλε την TRAINER CARD\n"
	.string "στο FRONTIER PASS.$"

BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier:
	.string "Ελπίζουμε να απολαύσεις ό,τι έχει να\n"
	.string "προσφέρει το BATTLE FRONTIER!$"

BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame:
	.string "???: Λοιπόν, λοιπόν, ποιον βλέπω,\n"
	.string "το {PLAYER}{KUN}! Κατάφερες να έρθεις!$"

BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay:
	.string "GUIDE: Ω! Κύριε SCOTT!\n"
	.string "Καλή σας μέρα, κύριε!$"

BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere:
	.string "SCOTT: Είναι υπέροχο που σε βλέπω εδώ,\n"
	.string "πραγματικά είναι!\p"
	.string "Ελπίζω να πάρεις το χρόνο σου και\n"
	.string "να εξερευνήσεις παντού.\p"
	.string "Και φυσικά, ελπίζω να βιώσεις \n"
	.string "και την αγνή ουσία της μάχης.\p"
	.string "Έχω κι εγώ τα δωμάτιά μου εδώ, γι' αυτό\n"
	.string "μη διστάσεις να έρθεις αν έχεις χρόνο.$"

BattleFrontier_ReceptionGate_Text_YourGuideToFacilities:
	.string "Είμαι ο οδηγός σου για τις διάφορες\n"
	.string "εγκαταστάσεις εδώ στο BATTLE FRONTIER.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich2:
	.string "Για ποια από όλες θα ήθελες να μάθεις;$"

BattleFrontier_ReceptionGate_Text_BattleTowerInfo:
	.string "Είναι ο γιγαντιαίος πύργος που \n"
	.string "θεωρείται το σύμβολο του FRONTIER.\p"
	.string "Υπάρχουν τέσσερα είδη BATTLE ROOMS\n"
	.string "στον πύργο για SINGLE, DOUBLE, MULTI,\l"
	.string "και LINK MULTI BATTLES.$"

BattleFrontier_ReceptionGate_Text_BattleDomeInfo:
	.string "Το BATTLE DOME είναι το μεγάλο κτίριο\n"
	.string "που έχει σχήμα ενός τεράστιου αυγού.\p"
	.string "Αγώνες που ονομάζονται Battle Tourneys\n"
	.string "πραγματοποιούνται σε αυτήν την\l"
	.string "εγκατάσταση.\p"
	.string "Tα Battle Tourneys προσφέρονται σε\n"
	.string "δύο courses--για SINGLE και DOUBLE\l"
	.string "BATTLES.$"

BattleFrontier_ReceptionGate_Text_BattlePalaceInfo:
	.string "Το BATTLE PALACE είναι το κόκκινο\n"
	.string "κτίριο δεξιά του BATTLE FRONTIER.\p"
	.string "Υπάρχουν δύο είδη BATTLE HALLS\n"
	.string "για SINGLE και DOUBLE BATTLES.$"

BattleFrontier_ReceptionGate_Text_BattleArenaInfo:
	.string "Η BATTLE ARENA είναι το κτίριο που\n"
	.string "μοιάζει με ντότζο στο κέντρο-δεξιά του\l"
	.string "BATTLE FRONTIER.\p"
	.string "Ένα event που λέγεται Set KO Tourney\n"
	.string "λαμβάνει χώρα στην BATTLE ARENA.$"

BattleFrontier_ReceptionGate_Text_BattleFactoryInfo:
	.string "Το BATTLE FACTORY είναι το μεγάλο\n"
	.string "κτίριο που βρίσκεται πιο κοντά σε μας.\p"
	.string "Εκεί διεξάγεται ένα event που\n"
	.string "ονομάζεται Battle Swap.\p"
	.string "To event Battle Swap προσφέρεται\n"
	.string "σε δύο courses για SINGLE και DOUBLE\l"
	.string "BATTLES.$"

BattleFrontier_ReceptionGate_Text_BattlePikeInfo:
	.string "Tο BATTLE PIKE είναι το κτίριο που\n"
	.string "έχει σχήμα POKéMON κι είναι αριστερά\l"
	.string "στο BATTLE FRONTIER.\p"
	.string "Εκεί διεξάγεται ένα event που\n"
	.string "ονομάζεται Battle Choice.$"

BattleFrontier_ReceptionGate_Text_BattlePyramidInfo:
	.string "Η BATTLE PYRAMID είναι η τεράστια\n"
	.string "πυραμίδα.\p"
	.string "Εκεί διεξάγεται ένα event που\n"
	.string "ονομάζεται Battle Quest.$"

BattleFrontier_ReceptionGate_Text_RankingHallInfo:
	.string "Το RANKING HALL βρίσκεται κοντά\n"
	.string "στο BATTLE TOWER.\p"
	.string "Εκεί, μπορείτε να δείτε τα φανταστικά\n"
	.string "ρεκόρ που άφησαν οι TRAINERS που\l"
	.string "αντιμετώπισαν τις προκλήσεις του\l"
	.string "BATTLE FRONTIER.$"

BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo:
	.string "Το EXCHANGE SERVICE CORNER\n"
	.string "είναι κοντά στο BATTLE TOWER.\p"
	.string "Τα Battle Points που έχετε κερδίσει \n"
	.string "στο BATTLE FRONTIER μπορούν να\l"
	.string "ανταλλαχθούν με υπέροχα δώρα εκεί.$"

BattleFrontier_ReceptionGate_Text_YourGuideToRules:
	.string "Είμαι ο οδηγός σας για τους βασικούς\n"
	.string "κανόνες που είναι κοινοί σε όλες τις\l"
	.string "προκλήσεις που προσφέρουν οι \l"
	.string "εγκαταστάσεις του BATTLE FRONTIER.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhat:
	.string "Τι θα θέλατε να μάθετε;$"

BattleFrontier_ReceptionGate_Text_LevelModeInfo:
	.string "Όλες οι προκλήσεις στις εγκαταστάσεις\n"
	.string "του BATTLE FRONTIER δίνονται σε\l"
	.string "δύο courses -- Level 50 & Open Level.$"

BattleFrontier_ReceptionGate_Text_Level50Info:
	.string "Tο Level 50 course είναι ανοιχτό στα \n"
	.string "POKéMON μέχρι και το Level 50.\p"
	.string "Λάβετε υπόψη, ωστόσο, ότι κανένας \n"
	.string "TRAINER που αντιμετωπίζετε δεν θα\l"
	.string "έχει POKéMON κάτω από το Level 50.\p"
	.string "Αυτό το course είναι το entry level\n"
	.string "για μάχες στο BATTLE FRONTIER.\p"
	.string "Για αρχή, ελπίζουμε να δοκιμάσετε\n"
	.string "αυτό το course.$"

BattleFrontier_ReceptionGate_Text_OpenLevelInfo:
	.string "Το Open Level Course δεν θέτει όριο\n"
	.string "στα levels των POKéMON που μπαίνουν\l"
	.string "στις προκλήσεις.\p"
	.string "Τα levels των αντιπάλων σας θα\n"
	.string "ρυθμιστούν ώστε να ταιριάζουν με\l"
	.string "τα levels των POKéMON σας.\p"
	.string "Ωστόσο, κανένας TRAINER που \n"
	.string "αντιμετωπίζετε δεν θα έχει\l"
	.string "POKéMON κάτω από το Level 60.$"

BattleFrontier_ReceptionGate_Text_MonEntryInfo:
	.string "Οποιοδήποτε είδος POKéMON μπορεί να\n"
	.string "αντιμετωπίσει τις προκλήσεις σε \l"
	.string "όλες τις εγκαταστάσεις.\p"
	.string "Tα EGGs και ορισμένα είδη POKéMON,\n"
	.string "ωστόσο, δεν επιτρέπονται.\p"
	.string "Ο αριθμός των POKéMON που \n"
	.string "απαιτούνται για τις προκλήσεις θα \l"
	.string "εξαρτηθεί από την εγκατάσταση.\p"
	.string "Σε όλες τις εγκαταστάσεις,\n"
	.string "δύο ή περισσότερα POKéMON ιδίου \l"
	.string "είδους δεν επιτρέπονται.$"

BattleFrontier_ReceptionGate_Text_HoldItemsInfo:
	.string "Όταν μπαίνετε σε μια πρόκληση \n"
	.string "σε μια εγκατάσταση BATTLE FRONTIER, τα\l"
	.string "POKéMON μπορεί να μην κρατούν το \l"
	.string "ίδιο είδος αντικειμένου.\p"
	.string "Βεβαιωθείτε ότι όλα τα POKéMON που\n"
	.string "συμμετέχουν σε μια πρόκληση κρατούν\l"
	.string "διαφορετικά αντικείμενα.$"

BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass:
	.string "Είμαι ο οδηγός σας για το FRONTIER \n"
	.string "PASS.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich1:
	.string "Για ποιο θα θέλατε να μάθετε;$"

BattleFrontier_ReceptionGate_Text_SymbolsInfo:
	.string "Υπάρχουν επτά εγκαταστάσεις στο\n"
	.string "BATTLE FRONTIER.\p"
	.string "Οι TRAINERS που κερδίζουν αναγνώριση\n"
	.string "αναγνώριση για τις ικανότητές τους\l"
	.string "μπορούν να ανταμειφθούν με symbols\l"
	.string "από κάθε εγκατάσταση.\p"
	.string "Για να κερδίσουν ένα symbol, ίσως να\n"
	.string "χρειαστεί να νικήσουν κι άλλους\l"
	.string "TRAINERS στη σειρά, και μπορεί να \l"
	.string "χρειαστεί να κερδίζουν συχνά events.\p"
	.string "Σίγουρα δεν είναι εύκολο να κερδίσεις\n"
	.string "τα symbols. Καλή Επιτυχία!$"

BattleFrontier_ReceptionGate_Text_RecordedBattleInfo:
	.string "Είναι δυνατή η καταγραφή μιας\n"
	.string "μάχης στο FRONTIER PASS σας.\p"
	.string "Μπορείτε να καταγράψετε μια μάχη που\n"
	.string "είχατε με έναν φίλο ή φίλους σας.\p"
	.string "Ή, μπορείτε να καταγράψετε μία μάχη \n"
	.string "από το BATTLE FRONTIER (εξαιρούνται \l"
	.string "τα BATTLE PIKE και BATTLE PYRAMID).\p"
	.string "Μπορείτε να επιλέξετε να \n"
	.string "καταγράψετε τον αγώνα σας \l"
	.string "στο τέλος μιας μάχης.$"

BattleFrontier_ReceptionGate_Text_BattlePointsInfo:
	.string "Τα Battle Points είναι ανταμοιβές \n"
	.string "που δίνονται στους TRAINERS που \l"
	.string "μάχονταν εξαιρετικά\l"
	.string "στο BATTLE FRONTIER.\p"
	.string "Μπορείτε να ανταλλάξετε τα \n"
	.string "Battle Points με βραβεία στο\l"
	.string "EXCHANGE SERVICE CORNER.$"

