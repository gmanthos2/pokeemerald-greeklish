BattleFrontier_Lounge2_MapScripts::
	.byte 0

@ This NPC gives hints about a random facility or battle mode.
@ For battle modes he gives generic advice
@ For facilities, depending on how far the player has progressed he will say either
@    The name of the Frontier Brain there
@    The type and description of the 3 pokemon they use in their silver battle
@    The type and description of the 3 pokemon they use in their gold battle
BattleFrontier_Lounge2_EventScript_FrontierManiac::
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_MANIAC, BattleFrontier_Lounge2_EventScript_AlreadyMetManiac
	setflag FLAG_MET_BATTLE_FRONTIER_MANIAC
	msgbox BattleFrontier_Lounge2_Text_FrontierManiacIntro, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_AlreadyMetManiac::
	msgbox BattleFrontier_Lounge2_Text_SwingByForTheLatestWord, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_GiveAdvice::
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_SINGLES, BattleFrontier_Lounge2_EventScript_BufferSingle
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_DOUBLES, BattleFrontier_Lounge2_EventScript_BufferDouble
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_MULTIS, BattleFrontier_Lounge2_EventScript_BufferMulti
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BufferMultiLink
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_BufferBattleDome
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_FACTORY, BattleFrontier_Lounge2_EventScript_BufferBattleFactory
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PALACE, BattleFrontier_Lounge2_EventScript_BufferBattlePalace
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_ARENA, BattleFrontier_Lounge2_EventScript_BufferBattleArena
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PIKE, BattleFrontier_Lounge2_EventScript_BufferBattlePike
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PYRAMID, BattleFrontier_Lounge2_EventScript_BufferBattlePyramid
@ <= FRONTIER_MANIAC_TOWER_LINK is any Battle Tower mode
	call_if_le VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BattleTowerNews
@ >= FRONTIER_MANIAC_DOME is any facility other than Battle Tower
	call_if_ge VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_FacilityNews
	special ShowFrontierManiacMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge2_EventScript_BattleTowerNews::
	msgbox BattleFrontier_Lounge2_Text_BattleTowerIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_FacilityNews::
	msgbox BattleFrontier_Lounge2_Text_FacilityIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_BufferSingle::
	bufferstdstring STR_VAR_1, STDSTRING_SINGLE
	return

BattleFrontier_Lounge2_EventScript_BufferDouble::
	bufferstdstring STR_VAR_1, STDSTRING_DOUBLE
	return

BattleFrontier_Lounge2_EventScript_BufferMulti::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI
	return

BattleFrontier_Lounge2_EventScript_BufferMultiLink::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI_LINK
	return

BattleFrontier_Lounge2_EventScript_BufferBattleDome::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_DOME
	return

BattleFrontier_Lounge2_EventScript_BufferBattleFactory::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_FACTORY
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePalace::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PALACE
	return

BattleFrontier_Lounge2_EventScript_BufferBattleArena::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_ARENA
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePike::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PIKE
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePyramid::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PYRAMID
	return

BattleFrontier_Lounge2_EventScript_Maniac1::
	lock
	msgbox BattleFrontier_Lounge2_Text_NewsGatheringPower, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowersOfObservation, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac3::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_TriathleteF::
	msgbox BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe, MSGBOX_NPC
	end

BattleFrontier_Lounge2_Text_FrontierManiacIntro::
	.string "Γεια! Όσον αφορά τα νέα για \n"
	.string "το BATTLE FRONTIER, είμαι ο Νο. 1.\p"
	.string "Μπορείς να με θεωρείς τον\n"
	.string "FRONTIER MANIAC.\p"
	.string "Απλώς ελέγχω, αλλά είσαι TRAINER,\n"
	.string "δεν είναι αλήθεια;\p"
	.string "Με χαρά θα μοιραστώ τα πιο καυτά νέα\n"
	.string "που μάζεψα για το BATTLE FRONTIER.$"

BattleFrontier_Lounge2_Text_SwingByForTheLatestWord::
	.string "Γεια σου! Πέρασες για να με ρωτήσεις \n"
	.string "για τα τελευταία νέα; Ω, εντάξει!$"

@ Unused
BattleFrontier_Lounge2_Text_MyInformationsBeenUsefulRight::
	.string "Λοιπόν; Λοιπόν; Λοιπόν;\p"
	.string "Είμαι σίγουρος ότι οι πληροφορίες \n"
	.string "μου σου φάνηκαν πολύ χρήσιμες, σωστά;$"

BattleFrontier_Lounge2_Text_FacilityIsHottest::
	.string "Ας δούμε τώρα…\p"
	.string "Ακούγεται σαν το {STR_VAR_1}\n"
	.string "είναι το πιο καυτό μέρος τώρα.$"

BattleFrontier_Lounge2_Text_BattleTowerIsHottest::
	.string "Ας δούμε τώρα…\p"
	.string "Ακούγεται σαν το BATTLE TOWER\n"
	.string "{STR_VAR_1} να είναι το πιο hot.$"

BattleFrontier_Lounge2_Text_SalonMaidenIsThere::
	.string "Πάω στοίχημα ότι δεν το ήξερες αυτό!\p"
	.string "Ένας από τους κορυφαίους TRAINERS που\n"
	.string "ο SCOTT αποκαλεί FRONTIER BRAINS \l"
	.string "είναι εκεί.\p"
	.string "Είναι αυτή η μυστηριώδης TRAINER\n"
	.string "η SALON MAIDEN που διευθύνει το μέρος.$"

BattleFrontier_Lounge2_Text_SalonMaidenSilverMons::
	.string "Έχεις πολεμήσει με την SALON MAIDEN;\p"
	.string "Όταν μετράει τον αντίπαλό της,\n"
	.string "προφανώς χρησιμοποιεί αυτά τα POKéMON:\p"
	.string "Ένα PSI POKéMON τύπου PSYCHIC,\n"
	.string "ένα VOLCANO POKéMON τύπου FIRE,\l"
	.string "και ένα SLEEPING POKéMON τύπου NORMAL.$"

BattleFrontier_Lounge2_Text_SalonMaidenGoldMons::
	.string "Έχεις πολεμήσει με την SALON MAIDEN\n"
	.string "όταν είναι σοβαρή;\p"
	.string "Όταν μάχεται σκληρά, χρησιμοποιεί\n"
	.string "αυτά τα POKéMON:\p"
	.string "Ένα EON POKéMON (DRAGON & PSYCHIC),\n"
	.string "ένα THUNDER POKéMON τύπου ELECTRIC,\l"
	.string "και ένα SLEEPING POKéMON τύπου NORMAL.$"

BattleFrontier_Lounge2_Text_DomeAceIsThere::
	.string "Πάω στοίχημα ότι δεν το ήξερες αυτό!\p"
	.string "Ο SCOTT αποκαλεί αυτούς τους top \n"
	.string "TRAINERS, FRONTIER BRAINS.\p"
	.string "Είναι ένας επιδεικτικός TRAINER \n"
	.string "ο DOME ACE που διευθύνει το μέρος.$"

BattleFrontier_Lounge2_Text_DomeAceSilverMons::
	.string "Έχεις πολεμήσει με τον DOME ACE;\p"
	.string "Όταν αντιμετωπίζει τον αντίπαλο\n"
	.string "ελαφρά, έχει αυτά τα τρία POKéMON:\p"
	.string "Ένα DRAGON POKéMON (DRAGON & FLYING)\n"
	.string "ένα MUD FISH POKéMON (WATER & GROUND),\l"
	.string "και ένα FLAME POKéMON (FIRE & FLYING).$"

BattleFrontier_Lounge2_Text_DomeAceGoldMons::
	.string "Έχεις πολεμήσει με τον DOME ACE\n"
	.string "όταν είναι σοβαρός;\p"
	.string "Οταν επιδεικνύει την στρατηγική του,\n"
	.string "τον βλέπεις με αυτά τα τρία POKéMON:\p"
	.string "Ένα EON POKéMON (DRAGON & FLYING)\n"
	.string "ένα MUD FISH POKéMON (WATER & GROUND),\l"
	.string "κι ένα IRON LEG POKéMON (STEEL &\l"
	.string "PSYCHIC).$"

BattleFrontier_Lounge2_Text_FactoryHeadIsThere::
	.string "Πάω στοίχημα ότι δεν το ήξερες αυτό!\p"
	.string "Ο SCOTT αποκαλεί αυτούς τους top \n"
	.string "TRAINERS, FRONTIER BRAINS.\p"
	.string "Είναι ένας φρικτός TRAINER με το\n"
	.string "όνομα FACTORY HEAD που τρέχει το μέρος.$"

BattleFrontier_Lounge2_Text_FactoryHeadSilverMons::
	.string "Έχεις πολεμήσει με τον FACTORY HEAD\n"
	.string "ήδη;\p"
	.string "Κάτσε… Όταν πάει πολεμήσει, παίρνει\n"
	.string "απλώς τρία ενοικιαζόμενα POKéMON.\p"
	.string "Αγωνίζεται σχεδόν με τις ίδιες \n"
	.string "συνθήκες με σένα.$"

BattleFrontier_Lounge2_Text_FactoryHeadGoldMons::
	.string "Έχεις πολεμήσει με τον FACTORY HEAD\n"
	.string "όταν είναι σοβαρός;\p"
	.string "Όταν πάει σοβαρά στη μάχη,\n"
	.string "παιρνει πάλι 3 ενοικιαζόμενα POKéMON.\p"
	.string "Μάχεται πρακτικά κάτω από τις ίδιες\n"
	.string "συνθήκες με εσένα.$"

BattleFrontier_Lounge2_Text_PikeQueenIsThere::
	.string "Πάω στοίχημα ότι δεν το ήξερες αυτό!\p"
	.string "Ο SCOTT αποκαλεί αυτούς τους top \n"
	.string "TRAINERS, FRONTIER BRAINS.\p"
	.string "Είναι μια τρομακτική TRAINER, \n"
	.string "η PIKE QUEEN που διευθύνει το μέρος.$"

BattleFrontier_Lounge2_Text_PikeQueenSilverMons::
	.string "Έχεις πολεμήσει την PIKE QUEEN\n"
	.string "πριν;\p"
	.string "Όταν είναι σε καλή διάθεση, λένε\n"
	.string "ότι χρησιμοποιεί αυτά τα 3 POKéMON:\p"
	.string "Ένα FANG SNAKE POKéMON τύπου POISON,\n"
	.string "ένα MOLD POKéMON (BUG & ROCK),\l"
	.string "και ένα TENDER POKéMON τύπου WATER.$"

BattleFrontier_Lounge2_Text_PikeQueenGoldMons::
	.string "Έχεις πολεμήσει με την PIKE QUEEN\n"
	.string "όταν είναι σοβαρή;\p"
	.string "Σοβαρά ενοχλημένη, λένε χρησιμοποιεί\n"
	.string "αυτά τα τρία POKéMON:\p"
	.string "Ένα FANG SNAKE POKéMON τύπου POISON,\n"
	.string "ένα IRON SNAKE POKéMON (STEEL & GROUND)\l"
	.string "κι ένα ATROCIOUS POKéMON τύπου WATER &\l"
	.string "FLYING.$"

BattleFrontier_Lounge2_Text_ArenaTycoonIsThere::
	.string "Πάω στοίχημα ότι δεν το ήξερες αυτό!\p"
	.string "Ο SCOTT αποκαλεί αυτούς τους top \n"
	.string "TRAINERS, FRONTIER BRAINS.\p"
	.string "Είναι μια χαριτωμένη TRAINER,\n"
	.string "η ARENA TYCOON που διευθύνει το μέρος.$"

BattleFrontier_Lounge2_Text_ArenaTycoonSilverMons::
	.string "Έχεις πολεμήσει την ARENA TYCOON\n"
	.string "πριν;\p"
	.string "Όταν αξιολογεί την ικανότητα του\n"
	.string "εχθρού, φαίνεται να έχει αυτά τα:\p"
	.string "SINGLE HORN POKéMON (BUG & FIGHTING),\n"
	.string "MOONLIGHT POKéMON τύπου DARK,\l"
	.string "και SHED POKéMON (BUG & GHOST).$"

BattleFrontier_Lounge2_Text_ArenaTycoonGoldMons::
	.string "Έχεις πολεμήσει με την ARENA TYCOON\n"
	.string "όταν είναι σοβαρή;\p"
	.string "Όταν μάχεται για τα καλά,\n"
	.string "υποτίθεται ότι χρησιμοποιεί αυτά:\p"
	.string "Ένα MOONLIGHT POKéMON τύπου DARK,\n"
	.string "SHADOW POKéMON (GHOST & POISON)\l"
	.string "και MUSHROOM POKéMON (GRASS &\l"
	.string "FIGHTING).$"

BattleFrontier_Lounge2_Text_PalaceMavenIsThere::
	.string "Πάω στοίχημα ότι δεν το ήξερες αυτό!\p"
	.string "Ο SCOTT αποκαλεί αυτούς τους top \n"
	.string "TRAINERS, FRONTIER BRAINS.\p"
	.string "Είναι ένας απαίσιος TRAINER,\n"
	.string "ο PALACE MAVEN που διευθύνει το μέρος.$"

BattleFrontier_Lounge2_Text_PalaceMavenSilverMons::
	.string "Έχεις πολεμήσει με τον PALACE MAVEN\n"
	.string "πριν;\p"
	.string "Όταν δοκιμάζει το πνεύμα του αντιπάλου\n"
	.string "του, λέγεται ότι έχει αυτά τα POKéMON:\p"
	.string "Ένα BAT POKéMON τύπου POISON & FLYING,\n"
	.string "ένα LAZY POKéMON τύπου NORMAL, και ένα\l"
	.string "TRANSPORT POKéMON τύπου WATER & ICE.$"

BattleFrontier_Lounge2_Text_PalaceMavenGoldMons::
	.string "Έχεις πολεμήσει με τον PALACE MAVEN\n"
	.string "όταν είναι σοβαρός;\p"
	.string "Όταν ρίχνει όλη του τη δύναμη στη\n"
	.string "μάχη, λέγεται ότι έχει αυτά τα POKéMON:\p"
	.string "Ένα LEGENDARY POKéMON τύπου FIRE,\n"
	.string "ένα LAZY POKéMON τύπου NORMAL,\l"
	.string "και ένα AURORA POKéMON τύπου WATER.$"

BattleFrontier_Lounge2_Text_PyramidKingIsThere::
	.string "Πάω στοίχημα ότι δεν το ήξερες αυτό!\p"
	.string "Ο SCOTT αποκαλεί αυτούς τους top \n"
	.string "TRAINERS, FRONTIER BRAINS.\p"
	.string "Είναι ένας φλογερός TRAINER,\n"
	.string "ο PYRAMID KING που διευθύνει το μέρος.$"

BattleFrontier_Lounge2_Text_PyramidKingSilverMons::
	.string "Έχεις πολεμήσει με τον PYRAMID KING\n"
	.string "πριν;\p"
	.string "Όταν ελέγχει τη δύναμη του εχθρού,\n"
	.string "προφανώς χρησιμοποιεί αυτά τα POKéMON:\p"
	.string "Ένα ROCK PEAK POKéMON τύπου ROCK,\n"
	.string "ένα ICEBERG POKéMON τύπου ICE,\l"
	.string "και ένα IRON POKéMON τύπου STEEL.$"

BattleFrontier_Lounge2_Text_PyramidKingGoldMons::
	.string "Έχεις πολεμήσει με τον PYRAMID KING\n"
	.string "όταν είναι σοβαρός;\p"
	.string "Όταν φουσκώνει με καυτή δύναμη,\n"
	.string "προφανώς χρησιμοποιεί αυτά τα POKéMON:\p"
	.string "Ένα FREEZE POKéMON (ICE & FLYING),\n"
	.string "ELECTRIC POKéMON (ELECTRIC & FLYING),\l"
	.string "και ένα FLAME POKéMON (FIRE &\l"
	.string "FLYING).$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice1::
	.string "Σίγουρα, υπάρχουν πολλά μέρη όπου\n"
	.string "μπορείς να μπεις σε DOUBLE BATTLES.\p"
	.string "Αλλά τα DOUBLE BATTLE ROOMS του\n"
	.string "BATTLE TOWER είναι, σαν, βασικά!\p"
	.string "Είναι εκεί που πρέπει να μάθεις\n"
	.string "πώς παίζονται τα DOUBLE BATTLES \l"
	.string "στο BATTLE FRONTIER.$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice2::
	.string "Πρόσεχε τον εαυτό σου στις μάχες εδώ.\p"
	.string "Ακούω ότι υπάρχουν TRAINERS που έχουν\n"
	.string "στρατηγικές που έχουν αναπτύξει μόνο\l"
	.string "για τις DOUBLE BATTLES.$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice3::
	.string "Μόλις νιώσεις σίγουρος και άνετος\n"
	.string "με τα DOUBLE BATTLES εδώ, θα πρέπει\l"
	.string "να σκεφτείς να προκαλέσεις άλλα μέρη\l"
	.string "που προσφέρουν DOUBLE BATTLES.$"

BattleFrontier_Lounge2_Text_MultiBattleAdvice::
	.string "Όλα τα είδη TRAINERS συγκεντρώνονται\n"
	.string "στο BATTLE SALON.\p"
	.string "Απλώς σκέψου--μπορεί να συναντήσεις\n"
	.string "τους φίλους ή τους ακολούθους σου!\l"
	.string "Πρέπει να κοιτάξεις προσεκτικά!$"

BattleFrontier_Lounge2_Text_LinkMultiBattleAdvice::
	.string "Αν είσαι με φίλο, πήγαινε στο\n"
	.string "LINK MULTI BATTLE ROOM.\p"
	.string "Δεδομένου ότι παίζεις με έναν ισχυρό\n"
	.string "φίλο, περίμενε να δεις και σκληρούς\l"
	.string "εχθρούς!$"

BattleFrontier_Lounge2_Text_NewsGatheringPower::
	.string "Τι εκπληκτική ισχύς συγκέντρωσης νέων!\n"
	.string "Ο μέντορας μου είναι μοναδικός!$"

BattleFrontier_Lounge2_Text_AmazingPowersOfObservation::
	.string "Τι καταπληκτικές δυνάμεις παρατήρησης!\n"
	.string "Ο μέντορας μου είναι μοναδικός!$"

BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion::
	.string "Τι εκπληκτική δύναμη πειθούς!\n"
	.string "Ο μέντορας μου είναι μοναδικός!$"

BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe::
	.string "…Τι είναι αυτό το μέρος;\n"
	.string "Με τρομάζει…$"

