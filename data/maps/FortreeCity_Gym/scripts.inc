FortreeCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, FortreeCity_Gym_OnWarp
	.byte 0

FortreeCity_Gym_OnTransition:
	special RotatingGate_InitPuzzle
	end

FortreeCity_Gym_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, FortreeCity_Gym_EventScript_InitRotatingGates
	.2byte 0

@ NOTE: This rotating gate puzzle makes use of VAR_TEMP_0 - VAR_TEMP_3
FortreeCity_Gym_EventScript_InitRotatingGates::
	special RotatingGate_InitPuzzleAndGraphics
	end

FortreeCity_Gym_EventScript_Winona::
	trainerbattle_single TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaIntro, FortreeCity_Gym_Text_WinonaDefeat, FortreeCity_Gym_EventScript_WinonaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_Gym_EventScript_WinonaRematch
	goto_if_unset FLAG_RECEIVED_TM_AERIAL_ACE, FortreeCity_Gym_EventScript_GiveAerialAce2
	msgbox FortreeCity_Gym_Text_WinonaPostBattle, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_WinonaDefeated::
	message FortreeCity_Gym_Text_ReceivedFeatherBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_FORTREE_GYM
	setflag FLAG_BADGE06_GET
	setvar VAR_0x8008, 6
	call Common_EventScript_SetGymTrainers
	call FortreeCity_Gym_EventScript_GiveAerialAce
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox FortreeCity_Gym_Text_RegisteredWinona, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WINONA_MATCH_CALL
	setvar VAR_SCOTT_FORTREE_CALL_STEP_COUNTER, 0
	setflag FLAG_SCOTT_CALL_FORTREE_GYM
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce2::
	giveitem ITEM_TM_AERIAL_ACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce::
	giveitem ITEM_TM_AERIAL_ACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	return

FortreeCity_Gym_EventScript_WinonaRematch::
	trainerbattle_rematch_double TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaPreRematch, FortreeCity_Gym_Text_WinonaRematchDefeat, FortreeCity_Gym_Text_WinonaRematchNeedTwoMons
	msgbox FortreeCity_Gym_Text_WinonaPostRematch, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Jared::
	trainerbattle_single TRAINER_JARED, FortreeCity_Gym_Text_JaredIntro, FortreeCity_Gym_Text_JaredDefeat
	msgbox FortreeCity_Gym_Text_JaredPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Edwardo::
	trainerbattle_single TRAINER_EDWARDO, FortreeCity_Gym_Text_EdwardoIntro, FortreeCity_Gym_Text_EdwardoDefeat
	msgbox FortreeCity_Gym_Text_EdwardoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Flint::
	trainerbattle_single TRAINER_FLINT, FortreeCity_Gym_Text_FlintIntro, FortreeCity_Gym_Text_FlintDefeat
	msgbox FortreeCity_Gym_Text_FlintPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Ashley::
	trainerbattle_single TRAINER_ASHLEY, FortreeCity_Gym_Text_AshleyIntro, FortreeCity_Gym_Text_AshleyDefeat
	msgbox FortreeCity_Gym_Text_AshleyPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Humberto::
	trainerbattle_single TRAINER_HUMBERTO, FortreeCity_Gym_Text_HumbertoIntro, FortreeCity_Gym_Text_HumbertoDefeat
	msgbox FortreeCity_Gym_Text_HumbertoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Darius::
	trainerbattle_single TRAINER_DARIUS, FortreeCity_Gym_Text_DariusIntro, FortreeCity_Gym_Text_DariusDefeat
	msgbox FortreeCity_Gym_Text_DariusPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_FORTREE_GYM, FortreeCity_Gym_EventScript_GymGuidePostVictory
	msgbox FortreeCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_GymGuidePostVictory::
	msgbox FortreeCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_GymStatueCertified::
	msgbox FortreeCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_EventScript_GymStatue::
	msgbox FortreeCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_Text_GymGuideAdvice:
	.string "Γεια, πώς πάει, μελλοντικέ CHAMPION\n"
	.string "{PLAYER};\p"
	.string "Η FORTREE GYM LEADER WINONA είναι\n"
	.string "εξπέρ στα POKéMON τύπου FLYING.\p"
	.string "Περιμένει στο πίσω μέρος αυτού του GYM,\n"
	.string "πίσω από τις περιστρεφόμενες πόρτες.\p"
	.string "Περιμένει νέους διεκδικητές\n"
	.string "που προσπαθούν να πετάξουν ψηλά!\p"
	.string "Εντάξει, προχώρα!$"

FortreeCity_Gym_Text_GymGuidePostVictory:
	.string "Τα κατάφερες!\n"
	.string "Έκανες την απογείωση!$"

FortreeCity_Gym_Text_JaredIntro:
	.string "Δες το κομψό στυλ μάχης των\n"
	.string "BIRD POKéMON!$"

FortreeCity_Gym_Text_JaredDefeat:
	.string "Εσύ…\n"
	.string "Εχεις δύναμη μέσα σου…$"

FortreeCity_Gym_Text_JaredPostBattle:
	.string "Ένας TRAINER πρέπει να είναι έξυπνος \n"
	.string "για να συμβαδίζει με απρόσμενες τροπές.\p"
	.string "Έχεις το μυαλό για να φτάσεις\n"
	.string "την LEADER μας;$"

FortreeCity_Gym_Text_EdwardoIntro:
	.string "Οι λάτρεις των BIRD POKéMON \n"
	.string "φιλοδοξούν να μπουν σε αυτό το GYM.\p"
	.string "Ως μέλος του FORTREE GYM,\n"
	.string "δεν επιτρέπεται να χάσω!$"

FortreeCity_Gym_Text_EdwardoDefeat:
	.string "Ήταν πολύ βαρύ το φορτίο για μένα\n"
	.string "για να το αντέξω…$"

FortreeCity_Gym_Text_EdwardoPostBattle:
	.string "Ο κόσμος είναι τεράστιος, και υπάρχουν\n"
	.string "αμέτρητοι σκληροί TRAINERS.\p"
	.string "Θα συνεχίσω να προπονούμαι και \n"
	.string "θα γίνω ακόμα πιο δυνατός.$"

FortreeCity_Gym_Text_FlintIntro:
	.string "Δεν υπάρχει ανάγκη η WINONA, η GYM\n"
	.string "LEADER μας, να ασχοληθεί μαζί σου!\p"
	.string "Εγώ είμαι παραπάνω από αρκετός \n"
	.string "για εσένα!$"

FortreeCity_Gym_Text_FlintDefeat:
	.string "WINONA, εγώ…\n"
	.string "Έχασα!$"

FortreeCity_Gym_Text_FlintPostBattle:
	.string "Η WINONA είναι χαριτωμένη και δυνατή.\n"
	.string "Είναι η απόλυτη LEADER!\p"
	.string "Κοκκίνισμα…$"

FortreeCity_Gym_Text_AshleyIntro:
	.string "Η WINONA με δίδαξε προσωπικά!\n"
	.string "Δεν μπορείς να με νικήσεις εύκολα!$"

FortreeCity_Gym_Text_AshleyDefeat:
	.string "Νικήθηκα…$"

FortreeCity_Gym_Text_AshleyPostBattle:
	.string "Χάρη στη WINONA, οι άνθρωποι του\n"
	.string "FORTREE μπορούν να ζουν χωρίς φόβο.$"

FortreeCity_Gym_Text_HumbertoIntro:
	.string "Όταν η WINONA ρίχνεται στη μάχη, \n"
	.string "το πρόσωπό της λάμπει \l"
	.string "με όμορφη αποφασιστικότητα…\p"
	.string "Δεν θα σε αφήσω να δεις αυτό το\n"
	.string "υπέροχο θέαμα!$"

FortreeCity_Gym_Text_HumbertoDefeat:
	.string "Ουργκ!\n"
	.string "Δεν μπόρεσα να σε σταματήσω.$"

FortreeCity_Gym_Text_HumbertoPostBattle:
	.string "Καλύτερα να προσέχεις!\n"
	.string "Μην αποσπαστείς κοιτάζοντας την WINONA\l"
	.string "αλλιώς θα καταρρεύσεις!$"

FortreeCity_Gym_Text_DariusIntro:
	.string "Καλό θα ήταν να ξέρεις ότι υπάρχουν\n"
	.string "όλα τα είδη FLYING-type POKéMON.\p"
	.string "Το ξέρεις αυτό, σωστά;$"

FortreeCity_Gym_Text_DariusDefeat:
	.string "Φαίνεται πως ξέρεις τι κάνεις!$"

FortreeCity_Gym_Text_DariusPostBattle:
	.string "Ναι, με νίκησες εντάξει.\n"
	.string "Αλλά πρόσεχε! \l"
	.string "Η LEADER μας WINONA και τα POKéMON\l"
	.string "της δεν αστειεύονται.$"

FortreeCity_Gym_Text_WinonaIntro:
	.string "Είμαι η WINONA. Είμαι η LEADER\n"
	.string "στο FORTREE POKéMON GYM.\p"
	.string "Έχω γίνει ένα με τα BIRD POKéMON\n"
	.string "και πετάξαμε ψηλά στους ουρανούς…\p"
	.string "Όσο σκληρή κι αν ήταν η μάχη, έχουμε\n"
	.string "θριαμβεύσει με χάρη…\p"
	.string "Δες την κομψή χορογραφία\n"
	.string "των BIRD POKéMON και εμένα!$"

FortreeCity_Gym_Text_WinonaDefeat:
	.string "Ποτέ πριν δεν έχω δει έναν TRAINER\n"
	.string "να διοικεί τα POKéMON \l"
	.string "με περισσότερη χάρη από μένα…\p"
	.string "Σε αναγνώριση της ανδρείας σου,\n"
	.string "σου παρουσιάζω αυτό το GYM BADGE.$"

FortreeCity_Gym_Text_ReceivedFeatherBadge:
	.string "Το {PLAYER} έλαβε το FEATHER BADGE\n"
	.string "από την WINONA.$"

FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis:
	.string "Με το FEATHER BADGE, όλα τα POKéMON \n"
	.string "έως το LV 70, ακόμα κι αυτά από \l"
	.string "ανταλλαγές, θα σ' υπακούνε.\p"
	.string "Θα μπορείς επίσης να χρησιμοποιήσεις\n"
	.string "το HM MOVE FLY εκτός μάχης.\p"
	.string "Και αυτό…\n"
	.string "Αυτό είναι ένα δώρο από μένα.$"

FortreeCity_Gym_Text_ExplainAerialAce:
	.string "Το TM40 περιέχει το AERIAL ACE.\p"
	.string "Η ταχύτητά του…\n"
	.string "Κανένα POKéMON δεν θα μπορεί να το \l"
	.string "αποφύγει.\p"
	.string "… … … … … …$"

FortreeCity_Gym_Text_RegisteredWinona:
	.string "Καταχωρήθηκε η GYM LEADER WINONA\n"
	.string "στο POKéNAV.$"

FortreeCity_Gym_Text_WinonaPostBattle:
	.string "Αν και έπεσα μπροστά σου, θα\n"
	.string "παραμείνω αφοσιωμένη \l"
	.string "στα BIRD POKéMON.$"

FortreeCity_Gym_Text_GymStatue:
	.string "FORTREE CITY POKéMON GYM$"

FortreeCity_Gym_Text_GymStatueCertified:
	.string "FORTREE CITY POKéMON GYM\p"
	.string "ΠΙΣΤΟΠΟΙΗΜΕΝΟΙ TRAINERS ΤΗΣ WINONA:\n"
	.string "{PLAYER}$"

FortreeCity_Gym_Text_WinonaPreRematch:
	.string "WINONA: Εμείς οι άνθρωποι \n"
	.string "δεν μπορούμε ποτέ να ξεφύγουμε\l"
	.string "από τη βαρύτητα της Γης.\p"
	.string "Αλλά προσπαθώντας για την τελειότητα,\n"
	.string "έχουμε τη δύναμη να πετάξουμε ψηλά!\p"
	.string "Έχεις φτάσει στην κορυφή ως\n"
	.string "ο εν ενεργεία CHAMPION.\p"
	.string "Σε παρακαλώ, \n"
	.string "επίτρεψέ μου να δω τη δύναμή σου \l"
	.string "εν πτήσει!$"

FortreeCity_Gym_Text_WinonaRematchDefeat:
	.string "Απέτυχα να φτάσω το ύψος σου \n"
	.string "και πάλι…$"

FortreeCity_Gym_Text_WinonaPostRematch:
	.string "WINONA: Παρόλο που έχασα,\n"
	.string "τα φτερά της καρδιάς μου\l"
	.string "παραμένουν άθικτα.\p"
	.string "Μπορώ να σηκωθώ και \n"
	.string "να πετάξω ξανά και ξανά.\p"
	.string "Είμαι πεπεισμένη γι' αυτό!$"

FortreeCity_Gym_Text_WinonaRematchNeedTwoMons:
	.string "WINONA: Εμείς οι άνθρωποι \n"
	.string "δεν μπορούμε ποτέ να ξεφύγουμε\l"
	.string "από τη βαρύτητα της Γης.\p"
	.string "Αλλά προσπαθώντας για την τελειότητα,\n"
	.string "έχουμε τη δύναμη να πετάξουμε ψηλά!\p"
	.string "Έχεις φτάσει στην κορυφή ως\n"
	.string "ο εν ενεργεία CHAMPION.\p"
	.string "Σε παρακαλώ, επίτρεψέ μου \n"
	.string "να δω τη δύναμή σου\l"
	.string "εν πτήσει!\p"
	.string "Ω, όχι… \n"
	.string "Έχεις μόνο ένα POKéMON μαζί σου;\p"
	.string "Σε παρακαλώ επέστρεψε \n"
	.string "με δύο POKéMON τουλάχιστον.$"
