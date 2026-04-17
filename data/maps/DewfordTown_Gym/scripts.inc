DewfordTown_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_Gym_OnTransition
	.byte 0

DewfordTown_Gym_OnTransition:
	call DewfordTown_Gym_EventScript_SetFlashLevel
	end

DewfordTown_Gym_EventScript_SetFlashLevel::
	goto_if_defeated TRAINER_BRAWLY_1, DewfordTown_Gym_EventScript_SetLightsOn
	call DewfordTown_Gym_EventScript_CountTrainersDefeated
	copyvar VAR_0x8001, VAR_0x8000
	goto_if_eq VAR_0x8000, 0, DewfordTown_Gym_EventScript_SetFlashLevel7
	goto_if_eq VAR_0x8000, 1, DewfordTown_Gym_EventScript_SetFlashLevel6
	goto_if_eq VAR_0x8000, 2, DewfordTown_Gym_EventScript_SetFlashLevel5
	goto_if_eq VAR_0x8000, 3, DewfordTown_Gym_EventScript_SetFlashLevel4
	goto_if_eq VAR_0x8000, 4, DewfordTown_Gym_EventScript_SetFlashLevel3
	goto_if_eq VAR_0x8000, 5, DewfordTown_Gym_EventScript_SetFlashLevel2
	goto DewfordTown_Gym_EventScript_SetFlashLevel1

DewfordTown_Gym_EventScript_SetLightsOn::
	setflashlevel 0
	return

@ Brightest
DewfordTown_Gym_EventScript_SetFlashLevel1::
	setflashlevel 1
	return

DewfordTown_Gym_EventScript_SetFlashLevel2::
	setflashlevel 2
	return

DewfordTown_Gym_EventScript_SetFlashLevel3::
	setflashlevel 3
	return

DewfordTown_Gym_EventScript_SetFlashLevel4::
	setflashlevel 4
	return

DewfordTown_Gym_EventScript_SetFlashLevel5::
	setflashlevel 5
	return

DewfordTown_Gym_EventScript_SetFlashLevel6::
	setflashlevel 6
	return

@ Darkest
DewfordTown_Gym_EventScript_SetFlashLevel7::
	setflashlevel 7
	return

DewfordTown_Gym_EventScript_BrightenRoom::
	call DewfordTown_Gym_EventScript_CountTrainersDefeated
	nop1
	goto_if_eq VAR_0x8000, VAR_0x8001, DewfordTown_Gym_EventScript_NoLightChange
	copyvar VAR_0x8001, VAR_0x8000
	goto_if_eq VAR_0x8000, 1, DewfordTown_Gym_EventScript_AnimateFlash1Trainer
	goto_if_eq VAR_0x8000, 2, DewfordTown_Gym_EventScript_AnimateFlash2Trainers
	goto_if_eq VAR_0x8000, 3, DewfordTown_Gym_EventScript_AnimateFlash3Trainers
	goto_if_eq VAR_0x8000, 4, DewfordTown_Gym_EventScript_AnimateFlash4Trainers
	goto_if_eq VAR_0x8000, 5, DewfordTown_Gym_EventScript_AnimateFlash5Trainers
	goto_if_eq VAR_0x8000, 6, DewfordTown_Gym_EventScript_AnimateFlash6Trainers

DewfordTown_Gym_EventScript_NoLightChange::
	return

@ NOTE: A little confusingly, a larger animateflash param value is a smaller flash radius
DewfordTown_Gym_EventScript_AnimateFlash1Trainer::
	playse SE_SWITCH
	animateflash 6
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash2Trainers::
	playse SE_SWITCH
	animateflash 5
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash3Trainers::
	playse SE_SWITCH
	animateflash 4
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash4Trainers::
	playse SE_SWITCH
	animateflash 3
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash5Trainers::
	playse SE_SWITCH
	animateflash 2
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash6Trainers::
	playse SE_SWITCH
	animateflash 1
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlashFullBrightness::
	playse SE_SWITCH
	animateflash 0
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_CountTrainersDefeated::
	setvar VAR_0x8000, 0
	goto_if_not_defeated TRAINER_TAKAO, DewfordTown_Gym_EventScript_CheckJocelyn
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckJocelyn::
	goto_if_not_defeated TRAINER_JOCELYN, DewfordTown_Gym_EventScript_CheckLaura
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckLaura::
	goto_if_not_defeated TRAINER_LAURA, DewfordTown_Gym_EventScript_CheckBrenden
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckBrenden::
	goto_if_not_defeated TRAINER_BRENDEN, DewfordTown_Gym_EventScript_CheckCristian
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckCristian::
	goto_if_not_defeated TRAINER_CRISTIAN, DewfordTown_Gym_EventScript_CheckLilith
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckLilith::
	goto_if_not_defeated TRAINER_LILITH, DewfordTown_Gym_EventScript_StopCountingTrainers
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_StopCountingTrainers::
	return

DewfordTown_Gym_EventScript_Brawly::
	trainerbattle_single TRAINER_BRAWLY_1, DewfordTown_Gym_Text_BrawlyIntro, DewfordTown_Gym_Text_BrawlyDefeat, DewfordTown_Gym_EventScript_BrawlyDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_Gym_EventScript_BrawlyRematch
	goto_if_unset FLAG_RECEIVED_TM_BULK_UP, DewfordTown_Gym_EventScript_GiveBulkUp2
	msgbox DewfordTown_Gym_Text_BrawlyPostBattle, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_BrawlyDefeated::
	call DewfordTown_Gym_EventScript_AnimateFlashFullBrightness
	message DewfordTown_Gym_Text_ReceivedKnuckleBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox DewfordTown_Gym_Text_KnuckleBadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_DEWFORD_GYM
	setflag FLAG_BADGE02_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 2
	call Common_EventScript_SetGymTrainers
	call DewfordTown_Gym_EventScript_GiveBulkUp
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox DewfordTown_Gym_Text_RegisteredBrawly, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_BRAWLY_MATCH_CALL
	setvar VAR_ROXANNE_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_ROXANNE_FIRST_CALL
	release
	end

DewfordTown_Gym_EventScript_GiveBulkUp::
	giveitem ITEM_TM_BULK_UP
	goto_if_eq VAR_RESULT, 0, Common_EventScript_BagIsFull
	msgbox DewfordTown_Gym_Text_ExplainBulkUp, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_BULK_UP
	return

DewfordTown_Gym_EventScript_GiveBulkUp2:
	giveitem ITEM_TM_BULK_UP
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	msgbox DewfordTown_Gym_Text_ExplainBulkUp, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_BULK_UP
	release
	end

DewfordTown_Gym_EventScript_BrawlyRematch::
	trainerbattle_rematch_double TRAINER_BRAWLY_1, DewfordTown_Gym_Text_BrawlyPreRematch, DewfordTown_Gym_Text_BrawlyRematchDefeat, DewfordTown_Gym_Text_BrawlyRematchNeedTwoMons
	msgbox DewfordTown_Gym_Text_BrawlyPostRematch, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_Takao::
	trainerbattle_single TRAINER_TAKAO, DewfordTown_Gym_Text_TakaoIntro, DewfordTown_Gym_Text_TakaoDefeat, DewfordTown_Gym_EventScript_TakaoBrightenRoom
	msgbox DewfordTown_Gym_Text_TakaoPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_TakaoBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Jocelyn::
	trainerbattle_single TRAINER_JOCELYN, DewfordTown_Gym_Text_JocelynIntro, DewfordTown_Gym_Text_JocelynDefeat, DewfordTown_Gym_EventScript_JocelynBrightenRoom
	msgbox DewfordTown_Gym_Text_JocelynPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_JocelynBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Laura::
	trainerbattle_single TRAINER_LAURA, DewfordTown_Gym_Text_LauraIntro, DewfordTown_Gym_Text_LauraDefeat, DewfordTown_Gym_EventScript_LauraBrightenRoom
	msgbox DewfordTown_Gym_Text_LauraPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_LauraBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Brenden::
	trainerbattle_single TRAINER_BRENDEN, DewfordTown_Gym_Text_BrendenIntro, DewfordTown_Gym_Text_BrendenDefeat, DewfordTown_Gym_EventScript_BrendenBrightenRoom
	msgbox DewfordTown_Gym_Text_BrendenPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_BrendenBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Cristian::
	trainerbattle_single TRAINER_CRISTIAN, DewfordTown_Gym_Text_CristianIntro, DewfordTown_Gym_Text_CristianDefeat, DewfordTown_Gym_EventScript_CristianBrightenRoom
	msgbox DewfordTown_Gym_Text_CristianPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_CristianBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Lilith::
	trainerbattle_single TRAINER_LILITH, DewfordTown_Gym_Text_LilithIntro, DewfordTown_Gym_Text_LilithDefeat, DewfordTown_Gym_EventScript_LilithBrightenRoom
	msgbox DewfordTown_Gym_Text_LilithPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_LilithBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_DEWFORD_GYM, DewfordTown_Gym_EventScript_GymGuidePostVictory
	msgbox DewfordTown_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_GymGuidePostVictory::
	msgbox DewfordTown_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE02_GET, DewfordTown_Gym_EventScript_GymStatueCertified
	goto DewfordTown_Gym_EventScript_GymStatue
	end

DewfordTown_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE02_GET, DewfordTown_Gym_EventScript_GymStatueCertified
	goto DewfordTown_Gym_EventScript_GymStatue
	end

DewfordTown_Gym_EventScript_GymStatueCertified::
	msgbox DewfordTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Gym_EventScript_GymStatue::
	msgbox DewfordTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Gym_Text_GymGuideAdvice:
	.string "Έι, πώς πάει {PLAYER}, \n"
	.string "μελλοντικέ CHAMPION;\p"
	.string "Ο GYM LEADER της DEWFORD, ο BRAWLY, \n"
	.string "έχει POKéMON τύπου FIGHTING.\p"
	.string "Το να τον αντιμετωπίσεις με NORMAL\n"
	.string "POKéMON είναι σαν να ζητάς μπελάδες.\p"
	.string "Τα POKéMON τύπου FIGHTING θα \n"
	.string "διαλύσουν τα NORMAL,\l"
	.string "γι' αυτό πρόσεχε!\p"
	.string "Και το χειρότερο, το GYM είναι τόσο \n"
	.string "σκοτεινό όσο ο βυθός του ωκεανού.\p"
	.string "Αλλά θα φωτίζει κάθε φορά που \n"
	.string "θα νικάς τους TRAINERS.\p"
	.string "Έι, έλα τώρα, δώσε τα όλα!$"

DewfordTown_Gym_Text_GymGuidePostVictory:
	.string "Ουάου! Έγινε πολύ φωτεινά εδώ μέσα!\p"
	.string "Το μέλλον σου είναι επίσης λαμπρό!$"

DewfordTown_Gym_Text_TakaoIntro:
	.string "Η δύναμη ειναι το παν!\n"
	.string "Έλα!$"

DewfordTown_Gym_Text_TakaoDefeat:
	.string "Δεν είχα αρκετή δύναμη…$"

DewfordTown_Gym_Text_TakaoPostBattle:
	.string "Η επιδεξιότητά σου ξεπέρασε τη δύναμή \n"
	.string "μου!\l"
	.string "Η τεχνική σου είναι αξιέπαινη!$"

DewfordTown_Gym_Text_JocelynIntro:
	.string "Δεν χρειάζεται να ασχοληθεί ο \n"
	.string "BRAWLY!\p"
	.string "Θα σε συντρίψω!$"

DewfordTown_Gym_Text_JocelynDefeat:
	.string "Μα… Πώς;\n"
	.string "Πώς μπόρεσα να χάσω τόσο εύκολα;$"

DewfordTown_Gym_Text_JocelynPostBattle:
	.string "Δεν θα πάει χαμένη αυτή η ήττα.\n"
	.string "Θα τη χρησιμοποιήσω για να εκπαιδευτώ!\p"
	.string "Μια μέρα θα γίνω GYM LEADER…\p"
	.string "Όχι, θα γίνω η POKéMON LEAGUE\n"
	.string "CHAMPION!$"

DewfordTown_Gym_Text_LauraIntro:
	.string "Μην τολμήσεις να με υποτιμήσεις!\n"
	.string "Δεν θα φταίω εγώ αν κλάψεις!$"

DewfordTown_Gym_Text_LauraDefeat:
	.string "Ουάαα!\n"
	.string "Έχασα!$"

DewfordTown_Gym_Text_LauraPostBattle:
	.string "Μάχομαι στο σκοτάδι για να κάνω την \n"
	.string "καρδιά μου πιο δυνατή.\p"
	.string "Αλλά επειδή είναι τόσο σκοτεινά, δεν\n"
	.string "μπορώ ποτέ να δω το πρόσωπο του BRAWLY…$"

DewfordTown_Gym_Text_LilithIntro:
	.string "Ουφούφου…\n"
	.string "Σκοντάφτεις στο σκοτάδι;$"

DewfordTown_Gym_Text_LilithDefeat:
	.string "Ωχ, εσύ…\n"
	.string "Δεν θέλω να σε ξέρω!$"

DewfordTown_Gym_Text_LilithPostBattle:
	.string "Σου αξίζει να χαθείς και να \n"
	.string "καταλήξεις πάλι στην είσοδο!$"

DewfordTown_Gym_Text_BrendenIntro:
	.string "Θα σου δείξω το σθένος \n"
	.string "ενός ναυτικού!$"

DewfordTown_Gym_Text_BrendenDefeat:
	.string "Πώς συνέβη αυτό;\n"
	.string "Δεν μου μοιάζει να χάνω έτσι!$"

DewfordTown_Gym_Text_BrendenPostBattle:
	.string "Ω, ναι! Είσαι άξιος να δεις \n"
	.string "τον GYM LEADER μας.$"

DewfordTown_Gym_Text_CristianIntro:
	.string "Αν θες να περάσεις, θα πρέπει να είναι\n"
	.string "από πάνω μου!$"

DewfordTown_Gym_Text_CristianDefeat:
	.string "Γκρρρ!\n"
	.string "Υπερβολικά δυνατός!$"

DewfordTown_Gym_Text_CristianPostBattle:
	.string "Νίκησες!\n"
	.string "Πήγαινε πάρε αυτό το BADGE!$"

DewfordTown_Gym_Text_BrawlyIntro:
	.string "Είμαι ο BRAWLY!\n"
	.string "Ο GYM LEADER της DEWFORD!\p"
	.string "Έχω συνηθίσει στα άγρια κύματα \n"
	.string "αυτών των περιοχών, και έχω γίνει \l"
	.string "σκληρός στο σκοτεινό σπήλαιο!\p"
	.string "Λοιπόν, ήθελες να με προκαλέσεις;\n"
	.string "Ας δούμε τι αξίζεις!$"

DewfordTown_Gym_Text_BrawlyDefeat:
	.string "Ουάου, ποπώ! Έκανες πολύ μεγαλύτερο \n"
	.string "πάταγο απ' ό,τι περίμενα!\p"
	.string "Με βούλιαξες!\p"
	.string "Εντάξει, με έπιασες.\n"
	.string "Πάρε αυτό το GYM BADGE!$"

DewfordTown_Gym_Text_ReceivedKnuckleBadge:
	.string "Το {PLAYER} έλαβε το KNUCKLE BADGE\n"
	.string "από τον BRAWLY.$"

DewfordTown_Gym_Text_KnuckleBadgeInfoTakeThis:
	.string "Το KNUCKLE BADGE κάνει όλα τα POKéMON\n"
	.string "μέχρι το Level 30, ακόμα και αυτά που \l"
	.string "έλαβες σε ανταλλαγή, να υπακούν.\p"
	.string "Και τώρα θα μπορείς να \n"
	.string "χρησιμοποιήσεις το FLASH \l"
	.string "και εκτός μάχης.\p"
	.string "Αν θέλεις, πάρε και \n"
	.string "αυτό το TECHNICAL MACHINE.$"

DewfordTown_Gym_Text_ExplainBulkUp:
	.string "Αυτό το TM08 περιέχει το BULK UP.\p"
	.string "Είναι μια κίνηση που αυξάνει τα\n"
	.string "stats ATTACK και DEFENSE.\p"
	.string "… … … … … …$"

DewfordTown_Gym_Text_RegisteredBrawly:
	.string "Ο GYM LEADER BRAWLY\n"
	.string "συσχετίστηκε στο POKéNAV.$"

DewfordTown_Gym_Text_BrawlyPostBattle:
	.string "Βλέπω το ταλέντο σου να γίνεται ένα\n"
	.string "γιγάντιο κύμα που θα προκαλέσει\l"
	.string "εντύπωση στους άλλους TRAINERS \l"
	.string "μια μέρα!$"

DewfordTown_Gym_Text_GymStatue:
	.string "DEWFORD TOWN POKéMON GYM$"

DewfordTown_Gym_Text_GymStatueCertified:
	.string "DEWFORD TOWN POKéMON GYM\p"
	.string "ΠΙΣΤΟΠΟΙΗΜΕΝΟΙ TRAINERS:\n"
	.string "{PLAYER}$"

DewfordTown_Gym_Text_BrawlyPreRematch:
	.string "BRAWLY: Ένα κύμα μπορεί να αποτραβηχτεί\n"
	.string "μα πάντα επιστρέφει στην ακτή.\p"
	.string "Ένα τεράστιο κύμα ταλέντου σαν εσένα…\n"
	.string "Ήξερα ότι θα επέστρεφες!\p"
	.string "Δείξε μου πόσο πιο δυνατός\n"
	.string "έγινες!$"

DewfordTown_Gym_Text_BrawlyRematchDefeat:
	.string "Ουάου!\n"
	.string "Με βούλιαξες πάλι!$"

DewfordTown_Gym_Text_BrawlyPostRematch:
	.string "BRAWLY: Το να μάχεσαι είναι και αρκετά \n"
	.string "αχανές μα και βαθύ.\l"
	.string "Δεν μπορείς να δεις τον βυθό.\l"
	.string "Είναι ακριβώς όπως η θάλασσα\l"
	.string "του HOENN!$"

DewfordTown_Gym_Text_BrawlyRematchNeedTwoMons:
	.string "BRAWLY: Ένα κύμα μπορεί να αποτραβηχτεί\n"
	.string "μα πάντα επιστρέφει στην ακτή.\p"
	.string "Ένα τεράστιο κύμα ταλέντου σαν εσένα…\n"
	.string "Ήξερα ότι θα επέστρεφες!\p"
	.string "Ω; Έχεις μόνο ένα POKéMON\n"
	.string "που μπορεί να μάχεται.\p"
	.string "Λυπάμαι, αλλά θα ήθελα να έρθεις \n"
	.string "πίσω με τουλάχιστον δύο POKéMON.$"
