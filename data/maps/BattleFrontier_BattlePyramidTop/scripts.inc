.set LOCALID_ATTENDANT, 1
.set LOCALID_BRANDON, 2

BattleFrontier_BattlePyramidTop_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattlePyramidTop_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidTop_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePyramidTop_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePyramidTop_OnWarp
	.byte 0

BattleFrontier_BattlePyramidTop_OnTransition:
	pyramid_updatelight 200, PYRAMID_LIGHT_SET_RADIUS
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidTop_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePyramidTop_EventScript_SetUpObjects
	.2byte 0

BattleFrontier_BattlePyramidTop_EventScript_SetUpObjects::
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	goto_if_ne VAR_TEMP_C, 0, BattleFrontier_BattlePyramidTop_EventScript_EndSetUpObjects
	setobjectxyperm LOCALID_BRANDON, 0, 0
BattleFrontier_BattlePyramidTop_EventScript_EndSetUpObjects::
	end

BattleFrontier_BattlePyramidTop_OnResume:
	frontier_getbrainstatus
	goto_if_eq VAR_RESULT, FRONTIER_BRAIN_NOT_READY, BattleFrontier_BattlePyramidTop_EventScript_CheckChallengeStatus
	call BattleFrontier_EventScript_SetBrainObjectGfx
BattleFrontier_BattlePyramidTop_EventScript_CheckChallengeStatus::
	copyvar VAR_TEMP_C, VAR_RESULT
	frontier_getstatus
	switch VAR_TEMP_CHALLENGE_STATUS
	case 0, BattleFrontier_BattlePyramidTop_EventScript_ReadyChallenge
	case CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramid_EventScript_WarpToLobby
	case CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidTop_EventScript_ReadyChallenge
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
	goto_if_eq VAR_RESULT, B_OUTCOME_LOST, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	goto_if_eq VAR_RESULT, B_OUTCOME_DREW, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	goto_if_eq VAR_RESULT, B_OUTCOME_FORFEITED, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattlePyramidTop_OnFrame:
	map_script_2 VAR_TEMP_PLAYING_PYRAMID_MUSIC, 0, BattleFrontier_BattlePyramidTop_EventScript_PlayPyramidMusic
	map_script_2 VAR_TEMP_F, 1, BattleFrontier_BattlePyramidTop_EventScript_ShowMapName
	.2byte 0

BattleFrontier_BattlePyramidTop_EventScript_PlayPyramidMusic::
	playbgm MUS_B_PYRAMID_TOP, FALSE
	setvar VAR_TEMP_PLAYING_PYRAMID_MUSIC, 1
	end

BattleFrontier_BattlePyramidTop_EventScript_ShowMapName::
	special ShowMapNamePopup
	setvar VAR_TEMP_F, 0
	end

BattleFrontier_BattlePyramidTop_EventScript_ReadyChallenge::
	pyramid_save CHALLENGE_STATUS_SAVING
	special SavePlayerParty
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	pyramid_settrainers
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidTop_EventScript_Attendant::
	lock
	faceplayer
	goto_if_ne VAR_TEMP_D, 0, BattleFrontier_BattlePyramidTop_EventScript_StepForwardWhenReady
	goto_if_ne VAR_TEMP_C, FRONTIER_BRAIN_NOT_READY, BattleFrontier_BattlePyramidTop_EventScript_BrandonHereMoveAside
	msgbox BattleFrontier_BattlePyramidTop_Text_ReachedSummitUpYouGo, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePyramidTop_Movement_AttendantMoveAside
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePyramidTop_Movement_PlayerClimbToTop
	waitmovement 0
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePyramidTop_Movement_AttendantBlockPath
	waitmovement 0
	message BattleFrontier_BattlePyramidTop_Text_PlayerConqueredPyramid
	waitmessage
	playfanfare MUS_OBTAIN_B_POINTS
	waitfanfare
	closemessage
BattleFrontier_BattlePyramidTop_EventScript_WarpToLobbyWon::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_WON
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_LOBBY, 7, 13
	waitstate
	end

BattleFrontier_BattlePyramidTop_EventScript_StepForwardWhenReady::
	msgbox BattleFrontier_BattlePyramidTop_Text_StepForwardWhenReady, MSGBOX_DEFAULT
	closemessage
	end

BattleFrontier_BattlePyramidTop_EventScript_BrandonHereMoveAside::
	msgbox BattleFrontier_BattlePyramidTop_Text_ChiefBeatYouHere, MSGBOX_DEFAULT
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePyramidTop_Movement_AttendantMoveAside
	setvar VAR_TEMP_D, 1
	closemessage
	end

BattleFrontier_BattlePyramidTop_EventScript_BattleBrandon::
	lockall
	switch VAR_TEMP_C
	case FRONTIER_BRAIN_GOLD, BattleFrontier_BattlePyramidTop_EventScript_BrandonIntroGold
	case FRONTIER_BRAIN_STREAK, BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardSilverSpeech
	case FRONTIER_BRAIN_STREAK_LONG, BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardGoldSpeech
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardSilverSpeech
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, BattleFrontier_BattlePyramidTop_Movement_CameraPanUp
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidTop_Text_ExplorationsAreGrandestAdventure, MSGBOX_DEFAULT
	closemessage
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
	applymovement LOCALID_BRANDON, BattleFrontier_BattlePyramidTop_Movement_BrandonApproachPlayer
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidTop_Text_ImPyramidKingBrandon, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidTop_EventScript_BattleBrandonSilver
	end

BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardSilverSpeech::
	applymovement LOCALID_BRANDON, BattleFrontier_BattlePyramidTop_Movement_BrandonApproachPlayer
	waitmovement 0
BattleFrontier_BattlePyramidTop_EventScript_BattleBrandonSilver::
	msgbox BattleFrontier_BattlePyramidTop_Text_BringCourageToOurBattle, MSGBOX_DEFAULT
	call BattleFrontier_BattlePyramidTop_EventScript_DoBrandonBattle
	playbgm MUS_B_PYRAMID_TOP, FALSE
	goto_if_eq VAR_RESULT, 1, BattleFrontier_BattlePyramidTop_EventScript_DefeatedBrandonSilver
	goto BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost

BattleFrontier_BattlePyramidTop_EventScript_DefeatedBrandonSilver::
	frontier_getsymbols
	goto_if_ne VAR_RESULT, 0, BattleFrontier_BattlePyramidTop_EventScript_WarpToLobbyWon
	msgbox BattleFrontier_BattlePyramidTop_Text_BrandonFrontierPassPlease, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattlePyramidTop_Text_ReceivedBraveSymbol
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattlePyramidTop_Text_LookForwardToNextMeeting, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidTop_EventScript_WarpToLobbyWon

BattleFrontier_BattlePyramidTop_EventScript_BrandonIntroGold::
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardGoldSpeech
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, BattleFrontier_BattlePyramidTop_Movement_CameraPanUp
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidTop_Text_BrandonYouveReturned, MSGBOX_DEFAULT
	closemessage
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
	applymovement LOCALID_BRANDON, BattleFrontier_BattlePyramidTop_Movement_BrandonApproachPlayer
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidTop_Text_MyCourageIsOffMeter, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidTop_EventScript_BattleBrandonGold
	end

BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardGoldSpeech::
	applymovement LOCALID_BRANDON, BattleFrontier_BattlePyramidTop_Movement_BrandonApproachPlayer
	waitmovement 0
BattleFrontier_BattlePyramidTop_EventScript_BattleBrandonGold::
	msgbox BattleFrontier_BattlePyramidTop_Text_EverythingYouHave, MSGBOX_DEFAULT
	call BattleFrontier_BattlePyramidTop_EventScript_DoBrandonBattle
	playbgm MUS_B_PYRAMID_TOP, FALSE
	goto_if_eq VAR_RESULT, 1, BattleFrontier_BattlePyramidTop_EventScript_DefeatedBrandonGold
	goto BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost

BattleFrontier_BattlePyramidTop_EventScript_DefeatedBrandonGold::
	frontier_getsymbols
	goto_if_eq VAR_RESULT, 2, BattleFrontier_BattlePyramidTop_EventScript_WarpToLobbyWon
	msgbox BattleFrontier_BattlePyramidTop_Text_BrandonRemarkableHaveThis, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattlePyramidTop_Text_BraveSymbolTookGoldenShine
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattlePyramidTop_Text_FarewellForNow, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidTop_EventScript_WarpToLobbyWon

BattleFrontier_BattlePyramidTop_EventScript_DoBrandonBattle::
	closemessage
	setvar VAR_0x8004, SPECIAL_BATTLE_PYRAMID
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	return

BattleFrontier_BattlePyramidTop_Movement_AttendantMoveAside:
	walk_right
	walk_in_place_faster_left
	step_end

BattleFrontier_BattlePyramidTop_Movement_AttendantBlockPath:
	walk_left
	walk_in_place_faster_up
	step_end

BattleFrontier_BattlePyramidTop_Movement_PlayerClimbToTop:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

BattleFrontier_BattlePyramidTop_Movement_BrandonApproachPlayer:
	walk_fast_down
	step_end

BattleFrontier_BattlePyramidTop_Movement_CameraPanUp:
	walk_slow_up
	walk_slow_up
	delay_16
	step_end

BattleFrontier_BattlePyramidTop_Text_ReachedSummitUpYouGo:
	.string "Είναι χαρά μου που σε βλέπω εδώ!\n"
	.string "Mόλις έφτασες στην κορυφή του\l"
	.string "BATTLE PYRAMID!\p"
	.string "Από πάνω είναι το σημείο παρατήρησης\n"
	.string "της PYRAMID.\p"
	.string "Είναι ένα μέρος ανοιχτό μόνο σε όσους\n"
	.string "έχουν κατακτήσει την PYRAMID.\p"
	.string "Τώρα, σε παρακαλώ!\n"
	.string "Ανέβα επάνω!$"

BattleFrontier_BattlePyramidTop_Text_PlayerConqueredPyramid:
	.string "Tο νέο άτομο που κατέκτησε την PYRAMID!\n"
	.string "Ας γίνει γνωστό το όνομα {PLAYER}!$"

BattleFrontier_BattlePyramidTop_Text_ChiefBeatYouHere:
	.string "Είναι χαρά μου που σε βλέπω εδώ!\p"
	.string "Δυστυχώς, ήρθες δεύτερη θέση για\n"
	.string "ένα κλάσμα του δευτερολέπτου!\p"
	.string "Ο chief μας έχει ήδη κατακτήσει την\n"
	.string "PYRAMID πριν από εσένα.\p"
	.string "Όμως, εξερευνητή μου...\n"
	.string "Είσαι ένα TRAINER άτομο!\p"
	.string "Δείξε τη δύναμή σου και πάρε τη δόξα\n"
	.string "της κορυφής από τον chief μας!\p"
	.string "Τώρα, σε παρακαλώ! Μόλις ετοιμαστείς,\n"
	.string "κάνε ένα ακόμα θαρραλέο βήμα!$"

BattleFrontier_BattlePyramidTop_Text_ExplorationsAreGrandestAdventure:
	.string "Νεαρέ μου εξερευνητή…\p"
	.string "Δεν θα συμφωνούσες ότι οι εξερευνήσεις\n"
	.string "είναι οι πιο σπουδαίες περιπέτειες;\p"
	.string "Το δικό σου μυαλό!\p"
	.string "Η δική σου δύναμη!\p"
	.string "Τα δικά σου POKéMON!\p"
	.string "Και πάνω απ' όλα, μόνο το θάρρος σου να\n"
	.string "σε οδηγεί μέσα από άγνωστους κόσμους…$"

BattleFrontier_BattlePyramidTop_Text_ImPyramidKingBrandon:
	.string "Ααχ, ναι, πράγματι αυτή η ζωή είναι\n"
	.string "υπέροχη! Υπέροχη, έτσι;\p"
	.string "Είμαι ο BRANDON!\p"
	.string "Είμαι ο PYRAMID KING, πράγμα που\n"
	.string "σημαίνει ότι εγώ κάνω κουμάντο εδώ.\p"
	.string "Οι περισσότεροι με λένε chief!\p"
	.string "Το ότι ήρθες εδώ, σημαίνει ότι έχεις\n"
	.string "πολλή αυτοπεποίθηση,\l"
	.string "έχω δίκιο;\p"
	.string "Χαχαχαχ!\n"
	.string "Αυτό θα είναι συναρπαστικό!$"

BattleFrontier_BattlePyramidTop_Text_BringCourageToOurBattle:
	.string "Λοιπόν, τώρα!\n"
	.string "Φέρε το θάρρος σου στη μάχη μας!$"

BattleFrontier_BattlePyramidTop_Text_BrandonFrontierPassPlease:
	.string "BRANDON: Χαχαχαχ! Ήταν υπέροχο!\n"
	.string "Υπέροχο, ναι, πράγματι!\p"
	.string "Μπράβο! Κέρδισες την αναγνώριση!\n"
	.string "Το FRONTIER PASS σου, παρακαλώ!$"

BattleFrontier_BattlePyramidTop_Text_ReceivedBraveSymbol:
	.string "Το Brave Symbol αποτυπώθηκε πάνω\n"
	.string "στο FRONTIER PASS!$"

BattleFrontier_BattlePyramidTop_Text_LookForwardToNextMeeting:
	.string "Έμπειρο εξερευνητικό άτομο!\n"
	.string "Ανυπομονώ για την επόμενη συνάντηση!$"

BattleFrontier_BattlePyramidTop_Text_BrandonYouveReturned:
	.string "BRANDON: …Επιτέλους επέστρεψες,\n"
	.string "νεαρέ μου εξερευνητή…\p"
	.string "H αγάπη σου για την περιπέτεια πηγάζει\n"
	.string "βαθιά από την καρδιά σου…\p"
	.string "Ναι… Είσαι ακριβώς όπως ήμουν\n"
	.string "κι εγώ στα νιάτα μου…\p"
	.string "… … …Αα…\p"
	.string "Οι παθιασμένες!\p"
	.string "Οι επικίνδυνες!\p"
	.string "Οι απελπισμένες!\p"
	.string "Εκείνες οι μέρες των περιπετειών\n"
	.string "που αψηφούν τον θάνατο, επέστρεψαν…$"

BattleFrontier_BattlePyramidTop_Text_MyCourageIsOffMeter:
	.string "Τώρα λοιπόν!\p"
	.string "Νιώθω ότι το δικό μου θάρρος\n"
	.string "έχει ξεφύγει!$"

BattleFrontier_BattlePyramidTop_Text_EverythingYouHave:
	.string "Δώσε όσα έχεις!\n"
	.string "Είμαι προετοιμασμένος για όλα!$"

BattleFrontier_BattlePyramidTop_Text_BrandonRemarkableHaveThis:
	.string "BRANDON: Χαχαχαχ!\n"
	.string "Αξιοσημείωτο!\l"
	.string "Ναι, είναι υπέροχο, πράγματι!\p"
	.string "Ατρόμητο εξερευνητικό άτομο!\p"
	.string "Με νίκησες κατά κράτος!\n"
	.string "Ορίστε! Θέλω να το πάρεις αυτό!$"

BattleFrontier_BattlePyramidTop_Text_BraveSymbolTookGoldenShine:
	.string "Το Brave Symbol πήρε μια\n"
	.string "χρυσή λάμψη!$"

BattleFrontier_BattlePyramidTop_Text_FarewellForNow:
	.string "Α, ναι! Αυτό δείχνει απλώς ότι\n"
	.string "έχω ακόμα πολλά να μάθω!\p"
	.string "Μακάρι να συναντηθούμε ξανά!\n"
	.string "Αντίο προς το παρόν, explorer!$"

BattleFrontier_BattlePyramidTop_Text_StepForwardWhenReady:
	.string "Τώρα, όταν ετοιμαστείς, πάρε θάρρος\n"
	.string "και κάνε ένα βήμα μπροστά.$"

