BattleFrontier_BattlePyramidFloor_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattlePyramidFloor_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidFloor_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePyramidFloor_OnTransition
	.byte 0

BattleFrontier_BattlePyramidFloor_OnFrame:
	map_script_2 VAR_TEMP_D, 1, BattleFrontier_BattlePyramidFloor_EventScript_UpdateLight
	map_script_2 VAR_TEMP_PLAYING_PYRAMID_MUSIC, 0, BattleFrontier_BattlePyramidFloor_EventScript_PlayPyramidMusic
	map_script_2 VAR_TEMP_F, 1, BattleFrontier_BattlePyramidFloor_EventScript_ShowMapName
	.2byte 0

BattleFrontier_BattlePyramidFloor_EventScript_UpdateLight::
	lockall
	@ pyramid_updatelight, cant use macro because it straddles the loop
	setvar VAR_0x8004, BATTLE_PYRAMID_FUNC_UPDATE_LIGHT
	setvar VAR_0x8005, 4
	setvar VAR_0x8006, PYRAMID_LIGHT_INCR_RADIUS
	setvar VAR_0x8007, SE_SAVE
	setvar VAR_RESULT, 0
BattleFrontier_BattlePyramidFloor_EventScript_UpdateLightLoop::
	special CallBattlePyramidFunction
	delay 2
	goto_if_ne VAR_RESULT, 2, BattleFrontier_BattlePyramidFloor_EventScript_UpdateLightLoop
	setvar VAR_TEMP_D, 0
	releaseall
	end

BattleFrontier_BattlePyramidFloor_EventScript_ShowMapName::
	special ShowMapNamePopup
	setvar VAR_TEMP_F, 0
	end

BattleFrontier_BattlePyramidFloor_EventScript_PlayPyramidMusic::
	playbgm MUS_B_PYRAMID, FALSE
	setvar VAR_TEMP_PLAYING_PYRAMID_MUSIC, 1
	end

BattleFrontier_BattlePyramidFloor_OnResume:
	pyramid_setfloorpal
	frontier_getstatus
	switch VAR_TEMP_CHALLENGE_STATUS
	case 0, BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge
	case CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramid_EventScript_WarpToLobby
	case CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, B_OUTCOME_LOST, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	goto_if_eq VAR_RESULT, B_OUTCOME_DREW, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	goto_if_eq VAR_RESULT, B_OUTCOME_FORFEITED, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	frontier_isbattletype BATTLE_TYPE_TRAINER  @ VAR_RESULT seems to be ignored here
	setvar VAR_TEMP_D, 1
BattleFrontier_BattlePyramidFloor_EventScript_ResetParty::
	pyramid_resetparty
	end

BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
	pyramid_set PYRAMID_DATA_TRAINER_FLAGS, 255
BattleFrontier_BattlePyramid_EventScript_WarpToLobby::
	pyramid_updatelight 0, PYRAMID_LIGHT_SET_RADIUS
	pyramid_clearhelditems
	special HealPlayerParty
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_LOBBY, 7, 13
	waitstate
	end

BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge::
	pyramid_save CHALLENGE_STATUS_SAVING
	special SavePlayerParty
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	pyramid_settrainers
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidFloor_OnTransition:
	call BattleFrontier_BattlePyramidFloor_EventScript_SetLightRadius
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidFloor_EventScript_SetLightRadius::
	pyramid_updatelight 32, PYRAMID_LIGHT_SET_RADIUS
	return

BattlePyramid_WarpToNextFloor::
	call BattleFrontier_EventScript_IncrementWinStreak
	frontier_get FRONTIER_DATA_BATTLE_NUM  @ Floor number
	addvar VAR_RESULT, 1
	frontier_set FRONTIER_DATA_BATTLE_NUM, VAR_RESULT
	goto_if_eq VAR_RESULT, 7, BattlePyramid_WarpToTop
	pyramid_seedfloor
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_RESULT, 0
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR, 1, 1
	waitstate
	end

BattlePyramid_WarpToTop::
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_TOP, 17, 17
	waitstate
	end

@ TRAINER_PHILLIP is used as a placeholder
BattlePyramid_TrainerBattle::
	trainerbattle TRAINER_BATTLE_PYRAMID, TRAINER_PHILLIP, 0, BattleFacility_TrainerBattle_PlaceholderText, BattleFacility_TrainerBattle_PlaceholderText
	pyramid_showhint
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattlePyramid_FindItemBall::
	pyramid_setitem
	callstd STD_FIND_ITEM
	goto_if_eq VAR_0x8007, 0, BattlePyramid_FindItemBallEnd
	pyramid_hideitem
BattlePyramid_FindItemBallEnd::
	end

BattlePyramid_Retire::
	goto BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost

@ Also used by Trainer Hill
BattleFacility_TrainerBattle_PlaceholderText:
	.string "Αυτό είναι ένα δείγμα μηνύματος.$"

gText_BattlePyramidConfirmRest::
	.string "Το BATTLE PYRAMID quest σου θα γίνει\n"
	.string "save για να μπορέσεις να βγεις.\l"
	.string "Είναι εντάξει;$"

gText_BattlePyramidConfirmRetire::
	.string "Θέλεις σίγουρα να εγκαταλείψεις το\n"
	.string "PYRAMID quest σου;$"

BattlePyramid_Text_ExitHintUp1::
	.string "Η έξοδος αυτού του ορόφου είναι\n"
	.string "προς εκείνη την κατεύθυνση: {UP_ARROW}$"

BattlePyramid_Text_ExitHintLeft1::
	.string "Η έξοδος αυτού του ορόφου είναι\n"
	.string "προς εκείνη την κατεύθυνση: {LEFT_ARROW}$"

BattlePyramid_Text_ExitHintRight1::
	.string "Η έξοδος αυτού του ορόφου είναι\n"
	.string "προς εκείνη την κατεύθυνση: {RIGHT_ARROW}$"

BattlePyramid_Text_ExitHintDown1::
	.string "Η έξοδος αυτού του ορόφου είναι\n"
	.string "προς εκείνη την κατεύθυνση: {DOWN_ARROW}$"

BattlePyramid_Text_ExitHintUp2::
	.string "Η έξοδος σε αυτόν τον όροφο είναι\n"
	.string "στην κατεύθυνση: {UP_ARROW}$"

BattlePyramid_Text_ExitHintLeft2::
	.string "Η έξοδος σε αυτόν τον όροφο είναι\n"
	.string "στην κατεύθυνση: {LEFT_ARROW}$"

BattlePyramid_Text_ExitHintRight2::
	.string "Η έξοδος σε αυτόν τον όροφο είναι\n"
	.string "στην κατεύθυνση: {RIGHT_ARROW}$"

BattlePyramid_Text_ExitHintDown2::
	.string "Η έξοδος σε αυτόν τον όροφο είναι\n"
	.string "στην κατεύθυνση: {DOWN_ARROW}$"

BattlePyramid_Text_ExitHintUp3::
	.string "Η έξοδος είναι προς\n"
	.string "τα εκεί: {UP_ARROW}$"

BattlePyramid_Text_ExitHintLeft3::
	.string "Η έξοδος είναι προς\n"
	.string "τα εκεί: {LEFT_ARROW}$"

BattlePyramid_Text_ExitHintRight3::
	.string "Η έξοδος είναι προς\n"
	.string "τα εκεί: {RIGHT_ARROW}$"

BattlePyramid_Text_ExitHintDown3::
	.string "Η έξοδος είναι προς\n"
	.string "τα εκεί: {DOWN_ARROW}$"

BattlePyramid_Text_ExitHintUp4::
	.string "Σε αυτόν τον όροφο, η έξοδος είναι\n"
	.string "κάπου προς την κατεύθυνση: {UP_ARROW}$"

BattlePyramid_Text_ExitHintLeft4::
	.string "Σε αυτόν τον όροφο, η έξοδος είναι\n"
	.string "κάπου προς την κατεύθυνση: {LEFT_ARROW}$"

BattlePyramid_Text_ExitHintRight4::
	.string "Σε αυτόν τον όροφο, η έξοδος είναι\n"
	.string "κάπου προς την κατεύθυνση: {RIGHT_ARROW}$"

BattlePyramid_Text_ExitHintDown4::
	.string "Σε αυτόν τον όροφο, η έξοδος είναι\n"
	.string "κάπου προς την κατεύθυνση: {DOWN_ARROW}$"

BattlePyramid_Text_ExitHintUp5::
	.string "Η έξοδος;\n"
	.string "Είναι προς τα εκεί: {UP_ARROW}$"

BattlePyramid_Text_ExitHintLeft5::
	.string "Η έξοδος;\n"
	.string "Είναι προς τα εκεί: {LEFT_ARROW}$"

BattlePyramid_Text_ExitHintRight5::
	.string "Η έξοδος;\n"
	.string "Είναι προς τα εκεί: {RIGHT_ARROW}$"

BattlePyramid_Text_ExitHintDown5::
	.string "Η έξοδος;\n"
	.string "Είναι προς τα εκεί: {DOWN_ARROW}$"

BattlePyramid_Text_ExitHintUp6::
	.string "Η έξοδος τυχαίνει να είναι\n"
	.string "στην κατεύθυνση: {UP_ARROW}$"

BattlePyramid_Text_ExitHintLeft6::
	.string "Η έξοδος τυχαίνει να είναι\n"
	.string "στην κατεύθυνση: {LEFT_ARROW}$"

BattlePyramid_Text_ExitHintRight6::
	.string "Η έξοδος τυχαίνει να είναι\n"
	.string "στην κατεύθυνση: {RIGHT_ARROW}$"

BattlePyramid_Text_ExitHintDown6::
	.string "Η έξοδος τυχαίνει να είναι\n"
	.string "στην κατεύθυνση: {DOWN_ARROW}$"

BattlePyramid_Text_EightItemsRemaining1::
	.string "Ψάχνεις για items;\p"
	.string "Υπάρχουν ακόμα οκτώ (8) items που\n"
	.string "πρέπει να βρεθούν.$"

BattlePyramid_Text_SevenItemsRemaining1::
	.string "Ψάχνεις για items;\p"
	.string "Υπάρχουν ακόμα επτά (7) items που\n"
	.string "πρέπει να βρεθούν.$"

BattlePyramid_Text_SixItemsRemaining1::
	.string "Ψάχνεις για items;\p"
	.string "Υπάρχουν ακόμα έξι (6) items που\n"
	.string "πρέπει να βρεθούν.$"

BattlePyramid_Text_FiveItemsRemaining1::
	.string "Ψάχνεις για items;\p"
	.string "Υπάρχουν ακόμα πέντε (5) items που\n"
	.string "πρέπει να βρεθούν.$"

BattlePyramid_Text_FourItemsRemaining1::
	.string "Ψάχνεις για items;\p"
	.string "Υπάρχουν ακόμα τέσσερα (4) items που\n"
	.string "πρέπει να βρεθούν.$"

BattlePyramid_Text_ThreeItemsRemaining1::
	.string "Ψάχνεις για items;\p"
	.string "Υπάρχουν ακόμα τρία (3) items που\n"
	.string "πρέπει να βρεθούν.$"

BattlePyramid_Text_TwoItemsRemaining1::
	.string "Ψάχνεις για items;\p"
	.string "Υπάρχουν ακόμα δύο (2) items που\n"
	.string "πρέπει να βρεθούν.$"

BattlePyramid_Text_OneItemRemaining1::
	.string "Ψάχνεις για items;\p"
	.string "Υπάρχει ακόμα ένα (1) item που\n"
	.string "πρέπει να βρεθεί.$"

BattlePyramid_Text_ZeroItemsRemaining1::
	.string "Ψάχνεις για items;\p"
	.string "Δεν υπάρχει τίποτα άλλο που\n"
	.string "πρέπει να βρεθεί!$"

BattlePyramid_Text_EightItemsRemaining2::
	.string "Επειδή νίκησες, θα σου πω\n"
	.string "ένα μικρό μυστικό!\p"
	.string "Υπάρχουν οκτώ items\n"
	.string "σκόρπια εδώ γύρω.$"

BattlePyramid_Text_SevenItemsRemaining2::
	.string "Επειδή νίκησες, θα σου πω\n"
	.string "ένα μικρό μυστικό!\p"
	.string "Υπάρχουν επτά items ακόμα\n"
	.string "σκόρπια εδώ γύρω.$"

BattlePyramid_Text_SixItemsRemaining2::
	.string "Επειδή νίκησες, θα σου πω\n"
	.string "ένα μικρό μυστικό!\p"
	.string "Υπάρχουν έξι items ακόμα\n"
	.string "σκόρπια εδώ γύρω.$"

BattlePyramid_Text_FiveItemsRemaining2::
	.string "Επειδή νίκησες, θα σου πω\n"
	.string "ένα μικρό μυστικό!\p"
	.string "Υπάρχουν πέντε items ακόμα\n"
	.string "σκόρπια εδώ γύρω.$"

BattlePyramid_Text_FourItemsRemaining2::
	.string "Επειδή νίκησες, θα σου πω\n"
	.string "ένα μικρό μυστικό!\p"
	.string "Υπάρχουν τέσσερα items ακόμα\n"
	.string "σκόρπια εδώ γύρω.$"

BattlePyramid_Text_ThreeItemsRemaining2::
	.string "Επειδή νίκησες, θα σου πω\n"
	.string "ένα μικρό μυστικό!\p"
	.string "Υπάρχουν τρία items ακόμα\n"
	.string "σκόρπια εδώ γύρω.$"

BattlePyramid_Text_TwoItemsRemaining2::
	.string "Επειδή νίκησες, θα σου πω\n"
	.string "ένα μικρό μυστικό!\p"
	.string "Υπάρχουν δύο items ακόμα\n"
	.string "σκόρπια εδώ γύρω.$"

BattlePyramid_Text_OneItemRemaining2::
	.string "Επειδή νίκησες, θα σου πω\n"
	.string "ένα μικρό μυστικό!\p"
	.string "Υπάρχει μόνο ένα item ακόμα\n"
	.string "σκόρπιο εδώ γύρω.$"

BattlePyramid_Text_ZeroItemsRemaining2::
	.string "Επειδή νίκησες, θα σου πω\n"
	.string "ένα μικρό μυστικό!\p"
	.string "Δεν υπάρχει τίποτα άλλο\n"
	.string "σκόρπιο εδώ γύρω.$"

BattlePyramid_Text_EightItemsRemaining3::
	.string "Πώς πάει το απόθεμά σου από items;\p"
	.string "Υπολογίζω ότι υπάρχουν οκτώ items\n"
	.string "που περιμένουν να βρεθούν στον όροφο.$"

BattlePyramid_Text_SevenItemsRemaining3::
	.string "Πώς πάει το απόθεμά σου από items;\p"
	.string "Υπολογίζω ότι υπάρχουν επτά items\n"
	.string "που περιμένουν να βρεθούν στον όροφο.$"

BattlePyramid_Text_SixItemsRemaining3::
	.string "Πώς πάει το απόθεμά σου από items;\p"
	.string "Υπολογίζω ότι υπάρχουν έξι items\n"
	.string "που περιμένουν να βρεθούν στον όροφο.$"

BattlePyramid_Text_FiveItemsRemaining3::
	.string "Πώς πάει το απόθεμά σου από items;\p"
	.string "Υπολογίζω ότι υπάρχουν πέντε items\n"
	.string "που περιμένουν να βρεθούν στον όροφο.$"

BattlePyramid_Text_FourItemsRemaining3::
	.string "Πώς πάει το απόθεμά σου από items;\p"
	.string "Υπολογίζω ότι υπάρχουν τέσσερα items\n"
	.string "που περιμένουν να βρεθούν στον όροφο.$"

BattlePyramid_Text_ThreeItemsRemaining3::
	.string "Πώς πάει το απόθεμά σου από items;\p"
	.string "Υπολογίζω ότι υπάρχουν τρία items\n"
	.string "που περιμένουν να βρεθούν στον όροφο.$"

BattlePyramid_Text_TwoItemsRemaining3::
	.string "Πώς πάει το απόθεμά σου από items;\p"
	.string "Υπολογίζω ότι υπάρχουν δύο items\n"
	.string "που περιμένουν να βρεθούν στον όροφο.$"

BattlePyramid_Text_OneItemRemaining3::
	.string "Πώς πάει το απόθεμά σου από items;\p"
	.string "Υπολογίζω ότι υπάρχει μόνο ένα item\n"
	.string "που περιμένει να βρεθεί στον όροφο.$"

BattlePyramid_Text_ZeroItemsRemaining3::
	.string "Πώς πάει το απόθεμά σου από items;\p"
	.string "Υπολογίζω πως δεν υπάρχουν άλλα items\n"
	.string "που περιμένουν να βρεθούν.\l"
	.string "Να προσέχεις!$"

BattlePyramid_Text_EightItemsRemaining4::
	.string "Είσαι δυνατό άτομο, οπότε κέρδισες\n"
	.string "ένα hint!\p"
	.string "Φαίνεται να υπάρχουν ακόμα οκτώ\n"
	.string "items στο έδαφος.$"

BattlePyramid_Text_SevenItemsRemaining4::
	.string "Είσαι δυνατό άτομο, οπότε κέρδισες\n"
	.string "ένα hint!\p"
	.string "Φαίνεται να υπάρχουν ακόμα επτά\n"
	.string "items στο έδαφος.$"

BattlePyramid_Text_SixItemsRemaining4::
	.string "Είσαι δυνατό άτομο, οπότε κέρδισες\n"
	.string "ένα hint!\p"
	.string "Φαίνεται να υπάρχουν ακόμα έξι\n"
	.string "items στο έδαφος.$"

BattlePyramid_Text_FiveItemsRemaining4::
	.string "Είσαι δυνατό άτομο, οπότε κέρδισες\n"
	.string "ένα hint!\p"
	.string "Φαίνεται να υπάρχουν ακόμα πέντε\n"
	.string "items στο έδαφος.$"

BattlePyramid_Text_FourItemsRemaining4::
	.string "Είσαι δυνατό άτομο, οπότε κέρδισες\n"
	.string "ένα hint!\p"
	.string "Φαίνεται να υπάρχουν ακόμα τέσσερα\n"
	.string "items στο έδαφος.$"

BattlePyramid_Text_ThreeItemsRemaining4::
	.string "Είσαι δυνατό άτομο, οπότε κέρδισες\n"
	.string "ένα hint!\p"
	.string "Φαίνεται να υπάρχουν ακόμα τρία\n"
	.string "items στο έδαφος.$"

BattlePyramid_Text_TwoItemsRemaining4::
	.string "Είσαι δυνατό άτομο, οπότε κέρδισες\n"
	.string "ένα hint!\p"
	.string "Φαίνεται να υπάρχουν ακόμα δύο\n"
	.string "items στο έδαφος.$"

BattlePyramid_Text_OneItemRemaining4::
	.string "Είσαι δυνατό άτομο, οπότε κέρδισες\n"
	.string "ένα hint!\p"
	.string "Φαίνεται να υπάρχει ακόμα ένα μόνο\n"
	.string "item στο έδαφος.$"

BattlePyramid_Text_ZeroItemsRemaining4::
	.string "Είσαι δυνατό άτομο, οπότε κέρδισες\n"
	.string "ένα hint!\p"
	.string "Φαίνεται να μην υπάρχουν\n"
	.string "άλλα items στο έδαφος.$"

BattlePyramid_Text_EightItemsRemaining5::
	.string "Σε αυτόν τον όροφο της PYRAMID,\n"
	.string "ακούω ότι υπάρχουν οκτώ items…$"

BattlePyramid_Text_SevenItemsRemaining5::
	.string "Σε αυτόν τον όροφο της PYRAMID,\n"
	.string "ακούω ότι υπάρχουν επτά items…$"

BattlePyramid_Text_SixItemsRemaining5::
	.string "Σε αυτόν τον όροφο της PYRAMID,\n"
	.string "ακούω ότι υπάρχουν έξι items…$"

BattlePyramid_Text_FiveItemsRemaining5::
	.string "Σε αυτόν τον όροφο της PYRAMID,\n"
	.string "ακούω ότι υπάρχουν πέντε items…$"

BattlePyramid_Text_FourItemsRemaining5::
	.string "Σε αυτόν τον όροφο της PYRAMID,\n"
	.string "ακούω ότι υπάρχουν τέσσερα items…$"

BattlePyramid_Text_ThreeItemsRemaining5::
	.string "Σε αυτόν τον όροφο της PYRAMID,\n"
	.string "ακούω ότι υπάρχουν τρία items…$"

BattlePyramid_Text_TwoItemsRemaining5::
	.string "Σε αυτόν τον όροφο της PYRAMID,\n"
	.string "ακούω ότι υπάρχουν δύο items…$"

BattlePyramid_Text_OneItemRemaining5::
	.string "Σε αυτόν τον όροφο της PYRAMID,\n"
	.string "ακούω ότι υπάρχει ένα item…$"

BattlePyramid_Text_ZeroItemsRemaining5::
	.string "Σε αυτόν τον όροφο της PYRAMID,\n"
	.string "ακούω ότι δεν υπάρχουν items…$"

BattlePyramid_Text_EightItemsRemaining6::
	.string "Έχεις μαζέψει καθόλου items;\p"
	.string "Πιστεύω ότι υπάρχουν οκτώ ακόμα\n"
	.string "items σε αυτόν τον όροφο.$"

BattlePyramid_Text_SevenItemsRemaining6::
	.string "Έχεις μαζέψει καθόλου items;\p"
	.string "Πιστεύω ότι υπάρχουν επτά ακόμα\n"
	.string "items σε αυτόν τον όροφο.$"

BattlePyramid_Text_SixItemsRemaining6::
	.string "Έχεις μαζέψει καθόλου items;\p"
	.string "Πιστεύω ότι υπάρχουν έξι ακόμα\n"
	.string "items σε αυτόν τον όροφο.$"

BattlePyramid_Text_FiveItemsRemaining6::
	.string "Έχεις μαζέψει καθόλου items;\p"
	.string "Πιστεύω ότι υπάρχουν πέντε ακόμα\n"
	.string "items σε αυτόν τον όροφο.$"

BattlePyramid_Text_FourItemsRemaining6::
	.string "Έχεις μαζέψει καθόλου items;\p"
	.string "Πιστεύω ότι υπάρχουν τέσσερα ακόμα\n"
	.string "items σε αυτόν τον όροφο.$"

BattlePyramid_Text_ThreeItemsRemaining6::
	.string "Έχεις μαζέψει καθόλου items;\p"
	.string "Πιστεύω ότι υπάρχουν τρία ακόμα\n"
	.string "items σε αυτόν τον όροφο.$"

BattlePyramid_Text_TwoItemsRemaining6::
	.string "Έχεις μαζέψει καθόλου items;\p"
	.string "Πιστεύω ότι υπάρχουν δύο ακόμα\n"
	.string "items σε αυτόν τον όροφο.$"

BattlePyramid_Text_OneItemRemaining6::
	.string "Έχεις μαζέψει καθόλου items;\p"
	.string "Πιστεύω ότι υπάρχει ένα ακόμα\n"
	.string "item σε αυτόν τον όροφο.$"

BattlePyramid_Text_ZeroItemsRemaining6::
	.string "Έχεις μαζέψει καθόλου items;\p"
	.string "Πιστεύω ότι δεν υπάρχουν άλλα\n"
	.string "items σε αυτόν τον όροφο.$"

BattlePyramid_Text_SevenTrainersRemaining1::
	.string "Ήσουν πραγματικά φοβερό άτομο!\p"
	.string "Όμως, υπάρχουν ακόμα επτά σκληρά\n"
	.string "TRAINER άτομα εκτός από μένα!$"

BattlePyramid_Text_SixTrainersRemaining1::
	.string "Ήσουν πραγματικά φοβερό άτομο!\p"
	.string "Όμως, υπάρχουν ακόμα έξι σκληρά\n"
	.string "TRAINER άτομα εκτός από μένα!$"

BattlePyramid_Text_FiveTrainersRemaining1::
	.string "Ήσουν πραγματικά φοβερό άτομο!\p"
	.string "Όμως, υπάρχουν ακόμα πέντε σκληρά\n"
	.string "TRAINER άτομα εκτός από μένα!$"

BattlePyramid_Text_FourTrainersRemaining1::
	.string "Ήσουν πραγματικά φοβερό άτομο!\p"
	.string "Όμως, υπάρχουν ακόμα τέσσερα σκληρά\n"
	.string "TRAINER άτομα εκτός από μένα!$"

BattlePyramid_Text_ThreeTrainersRemaining1::
	.string "Ήσουν πραγματικά φοβερό άτομο!\p"
	.string "Όμως, υπάρχουν ακόμα τρία σκληρά\n"
	.string "TRAINER άτομα εκτός από μένα!$"

BattlePyramid_Text_TwoTrainersRemaining1::
	.string "Ήσουν πραγματικά φοβερό άτομο!\p"
	.string "Όμως, υπάρχουν ακόμα δύο σκληρά\n"
	.string "TRAINER άτομα εκτός από μένα!$"

BattlePyramid_Text_OneTrainersRemaining1::
	.string "Ήσουν πραγματικά φοβερό άτομο!\p"
	.string "Όμως, υπάρχει ακόμα ένα σκληρό\n"
	.string "TRAINER άτομο εκτός από μένα!$"

BattlePyramid_Text_ZeroTrainersRemaining1::
	.string "Ήσουν πραγματικά φοβερό άτομο!\p"
	.string "Δεν έχει μείνει κανένας που\n"
	.string "να μπορεί να σε κερδίσει!$"

BattlePyramid_Text_SevenTrainersRemaining2::
	.string "Αυτό είναι τόσο εκνευριστικό!\p"
	.string "Αλλά υπάρχουν επτά TRAINERS ακόμα!\n"
	.string "Κάποιο θα σου κόψει τον αέρα!$"

BattlePyramid_Text_SixTrainersRemaining2::
	.string "Αυτό είναι τόσο εκνευριστικό!\p"
	.string "Αλλά υπάρχουν έξι TRAINERS ακόμα!\n"
	.string "Κάποιο θα σου κόψει τον αέρα!$"

BattlePyramid_Text_FiveTrainersRemaining2::
	.string "Αυτό είναι τόσο εκνευριστικό!\p"
	.string "Αλλά υπάρχουν πέντε TRAINERS ακόμα!\n"
	.string "Κάποιο θα σου κόψει τον αέρα!$"

BattlePyramid_Text_FourTrainersRemaining2::
	.string "Αυτό είναι τόσο εκνευριστικό!\p"
	.string "Αλλά υπάρχουν τέσσερα TRAINERS ακόμα!\n"
	.string "Κάποιο θα σου κόψει τον αέρα!$"

BattlePyramid_Text_ThreeTrainersRemaining2::
	.string "Αυτό είναι τόσο εκνευριστικό!\p"
	.string "Αλλά υπάρχουν τρία TRAINERS ακόμα!\n"
	.string "Κάποιο θα σου κόψει τον αέρα!$"

BattlePyramid_Text_TwoTrainersRemaining2::
	.string "Αυτό είναι τόσο εκνευριστικό!\p"
	.string "Αλλά υπάρχουν δύο TRAINERS ακόμα!\n"
	.string "Κάποιο θα σου κόψει τον αέρα!$"

BattlePyramid_Text_OneTrainersRemaining2::
	.string "Αυτό είναι τόσο εκνευριστικό!\p"
	.string "Υπάρχει όμως ένα TRAINER άτομο ακόμα!\n"
	.string "Είμαι σίγουρο πως θα ταπεινωθείς!$"

BattlePyramid_Text_ZeroTrainersRemaining2::
	.string "Αυτό είναι τόσο εκνευριστικό!\p"
	.string "Αλλά δεν υπάρχουν άλλα TRAINER άτομα\n"
	.string "που να μπορούν να σε αντιμετωπίσουν!$"

BattlePyramid_Text_SevenTrainersRemaining3::
	.string "Αυτό είναι πολύ εντυπωσιακό!\p"
	.string "Όμως υπάρχουν επτά TRAINERS ακόμα\n"
	.string "στον όροφο. Μπορείς να τα κερδίσεις;$"

BattlePyramid_Text_SixTrainersRemaining3::
	.string "Αυτό είναι πολύ εντυπωσιακό!\p"
	.string "Όμως υπάρχουν έξι TRAINERS ακόμα\n"
	.string "στον όροφο. Μπορείς να τα κερδίσεις;$"

BattlePyramid_Text_FiveTrainersRemaining3::
	.string "Αυτό είναι πολύ εντυπωσιακό!\p"
	.string "Όμως υπάρχουν πέντε TRAINERS ακόμα\n"
	.string "στον όροφο. Μπορείς να τα κερδίσεις;$"

BattlePyramid_Text_FourTrainersRemaining3::
	.string "Αυτό είναι πολύ εντυπωσιακό!\p"
	.string "Όμως υπάρχουν τέσσερα TRAINERS ακόμα\n"
	.string "στον όροφο. Μπορείς να τα κερδίσεις;$"

BattlePyramid_Text_ThreeTrainersRemaining3::
	.string "Αυτό είναι πολύ εντυπωσιακό!\p"
	.string "Όμως υπάρχουν τρία TRAINERS ακόμα\n"
	.string "στον όροφο. Μπορείς να τα κερδίσεις;$"

BattlePyramid_Text_TwoTrainersRemaining3::
	.string "Αυτό είναι πολύ εντυπωσιακό!\p"
	.string "Όμως υπάρχουν δύο TRAINERS ακόμα\n"
	.string "στον όροφο. Μπορείς να τα κερδίσεις;$"

BattlePyramid_Text_OneTrainersRemaining3::
	.string "Αυτό είναι πολύ εντυπωσιακό!\p"
	.string "Όμως υπάρχει ένα TRAINER άτομο ακόμα\n"
	.string "στον όροφο. Μπορείς να επικρατήσεις;$"

BattlePyramid_Text_ZeroTrainersRemaining3::
	.string "Αυτό είναι πολύ εντυπωσιακό!\p"
	.string "Έχεις περάσει όλα τα TRAINERS σε\n"
	.string "αυτόν τον όροφο.$"

BattlePyramid_Text_SevenTrainersRemaining4::
	.string "Ίσως μπορείς να κερδίσεις τα επτά\n"
	.string "TRAINERS που απέμειναν στον όροφο.$"

BattlePyramid_Text_SixTrainersRemaining4::
	.string "Ίσως μπορείς να κερδίσεις τα έξι\n"
	.string "TRAINERS που απέμειναν στον όροφο.$"

BattlePyramid_Text_FiveTrainersRemaining4::
	.string "Ίσως μπορείς να κερδίσεις τα πέντε\n"
	.string "TRAINERS που απέμειναν στον όροφο.$"

BattlePyramid_Text_FourTrainersRemaining4::
	.string "Ίσως μπορείς να κερδίσεις τα τέσσερα\n"
	.string "TRAINERS που απέμειναν στον όροφο.$"

BattlePyramid_Text_ThreeTrainersRemaining4::
	.string "Ίσως μπορείς να κερδίσεις τα τρία\n"
	.string "TRAINERS που απέμειναν στον όροφο.$"

BattlePyramid_Text_TwoTrainersRemaining4::
	.string "Ίσως μπορείς να κερδίσεις τα δύο\n"
	.string "TRAINERS που απέμειναν στον όροφο.$"

BattlePyramid_Text_OneTrainersRemaining4::
	.string "Ίσως νικήσεις και το τελευταίο από τα\n"
	.string "άτομα TRAINER που απέμειναν στον όροφο.$"

BattlePyramid_Text_ZeroTrainersRemaining4::
	.string "Δεν υπάρχει ούτε ένα άτομο που\n"
	.string "να μπορεί να σε κερδίσει τώρα…$"

BattlePyramid_Text_SevenTrainersRemaining5::
	.string "Μπορεί να έχεις ό,τι χρειάζεται για τα\n"
	.string "επτά έμπειρα TRAINERS που απέμειναν.$"

BattlePyramid_Text_SixTrainersRemaining5::
	.string "Μπορεί να έχεις ό,τι χρειάζεται για τα\n"
	.string "έξι έμπειρα TRAINERS που απέμειναν.$"

BattlePyramid_Text_FiveTrainersRemaining5::
	.string "Μπορεί να έχεις ό,τι χρειάζεται για τα\n"
	.string "πέντε έμπειρα TRAINERS που απέμειναν.$"

BattlePyramid_Text_FourTrainersRemaining5::
	.string "Μπορεί να έχεις ό,τι χρειάζεται για τα\n"
	.string "τέσσερα έμπειρα TRAINERS που απέμειναν.$"

BattlePyramid_Text_ThreeTrainersRemaining5::
	.string "Μπορεί να έχεις ό,τι χρειάζεται για τα\n"
	.string "τρία έμπειρα TRAINERS που απέμειναν.$"

BattlePyramid_Text_TwoTrainersRemaining5::
	.string "Μπορεί να έχεις ό,τι χρειάζεται για τα\n"
	.string "δύο έμπειρα TRAINERS που απέμειναν.$"

BattlePyramid_Text_OneTrainersRemaining5::
	.string "Μπορεί να έχεις ό,τι χρειάζεται για το\n"
	.string "ένα έμπειρο TRAINER που απέμεινε.$"

BattlePyramid_Text_ZeroTrainersRemaining5::
	.string "Οι ικανότητές σου είναι αψεγάδιαστες.\p"
	.string "Δεν υπάρχουν άλλα TRAINER άτομα εδώ\n"
	.string "που να έχουν πιθανότητα να σε νικήσουν.$"

BattlePyramid_Text_SevenTrainersRemaining6::
	.string "Μπορείς να συνεχίσεις να κερδίζεις\n"
	.string "έναντι των επτά εναπομενόντων TRAINERS;$"

BattlePyramid_Text_SixTrainersRemaining6::
	.string "Μπορείς να συνεχίσεις να κερδίζεις\n"
	.string "έναντι των έξι εναπομενόντων TRAINERS;$"

BattlePyramid_Text_FiveTrainersRemaining6::
	.string "Μπορείς να συνεχίσεις να κερδίζεις\n"
	.string "έναντι των πέντε TRAINERS ακόμα;$"

BattlePyramid_Text_FourTrainersRemaining6::
	.string "Μπορείς να συνεχίσεις να κερδίζεις\n"
	.string "έναντι των τεσσάρων TRAINERS ακόμα;$"

BattlePyramid_Text_ThreeTrainersRemaining6::
	.string "Μπορείς να συνεχίσεις να κερδίζεις\n"
	.string "έναντι των τριών TRAINERS ακόμα;$"

BattlePyramid_Text_TwoTrainersRemaining6::
	.string "Μπορείς να συνεχίσεις να κερδίζεις\n"
	.string "έναντι των δύο TRAINERS ακόμα;$"

BattlePyramid_Text_OneTrainersRemaining6::
	.string "Μπορείς να συνεχίσεις να κερδίζεις\n"
	.string "έναντι στο τελευταίο TRAINER άτομο;$"

BattlePyramid_Text_ZeroTrainersRemaining6::
	.string "Δεν υπάρχουν πια άλλα TRAINER άτομα\n"
	.string "που να μπορούν να σε αντιμετωπίσουν…$"
