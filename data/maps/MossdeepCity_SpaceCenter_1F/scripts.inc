.set LOCALID_SCIENTIST_1, 1
.set LOCALID_SCIENTIST_2, 2
.set LOCALID_SAILOR, 3
.set LOCALID_OLD_MAN, 4
.set LOCALID_WOMAN, 5
.set LOCALID_STAIR_GRUNT, 9

MossdeepCity_SpaceCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MossdeepCity_SpaceCenter_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_SpaceCenter_1F_OnTransition
	.byte 0

MossdeepCity_SpaceCenter_1F_OnTransition:
	goto_if_eq VAR_MOSSDEEP_CITY_STATE, 2, MossdeepCity_SpaceCenter_1F_EventScript_MoveObjectsForTeamMagma
	end

MossdeepCity_SpaceCenter_1F_EventScript_MoveObjectsForTeamMagma::
	setobjectxyperm LOCALID_SAILOR, 1, 9
	setobjectmovementtype LOCALID_SAILOR, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_WOMAN, 0, 8
	setobjectmovementtype LOCALID_WOMAN, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_OLD_MAN, 1, 6
	setobjectmovementtype LOCALID_OLD_MAN, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_SCIENTIST_1, 3, 4
	setobjectmovementtype LOCALID_SCIENTIST_1, MOVEMENT_TYPE_FACE_RIGHT
	setobjectmovementtype LOCALID_SCIENTIST_2, MOVEMENT_TYPE_FACE_RIGHT
	goto_if_eq VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE, 1, MossdeepCity_SpaceCenter_1F_EventScript_MoveStairGuardLeft
	goto_if_eq VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE, 2, MossdeepCity_SpaceCenter_1F_EventScript_MoveStairGuardDown
	goto_if_eq VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE, 3, MossdeepCity_SpaceCenter_1F_EventScript_MoveStairGuardRight
	end

MossdeepCity_SpaceCenter_1F_EventScript_MoveStairGuardLeft::
	setobjectxyperm LOCALID_STAIR_GRUNT, 12, 2
	end

MossdeepCity_SpaceCenter_1F_EventScript_MoveStairGuardDown::
	setobjectxyperm LOCALID_STAIR_GRUNT, 13, 3
	end

@ Functionally unused. See comment on MossdeepCity_SpaceCenter_1F_EventScript_MoveGruntFromStairsEast
MossdeepCity_SpaceCenter_1F_EventScript_MoveStairGuardRight::
	setobjectxyperm LOCALID_STAIR_GRUNT, 14, 2
	end

MossdeepCity_SpaceCenter_1F_OnLoad:
	goto_if_le VAR_MOSSDEEP_CITY_STATE, 2, MossdeepCity_SpaceCenter_1F_EventScript_SetMagmaNote
	end

MossdeepCity_SpaceCenter_1F_EventScript_SetMagmaNote::
	setmetatile 2, 5, METATILE_Facility_DataPad, TRUE
	return

MossdeepCity_SpaceCenter_1F_EventScript_RocketLaunchCounter::
	lock
	faceplayer
	goto_if_eq VAR_MOSSDEEP_CITY_STATE, 2, MossdeepCity_SpaceCenter_1F_EventScript_RocketLaunchCounterMagma
	dotimebasedevents
	specialvar VAR_RESULT, GetWeekCount
	buffernumberstring STR_VAR_1, VAR_RESULT
	call_if_eq VAR_RESULT, 0, MossdeepCity_SpaceCenter_1F_EventScript_NoLaunchesYet
	call_if_ge VAR_RESULT, 1, MossdeepCity_SpaceCenter_1F_EventScript_ShowLaunchNumber
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_NoLaunchesYet::
	msgbox MossdeepCity_SpaceCenter_1F_Text_RocketLaunchImminent, MSGBOX_DEFAULT
	return

MossdeepCity_SpaceCenter_1F_EventScript_ShowLaunchNumber::
	msgbox MossdeepCity_SpaceCenter_1F_Text_SuccessfulLaunchNumber, MSGBOX_DEFAULT
	return

MossdeepCity_SpaceCenter_1F_EventScript_RocketLaunchCounterMagma::
	dotimebasedevents
	specialvar VAR_RESULT, GetWeekCount
	buffernumberstring STR_VAR_1, VAR_RESULT
	call_if_eq VAR_RESULT, 0, MossdeepCity_SpaceCenter_1F_EventScript_NoLaunchesYetMagma
	call_if_ge VAR_RESULT, 1, MossdeepCity_SpaceCenter_1F_EventScript_ShowLaunchNumberMagma
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_NoLaunchesYetMagma::
	msgbox MossdeepCity_SpaceCenter_1F_Text_HaywireButRocketLaunchImminent, MSGBOX_DEFAULT
	return

MossdeepCity_SpaceCenter_1F_EventScript_ShowLaunchNumberMagma::
	msgbox MossdeepCity_SpaceCenter_1F_Text_HaywireButSuccessfulLaunchNumber, MSGBOX_DEFAULT
	return

MossdeepCity_SpaceCenter_1F_EventScript_Scientist::
	lock
	faceplayer
	goto_if_eq VAR_MOSSDEEP_CITY_STATE, 2, MossdeepCity_SpaceCenter_1F_EventScript_ScientistMagma
	msgbox MossdeepCity_SpaceCenter_1F_Text_RocketLaunchDemandsPerfection, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_ScientistMagma::
	msgbox MossdeepCity_SpaceCenter_1F_Text_MagmaHaveSightsOnSpaceCenter, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_SunStoneMan::
	lock
	faceplayer
	goto_if_eq VAR_MOSSDEEP_CITY_STATE, 2, MossdeepCity_SpaceCenter_1F_EventScript_SunStoneManMagma
	goto_if_set FLAG_RECEIVED_SUN_STONE_MOSSDEEP, MossdeepCity_SpaceCenter_1F_EventScript_GaveSunStone
	msgbox MossdeepCity_SpaceCenter_1F_Text_FoundThisYouCanHaveIt, MSGBOX_DEFAULT
	giveitem ITEM_SUN_STONE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SUN_STONE_MOSSDEEP
	msgbox MossdeepCity_SpaceCenter_1F_Text_HoennFamousForMeteorShowers, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_GaveSunStone::
	msgbox MossdeepCity_SpaceCenter_1F_Text_HoennFamousForMeteorShowers, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_SunStoneManMagma::
	goto_if_set FLAG_RECEIVED_SUN_STONE_MOSSDEEP, MossdeepCity_SpaceCenter_1F_EventScript_GaveSunStoneMagma
	msgbox MossdeepCity_SpaceCenter_1F_Text_MagmaCantStealFuelTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_SUN_STONE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SUN_STONE_MOSSDEEP
	msgbox MossdeepCity_SpaceCenter_1F_Text_CantStrollOnBeachWithMagma, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_GaveSunStoneMagma::
	msgbox MossdeepCity_SpaceCenter_1F_Text_CantStrollOnBeachWithMagma, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, MossdeepCity_SpaceCenter_1F_EventScript_WomanNormal
	goto_if_eq VAR_MOSSDEEP_CITY_STATE, 2, MossdeepCity_SpaceCenter_1F_EventScript_WomanMagma
	goto_if_lt VAR_MOSSDEEP_CITY_STATE, 2, MossdeepCity_SpaceCenter_1F_EventScript_WomanNormal
	goto MossdeepCity_SpaceCenter_1F_EventScript_WomanMagma
	end

MossdeepCity_SpaceCenter_1F_EventScript_WomanNormal::
	msgbox MossdeepCity_SpaceCenter_1F_Text_DidPokemonComeFromSpace, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_WomanMagma::
	msgbox MossdeepCity_SpaceCenter_1F_Text_AquaShouldBeatMagma, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, MossdeepCity_SpaceCenter_1F_EventScript_OldManNormal
	goto_if_eq VAR_MOSSDEEP_CITY_STATE, 2, MossdeepCity_SpaceCenter_1F_EventScript_OldManMagma
	goto_if_lt VAR_MOSSDEEP_CITY_STATE, 2, MossdeepCity_SpaceCenter_1F_EventScript_OldManNormal
	goto MossdeepCity_SpaceCenter_1F_EventScript_OldManMagma
	end

MossdeepCity_SpaceCenter_1F_EventScript_OldManNormal::
	msgbox MossdeepCity_SpaceCenter_1F_Text_RocketsBoggleMyMind, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_OldManMagma::
	msgbox MossdeepCity_SpaceCenter_1F_Text_MagmaWantsToSpoilMyDream, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_Steven::
	lock
	faceplayer
	msgbox MossdeepCity_SpaceCenter_1F_Text_StevenMagmaCantBeAllowedToTakeFuel, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_MagmaNote::
	lockall
	msgbox MossdeepCity_SpaceCenter_1F_Text_MagmaIntentToStealNotice, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_SpaceCenter_1F_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_SPACE_CENTER_3, MossdeepCity_SpaceCenter_1F_Text_Grunt3Intro, MossdeepCity_SpaceCenter_1F_Text_Grunt3Defeat
	msgbox MossdeepCity_SpaceCenter_1F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_SpaceCenter_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_SPACE_CENTER_1, MossdeepCity_SpaceCenter_1F_Text_Grunt1Intro, MossdeepCity_SpaceCenter_1F_Text_Grunt1Defeat
	msgbox MossdeepCity_SpaceCenter_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_SpaceCenter_1F_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_SPACE_CENTER_4, MossdeepCity_SpaceCenter_1F_Text_Grunt4Intro, MossdeepCity_SpaceCenter_1F_Text_Grunt4Defeat
	msgbox MossdeepCity_SpaceCenter_1F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_SpaceCenter_1F_EventScript_Grunt2::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_GRUNT_SPACE_CENTER_1F, MossdeepCity_SpaceCenter_1F_EventScript_Grunt2Defeated
	msgbox MossdeepCity_SpaceCenter_1F_Text_Grunt2Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_SPACE_CENTER_2, MossdeepCity_SpaceCenter_1F_Text_Grunt2Defeat
	setflag FLAG_DEFEATED_GRUNT_SPACE_CENTER_1F
	copyobjectxytoperm LOCALID_STAIR_GRUNT
	switch VAR_FACING
	case DIR_WEST, MossdeepCity_SpaceCenter_1F_EventScript_MoveGruntFromStairsWest
#ifdef BUGFIX
	case DIR_EAST, MossdeepCity_SpaceCenter_1F_EventScript_MoveGruntFromStairsEast
#else
	case DIR_WEST, MossdeepCity_SpaceCenter_1F_EventScript_MoveGruntFromStairsEast
#endif
	applymovement LOCALID_STAIR_GRUNT, MossdeepCity_SpaceCenter_1F_Movement_MoveGruntFromStairs
	waitmovement 0
	setvar VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE, 2
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_Grunt2Defeated::
	msgbox MossdeepCity_SpaceCenter_1F_Text_Grunt2PostBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_MoveGruntFromStairsWest::
	applymovement LOCALID_STAIR_GRUNT, MossdeepCity_SpaceCenter_1F_Movement_MoveGruntFromStairsWest
	waitmovement 0
	setvar VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE, 1
	release
	end

@ Functionally unused by mistake. The movement is handled anyway after the switch (see above)
@ This also means VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE can never be 3
MossdeepCity_SpaceCenter_1F_EventScript_MoveGruntFromStairsEast::
	applymovement LOCALID_STAIR_GRUNT, MossdeepCity_SpaceCenter_1F_Movement_MoveGruntFromStairsEast
	waitmovement 0
	setvar VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE, 3
	release
	end

MossdeepCity_SpaceCenter_1F_Movement_MoveGruntFromStairsWest:
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

@ Functionally unused. See above
MossdeepCity_SpaceCenter_1F_Movement_MoveGruntFromStairsEast:
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

@ This was meant to only handle the player facing North, but by mistake(?) it also handles the player facing East
MossdeepCity_SpaceCenter_1F_Movement_MoveGruntFromStairs:
	face_left
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

MossdeepCity_SpaceCenter_1F_Text_RocketLaunchImminent:
	.string "Η εκτόξευση του πυραύλου επίκειται!$"

MossdeepCity_SpaceCenter_1F_Text_SuccessfulLaunchNumber:
	.string "O πύραυλος εκτοξεύτηκε με ασφάλεια!\n"
	.string "Είναι η επιτυχημένη εκτόξευση no. {STR_VAR_1}!$"

MossdeepCity_SpaceCenter_1F_Text_HaywireButRocketLaunchImminent:
	.string "Ξέρω ότι τα πράγματα είναι λίγο \n"
	.string "άνω-κάτω τώρα, αλλά…\p"
	.string "Η εκτόξευση του πυραύλου επίκειται!$"

MossdeepCity_SpaceCenter_1F_Text_HaywireButSuccessfulLaunchNumber:
	.string "Ξέρω ότι τα πράγματα είναι λίγο \n"
	.string "άνω-κάτω τώρα, αλλά…\p"
	.string "Ο πύραυλος εκτοξεύτηκε με ασφάλεια!\n"
	.string "Είναι η επιτυχημένη εκτόξευση no. {STR_VAR_1}!$"

MossdeepCity_SpaceCenter_1F_Text_RocketLaunchDemandsPerfection:
	.string "Μια εκτόξευση πυραύλου απαιτεί \n"
	.string "τελειότητα. Ούτε 1% περιθώριο \l"
	.string "λάθους δεν επιτρέπεται.\p"
	.string "Ακόμα κι αν είναι 99% εντάξει, \n"
	.string "όλο το πράγμα είναι άχρηστο αν το \l"
	.string "υπόλοιπο 1% δεν είναι καλό.\p"
	.string "Παρόλα αυτά, δεν σταματάμε ποτέ να \n"
	.string "προσπαθούμε. Γιατί; Είναι ένα όνειρο \l"
	.string "που δεν τελειώνει ποτέ.$"

MossdeepCity_SpaceCenter_1F_Text_MagmaHaveSightsOnSpaceCenter:
	.string "Αυτοί οι κακοποιοί της TEAM MAGMA \n"
	.string "έχουν βάλει στόχο το SPACE CENTER μας.\p"
	.string "Αλλά δεν μπορούμε να αφήσουμε κάτι \n"
	.string "τόσο ασήμαντο να εμποδίσει την \l"
	.string "εκτόξευση του πυραύλου μας!$"

MossdeepCity_SpaceCenter_1F_Text_FoundThisYouCanHaveIt:
	.string "Έκανα μια βόλτα στην παραλία \n"
	.string "όταν βρήκα αυτό.\p"
	.string "Δεν είναι κάτι που χρειάζομαι, \n"
	.string "οπότε μπορείς να το πάρεις.$"

MossdeepCity_SpaceCenter_1F_Text_HoennFamousForMeteorShowers:
	.string "Η περιοχή HOENN είναι φημισμένη για \n"
	.string "τις βροχές μετεωριτών εδώ και καιρό.$"

MossdeepCity_SpaceCenter_1F_Text_MagmaCantStealFuelTakeThis:
	.string "Δεν πρέπει να επιτρέψουμε στην \n"
	.string "TEAM MAGMA να κλέψει τα καύσιμα.\p"
	.string "Α, παρεμπιπτόντως, μπορείς να πάρεις \n"
	.string "αυτή την πέτρα που βρήκα στην παραλία.$"

MossdeepCity_SpaceCenter_1F_Text_CantStrollOnBeachWithMagma:
	.string "Με την TEAM MAGMA τριγύρω, μάλλον οι \n"
	.string "βόλτες στην παραλία δεν είναι πια \l"
	.string "ασφαλείς.$"

MossdeepCity_SpaceCenter_1F_Text_DidPokemonComeFromSpace:
	.string "Κάποιοι ισχυρίζονται ότι τα POKéMON \n"
	.string "ήρθαν από το διάστημα. Λες να \l"
	.string "είναι αλήθεια;$"

MossdeepCity_SpaceCenter_1F_Text_AquaShouldBeatMagma:
	.string "Η TEAM AQUA θα έπρεπε να \n"
	.string "ξεφορτωθεί την TEAM MAGMA!\p"
	.string "Αλλά αν το έκαναν αυτό, η TEAM AQUA \n"
	.string "θα γινόταν πιο τολμηρή και θρασύς, \l"
	.string "έτσι δεν είναι;$"

MossdeepCity_SpaceCenter_1F_Text_RocketsBoggleMyMind:
	.string "Ένα γιγάντιο κομμάτι μέταλλο διασχίζει \n"
	.string "τους ουρανούς και πετάει στο διάστημα…\p"
	.string "Το μυαλό μου σταματάει!$"

MossdeepCity_SpaceCenter_1F_Text_MagmaWantsToSpoilMyDream:
	.string "Ένα γιγάντιο κομμάτι μέταλλο διασχίζει \n"
	.string "τους ουρανούς και πετάει στο διάστημα…\p"
	.string "Αλλά η TEAM MAGMA θέλει να \n"
	.string "καταστρέψει αυτό το όνειρό μου!\p"
	.string "Δεν θα το επιτρέψω!$"

MossdeepCity_SpaceCenter_1F_Text_StevenMagmaCantBeAllowedToTakeFuel:
	.string "STEVEN: {PLAYER}, έχεις διαβάσει ήδη \n"
	.string "εκείνη την προκήρυξη;\p"
	.string "Η TEAM MAGMA έρχεται για τα καύσιμα \n"
	.string "πυραύλων σε αυτό το νησί.\p"
	.string "Δεν ξέρω τι τα θέλουν, αλλά δεν \n"
	.string "πρέπει να τους επιτραπεί να τα πάρουν.\p"
	.string "Θα παρακολουθώ την κατάσταση για \n"
	.string "λίγο ακόμα.\p"
	.string "Στο μεταξύ, γιατί δεν πας να \n"
	.string "ρίξεις μια ματιά στην πόλη;$"

MossdeepCity_SpaceCenter_1F_Text_Grunt3Intro:
	.string "Όπως υποσχεθήκαμε, ήρθαμε για \n"
	.string "τα καύσιμα των πυραύλων!$"

MossdeepCity_SpaceCenter_1F_Text_Grunt3Defeat:
	.string "Ξέμεινα από καύσιμα…$"

MossdeepCity_SpaceCenter_1F_Text_Grunt3PostBattle:
	.string "Μην νομίζεις ότι πήρες φόρα \n"
	.string "απλώς επειδή με νίκησες!$"

MossdeepCity_SpaceCenter_1F_Text_Grunt1Intro:
	.string "Σας προειδοποιήσαμε δίκαια!\n"
	.string "Δεν υπάρχει τίποτα ύπουλο σε εμάς!$"

MossdeepCity_SpaceCenter_1F_Text_Grunt1Defeat:
	.string "Γκρρρ…\n"
	.string "Έπρεπε να είχαμε χρησιμοποιήσει \l"
	.string "ύπουλες προδοσίες…$"

MossdeepCity_SpaceCenter_1F_Text_Grunt1PostBattle:
	.string "Εντάξει, το κατάλαβα ήδη! Την \n"
	.string "επόμενη φορά, θα έρθουμε απροειδοποίητα.$"

MossdeepCity_SpaceCenter_1F_Text_Grunt4Intro:
	.string "Τα καύσιμα πυραύλων που έχει το \n"
	.string "SPACE CENTER στην αποθήκη--αυτά \l"
	.string "ψάχνουμε.\p"
	.string "Σκοπεύουμε να πάρουμε και την \n"
	.string "τελευταία σταγόνα!$"

MossdeepCity_SpaceCenter_1F_Text_Grunt4Defeat:
	.string "Σε παρακαλώ, μπορείς να μας δώσεις \n"
	.string "λίγα καύσιμα; Έστω κι ένα \l"
	.string "ποτηράκι αρκεί!$"

MossdeepCity_SpaceCenter_1F_Text_Grunt4PostBattle:
	.string "Τι θα κάνουμε με τα καύσιμα \n"
	.string "των πυραύλων;\p"
	.string "Πού να ξέρω; Ρώτα τον αρχηγό \n"
	.string "μας πάνω!$"

MossdeepCity_SpaceCenter_1F_Text_Grunt2Intro:
	.string "Ο αρχηγός μας είπε ότι κανείς, \n"
	.string "μα απολύτως κανείς, δεν περνάει \l"
	.string "από μένα!$"

MossdeepCity_SpaceCenter_1F_Text_Grunt2Defeat:
	.string "Ακ! Ακ! Ααακ!$"

MossdeepCity_SpaceCenter_1F_Text_Grunt2PostBattle:
	.string "Σε παρακαλώ, πες στον αρχηγό μας \n"
	.string "ότι δεν εγκατέλειψα ποτέ τη \l"
	.string "θέση μου.\p"
	.string "Ότι έμεινα μέχρι το πικρό τέλος…$"

MossdeepCity_SpaceCenter_1F_Text_MagmaIntentToStealNotice:
	.string "Αυτό είναι…\n"
	.string "Μια ειδοποίηση κλοπής;\p"
	.string "“Προς το προσωπικό του \n"
	.string "SPACE CENTER: Πώς είστε; Εμείς \l"
	.string "είμαστε μια χαρά.\p"
	.string "“Θα σας επισκεφτούμε σύντομα για \n"
	.string "να πάρουμε τα καύσιμα των πυραύλων.\p"
	.string "“Παρακαλώ μην προσπαθήσετε να μας \n"
	.string "σταματήσετε. Θα τα πάρουμε ό,τι \l"
	.string "κι αν γίνει.\p"
	.string "“Ας υπάρχει περισσότερη στεριά!\n"
	.string "TEAM MAGMA”$"
