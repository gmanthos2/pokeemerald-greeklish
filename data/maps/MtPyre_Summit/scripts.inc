.set LOCALID_ARCHIE, 2
.set LOCALID_OLD_LADY, 3
.set LOCALID_GRUNT_1, 4
.set LOCALID_GRUNT_2, 5
.set LOCALID_GRUNT_3, 6
.set LOCALID_GRUNT_4, 7
.set LOCALID_MAXIE, 8

MtPyre_Summit_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtPyre_Summit_OnTransition
	.byte 0

MtPyre_Summit_OnTransition:
	call_if_eq VAR_MT_PYRE_STATE, 2, MtPyre_Summit_EventScript_SetArchieMaxiePositions
	end

MtPyre_Summit_EventScript_SetArchieMaxiePositions::
	setobjectxyperm LOCALID_MAXIE, 23, 6
	setobjectxyperm LOCALID_ARCHIE, 22, 6
	end

MtPyre_Summit_EventScript_TeamAquaTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaExits::
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_ArchieFacePlayer0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_ArchieFacePlayer1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_ArchieFacePlayer2
	msgbox MtPyre_Summit_Text_ArchieWeGotTheOrbLetsGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_GRUNT_4
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_ARCHIE
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_TEAM_AQUA
	fadedefaultbgm
	fadescreen FADE_FROM_BLACK
	delay 20
	setvar VAR_MT_PYRE_STATE, 1
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_OldLadyApproachPlayer0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_OldLadyApproachPlayer1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_OldLadyApproachPlayer2
	msgbox MtPyre_Summit_Text_BothOrbsTakenMagmaLeftThis, MSGBOX_DEFAULT
	giveitem ITEM_MAGMA_EMBLEM
	setflag FLAG_RECEIVED_RED_OR_BLUE_ORB
	setflag FLAG_HIDE_JAGGED_PASS_MAGMA_GUARD
	releaseall
	end

MtPyre_Summit_EventScript_ArchieFacePlayer0::
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieFacePlayer0
	waitmovement 0
	return

@ Archie is already facing player
MtPyre_Summit_EventScript_ArchieFacePlayer1::
	return

MtPyre_Summit_EventScript_ArchieFacePlayer2::
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieFacePlayer2
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer0::
	applymovement LOCALID_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer0
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer1::
	applymovement LOCALID_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer1
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer2::
	applymovement LOCALID_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer2
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

MtPyre_Summit_Movement_OldLadyApproachPlayer0:
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_OldLadyApproachPlayer1:
	walk_down
	step_end

MtPyre_Summit_Movement_OldLadyApproachPlayer2:
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_ArchieFacePlayer0:
	walk_left
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_ArchieFacePlayer2:
	walk_right
	walk_in_place_faster_down
	step_end

MtPyre_Summit_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE, MtPyre_Summit_EventScript_OldManAfterRayquaza
	msgbox MtPyre_Summit_Text_WillYouHearOutMyTale, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, MtPyre_Summit_EventScript_OldManTale
	call_if_eq VAR_RESULT, NO, MtPyre_Summit_EventScript_DeclineOldManTale
	release
	end

MtPyre_Summit_EventScript_OldManAfterRayquaza::
	msgbox MtPyre_Summit_Text_HearTheNewLegendOfHoenn, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, MtPyre_Summit_EventScript_OldManNewTale
	call_if_eq VAR_RESULT, NO, MtPyre_Summit_EventScript_DeclineOldManTale
	release
	end

MtPyre_Summit_EventScript_OldManTale::
	msgbox MtPyre_Summit_Text_GroudonKyogreTale, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_DeclineOldManTale::
	msgbox MtPyre_Summit_Text_WellThatTooIsFine, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_OldManNewTale::
	msgbox MtPyre_Summit_Text_HoennTrioTale, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_OldLady::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_RED_OR_BLUE_ORB, MtPyre_Summit_EventScript_OldLadyAfterOrbsReturned
	call_if_ge VAR_MT_PYRE_STATE, 3, MtPyre_Summit_EventScript_OldLadyOrbsReturned
	goto_if_set FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, MtPyre_Summit_EventScript_OldLadyLegendariesAwake
	msgbox MtPyre_Summit_Text_OrbsHaveBeenTaken, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_OldLadyOrbsReturned::
	msgbox MtPyre_Summit_Text_ThoseTwoMenReturnedOrbs, MSGBOX_DEFAULT
	setflag FLAG_RETURNED_RED_OR_BLUE_ORB
	release
	end

MtPyre_Summit_EventScript_OldLadyLegendariesAwake::
	msgbox MtPyre_Summit_Text_GroudonKyogreAwakened, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_OldLadyAfterOrbsReturned::
	msgbox MtPyre_Summit_Text_SuperAncientPokemonTaughtUs, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_ArchieMaxieBeginExit0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_ArchieMaxieBeginExit1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_ArchieMaxieBeginExit2
	playse SE_PIN
	applymovement LOCALID_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAXIE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_MaxieApproachPlayer0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_MaxieApproachPlayer1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_MaxieApproachPlayer2
	msgbox MtPyre_Summit_Text_MaxieSilence, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_MaxieApproachArchie0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_MaxieApproachArchie1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_MaxieApproachArchie2
	delay 30
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_MAXIE
	setvar VAR_MT_PYRE_STATE, 3
	releaseall
	end

MtPyre_Summit_EventScript_ArchieMaxieBeginExit0::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit0
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_ArchieMaxieBeginExit1::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit1
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_ArchieMaxieBeginExit2::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit2
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer0::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie0
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer0
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer1::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer1
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer2::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer2
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie0::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie0
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie1::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie1
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie2::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie2
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_Movement_PlayerFaceMaxie0:
	delay_16
	delay_16
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_PlayerFaceMaxie:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_ArchieExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtPyre_Summit_Movement_MaxieExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit0:
	delay_16
	delay_8
	walk_left
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit1:
	delay_16
	delay_8
	walk_right
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit2:
	delay_16
	delay_8
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer0:
	walk_up
	walk_up
	walk_up
	walk_left
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer1:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer2:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_ArchieWatchMaxie:
	delay_16
	walk_in_place_faster_up
	step_end

MtPyre_Summit_Movement_PlayerWatchMaxie:
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie0:
	walk_down
	walk_right
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie1:
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie2:
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_1, MtPyre_Summit_Text_Grunt1Intro, MtPyre_Summit_Text_Grunt1Defeat
	msgbox MtPyre_Summit_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_2, MtPyre_Summit_Text_Grunt2Intro, MtPyre_Summit_Text_Grunt2Defeat
	msgbox MtPyre_Summit_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_3, MtPyre_Summit_Text_Grunt3Intro, MtPyre_Summit_Text_Grunt3Defeat
	msgbox MtPyre_Summit_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_4, MtPyre_Summit_Text_Grunt4Intro, MtPyre_Summit_Text_Grunt4Defeat
	msgbox MtPyre_Summit_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_Text_Grunt1Intro:
	.string "Όχι! Αυτά τα τσιράκια της TEAM MAGMA \n"
	.string "έφτασαν εδώ πριν από εμάς!\p"
	.string "Δεν πρέπει να μείνουμε πίσω!$"

MtPyre_Summit_Text_Grunt1Defeat:
	.string "Νόμιζα ότι ήσουν ένας από τους \n"
	.string "MAGMA που έτυχε να επιστρέψει…$"

MtPyre_Summit_Text_Grunt1PostBattle:
	.string "Ναι, λοιπόν, είσαι δυνατός…\n"
	.string "Αλλά είμαστε πολλοί!$"

MtPyre_Summit_Text_Grunt2Intro:
	.string "Χα!\n"
	.string "Τόσο το χειρότερο για σένα!\p"
	.string "Αν ερχόσουν νωρίτερα, θα έπρεπε \n"
	.string "μόνο να παλέψεις με τους \l"
	.string "αδύναμους της TEAM MAGMA.\p"
	.string "Αλλά αφού έφτασες τώρα, πρέπει να \n"
	.string "τα βάλεις με εμάς τους σκληρούς!$"

MtPyre_Summit_Text_Grunt2Defeat:
	.string "Ουργκ… Έπρεπε να σε είχα αφήσει \n"
	.string "να τα βάλεις με την TEAM MAGMA \l"
	.string "πρώτα…$"

MtPyre_Summit_Text_Grunt2PostBattle:
	.string "Δεν ξέρεις τίποτα!\n"
	.string "Γιατί λοιπόν μας ενοχλείς;$"

MtPyre_Summit_Text_Grunt3Intro:
	.string "Εσύ…\n"
	.string "Σε είδαμε στο MT. CHIMNEY.\p"
	.string "Δεν ανήκεις σε καμία TEAM, οπότε \n"
	.string "γιατί να βρίσκεσαι εδώ;$"

MtPyre_Summit_Text_Grunt3Defeat:
	.string "Αν πρόκειται να ενοχλήσεις \n"
	.string "κάποιον, ας είναι η TEAM MAGMA…$"

MtPyre_Summit_Text_Grunt3PostBattle:
	.string "Χεχ, δεν έχει σημασία!\n"
	.string "Κερδίσαμε λίγο χρόνο!\p"
	.string "Το BOSS πρέπει να έχει ήδη \n"
	.string "αρπάξει αυτό που έψαχνε!$"

MtPyre_Summit_Text_Grunt4Intro:
	.string "Ω, το ξέρω!\n"
	.string "Προσπάθησες να μπεις στην \l"
	.string "TEAM MAGMA, αλλά δεν σε δέχτηκαν!\p"
	.string "Λοιπόν, μην νομίζεις ότι θα σε \n"
	.string "αφήσουμε να μπεις στη δική μας \l"
	.string "TEAM AQUA!$"

MtPyre_Summit_Text_Grunt4Defeat:
	.string "Αν θέλεις τόσο πολύ να μπεις στην \n"
	.string "TEAM AQUA, μπορούμε να το \l"
	.string "σκεφτούμε…$"

MtPyre_Summit_Text_Grunt4PostBattle:
	.string "Έχουμε έναν εξαιρετικό συνδυασμό \n"
	.string "εδώ με τα μέλη μας και τον \l"
	.string "αρχηγό μας.$"

MtPyre_Summit_Text_ArchieWeGotTheOrbLetsGo:
	.string "ARCHIE: Ο MAXIE της TEAM MAGMA μας \n"
	.string "πρόλαβε, αλλά πήραμε κι εμείς \l"
	.string "αυτό που θέλαμε.\p"
	.string "Το RED ORB που φυλασσόταν στο \n"
	.string "MT. PYRE… Εγώ, ο ARCHIE, το έχω \l"
	.string "τώρα στην κατοχή μου!\p"
	.string "Φουφουφου… Τώρα μπορούμε να \n"
	.string "πραγματοποιήσουμε τον τελικό μας \l"
	.string "στόχο!\p"
	.string "Εντάξει, TEAM!\n"
	.string "Αποχωρούμε!$"

MtPyre_Summit_Text_BothOrbsTakenMagmaLeftThis:
	.string "Ω, όχι…\n"
	.string "Αυτό δεν μπορεί να συμβαίνει…\p"
	.string "Όχι μόνο το BLUE ORB, αλλά ακόμα \n"
	.string "και το RED ORB έχουν κλαπεί…\p"
	.string "Το BLUE ORB και το RED ORB δεν \n"
	.string "πρέπει ποτέ να χωρίζονται. \l"
	.string "Ανήκουν μαζί.\p"
	.string "Τι προσπαθούν να κάνουν αυτοί οι \n"
	.string "άνδρες με τα δύο ORBS;\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Α, ναι. Ήταν η TEAM MAGMA που ήρθε \n"
	.string "και πήρε πρώτη το BLUE ORB;\p"
	.string "Λοιπόν, μέσα στη βιασύνη τους, \n"
	.string "άφησαν αυτό πίσω τους.\p"
	.string "Δεν μπορούσα να φανταστώ τι \n"
	.string "ακριβώς θα μπορούσε να είναι.\p"
	.string "Θα ήθελα να το πάρεις εσύ.\n"
	.string "Ίσως φανεί χρήσιμο με κάποιο τρόπο.$"

MtPyre_Summit_Text_OrbsHaveBeenTaken:
	.string "Το BLUE ORB και το RED ORB που \n"
	.string "πήραν αυτοί οι σκοτεινοί άνδρες…\p"
	.string "Δεν πρέπει ποτέ να είναι χώρια… \n"
	.string "Φοβάμαι ότι κάτι τρομερό θα \l"
	.string "συμβεί…$"

MtPyre_Summit_Text_GroudonKyogreAwakened:
	.string "Ω, θεέ μου…\p"
	.string "Λες ότι και ο GROUDON και ο KYOGRE \n"
	.string "έχουν ξυπνήσει;\p"
	.string "Λέγεται ότι το BLUE ORB και το \n"
	.string "RED ORB καταπράυναν την οργή των \l"
	.string "δύο POKéMON…\p"
	.string "Λέγεται επίσης ότι ο πραγματικός \n"
	.string "κάτοχος των ORBS υπάρχει ακόμα.\p"
	.string "Ωστόσο, κανείς δεν ξέρει σε ποιον, \n"
	.string "ή σε τι ακριβώς, ανήκουν τα ORBS.\p"
	.string "Θα μπορούσε να είναι άνθρωπος, ή \n"
	.string "ίσως ένα POKéMON, αλλά κανείς \l"
	.string "δεν ξέρει.$"

MtPyre_Summit_Text_ThoseTwoMenReturnedOrbs:
	.string "Οι δύο άνδρες που πήραν τα ORBS \n"
	.string "επέστρεψαν για να τα παραδώσουν \l"
	.string "από μόνοι τους.\p"
	.string "Αυτοί οι άνδρες…\n"
	.string "Ίσως τελικά να μην είναι τόσο \l"
	.string "κακοί…$"

MtPyre_Summit_Text_SuperAncientPokemonTaughtUs:
	.string "Οι ενσαρκώσεις της στεριάς, της \n"
	.string "θάλασσας και του ουρανού…\p"
	.string "Αυτή λέγεται ότι είναι η ταυτότητα \n"
	.string "των υπερ-αρχαίων POKéMON…\p"
	.string "Με τον ίδιο τρόπο που εμείς οι \n"
	.string "άνθρωποι και τα POKéMON έχουμε \l"
	.string "ζωή, έτσι και ο κόσμος μας είναι \l"
	.string "ζωντανός…\p"
	.string "Τα υπερ-αρχαία POKéMON μας το \n"
	.string "δίδαξαν αυτό…$"

MtPyre_Summit_Text_WillYouHearOutMyTale:
	.string "Το MT. PYRE είναι εκεί που \n"
	.string "κατευνάζουμε τα πνεύματα των \l"
	.string "POKéMON που έχουν φύγει…\p"
	.string "Αυτό είναι ένα ψηλό μέρος από όπου \n"
	.string "μπορεί κανείς να δει όλο το HOENN…\p"
	.string "Τα ασώματα πνεύματα των POKéMON \n"
	.string "πρέπει να βρίσκουν παρηγοριά εδώ…\p"
	.string "Είναι σύμπτωση που βρίσκεσαι εδώ…\p"
	.string "Θέλεις να ακούσεις την ιστορία μου; \n"
	.string "Μια ιστορία που λέγεται από παλιά \l"
	.string "στην περιοχή HOENN;$"

MtPyre_Summit_Text_GroudonKyogreTale:
	.string "Συνέβη πριν από πολύ, πολύ καιρό…\p"
	.string "Ο κόσμος συγκλονίστηκε από μια \n"
	.string "σφοδρή σύγκρουση μεταξύ των POKéMON \l"
	.string "της στεριάς και των POKéMON της \l"
	.string "θάλασσας…\p"
	.string "Τα POKéMON της στεριάς ύψωσαν \n"
	.string "βουνά και δημιούργησαν ηπείρους…\p"
	.string "Τα POKéMON της θάλασσας ύψωσαν \n"
	.string "πελώρια κύματα και δημιούργησαν \l"
	.string "ωκεανούς…\p"
	.string "Η τρομερή μονομαχία τους μαινόταν \n"
	.string "χωρίς τέλος.\p"
	.string "Ο κόσμος τυλίχτηκε σε τεράστιες \n"
	.string "πυρκαγιές και άγριες καταιγίδες.\p"
	.string "Το BLUE ORB και το RED ORB έδωσαν \n"
	.string "τέλος στη συμφορά.\p"
	.string "Φως ξεχύθηκε από τα δύο ORBS και \n"
	.string "καταπράυνε τους οργισμένους \l"
	.string "αντιπάλους.\p"
	.string "Το ζευγάρι, πλέον ήρεμο, βούτηξε \n"
	.string "βαθιά στη θάλασσα όπου τελικά \l"
	.string "εξαφανίστηκε…$"

MtPyre_Summit_Text_WellThatTooIsFine:
	.string "Καταλαβαίνω…\n"
	.string "Λοιπόν, κι αυτό εντάξει είναι…$"

MtPyre_Summit_Text_MaxieSilence:
	.string "MAXIE: {PLAYER}…\p"
	.string "… … … … … …\n"
	.string "… … … … … …$"

MtPyre_Summit_Text_HearTheNewLegendOfHoenn:
	.string "Ο ρόλος μου είναι να μεταφέρω τους \n"
	.string "θρύλους του HOENN στις μελλοντικές \l"
	.string "γενιές.\p"
	.string "Και η κρίση που μόλις τελείωσε στη \n"
	.string "SOOTOPOLIS ξαναέγραψε έναν \l"
	.string "θρύλο…\p"
	.string "Έχεις χρόνο να ακούσεις τον νέο \n"
	.string "θρύλο του HOENN;$"

MtPyre_Summit_Text_HoennTrioTale:
	.string "Συνέβη πριν από πολύ, πολύ καιρό…\p"
	.string "Ο κόσμος συγκλονίστηκε από μια \n"
	.string "σφοδρή σύγκρουση μεταξύ των POKéMON \l"
	.string "της στεριάς και των POKéMON της \l"
	.string "θάλασσας…\p"
	.string "Τα POKéMON της στεριάς ύψωσαν \n"
	.string "βουνά και δημιούργησαν ηπείρους…\p"
	.string "Τα POKéMON της θάλασσας ύψωσαν \n"
	.string "πελώρια κύματα και δημιούργησαν \l"
	.string "ωκεανούς…\p"
	.string "Η τρομερή μονομαχία τους μαινόταν \n"
	.string "χωρίς τέλος.\p"
	.string "Ο κόσμος τυλίχτηκε σε τεράστιες \n"
	.string "φωτιές και άγριες καταιγίδες.\p"
	.string "Ήταν τότε που το POKéMON του \n"
	.string "ουρανού κατέβηκε μέσα από μια \l"
	.string "καταιγίδα.\p"
	.string "Το POKéMON, λάμποντας με ένα ζωηρό \n"
	.string "πράσινο χρώμα, καταπράυνε τα δύο \l"
	.string "οργισμένα POKéMON.\p"
	.string "Μετά, έχοντας επιτελέσει το καθήκον \n"
	.string "του, το πράσινο POKéMON πέταξε \l"
	.string "μακριά στο αχανές γαλάζιο…$"

