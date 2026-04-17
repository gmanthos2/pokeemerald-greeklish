.set LOCALID_EXPERT_M, 4
.set LOCALID_TWIN, 5
.set LOCALID_SCHOOL_KID_M, 7
.set LOCALID_PSYCHIC_M, 8

DewfordTown_Hall_MapScripts::
	.byte 0

DewfordTown_Hall_EventScript_Girl::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special IsTrendyPhraseBoring
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_Hall_EventScript_GirlBoredOfTrend
	msgbox DewfordTown_Hall_Text_CantImagineLifeWithoutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_GirlBoredOfTrend::
	msgbox DewfordTown_Hall_Text_GettingBoredOfTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Woman::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_TeachingMonAboutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Man::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special BufferDeepLinkPhrase
	msgbox DewfordTown_Hall_Text_DeepLinkBetweenXAndY, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DewfordTown_Hall_EventScript_ConfirmTrendLink
	goto_if_eq VAR_RESULT, NO, DewfordTown_Hall_EventScript_RejectTrendLink
	end

DewfordTown_Hall_EventScript_ConfirmTrendLink::
	msgbox DewfordTown_Hall_Text_MyHunchWasRight, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_RejectTrendLink::
	msgbox DewfordTown_Hall_Text_NotEasyToKeepUp, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_ExpertM::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_TVShowAboutTrend, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_EXPERT_M, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_Twin::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TWIN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_LittleBoy::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_CollectTrendMerchandise, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Bookshelf::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_BooksAboutTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_Painting::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordTown_Hall_EventScript_ScreamTitle
	case 4, DewfordTown_Hall_EventScript_ScreamTitle
	case 1, DewfordTown_Hall_EventScript_SmileTitle
	case 5, DewfordTown_Hall_EventScript_ScreamTitle
	case 2, DewfordTown_Hall_EventScript_LastTitle
	case 6, DewfordTown_Hall_EventScript_LastTitle
	case 3, DewfordTown_Hall_EventScript_BirthTitle
	case 7, DewfordTown_Hall_EventScript_LastTitle
	end

DewfordTown_Hall_EventScript_ScreamTitle::
	msgbox DewfordTown_Hall_Text_TrendsScream, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_SmileTitle::
	msgbox DewfordTown_Hall_Text_TrendsSmile, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_LastTitle::
	msgbox DewfordTown_Hall_Text_LastTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_BirthTitle::
	msgbox DewfordTown_Hall_Text_BirthOfTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_SchoolKidM::
	lockall
	setvar VAR_0x8008, 0
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_PsychicM::
	lockall
	setvar VAR_0x8008, 1
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_DoTrendDebate::
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordTown_Hall_EventScript_TrendDebate1
	case 1, DewfordTown_Hall_EventScript_TrendDebate1
	case 2, DewfordTown_Hall_EventScript_TrendDebate2
	case 3, DewfordTown_Hall_EventScript_TrendDebate2
	case 4, DewfordTown_Hall_EventScript_TrendDebate3
	case 5, DewfordTown_Hall_EventScript_TrendDebate3
	case 6, DewfordTown_Hall_EventScript_TrendDebate4
	case 7, DewfordTown_Hall_EventScript_TrendDebate5
	end

DewfordTown_Hall_EventScript_TrendDebate1::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_SawTrendCoolestThing, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_AllegedTrendNotAuthentic, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate2::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_ComposedTrendThemeSong, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WorkOnYourSinging, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate3::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_OrganizeTrendParty, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_BrilliantIndeed, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate4::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_TrendHasBecomePartOfLife, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate5::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WellBeTrendDuo, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_DontMovePlayer1::
	return

DewfordTown_Hall_EventScript_DebateReact1::
	applymovement LOCALID_PSYCHIC_M, DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactWest
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_DontMovePlayer2
	end

DewfordTown_Hall_EventScript_PlayerReactWest::
	goto_if_eq VAR_FACING, DIR_EAST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

DewfordTown_Hall_EventScript_DontMovePlayer2::
	return

DewfordTown_Hall_EventScript_DebateReact2::
	applymovement LOCALID_SCHOOL_KID_M, DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactNorthSouth
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_PlayerReactEast
	end

DewfordTown_Hall_EventScript_PlayerReactNorthSouth::
	call_if_eq VAR_FACING, DIR_NORTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp
	call_if_eq VAR_FACING, DIR_SOUTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerReactEast::
	goto_if_eq VAR_FACING, DIR_WEST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft:
	walk_in_place_left
	step_end

DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight:
	walk_in_place_right
	step_end

DewfordTown_Hall_EventScript_SludgeBombMan::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	goto_if_set FLAG_RECEIVED_TM_SLUDGE_BOMB, DewfordTown_Hall_EventScript_ReceivedSludgeBomb
	msgbox DewfordTown_Hall_Text_GiveYouSludgeBomb, MSGBOX_DEFAULT
	giveitem ITEM_TM_SLUDGE_BOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_SLUDGE_BOMB
	release
	end

DewfordTown_Hall_EventScript_ReceivedSludgeBomb::
	msgbox DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_Text_CantImagineLifeWithoutTrend:
	.string "Τι είναι στη μόδα; Μα, φυσικά,\n"
	.string "“{STR_VAR_1}”!\p"
	.string "Δεν μπορώ να φανταστώ πώς θα ήταν\n"
	.string "η ζωή χωρίς “{STR_VAR_1}”!$"

DewfordTown_Hall_Text_GettingBoredOfTrend:
	.string "Τι είναι στη μόδα; Μα, φυσικά,\n"
	.string "“{STR_VAR_1}”!\p"
	.string "Αλλά αρχίζω να το βαριέμαι.\p"
	.string "Πρέπει να ψάξω για τη νέα τάση.$"

DewfordTown_Hall_Text_TeachingMonAboutTrend:
	.string "Διδάσκω τα POKéMON μου για το\n"
	.string "“{STR_VAR_1},”\l"
	.string "αλλά δεν πάει τόσο καλά.\p"
	.string "Είναι μάλλον λίγο υπερβολικό.$"

DewfordTown_Hall_Text_DeepLinkBetweenXAndY:
	.string "Μελετάω το νέο και μοντέρνο\n"
	.string "“{STR_VAR_1}” τώρα.\p"
	.string "Αληθεύει ότι υπάρχει βαθιά σύνδεση\n"
	.string "μεταξύ του “{STR_VAR_1}”\l"
	.string "και του “{STR_VAR_2}”;$"

DewfordTown_Hall_Text_MyHunchWasRight:
	.string "Ω!\n"
	.string "Οπότε, το προαίσθημά μου ήταν σωστό!\p"
	.string "Είμαι ένα βήμα πιο κοντά στο να είμαι \n"
	.string "νέος και μοντέρνος, γιούπι!$"

DewfordTown_Hall_Text_NotEasyToKeepUp:
	.string "Τι;!\n"
	.string "Έτσι είναι;!\p"
	.string "Δεν είναι εύκολο για έναν μεγάλο\n"
	.string "όπως εγώ να ακολουθεί τις τάσεις!$"

DewfordTown_Hall_Text_TVShowAboutTrend:
	.string "Όλη αυτή η υπόθεση με το\n"
	.string "“{STR_VAR_1}”…\l"
	.string "Δεν υπάρχει και εκπομπή στην τηλεόραση;$"

DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea:
	.string "Απέναντι από τη θάλασσα…\p"
	.string "Είναι το “{STR_VAR_1}”\n"
	.string "ακόμα πιο διάσημο;$"

DewfordTown_Hall_Text_CollectTrendMerchandise:
	.string "Συλλέγω επίσημα\n"
	.string "“{STR_VAR_1}”\l"
	.string "εμπορεύματα.\p"
	.string "Έχω επίσημα λούτρινα\n"
	.string "“{STR_VAR_1}” DOLLS…\p"
	.string "Επίσημα “{STR_VAR_1}”\n"
	.string "ρούχα…\p"
	.string "Και εγκεκριμένα “{STR_VAR_1}”\n"
	.string "εικονογραφημένα βιβλία.\p"
	.string "Χεχε, τα έχω!\n"
	.string "Δεν θα μοιραστώ τίποτα με εσένα!$"

DewfordTown_Hall_Text_BooksAboutTrend:
	.string "ΞΕΧΩΡΙΖΟΝΤΑΣ ΚΑΛΟ\n"
	.string "“{STR_VAR_1}” &\l"
	.string "ΚΑΚΟ “{STR_VAR_1}”…\p"
	.string "Η ΣΥΝΔΕΣΗ ΜΕΤΑΞΥ\n"
	.string "“{STR_VAR_1}” ΚΑΙ\l"
	.string "POKéMON…\p"
	.string "ΧΡΗΣΙΜΟ\n"
	.string "“{STR_VAR_1}”…\p"
	.string "Είναι γεμάτο με βιβλία\n"
	.string "“{STR_VAR_1}.”$"

DewfordTown_Hall_Text_TrendsScream:
	.string "Ο τίτλος είναι “{STR_VAR_1}'S\n"
	.string "SCREAM”.$"

DewfordTown_Hall_Text_TrendsSmile:
	.string "Ο τίτλος είναι “{STR_VAR_1}'S\n"
	.string "SMILE”.$"

DewfordTown_Hall_Text_LastTrend:
	.string "Ο τίτλος είναι “THE LAST\n"
	.string "{STR_VAR_1}”.$"

DewfordTown_Hall_Text_BirthOfTrend:
	.string "Ο τίτλος είναι “Η ΓΕΝΝΗΣΗ ΤΟΥ\n"
	.string "{STR_VAR_1}”.$"

DewfordTown_Hall_Text_SawTrendCoolestThing:
	.string "Είδα “{STR_VAR_1}”!\n"
	.string "Τέλειο ε;\p"
	.string "Είναι ίσως ό,τι καλύτερο υπάρχει!\p"
	.string "Ήταν τέλειο!\n"
	.string "Ήταν το αυθεντικό ρε φίλε!$"

DewfordTown_Hall_Text_AllegedTrendNotAuthentic:
	.string "Ω, όχι, όχι, όχι.\p"
	.string "Αυτό που λες\n"
	.string "“{STR_VAR_1}”\l"
	.string "ότι είδες--δεν είναι.\p"
	.string "Το αυθεντικό είναι πολύ…\n"
	.string "Πώς να το πω;\l"
	.string "Πιο έντονο, μα πιο γλυκό!\p"
	.string "Α, δεν πειράζει. Είναι συναρπαστικό!$"

DewfordTown_Hall_Text_ComposedTrendThemeSong:
	.string "Ε, άκου εδώ, έγραψα ένα θεματικό \n"
	.string "τραγούδι για το “{STR_VAR_1}.”\p"
	.string "Το “{STR_VAR_1}”\n"
	.string "είναι πολύ της μόδας τώρα.\p"
	.string "Λοιπόν, άκουσε!\n"
	.string "… …\p"
	.string "Ω!\n"
	.string "{STR_VAR_1}!\p"
	.string "Υπέροχο\n"
	.string "{STR_VAR_1}!$"

DewfordTown_Hall_Text_WorkOnYourSinging:
	.string "… …\p"
	.string "Θα τολμούσα να πω, φίλε μου, ότι \n"
	.string "πρέπει να δουλέψεις στο τραγούδι σου \l"
	.string "πριν ασχοληθείς με το\l"
	.string "“{STR_VAR_1}.”$"

DewfordTown_Hall_Text_OrganizeTrendParty:
	.string "Όπως και να χει, όπως έλεγα πριν,\n"
	.string "πρέπει να μαζευτούμε και να κάνουμε \l"
	.string "ένα πάρτι “{STR_VAR_1}”\l"
	.string "στο νησί.$"

DewfordTown_Hall_Text_BrilliantIndeed:
	.string "Ω, μια εξαιρετική ιδέα!\p"
	.string "Θα ξεκαθαρίσει μια και καλή\n"
	.string "ποιος είναι ο καλύτερος στο\l"
	.string "“{STR_VAR_1}.”\l"
	.string "Εξαιρετικά, ειλικρινά!\p"
	.string "Από σήμερα, η ζωή μας θα περιστρέφεται\n"
	.string "γύρω από το “{STR_VAR_1}”!$"

DewfordTown_Hall_Text_TrendHasBecomePartOfLife:
	.string "Σκεφτόμουν, όμως…\p"
	.string "Δεν συμφωνείς ότι το\n"
	.string "“{STR_VAR_1}” έχει\l"
	.string "από απλώς μια τάση γίνει \l"
	.string "κομμάτι της καθημερινότητάς μας;$"

DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind:
	.string "Με συγχωρείς;\n"
	.string "Τόσο πολύ, τι;\p"
	.string "Όμως, είναι αλήθεια ότι\n"
	.string "“{STR_VAR_1}”\l"
	.string "σε απασχολεί έντονα, \l"
	.string "είτε είσαι ξύπνιος είτε κοιμάσαι.\p"
	.string "Σίγουρα, είσαι ο ΚΑΘΗΓΗΤΗΣ του\n"
	.string "“{STR_VAR_1}”, φίλε μου!$"

DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible:
	.string "Αν ενώσουμε τις δυνάμεις μας\n"
	.string "λοιπόν, θα είμαστε αήττητοι \l"
	.string "σχετικά με τα πάντα στο “{STR_VAR_1}”!$"

DewfordTown_Hall_Text_WellBeTrendDuo:
	.string "Μέσα έπεσες, φίλε μου!\p"
	.string "Θα είμαστε το ΔΙΔΥΜΟ \n"
	.string "“{STR_VAR_1}”!\p"
	.string "Δεν είναι ωραία ιδέα;\n"
	.string "Χαχαχα!$"

DewfordTown_Hall_Text_GiveYouSludgeBomb:
	.string "Για εμένα, η SLUDGE BOMB είναι\n"
	.string "στην κορυφή της δημοτικότητας.\p"
	.string "Ε; Τι λες; Μου λες ότι δεν την ξέρεις;\n"
	.string "Αυτό είναι αξιολύπητο!\p"
	.string "Θα σου δώσω μία.$"

DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo:
	.string "Λατρεύω τη SLUDGE BOMB.\p"
	.string "Αλλά και τα POKéMON με κίνηση\n"
	.string "“{STR_VAR_1}”\l"
	.string "είναι και αυτά της μόδας.$"

