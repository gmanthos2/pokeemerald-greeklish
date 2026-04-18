.set LOCALID_FOSSIL_MANIAC, 1

Route114_FossilManiacsTunnel_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsTunnel_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route114_FossilManiacsTunnel_OnLoad
	.byte 0

Route114_FossilManiacsTunnel_OnTransition:
	call_if_set FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac
	end

Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac::
	setobjectxyperm LOCALID_FOSSIL_MANIAC, 6, 5
	setobjectmovementtype LOCALID_FOSSIL_MANIAC, MOVEMENT_TYPE_FACE_DOWN
	return

Route114_FossilManiacsTunnel_OnLoad:
	call_if_unset FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass
	end

Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass::
	setmetatile 6, 1, METATILE_Fallarbor_RedRockWall, TRUE
	setmetatile 6, 2, METATILE_Fallarbor_RedRockWall, TRUE
	return

Route114_FossilManiacsTunnel_EventScript_ManiacMentionCaveIn::
	lockall
	applymovement LOCALID_FOSSIL_MANIAC, Common_Movement_WalkInPlaceFasterUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox Route114_FossilManiacsTunnel_Text_NotSafeThatWay, MSGBOX_DEFAULT
	setvar VAR_FOSSIL_MANIAC_STATE, 2
	releaseall
	end

Route114_FossilManiacsTunnel_EventScript_FossilManiac::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_REVIVED_FOSSIL_MON, Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil
	msgbox Route114_FossilManiacsTunnel_Text_LookInDesertForFossils, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil::
	msgbox Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil::
	msgbox Route114_FossilManiacsTunnel_Text_FossilsAreWonderful, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_Text_LookInDesertForFossils:
	.string "Είμαι ο FOSSIL MANIAC…\n"
	.string "Είμαι ένα καλό παιδί που\l"
	.string "αγαπά τα FOSSILS…\p"
	.string "Θέλεις ένα FOSSIL;\p"
	.string "Αλλά τα FOSSILS γύρω από\n"
	.string "αυτά τα μέρη ανήκουν όλα σε\l"
	.string "μένα… Κανένα για σένα…\p"
	.string "Αν δεν αντέχεις να είσαι χωρίς\n"
	.string "FOSSIL, ψάξε σε μια έρημο όπου\l"
	.string "υπάρχουν πέτρες και άμμος που\l"
	.string "μπορεί να κρύβουν FOSSILS…$"

Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils:
	.string "Βρήκες ένα FOSSIL, έτσι δεν\n"
	.string "είναι;\l"
	.string "Είναι τόσο ωραία… Είναι\l"
	.string "ονειρικά…\p"
	.string "Τι θα κάνεις με αυτό το\n"
	.string "FOSSIL;\p"
	.string "Από ό,τι έχω ακούσει, η DEVON\n"
	.string "κάνει έρευνα για την\l"
	.string "αναβίωση POKéMON από FOSSILS…\p"
	.string "Αγαπώ τα FOSSILS μου, οπότε\n"
	.string "δεν θα έκανα ποτέ κάτι\l"
	.string "τέτοιο…$"

Route114_FossilManiacsTunnel_Text_FossilsAreWonderful:
	.string "Τα FOSSILS είναι τόσο… Υπέροχα…\n"
	.string "Είναι τόσο ονειρικά…$"

Route114_FossilManiacsTunnel_Text_NotSafeThatWay:
	.string "Ω…\n"
	.string "Δεν είναι ασφαλές προς τα\l"
	.string "εκεί…\p"
	.string "Έσκαβα βαθιά, βλέπεις…\n"
	.string "Όταν ολόκληρος ο τοίχος\l"
	.string "κατέρρευσε…\p"
	.string "Νομίζω ότι υπάρχει μια\n"
	.string "τεράστια σπηλιά από κάτω\l"
	.string "τώρα…\p"
	.string "Αλλά το άφησα ήσυχο γιατί δεν\n"
	.string "νομίζω ότι υπάρχουν\l"
	.string "καθόλου FOSSILS εκεί…$"

