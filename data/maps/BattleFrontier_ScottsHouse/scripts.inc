.set LOCALID_SCOTT, 1

BattleFrontier_ScottsHouse_MapScripts::
	.byte 0

BattleFrontier_ScottsHouse_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_TEMP_4, BattleFrontier_ScottsHouse_EventScript_GivenBerry
	goto_if_set FLAG_TEMP_3, BattleFrontier_ScottsHouse_EventScript_GivenShield
	goto_if_set FLAG_TEMP_2, BattleFrontier_ScottsHouse_EventScript_GivenBattlePoints
	goto BattleFrontier_ScottsHouse_EventScript_CheckGiveItems
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveItems::
	goto_if_unset FLAG_SCOTT_GIVES_BATTLE_POINTS, BattleFrontier_ScottsHouse_EventScript_WelcomeToFrontier
	goto_if_unset FLAG_COLLECTED_ALL_SILVER_SYMBOLS, BattleFrontier_ScottsHouse_EventScript_CheckSilverSymbols
	goto_if_unset FLAG_COLLECTED_ALL_GOLD_SYMBOLS, BattleFrontier_ScottsHouse_EventScript_CheckGoldSymbols
	goto BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveShield::
	goto_if_unset FLAG_RECEIVED_SILVER_SHIELD, BattleFrontier_ScottsHouse_EventScript_CheckGiveSilverShield
	goto_if_unset FLAG_RECEIVED_GOLD_SHIELD, BattleFrontier_ScottsHouse_EventScript_CheckGiveGoldShield
	goto BattleFrontier_ScottsHouse_EventScript_RandomComment
	end

BattleFrontier_ScottsHouse_EventScript_CheckSilverSymbols::
	goto_if_unset FLAG_SYS_TOWER_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_DOME_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PALACE_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_ARENA_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_FACTORY_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PIKE_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PYRAMID_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	msgbox BattleFrontier_ScottsHouse_Text_YouveCollectedAllSilverSymbols, MSGBOX_DEFAULT
	giveitem ITEM_LANSAT_BERRY
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_BerryPocketFull
	setflag FLAG_COLLECTED_ALL_SILVER_SYMBOLS
	setflag FLAG_TEMP_4
	release
	end

BattleFrontier_ScottsHouse_EventScript_CheckGoldSymbols::
	goto_if_unset FLAG_SYS_TOWER_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_DOME_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PALACE_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_ARENA_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_FACTORY_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PIKE_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PYRAMID_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	msgbox BattleFrontier_ScottsHouse_Text_YouveCollectedAllGoldSymbols, MSGBOX_DEFAULT
	giveitem ITEM_STARF_BERRY
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_BerryPocketFull
	setflag FLAG_COLLECTED_ALL_GOLD_SYMBOLS
	setflag FLAG_TEMP_4
	release
	end

BattleFrontier_ScottsHouse_EventScript_BerryPocketFull::
	msgbox BattleFrontier_ScottsHouse_Text_BerryPocketStuffed, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_GivenBerry::
	msgbox BattleFrontier_ScottsHouse_Text_SoGladIBroughtYouHere, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_RandomComment::
	random 3
	goto_if_eq VAR_RESULT, 1, BattleFrontier_ScottsHouse_EventScript_FrontierBrainComment
	goto_if_eq VAR_RESULT, 2, BattleFrontier_ScottsHouse_EventScript_ArtisanCaveComment
	msgbox BattleFrontier_ScottsHouse_Text_WhyIGoSeekingTrainers, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_FrontierBrainComment::
	msgbox BattleFrontier_ScottsHouse_Text_HaveYouMetFrontierBrain, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_ArtisanCaveComment::
	msgbox BattleFrontier_ScottsHouse_Text_MayFindWildMonsInFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveSilverShield::
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 50, BattleFrontier_ScottsHouse_EventScript_GiveSilverShield
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_OPEN
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 50, BattleFrontier_ScottsHouse_EventScript_GiveSilverShield
	goto BattleFrontier_ScottsHouse_EventScript_RandomComment
	end

BattleFrontier_ScottsHouse_EventScript_GiveSilverShield::
	msgbox BattleFrontier_ScottsHouse_Text_Beat50TrainersInARow, MSGBOX_DEFAULT
	givedecoration DECOR_SILVER_SHIELD
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_NoRoomForShield
	setflag FLAG_RECEIVED_SILVER_SHIELD
	setflag FLAG_TEMP_3
	goto BattleFrontier_ScottsHouse_EventScript_GivenShield
	end

BattleFrontier_ScottsHouse_EventScript_NoRoomForShield::
	msgbox BattleFrontier_ScottsHouse_Text_ComeBackForThisLater, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_GivenShield::
	msgbox BattleFrontier_ScottsHouse_Text_ExpectingToHearEvenGreaterThings, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveGoldShield::
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 100, BattleFrontier_ScottsHouse_EventScript_GiveGoldShield
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_OPEN
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 100, BattleFrontier_ScottsHouse_EventScript_GiveGoldShield
	goto BattleFrontier_ScottsHouse_EventScript_RandomComment
	end

BattleFrontier_ScottsHouse_EventScript_GiveGoldShield::
	msgbox BattleFrontier_ScottsHouse_Text_Beat100TrainersInARow, MSGBOX_DEFAULT
	givedecoration DECOR_GOLD_SHIELD
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_NoRoomForShield
	setflag FLAG_RECEIVED_GOLD_SHIELD
	setflag FLAG_TEMP_3
	goto BattleFrontier_ScottsHouse_EventScript_GivenShield
	end

BattleFrontier_ScottsHouse_EventScript_GivenBattlePoints::
	msgbox BattleFrontier_ScottsHouse_Text_ExpectingGreatThings, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_WelcomeToFrontier::
	msgbox BattleFrontier_ScottsHouse_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	closemessage
	delay 30
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayNorth
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_ScottsHouse_EventScript_ScottFaceAwaySouth
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayEast
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayWest
	msgbox BattleFrontier_ScottsHouse_Text_HowMuchEffortItTookToMakeReal, MSGBOX_DEFAULT
	applymovement LOCALID_SCOTT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_ScottsHouse_Text_HaveThisAsMementoOfOurPathsCrossing, MSGBOX_DEFAULT
	goto_if_eq VAR_SCOTT_STATE, 13, BattleFrontier_ScottsHouse_EventScript_Give4BattlePoints
	goto_if_ge VAR_SCOTT_STATE, 9, BattleFrontier_ScottsHouse_EventScript_Give3BattlePoints
	goto_if_ge VAR_SCOTT_STATE, 6, BattleFrontier_ScottsHouse_EventScript_Give2BattlePoints
	goto BattleFrontier_ScottsHouse_EventScript_Give1BattlePoint
	end

BattleFrontier_ScottsHouse_EventScript_Give4BattlePoints::
	buffernumberstring STR_VAR_1, 4
	setvar VAR_0x8004, 4
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_Give3BattlePoints::
	buffernumberstring STR_VAR_1, 3
	setvar VAR_0x8004, 3
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_Give2BattlePoints::
	buffernumberstring STR_VAR_1, 2
	setvar VAR_0x8004, 2
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_Give1BattlePoint::
	buffernumberstring STR_VAR_1, 1
	setvar VAR_0x8004, 1
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints::
	special GiveFrontierBattlePoints
	msgbox BattleFrontier_ScottsHouse_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	msgbox BattleFrontier_ScottsHouse_Text_ExplainBattlePoints, MSGBOX_DEFAULT
	setflag FLAG_SCOTT_GIVES_BATTLE_POINTS
	setflag FLAG_TEMP_2
	release
	end

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayNorth::
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwaySouth::
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayEast::
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayWest::
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

BattleFrontier_ScottsHouse_Text_WelcomeToBattleFrontier:
	.string "SCOTT: Ε, γεια σου και καλώς ήρθες!\n"
	.string "Χεχε… Συγγνώμη για τον στενό χώρο.\p"
	.string "Τέλος πάντων, {PLAYER}{KUN}, επίτρεψέ \n"
	.string "μου να σε καλωσορίσω επίσημα στο \l"
	.string "BATTLE FRONTIER.\p"
	.string "Αυτό είναι το όνειρό μου που\n"
	.string "έγινε πραγματικότητα.\l"
	.string "Μου πήρε χρόνια, αλλά επιτέλους\l"
	.string "το όνειρό μου πήρε μορφή.$"

BattleFrontier_ScottsHouse_Text_HowMuchEffortItTookToMakeReal:
	.string "Τώρα που το σκέφτομαι, ήταν ένα \n"
	.string "τρομερά μακρύ ταξίδι…\p"
	.string "Έφυγα από το σπίτι μόνος σε μια \n"
	.string "αναζήτηση για δυνατούς TRAINERS.\p"
	.string "Κανείς δεν μπορεί να φανταστεί πόση \n"
	.string "προσπάθεια ή χρόνο χρειάστηκε για να \l"
	.string "γίνει αυτό πραγματικότητα.$"

BattleFrontier_ScottsHouse_Text_HaveThisAsMementoOfOurPathsCrossing:
	.string "Αλλά αυτά ανήκουν στο παρελθόν.\n"
	.string "Δεν έχει νόημα να σταθούμε εκεί!\p"
	.string "Το μόνο που θέλω για 'σένα είναι να\n"
	.string "απολαύσεις τις μάχες με την ψυχή σου.\p"
	.string "{PLAYER}{KUN}, θέλω να το έχεις αυτό \n"
	.string "σαν ενθύμιο για όλον αυτόν τον χρόνο\l"
	.string "που διασταυρώθηκαν οι δρόμοι μας.$"

BattleFrontier_ScottsHouse_Text_ObtainedXBattlePoints:
	.string "Το {PLAYER} πήρε\n"
	.string "{STR_VAR_1} Battle Point(s).$"

BattleFrontier_ScottsHouse_Text_ExplainBattlePoints:
	.string "SCOTT: Μπορείς να ελέγξεις τα Battle\n"
	.string "Points σου στο FRONTIER PASS.\p"
	.string "Όση περισσότερη επιτυχία έχεις εδώ \n"
	.string "στο BATTLE FRONTIER, τόσα\l"
	.string "περισσότερα Battle Points θα μαζεύεις.\p"
	.string "Χρησιμοποίησε τα Battle Points σου \n"
	.string "όπως νομίζεις, όπως το να τα \l"
	.string "ανταλλάσσεις για items.$"

BattleFrontier_ScottsHouse_Text_ExpectingGreatThings:
	.string "Περιμένω σπουδαία πράγματα από σένα!$"

BattleFrontier_ScottsHouse_Text_WhyIGoSeekingTrainers:
	.string "SCOTT: Κάθε TRAINER είναι ξεχωριστός.\n"
	.string "Όλοι ζουν τις δικές τους ζωές.\p"
	.string "Αλλά όταν βρίσκονται σε μάχη,\n"
	.string "δεν έχει σημασία ποιοι είναι.\p"
	.string "Είναι όλοι το ίδιο!\p"
	.string "Λατρεύω την αγνότητα της μάχης,\n"
	.string "όπου όλοι είναι ίσοι.\p"
	.string "Γι' αυτό πηγαίνω παντού ψάχνοντας\n"
	.string "TRAINERS που ασχολούνται σοβαρά \l"
	.string "με τις μάχες, και τους καλώ εδώ.$"

BattleFrontier_ScottsHouse_Text_HaveYouMetFrontierBrain:
	.string "SCOTT: Έχεις γνωρίσει\n"
	.string "κάποιον από τους FRONTIER BRAINS;\p"
	.string "Ή μάλλον, έχεις πάρει κάποια \n"
	.string "symbols από αυτούς;\p"
	.string "Επέλεξα τους FRONTIER BRAINS ώστε\n"
	.string "να είναι οι πιο σκληροί TRAINERS.\p"
	.string "Αλλά είμαι σίγουρος ότι βλέποντας πόσο\n"
	.string "σκληρός είσαι, θα ξαφνιαστούν κι \l"
	.string "αυτοί!$"

BattleFrontier_ScottsHouse_Text_MayFindWildMonsInFrontier:
	.string "SCOTT: Δεν προπονείσαι μόνο για\n"
	.string "μάχες, ε;\p"
	.string "Νομίζω θυμάμαι να συπληρώνεις\n"
	.string "και το POKéDEX σου.\p"
	.string "Λοιπόν, μάντεψε.\p"
	.string "Μπορεί να συναντήσεις άγρια POKéMON\n"
	.string "κάπου στο BATTLE FRONTIER…\l"
	.string "Φουφουφου!$"

BattleFrontier_ScottsHouse_Text_YouveCollectedAllSilverSymbols:
	.string "SCOTT: Απολαμβάνεις τα πράγματα\n"
	.string "στο BATTLE FRONTIER;\p"
	.string "…Μισό λεπτό…\n"
	.string "Ω!\p"
	.string "Το FRONTIER PASS σου!\n"
	.string "Έχεις μαζέψει το πλήρες σετ\l"
	.string "από ασημένια symbols!\p"
	.string "Αυτό είναι κάτι περισσότερο από \n"
	.string "εντυπωσιακό!\l"
	.string "Είσαι σκληρός, όπως το υποψιαζόμουν!\p"
	.string "Κανονικά, δεν θα έκανα \n"
	.string "κάτι τέτοιο, αλλά είναι ειδική περίσταση!\p"
	.string "Θέλω να το έχεις αυτό.\n"
	.string "Είμαι σίγουρος ότι θα το χρειαστείς.$"

BattleFrontier_ScottsHouse_Text_YouveCollectedAllGoldSymbols:
	.string "SCOTT: Ελπίζω να απολαμβάνεις \n"
	.string "τα πάντα στο BATTLE FRONTIER.\p"
	.string "…Μισό λεπτό…\n"
	.string "Ω, τι βλέπουν τα μάτια μου!\p"
	.string "Το FRONTIER PASS σου!\n"
	.string "Έχεις συγκεντρώσει όλο το σετ\l"
	.string "από χρυσά symbols!\p"
	.string "Αυτό είναι κάτι παραπάνω \n"
	.string "από εκπληκτικό!\l"
	.string "Είσαι απίστευτος, όπως το υποψιαζόμουν!\p"
	.string "… … … … … …\p"
	.string "{PLAYER}, πρέπει να το δεχτείς αυτό!\p"
	.string "Νομίζω ότι θα μπορέσεις να \n"
	.string "εκτιμήσεις την αξία του δώρου μου!$"

BattleFrontier_ScottsHouse_Text_SoGladIBroughtYouHere:
	.string "Πρέπει να πω ότι έχω το χάρισμα να\n"
	.string "καταλαβαίνω έναν καλό TRAINER \l"
	.string "μόλις τον βλέπω.\p"
	.string "Χαίρομαι τόσο πολύ που είχα \n"
	.string "την προνοητικότητα να σε φέρω εδώ!$"

BattleFrontier_ScottsHouse_Text_BerryPocketStuffed:
	.string "Το BERRY POCKET σου φαίνεται\n"
	.string "να είναι παραγεμισμένο.$"

BattleFrontier_ScottsHouse_Text_Beat50TrainersInARow:
	.string "SCOTT: Ω, άκουσα για 'σένα!\n"
	.string "Πώς κυριάρχησες στο BATTLE TOWER!\l"
	.string "Νίκησες πάνω από 50 TRAINERS στη σειρά;\p"
	.string "Είναι φανταστικό!\n"
	.string "Θέλω να το έχεις αυτό!$"

BattleFrontier_ScottsHouse_Text_Beat100TrainersInARow:
	.string "SCOTT: Ωχ! Άκουσα για 'σένα!\n"
	.string "Πώς ισοπέδωσες το BATTLE TOWER!\l"
	.string "Νίκησες πάνω από 100 TRAINERS στη σειρά;\p"
	.string "Αυτό είναι γελοία εντυπωσιακό!\n"
	.string "Πρέπει να το έχεις αυτό!$"

BattleFrontier_ScottsHouse_Text_ExpectingToHearEvenGreaterThings:
	.string "Θα περιμένω να ακούσω ακόμα πιο \n"
	.string "σπουδαία πράγματα για 'σένα από δω\l"
	.string "και πέρα!$"

BattleFrontier_ScottsHouse_Text_ComeBackForThisLater:
	.string "Ουπς, λοιπόν, μάλλον έχεις \n"
	.string "πάρα πολλά πράγματα, έλα \l"
	.string "να το πάρεις αργότερα.$"

