MauvilleCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MauvilleCity_Gym_OnLoad
	.byte 0

MauvilleCity_Gym_OnLoad:
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_DeactivatePuzzle
	switch VAR_MAUVILLE_GYM_STATE
	case 0, MauvilleCity_Gym_EventScript_UpdateBarriers
	case 1, MauvilleCity_Gym_EventScript_Switch1Pressed
	case 2, MauvilleCity_Gym_EventScript_Switch2Pressed
	case 3, MauvilleCity_Gym_EventScript_Switch3Pressed
	case 4, MauvilleCity_Gym_EventScript_Switch4Pressed
	end

MauvilleCity_Gym_EventScript_UpdateBarriers::
	goto_if_set FLAG_MAUVILLE_GYM_BARRIERS_STATE, MauvilleCity_Gym_EventScript_SetAltBarriers
	end

MauvilleCity_Gym_EventScript_SetAltBarriers::
	setmetatile 3, 11, METATILE_MauvilleGym_RedBeamV1_On, TRUE
	setmetatile 3, 12, METATILE_MauvilleGym_RedBeamV2_On, TRUE
	setmetatile 3, 13, METATILE_MauvilleGym_PoleTop_On, TRUE
	setmetatile 4, 10, METATILE_MauvilleGym_RedBeamH1_On, FALSE
	setmetatile 5, 10, METATILE_MauvilleGym_RedBeamH2_On, FALSE
	setmetatile 4, 11, METATILE_MauvilleGym_RedBeamH3_On, TRUE
	setmetatile 5, 11, METATILE_MauvilleGym_RedBeamH4_On, TRUE
	setmetatile 7, 10, METATILE_MauvilleGym_RedBeamH1_On, FALSE
	setmetatile 8, 10, METATILE_MauvilleGym_RedBeamH2_On, FALSE
	setmetatile 7, 11, METATILE_MauvilleGym_RedBeamH3_On, TRUE
	setmetatile 8, 11, METATILE_MauvilleGym_RedBeamH4_On, TRUE
	setmetatile 4, 13, METATILE_MauvilleGym_GreenBeamH1_Off, FALSE
	setmetatile 5, 13, METATILE_MauvilleGym_GreenBeamH2_Off, FALSE
	setmetatile 4, 14, METATILE_MauvilleGym_GreenBeamH3_Off, FALSE
	setmetatile 5, 14, METATILE_MauvilleGym_GreenBeamH4_Off, FALSE
	setmetatile 1, 10, METATILE_MauvilleGym_GreenBeamH1_Off, FALSE
	setmetatile 2, 10, METATILE_MauvilleGym_GreenBeamH2_Off, FALSE
	setmetatile 1, 11, METATILE_MauvilleGym_GreenBeamH3_Off, FALSE
	setmetatile 2, 11, METATILE_MauvilleGym_GreenBeamH4_Off, FALSE
	setmetatile 6, 8, METATILE_MauvilleGym_PoleBottom_On, TRUE
	setmetatile 6, 9, METATILE_MauvilleGym_FloorTile, FALSE
	setmetatile 6, 10, METATILE_MauvilleGym_PoleTop_Off, FALSE
	setmetatile 4, 6, METATILE_MauvilleGym_GreenBeamH1_Off, FALSE
	setmetatile 5, 6, METATILE_MauvilleGym_GreenBeamH2_Off, FALSE
	setmetatile 4, 7, METATILE_MauvilleGym_GreenBeamH3_Off, FALSE
	setmetatile 5, 7, METATILE_MauvilleGym_GreenBeamH4_Off, FALSE
	end

MauvilleCity_Gym_EventScript_Switch1Pressed::
	setvar VAR_0x8004, 0
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_Switch2Pressed::
	setvar VAR_0x8004, 1
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_Switch3Pressed::
	setvar VAR_0x8004, 2
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_Switch4Pressed::
	setvar VAR_0x8004, 3
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_DeactivatePuzzle::
	special MauvilleGymDeactivatePuzzle
	end

MauvilleCity_Gym_EventScript_Wattson::
	trainerbattle_single TRAINER_WATTSON_1, MauvilleCity_Gym_Text_WattsonIntro, MauvilleCity_Gym_Text_WattsonDefeat, MauvilleCity_Gym_EventScript_WattsonDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_Gym_EventScript_WattsonRematch
	goto_if_unset FLAG_RECEIVED_TM_SHOCK_WAVE, MauvilleCity_Gym_EventScript_GiveShockWave2
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, MauvilleCity_Gym_EventScript_CompletedNewMauville
	msgbox MauvilleCity_Gym_Text_WattsonPostBattle, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_WattsonDefeated::
	message MauvilleCity_Gym_Text_ReceivedDynamoBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MauvilleCity_Gym_Text_ExplainDynamoBadgeTakeThis, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 3
	clearflag FLAG_HIDE_VERDANTURF_TOWN_SCOTT
	setflag FLAG_DEFEATED_MAUVILLE_GYM
	setflag FLAG_BADGE03_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 3
	call Common_EventScript_SetGymTrainers
	special MauvilleGymDeactivatePuzzle
	special DrawWholeMapView
	playse SE_UNLOCK
	call MauvilleCity_Gym_EventScript_GiveShockWave
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Gym_Text_RegisteredWattson, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WATTSON_MATCH_CALL
	release
	end

MauvilleCity_Gym_EventScript_GiveShockWave2::
	giveitem ITEM_TM_SHOCK_WAVE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox MauvilleCity_Gym_Text_ExplainShockWave, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_SHOCK_WAVE
	release
	end

MauvilleCity_Gym_EventScript_GiveShockWave::
	giveitem ITEM_TM_SHOCK_WAVE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox MauvilleCity_Gym_Text_ExplainShockWave, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_SHOCK_WAVE
	return

MauvilleCity_Gym_EventScript_CompletedNewMauville::
	msgbox MauvilleCity_Gym_Text_WattsonGoForthAndEndeavor, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_WattsonRematch::
	trainerbattle_rematch_double TRAINER_WATTSON_1, MauvilleCity_Gym_Text_WattsonPreRematch, MauvilleCity_Gym_Text_WattsonRematchDefeat, MauvilleCity_Gym_Text_WattsonRematchNeedTwoMons
	msgbox MauvilleCity_Gym_Text_WattsonPostRematch, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Switch1::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 1, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 1
	setvar VAR_0x8004, 0
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_Switch2::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 2, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 2
	setvar VAR_0x8004, 1
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_Switch3::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 3, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 3
	setvar VAR_0x8004, 2
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_Switch4::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 4, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 4
	setvar VAR_0x8004, 3
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_PressFloorSwitch::
	special MauvilleGymSetDefaultBarriers
	special MauvilleGymPressSwitch
	special DrawWholeMapView
	playse SE_UNLOCK
	goto_if_set FLAG_MAUVILLE_GYM_BARRIERS_STATE, MauvilleCity_Gym_EventScript_ClearBarriersAltState
	goto_if_unset FLAG_MAUVILLE_GYM_BARRIERS_STATE, MauvilleCity_Gym_EventScript_SetBarriersAltState
	releaseall
	end

MauvilleCity_Gym_EventScript_SwitchDoNothing::
	releaseall
	end

MauvilleCity_Gym_EventScript_SetBarriersAltState::
	setflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	releaseall
	end

MauvilleCity_Gym_EventScript_ClearBarriersAltState::
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	releaseall
	end

MauvilleCity_Gym_EventScript_Kirk::
	trainerbattle_single TRAINER_KIRK, MauvilleCity_Gym_Text_KirkIntro, MauvilleCity_Gym_Text_KirkDefeat
	msgbox MauvilleCity_Gym_Text_KirkPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Shawn::
	trainerbattle_single TRAINER_SHAWN, MauvilleCity_Gym_Text_ShawnIntro, MauvilleCity_Gym_Text_ShawnDefeat
	msgbox MauvilleCity_Gym_Text_ShawnPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Ben::
	trainerbattle_single TRAINER_BEN, MauvilleCity_Gym_Text_BenIntro, MauvilleCity_Gym_Text_BenDefeat
	msgbox MauvilleCity_Gym_Text_BenPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Vivian::
	trainerbattle_single TRAINER_VIVIAN, MauvilleCity_Gym_Text_VivianIntro, MauvilleCity_Gym_Text_VivianDefeat
	msgbox MauvilleCity_Gym_Text_VivianPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Angelo::
	trainerbattle_single TRAINER_ANGELO, MauvilleCity_Gym_Text_AngeloIntro, MauvilleCity_Gym_Text_AngeloDefeat
	msgbox MauvilleCity_Gym_Text_AngeloPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_GymGuidePostVictory
	msgbox MauvilleCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_GymGuidePostVictory::
	msgbox MauvilleCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE03_GET, MauvilleCity_Gym_EventScript_GymStatueCertified
	goto MauvilleCity_Gym_EventScript_GymStatue
	end

MauvilleCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE03_GET, MauvilleCity_Gym_EventScript_GymStatueCertified
	goto MauvilleCity_Gym_EventScript_GymStatue
	end

MauvilleCity_Gym_EventScript_GymStatueCertified::
	msgbox MauvilleCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_Gym_EventScript_GymStatue::
	msgbox MauvilleCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_Gym_Text_GymGuideAdvice:
	.string "Ε, πώς πάει, μελλοντικέ CHAMPION\n"
	.string "{PLAYER};\p"
	.string "Ο WATTSON, o LEADER του MAUVILLE\n"
	.string "GYM, έχει ELECTRIC POKéMON.\p"
	.string "Εάν τον προκαλέσεις με WATER\n"
	.string "POKéMON, θα τα κάψει! Μπζζτ!\p"
	.string "Και, έχει βάλει πόρτες με διακόπτες\n"
	.string "σε όλο του το GYM! Εκκεντρικός!\p"
	.string "Πήγαινε για αυτό!$"

MauvilleCity_Gym_Text_GymGuidePostVictory:
	.string "Ουάου, είσαι ηλεκτρισμένος!\n"
	.string "Άνοιξες την πόρτα!$"

MauvilleCity_Gym_Text_KirkIntro:
	.string "Η ηλεκτρική μου ψυχή, θα συντρίψει\n"
	.string "τα όνειρα σου, ουόου-γιε!$"

MauvilleCity_Gym_Text_KirkDefeat:
	.string "Αυτό ήταν στην πρίζα, ενισχυμένο,\n"
	.string "στην τσίτα ηλεκτρικό φίλε μου!$"

MauvilleCity_Gym_Text_KirkPostBattle:
	.string "Tα POKéMON και το ροκ θέλουν\n"
	.string "καρδιά, ουόου-γιε!$"

MauvilleCity_Gym_Text_ShawnIntro:
	.string "Προπονήθηκα κάτω από τον WATTSON!\n"
	.string "Δεν υπάρχει περίπτωση να χάσω!$"

MauvilleCity_Gym_Text_ShawnDefeat:
	.string "Στην πρίζα και σβηστός…$"

MauvilleCity_Gym_Text_ShawnPostBattle:
	.string "Ο WATTSON, LEADER του GYM μας,\n"
	.string "είναι εδώ πολύ καιρό.\p"
	.string "Πάλευε ακόμα και πριν γεννηθεί ο\n"
	.string "πατέρας σου, ο σκληρός γέρος.$"

MauvilleCity_Gym_Text_BenIntro:
	.string "Αυτό το GYM έχει γρίφους!\n"
	.string "Δεν είναι διασκεδαστικό;$"

MauvilleCity_Gym_Text_BenDefeat:
	.string "Δεν είναι διασκεδαστικό να χάνεις…$"

MauvilleCity_Gym_Text_BenPostBattle:
	.string "Ο WATTSON λέει ότι του αρέσει να\n"
	.string "βάζει μικρές παγίδες με διακόπτες.$"

MauvilleCity_Gym_Text_VivianIntro:
	.string "Με τη γοητεία μου και τις κινήσεις \n"
	.string "των POKéMON μου, θα σοκαριστείς!$"

MauvilleCity_Gym_Text_VivianDefeat:
	.string "Είμαι συγκλονισμένη από τη δύναμή σου!$"

MauvilleCity_Gym_Text_VivianPostBattle:
	.string "Έχω ακούσει ότι το MAUVILLE ιδρύθηκε\n"
	.string "από τον WATTSON.\p"
	.string "Ήταν TRAINER πολύ πριν γίνουμε εμείς\n"
	.string "TRAINERS.\l"
	.string "Πρέπει να ξέρει κάθε είδους\l"
	.string "πράγματα!$"

MauvilleCity_Gym_Text_AngeloIntro:
	.string "Μου αρέσουν τα λαμπερά πράγματα!$"

MauvilleCity_Gym_Text_AngeloDefeat:
	.string "Ω…\n"
	.string "Τα μάτια μου τσουρουφλίζονται…$"

MauvilleCity_Gym_Text_AngeloPostBattle:
	.string "Ο WATTSON του MAUVILLE GYM\n"
	.string "έχει λαμπερό μέτωπο.\l"
	.string "Αυτό με κάνει χαρούμενο!$"

MauvilleCity_Gym_Text_WattsonIntro:
	.string "Παράτησα τα σχέδια μου να \n"
	.string "μετατρέψω την πόλη.\p"
	.string "Και έτσι, αφιερώνω το χρόνο μου \n"
	.string "για να φτιάξω πόρτες με\l"
	.string "παγίδες στο GYM μου.\p"
	.string "Ω; Τώρα, τι κάνεις εδώ;\p"
	.string "Τι είναι αυτό; Λες ότι πέρασες όλες\n"
	.string "τις πόρτες μου;\p"
	.string "Χαχαχαχα!\n"
	.string "Τώρα, αυτό είναι διασκεδαστικό!\p"
	.string "Τότε, εγώ, ο WATTSON, o LEADER\n"
	.string "του MAUVILLE GYM, \l"
	.string "θα σε ηλεκτρίσω!$"

MauvilleCity_Gym_Text_WattsonDefeat:
	.string "Χαχαχαχα!\n"
	.string "Καλά, έχασα!\p"
	.string "Μου έδωσες μια συγκίνηση!\n"
	.string "Πάρε αυτό το BADGE!$"

MauvilleCity_Gym_Text_ReceivedDynamoBadge:
	.string "To {PLAYER} πήρε το DYNAMO BADGE\n"
	.string "από τον WATTSON.$"

MauvilleCity_Gym_Text_ExplainDynamoBadgeTakeThis:
	.string "Με το DYNAMO BADGE, τα POKéMON\n"
	.string "σου μπορούν να χρησιμοποιήσουν \l"
	.string "το ROCK SMASH εκτός μάχης.\p"
	.string "Και, θα κάνει το POKéMON σας\n"
	.string "λίγο πιο γρήγορο, επίσης.\p"
	.string "Χμμ…\n"
	.string "Πρέπει να το πάρεις κι αυτό!$"

MauvilleCity_Gym_Text_ExplainShockWave:
	.string "Εκείνο το TM34 περιέχει \n"
	.string "το SHOCK WAVE.\p"
	.string "Είναι μια αξιόπιστη κίνηση που δεν\n"
	.string "αποτυγχάνει ποτέ! \l"
	.string "Μπορείς να υπολογίζεις σε αυτό!\p"
	.string "… … … … … …$"

MauvilleCity_Gym_Text_RegisteredWattson:
	.string "Καταχωρήθηκε o GYM LEADER WATTSON\n"
	.string "στο POKéNAV.$"

MauvilleCity_Gym_Text_WattsonPostBattle:
	.string "Γεμίζω με αισιοδοξία, \n"
	.string "βλέποντας έναν πολλά υποσχόμενο\l"
	.string "νεαρό TRAINER σαν εσένα!$"

MauvilleCity_Gym_Text_WattsonGoForthAndEndeavor:
	.string "Χαχαχαχα!\n"
	.string "Προχώρησε και προσπάθησε, μικρέ!$"

MauvilleCity_Gym_Text_GymStatue:
	.string "MAUVILLE CITY POKéMON GYM$"

MauvilleCity_Gym_Text_GymStatueCertified:
	.string "MAUVILLE CITY POKéMON GYM\p"
	.string "WATTSON'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"

MauvilleCity_Gym_Text_WattsonPreRematch:
	.string "WATTSON: Α-χα! Επιτέλους εδώ!\n"
	.string "Ξέρω τι θέλεις.\l"
	.string "Θέλεις να πολεμήσεις τα POKéMON μου!\p"
	.string "Χαχαχαχαχα!\p"
	.string "Θα κάνω σπίθες να πετάνε από πάνω σου!\n"
	.string "Μην πεις ότι δεν σε προειδοποίησα!$"

MauvilleCity_Gym_Text_WattsonRematchDefeat:
	.string "Ουφ…\n"
	.string "Στεγνώσαν οι μπαταρίες μας…$"

MauvilleCity_Gym_Text_WattsonPostRematch:
	.string "WATTSON: Θα πρέπει να φορτίσουμε \n"
	.string "πάλι τις μπαταρίες μας.\p"
	.string "Όταν φορτιστούμε πλήρως, \n"
	.string "θα δεχτούμε με χαρά την πρόκλησή σου.\p"
	.string "Οπότε, έλα πάλι κάποια στιγμή, \n"
	.string "δεν θα το κάνεις;$"

MauvilleCity_Gym_Text_WattsonRematchNeedTwoMons:
	.string "WATTSON: Α-χα! Επιτέλους εδώ!\n"
	.string "Ξέρω τι θέλεις.\l"
	.string "Θέλεις να πολεμήσεις τα POKéMON μου!\p"
	.string "Ουαχαχαχαχα!\p"
	.string "Ωπ! Περίμενε!\n"
	.string "Έχεις μόνο ένα POKéMON μαζί σου!\p"
	.string "Έλα να με δεις με δύο ή\n"
	.string "περισσότερα POKéMON, εντάξει;$"

