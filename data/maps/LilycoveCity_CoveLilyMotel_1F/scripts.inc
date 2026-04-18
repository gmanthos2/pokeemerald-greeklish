.set LOCALID_OWNER, 1

LilycoveCity_CoveLilyMotel_1F_MapScripts::
	.byte 0

LilycoveCity_CoveLilyMotel_1F_EventScript_MotelOwner::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_CoveLilyMotel_1F_EventScript_GameClear
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_CoveLilyMotel_1F_EventScript_AquaHideoutBusted
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_GuestsDoubledByMascot, MSGBOX_DEFAULT
	applymovement LOCALID_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_NoGuestsWithTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_AquaHideoutBusted::
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_MonFoundLostItem, MSGBOX_DEFAULT
	applymovement LOCALID_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_HeardAquaHideoutBusted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_GameClear::
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_HouseSittingMonCaughtBurglar, MSGBOX_DEFAULT
	applymovement LOCALID_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_BetterGetWorkingOnGuestsDinner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_BlockingTV::
	lockall
	playse SE_PIN
	applymovement LOCALID_OWNER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_OWNER, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_CantSeeTheTV, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveCity_CoveLilyMotel_1F_Movement_PlayerPushFromTV
	applymovement LOCALID_OWNER, LilycoveCity_CoveLilyMotel_1F_Movement_OwnerPushPlayer
	waitmovement 0
	applymovement LOCALID_OWNER, LilycoveCity_CoveLilyMotel_1F_Movement_OwnerReturn
	waitmovement 0
	release
	end

LilycoveCity_CoveLilyMotel_1F_Movement_PlayerPushFromTV:
	face_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

LilycoveCity_CoveLilyMotel_1F_Movement_OwnerPushPlayer:
	walk_up
	step_end

LilycoveCity_CoveLilyMotel_1F_Movement_OwnerReturn:
	face_down
	walk_down
	face_up
	step_end

LilycoveCity_CoveLilyMotel_1F_Text_GuestsDoubledByMascot:
	.string "Χμ, οπότε διπλασίασαν τους\n"
	.string "επισκέπτες χρησιμοποιώντας POKéMON;\p"
	.string "Χμ, λοιπόν, ίσως θα έπρεπε να \n"
	.string "κάνω ένα γλυκό POKéMON τη \l"
	.string "μασκότ μας.\p"
	.string "Αναρωτιέμαι αν αυτό θα προσελκύσει \n"
	.string "περισσότερους επισκέπτες να \l"
	.string "μείνουν μαζί μας;$"

LilycoveCity_CoveLilyMotel_1F_Text_NoGuestsWithTeamAqua:
	.string "Ω, συγγνώμη, συγγνώμη!\n"
	.string "Αφοσιώθηκα πάρα πολύ στην τηλεόραση!\p"
	.string "Από τότε που αυτή η TEAM AQUA ήρθε\n"
	.string "στην πόλη, οι τουρίστες μένουν μακριά.$"

LilycoveCity_CoveLilyMotel_1F_Text_CantSeeTheTV:
	.string "Ε, εκεί μπροστά!\n"
	.string "Δεν μπορώ να δω την τηλεόραση!$"

LilycoveCity_CoveLilyMotel_1F_Text_MonFoundLostItem:
	.string "Εκπληκτικό! Μου λες ότι ένα POKéMON\n"
	.string "βρήκε το χαμένο αντικείμενο \l"
	.string "κάποιου;\p"
	.string "Αυτό είναι κάτι. Αν είχαμε \n"
	.string "κάποια έξυπνα POKéMON σαν \l"
	.string "κι αυτό…\p"
	.string "Θα μπορούσαμε να ανακτήσουμε \n"
	.string "οτιδήποτε έχουν χάσει οι \l"
	.string "επισκέπτες μας…$"

LilycoveCity_CoveLilyMotel_1F_Text_HeardAquaHideoutBusted:
	.string "Ω, συγγνώμη, συγγνώμη!\n"
	.string "Αφοσιώθηκα πάρα πολύ στην τηλεόραση!\p"
	.string "Άκουσα ότι κάποιος διέλυσε\n"
	.string "το HIDEOUT της TEAM AQUA.\p"
	.string "Χάρη σ' αυτό, μόλις κλείσαμε μια\n"
	.string "κράτηση από μια μεγάλη ομάδα.\p"
	.string "Ήταν μια εταιρεία που λεγόταν… Ε…\n"
	.string "GAME κάτι…$"

LilycoveCity_CoveLilyMotel_1F_Text_HouseSittingMonCaughtBurglar:
	.string "Καταπληκτικό! Ένα POKéMON \n"
	.string "φύλακας έπιασε έναν διαρρήκτη;\p"
	.string "Αυτό είναι κάτι. Αν είχαμε ένα\n"
	.string "σκληρό POKéMON ως φύλακα…\p"
	.string "Θα μπορούσαμε να παρέχουμε στους\n"
	.string "πελάτες μας μεγαλύτερη ασφάλεια.$"

LilycoveCity_CoveLilyMotel_1F_Text_BetterGetWorkingOnGuestsDinner:
	.string "Ω, συγγνώμη, συγγνώμη!\n"
	.string "Ήμουν απορροφημένη στην τηλεόραση.\p"
	.string "Ω, ναι. Μια μεγάλη ομάδα επισκεπτών \n"
	.string "έφτασε πριν από λίγο.\p"
	.string "Κλείσανε ως GAME FREAK,\n"
	.string "οπότε υποθέτω ότι φτιάχνουν \l"
	.string "παιχνίδια.\p"
	.string "Ωχ, καλύτερα να πιάσω δουλειά για \n"
	.string "το δείπνο τους!$"

