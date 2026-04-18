@ VAR_LAST_TALKED would have made all these direct references unnecessary
.set LOCALID_SMART_MC, 4
.set LOCALID_SMART_JUDGE, 5
.set LOCALID_SMART_CONTESTANT_1, 6
.set LOCALID_SMART_CONTESTANT_2, 7
.set LOCALID_SMART_CONTESTANT_3, 8
.set LOCALID_SMART_CONTESTANT_4, 9
.set LOCALID_SMART_AUDIENCE_4, 11
.set LOCALID_SMART_AUDIENCE_2, 12
.set LOCALID_BEAUTY_MC, 13
.set LOCALID_BEAUTY_JUDGE, 14
.set LOCALID_BEAUTY_CONTESTANT_1, 15
.set LOCALID_BEAUTY_CONTESTANT_2, 16
.set LOCALID_BEAUTY_CONTESTANT_3, 17
.set LOCALID_BEAUTY_CONTESTANT_4, 18
.set LOCALID_BEAUTY_AUDIENCE_1, 19
.set LOCALID_BEAUTY_AUDIENCE_3, 20
.set LOCALID_BEAUTY_AUDIENCE_2, 21
.set LOCALID_SMART_AUDIENCE_3, 22
.set LOCALID_CUTE_MC, 23
.set LOCALID_CUTE_JUDGE, 24
.set LOCALID_CUTE_CONTESTANT_1, 25
.set LOCALID_CUTE_CONTESTANT_2, 26
.set LOCALID_CUTE_CONTESTANT_3, 27
.set LOCALID_CUTE_CONTESTANT_4, 28
.set LOCALID_CUTE_AUDIENCE_1, 29
.set LOCALID_CUTE_AUDIENCE_3, 30
.set LOCALID_CUTE_AUDIENCE_2, 31

LilycoveCity_ContestHall_MapScripts::
	.byte 0

LilycoveCity_ContestHall_EventScript_Boy1::
	msgbox LilycoveCity_ContestHall_Text_TodayWonSmartnessContest, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Boy2::
	msgbox LilycoveCity_ContestHall_Text_EnteredBunchOfContests, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Girl::
	msgbox LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Sailor::
	msgbox LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_SmartContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EnteredWrongContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_RaisedMonToBeSmart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience1::
	msgbox LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_StillLoveSmartnessContests, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_OverdidGrooming, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_InTheMiddleOfContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyAzurillWasDistracted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_NeverWonBattleButContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PetalDanceIsMarvel, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience1::
	lockall
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_ContestHall_Text_MyChildIsInContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	delay 25
	msgbox LilycoveCity_ContestHall_Text_ComeOnDear, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyStageSign::
	msgbox LilycoveCity_ContestHall_Text_BeautyContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_CuteStageSign::
	msgbox LilycoveCity_ContestHall_Text_CuteContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartStageSign::
	msgbox LilycoveCity_ContestHall_Text_SmartContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_Text_TodayWonSmartnessContest:
	.string "Αυτό το POKéMON κέρδισε το\n"
	.string "BEAUTY CONTEST εδώ παλαιότερα.\p"
	.string "Λοιπόν, μάντεψε. Σήμερα, το έκανα\n"
	.string "να κερδίσει ένα SMARTNESS CONTEST!\p"
	.string "Οι ικανότητές μου τρομάζουν κι εμένα…$"

LilycoveCity_ContestHall_Text_EnteredBunchOfContests:
	.string "Έχω συμμετάσχει σε ένα σωρό CONTESTS,\n"
	.string "οπότε βλέπω πώς λειτουργούν τα\l"
	.string "πράγματα.\p"
	.string "Αν βρίσκεσαι σε COOLNESS CONTEST,\n"
	.string "οι κουλ κινήσεις ανεβάζουν το appeal.\p"
	.string "Αλλά οι έξυπνες και οι χαριτωμένες \n"
	.string "κινήσεις δεν τα πάνε καλά, για \l"
	.string "παράδειγμα.$"

LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks:
	.string "Εκείνος ο νεαρός που κέρδισε \n"
	.string "πριν είχε ένα σωρό διαφορετικά\l"
	.string "{POKEBLOCK}S.\p"
	.string "Μπορείς να κερδίσεις αν έχεις τόσα \n"
	.string "πολλά από αυτά τα πράγματα;$"

LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous:
	.string "Ουάου, δεν είναι τεράστιο \n"
	.string "αυτό το μέρος;\p"
	.string "Η ένταση στον αέρα… Δεν \n"
	.string "είναι σαν την αίθουσα CONTEST \l"
	.string "στην ύπαιθρο.$"

LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal:
	.string "MC: Εντάξει, SMART POKéMON και\n"
	.string "οι TRAINERS τους, είστε έτοιμοι;\p"
	.string "Δώστε την καλύτερή σας εμφάνιση!\n"
	.string "Ας κάνουμε appeal!$"

LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest:
	.string "JUDGE: Απολαμβάνεις αυτό το CONTEST;\p"
	.string "Έλα πίσω με τρεις φίλους σου, και\n"
	.string "όλοι σας μπορείτε να μπείτε\l"
	.string "σε ένα CONTEST!$"

LilycoveCity_ContestHall_Text_EnteredWrongContest:
	.string "Αγιαγιαγια…\n"
	.string "Μπήκα σε λάθος CONTEST.\p"
	.string "Έβαλα αυτό το σκληρό POKéMON \n"
	.string "στο SMARTNESS CONTEST…\p"
	.string "Έλα, εντυπωσίασέ τους με ένα \n"
	.string "έξυπνο ROCK SMASH.$"

LilycoveCity_ContestHall_Text_RaisedMonToBeSmart:
	.string "Έχω αφιερώσει πολλά χρόνια, \n"
	.string "και όλη μου τη σοφία \l"
	.string "μεγαλώνοντας αυτό το POKéMON\l"
	.string "για να είναι έξυπνο.\p"
	.string "Δεν θα νικηθεί εύκολα από το\n"
	.string "POKéMON κάποιου νεαρού κουταβιού.\p"
	.string "Αγαπημένη μου γυναίκα, το βλέπεις \n"
	.string "αυτό;$"

LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext:
	.string "Εκεί είναι!\p"
	.string "Αν το POKéMON μου κάνει μια έξυπνη\n"
	.string "κίνηση τώρα, ο ενθουσιασμός \l"
	.string "του κοινού θα φτάσει στο αποκορύφωμα!$"

LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife:
	.string "Ω, Θεέ μου, όχι!\p"
	.string "Το LEECH LIFE του αγαπημένου μου ZUBAT\n"
	.string "είναι τόσο χαριτωμένο που συνέχισα\l"
	.string "να το χρησιμοποιώ ξανά και ξανά!\p"
	.string "Αλλά αυτοί οι κακοί άνθρωποι δεν το\n"
	.string "εκτιμούν καθόλου!$"

LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa:
	.string "Κιγιαααχ! Είσαι υπέροχος, παππού!$"

LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves:
	.string "Ακόμα κι όταν οι TRAINERS μπαίνουν\n"
	.string "με το ίδιο είδος POKéMON, \l"
	.string "όλοι τους φαίνεται να \l"
	.string "χρησιμοποιούν διαφορετικές κινήσεις\l"
	.string "για appeals.\p"
	.string "Είναι ακριβώς όπως οι άνθρωποι \n"
	.string "έχουν διαφορετικά στυλ στη μάχη.$"

LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers:
	.string "Νομίζω ότι τα POKéMON φαίνονται\n"
	.string "πιο έξυπνα από τους TRAINERS τους. \l"
	.string "Και μάλιστα κατά πολύ.$"

LilycoveCity_ContestHall_Text_StillLoveSmartnessContests:
	.string "Όταν όλα τελειώσουν, εξακολουθώ να\n"
	.string "αγαπώ τα SMARTNESS CONTESTS.\p"
	.string "Αυτό το διανοητικό πράσινο χρώμα…\n"
	.string "Είναι τόσο… Τόσο… Κουλ.$"

LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest:
	.string "MC: Μπαίνεις κι εσύ στο BEAUTY\n"
	.string "CONTEST; Καλή επιτυχία!$"

LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty:
	.string "JUDGE: Αχ, κάθε POKéMON εδώ\n"
	.string "είναι ένα μοντέλο αγνής ομορφιάς!\p"
	.string "Παραλίγο να ξεχάσω να τα\n"
	.string "βαθμολογήσω!$"

LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty:
	.string "Ένα POKéMON τόσο όμορφο…\n"
	.string "Δεν υπάρχει άλλο σαν κι αυτό.\p"
	.string "Τα μάτια όλων θα είναι καρφωμένα\n"
	.string "στην ομορφιά μου.$"

LilycoveCity_ContestHall_Text_OverdidGrooming:
	.string "Ουάαααχ!\p"
	.string "Βούρτσισα και περιποιήθηκα το\n"
	.string "POKéMON μου προσεκτικά \l"
	.string "για αυτό το CONTEST…\p"
	.string "Αλλά το παράκανα…\n"
	.string "Το τρίχωμά του έγινε τελείως ατημέλητο…\p"
	.string "Τι πρέπει να κάνω;$"

LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam:
	.string "Αυτό το AURORA BEAM είναι \n"
	.string "τόσο εκθαμβωτικό, που ο JUDGE \l"
	.string "δεν θα μπορέσει να το παρατηρήσει.\p"
	.string "Α, περίμενε ένα λεπτό…\n"
	.string "Αυτό δεν θα έχει νόημα, τότε!$"

LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe:
	.string "Αυτό το όμορφο POKéMON μου μοιάζει \n"
	.string "ακριβώς όπως ήμουν όταν ήμουν \l"
	.string "νεότερη.\p"
	.string "Ακριβώς όταν το είπα αυτό,\n"
	.string "ο άντρας μου έφτυσε \l"
	.string "τον καφέ που έπινε.\p"
	.string "Είπα κάτι αστείο;$"

LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy:
	.string "Ξέρεις, αν κερδίσω σε ένα BEAUTY\n"
	.string "CONTEST, σίγουρα με κάνει \l"
	.string "χαρούμενο. Περισσότερο από\l"
	.string "ό,τι συνήθως, τουλάχιστον.$"

LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon:
	.string "Ουαχαχαχαχ!\p"
	.string "Θα ρίξεις μια ματιά σε όλα αυτά \n"
	.string "τα όμορφα POKéMON;\p"
	.string "Απλά λατρεύω αυτού του\n"
	.string "είδους τη λάμψη!$"

LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone:
	.string "Δεν μπορείς πάντα να κερδίζεις μόνο με\n"
	.string "την ομορφιά.\p"
	.string "Πρέπει να περιποιείσαι το POKéMON σου,\n"
	.string "ώστε να είναι ωραίο \l"
	.string "και γυαλιστερό σαν το δικό μου.$"

LilycoveCity_ContestHall_Text_InTheMiddleOfContest:
	.string "MC: Ωχ! Γεια σας!\n"
	.string "Είμαστε στη μέση ενός CONTEST!\p"
	.string "Παρακαλώ περάστε από το\n"
	.string "γκισέ εγγραφής μας \l"
	.string "πρώτα, εντάξει;$"

LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals:
	.string "JUDGE: Ω, τι γοητευτικά και\n"
	.string "χαριτωμένα appeals!\p"
	.string "Θεούλη μου! Τι απόλυτα χαριτωμένο\n"
	.string "WATER SPORT appeal!$"

LilycoveCity_ContestHall_Text_MyAzurillWasDistracted:
	.string "Ω, όχι… Το γλυκό μου AZURILL\n"
	.string "αποσπάστηκε από ένα άλλο POKéMON.$"

LilycoveCity_ContestHall_Text_NeverWonBattleButContest:
	.string "Το POKéMON μου δεν έχει κερδίσει ποτέ \n"
	.string "σε μάχη, αλλά βάλτο σε ένα \l"
	.string "CONTEST και κοίτα το!$"

LilycoveCity_ContestHall_Text_PetalDanceIsMarvel:
	.string "Το PETAL DANCE του POKéMON μου είναι\n"
	.string "ένα θαύμα κομψότητας.\p"
	.string "Δεν θα αφήσω κανέναν να ενοχλήσει\n"
	.string "την παράστασή του.$"

LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter:
	.string "Τα POKéMON όλων είναι πολύ χαριτωμένα.\p"
	.string "Ωστόσο, αν το POKéMON μου έκανε ένα \n"
	.string "αυτό appeal…\p"
	.string "Είμαι σίγουρη ότι θα ήταν\n"
	.string "πολύ πιο χαριτωμένο\l"
	.string "από τα άλλα.$"

LilycoveCity_ContestHall_Text_MyChildIsInContest:
	.string "Το παιδί μου είναι σε αυτό\n"
	.string "το CONTEST.$"

LilycoveCity_ContestHall_Text_ComeOnDear:
	.string "Έλα, αγάπη μου. Βάλε τα δυνατά σου!\n"
	.string "Το POKéMON σου είναι το καλύτερο!$"

LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest:
	.string "Νομίζω ότι αυτό το κορίτσι εκεί\n"
	.string "είναι το πιο χαριτωμένο απ' όλα.\p"
	.string "Μα τι; Αυτοί κρίνουν\n"
	.string "τα POKéMON από την εμφάνισή τους;$"

LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn:
	.string "Ωωχ, βλέποντας όλα αυτά τα\n"
	.string "χαριτωμένα POKéMON, με κάνουν \l"
	.string "να θέλω να αποκτήσω τα δικά μου!\p"
	.string "Θα πάω να πιάσω μερικά!$"

LilycoveCity_ContestHall_Text_BeautyContestStage:
	.string "BEAUTY CONTEST STAGE\n"
	.string "ΓΟΗΤΕΥΤΕΙΤΕ ΑΠΟ\l"
	.string "ΟΜΟΡΦΑ POKéMON!$"

LilycoveCity_ContestHall_Text_CuteContestStage:
	.string "CUTENESS CONTEST STAGE\n"
	.string "ΜΑΓΕΥΤΕΙΤΕ ΑΠΟ\l"
	.string "ΧΑΡΙΤΩΜΕΝΑ POKéMON!$"

LilycoveCity_ContestHall_Text_SmartContestStage:
	.string "SMARTNESS CONTEST STAGE\n"
	.string "ΕΝΤΥΠΩΣΙΑΣΤΕΙΤΕ ΑΠΟ\l"
	.string "ΕΞΥΠΝΑ POKéMON!$"

