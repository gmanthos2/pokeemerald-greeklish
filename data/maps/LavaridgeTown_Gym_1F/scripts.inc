.set LOCALID_COLE, 2
.set LOCALID_GERALD, 3
.set LOCALID_AXLE, 4
.set LOCALID_DANIELLE, 5

LavaridgeTown_Gym_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_Gym_1F_OnTransition
	.byte 0

LavaridgeTown_Gym_1F_OnTransition:
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	call LavaridgeTown_Gym_1F_EventScript_CheckBuryTrainers
	end

@ Unclear where/if these temp vars are getting checked
LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars::
	setvar VAR_TEMP_B, 0
	setvar VAR_TEMP_C, 0
	setvar VAR_TEMP_D, 0
	setvar VAR_TEMP_E, 0
	setvar VAR_TEMP_F, 0
	goto_if_defeated TRAINER_COLE, LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar
	setvar VAR_TEMP_B, 1
LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar::
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar
	setvar VAR_TEMP_C, 1
LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar::
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar
	setvar VAR_TEMP_D, 1
LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar::
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars
	setvar VAR_TEMP_E, 1
LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars::
	return

LavaridgeTown_Gym_1F_EventScript_CheckBuryTrainers::
	goto_if_defeated TRAINER_COLE, LavaridgeTown_Gym_1F_EventScript_CheckBuryGerald
	setobjectmovementtype LOCALID_COLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryGerald::
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_CheckBuryAxle
	setobjectmovementtype LOCALID_GERALD, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryAxle::
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_CheckBuryDanielle
	setobjectmovementtype LOCALID_AXLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryDanielle::
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndCheckBuryTrainers
	setobjectmovementtype LOCALID_DANIELLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_EndCheckBuryTrainers::
	return

LavaridgeTown_Gym_1F_EventScript_Flannery::
	trainerbattle_single TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryIntro, LavaridgeTown_Gym_1F_Text_FlanneryDefeat, LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, LavaridgeTown_Gym_1F_EventScript_FlanneryRematch
	goto_if_unset FLAG_RECEIVED_TM_OVERHEAT, LavaridgeTown_Gym_1F_EventScript_GiveOverheat2
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostBattle, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated::
	message LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_WHITEOUT_TO_LAVARIDGE
	setflag FLAG_DEFEATED_LAVARIDGE_GYM
	setflag FLAG_BADGE04_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 4
	call Common_EventScript_SetGymTrainers
	setflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	setvar VAR_LAVARIDGE_TOWN_STATE, 1
	call LavaridgeTown_Gym_1F_EventScript_GiveOverheat
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox LavaridgeTown_Gym_1F_Text_RegisteredFlannery, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_FLANNERY_MATCH_CALL
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat2::
	giveitem ITEM_TM_OVERHEAT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_OVERHEAT
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat::
	giveitem ITEM_TM_OVERHEAT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_OVERHEAT
	return

LavaridgeTown_Gym_1F_EventScript_FlanneryRematch::
	trainerbattle_rematch_double TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryPreRematch, LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat, LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostRematch, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Cole::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_COLE, LOCALID_COLE, LavaridgeTown_Gym_1F_Text_ColeIntro, LavaridgeTown_Gym_1F_Text_ColeDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_ColePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_EventScript_CheckTrainerScript::
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	release
	special ShouldTryGetTrainerScript
	goto_if_eq VAR_RESULT, 1, EventScript_GotoTrainerScript
	end

LavaridgeTown_Gym_1F_EventScript_Axle::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_AXLE, LOCALID_AXLE, LavaridgeTown_Gym_1F_Text_AxleIntro, LavaridgeTown_Gym_1F_Text_AxleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_AxlePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Keegan::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_KEEGAN, LOCALID_KEEGAN, LavaridgeTown_Gym_B1F_Text_KeeganIntro, LavaridgeTown_Gym_B1F_Text_KeeganDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_KeeganPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Danielle::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_DANIELLE, LOCALID_DANIELLE, LavaridgeTown_Gym_1F_Text_DanielleIntro, LavaridgeTown_Gym_1F_Text_DanielleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_DaniellePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Gerald::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_GERALD, LOCALID_GERALD, LavaridgeTown_Gym_1F_Text_GeraldIntro, LavaridgeTown_Gym_1F_Text_GeraldDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_GeraldPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jace::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_JACE, LOCALID_JACE, LavaridgeTown_Gym_B1F_Text_JaceIntro, LavaridgeTown_Gym_B1F_Text_JaceDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_JacePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jeff::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_JEFF, LOCALID_JEFF, LavaridgeTown_Gym_B1F_Text_JeffIntro, LavaridgeTown_Gym_B1F_Text_JeffDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_JeffPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Eli::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_ELI, LOCALID_ELI, LavaridgeTown_Gym_B1F_Text_EliIntro, LavaridgeTown_Gym_B1F_Text_EliDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_EliPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory
	msgbox LavaridgeTown_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory::
	msgbox LavaridgeTown_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_GymStatueCertified::
	msgbox LavaridgeTown_Gym_1F_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_EventScript_GymStatue::
	msgbox LavaridgeTown_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_Text_GymGuideAdvice:
	.string "Γεια, πώς πάει, μελλοντικό\n"
	.string "CHAMPION {PLAYER};\p"
	.string "Η GYM LEADER του LAVARIDGE, \n"
	.string "η FLANNERY, χρησιμοποιεί\l"
	.string "POKéMON τύπου FIRE.\p"
	.string "Το πάθος της για τα POKéMON καίει \n"
	.string "πιο δυνατά και από έκρηξη ηφαιστείου.\p"
	.string "Μην την πλησιάσεις πολύ--θα καείς!\n"
	.string "Ρίξε της κρύο νερό και μετά\l"
	.string "προχώρα!$"

LavaridgeTown_Gym_1F_Text_GymGuidePostVictory:
	.string "Ουάου! Αυτή ήταν μια πολύ καυτή \n"
	.string "μάχη!$"

LavaridgeTown_Gym_1F_Text_ColeIntro:
	.string "Ουαουαουαουα!\n"
	.string "Αμάν, καίει!$"

LavaridgeTown_Gym_1F_Text_ColeDefeat:
	.string "Έχω τυφλωθεί από τον ιδρώτα…$"

LavaridgeTown_Gym_1F_Text_ColePostBattle:
	.string "Το να σε θάβουν στην καυτή άμμο\n"
	.string "προάγει την κυκλοφορία.\p"
	.string "Είναι αποτελεσματικό για την \n"
	.string "επούλωση του πόνου \l"
	.string "στις αρθρώσεις σου.$"

LavaridgeTown_Gym_1F_Text_AxleIntro:
	.string "Προσπαθώ να ανακουφιστώ.\n"
	.string "Μην έρχεσαι εδώ και με αγχώνεις!$"

LavaridgeTown_Gym_1F_Text_AxleDefeat:
	.string "Ελπίζω η FLANNERY να σε κάψει!$"

LavaridgeTown_Gym_1F_Text_AxlePostBattle:
	.string "Αααχ… Φιου…\p"
	.string "Αν περνάς πολύ χρόνο θαμμένο στην \n"
	.string "καυτή άμμο, σε εξαντλεί…$"

LavaridgeTown_Gym_B1F_Text_KeeganIntro:
	.string "Πρέπει να έχεις κουραστεί πια.\n"
	.string "Θα ήθελες να ξεκουραστείς στην\l"
	.string "καυτή άμμο, δεν νομίζεις;\p"
	.string "Αλλά θα πρέπει να ξέρεις ότι \n"
	.string "η διατήρηση της θέλησής σου είναι \l"
	.string "μια σημαντική ικανότητα για όλους\l"
	.string "τους TRAINERS.$"

LavaridgeTown_Gym_B1F_Text_KeeganDefeat:
	.string "Παίξε με τη φωτιά, και θα καείς…$"

LavaridgeTown_Gym_B1F_Text_KeeganPostBattle:
	.string "Η ικανότητά σου είναι πραγματική…\n"
	.string "Αλλά η LEADER μας,  είναι δυνατή.\p"
	.string "Αν δεν προσέχεις,\n"
	.string "θα καείς σοβαρά.$"

LavaridgeTown_Gym_1F_Text_GeraldIntro:
	.string "Μπορεί το POKéMON σου να αντέξει\n"
	.string "σε θερμοκρασία 392 βαθμών;$"

LavaridgeTown_Gym_1F_Text_GeraldDefeat:
	.string "Δεν έκαιγε αρκετά…$"

LavaridgeTown_Gym_1F_Text_GeraldPostBattle:
	.string "Η θερμοκρασία του μάγματος είναι\n"
	.string "392 βαθμοί.\p"
	.string "Τα POKéMON σου με νίκησαν, οπότε \n"
	.string "θα πρέπει εύκολα να επιζήσουν.$"

LavaridgeTown_Gym_1F_Text_DanielleIntro:
	.string "Εμ…\n"
	.string "Εντάξει, θα παλέψω μαζί σου.$"

LavaridgeTown_Gym_1F_Text_DanielleDefeat:
	.string "Ω, αλλά είσαι πολύ δυνατό.$"

LavaridgeTown_Gym_1F_Text_DaniellePostBattle:
	.string "Θα γίνω μια όμορφη και δυνατή\n"
	.string "TRAINER όπως η FLANNERY.$"

LavaridgeTown_Gym_B1F_Text_JaceIntro:
	.string "Έλα, πάμε!\n"
	.string "Ας πάμε πριν στερέψουν\l"
	.string "τα συναισθήματά μου!$"

LavaridgeTown_Gym_B1F_Text_JaceDefeat:
	.string "Κάνει τόση ζέστη, κι όμως η καρδιά \n"
	.string "μου πιάνεται από πάγο…$"

LavaridgeTown_Gym_B1F_Text_JacePostBattle:
	.string "Έτσι όπως καίει το μαχητικό πνεύμα\n"
	.string "μέσα σου, ίσως έχεις μια ευκαιρία\l"
	.string "απέναντι στη LEADER μας.$"

LavaridgeTown_Gym_B1F_Text_JeffIntro:
	.string "Βλέπεις πώς φουντώνουν οι φλόγες;\n"
	.string "Λάμπουν εν αναμονή της νίκης μου!$"

LavaridgeTown_Gym_B1F_Text_JeffDefeat:
	.string "Κάτι δεν πήγε καλά.$"

LavaridgeTown_Gym_B1F_Text_JeffPostBattle:
	.string "Λοιπόν, και τι έγινε; \n"
	.string "Μπορώ να περπατήσω σε καυτά κάρβουνα!\p"
	.string "…Μην το σκεφτείς καν να το προσπαθήσεις!$"

LavaridgeTown_Gym_B1F_Text_EliIntro:
	.string "Όσο κι αν αγαπώ τα βουνά,\n"
	.string "αγαπώ ιδιαίτερα τα ηφαίστεια.$"

LavaridgeTown_Gym_B1F_Text_EliDefeat:
	.string "Λοιπόν, μου φαίνεται ότι έχασα χωρίς\n"
	.string "καν να έχω τον έλεγχο.$"

LavaridgeTown_Gym_B1F_Text_EliPostBattle:
	.string "Μένω εδώ γιατί έγινα φαν\n"
	.string "της δύναμης της FLANNERY.\p"
	.string "Χεχεχεχε.$"

LavaridgeTown_Gym_1F_Text_FlanneryIntro:
	.string "Καλώς ήρθατε… Όχι, περίμενε.\p"
	.string "Μικρούλη TRAINER, πόσο καλό που βλέπω\n"
	.string "ότι τα κατάφερες να φτάσεις ως εδώ!\p"
	.string "Μου έχουν αναθέσει την…\n"
	.string "Όχι, περίμενε.\p"
	.string "Είμαι η FLANNERY, και είμαι η GYM\n"
	.string "LEADER εδώ!\p"
	.string "Εχμ…\n"
	.string "Μην τολμήσεις να με υποτιμήσεις, \l"
	.string "παρόλο που είμαι LEADER μόνο για \l"
	.string "λίγο καιρό!\p"
	.string "Με τις δεξιότητες που κληρονόμησα \n"
	.string "από τον παππού μου, θα, θα… σου \l"
	.string "δείξω τις καυτές κινήσεις μας!$"

LavaridgeTown_Gym_1F_Text_FlanneryDefeat:
	.string "Ω…\n"
	.string "Μάλλον προσπαθούσα πάρα πολύ…\p"
	.string "Εγώ… Ήμουν μόνο πρόσφατα\n"
	.string "GYM LEADER.\p"
	.string "Προσπάθησα πάρα πολύ να γίνω κάποια\n"
	.string "που δεν είμαι.\p"
	.string "Πρέπει να κάνω τα πράγματα με \n"
	.string "τον φυσικό μου τρόπο. Αν δεν το\l"
	.string "κάνω, τα POKéMON μου θα μπερδευτούν.\p"
	.string "Ευχαριστώ που μου το έμαθες αυτό.\n"
	.string "Γι' αυτό, σου αξίζει αυτό.$"

LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge:
	.string "Το {PLAYER} έλαβε το HEAT BADGE\n"
	.string "από τη FLANNERY.$"

LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis:
	.string "Εάν έχεις HEAT BADGE, όλα τα \n"
	.string "POKéMON μέχρι το επίπεδο 50, θα \l"
	.string "σε υπακούνε πλήρως.\p"
	.string "Και επιτρέπει στα POKéMON να\n"
	.string "χρησιμοποιούν το HM STRENGTH \l"
	.string "εκτός μάχης.\p"
	.string "Αυτό είναι ένα δείγμα της \n"
	.string "εκτίμησής μου. Παρ' το!$"

LavaridgeTown_Gym_1F_Text_ExplainOverheat:
	.string "Αυτό το TM50 περιέχει OVERHEAT.\p"
	.string "Αυτή η κίνηση προκαλεί σοβαρή \n"
	.string "ζημιά στον αντίπαλο.\p"
	.string "Αλλά μειώνει επίσης απότομα το\n"
	.string "SP. ATK του POKéMON που το \l"
	.string "χρησιμοποιεί.\l"
	.string "Μπορεί να μην είναι κατάλληλη \l"
	.string "για μεγαλύτερες μάχες.$"

LavaridgeTown_Gym_1F_Text_RegisteredFlannery:
	.string "H GYM LEADER FLANNERY\n"
	.string "προστέθηκε στο POKéNAV.$"

LavaridgeTown_Gym_1F_Text_FlanneryPostBattle:
	.string "Η δύναμή σου μου θυμίζει κάποιον…\p"
	.string "Α! Το ξέρω! Παλεύεις σαν τον NORMAN,\n"
	.string "τον GYM LEADER του PETALBURG.$"

LavaridgeTown_Gym_1F_Text_GymStatue:
	.string "LAVARIDGE TOWN POKéMON GYM$"

LavaridgeTown_Gym_1F_Text_GymStatueCertified:
	.string "LAVARIDGE TOWN POKéMON GYM\p"
	.string "FLANNERY'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"

LavaridgeTown_Gym_1F_Text_FlanneryPreRematch:
	.string "FLANNERY: Η απώλεια μιας μάχης \n"
	.string "δεν πρόκειται να με ξεφουσκώσει.\p"
	.string "Αγαπώ τα POKéMON.\n"
	.string "Αγαπώ τις μάχες.\l"
	.string "Και… Αγαπώ αυτό το GYM!\p"
	.string "Ας ανταλλάξουμε υπερκαυτές\n"
	.string "κινήσεις σε μια άλλη μάχη!$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat:
	.string "Ουφ!\n"
	.string "Στα πρόθυρα της έκρηξης!$"

LavaridgeTown_Gym_1F_Text_FlanneryPostRematch:
	.string "FLANNERY: Έχασα τον αγώνα,\n"
	.string "αλλά είμαι απόλυτα ικανοποιημένη.\p"
	.string "Δεν είναι συχνό να απολαμβάνω μια \n"
	.string "τόσο θερμή μάχη.\p"
	.string "Ας κάνουμε κι άλλη μια\n"
	.string "κάποια άλλη φορά!$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons:
	.string "FLANNERY: Το να χάσω μια μάχη \n"
	.string "δεν πρόκειται να με πτοήσει.\p"
	.string "Αγαπώ τα POKéMON.\n"
	.string "Λατρεύω να πολεμώ.\l"
	.string "Και… Αγαπώ αυτό το GYM!\p"
	.string "Ας ανταλλάξουμε σούπερ καυτές \n"
	.string "κινήσεις σε μια άλλη μάχη!\p"
	.string "Στάσου. Έχεις μαζί σου μόνο ένα \n"
	.string "στην ομάδα σου;\p"
	.string "Σιχαίνομαι που το λέω, αλλά\n"
	.string "όταν θα έρθεις να με ξαναδείς, \l"
	.string "φέρε τουλάχιστον δύο POKéMON.$"
