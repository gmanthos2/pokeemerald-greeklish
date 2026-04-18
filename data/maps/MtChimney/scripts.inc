.set LOCALID_ARCHIE, 1
.set LOCALID_MAXIE, 2
.set LOCALID_TABITHA, 3
.set LOCALID_MAGMA_GRUNT_2, 22
.set LOCALID_MAGMA_GRUNT_1, 29


MtChimney_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MtChimney_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MtChimney_OnTransition
	.byte 0

MtChimney_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 1
	end

MtChimney_OnResume:
	setstepcallback STEP_CB_ASH
	end

MtChimney_EventScript_Archie::
	lock
	faceplayer
	call_if_unset FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieGoStopTeamMagma
	call_if_set FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieBusyFighting
	closemessage
	applymovement LOCALID_ARCHIE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_EVIL_LEADER_PLEASE_STOP
	release
	end

MtChimney_EventScript_ArchieGoStopTeamMagma::
	msgbox MtChimney_Text_ArchieGoStopTeamMagma, MSGBOX_DEFAULT
	return

MtChimney_EventScript_ArchieBusyFighting::
	msgbox MtChimney_Text_ArchieIHaveMyHandsFull, MSGBOX_DEFAULT
	return

MtChimney_EventScript_Maxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MtChimney_Text_MeteoriteWillActivateVolcano, MSGBOX_DEFAULT
	applymovement LOCALID_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAXIE, Common_Movement_Delay48
	waitmovement 0
	msgbox MtChimney_Text_MaxieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat
	msgbox MtChimney_Text_MaxieYouHaventSeenLastOfMagma, MSGBOX_DEFAULT
	closemessage
	delay 30
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAXIE
	removeobject LOCALID_MAGMA_GRUNT_1
	removeobject LOCALID_TABITHA
	removeobject LOCALID_MAGMA_GRUNT_2
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_MAGMA
	fadescreen FADE_FROM_BLACK
	setobjectxyperm LOCALID_ARCHIE, 10, 12
	addobject LOCALID_ARCHIE
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieApproachPlayerEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieApproachPlayerNorth
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MtChimney_Text_ArchieThankYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieExitEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieExitNorth
	removeobject LOCALID_ARCHIE
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA
	setflag FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY
	clearflag FLAG_HIDE_FALLARBOR_HOUSE_PROF_COZMO
	setflag FLAG_HIDE_METEOR_FALLS_1F_1R_COZMO
	clearflag FLAG_HIDE_MT_CHIMNEY_LAVA_COOKIE_LADY
	releaseall
	end

MtChimney_EventScript_ArchieApproachPlayerEast::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieApproachPlayerEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieApproachPlayerNorth::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieApproachPlayerNorth
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitEast::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieExitEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitNorth::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieExitNorth
	waitmovement 0
	return

MtChimney_EventScript_LavaCookieLady::
	lock
	faceplayer
	showmoneybox 0, 0
	msgbox MtChimney_Text_LavaCookiesJust200, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_DeclineLavaCookie
	checkmoney 200
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_NotEnoughMoney
	msgbox MtChimney_Text_ThankYouDear, MSGBOX_DEFAULT
	checkitemspace ITEM_LAVA_COOKIE
	call_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RemoveMoney
	giveitem ITEM_LAVA_COOKIE
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_BagIsFull
	hidemoneybox
	release
	end

MtChimney_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_RemoveMoney::
	removemoney 200
	updatemoneybox
	return

MtChimney_EventScript_DeclineLavaCookie::
	msgbox MtChimney_Text_OhFineThen, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_NotEnoughMoney::
	msgbox MtChimney_Text_YouveNotGotTheMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_Movement_ArchieApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

MtChimney_Movement_ArchieExitEast:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_ArchieApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

MtChimney_Movement_ArchieExitNorth:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused2:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused3:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused4:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused5:
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused6:
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused7:
	delay_16
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused8:
	delay_16
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

MtChimney_Movement_Unused9:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused10:
	walk_down
	step_end

MtChimney_Movement_Unused11:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused12:
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused13:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused14:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_right
	step_end

MtChimney_Movement_Unused15:
	walk_left
	walk_in_place_faster_right
	delay_16
	step_end

MtChimney_EventScript_BusyAquaGrunt1::
	msgbox MtChimney_Text_MagmaOutnumbersUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt2::
	msgbox MtChimney_Text_LessHabitatForWaterPokemon, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt3::
	msgbox MtChimney_Text_MagmasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MT_CHIMNEY, MtChimney_Text_TabithaIntro, MtChimney_Text_TabithaDefeat
	msgbox MtChimney_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_2, MtChimney_Text_Grunt2Intro, MtChimney_Text_Grunt2Defeat
	msgbox MtChimney_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_BusyMagmaGrunt1::
	msgbox MtChimney_Text_TeamAquaAlwaysMessingWithPlans, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt2::
	msgbox MtChimney_Text_MeteoritesPackAmazingPower, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt3::
	msgbox MtChimney_Text_YouBetterNotMessWithUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt4::
	msgbox MtChimney_Text_AquasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt5::
	msgbox MtChimney_Text_DouseThemInFire, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt6::
	msgbox MtChimney_Text_KeepMakingMoreLand, MSGBOX_SIGN
	end

MtChimney_EventScript_MagmaPoochyena::
	msgbox MtChimney_Text_Bufoh, MSGBOX_SIGN
	end

MtChimney_EventScript_AquaPoochyena::
	msgbox MtChimney_Text_Bushaa, MSGBOX_SIGN
	end

MtChimney_EventScript_MeteoriteMachine::
	lockall
	goto_if_unset FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, MtChimney_EventScript_MachineOn
	goto_if_set FLAG_RECEIVED_METEORITE, MtChimney_EventScript_MachineOff
	msgbox MtChimney_Text_RemoveTheMeteorite, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_LeaveMeteoriteAlone
	msgbox MtChimney_Text_PlayerRemovedMeteorite, MSGBOX_DEFAULT
	giveitem ITEM_METEORITE
	setflag FLAG_RECEIVED_METEORITE
	releaseall
	end

MtChimney_EventScript_LeaveMeteoriteAlone::
	msgbox MtChimney_Text_PlayerLeftMeteorite, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOff::
	msgbox MtChimney_Text_MachineMakesNoResponse, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOn::
	msgbox MtChimney_Text_MetoriteFittedOnMachine, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_RouteSign::
	msgbox MtChimney_Text_RouteSign, MSGBOX_SIGN
	end

MtChimney_EventScript_Shelby::
	trainerbattle_single TRAINER_SHELBY_1, MtChimney_Text_ShelbyIntro, MtChimney_Text_ShelbyDefeat, MtChimney_EventScript_DefeatedShelby
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RematchShelby
	msgbox MtChimney_Text_ShelbyPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_DefeatedShelby::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_ShelbyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SHELBY_1
	release
	end

MtChimney_EventScript_RematchShelby::
	trainerbattle_rematch TRAINER_SHELBY_1, MtChimney_Text_ShelbyRematchIntro, MtChimney_Text_ShelbyRematchDefeat
	msgbox MtChimney_Text_ShelbyPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Melissa::
	trainerbattle_single TRAINER_MELISSA, MtChimney_Text_MelissaIntro, MtChimney_Text_MelissaDefeat
	msgbox MtChimney_Text_MelissaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sheila::
	trainerbattle_single TRAINER_SHEILA, MtChimney_Text_SheilaIntro, MtChimney_Text_SheilaDefeat
	msgbox MtChimney_Text_SheilaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Shirley::
	trainerbattle_single TRAINER_SHIRLEY, MtChimney_Text_ShirleyIntro, MtChimney_Text_ShirleyDefeat
	msgbox MtChimney_Text_ShirleyPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_Grunt1Intro, MtChimney_Text_Grunt1Defeat
	msgbox MtChimney_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sawyer::
	trainerbattle_single TRAINER_SAWYER_1, MtChimney_Text_SawyerIntro, MtChimney_Text_SawyerDefeat, MtChimney_EventScript_SawyerDefeated
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_SawyerRematch
	msgbox MtChimney_Text_SawyerPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_SawyerDefeated::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_SawyerRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SAWYER_1
	release
	end

MtChimney_EventScript_SawyerRematch::
	trainerbattle_rematch TRAINER_SAWYER_1, MtChimney_Text_SawyerRematchIntro, MtChimney_Text_SawyerRematchDefeat
	msgbox MtChimney_Text_SawyerPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_Text_MeteoriteWillActivateVolcano:
	.string "Η δύναμη που κρύβεται στον \n"
	.string "METEORITE…\p"
	.string "Ενισχύοντας τη δύναμή του με αυτό \n"
	.string "το μηχάνημα, η ηφαιστειακή \l"
	.string "δραστηριότητα του MT. CHIMNEY θα \l"
	.string "ενταθεί αμέσως…\p"
	.string "Η ενέργειά του θα μεγαλώσει βαθιά \n"
	.string "μέσα στον κρατήρα και…\l"
	.string "Φουφουφου…$"

MtChimney_Text_MaxieIntro:
	.string "MAXIE: Χμ;\n"
	.string "Ποιος είσαι εσύ;\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Είχα ακούσει τον ARCHIE να γκρινιάζει \n"
	.string "για ένα παιδί που ανακατεύεται στις \l"
	.string "υποθέσεις της TEAM AQUA.\p"
	.string "Εσένα πρέπει να εννοούσε.\p"
	.string "Χουμ! Σκέφτεσαι λοιπόν να \n"
	.string "παρέμβεις σε εμάς, την TEAM MAGMA;\p"
	.string "Τώρα άκου.\n"
	.string "Πριν από πολύ καιρό, τα ζωντανά \l"
	.string "πλάσματα χρησιμοποιούσαν τη \l"
	.string "στεριά για να ζήσουν και να \l"
	.string "αναπτυχθούν.\p"
	.string "Γι' αυτό η στεριά είναι το παν!\n"
	.string "Είναι το λίκνο όλων!\p"
	.string "Αυτός είναι ο λόγος που η TEAM MAGMA \n"
	.string "είναι αφοσιωμένη στην επέκταση της \l"
	.string "μάζας της στεριάς.\p"
	.string "Είναι για την περαιτέρω πρόοδο της \n"
	.string "ανθρωπότητας και των POKéMON!\p"
	.string "Και γι' αυτό, χρειαζόμαστε τη δύναμη \n"
	.string "αυτού που κοιμάται μέσα σε αυτό \l"
	.string "το βουνό…\p"
	.string "Ω! Δεν υπήρχε λόγος να μάθεις \n"
	.string "τόσα πολλά.\p"
	.string "Αλλά, δεν πειράζει!\n"
	.string "Θα σου διδάξω τις συνέπειες της \l"
	.string "παρέμβασης στο μεγάλο μας σχέδιο!$"

MtChimney_Text_MaxieDefeat:
	.string "Τι;!\p"
	.string "Εγώ, ο MAXIE, πιάστηκα απροετοίμαστος;!$"

MtChimney_Text_MaxieYouHaventSeenLastOfMagma:
	.string "MAXIE: Αλλά, αρκετά.\n"
	.string "Θα αποσυρθώ αυτή τη φορά.\p"
	.string "Αλλά μην νομίζεις ότι αυτή είναι η \n"
	.string "τελευταία φορά που βλέπεις την \l"
	.string "TEAM MAGMA.\p"
	.string "Φουφουφου…\p"
	.string "Ακόμα και χωρίς τον METEORITE, αν \n"
	.string "αποκτήσουμε εκείνο το ORB… \l"
	.string "Φουφουφου…$"

MtChimney_Text_TabithaIntro:
	.string "Χεχεχε!\p"
	.string "Ήρθες λοιπόν μέχρι εδώ!\p"
	.string "Αλλά είναι πολύ αργά!\n"
	.string "Έχω ήδη παραδώσει τον METEORITE \l"
	.string "από τα METEOR FALLS στο BOSS!$"

MtChimney_Text_TabithaDefeat:
	.string "Χεχεχε…\p"
	.string "Ακόμα κι αν έχασα, αν ο αρχηγός μας \n"
	.string "ξυπνήσει εκείνο το πράγμα…$"

MtChimney_Text_TabithaPostBattle:
	.string "BOSS, γρήγορα!\n"
	.string "Δώστε του την ενέργεια του \l"
	.string "METEORITE!\p"
	.string "Χεχεχε…$"

MtChimney_Text_Grunt2Intro:
	.string "Εμείς της TEAM MAGMA δουλεύουμε \n"
	.string "σκληρά για το καλό όλων.\p"
	.string "Για παράδειγμα, αν η δύναμη αυτού \n"
	.string "του πράγματος δημιουργούσε \l"
	.string "περισσότερη στεριά, θα υπήρχαν \l"
	.string "περισσότερα μέρη για να ζήσουμε.\p"
	.string "Όλοι θα ήταν χαρούμενοι!$"

MtChimney_Text_Grunt2Defeat:
	.string "Ε; Τι εννοείς ότι έχασα;$"

MtChimney_Text_Grunt2PostBattle:
	.string "Το BOSS μας λέει, “Θα κάνει τους \n"
	.string "πάντες χαρούμενους.”\p"
	.string "Αλλά γιατί όλοι συνεχίζουν να \n"
	.string "μπαίνουν στον δρόμο μας;$"

MtChimney_Text_Grunt1Intro:
	.string "Αν υπήρχε περισσότερη στεριά, θα \n"
	.string "μπορούσα να αποκτήσω ένα δικό μου \l"
	.string "μεγάλο σπίτι!\p"
	.string "Θα το χτίσω πάνω σε σκληρυμένη λάβα!$"

MtChimney_Text_Grunt1Defeat:
	.string "Το όνειρό μου για ένα μεγάλο σπίτι…$"

MtChimney_Text_Grunt1PostBattle:
	.string "Ένα παιδί σαν εσένα, θα έπρεπε να \n"
	.string "πλατσουρίζει στα κύματα!$"

MtChimney_Text_TeamAquaAlwaysMessingWithPlans:
	.string "Αυτή η ενοχλητική TEAM AQUA…\n"
	.string "Πάντα καταστρέφουν τα σχέδιά μας!$"

MtChimney_Text_MeteoritesPackAmazingPower:
	.string "Οι METEORITES έχουν εκπληκτική \n"
	.string "δύναμη!$"

MtChimney_Text_YouBetterNotMessWithUs:
	.string "Καλύτερα να μην μας ενοχλείς!\p"
	.string "Προσπαθούμε να ξυπνήσουμε εκείνο \n"
	.string "το πράγμα προς όφελος όλων!$"

MtChimney_Text_AquasNameSimilar:
	.string "Είμαστε η TEAM MAGMA!\p"
	.string "Εκείνοι είναι η TEAM AQUA!\p"
	.string "Με εκνευρίζει απίστευτα που \n"
	.string "χρησιμοποιούν ένα όνομα σαν το δικό μας!$"

MtChimney_Text_DouseThemInFire:
	.string "Ναι!\n"
	.string "Περιλούστε τους με φωτιά!$"

MtChimney_Text_KeepMakingMoreLand:
	.string "Θα συνεχίσουμε να δημιουργούμε \n"
	.string "περισσότερη στεριά!$"

MtChimney_Text_Bufoh:
	.string "Μπουφόχ!$"

MtChimney_Text_ArchieGoStopTeamMagma:
	.string "ARCHIE: Γκρρ, {PLAYER}!\n"
	.string "Θα έπρεπε να το είχα μαντέψει ότι θα \l"
	.string "εμφανιζόσουν!\p"
	.string "Δες και μόνος σου τι σκαρώνουν οι \n"
	.string "φανατικοί της TEAM MAGMA!\p"
	.string "Προσπαθούν να διοχετεύσουν τη δύναμη \n"
	.string "του κλεμμένου METEORITE στο ηφαίστειο!\p"
	.string "Κάνοντας κάτι τέτοιο, θα προκαλέσουν \n"
	.string "την έκρηξη του ηφαιστείου!$"

MtChimney_Text_ArchieIHaveMyHandsFull:
	.string "ARCHIE: Γκρρρ…\p"
	.string "Θέλω να σταματήσω αυτόν τον MAXIE,\n"
	.string "αλλά δεν μπορώ!\p"
	.string "Όχι όταν έχω τα χέρια μου γεμάτα \n"
	.string "παλεύοντας με τρεις αντιπάλους \l"
	.string "ταυτόχρονα!$"

MtChimney_Text_ArchieThankYou:
	.string "ARCHIE: {PLAYER}!\n"
	.string "Σε ευχαριστώ!\p"
	.string "Με τη βοήθειά σου, αποτρέψαμε το \n"
	.string "καταστροφικό σχέδιο της TEAM MAGMA!\p"
	.string "Αλλά… Εσύ…\n"
	.string "Με ποιανού το μέρος είσαι;\p"
	.string "Α, δεν έχει σημασία.\p"
	.string "Θα παραμείνουμε σε εγρήγορση και θα \n"
	.string "συνεχίσουμε την καταδίωξη της \l"
	.string "TEAM MAGMA.\p"
	.string "{PLAYER}, θα ξανασυναντηθούμε!$"

MtChimney_Text_MagmaOutnumbersUs:
	.string "Κρίμα… Η TEAM MAGMA μας ξεπερνά σε \n"
	.string "αριθμό! Δεν μπορούμε να τους \l"
	.string "προφτάσουμε!$"

MtChimney_Text_LessHabitatForWaterPokemon:
	.string "Αν επεκτείνουν τη στεριά, θα υπάρχουν \n"
	.string "λιγότερα ενδιαιτήματα για τα \l"
	.string "WATER POKéMON!$"

MtChimney_Text_MagmasNameSimilar:
	.string "Είμαστε η TEAM AQUA!\p"
	.string "Εκείνοι είναι η TEAM MAGMA!\p"
	.string "Με εξοργίζει που χρησιμοποιούν ένα \n"
	.string "τόσο μπερδεμένο όνομα!$"

MtChimney_Text_Bushaa:
	.string "Μπουσάα!$"

MtChimney_Text_LavaCookiesJust200:
	.string "Τα LAVA COOKIES είναι η τοπική \n"
	.string "σπεσιαλιτέ του MT. CHIMNEY.\p"
	.string "Δοκίμασε ένα. Είναι μόνο ¥200.$"

MtChimney_Text_ThankYouDear:
	.string "Σε ευχαριστώ, χρυσό μου!$"

MtChimney_Text_YouveNotGotTheMoney:
	.string "Ω, καλέ μου. Δεν μπορείς να αγοράσεις \n"
	.string "κάτι αν δεν έχεις τα χρήματα.$"

MtChimney_Text_OhFineThen:
	.string "Ω, καλά τότε.$"

MtChimney_Text_MetoriteFittedOnMachine:
	.string "Ένας METEORITE είναι τοποθετημένος σε \n"
	.string "ένα μυστηριώδες μηχάνημα…\p"
	.string "Το μηχάνημα φαίνεται να αποθηκεύει \n"
	.string "ενέργεια στον METEORITE.$"

MtChimney_Text_RemoveTheMeteorite:
	.string "Ένας METEORITE είναι τοποθετημένος \n"
	.string "σε ένα μυστηριώδες μηχάνημα…\p"
	.string "Θέλεις να αφαιρέσεις τον METEORITE;$"

MtChimney_Text_PlayerRemovedMeteorite:
	.string "{PLAYER} αφαίρεσε τον METEORITE από \n"
	.string "το μυστηριώδες μηχάνημα.$"

MtChimney_Text_PlayerLeftMeteorite:
	.string "{PLAYER} left the METEORITE where\n"
	.string "it was.$"

MtChimney_Text_MachineMakesNoResponse:
	.string "This mysterious machine…\n"
	.string "It makes no response whatsoever.$"

MtChimney_Text_RouteSign:
	.string "{DOWN_ARROW} JAGGED PATH\n"
	.string "LAVARIDGE TOWN AHEAD$"

MtChimney_Text_ShelbyIntro:
	.string "I've been to the hot springs and\n"
	.string "refreshed my tired bones.\l"
	.string "Right now I'm feeling strong!$"

MtChimney_Text_ShelbyDefeat:
	.string "Oh, my goodness.\n"
	.string "Now, aren't you something!$"

MtChimney_Text_ShelbyPostBattle:
	.string "Well, well, I've lost. I can't call\n"
	.string "myself an EXPERT now, can I?$"

MtChimney_Text_ShelbyRegister:
	.string "Thank you, child. It was fun, as if\n"
	.string "I were battling my own grandchild.\p"
	.string "Please, come see me again for\n"
	.string "a rematch.$"

MtChimney_Text_ShelbyRematchIntro:
	.string "If you can mesh your heart with those\n"
	.string "of your POKéMON, why, you should be\l"
	.string "able to achieve great things.$"

MtChimney_Text_ShelbyRematchDefeat:
	.string "Oh, my goodness.\n"
	.string "Now, aren't you something!$"

MtChimney_Text_ShelbyPostRematch:
	.string "Perhaps your heart has become one\n"
	.string "with the hearts of your POKéMON.$"

MtChimney_Text_MelissaIntro:
	.string "I've got the fire in me, baby.\n"
	.string "I can't stand it! I have to battle!$"

MtChimney_Text_MelissaDefeat:
	.string "Ooh, that was a scorching-hot match!$"

MtChimney_Text_MelissaPostBattle:
	.string "The heat of MT. CHIMNEY warms\n"
	.string "me up, baby!$"

MtChimney_Text_SheilaIntro:
	.string "I've finally made it to MT. CHIMNEY.\n"
	.string "I want to make my POKéMON battle!$"

MtChimney_Text_SheilaDefeat:
	.string "The way you battle…\n"
	.string "It's like a MT. CHIMNEY eruption!$"

MtChimney_Text_SheilaPostBattle:
	.string "Like I said, I've finally made it to\n"
	.string "MT. CHIMNEY. It would be a shame if\l"
	.string "I only do a little sightseeing…\p"
	.string "I want to get in some battles and buy\n"
	.string "COOKIES as souvenirs.$"

MtChimney_Text_ShirleyIntro:
	.string "Since I bathed in the hot springs,\n"
	.string "I've been feeling great!\l"
	.string "I'm sure I'm going to win!$"

MtChimney_Text_ShirleyDefeat:
	.string "Yowch!\n"
	.string "I'm getting a chill out of the water.$"

MtChimney_Text_ShirleyPostBattle:
	.string "I'll have to take another dip in the\n"
	.string "hot springs. Want to join me?\p"
	.string "Just joking!$"

MtChimney_Text_SawyerIntro:
	.string "This is one fine mountain! Plenty of\n"
	.string "hot people around for company!$"

MtChimney_Text_SawyerDefeat:
	.string "Oh, you're a real firebrand, too!$"

MtChimney_Text_SawyerPostBattle:
	.string "I think I need a dip in LAVARIDGE\n"
	.string "HOT SPRING with the locals!$"

MtChimney_Text_SawyerRegister:
	.string "I like little fireballs like you.\n"
	.string "Let me register you in my POKéNAV.$"

MtChimney_Text_SawyerRematchIntro:
	.string "I'm happily surrounded by hot people\n"
	.string "around these parts. I won't lose!$"

MtChimney_Text_SawyerRematchDefeat:
	.string "Gosh, you're still the same\n"
	.string "firebrand as before!$"

MtChimney_Text_SawyerPostRematch:
	.string "Actually, it really is hot here.\n"
	.string "I'm overdressed for these parts.$"

