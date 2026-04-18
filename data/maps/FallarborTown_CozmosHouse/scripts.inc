FallarborTown_CozmosHouse_MapScripts::
	.byte 0

FallarborTown_CozmosHouse_EventScript_ProfCozmo::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_GaveMeteorite
	checkitem ITEM_METEORITE
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite::
	call_if_unset FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_NoticeMeteorite
	call_if_set FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_AskForMeteorite
	goto_if_eq VAR_RESULT, NO, FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite
	msgbox FallarborTown_CozmosHouse_Text_PleaseUseThisTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_RETURN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_0x8004, ITEM_METEORITE
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_RECEIVED_TM_RETURN
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_NoticeMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	msgbox FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_AskForMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MayIHaveMeteorite, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite::
	setflag FLAG_TEMP_2
	msgbox FallarborTown_CozmosHouse_Text_CrushedWithDisappointment, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_GaveMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmosWife::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_CozmoIsHappy
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_CozmosHouse_EventScript_CozmoIsSad
	msgbox FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsSad::
	msgbox FallarborTown_CozmosHouse_Text_FeelSorryForCozmo, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsHappy::
	msgbox FallarborTown_CozmosHouse_Text_CozmoIsSoHappy, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow:
	.string "PROF. COZMO: Αχ…\n"
	.string "Δεν έπρεπε ποτέ να αφήσω να με \l"
	.string "ξεγελάσουν λέγοντας στην TEAM MAGMA \l"
	.string "πού θα βρουν METEORITES…\p"
	.string "Αυτός ο METEORITE από το\n"
	.string "METEOR FALLS… Δεν θα γίνει δικός μου…$"

FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt:
	.string "Ω!\n"
	.string "Ε;\p"
	.string "Αυτό το αντικείμενο…\p"
	.string "Λες να είναι;\p"
	.string "Μήπως είναι ο METEORITE που \n"
	.string "πήρε η TEAM MAGMA;\p"
	.string "Σε παρακαλώ, μπορώ να τον έχω;\p"
	.string "Δεν το ζητάω δωρεάν.\n"
	.string "Τι θα έλεγες για αυτό το TM;$"

FallarborTown_CozmosHouse_Text_PleaseUseThisTM:
	.string "PROF. COZMO: Αυτό το TM, \n"
	.string "αντιπροσωπεύει την ευγνωμοσύνη μου.\l"
	.string "Σε παρακαλώ, χρησιμοποίησέ το!$"

FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch:
	.string "PROF. COZMO: Ω, δεν το πιστεύω.\n"
	.string "Αυτό είναι πραγματικά υπέροχο!\p"
	.string "Αυτό θα βοηθήσει πολύ την έρευνά μου!$"

FallarborTown_CozmosHouse_Text_CrushedWithDisappointment:
	.string "PROF. COZMO: Αχ, μα…\n"
	.string "Είμαι συντετριμμένος…$"

FallarborTown_CozmosHouse_Text_MayIHaveMeteorite:
	.string "PROF. COZMO: Σε παρακαλώ, μπορώ να\n"
	.string "έχω αυτόν τον METEORITE;\p"
	.string "Δεν τον ζητάω δωρεάν.\n"
	.string "Τι λες γι' ανταλλαγή με αυτό το TM;$"

FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls:
	.string "Ο PROF. COZMO πήγε στo METEOR FALLS \n"
	.string "στην ROUTE 114 με κάτι τύπους \l"
	.string "από την TEAM MAGMA.$"

FallarborTown_CozmosHouse_Text_FeelSorryForCozmo:
	.string "Καημένε PROF. COZMO…\n"
	.string "Είναι τόσο λυπημένος… Τον λυπάμαι.$"

FallarborTown_CozmosHouse_Text_CozmoIsSoHappy:
	.string "Κοίτα τον PROF. COZMO…\n"
	.string "Είναι τόσο χαρούμενος! Είναι γλυκό.$"

