.set LOCALID_ATTENDANT, 1

BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleTowerMultiPartnerRoom_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame
	.byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_OnResume:
	pyramid_resetparty
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition:
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_1
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_2
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_3
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_4
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_5
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_6
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_1
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_2
	tower_loadpartners
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_3, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_4, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_5, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_6, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_7, OBJ_EVENT_GFX_BOY_1
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_3, 1
	setobjectxyperm LOCALID_ATTENDANT, 10, 2
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp:
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom::
	lockall
	setvar VAR_TEMP_3, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom
	waitmovement 0
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit
	waitmovement 0
	copyobjectxytoperm LOCALID_ATTENDANT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner, MSGBOX_DEFAULT
	special HealPlayerParty
	setvar VAR_TEMP_1, 1
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom:
	walk_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit:
	walk_left
	walk_in_place_faster_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Attendant::
	lock
	faceplayer
	message BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge::
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator::
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 10, 1
	waitdooranim
	call BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator
	closedoor 10, 1
	waitdooranim
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_ELEVATOR, 1, 6
	waitstate
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator::
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorEast:
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorWest:
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator:
	walk_up
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast:
	walk_right
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest:
	walk_left
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner1::
	lock
	faceplayer
	setvar VAR_TEMP_2, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner::
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_INTRO
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON1
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON2_ASK
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_ACCEPT
	waitmessage
	waitbuttonpress
	closemessage
	call_if_ne VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth
	removeobject VAR_LAST_TALKED
	setflag FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_TOWER_MULTI_PARTNER_ROOM, 10, 3
	waitstate
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner::
	tower_dopartnermsg PARTNER_MSGID_REJECT
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner2::
	lock
	faceplayer
	setvar VAR_TEMP_2, 1
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner3::
	lock
	faceplayer
	setvar VAR_TEMP_2, 2
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner4::
	lock
	faceplayer
	setvar VAR_TEMP_2, 3
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner5::
	lock
	faceplayer
	setvar VAR_TEMP_2, 4
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner6::
	lock
	faceplayer
	setvar VAR_TEMP_2, 5
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner7::
	lock
	faceplayer
	setvar VAR_TEMP_2, 6
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner8::
	lock
	faceplayer
	setvar VAR_TEMP_2, 7
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner:
	.string "Σε παρακαλώ, βρες ένα άτομο από όσους \n"
	.string "TRAINERS έχουν συγκεντρωθεί εδώ.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner:
	.string "{PLAYER}, δεν έχεις βρει κάποιο άτομο\n"
	.string "για να γίνεται ζευγάρι.\p"
	.string "Θα ήθελες να σταματήσεις το ψάξιμο και\n"
	.string "να επιστρέψεις στο γκισέ υποδοχής;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2:
	.string "Τότε, σε παρακαλώ, βρες ένα άτομο \n"
	.string "από όσους TRAINERS βρίσκονται εδώ.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner::
	.string "Ευχαριστούμε για την επιλογή σου.\p"
	.string "Τώρα θα σε οδηγήσω στο MULTΙ\n"
	.string "BATTLE ROOM σου.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Intro::
	.string "Είμαι ο μαθητευόμενος ν. {STR_VAR_2} του\n"
	.string "ατόμου {STR_VAR_1}. Με λένε {STR_VAR_3}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon1::
	.string "Με τη συμβουλή του {STR_VAR_1}, έφερα\n"
	.string "ένα {STR_VAR_3} με {STR_VAR_2} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Παρακαλώ, άφησέ με να γίνουμε ομάδα.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Accept::
	.string "Ευχαριστώ!\n"
	.string "Πάω να κάνω εγγραφή αμέσως.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Reject::
	.string "Πραγματικά ήθελα να γίνουμε ομάδα,\n"
	.string "{PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Intro::
	.string "Είμαι η μαθητευόμενη ν. {STR_VAR_2} του\n"
	.string "ατόμου {STR_VAR_1}. Με λένε {STR_VAR_3}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon1::
	.string "Πήρα συμβουλή από {STR_VAR_1} κι επέλεξα\n"
	.string "ένα {STR_VAR_3} με {STR_VAR_2} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Σε παρακαλώ, ας φτιάξουμε ομάδα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Accept::
	.string "Ευχαριστώ πάρα πολύ!\n"
	.string "Θα τελειώσω με την εγγραφή σύντομα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Reject::
	.string "{PLAYER}, ήλπιζα ότι θα μπορούσα\n"
	.string "να γίνω ομάδα μαζί σου…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Intro::
	.string "Εμ, το όνομά μου είναι {STR_VAR_3}, κι είμαι\n"
	.string "το μαθητευόμενο ν. {STR_VAR_2} του {STR_VAR_1}.\p"
	.string "Σνιφ…\p"
	.string "Συγγνώμη!\n"
	.string "Αυτή η ένταση με κάνει να κλαίω…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon1::
	.string "Το {STR_VAR_3} με συμβούλεψε, κι έχω\n"
	.string "ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Σνιφ…\n"
	.string "Σε παρακαλώ, γίνε ομάδα μαζί μου!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Accept::
	.string "Ω, αλήθεια; Θα γίνεις;\n"
	.string "Τέλεια! Φοβερά! Ουάου!\p"
	.string "Ω... συγγνώμη...\n"
	.string "Χαίρομαι τόσο πολύ, κλαίω...\p"
	.string "Πάω να κάνω εγγραφή αμέσως.\n"
	.string "Σε παρακαλώ μην φύγεις!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Reject::
	.string "Ω, μ-μα…\n"
	.string "Σνιφ… Ουάααα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Intro::
	.string "Γεια σου! Είμαι {STR_VAR_3}!\n"
	.string "Είμαι το μαθητευόμενο ν. {STR_VAR_2} του {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon1::
	.string "Το {STR_VAR_3} πρότεινε την ομάδα μου.\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1},\n"
	.string "αυτά έχω! Τέλειο, ε;\p"
	.string "Οπότε έλα!\n"
	.string "Ας γίνουμε ομάδα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Accept::
	.string "Γιούπι! Τέλεια!\n"
	.string "Εντάξει, πάω να κάνω εγγραφή, εντάξει;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Reject::
	.string "Αχ, γιατί;\n"
	.string "Ήθελα να γίνουμε ομάδα, {PLAYER}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Intro::
	.string "Είμαι {STR_VAR_3}, το μαθητευόμενο ν. {STR_VAR_2}\n"
	.string "του διάσημου ατόμου {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon1::
	.string "Ζήτησα συμβουλή από {STR_VAR_3}.\n"
	.string "Ένα {STR_VAR_2} με χρήση {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon2Ask::
	.string "και ένα {STR_VAR_2} με {STR_VAR_1},\n"
	.string "αυτά έχω!\p"
	.string "Σε παρακαλώ, μπορούμε να\n"
	.string "γίνουμε ομάδα;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Accept::
	.string "Ευχαριστώ!\n"
	.string "Πάω να κάνω εγγραφή αμέσως!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Reject::
	.string "{PLAYER}, ήλπιζα να γίνουμε\n"
	.string "ομάδα…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Intro::
	.string "Εμ… Χαίρομαι ειλικρινά που\n"
	.string "έχεις τον χρόνο να μου μιλήσεις.\p"
	.string "Είμαι {STR_VAR_3}.\n"
	.string "Το μαθητευόμενο ν. {STR_VAR_2} του {STR_VAR_1}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon1::
	.string "Το {STR_VAR_3} μου έδωσε μια συμβουλή.\n"
	.string "Είμαι πολύ ευγνώμων γι' αυτήν.\p"
	.string "Έχω μια ομάδα από ένα {STR_VAR_2}\n"
	.string "με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\n"
	.string "Ξέρω ότι ζητάω πολλά…\p"
	.string "Δεν νομίζω να θέλεις, αλλά\n"
	.string "μπορώ να γίνω ομάδα μαζί σου;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Accept::
	.string "Αλήθεια; Δεν το πιστεύω!\n"
	.string "Δεν πιστεύω ότι με δέχεσαι!\l"
	.string "Εγώ... Δεν θα σε απογοητεύσω!\p"
	.string "Εμ... Ανόντως συμφωνείς, πάω \n"
	.string "να κάνω εγγραφή τώρα αμέσως!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Reject::
	.string "Ω…\n"
	.string "Δεν πίστευα ότι ήμουν αρκετά καλό…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Intro::
	.string "Γεια, είμαι {STR_VAR_3}.\n"
	.string "Το μαθητευόμενο ν. {STR_VAR_2} του {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon1::
	.string "Το {STR_VAR_3} είπε ότι είναι καλό να\n"
	.string "έχεις αυτή την ομάδα:\l"
	.string "ένα {STR_VAR_2} με χρήση {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon2Ask::
	.string "και ένα {STR_VAR_2} που ξέρει πώς\n"
	.string "να χρησιμοποιήσει {STR_VAR_1}.\p"
	.string "Δεν είναι κακό, σωστά;\n"
	.string "Θέλεις να γίνουμε ομάδα;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Accept::
	.string "Εντάξει, χαίρομαι που σε συνοδεύω!\n"
	.string "Ελπίζω να μην μου τα χαλάσεις!\l"
	.string "Πάω να κάνω εγγραφή τώρα.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Reject::
	.string "Ε; Γιατί με απέρριψας;\n"
	.string "Δεν ξέρεις να κρίνεις χαρακτήρες!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Intro::
	.string "Είμαι {STR_VAR_3} κι είμαι ΤΡΙΑΘΛΗΤΗΣ.\n"
	.string "Είμαι απασχολημένος κάθε μέρα με\l"
	.string "τζόκινγκ, προπόνηση και ραπ.\p"
	.string "Επίσης, είμαι ο μαθητευόμενος\n"
	.string "ν. {STR_VAR_2} της {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon1::
	.string "Αυτά μου πρότεινε το {STR_VAR_3}.\n"
	.string "Ένα {STR_VAR_2} με χρήση {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon2Ask::
	.string "και ένα {STR_VAR_2} με\n"
	.string "χρήση {STR_VAR_1}.\p"
	.string "Έκανα προσπάθεια να τα μεγαλώσω,\n"
	.string "παρόλο που είμαι πολυάσχολος.\p"
	.string "Ας γίνουμε ομάδα και πάμε\n"
	.string "να προσπαθήσουμε!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Accept::
	.string "Ευχαριστώ, αυτό είναι το πνεύμα!\n"
	.string "Μείνε εδώ καθώς πάω να κάνω εγγραφή, οκ;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Reject::
	.string "Βρήκα χρόνο από το πρόγραμμά μου\n"
	.string "για να είμαι εδώ! Κάνε μου τη χάρη!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Intro::
	.string "Γεια!\n"
	.string "Τι κάνουμε;\p"
	.string "Είμαι {STR_VAR_3}, το μαθητευόμενο\n"
	.string "ν. {STR_VAR_2} του ατόμου {STR_VAR_1}. Χάρηκα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon1::
	.string "Άκου, άκου! Πρέπει να ακούσεις για το\n"
	.string "POKéMON που πρότεινε το {STR_VAR_3}.\l"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\n"
	.string "Φυσικά τα μεγάλωσα τέλεια!\p"
	.string "Λοιπόν, θέλεις να γίνουμε ομάδα;\n"
	.string "Είμαι σίγουρο ότι θα είναι απίστευτο!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Accept::
	.string "Γιούπι, νομίζω θα έχει πλάκα!\n"
	.string "Θα πάω να κάνω εγγραφή!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Reject::
	.string "Αχ, είσαι κακό άτομο!\n"
	.string "Με έχουν προτείνει, να ξέρεις.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Intro::
	.string "Σε παρακαλώ, ας συστηθώ.\n"
	.string "Είμαι το {STR_VAR_3}.\p"
	.string "Είμαι το μαθητευόμενο ν. {STR_VAR_2}\n"
	.string "του ατόμου {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon1::
	.string "Αναζήτησα τη σοφή συμβουλή του\n"
	.string "{STR_VAR_3} και μεγάλωσα την ομάδα\l"
	.string "μου με ένα {STR_VAR_2} με {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon2Ask::
	.string "κι ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Παρακαλώ δέξου να γίνουμε ομάδα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Accept::
	.string "Ω… Είμαι χαρούμενο!\n"
	.string "Υπόσχομαι να βάλω τα δυνατά μου!\p"
	.string "Φυσικά θα κάνω την εγγραφή!\n"
	.string "Σε παρακαλώ περίμενε!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Reject::
	.string "Ήλπιζα να γίνω ομάδα μαζί σου,\n"
	.string "{PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Intro::
	.string "Αχ! Μου μίλησες!\n"
	.string "Ε... Είμαι πανευτυχές!\p"
	.string "Είμαι το {STR_VAR_3}! Είμαι το μαθητευόμενο\n"
	.string "ν. {STR_VAR_2} του {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon1::
	.string "Με τη συμβουλή του {STR_VAR_3}, εκπαίδευσα\n"
	.string "ένα {STR_VAR_2} με {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon2Ask::
	.string "και ένα {STR_VAR_2} με χρήση\n"
	.string "{STR_VAR_1}.\p"
	.string "Παρακαλώ, μπορείς να μου κάνεις τη χάρη;\n"
	.string "Θέλω να είμαι το ζευγάρι σου!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Accept::
	.string "A! Νιώθω ζαλάδα!\n"
	.string "Σε ευχαριστώ πάρα πολύ!\l"
	.string "Θα πάω να μας κάνω εγγραφή αμέσως!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Reject::
	.string "Ουάα! Δεν με λυπάσαι καθόλου;\n"
	.string "Αλλά αυτό σε κάνει πιο κουλ ταυτόχρονα…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Intro::
	.string "Γιούχου! Είμαι το μαθητευόμενο ν. {STR_VAR_2}\n"
	.string "του ατόμου {STR_VAR_1}!\p"
	.string "{STR_VAR_3} είναι το όνομά μου, γεια, γεια!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon1::
	.string "Το άτομο μέντοράς μου {STR_VAR_3} πρότεινε\n"
	.string "ένα μάστερ από το είδος {STR_VAR_2}\l"
	.string "με τη χρήση του {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon2Ask::
	.string "και ένα {STR_VAR_2} μάστερ στη χρήση\n"
	.string "{STR_VAR_1}.\p"
	.string "Καλό περιεχόμενο, ε;\n"
	.string "Θα γίνεις ομάδα μαζί μου, έτσι δεν είναι;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Accept::
	.string "Εντάξει, τέλεια!\n"
	.string "Θα κάνω την εγγραφή γρήγορα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Reject::
	.string "Γκάααα!\n"
	.string "Είσαι ένα υπολογιστικό άτομο, {PLAYER}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Intro::
	.string "Έι! Υπάρχει μεγάλο πρόβλημα! Αυτή είναι\n"
	.string "η τελευταία μέρα του BATTLE TOWER!\p"
	.string "… … … … … …\n"
	.string "Απλώς κάνω πλάκα!\p"
	.string "Ο κόσμος με λέει {STR_VAR_3} κι εγώ το ίδιο!\n"
	.string "Είμαι το 1000ό μαθητευόμενο του {STR_VAR_1}!\l"
	.string "Βασικά, είμαι το ν. {STR_VAR_2}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon1::
	.string "Το {STR_VAR_3} μου έδωσε μια συμβουλή.\n"
	.string "{STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon2Ask::
	.string "{STR_VAR_2} με {STR_VAR_1}.\n"
	.string "Έχω δέκα από το κάθε είδος!\l"
	.string "Βέβαια, έχω μόνο ένα από το καθένα!\p"
	.string "Λοιπόν;\n"
	.string "Θες να δοκιμάσουμε tag battles;$ "

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Accept::
	.string "Γιούπι!\n"
	.string "Θα σου δώσω ένα POKéMON ως \n"
	.string "ευχαριστώ!\p"
	.string "Πλάκα κάνω! Αλλά θα πάω κυριολεκτικά\n"
	.string "να κάνω την εγγραφή, εντάξει;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Reject::
	.string "Ω, αυτό είναι τόσο κρύο! θα\n"
	.string "πρέπει να καταστρέψω το BATTLE TOWER!\p"
	.string "Φυσικά και δεν θα το κάνω! $"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Intro::
	.string "Εεε, χορεύω και τραγουδώ!\n"
	.string "Τα POKéMON καθοδηγώ!\p"
	.string "Είμαι ο ράπερ ναύτης, {STR_VAR_3}.\n"
	.string "Μη με περνάς για κανένα ψευτοκαλλιτέχνη!\p"
	.string "Είμαι ο μαθητευόμενος ν. {STR_VAR_2} του\n"
	.string "{STR_VAR_1}. Μη με υποτιμάς κι εσύ!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon1::
	.string "Με τη συμβουλή του {STR_VAR_3}\n"
	.string "έφτιαξα την ομάδα της περηφάνιας μου!\l"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon2Ask::
	.string "κι ένα {STR_VAR_2}\n"
	.string "με {STR_VAR_1}!\p"
	.string "Αυτή τη συνάντηση πρέπει να τιμήσουμε,\n"
	.string "με μια νίκη tag-team να πανηγυρίσουμε!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Accept::
	.string "Ε, ε, μου αρέσει το στιλ σου!\n"
	.string "Την εγγραφή μας, εγώ θα κανονίσω!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Reject::
	.string "Ω, {PLAYER}, αυτόν ήταν \n"
	.string "παγωμένο, τόσο ειρωνικό!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Intro::
	.string "Γιούπι-γιαχου!\n"
	.string "Ω, μην τρέχεις! Απλώς διασκέδαζα!\p"
	.string "Γεια! Είμαι {STR_VAR_3}!\n"
	.string "Είμαι το μαθητευόμενο ν. {STR_VAR_2} του {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon1::
	.string "Το {STR_VAR_3} μου είπε τι να κάνω.\n"
	.string "Έτσι ένα {STR_VAR_2} με {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon2Ask::
	.string "και ένα {STR_VAR_2} με {STR_VAR_1},\n"
	.string "δηλαδή τα επέλεξα.\p"
	.string "Λοιπόν, τι λες;\n"
	.string "Έλα, φτιάξε μου τη μέρα!\p"
	.string "Σε ικετεύω!\n"
	.string "Άσε με να είμαι μαζί σου, μην αρνείσαι!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Accept::
	.string "Ναι! Η τύχη είναι με το μέρος μου!\n"
	.string "Αυτό με κάνει πολύ χαρούμενο άτομο!\p"
	.string "Πριν πάμε στη μάχη, θα\n"
	.string "πάω να κάνω εγγραφή αμέσως!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Reject::
	.string "Με απορρίπτεις;\n"
	.string "{PLAYER}, με στεναχωρείς!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Intro::
	.string "Γκουχ!\p"
	.string "Ω, συγγνώμη, είμαι κρυωμένο άτομο.\n"
	.string "Όμως τα POKéMON μου είναι καλά.\p"
	.string "Το όνομά μου είναι {STR_VAR_3}, το μαθητευόμενο\n"
	.string "ν. {STR_VAR_2} του {STR_VAR_1}. Γκουχ!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon1::
	.string "Πήρα τη συμβουλή του {STR_VAR_3} \n"
	.string "και συγκέντρωσα την ομάδα μου\l"
	.string "από ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Δούλεψαν μαζί μου κάθε μέρα,\n"
	.string "ακόμη και στη βροχή και τον αέρα.\p"
	.string "Γι' αυτό είμαι κρυωμένο άτομο, νομίζω.\p"
	.string "Έτσι είμαι εγώ.\n"
	.string "Θέλεις να είσαι το ζευγάρι μου;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Accept::
	.string "Σε ευχαριστώ, το εκτιμώ πολύ!\n"
	.string "Γκουχ, γκουχ!\l"
	.string "Περίμενε όσο πάω να κάνω εγγραφή.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Reject::
	.string "Ω, δεν το θες;\n"
	.string "{PLAYER}, νομίζω θα κάναμε καλό ζευγάρι.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Intro::
	.string "Ω, γεια!\n"
	.string "Αυτό είναι εξουθενωτικό.\p"
	.string "Είμαι {STR_VAR_3}.\n"
	.string "Είμαι το μαθητευόμενο ν. {STR_VAR_2} του {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon1::
	.string "Το {STR_VAR_3} είπε ότι αυτή η ομάδα είναι καλή-\n"
	.string "ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Νιώθω λίγο αμήχανα γι' αυτό,\n"
	.string "αλλά θα με αφήσεις να είμαι μαζί σου;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Accept::
	.string "Ωωο, σε ευχαριστώ!\n"
	.string "Νιώθω ντροπή, αλλά θα κάνω ό,τι μπορώ!\p"
	.string "Θα πάω να κάνω την εγγραφή.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Reject::
	.string "Σε παρακαλώ, μην πεις όχι!\n"
	.string "Νιώθω ήδη αρκετή αμηχανία...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Intro::
	.string "Είμαι {STR_VAR_3}, κι αυτό δεν είναι ψέμα.\n"
	.string "Είμαι μαθητευόμενο ν. {STR_VAR_2} του {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon1::
	.string "Το {STR_VAR_3} πρότεινε την ομάδα μου.\p"
	.string "Επειδή η συμβουλή φαινόταν ειλικρινής,\n"
	.string "αποφάσισα να φέρω μαζί μου\l"
	.string "ένα {STR_VAR_2} με χρήση {STR_VAR_1} κι$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon2Ask::
	.string "ένα {STR_VAR_2} με χρήση {STR_VAR_1}.\p"
	.string "Αν είναι δυνατόν, θα ήθελα να με \n"
	.string "δεχτείς ως ζευγάρι σου.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Accept::
	.string "Αλήθεια θα με δεχτείς;\n"
	.string "Θα ήταν πολύ άσχημο διαφορετικά.\p"
	.string "Αλλά αφού συμφώνησες, όλα καλά.\n"
	.string "Θα πάω να μας εγγράψω και τα δύο.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Reject::
	.string "Χμ; Τώρα γιατί να αρνιόσουν;\n"
	.string "Μήπως είναι κάποιου είδους αστείο;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassIntro::
	.string "Είμαι {STR_VAR_1}, κι είμαι LASS!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon1::
	.string "Αυτά που έχω είναι ένα {STR_VAR_2}\n"
	.string "που χρησιμοποιεί {STR_VAR_1} και ένα$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon2Ask::
	.string "{STR_VAR_2} που χρησιμοποιεί {STR_VAR_1}.\n"
	.string "Αυτά τα πλάσματα έχω μαζί μου.\p"
	.string "Θα είσαι το ζευγάρι μου;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassAccept::
	.string "Σε ευχαριστώ!\n"
	.string "Θα πάω να κάνω την εγγραφή!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassReject::
	.string "Δεν θέλεις να είσαι το ζευγάρι μου;\n"
	.string "Θα το μετανιώσεις αργότερα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterIntro::
	.string "Γεια σας!\p"
	.string "Είμαι YOUNGSTER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon1::
	.string "Θες να μάθεις τι έχω;\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} κι$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Θα είσαι το ζευγάρι μου σε\n"
	.string "tag-team, ε;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterAccept::
	.string "Γιούπι!\n"
	.string "Πάω να κάνω εγγραφή, εντάξει;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterReject::
	.string "Αχ! Αν φτιάχναμε ομάδα με\n"
	.string "τα POKéMON μου, δεν θα χάναμε!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerIntro:
	.string "Γιούχου!\n"
	.string "Είμαι HIKER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon1::
	.string "Ξέρεις τι έχω μαζί μου;\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Καλό ακούγεται, ε;\n"
	.string "Θες να φτιάξουμε ένα tag team;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerAccept::
	.string "Γιούχου!\n"
	.string "Θα πάω να κάνω την εγγραφή τότε.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerReject::
	.string "Θα μου άρεσε να σε έχω στο \n"
	.string "πλευρό μου.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyIntro::
	.string "Γεια σας!\n"
	.string "Είμαι {STR_VAR_1}, κι είμαι BEAUTY!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon1::
	.string "Ξέρεις τι μεγαλώνω;\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Τι λες;\n"
	.string "Θέλεις να φτιάξουμε tag team μαζί;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyAccept::
	.string "Υπέροχα!\n"
	.string "Θα ολοκληρώσω την εγγραφή τώρα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyReject::
	.string "Τι απογοητευτικό!\p"
	.string "Εμείς τα δύο μαζί--θα ήμασταν\n"
	.string "η κορυφαία ομάδα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanIntro::
	.string "Γιο!\p"
	.string "Ξέρεις ποιο άτομο είμαι;\n"
	.string "Είμαι {STR_VAR_1} το FISHERMAN!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon1::
	.string "Έχω μαζί μου μια ομάδα από ένα\n"
	.string "{STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Λοιπόν, τι λες;\n"
	.string "Θα πολεμήσεις στο πλευρό μου;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanAccept::
	.string "Καλά, καλά!\n"
	.string "Άστο πάνω μου!\p"
	.string "Θα πάω να μας κάνω εγγραφή τώρα.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanReject::
	.string "Ταιριάζαμε περίφημα, κιόλας…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyIntro::
	.string "Χαίρομαι για τη γνωριμία μας.\n"
	.string "Είμαι {STR_VAR_1}, ένα LADY.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon1::
	.string "Συνοδεύομαι από μια ομάδα με ένα\n"
	.string "{STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Ελπίζω να έχω την έγκρισή σου.\n"
	.string "Διότι επιθυμώ να γίνουμε ομάδα.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyAccept::
	.string "Σε ευχαριστώ ειλικρινά.\n"
	.string "Εγώ θα κανονίσω την εγγραφή.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyReject::
	.string "Είμαι βέβαιο πως θα μετανιώσεις \n"
	.string "που δε με δέχτηκες για ομάδα.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFIntro::
	.string "Είμαι TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon1::
	.string "Αυτά που έχω…\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\n"
	.string "Αυτό είναι το ζευγάρι μου!\p"
	.string "Σε παρακαλώ;\n"
	.string "Θα φτιάξεις tag team μαζί μου;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFAccept::
	.string "Ω, ευχαριστώ!\n"
	.string "Θα πάω να κάνω εγγραφή στο γκισέ.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFReject::
	.string "Εμείς τα δύο μαζί, θα ήμασταν\n"
	.string "σίγουρα σκληρό καρύδι να μας νικήσουν!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherIntro::
	.string "Γεια σας!\n"
	.string "Είμαι BUG CATCHER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon1::
	.string "Κοίτα να δεις τι έχω!\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Λοιπόν, άκου!\n"
	.string "Θέλεις να φτιάξουμε ένα tag team;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherAccept::
	.string "Σε τσάκωσα!\p"
	.string "Θα πάω να κάνω τα χαρτιά\n"
	.string "της εγγραφής στο γκισέ.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherReject::
	.string "Αχ, τα POKéMON μου είναι τέλεια.\n"
	.string "Ελπίζω να μην το μετανιώσεις αυτό!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMIntro::
	.string "Καλημέρα!\n"
	.string "Είμαι SCHOOL KID {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon1::
	.string "Αυτά που φρόντιζα είναι ένα\n"
	.string "{STR_VAR_2} με {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon2Ask::
	.string "κι ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Όχι κι άσχημα, δεν νομίζεις;\n"
	.string "Θα ήθελες να φτιάξουμε ένα tag team;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMAccept::
	.string "Ευχαριστώ πάρα πολύ!\n"
	.string "Θα τελειώσω με την εγγραφή.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMReject::
	.string "Κρίμα…\p"
	.string "Ήλπιζα ότι θα μπορούσα να μάθω\n"
	.string "από σένα ως ζευγάρι σου…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyIntro::
	.string "Γιο! Άσε με να σου πω ποιο άτομο είμαι!\n"
	.string "Είμαι το RICH BOY {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon1::
	.string "Μάντεψε τι έχω!\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Είμαι πρόθυμο να σου προσφέρω την \n"
	.string "ευκαιρία να κάνεις ομάδα μαζί μου.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyAccept::
	.string "Έξυπνη κίνηση!\p"
	.string "Θα τελειώσω τη διαδικασία\n"
	.string "εγγραφής γρήγορα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyReject::
	.string "Θα απέρριπτες εμένα απ' όλα τα άτομα;\n"
	.string "Θα μετανιώσεις για αυτή την απόφαση!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltIntro::
	.string "Χίγια!\n"
	.string "Είμαι BLACK BELT {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon1::
	.string "Ως συνοδούς μου, έχω\n"
	.string "ένα {STR_VAR_2} με {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon2Ask::
	.string "κι ένα {STR_VAR_2} με\n"
	.string "{STR_VAR_1}.\p"
	.string "Σε παρακαλώ, κάνε μου τη χάρη!\n"
	.string "Επίτρεψέ μου να γίνω ζευγάρι σου!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltAccept::
	.string "Χίγια!\n"
	.string "Θα πάω να κάνω εγγραφή αμέσως!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltReject::
	.string "Καταλαβαίνω… Ελπίζω σε μια \n"
	.string "ευκαιρία την επόμενη φορά…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFIntro::
	.string "Γεια!\n"
	.string "Είμαι {STR_VAR_1}, κι είμαι TUBER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon1::
	.string "Θα σου πω τι έχω.\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\n"
	.string "Μπορώ σε παρακαλώ να είμαι στο tag team;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFAccept::
	.string "Ευχαριστώ!\n"
	.string "Πάω να μας γράψω τώρα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFReject::
	.string "Αν ήμασταν ζευγάρι, θα μπορούσαμε\n"
	.string "να ήμασταν τόσο δυνατά!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacIntro::
	.string "Χαίρετε…\n"
	.string "Είμαι το HEX MANIAC {STR_VAR_1}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon1::
	.string "Φέρω μαζί μου ένα {STR_VAR_2}\n"
	.string "με {STR_VAR_1} μαζί με ένα$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon2Ask::
	.string "{STR_VAR_2} με {STR_VAR_1}…\p"
	.string "Σε ικετεύω…\n"
	.string "Γίνε μαζί μου ομάδα…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacAccept::
	.string "Σε ευχαριστώ…\n"
	.string "Θα ζητήσω να μας κάνουν εγγραφή…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacReject::
	.string "Τόσο πολύ λαχταρούσα να σε ακολουθήσω…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMIntro::
	.string "Τι γίνεται; Είμαι {STR_VAR_1},\n"
	.string "κι είμαι POKéMON BREEDER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon1::
	.string "Μεγαλώνω δυο πολύ καλά!\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Πώς σου φαίνεται;\n"
	.string "Θέλεις να φτιάξουμε ένα tag team;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMAccept::
	.string "Ευχαριστώ πολύ!\p"
	.string "Θα πάω να φροντίσω για την \n"
	.string "εγγραφή μας, οπότε περίμενε εδώ!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMReject::
	.string "Ανυπομονούσα να γίνω ζευγάρι σου…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFIntro::
	.string "Χαίρετε!\n"
	.string "Είμαι το άτομο TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon1::
	.string "Θες να μάθεις με τι τρέχω;\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Λοιπόν;\n"
	.string "Θες να είμαστε σε tag team ομάδα;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFAccept::
	.string "Αυτό μάλιστα!\p"
	.string "Θα βιαστώ να τελειώσω\n"
	.string "με την εγγραφή μας!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFReject::
	.string "Εσύ κι εγώ, θα ήμασταν στην\n"
	.string "κορυφή. Είναι κρίμα…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMIntro::
	.string "Γεια! Το όνομά μου είναι {STR_VAR_1}!\n"
	.string "Είμαι TRIATHLETE!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon1::
	.string "Πηγαίνω για τρέξιμο με την ανθεκτική\n"
	.string "ομάδα μου--ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Τέλεια δεν είναι;\n"
	.string "Θα έπρεπε να είμαστε μαζί σε tag team!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMAccept::
	.string "Εντάξει!\n"
	.string "Θα πάω να κάνω εγγραφή στο λεπτό!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMReject::
	.string "Ήθελα πραγματικά να πολεμήσω\n"
	.string "δίπλα σου…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlIntro::
	.string "Είμαι το BATTLE GIRL {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon1::
	.string "Δυνάμωνα ένα {STR_VAR_2} με\n"
	.string "{STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Σου αρέσει αυτός ο συνδυασμός;\n"
	.string "Τι λες να ενώναμε τις δυνάμεις μας;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlAccept::
	.string "Γιατί, ευχαριστώ!\p"
	.string "Θα τελειώσω την εγγραφή\n"
	.string "τώρα αμέσως!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlReject::
	.string "Μαζί σου, πίστευα ότι\n"
	.string "θα ήμασταν η απόλυτη tag team…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMIntro::
	.string "Είμαι το TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon1::
	.string "Τρέχω με ένα {STR_VAR_2} που\n"
	.string "ξέρει να χρησιμοποιεί {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon2Ask::
	.string "κι ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Θα μπορούσαμε να είμαστε σε tag team.\n"
	.string "Δεν θα ήταν υπέροχο;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMAccept::
	.string "Σε ευχαριστώ!\p"
	.string "Θα πάω να μας εγγράψω τώρα\n"
	.string "αμέσως!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMReject::
	.string "Αχ, είναι κρίμα. Θα ήμασταν η\n"
	.string "πιο σκληρή ομάδα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMIntro::
	.string "Εγώ;\n"
	.string "Είμαι το TUBER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon1::
	.string "Tι έχω μαζί μου;\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Ε;\n"
	.string "Θα είσαι ομάδα μαζί μου, έτσι;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMAccept::
	.string "Εντάξει!\p"
	.string "Πάω να κάνω εγγραφή!\n"
	.string "Ας είμαστε υπέροχα μαζί!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMReject::
	.string "Τα POKéMON μου είναι σίγουρα σκληρά…\n"
	.string "Είναι κρίμα που δεν θες να γίνουμε ομάδα.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristIntro::
	.string "Γιάου-έι!\n"
	.string "Πες με GUITARIST {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon1::
	.string "Τσέκαρε την ακολουθία μου!\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Γιάου-έι! Πολύ άγριο, ε;\n"
	.string "Θα πρέπει να κάνουμε ντουέτο σε tag team!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristAccept::
	.string "Γιάου-έι! Σωστά!\n"
	.string "Θα κάνω αυτά με την εγγραφή τώρα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristReject::
	.string "Τα POKéMON μου ροκάρουν σκληρά!\n"
	.string "Θα το μετανιώσεις, σου λέω!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanIntro::
	.string "Χαίρω πολύ για τη γνωριμία.\n"
	.string "Είμαι {STR_VAR_1}, ένα GENTLEMAN.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon1::
	.string "Συνοδεύομαι από το έμπιστο\n"
	.string "{STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Μπορώ να σου ζητήσω να\n"
	.string "συνεργαστούμε σε tag-team;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanAccept::
	.string "Α, σε ευχαριστώ για την εμπιστοσύνη.\n"
	.string "Θα τελειώσω με την εγγραφή.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanReject::
	.string "Αυτό είναι άκρως ατυχές…\p"
	.string "Θα ανυπομονώ για την\n"
	.string "επόμενη ευκαιρία…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMIntro::
	.string "Γεια σας, είμαι {STR_VAR_1},\n"
	.string "και είμαι ένα POKéFAN.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon1::
	.string "Έχω μαζί μου τώρα ένα {STR_VAR_2}\n"
	.string "που ξέρει την κίνηση {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Σου αρέσουν αυτά που βλέπεις;\n"
	.string "Γιατί δεν γίνεσαι το ζευγάρι μου;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMAccept::
	.string "Σε ευχαριστώ!\n"
	.string "Θα φροντίσω για την εγγραφή!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMReject::
	.string "Τα POKéMON μου είναι πρώτης τάξεως…\n"
	.string "Είναι κρίμα που δεν μπορείς να το δεις.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMIntro::
	.string "Χμ!\n"
	.string "Είμαι {STR_VAR_1}, κι είμαι EXPERT!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon1::
	.string "Τα POKéMON που έχω δυναμώσει είναι\n"
	.string "ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Τι λες για μια ομάδα tag μαζί μου;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMAccept::
	.string "Χμ!\n"
	.string "Λοιπόν, θα μας γράψω αμέσως!\l"
	.string "Ας βάλουμε και τα δυο τα δυνατά μας!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMReject::
	.string "Ελπίζω ότι η επιλογή σου είναι\n"
	.string "πράγματι σωστή…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFIntro::
	.string "Γεια, γεια.\n"
	.string "Είμαι {STR_VAR_1}, και είμαι EXPERT.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon1::
	.string "Έχω μεγαλώσει τα POKéMON μου τελείως.\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}--\n"
	.string "αυτά έχω.\p"
	.string "Δεν θα ήθελες να γίνουμε ομάδα μαζί;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFAccept::
	.string "Καλά, καλά.\n"
	.string "Θα φροντίσω την εγγραφή αμέσως.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFReject::
	.string "Ίσως μπορούμε να φτιάξουμε μια \n"
	.string "ομάδα την επόμενη φορά που θα βρεθούμε.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerIntro::
	.string "Είμαι DRAGON TAMER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon1::
	.string "Η ομάδα που έχω σκληραγωγήσει είναι\n"
	.string "ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Λοιπόν;\n"
	.string "Θες να είσαι το ζευγάρι μου;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerAccept::
	.string "Εντάξει, θα δώσω τον καλύτερό μου εαυτό!\n"
	.string "Πάω να κάνω εγγραφή τώρα, εντάξει;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerReject::
	.string "Δεν πρόκειται να βρεις πολλά πιο σκληρά\n"
	.string "ζευγάρια από εμένα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperIntro::
	.string "Είμαι BIRD KEEPER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon1::
	.string "Τι POKéMON έχω;\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Δεν νομίζεις ότι θα κάναμε μια\n"
	.string "αξιοπρεπή tag team;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperAccept::
	.string "Τέλεια, ευχαριστώ!\n"
	.string "Θα φροντίσω για την εγγραφή!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperReject::
	.string "Τα POKéMON μου κι εγώ είμαστε δυνατοί.\n"
	.string "Τι απογοήτευση.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyIntro::
	.string "Είμαι το NINJA BOY {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon1::
	.string "Η ομάδα POKéMON μου αποτελείται από\n"
	.string "ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Ας κάνουμε tag team μαζί!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyAccept::
	.string "Γιούπι!\n"
	.string "Πάω να κάνω εγγραφή!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyReject::
	.string "Θα μετανιώσεις που δεν έχεις τα σκληρά\n"
	.string "μου POKéMON με το μέρος σου!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyIntro::
	.string "Γεια σας!\n"
	.string "Είμαι η PARASOL LADY {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon1::
	.string "Με συνοδεύουν τώρα τα {STR_VAR_2}\n"
	.string "μου που χρησιμοποιούν {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon2Ask::
	.string "ένα {STR_VAR_2} που χρησιμοποιεί\n"
	.string "{STR_VAR_1}.\p"
	.string "Δεν είναι ωραία;\n"
	.string "Θέλεις να έρθεις μαζί μας σε tag team;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyAccept::
	.string "Ευχαριστώ πολύ!\p"
	.string "Θα πάω να μας εγγράψω στο γκισέ.\n"
	.string "Ας μην απογοητεύσουμε ο ένας τον άλλο!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyReject::
	.string "Τα POKéMON μου είναι τρομερά δυνατά.\n"
	.string "Τι απογοητευτικό…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacIntro::
	.string "Γεια.\n"
	.string "Είμαι {STR_VAR_1}, ένα BUG MANIAC!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon1::
	.string "Βρήκα τα POKéMON μου, ναι.\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}--\n"
	.string "αυτά είναι που βρήκα.\p"
	.string "Να σε ενδιέφερε να φτιάξουμε\n"
	.string "ένα tag team;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacAccept::
	.string "Εντάξει!\n"
	.string "Το έπιασα!\p"
	.string "Δεν θα αργήσω με την εγγραφή!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacReject::
	.string "Με τα POKéMON που βρήκα, δε θα\n"
	.string "χάναμε…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorIntro::
	.string "Αχόι, εκεί!\n"
	.string "Είμαι SAILOR {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon1::
	.string "Ας σου δείξω το καμάρι και τη χαρά μου!\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Φυσικά και δεν πρόκειται να\n"
	.string "με απορρίψεις. Θα κάνουμε ομάδα, σωστά;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorAccept::
	.string "Δεν περίμενα τίποτα λιγότερο!\n"
	.string "Πάω να κάνω εγγραφή τώρα.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorReject::
	.string "Θα είχαμε ταράξει τους αντίπαλους!\n"
	.string "Κρίμα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorIntro::
	.string "Γεια, είμαι {STR_VAR_1}.\n"
	.string "Είμαι COLLECTOR.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon1::
	.string "Τα πετράδια στη συλλογή μου είναι\n"
	.string "τα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Φανταστικό, ε;\n"
	.string "Θα έπρεπε να είμαστε μαζί σε ομάδα.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorAccept::
	.string "Ω, ναι!\p"
	.string "Λοιπόν, ας μη χάνουμε χρόνο.\n"
	.string "Θα πάω να μας εγγράψω τους δυο μας.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorReject::
	.string "Λοιπόν, αυτό είναι στενάχωρο.\n"
	.string "Δεν εκτιμάς τα POKéMON μου.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMIntro::
	.string "Γεια, είμαι {STR_VAR_1}.\n"
	.string "Είμαι POKéMON RANGER.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon1::
	.string "Μου κάνουν παρέα ένα {STR_VAR_2}\n"
	.string "που χρησιμοποιεί {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Δεν νομίζεις ότι θα κάναμε ένα \n"
	.string "εντυπωσιακό tag team;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMAccept::
	.string "Αυτό είναι σούπερ!\n"
	.string "Θα ασχοληθώ με την εγγραφή τώρα.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMReject::
	.string "Την επόμενη φορά, διάλεξε τα POKéMON \n"
	.string "μου, θα το κάνεις;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFIntro::
	.string "Το όνομά μου είναι {STR_VAR_1}.\n"
	.string "Είμαι POKéMON RANGER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon1::
	.string "Θα σου πω για την ομάδα μου. Έχω\n"
	.string "ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Πώς θα σου φαινόταν να φτιάξεις\n"
	.string "ένα tag team με την παρέα μου;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFAccept::
	.string "Θα είμαστε στα καλύτερά μας!\n"
	.string "Θα τελειώσω γρήγορα την εγγραφή!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFReject::
	.string "Ελπίζω να επιλέξεις τα POKéMON\n"
	.string "μου την επόμενη φορά.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyIntro::
	.string "Χαίρω πολύ. Είμαι η {STR_VAR_1}.\n"
	.string "Θεωρώ τον εαυτό μου AROMA LADY.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon1::
	.string "Ταξιδεύω με ένα {STR_VAR_2}\n"
	.string "που χρησιμοποιεί {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon2Ask::
	.string "ένα {STR_VAR_2} που χρησιμοποιεί\n"
	.string "{STR_VAR_1}.\p"
	.string "Ελπίζω να σου αρέσουν.\n"
	.string "Θα ήθελες να γίνουμε ζευγάρι;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyAccept::
	.string "Μου κάνεις τιμή με την αποδοχή σου.\n"
	.string "Θα πάω να κάνω την εγγραφή τώρα.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyReject::
	.string "Θα ήταν υπέροχο αν μπορούσαμε να \n"
	.string "κάνουμε ομάδα την επόμενη φορά.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacIntro::
	.string "Θες να μάθεις ποιο άτομο είμαι;\n"
	.string "Είμαι {STR_VAR_1}, το RUIN MANIAC!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon1::
	.string "Τα POKéMON που έχω μαζί μου είναι\n"
	.string "ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Ιντριγκαδόρικο, ε;\n"
	.string "Τι λες να συνεργαστούμε εγώ κι εσύ;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacAccept::
	.string "Αυτή είναι μια λογική απόφαση!\n"
	.string "Θα πάω να κάνω τα χαρτιά της εγγραφής.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacReject::
	.string "Χμμ…\n"
	.string "Πιστεύω ότι τα POKéMON μου είναι σκληρά$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMIntro::
	.string "Είμαι το COOLTRAINER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon1::
	.string "Τα POKéMON που έχω τώρα είναι ένα\n"
	.string "{STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\n"
	.string "Κουλ, ε;\p"
	.string "Δεν νομίζεις ότι θα ήταν πολύ κουλ αν\n"
	.string "κάναμε ένα tag team;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMAccept::
	.string "Τέλειο!\n"
	.string "Πάω να κάνω εγγραφή στο άψε σβήσε!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMReject::
	.string "Σκεφτόμουν ότι θα ήμασταν η\n"
	.string "καλύτερη ομάδα όλων των εποχών.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFIntro::
	.string "Είμαι COOLTRAINER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon1::
	.string "Η ομάδα που μεγάλωνα έχει ένα\n"
	.string "{STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Καλά δεν ακούγεται αυτο;\n"
	.string "Τι θα έλεγες να γίνουμε tag partners;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFAccept::
	.string "Ακούγεται OK!\n"
	.string "Καλύτερα να κάνω την εγγραφή.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFReject::
	.string "Σκεφτόμουν ότι θα ήμασταν μια\n"
	.string "σκληρή ομάδα…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacIntro::
	.string "Έι!\n"
	.string "Είμαι {STR_VAR_1}, το POKéMANIAC!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon1::
	.string "Τι έχει ένας τύπος σαν εμένα;\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1},\n"
	.string "αυτό έχω!\p"
	.string "Ας το κάνουμε!\n"
	.string "Θα παρελάσουμε ως tag team!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacAccept::
	.string "Καλή απόφαση!\n"
	.string "Θα μας εγγράψω κι εμάς τους δύο!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacReject::
	.string "Τα POKéMON μου είναι βάναυσα!\n"
	.string "Δεν φταίω εγώ αν το μετανιώσεις αυτό!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerIntro::
	.string "Γεια, εκεί!\n"
	.string "Είμαι το KINDLER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon1::
	.string "Ξέρεις τι μαγείρεψε η προπόνησή μου;\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Λοιπόν, τι λες;\n"
	.string "Θέλεις να φτιάξουμε ένα tag team;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerAccept::
	.string "Εντάξει!\n"
	.string "Θα προχωρήσω με την εγγραφή.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerReject::
	.string "Λοιπόν! Την επόμενη φορά που θα \n"
	.string "συναντηθούμε, ας γίνουμε ομάδα, οκ;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperIntro::
	.string "Είμαι {STR_VAR_1}, κι είμαι CAMPER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon1::
	.string "Έχω μεγαλώσει ένα {STR_VAR_2} που\n"
	.string "χρησιμοποιεί {STR_VAR_1} και ένα$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon2Ask::
	.string "{STR_VAR_2} να χρησιμοποιεί {STR_VAR_1}.\p"
	.string "Νομίζεις ότι θα ήταν διασκεδαστικό \n"
	.string "να είμαστε ομάδα; Σίγουρα θα ήταν!»$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperAccept::
	.string "Ναι!\n"
	.string "Φεύγω για προπόνηση!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperReject::
	.string "Την επόμενη φορά, εντάξει;\n"
	.string "Θέλω να είμαι στην ομάδα σου.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerIntro::
	.string "Γεια σας!\n"
	.string "Είμαι {STR_VAR_1}, κι είμαι PICNICKER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon1::
	.string "Τα POKéMON που έπαιρνα είναι\n"
	.string "ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Σε ενδιαφέρει να γίνεις μαζί\n"
	.string "μου σε tag team ομάδα;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerAccept::
	.string "Μα, σε ευχαριστώ!\n"
	.string "Θα κάνω την εγγραφή τώρα.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerReject::
	.string "Θα ήταν ωραίο αν μπορούσα να είμαι \n"
	.string "μαζί σου κάποια άλλη φορά.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMIntro::
	.string "Είμαι το PSYCHIC {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon1::
	.string "Το ζευγάρι που μεγαλώνω είναι\n"
	.string "ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Θα ήθελες να φτιάξουμε ομάδα σε \n"
	.string "tag team μαζί;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMAccept::
	.string "Σίγουρα!\n"
	.string "Θα αναλάβω την εγγραφή!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMReject::
	.string "Αν ξανασυναντηθούμε, τότε θα ήθελα\n"
	.string "να συνεργαστούμε.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFIntro::
	.string "Είμαι {STR_VAR_1}.\n"
	.string "Είμαι PSYCHIC.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon1::
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}--\n"
	.string "είναι τα δικά μου.\p"
	.string "Δεν σε ιντριγκάρει η ιδέα να \n"
	.string "συνεργαστούμε σε tag-team;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFAccept::
	.string "Ευχαριστώ.\n"
	.string "Θα πάω να ασχοληθώ με την εγγραφή.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFReject::
	.string "Ελπίζω ότι θα υπάρξει άλλη μια φορά\n"
	.string "για να σφυρηλατήσουμε μια συμμαχία.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFIntro::
	.string "Είμαι το SCHOOL KID {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon1::
	.string "Ένα {STR_VAR_2} με {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon2Ask::
	.string "και ένα {STR_VAR_2} με {STR_VAR_1}\n"
	.string "είναι το ζευγάρι POKéMON μου.\p"
	.string "Μπορώ σε παρακαλώ να είμαι  \n"
	.string "ζευγάρι σου σε tag team;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFAccept::
	.string "Ου, ευχαριστώ!\n"
	.string "Θα εγγραφώ στο γκισέ αμέσως!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFReject::
	.string "Σε παρακαλώ; Μπορώ να μοιραστώ μαζί\n"
	.string "σου την επόμενη φορά;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFIntro::
	.string "Γεια σας! Το όνομα είναι {STR_VAR_1}!\n"
	.string "Είμαι POKéMON BREEDER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon1::
	.string "Τα POKéMON που έχω μεγαλώσει είναι ένα\n"
	.string "{STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Ακούγεται ενδιαφέρον;\n"
	.string "Τι θα έλεγες να φτιάξουμε ένα tag team;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFAccept::
	.string "Εντάξει λοιπόν!\n"
	.string "Να αφήσεις την εγγραφή σε μένα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFReject::
	.string "Πρέπει να συνεργαστείς μαζί μου\n"
	.string "την επόμενη φορά, εντάξει;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFIntro::
	.string "Είμαι {STR_VAR_1},  και λέω περήφανα\n"
	.string "ότι είμαι POKéFAN.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon1::
	.string "Τα αγαπημένα μου POKéMON είναι\n"
	.string "ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}.\p"
	.string "Δεν είναι τα πιο χαριτωμένα;\n"
	.string "Πρέπει να κάνουμε μια ομάδα!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFAccept::
	.string "Ευχαριστώ, αγαπητέ μου!\n"
	.string "Θα είμαι στο δρόμο για να εγγραφώ!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFReject::
	.string "Τα αγαπημένα μου POKéMON είναι τα \n"
	.string "καλύτερα, να ξέρεις. Πόσο ενοχλητικό!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFIntro::
	.string "Γεια, είμαι SWIMMER {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon1::
	.string "Ένα {STR_VAR_2} με {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon2Ask::
	.string "κι ένα {STR_VAR_2} με\n"
	.string "{STR_VAR_1} είναι αυτά που έχω.\p"
	.string "Εσύ κι εγώ, ας κάνουμε ένα tag team.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFAccept::
	.string "Αυτό είναι τέλειο!\n"
	.string "Θα μας γράψω και τους δυο μας.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFReject::
	.string "Αν ξανασυναντηθούμε, μου χρωστάς\n"
	.string "ένα tag team!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMIntro::
	.string "Τι γίνεται;\n"
	.string "Είμαι {STR_VAR_1}, και είμαι TRIATHLETE.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon1::
	.string "Έχω μερικά αξιοπρεπή POKéMON.\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Θα ήταν ωραίο αν κάναμε μαζί ένα \n"
	.string "tag team, λοιπόν τι λες;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMAccept::
	.string "Σωστά!\n"
	.string "Εσύ περίμενε να κάνω εγγραφή, εντάξει;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMReject::
	.string "Περιμένω να με αφήσεις να έρθω \n"
	.string "μαζί σου την επόμενη φορά, πώς σου φαίνεται;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFIntro::
	.string "Είμαι το TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon1::
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon2Ask::
	.string "άλλο {STR_VAR_2} που ξέρει πως να\n"
	.string "χρησιμοποιεί {STR_VAR_1}. Είναι το ζευγάρι μου.\p"
	.string "Τι νομίζεις;\n"
	.string "Θα κάναμε καλή ομάδα, θα έλεγα.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFAccept::
	.string "Μου αρέσει αυτή η απάντηση!\n"
	.string "Θα τελειώσω γρήγορα την εγγραφή!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFReject::
	.string "Θα μου δώσεις άλλη μια ευκαιρία να \n"
	.string "συνεργαστούμε, δεν θα το κάνεις;$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMIntro::
	.string "Γεια, εκεί! Γεια σας!\n"
	.string "Είμαι {STR_VAR_1}, κι είμαι SWIMMER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon1::
	.string "Δες τι μεγάλωνα!\n"
	.string "Ένα {STR_VAR_2} με {STR_VAR_1} και$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon2Ask::
	.string "ένα {STR_VAR_2} με {STR_VAR_1}!\p"
	.string "Γλυκό, ε;\n"
	.string "Θα ήταν γλυκό να κάνουμε ομάδα, επίσης!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMAccept::
	.string "Υποχρεωμένος!\n"
	.string "Θα κάνω αυτό το πράγμα με την εγγραφή!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMReject::
	.string "Αν ξανασυναντηθούμε, πρέπει να γίνουμε \n"
	.string "ομάδα. Θα το κάνεις αυτό, σωστά;$"

