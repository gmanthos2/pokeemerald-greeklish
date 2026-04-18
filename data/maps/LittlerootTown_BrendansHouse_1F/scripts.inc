.set LOCALID_MOM, 1
.set LOCALID_RIVAL_MOM, 4
.set LOCALID_RIVAL, 7

LittlerootTown_BrendansHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, LittlerootTown_BrendansHouse_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_BrendansHouse_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_BrendansHouse_1F_OnFrame
	.byte 0

LittlerootTown_BrendansHouse_1F_OnLoad:
	call_if_lt VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes
	call_if_set FLAG_RECEIVED_RUNNING_SHOES, LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual
	end

LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes::
	setmetatile 5, 4, METATILE_BrendansMaysHouse_MovingBox_Open, TRUE
	setmetatile 5, 2, METATILE_BrendansMaysHouse_MovingBox_Closed, TRUE
	return

LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual
	return

LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual::
	setmetatile 3, 7, METATILE_BrendansMaysHouse_BookOnTable, TRUE
	return

LittlerootTown_BrendansHouse_1F_OnTransition:
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV
	end

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs::
	setobjectxyperm LOCALID_MOM, 8, 4
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV::
	setobjectxyperm LOCALID_MOM, 4, 5
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor::
	setobjectxyperm LOCALID_MOM, 9, 8
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

@ Many of the below scripts have no gender check because they assume youre in the correct house
@ The below SS Ticket script uses Mays house state by accident(?), but theyre both set identically after the intro
LittlerootTown_BrendansHouse_1F_OnFrame:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 1, LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 3, PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV
	.2byte 0

LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock::
	lockall
	msgbox PlayersHouse_1F_Text_GoSetTheClock, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	applymovement LOCALID_MOM, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	waitmovement 0
	warp MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F, 7, 1
	waitstate
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs:
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn::
	lockall
	setvar VAR_0x8004, LOCALID_MOM
	setvar VAR_0x8005, MALE
	goto PlayersHouse_1F_EventScript_EnterHouseMovingIn
	end

LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport::
	lockall
	setvar VAR_0x8004, MALE
	setvar VAR_0x8005, LOCALID_MOM
	goto PlayersHouse_1F_EventScript_PetalburgGymReportMale
	end

LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor::
	lockall
	playse SE_PIN
	applymovement LOCALID_RIVAL_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL_MOM, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_RIVAL_MOM, LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach
	waitmovement 0
	special GetRivalSonDaughterString
	msgbox RivalsHouse_1F_Text_OhYoureTheNewNeighbor, MSGBOX_DEFAULT
	setflag FLAG_MET_RIVAL_MOM
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 2
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_GoSeeRoom::
	lockall
	setvar VAR_0x8004, LOCALID_MOM
	setvar VAR_0x8005, MALE
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto PlayersHouse_1F_EventScript_MomGoSeeRoom
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival0::
	lockall
	setvar VAR_0x8008, 0
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival1::
	lockall
	setvar VAR_0x8008, 1
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival2::
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival::
	playse SE_EXIT
	delay 10
	addobject LOCALID_RIVAL
	delay 30
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call_if_ne VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2
	msgbox RivalsHouse_1F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2
	playse SE_EXIT
	removeobject LOCALID_RIVAL
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_BRENDAN
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	delay 30
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1:
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0::
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1::
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2::
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1:
	delay_16
	delay_8
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

PlayersHouse_1F_Text_IsntItNiceInHere:
	.string "MOM: Είδες, {PLAYER};\n"
	.string "Δεν είναι ωραία εδώ μέσα;$"

PlayersHouse_1F_Text_MoversPokemonGoSetClock:
	.string "Τα POKéMON των μεταφορέων έκαναν \n"
	.string "όλη τη δουλειά.\l"
	.string "Αυτό είναι τόσο βολικό!\p"
	.string "{PLAYER}, το δωμάτιό σου είναι πάνω.\n"
	.string "Πήγαινε να το δεις, χρυσό μου!\p"
	.string "Ο DAD σου πήρε ένα νέο ρολόι \n"
	.string "για να σηματοδοτήσει \l"
	.string "τη μετακόμισή μας εδώ.\l"
	.string "Μην ξεχάσεις να το ρυθμίσεις!$"

PlayersHouse_1F_Text_ArentYouInterestedInRoom:
	.string "MOM: Λοιπόν, {PLAYER};\p"
	.string "Δεν ενδιαφέρεσαι να δεις το\n"
	.string "δικό σου δωμάτιο;$"

PlayersHouse_1F_Text_GoSetTheClock:
	.string "MOM: {PLAYER}.\p"
	.string "Πήγαινε να ρυθμίσεις το ρολόι \n"
	.string "στο δωμάτιό σου, χρυσό μου.$"

PlayersHouse_1F_Text_OhComeQuickly:
	.string "MOM: Ω! {PLAYER}, {PLAYER}!\n"
	.string "Γρήγορα! Έλα γρήγορα!$"

PlayersHouse_1F_Text_MaybeDadWillBeOn:
	.string "MOM: Κοίτα! Είναι το PETALBURG GYM!\n"
	.string "Ίσως είναι ο DAD στην τηλεόραση!$"

PlayersHouse_1F_Text_ItsOverWeMissedHim:
	.string "MOM: Ω… Τελείωσε.\p"
	.string "Νομίζω ότι έδειχνε τον DAD \n"
	.string "αλλά τον χάσαμε.\l"
	.string "Τι κρίμα.$"

PlayersHouse_1F_Text_GoIntroduceYourselfNextDoor:
	.string "Α, ναι.\n"
	.string "Ένας φίλος του DAD μένει στην πόλη.\p"
	.string "Το όνομά του είναι PROF. BIRCH.\p"
	.string "Μένει ακριβώς δίπλα, \n"
	.string "οπότε θα πρέπει να πας \l"
	.string "να συστηθείς.$"

PlayersHouse_1F_Text_SeeYouHoney:
	.string "MOM: Τα λέμε, χρυσό μου!$"

PlayersHouse_1F_Text_DidYouMeetProfBirch:
	.string "MOM: Συστήθηκες στον\n"
	.string "PROF. BIRCH;$"

PlayersHouse_1F_Text_YouShouldRestABit:
	.string "MOM: Πώς τα πας, {PLAYER};\n"
	.string "Φαίνεσαι λίγο κουρασμένο παιδί μου.\p"
	.string "Νομίζω ότι πρέπει να\n"
	.string "ξεκουραστείς λιγάκι.$"

PlayersHouse_1F_Text_TakeCareHoney:
	.string "MOM: Να προσέχεις, χρυσό μου!$"

PlayersHouse_1F_Text_GotDadsBadgeHeresSomethingFromMom:
	.string "MOM: Α; Ο DAD σου έδωσε αυτό το BADGE;\p"
	.string "Τότε ορίστε κάτι από την MOM σου!$"

PlayersHouse_1F_Text_DontPushYourselfTooHard:
	.string "Μην πιέζεις πολύ τον \n"
	.string "εαυτό σου, χρυσό μου.\l"
	.string "Μπορείς πάντα να γυρίσεις σπίτι.\p"
	.string "Πάμε, χρυσό μου!$"

PlayersHouse_1F_Text_IsThatAPokenav:
	.string "MOM: Τι είναι αυτό; Ένα POKéNAV;\n"
	.string "Στο έδωσε κάποιος από τη DEVON;\p"
	.string "Λοιπόν, τι θα έλεγες να\n"
	.string "καταχωρήσεις τη MOM σου;\p"
	.string "… … …$"

PlayersHouse_1F_Text_RegisteredMom:
	.string "Καταχώρηση MOM\n"
	.string "στο POKéNAV.$"

PlayersHouse_1F_Text_Vigoroth1:
	.string "Φουγκιιιιιχ!$"

PlayersHouse_1F_Text_Vigoroth2:
	.string "Χαγκο, ουγκ, ουργκ...$"

PlayersHouse_1F_Text_ReportFromPetalburgGym:
	.string "ΔΗΜΟΣΙΟΓΡΑΦΟΣ: Σας μεταφέρουμε αυτό το\n"
	.string "ρεπορτάζ μπροστά από το PETALBURG GYM.$"

PlayersHouse_1F_Text_TheresAMovieOnTV:
	.string "Έχει μια ταινία στην τηλεόραση.\p"
	.string "Δύο άντρες χορεύουν σε \n"
	.string "ένα μεγάλο πιάνο.\p"
	.string "Καλύτερα να ξεκινάω!$"

PlayersHouse_1F_Text_RunningShoesManual:
	.string "Είναι το βιβλιαράκι οδηγιών για τα\n"
	.string "RUNNING SHOES.\p"
	.string "“Πάτα το κουμπί B για να τρέξεις\n"
	.string "φορώντας τα RUNNING SHOES σου.\p"
	.string "“Βάλε τα RUNNING SHOES σου \n"
	.string "και βγες να τρέξεις στον δρόμο!”$"

PlayersHouse_1F_Text_TicketFromBrineyCameForYou:
	.string "DAD: Χμ;\p"
	.string "Έι, είναι το {PLAYER}!\p"
	.string "Πάει καιρός από τότε \n"
	.string "που σε είδα, αλλά φαίνεσαι… \l"
	.string "πιο δυνατό, κάπως.\p"
	.string "Αυτή είναι η εντύπωση που έχω.\n"
	.string "Αλλά ο γέρος σου δεν έχει \l"
	.string "τα παρατήσει ακόμα!\p"
	.string "Α, ναι, έχω κάτι για σένα.\n"
	.string "Αυτό ήρθε για σένα από \l"
	.string "κάποιον που λέγεται MR. BRINEY.$"

PlayersHouse_1F_Text_PortsInSlateportLilycove:
	.string "DAD: Χμ, ένα TICKET για πλοίο;\p"
	.string "Αν θυμάμαι καλά, υπάρχουν λιμάνια\n"
	.string "στο SLATEPORT και στο LILYCOVE.$"

PlayersHouse_1F_Text_BetterGetBackToGym:
	.string "Θα ήταν καλύτερα να επιστρέψω\n"
	.string "στο PETALBURG GYM.\p"
	.string "MOM, ευχαριστώ που προσέχεις το σπίτι\n"
	.string "όσο λείπω.$"

PlayersHouse_1F_Text_DadShouldStayLonger:
	.string "MOM: Αυτός ο DAD σου…\p"
	.string "Έρχεται σπίτι για πρώτη φορά μετά από\n"
	.string "καιρό και μιλάει μόνο για POKéMON.\p"
	.string "Θα μπορούσε να χαλαρώσει \n"
	.string "και να μείνει λίγο ακόμα.$"

PlayersHouse_1F_Text_IsThatABreakingStory:
	.string "MOM: Είναι αυτή μια έκτακτη είδηση;$"

PlayersHouse_1F_Text_LatiEmergencyNewsFlash:
	.string "Σας φέρνουμε αυτό το\n"
	.string "έκτακτο δελτίο ειδήσεων!\p"
	.string "Σε διάφορες περιοχές της HOENN,\n"
	.string "υπάρχουν αναφορές για ένα POKéMON \l"
	.string "χρώματος ΜΠΖΖΤ… εν πτήσει.\p"
	.string "Η ταυτότητα αυτού του POKéMON είναι\n"
	.string "προς το παρόν άγνωστη.\p"
	.string "Επιστρέφουμε τώρα \n"
	.string "στο κανονικό \l"
	.string "πρόγραμμα ταινιών.$"

PlayersHouse_1F_Text_WhatColorDidTheySay:
	.string "MOM: {PLAYER}, το έπιασες αυτό;\p"
	.string "Τι χρώμα είπε ο εκφωνητής\n"
	.string "ότι ήταν αυτό το POKéMON;$"

PlayersHouse_1F_Text_StillUnknownPokemon:
	.string "MOM: Λοιπόν, δεν είναι \n"
	.string "κάτι το εξαιρετικό!\l"
	.string "Υπάρχουν ακόμα άγνωστα POKéMON.$"
