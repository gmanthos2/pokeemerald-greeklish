.set LOCALID_SUDOWOODO, 14

BattleFrontier_OutsideEast_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_OutsideEast_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideEast_OnTransition
	.byte 0

BattleFrontier_OutsideEast_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

BattleFrontier_OutsideEast_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	call_if_unset FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_ShowSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_ShowSudowoodo::
	clearflag FLAG_HIDE_BATTLE_FRONTIER_SUDOWOODO
	return

BattleFrontier_OutsideEast_EventScript_BattleTowerSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePalaceSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattleArenaSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleArenaSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePyramidSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_NinjaBoy::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man1::
	msgbox BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Hiker::
	msgbox BattleFrontier_OutsideEast_Text_PyramidTooHarsh, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_HexManiac::
	msgbox BattleFrontier_OutsideEast_Text_ThriveInDarkness, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt1::
	msgbox BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Cook::
	lock
	msgbox BattleFrontier_OutsideEast_Text_BelieveInYouBuddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_OutsideEast_EventScript_RichBoy::
	msgbox BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_ExpertF::
	msgbox BattleFrontier_OutsideEast_Text_OnceBeatGymLeader, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_TriathleteF::
	msgbox BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Twin::
	msgbox BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_TriathleteM::
	msgbox BattleFrontier_OutsideEast_Text_DidScottBringYouHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Sudowoodo::
	lock
	faceplayer
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	release
	end

BattleFrontier_OutsideEast_EventScript_WaterSudowoodo::
	lock
	faceplayer
	special DoWateringBerryTreeAnim
	waitstate
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	msgbox gText_Sudowoodo_Attacked, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SUDOWOODO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_SUDOWOODO
	setwildbattle SPECIES_SUDOWOODO, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	setflag FLAG_DEFEATED_SUDOWOODO
	release
	end

BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo::
	setflag FLAG_DEFEATED_SUDOWOODO
	goto Common_EventScript_RemoveStaticPokemon
	end

BattleFrontier_OutsideEast_Movement_SudowoodoShake:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

BattleFrontier_OutsideEast_EventScript_Maniac1::
	msgbox BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Girl::
	msgbox BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_PsychicM::
	msgbox BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man3::
	msgbox BattleFrontier_OutsideEast_Text_GotWipedOut, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman1::
	msgbox BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman2::
	msgbox BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt2::
	msgbox BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RankingHallSign::
	msgbox BattleFrontier_OutsideEast_Text_RankingHallSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_ExchangeCornerSign::
	msgbox BattleFrontier_OutsideEast_Text_ExchangeCornerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_OldWoman::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone
	msgbox BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone::
	msgbox BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Camper::
	msgbox BattleFrontier_OutsideEast_Text_StickyMonWithLongTail, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Text_BattleTowerSign:
	.string "Αυτό είναι το BATTLE TOWER!\n"
	.string "Διατήρησε το νικηφόρο σερί ως\l"
	.string "το πιο δυνατό άτομο TRAINER!$"

BattleFrontier_OutsideEast_Text_BattlePalaceSign:
	.string "Αυτό είναι το BATTLE PALACE!\n"
	.string "Δώσε προσοχή στις μάχες POKéMON!$"

BattleFrontier_OutsideEast_Text_BattleArenaSign:
	.string "Αυτό είναι το BATTLE ARENA!\n"
	.string "Ας μαζευτούν εδώ οι δυνατότερες ομάδες!$"

BattleFrontier_OutsideEast_Text_BattlePyramidSign:
	.string "Αυτό είναι το BATTLE PYRAMID!\n"
	.string "Προχώρα μέσω του Battle Quest!$"

BattleFrontier_OutsideEast_Text_RankingHallSign:
	.string "BATTLE FRONTIER RANKING HALL\n"
	.string "Βάλε στόχο τα νέα ρεκόρ!$"

BattleFrontier_OutsideEast_Text_ExchangeCornerSign:
	.string "BATTLE POINT EXCHANGE SERVICE CORNER\n"
	.string "Αντάλλαξε τα Battle Points σου!$"

BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial:
	.string "Ουάου!\n"
	.string "Είναι τεράστιο!\p"
	.string "Το BATTLE TOWER έχει άλλη αίσθηση.\n"
	.string "Είναι διαφορετικό από τα υπόλοιπα.$"

BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier:
	.string "Ο μεγάλος μου στόχος είναι να \n"
	.string "κατακτήσω το BATTLE FRONTIER και το\l"
	.string "POKéMON LEAGUE.\p"
	.string "Και αν το όνειρό μου γίνει\n"
	.string "πραγματικότητα…\p"
	.string "Εγώ... θα ζητήσω από τη ΜΙΜΙ της \n"
	.string "διπλανής πόρτας να γίνει φίλη μου!$"

BattleFrontier_OutsideEast_Text_PyramidTooHarsh:
	.string "Το BATTLE PYRAMID είναι πολύ σκληρό!\n"
	.string "Απλά δεν μπορώ να φτάσω στην κορυφή!\p"
	.string "Αφού ξέμεινα από επιλογές, ίσως μπορώ να\n"
	.string "σκαρφαλώσω από έξω…$"

BattleFrontier_OutsideEast_Text_ThriveInDarkness:
	.string "Απολαμβάνω το σκοτάδι…\n"
	.string "Ναι… Τι αξίζει σε μένα;\l"
	.string "Τίποτα άλλο από το BATTLE PYRAMID…\p"
	.string "Τι λες να περιπλανηθείς στο σκοτάδι\n"
	.string "και σε απόλυτη απόγνωση;$"

BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam:
	.string "Δεν κοιμήθηκα για μια εβδομάδα, αλλά\n"
	.string "έπειτα έφτιαξα την απόλυτη ομάδα!\p"
	.string "Δεν γίνεται να χάσω με τίποτα,\n"
	.string "χωρίς πλάκα. Τα σπάμε στο\l"
	.string "BATTLE ARENA!$"

BattleFrontier_OutsideEast_Text_DidScottBringYouHere:
	.string "Σε έφερε και σένα ο SCOTT εδώ;\n"
	.string "Τι παίζει μ' αυτόν τον τύπο;\p"
	.string "Ακούγεται σαν να ξέρει να εντοπίζει\n"
	.string "ταλαντούχα άτομα TRAINERS, αλλά…\p"
	.string "Δεν τον έχω δει ποτέ να παλεύει από\n"
	.string "κοντά.$"

BattleFrontier_OutsideEast_Text_BelieveInYouBuddy:
	.string "ZIGG!\n"
	.string "Πιστεύω σε σένα, φιλαράκο!\p"
	.string "Θα φτιάξω στο μικρό μου ZIGG ό,τι λιχουδιά\n"
	.string "θέλει, αν κερδίσεις!$"

BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant:
	.string "Το ZIGZAGOON δείχνει άδειο…$"

BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody:
	.string "Ο κόσμος με λέει πολυάσχολο άτομο,\n"
	.string "αλλά δεν μπορώ να το αποφύγω.\p"
	.string "Το καπέλο σου είναι στραβό!\n"
	.string "Ω, όχι, σκουπίδια κάτω!\l"
	.string "Ουπς, είναι σχεδόν ώρα για βραδινό!\p"
	.string "Δεν ξέρω αν αντέχω απλά\n"
	.string "να παρακολουθώ στο BATTLE PALACE…$"

BattleFrontier_OutsideEast_Text_OnceBeatGymLeader:
	.string "Μπορεί να μη φαίνομαι και τόσο\n"
	.string "εντυπωσιακό άτομο τώρα, αλλά\l"
	.string "κάποτε νίκησα ένα άτομο GYM LEADER.\p"
	.string "Ποιος ξέρει, ίσως θα πρέπει να δώσω\n"
	.string "άλλη μια ευκαιρία στη δόξα.$"

BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles:
	.string "Είμαι γρήγορο άτομο στο BIKE μου, και\n"
	.string "αυτό ισχύει και για τον τρόπο που μάχομαι.\p"
	.string "Κερδίζω τους αγώνες στο άψι\n"
	.string "σβήσε!$"

BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon:
	.string "Είμαι καλύτερη από τον μπαμπά μου\n"
	.string "στα POKéMON.$"

BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy:
	.string "Μπράβο, γλυκούλι μου!\n"
	.string "Πήγαινε φέρε μερικές νίκες στον\l"
	.string "μπαμπά!\p"
	.string "Είσαι ίδιος η μητέρα σου, οπότε\n"
	.string "θα κυριαρχήσεις!$"

BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena:
	.string "Δεν ήταν εύκολο να φτάσω εδώ,\n"
	.string "αλλά είχα ακούσει για ένα όμορφο\l"
	.string "κορίτσι στο BATTLE ARENA.\p"
	.string "Αντ' αυτής, ξέρεις τι\n"
	.string "βρήκα;\p"
	.string "Ένα τεράστιο πλήθος από ιδρωμένους,\n"
	.string "βρομερούς και πρωτόγονους πολεμιστές!$"

BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere:
	.string "Μερικές φορές βλέπω ένα πολύ σημαντικό\n"
	.string "γέρο να μπαίνει εκεί μέσα.\p"
	.string "Έχει κάτι πολύ φοβερά POKéMON.\n"
	.string "Φαίνεται πολύ καλός, ωστόσο.$"

BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid:
	.string "Το ξέρεις;\n"
	.string "Τον θρύλο του BATTLE PYRAMID;\p"
	.string "Όταν εμφανίζεται ένα γεμάτο με\n"
	.string "αυτοπεποίθηση άτομο TRAINER που \l"
	.string "στοχεύει τη χρυσή κορυφή,\l"
	.string "εμφανίζεται ένας άνδρας ανάμεσα \l"
	.string "στους άνδρες.\p"
	.string "Δεν ξέρεις τον μύθο;\n"
	.string "Ε φυσικά και όχι!\l"
	.string "Τον έβγαλα από το μυαλό μου!\p"
	.string "Τι υποτίθεται ότι σημαίνει;\n"
	.string "Αυτό φίλε μου, ούτε γω το ξέρω!$"

BattleFrontier_OutsideEast_Text_GotWipedOut:
	.string "Φίλε μου! Θεέ μου!\n"
	.string "Δεν έχω χάσει ούτε μία φορά στο παρελθόν!\p"
	.string "Αλλά με έσβησαν χωρίς καμία\n"
	.string "λύτρωση!\p"
	.string "Και μετά μου λένε, ότι δεν έχω καθόλου\n"
	.string "ταλέντο;! Θεέ μου!$"

BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower:
	.string "Αυτός ο τύπος έπεσε πάνω σε ένα\n"
	.string "φρικτά σκληρό άτομο TRAINER κατά τη\l"
	.string "διάρκεια του challenge στο BATTLE TOWER.\p"
	.string "Κοίτα τον τώρα...\p"
	.string "Πρέπει να πηγαίνεις με προσοχή,\n"
	.string "εφόσον αποφασίσεις να πας στο\l"
	.string "BATTLE TOWER.$"

BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll:
	.string "Ναι!\n"
	.string "Επιτέλους πήρα αρκετά Battle Points!\p"
	.string "Μάλλον θα κάνω ανταλλαγή για ένα ακόμη\n"
	.string "τεράστιο λούτρινο DOLL!$"

BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere:
	.string "Ω, ναι, εντάξει!\n"
	.string "Οπότε αυτό είναι το RANKING HALL!\p"
	.string "Θα ήθελα να γράψω ιστορία\n"
	.string "ως άτομο σούπερ πρωταθλητής\l"
	.string "και το όνομά μου να μείνει\l"
	.string "γραμμένο εδώ για πάντα.$"

BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou:
	.string "Με εσένα στο πλάι μου, μπορώ\n"
	.string "να κάνω τα πάντα.$"

BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome:
	.string "Ωωχ, αγάπη μου, είσαι τόσο τέλειος!\p"
	.string "Ωωχ, δεν μπορώ να περιμένω άλλο!\p"
	.string "Πάμε σε ένα MULTI BATTLE ROOM\n"
	.string "τώρα αμέσως!\p"
	.string "Αν είμαστε μαζί στο BATTLE SALON,\n"
	.string "η δύναμη της αγάπης μας θα νικήσει\l"
	.string "όποιον συναντήσουμε.\p"
	.string "Γιατί, μπροστά μας, αγάπη μου, όλα\n"
	.string "θα πέσουν σαν ντόμινο!$"

BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers:
	.string "Το BATTLE FRONTIER δεν είναι\n"
	.string "αποκλειστικά για σκληρά άτομα TRAINERS.\p"
	.string "Πολλά άτομα με ξεχωριστές ικανότητες\n"
	.string "φαίνεται να έχουν προσκληθεί.\p"
	.string "Αυτός ο άνθρωπος, ο SCOTT…\p"
	.string "Μπορεί να έφτιαξε αυτό το μέρος για να\n"
	.string "εξυπηρετήσει έναν μεγαλύτερο σκοπό…$"

BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle:
	.string "Mε συγχωρείς, νεαρέ μου.\n"
	.string "Έχεις καλή όραση;\p"
	.string "Υπάρχει ένα παράξενο δέντρο, \n"
	.string "και στα κουρασμένα μου μάτια\l"
	.string "κουνιέται.$"

BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere:
	.string "Με συγχωρείς, νεαρέ μου.\n"
	.string "Έχεις καλή μνήμη;\p"
	.string "Έχω την αίσθηση ότι υπήρχε\n"
	.string "ένα παράξενο δέντρο εδώ πέρα.$"

BattleFrontier_OutsideEast_Text_StickyMonWithLongTail:
	.string "Το…\n"
	.string "Το είδα!\p"
	.string "Υπήρχε ένα κολλώδες POKéMON\n"
	.string "με μακριά ουρά εκεί μπροστά!\p"
	.string "Κρυβόταν κάτω από έναν βράχο,\n"
	.string "και με κοιτούσε διαρκώς!$"
