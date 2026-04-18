.set LOCALID_MAGMA_GRUNT_1, 5
.set LOCALID_MAGMA_GRUNT_2, 6
.set LOCALID_ARCHIE, 7
.set LOCALID_AQUA_GRUNT_1, 8
.set LOCALID_AQUA_GRUNT_2, 9

MeteorFalls_1F_1R_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MeteorFalls_1F_1R_OnLoad
	.byte 0

MeteorFalls_1F_1R_OnLoad:
	call_if_set FLAG_SYS_GAME_CLEAR, MeteorFalls_1F_1R_EventScript_OpenStevensCave
	end

MeteorFalls_1F_1R_EventScript_OpenStevensCave::
	setmetatile 4, 1, METATILE_MeteorFalls_CaveEntrance_Top, TRUE
	setmetatile 3, 2, METATILE_MeteorFalls_CaveEntrance_Left, TRUE
	setmetatile 4, 2, METATILE_MeteorFalls_CaveEntrance_Bottom, FALSE
	setmetatile 5, 2, METATILE_MeteorFalls_CaveEntrance_Right, TRUE
	return

MeteorFalls_1F_1R_EventScript_MagmaStealsMeteoriteScene::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	delay 30
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceDown
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_WithThisMeteorite, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_Delay48
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_DontExpectMercyFromMagma, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAGMA_GRUNT_1, MeteorFalls_1F_1R_Movement_MagmaGruntApproachPlayer
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_HoldItRightThereMagma, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	addobject LOCALID_ARCHIE
	addobject LOCALID_AQUA_GRUNT_1
	addobject LOCALID_AQUA_GRUNT_2
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieArrive
	applymovement LOCALID_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1Arrive
	applymovement LOCALID_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2Arrive
	waitmovement 0
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_BeSeeingYouTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_PushPlayerOutOfWay
	applymovement LOCALID_MAGMA_GRUNT_1, MeteorFalls_1F_1R_Movement_MagmaGrunt1Exit
	applymovement LOCALID_MAGMA_GRUNT_2, MeteorFalls_1F_1R_Movement_MagmaGrunt2Exit
	waitmovement 0
	removeobject LOCALID_MAGMA_GRUNT_1
	removeobject LOCALID_MAGMA_GRUNT_2
	applymovement LOCALID_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieSeenYouBefore, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1ApproachArchie
	applymovement LOCALID_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2ApproachArchie
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_BossWeShouldChaseMagma, MSGBOX_DEFAULT
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieYesNoTellingWhatMagmaWillDo, MSGBOX_DEFAULT
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieFarewell, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieExit
	applymovement LOCALID_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1Exit
	applymovement LOCALID_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2Exit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_AQUA_GRUNT_1
	removeobject LOCALID_AQUA_GRUNT_2
	setflag FLAG_HIDE_ROUTE_112_TEAM_MAGMA
	setflag FLAG_MET_ARCHIE_METEOR_FALLS
	setflag FLAG_HIDE_FALLARBOR_TOWN_BATTLE_TENT_SCOTT
	setvar VAR_METEOR_FALLS_STATE, 1
	releaseall
	end

MeteorFalls_1F_1R_Movement_MagmaGruntApproachPlayer:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MeteorFalls_1F_1R_Movement_MagmaGrunt1Exit:
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

MeteorFalls_1F_1R_Movement_MagmaGrunt2Exit:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieArrive:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1Arrive:
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2Arrive:
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieExit:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieApproachPlayer:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_in_place_faster_left
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1Exit:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1ApproachArchie:
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2Exit:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2ApproachArchie:
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MeteorFalls_1F_1R_Movement_PushPlayerOutOfWay:
	walk_in_place_faster_down
	delay_4
	walk_in_place_faster_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	face_right
	step_end

MeteorFalls_1F_1R_EventScript_ProfCozmo::
	lock
	faceplayer
	goto_if_set FLAG_MET_PROF_COZMO, MeteorFalls_1F_1R_EventScript_MetCozmo
	setflag FLAG_MET_PROF_COZMO
	msgbox MeteorFalls_1F_1R_Text_MeetProfCozmo, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_1R_EventScript_MetCozmo::
	msgbox MeteorFalls_1F_1R_Text_WhatsTeamMagmaDoingAtMtChimney, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_1R_Text_WithThisMeteorite:
	.string "Χεχεχε!\p"
	.string "Με αυτό το METEORITE, εκείνο το \n"
	.string "πράγμα στο MT. CHIMNEY θα…$"

MeteorFalls_1F_1R_Text_DontExpectMercyFromMagma:
	.string "Ε;\p"
	.string "Δεν ξέρω ποιος είσαι, αλλά αν μπεις \n"
	.string "στο δρόμο της TEAM MAGMA, μην \l"
	.string "προσδοκάς κανένα έλεος!$"

MeteorFalls_1F_1R_Text_HoldItRightThereMagma:
	.string "Σταματήστε αμέσως εκεί, TEAM MAGMA!\p"
	.string "Κάνετε μεγάλο λάθος αν νομίζετε ότι \n"
	.string "μπορείτε να κάνετε ό,τι θέλετε \l"
	.string "με τον κόσμο!$"

MeteorFalls_1F_1R_Text_BeSeeingYouTeamAqua:
	.string "Xεχεχε!\n"
	.string "Ακόμα και η TEAM AQUA!\p"
	.string "Αλλά είναι πολύς κόπος να \n"
	.string "ασχοληθούμε μαζί σας…\p"
	.string "Ε, δεν πειράζει!\p"
	.string "Έχουμε το METEORITE, οπότε \n"
	.string "φεύγουμε για το MT. CHIMNEY!\p"
	.string "Χεχεχε! Θα τα πούμε, εσείς \n"
	.string "ανόητοι της TEAM AQUA!$"

MeteorFalls_1F_1R_Text_ArchieSeenYouBefore:
	.string "ARCHIE: Δεν σε έχω ξαναδεί;\n"
	.string "Στο MUSEUM του SLATEPORT;\p"
	.string "Α, οπότε το όνομά σου είναι {PLAYER}.\p"
	.string "Εκείνη τη φορά, πίστευα ότι ήσουν \n"
	.string "ένας από τους τραμπούκους \l"
	.string "της TEAM MAGMA.\p"
	.string "Χμ…\n"
	.string "Είσαι ένα περίεργο παιδί.\p"
	.string "Η TEAM MAGMA είναι μια επικίνδυνη \n"
	.string "ομάδα από φανατικούς.\p"
	.string "Εμπλέκονται σε καταστροφές, \n"
	.string "ισχυριζόμενοι ότι θέλουν \l"
	.string "να επεκτείνουν τη στεριά.\p"
	.string "Είναι οι αντίπαλοί μας, \n"
	.string "της θαλασσόφιλης TEAM AQUA!$"

MeteorFalls_1F_1R_Text_BossWeShouldChaseMagma:
	.string "ΑΡΧΗΓΕ, θα έπρεπε να \n"
	.string "κυνηγήσουμε την TEAM MAGMA…$"

MeteorFalls_1F_1R_Text_ArchieYesNoTellingWhatMagmaWillDo:
	.string "ARCHIE: Ναι, ναι, πρέπει!\n"
	.string "Πρέπει να βιαστούμε.\p"
	.string "Ποιος ξέρει τι θα κάνει η TEAM MAGMA \n"
	.string "στο MT. CHIMNEY!$"

MeteorFalls_1F_1R_Text_ArchieFarewell:
	.string "ARCHIE: {PLAYER}, θα πρέπει \n"
	.string "να προσέχεις την TEAM MAGMA, επίσης.\p"
	.string "Αντίο!$"

MeteorFalls_1F_1R_Text_MeetProfCozmo:
	.string "Εγώ… Είμαι ο COZMO…\n"
	.string "Είμαι ένας PROFESSOR…\p"
	.string "Η TEAM MAGMA μου ζήτησε να τους \n"
	.string "οδηγήσω στο METEOR FALLS…\p"
	.string "Αλλά με ξεγέλασαν.\n"
	.string "Πήραν ακόμα και το METEORITE μου…\p"
	.string "Και μετά μια παρόμοια ομάδα, \n"
	.string "η TEAM AQUA εμφανίστηκε.\p"
	.string "Μετά από αυτό…\n"
	.string "Δεν καταλαβαίνω τίποτα.\p"
	.string "Αλλά αυτή η TEAM MAGMA…\p"
	.string "Τι θα κάνουν με αυτό το METEORITE \n"
	.string "στο MT. CHIMNEY;$"

MeteorFalls_1F_1R_Text_WhatsTeamMagmaDoingAtMtChimney:
	.string "PROF. COZMO: Αλλά αυτή η TEAM MAGMA…\p"
	.string "Τι θα κάνουν με αυτό το METEORITE \n"
	.string "στο MT. CHIMNEY;$"
