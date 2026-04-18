MossdeepCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MossdeepCity_Gym_OnLoad
	.byte 0

@ NOTE: Mossdeep Gym was redesigned between R/S and E. Leftover (and now functionally unused) scripts are commented below

@ All the below checks are leftover from RS. FLAG_MOSSDEEP_GYM_SWITCH_X is never set
MossdeepCity_Gym_OnLoad:
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_SetSwitch1Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_CheckSwitch2::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_SetSwitch2Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_CheckSwitch3::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_SetSwitch3Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_CheckSwitch4::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_SetSwitch4Metatiles
	end

@ All the below set metatile scripts are leftover from RS and are functionally unused
MossdeepCity_Gym_EventScript_SetSwitch1Metatiles::
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_SetSwitch2Metatiles::
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_SetSwitch3Metatiles::
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_SetSwitch4Metatiles::
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	end

MossdeepCity_Gym_EventScript_TateAndLiza::
	trainerbattle_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaIntro, MossdeepCity_Gym_Text_TateAndLizaDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons, MossdeepCity_Gym_EventScript_TateAndLizaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MossdeepCity_Gym_EventScript_TateAndLizaRematch
	goto_if_unset FLAG_RECEIVED_TM_CALM_MIND, MossdeepCity_Gym_EventScript_GiveCalmMind2
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_TateAndLizaDefeated::
	message MossdeepCity_Gym_Text_ReceivedMindBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_MOSSDEEP_GYM
	setflag FLAG_BADGE07_GET
	setflag FLAG_HIDE_AQUA_HIDEOUT_GRUNTS
	clearflag FLAG_HIDE_SLATEPORT_CITY_STERNS_SHIPYARD_MR_BRINEY
	clearflag FLAG_UNKNOWN_0x393
	setvar VAR_0x8008, 7
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_PATRONS
	clearflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_STEVEN
	setvar VAR_MOSSDEEP_CITY_STATE, 1
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_STEVEN
	setvar VAR_MOSSDEEP_SPACE_CENTER_STATE, 1
	call MossdeepCity_Gym_EventScript_GiveCalmMind
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MossdeepCity_Gym_Text_RegisteredTateAndLiza, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_TATE_AND_LIZA_MATCH_CALL
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind2::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	return

MossdeepCity_Gym_EventScript_TateAndLizaRematch::
	trainerbattle_rematch_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaPreRematch, MossdeepCity_Gym_Text_TateAndLizaRematchDefeat, MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostRematch, MSGBOX_AUTOCLOSE
	end

@ All the below switch scripts are leftover from RS and are functionally unused
MossdeepCity_Gym_EventScript_Switch1::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_ClearSwitch1
	setflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed::
	special DrawWholeMapView
	playse SE_CLICK
	releaseall
	end

MossdeepCity_Gym_EventScript_ClearSwitch1::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch2::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_ClearSwitch2
	setflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch2::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Down, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch3::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_ClearSwitch3
	setflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch3::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch4::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_ClearSwitch4
	setflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch4::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_WarpToEntrance::
	lockall
	warpmossdeepgym MAP_MOSSDEEP_CITY_GYM, 7, 30
	waitstate
	releaseall
	end

MossdeepCity_Gym_EventScript_Preston::
	trainerbattle_single TRAINER_PRESTON, MossdeepCity_Gym_Text_PrestonIntro, MossdeepCity_Gym_Text_PrestonDefeat
	msgbox MossdeepCity_Gym_Text_PrestonPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Virgil::
	trainerbattle_single TRAINER_VIRGIL, MossdeepCity_Gym_Text_VirgilIntro, MossdeepCity_Gym_Text_VirgilDefeat
	msgbox MossdeepCity_Gym_Text_VirgilPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Blake::
	trainerbattle_single TRAINER_BLAKE, MossdeepCity_Gym_Text_BlakeIntro, MossdeepCity_Gym_Text_BlakeDefeat
	msgbox MossdeepCity_Gym_Text_BlakePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Hannah::
	trainerbattle_single TRAINER_HANNAH, MossdeepCity_Gym_Text_HannahIntro, MossdeepCity_Gym_Text_HannahDefeat
	msgbox MossdeepCity_Gym_Text_HannahPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Samantha::
	trainerbattle_single TRAINER_SAMANTHA, MossdeepCity_Gym_Text_SamanthaIntro, MossdeepCity_Gym_Text_SamanthaDefeat
	msgbox MossdeepCity_Gym_Text_SamanthaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Maura::
	trainerbattle_single TRAINER_MAURA, MossdeepCity_Gym_Text_MauraIntro, MossdeepCity_Gym_Text_MauraDefeat
	msgbox MossdeepCity_Gym_Text_MauraPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Sylvia::
	trainerbattle_single TRAINER_SYLVIA, MossdeepCity_Gym_Text_SylviaIntro, MossdeepCity_Gym_Text_SylviaDefeat
	msgbox MossdeepCity_Gym_Text_SylviaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nate::
	trainerbattle_single TRAINER_NATE, MossdeepCity_Gym_Text_NateIntro, MossdeepCity_Gym_Text_NateDefeat
	msgbox MossdeepCity_Gym_Text_NatePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Macey::
	trainerbattle_single TRAINER_MACEY, MossdeepCity_Gym_Text_MaceyIntro, MossdeepCity_Gym_Text_MaceyDefeat
	msgbox MossdeepCity_Gym_Text_MaceyPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Clifford::
	trainerbattle_single TRAINER_CLIFFORD, MossdeepCity_Gym_Text_CliffordIntro, MossdeepCity_Gym_Text_CliffordDefeat
	msgbox MossdeepCity_Gym_Text_CliffordPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nicholas::
	trainerbattle_single TRAINER_NICHOLAS, MossdeepCity_Gym_Text_NicholasIntro, MossdeepCity_Gym_Text_NicholasDefeat
	msgbox MossdeepCity_Gym_Text_NicholasPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Kathleen::
	trainerbattle_single TRAINER_KATHLEEN, MossdeepCity_Gym_Text_KathleenIntro, MossdeepCity_Gym_Text_KathleenDefeat
	msgbox MossdeepCity_Gym_Text_KathleenPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MOSSDEEP_GYM, MossdeepCity_Gym_EventScript_GymGuidePostVictory
	msgbox MossdeepCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_GymGuidePostVictory::
	msgbox MossdeepCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

@ Leftover from RS, functionally unused
MossdeepCity_Gym_Movement_WaitAfterSwitchUse:
	delay_16
	delay_16
	step_end

MossdeepCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_GymStatueCertified::
	msgbox MossdeepCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_GymStatue::
	msgbox MossdeepCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_YellowFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 0
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_BlueFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 1
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_GreenFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 2
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_PurpleFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 3
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_RedFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 4
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_Text_GymGuideAdvice:
	.string "Yo, πώς πάει, μελλοντικέ CHAMPION \n"
	.string "{PLAYER};\p"
	.string "Οι GYM LEADERS εδώ χρησιμοποιούν \n"
	.string "POKéMON τύπου PSYCHIC.\p"
	.string "Αν τους αντιμετωπίσεις με POKéMON \n"
	.string "τύπου FIGHTING ή POISON, θα σου \l"
	.string "προκαλέσουν τρομερή ζημιά!\p"
	.string "Επιπλέον, θα σου επιτεθούν με \n"
	.string "εκπληκτικές συνδυαστικές επιθέσεις.\p"
	.string "Αν θες να νικήσεις, θα πρέπει να \n"
	.string "τους δείξεις πόσο δεμένος είσαι με \l"
	.string "τα POKéMON σου. Δώσε τα όλα!$"

MossdeepCity_Gym_Text_GymGuidePostVictory:
	.string "Ουάου, είσαι καταπληκτικός!\n"
	.string "Είσαι ένας σπουδαίος TRAINER!$"

MossdeepCity_Gym_Text_PrestonIntro:
	.string "Οι μάχες κρίνονται από τη δύναμη \n"
	.string "του πνεύματός σου! Οι αδύναμοι στο \l"
	.string "πνεύμα δεν θα νικήσουν ποτέ!$"

MossdeepCity_Gym_Text_PrestonDefeat:
	.string "Έχασα!\n"
	.string "Πρέπει να ατσαλώσω το πνεύμα μου!$"

MossdeepCity_Gym_Text_PrestonPostBattle:
	.string "Οι αναποφάσιστοι χάνουν.\n"
	.string "Αυτή είναι η προειδοποίησή μου.$"

MossdeepCity_Gym_Text_VirgilIntro:
	.string "Δείξε μου το ταλέντο σου!$"

MossdeepCity_Gym_Text_VirgilDefeat:
	.string "Διαθέτεις θεαματικό ταλέντο!$"

MossdeepCity_Gym_Text_VirgilPostBattle:
	.string "Αν υπάρχουν θαύματα στον κόσμο, \n"
	.string "τότε οι GYM LEADERS μας είναι \l"
	.string "ένα από αυτά!\p"
	.string "Ωστόσο, εσύ μπορεί να είσαι ακόμα \n"
	.string "πιο ταλαντούχος από αυτούς…$"

MossdeepCity_Gym_Text_BlakeIntro:
	.string "Φουφουφου… Δες με που αιωρώ μια \n"
	.string "POKé BALL τηλεκινητικά!\p"
	.string "Bροοοοοοοοοοαρ!\n"
	.string "… … … … … … …\p"
	.string "Μερικές φορές, είμαι εκτός \n"
	.string "συντονισμού…$"

MossdeepCity_Gym_Text_BlakeDefeat:
	.string "Οι ικανότητές μου στη μάχη POKéMON \n"
	.string "είναι επίσης εκτός συντονισμού!$"

MossdeepCity_Gym_Text_BlakePostBattle:
	.string "Μια POKé BALL ήταν πολύ βαριά για \n"
	.string "να την σηκώσω ψυχικά. Αλλά αυτό \l"
	.string "το χνούδι…\p"
	.string "Oυοοοοοοοοοοοοο!\n"
	.string "… … … … … …\p"
	.string "Όχι, δεν κλέβω!\n"
	.string "Δεν το φύσηξα! Ειλικρινά!$"

MossdeepCity_Gym_Text_HannahIntro:
	.string "Όταν χάσεις από μένα, μην είσαι \n"
	.string "πολύ σκληρός με τον εαυτό σου.\p"
	.string "Δεν είναι ότι είσαι αδύναμος--απλώς\n"
	.string "εγώ είμαι πολύ δυνατή!$"

MossdeepCity_Gym_Text_HannahDefeat:
	.string "Είσαι απλά πολύ δυνατός!$"

MossdeepCity_Gym_Text_HannahPostBattle:
	.string "Δεν πρόκειται να απογοητευτώ \n"
	.string "που έχασα. Απλώς πρέπει να \l"
	.string "προπονηθώ πιο σκληρά.\p"
	.string "Θετική σκέψη--αυτό είναι το δυνατό \n"
	.string "μου σημείο!$"

MossdeepCity_Gym_Text_SamanthaIntro:
	.string "Το βλέπω…\n"
	.string "Βλέπω το μέλλον σου…\p"
	.string "Αν μπορέσεις να με νικήσεις, θα σου \n"
	.string "πω το μέλλον σου!$"

MossdeepCity_Gym_Text_SamanthaDefeat:
	.string "Παραδίδομαι!$"

MossdeepCity_Gym_Text_SamanthaPostBattle:
	.string "Θα δώσεις μια τρομερά έντονη μάχη \n"
	.string "με τους GYM LEADERS μας…\p"
	.string "Το αποτέλεσμα…\n"
	.string "Δεν θα το ακούσεις από μένα!$"

MossdeepCity_Gym_Text_MauraIntro:
	.string "Οι δρόμοι που έχεις διανύσει…\n"
	.string "Αυτά που έχεις βιώσει…\p"
	.string "Έλα πάνω μου με όλα όσα \n"
	.string "έχεις μάθει!$"

MossdeepCity_Gym_Text_MauraDefeat:
	.string "Έχεις διανύσει ένα μονοπάτι \n"
	.string "μεγαλείου!$"

MossdeepCity_Gym_Text_MauraPostBattle:
	.string "Ένα λαμπρό μέλλον περιμένει όσους \n"
	.string "εργάστηκαν επιμελώς.\p"
	.string "Για όσους τεμπέλιαζαν, υπάρχει μόνο \n"
	.string "απόγνωση στο τέλος.\p"
	.string "Ό,τι σπέρνεις, θερίζεις…$"

MossdeepCity_Gym_Text_SylviaIntro:
	.string "Ακόμα και με κίνδυνο της ζωής μου, \n"
	.string "θα κερδίσω αυτή τη μάχη!$"

MossdeepCity_Gym_Text_SylviaDefeat:
	.string "Αυτό που κάνεις…\n"
	.string "Με τρομάζει…$"

MossdeepCity_Gym_Text_SylviaPostBattle:
	.string "Πώς τολμάς να με νικήσεις…\p"
	.string "Δεν θα φταίω εγώ αν σου συμβεί \n"
	.string "κάτι φρικτό…$"

MossdeepCity_Gym_Text_NateIntro:
	.string "Χοχοχο.\p"
	.string "Πρέπει να σου δείξω πόσο επίμονος \n"
	.string "μπορεί να είναι ο τύπος PSYCHIC.$"

MossdeepCity_Gym_Text_NateDefeat:
	.string "Ω! Κοίτα να δεις!\n"
	.string "Το στυλ μάχης σου είναι φανταστικό!$"

MossdeepCity_Gym_Text_NatePostBattle:
	.string "Εγώ… δεν αφήνω την ήττα να με \n"
	.string "ταράξει, όσο άσχημη κι αν είναι.$"

MossdeepCity_Gym_Text_KathleenIntro:
	.string "Άσε με να σου δείξω μια απόλυτα \n"
	.string "φρικτή και τρομακτική στιγμή!$"

MossdeepCity_Gym_Text_KathleenDefeat:
	.string "Ό-όχιαααα!$"

MossdeepCity_Gym_Text_KathleenPostBattle:
	.string "Η ζωτικότητά σου είναι κολλητική!\n"
	.string "Φύγε μακριά μου γρήγορα!$"

MossdeepCity_Gym_Text_CliffordIntro:
	.string "Μπορεί να πέρασαν τα χρόνια μου, \n"
	.string "αλλά σου προτείνω να μη με \l"
	.string "υποτιμάς.$"

MossdeepCity_Gym_Text_CliffordDefeat:
	.string "Αχ, ξεχειλίζεις από τη δύναμη \n"
	.string "της νιότης!$"

MossdeepCity_Gym_Text_CliffordPostBattle:
	.string "Φαίνεται ότι δεν μπόρεσα να \n"
	.string "νικήσω τη νεανική σου ενέργεια.$"

MossdeepCity_Gym_Text_MaceyIntro:
	.string "Δεν θα φτάσεις μέχρι το τέλος!\n"
	.string "Όχι αν μπορώ να το εμποδίσω!$"

MossdeepCity_Gym_Text_MaceyDefeat:
	.string "Πώς θα μπορούσες να είσαι τόσο \n"
	.string "παράλογα δυνατός;$"

MossdeepCity_Gym_Text_MaceyPostBattle:
	.string "Χμ! Μπορεί να είσαι δυνατός, αλλά \n"
	.string "δεν κάνεις για τον τύπο PSYCHIC!\p"
	.string "Ο τρόπος που παλεύεις είναι \n"
	.string "κάπως κτηνώδης!$"

MossdeepCity_Gym_Text_NicholasIntro:
	.string "Bροοοαρ! Πάρε μια γεύση από τη σούπερ \n"
	.string "δύναμη POKéMON μου!$"

MossdeepCity_Gym_Text_NicholasDefeat:
	.string "Ω!\n"
	.string "Τέλειωσα!$"

MossdeepCity_Gym_Text_NicholasPostBattle:
	.string "Εντάξει! Νομίζω ότι θα αναπτύξω μια \n"
	.string "ειδική ανίκητη δύναμη POKéMON μετά.$"

MossdeepCity_Gym_Text_TateAndLizaIntro:
	.string "TATE: Χεχεχε… εξεπλάγης;\p"
	.string "LIZA: Φουφουφου… εξεπλάγης;\p"
	.string "TATE: Που υπάρχουν δύο GYM LEADERS;\n"
	.string "LIZA: Που υπάρχουν δύο GYM LEADERS;\p"
	.string "TATE: Είμαστε δίδυμα!\n"
	.string "LIZA: Είμαστε δίδυμα!\p"
	.string "TATE: Δεν χρειάζεται να μιλάμε γιατί…\n"
	.string "LIZA: Ο καθένας μας μπορεί να ξέρει…\p"
	.string "TATE: Τι σκέφτεται ο άλλος…\n"
	.string "LIZA: Όλα στο μυαλό μας!\p"
	.string "TATE: Αυτόν τον συνδυασμό μας…\n"
	.string "LIZA: Μπορείς να τον νικήσεις;$"

MossdeepCity_Gym_Text_TateAndLizaDefeat:
	.string "TATE: Τι;! Ο συνδυασμός μας…\n"
	.string "LIZA: Συντρίφθηκε!\p"
	.string "TATE: Δεν πειράζει. Νίκησες…\n"
	.string "LIZA: Οπότε, ως αναγνώριση, πάρε αυτό.$"

MossdeepCity_Gym_Text_ReceivedMindBadge:
	.string "Το {PLAYER} έλαβε το MIND BADGE\n"
	.string "από τους TATE και LIZA.$"

MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis:
	.string "TATE: Το MIND BADGE ενισχύει το\n"
	.string "SP. ATK και το SP. DEF των POKéMON.\p"
	.string "LIZA: Σου επιτρέπει επίσης να \n"
	.string "χρησιμοποιείς το HM DIVE \l"
	.string "έξω από τη μάχη.\p"
	.string "TATE: Θα πρέπει να πάρεις και \n"
	.string "αυτό, επίσης.$"

MossdeepCity_Gym_Text_ExplainCalmMind:
	.string "TATE: Αυτό το TM04 περιέχει…\n"
	.string "LIZA: Την κίνηση CALM MIND!\p"
	.string "TATE: Αυξάνει το SP. ATK και…\n"
	.string "LIZA: Αυξάνει το SP. DEF!\p"
	.string "TATE: Είναι μια κίνηση τέλεια…\n"
	.string "LIZA: Για POKéMON τύπου PSYCHIC!\p"
	.string "… … … … … …$"

MossdeepCity_Gym_Text_RegisteredTateAndLiza:
	.string "Οι GYM LEADERS TATE & LIZA \n"
	.string "καταχωρήθηκαν στο POKéNAV.$"

MossdeepCity_Gym_Text_TateAndLizaPostBattle:
	.string "TATE: Φαίνεται ότι ο δεσμός ανάμεσα \n"
	.string "σε εσένα και τα POKéMON σου είναι \l"
	.string "πολύ ισχυρότερος από τον δεσμό που \l"
	.string "μοιραζόμαστε εμείς ως δίδυμα.\p"
	.string "LIZA: Θα γίνεις ακόμα πιο δυνατός!\n"
	.string "Σε παλέψαμε, οπότε το ξέρουμε.$"

MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons:
	.string "TATE: Χεχεχε… εξεπλάγης;\p"
	.string "LIZA: Που υπάρχουν δύο GYM LEADERS;\p"
	.string "TATE: Ωχ, έχεις μόνο ένα…\n"
	.string "LIZA: POKéMON που μπορεί να παλέψει.\p"
	.string "TATE: Δεν μπορούμε να παλέψουμε έτσι!\p"
	.string "LIZA: Αν θες να μας προκαλέσεις, \n"
	.string "φέρε κι άλλα POKéMON.$"

MossdeepCity_Gym_Text_GymStatue:
	.string "MOSSDEEP CITY POKéMON GYM$"

MossdeepCity_Gym_Text_GymStatueCertified:
	.string "MOSSDEEP CITY POKéMON GYM\p"
	.string "ΠΙΣΤΟΠΟΙΗΜΕΝΟΙ TRAINERS ΤΩΝ \n"
	.string "LIZA ΚΑΙ TATE: {PLAYER}$"

MossdeepCity_Gym_Text_TateAndLizaPreRematch:
	.string "TATE: POKéMON…\n"
	.string "LIZA: POKéMON…\p"
	.string "TATE: Αλλάζοντας τη σύνθεση…\n"
	.string "LIZA: Το στυλ μάχης αλλάζει.\p"
	.string "TATE: Αλλά εγώ…\n"
	.string "LIZA: Αλλά εγώ…\p"
	.string "TATE: Θα είμαι πάντα με τη LIZA!\n"
	.string "LIZA: Θα είμαι πάντα με τον TATE!\p"
	.string "TATE: Τον συνδυασμό μας…\n"
	.string "LIZA: Θα τον δείχνουμε ξανά και ξανά!$"

MossdeepCity_Gym_Text_TateAndLizaRematchDefeat:
	.string "TATE: Εσύ και τα POKéMON σου…\n"
	.string "LIZA: Είναι σαν να είστε αδέρφια!$"

MossdeepCity_Gym_Text_TateAndLizaPostRematch:
	.string "TATE: Μπορείς να μας ρίξεις κάτω,\n"
	.string "αλλά δεν θα μείνουμε κάτω!\p"
	.string "LIZA: Επειδή οι δυο μας,\n"
	.string "πάντα υποστηρίζουμε ο ένας τον άλλο!$"

MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons:
	.string "TATE: Επέστρεψες πάλι…\n"
	.string "LIZA: Επέστρεψες πάλι…\p"
	.string "TATE: Για να ζητήσεις ρεβάνς.\n"
	.string "LIZA: Για να ζητήσεις ρεβάνς.\p"
	.string "TATE: Αλλά…\n"
	.string "LIZA: Για τη μάχη μας…\p"
	.string "TATE: Έφερες μόνο ένα POKéMON!\n"
	.string "LIZA: Έφερες μόνο ένα POKéMON!\p"
	.string "TATE: Πρέπει να φέρεις τουλάχιστον…\n"
	.string "LIZA: Δύο POKéMON όταν επιστρέψεις.$"
