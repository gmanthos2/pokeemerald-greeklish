AquaHideout_1F_MapScripts::
	.byte 0

@ The below two entrance guards give hints about what to do to progress the story
AquaHideout_1F_EventScript_HideoutEntranceGrunt1::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint1
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint1
	msgbox AquaHideout_1F_Text_OurBossIsSnatchingSomething, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint1::
	msgbox AquaHideout_1F_Text_WhereMightMagmaHideoutBe, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint1::
	msgbox AquaHideout_1F_Text_BossWentToJackASubmarine, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_HideoutEntranceGrunt2::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint2
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint2
	msgbox AquaHideout_1F_Text_BossIsOnRoute122, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint2::
	msgbox AquaHideout_1F_Text_TeamMagmaAtMtChimney, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint2::
	msgbox AquaHideout_1F_Text_BossIsInSlateportCity, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_1, AquaHideout_1F_Text_Grunt1Intro, AquaHideout_1F_Text_Grunt1Defeat, AquaHideout_1F_EventScript_Grunt1Defeated
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_1F_EventScript_Grunt1Defeated::
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_Text_OurBossIsSnatchingSomething:
	.string "Τι; Τι; Τι θέλεις από την\n"
	.string "TEAM AQUA;\p"
	.string "Ο BOSS μας λείπει! Έφυγε για να\n"
	.string "αρπάξει κάτι πολύ σημαντικό!\p"
	.string "… …\n"
	.string "Πού πήγε;\p"
	.string "Μπαχαχα! Πιστεύεις ότι θα σου πω κάτι\n"
	.string "τόσο κρίσιμο;$"

AquaHideout_1F_Text_WhereMightMagmaHideoutBe:
	.string "Τι; Τι;\n"
	.string "Είσαι μέλος της TEAM MAGMA;\p"
	.string "Άκουσα ότι η TEAM MAGMA προσπαθεί να\n"
	.string "ξυπνήσει ένα φοβερό POKéMON στο\l"
	.string "HIDEOUT τους.\p"
	.string "Πού να είναι άραγε το HIDEOUT τους;$"

AquaHideout_1F_Text_BossWentToJackASubmarine:
	.string "Τι; Τι; Τι θέλεις από την\n"
	.string "TEAM AQUA;\p"
	.string "Ο BOSS μας λείπει!\n"
	.string "Έφυγε για να κλέψει ένα υποβρύχιο!\p"
	.string "… …\n"
	.string "Πού πήγε;\p"
	.string "Μπαχαχα! Πιστεύεις ότι θα σου πω κάτι\n"
	.string "τόσο κρίσιμο;$"

AquaHideout_1F_Text_BossIsOnRoute122:
	.string "Τι; Τι; Τι θέλεις από την\n"
	.string "TEAM AQUA;\p"
	.string "Ο BOSS μας δεν είναι εδώ! Πηγαίνει\n"
	.string "στο MT. PYRE, στην ROUTE 122!\p"
	.string "… …\n"
	.string "Γιατί πήγε;\p"
	.string "Μπαχαχα! Πιστεύεις ότι θα σου πω κάτι\n"
	.string "τόσο κρίσιμο;$"

AquaHideout_1F_Text_TeamMagmaAtMtChimney:
	.string "Τι; Τι;\n"
	.string "Είσαι μέλος της TEAM MAGMA;\p"
	.string "Άκουσα ότι η TEAM MAGMA κυνηγάει ένα\n"
	.string "τρομερό POKéMON στο MT. CHIMNEY.\p"
	.string "Αλλά πώς να είναι αυτό το POKéMON;$"

AquaHideout_1F_Text_BossIsInSlateportCity:
	.string "Τι; Τι; Τι θέλεις από την\n"
	.string "TEAM AQUA;\p"
	.string "Ο BOSS μας λείπει!\n"
	.string "Κατευθύνεται στην SLATEPORT CITY!\p"
	.string "… …\n"
	.string "Γιατί πήγε;\p"
	.string "Μπαχαχα! Πιστεύεις ότι θα σου πω κάτι\n"
	.string "τόσο κρίσιμο;$"

AquaHideout_1F_Text_Grunt1Intro:
	.string "Αγιγιγι!\n"
	.string "Εντοπίστηκε ύποπτο άτομο!$"

AquaHideout_1F_Text_Grunt1Defeat:
	.string "Γκρρρρ…\n"
	.string "Έχασα!$"

AquaHideout_1F_Text_Grunt1PostBattle:
	.string "Έχασα για χάρη της TEAM, αλλά\n"
	.string "τουλάχιστον έκανα τη δουλειά μου…$"

