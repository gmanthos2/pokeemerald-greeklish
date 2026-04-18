.set LOCALID_RIVAL_ON_BIKE, 7
.set LOCALID_RIVAL, 8

LavaridgeTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LavaridgeTown_OnFrame
	.byte 0

LavaridgeTown_OnTransition:
	setflag FLAG_VISITED_LAVARIDGE_TOWN
	call_if_set FLAG_WHITEOUT_TO_LAVARIDGE, LavaridgeTown_EventScript_ClearLavaridgeWhiteOut
	call_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, LavaridgeTown_EventScript_ShowMtChimneyTrainers
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_CheckSetRivalPos
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_HideMapNamePopup
	end

LavaridgeTown_EventScript_ClearLavaridgeWhiteOut::
	clearflag FLAG_WHITEOUT_TO_LAVARIDGE
	return

LavaridgeTown_EventScript_CheckSetRivalPos::
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 9, LavaridgeTown_EventScript_SetRivalPos
	return

LavaridgeTown_EventScript_SetRivalPos::
	setobjectxyperm LOCALID_RIVAL, 11, 9
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 9, 8
	setobjectmovementtype LOCALID_RIVAL_ON_BIKE, MOVEMENT_TYPE_FACE_UP
	clearflag FLAG_HIDE_LAVARIDGE_TOWN_RIVAL
	return

LavaridgeTown_EventScript_ShowMtChimneyTrainers::
	clearflag FLAG_HIDE_MT_CHIMNEY_TRAINERS
	return

LavaridgeTown_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

LavaridgeTown_OnFrame:
	map_script_2 VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_RivalGiveGoGoggles
	.2byte 0

LavaridgeTown_EventScript_RivalGiveGoGoggles::
	lockall
	getplayerxy VAR_0x8008, VAR_0x8009
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalNoticePlayer
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExitHerbShop
	delay 20
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_PlayBrendanMusic
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer2
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_MayGiveGoGoggles
	goto_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_BrendanGiveGoGoggles
	end

LavaridgeTown_EventScript_MayGiveGoGoggles::
	msgbox LavaridgeTown_Text_MayNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_MayExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_BrendanGiveGoGoggles::
	msgbox LavaridgeTown_Text_BrendanNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_RivalExit::
	closemessage
	removeobject LOCALID_RIVAL
	addobject LOCALID_RIVAL_ON_BIKE
	delay 30
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit2
	removeobject LOCALID_RIVAL_ON_BIKE
	setvar VAR_LAVARIDGE_TOWN_STATE, 2
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LavaridgeTown_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

LavaridgeTown_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

LavaridgeTown_EventScript_RivalNoticePlayer::
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExitHerbShop::
	opendoor 12, 15
	waitdooranim
	addobject LOCALID_RIVAL
	applymovement LOCALID_RIVAL, LavaridgeTown_Movement_RivalExitHerbShop
	waitmovement 0
	closedoor 12, 15
	waitdooranim
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer1::
	applymovement LOCALID_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer2::
	applymovement LOCALID_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer2
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit1::
	applymovement OBJ_EVENT_ID_PLAYER, LavaridgeTown_Movement_PlayerWatchRivalExit
	applymovement LOCALID_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit2::
	applymovement LOCALID_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit2
	waitmovement 0
	return

LavaridgeTown_Movement_RivalExit2:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LavaridgeTown_Movement_PlayerWatchRivalExit:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LavaridgeTown_Movement_RivalExit1:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

LavaridgeTown_Movement_RivalApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LavaridgeTown_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	walk_up
	step_end

LavaridgeTown_Movement_RivalExitHerbShop:
	walk_down
	step_end

LavaridgeTown_EventScript_HotSpringsTrigger::
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_SOUTH, LavaridgeTown_EventScript_EnteredHotSprings
	end

LavaridgeTown_EventScript_EnteredHotSprings::
	incrementgamestat GAME_STAT_ENTERED_HOT_SPRINGS
	end

LavaridgeTown_EventScript_ExpertM::
	msgbox LavaridgeTown_Text_HotSpringsNeverRunDry, MSGBOX_NPC
	end

LavaridgeTown_EventScript_OldMan::
	msgbox LavaridgeTown_Text_PokemonNippedBackside, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_Twin::
	msgbox LavaridgeTown_Text_BatheInHotSpringsEveryDay, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman1::
	msgbox LavaridgeTown_Text_IfPokemonInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman2::
	msgbox LavaridgeTown_Text_HotSpringsClaims, MSGBOX_NPC
	end

LavaridgeTown_EventScript_ExpertF::
	msgbox LavaridgeTown_Text_OhYouLikeHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_EggWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_LAVARIDGE_EGG, LavaridgeTown_EventScript_ReceivedEgg
	msgbox LavaridgeTown_Text_HaveEggWillYouTakeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LavaridgeTown_EventScript_DeclineEgg
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, LavaridgeTown_EventScript_NoRoomForEgg
	msgbox LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_LAVARIDGE_EGG
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
	giveegg SPECIES_WYNAUT
	release
	end

LavaridgeTown_EventScript_ReceivedEgg::
	msgbox LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_NoRoomForEgg::
	msgbox LavaridgeTown_Text_NoRoomForThisEgg, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_DeclineEgg::
	msgbox LavaridgeTown_Text_AsYouWishThen, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_TownSign::
	msgbox LavaridgeTown_Text_TownSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_GymSign::
	msgbox LavaridgeTown_Text_GymSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_HerbShopSign::
	msgbox LavaridgeTown_Text_HerbShopSign, MSGBOX_SIGN
	end

LavaridgeTown_Text_MayNiceBadgesTakeThis:
	.string "MAY: {PLAYER}{KUN}! Καιρό έχουμε να τα πούμε!\p"
	.string "Ω; Ενώ επισκέφτηκα τις θερμές πηγές,\n"
	.string "εσύ πήρες το LAVARIDGE GYM BADGE.\p"
	.string "Πρέπει να έχεις συλλέξει \n"
	.string "καλά POKéMON…\l"
	.string "Όχι, πιστεύω ότι έχεις \l"
	.string "μεγαλώσει μερικά.\p"
	.string "Υποθέτω ότι θα ήταν εντάξει για\n"
	.string "σένα να το έχεις αυτό.$"

LavaridgeTown_Text_MayExplainGoGogglesChallengeDad:
	.string "MAY: Με αυτά τα GO-GOGGLES, \n"
	.string "δε θα έχεις πρόβλημα να περάσεις\l"
	.string "την έρημο κοντά στο ROUTE 111.\p"
	.string "Μα, γουάου, {PLAYER}{KUN}…\n"
	.string "Το να προκαλείς GYMS…\p"
	.string "Προσπαθείς σκληρά γιατί δεν\n"
	.string "θέλεις να χάσεις από εμένα, \l"
	.string "στοιχηματίζω!\p"
	.string "{PLAYER}{KUN}, νομίζω ότι πρέπει \n"
	.string "να προκαλέσω τον μπαμπά σου \l"
	.string "στο PETALBURG GYM.\p"
	.string "Τα λέμε πάλι!$"

LavaridgeTown_Text_BrendanNiceBadgesTakeThis:
	.string "BRENDAN: Έι {PLAYER}, \n"
	.string "πάει καιρός. Πώς πάει;\p"
	.string "Χμμ…\n"
	.string "Αυτή είναι μια καλή συλλογή \l"
	.string "από BADGES.\p"
	.string "Εντάξει, λοιπόν.\n"
	.string "Μπορείς και εσύ να έχεις αυτό.$"

LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad:
	.string "BRENDAN: Κράτα τα μαζί σου αν  \n"
	.string "σκοπεύεις να πας σε \l"
	.string "αυτήν την έρημο κοντά \l"
	.string "στο ROUTE 111.\p"
	.string "Πρέπει να υπάρχουν εκεί POKéMON που\n"
	.string "κατοικούν αποκλειστικά στην έρημο.\l"
	.string "Μπορείς να ψάξεις για αυτά.\p"
	.string "Όσο για μένα…\n"
	.string "Σκέφτομαι να προκαλέσω τον NORMAN,\l"
	.string "τον GYM LEADER του PETALBURG.\p"
	.string "Σε αντίθεση με εσένα, {PLAYER}, \n"
	.string "ο μπαμπάς σου φαίνεται \l"
	.string "ότι είναι πραγματικά σκληρός.\p"
	.string "Τα λέμε!$"

LavaridgeTown_Text_HaveEggWillYouTakeIt:
	.string "Έχω εδώ ένα EGG.\p"
	.string "Ήλπιζα να το εκκολάψω καλύπτοντάς\n"
	.string "το με καυτή άμμο στις \l"
	.string "θερμές πηγές.\l"
	.string "Αλλά αυτό δεν φαίνεται\l"
	.string "να είναι αρκετό…\p"
	.string "Άκουσα ότι θα ήταν καλύτερο\n"
	.string "να κρατηθεί μαζί με POKéMON \l"
	.string "και να το κουβαλάς.\p"
	.string "Είσαι TRAINER, ναι;\n"
	.string "Και τα POKéMON σου \l"
	.string "ακτινοβολούν ζωντάνια.\p"
	.string "Λοιπόν, τι λες;\n"
	.string "Θα πάρεις αυτό \l"
	.string "το EGG για να το εκκολάψεις;$"

LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg:
	.string "Ωραία! Ελπίζω να περπατήσεις πολύ\n"
	.string "με αυτό το EGG!$"

LavaridgeTown_Text_ReceivedTheEgg:
	.string "Το {PLAYER} έλαβε το EGG.$"

LavaridgeTown_Text_NoRoomForThisEgg:
	.string "Ω; Έχεις πάρα πολλά POKéMON.\n"
	.string "Δεν υπάρχει χώρος για αυτό το EGG…$"

LavaridgeTown_Text_AsYouWishThen:
	.string "Όπως επιθυμείς, λοιπόν…\p"
	.string "Αν αλλάξεις γνώμη \n"
	.string "για την εκκόλαψη αυτού του EGG, \l"
	.string "θα είμαι εδώ.$"

LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare:
	.string "Κάθε τόσο, ένα EGG θα βρίσκεται \n"
	.string "στον POKéMON DAY CARE.\p"
	.string "Ή τουλάχιστον έτσι λέει η φήμη.$"

LavaridgeTown_Text_HotSpringsNeverRunDry:
	.string "Τραβάμε όσο ζεστό νερό χρειαζόμαστε,\n"
	.string "κι όμως οι θερμές πηγές \l"
	.string "δεν στερεύουν ποτέ.\p"
	.string "Δεν είναι μαγικό;\p"
	.string "Αυτές οι θερμές πηγές εμφανίζονται\n"
	.string "κοντά σε ενεργά ηφαίστεια. \l"
	.string "Οι φλέβες νερού κάτω από \l"
	.string "το έδαφος θερμαίνονται \l"
	.string "από το μάγμα \l"
	.string "και αναβλύζουν ως θερμές πηγές.$"

LavaridgeTown_Text_PokemonNippedBackside:
	.string "Το να είσαι θαμμένος\n"
	.string "σε αυτή την καυτή άμμο είναι…\n"
	.string "Αααχ…\p"
	.string "Τόσο ζεστό και παραδεισένιο…\p"
	.string "Ε; Γκιάα! Άουτς!\p"
	.string "Ένα POKéMON δάγκωσε τα οπίσθιά μου!$"

LavaridgeTown_Text_OhYouLikeHotSprings:
	.string "Α, σου αρέσουν οι θερμές \n"
	.string "πηγές, ε;\p"
	.string "Αυτό είναι έκπληξη για τόσο μικρό\n"
	.string "παιδί όσο εσύ.$"

LavaridgeTown_Text_BatheInHotSpringsEveryDay:
	.string "Κάνω μπάνιο στις θερμές \n"
	.string "πηγές κάθε μέρα.\p"
	.string "Θέλω να γίνω μια όμορφη και \n"
	.string "δυνατή GYM LEADER όπως η FLANNERY.$"

LavaridgeTown_Text_IfPokemonInHotSprings:
	.string "Αν οι άνθρωποι έβαζαν POKéMON \n"
	.string "σε θερμές πηγές,\l"
	.string "μπορεί να ήταν πολύ περίεργο.\p"
	.string "Γιατί μπορεί να ήταν ένα \n"
	.string "ηλεκτρικό μπάνιο, ή ένα \l"
	.string "αφρόλουτρο, \l"
	.string "ή ακόμα και ένα λουτρό λάβας…$"

LavaridgeTown_Text_HotSpringsClaims:
	.string "Ισχυρίζονται ότι αυτές οι θερμές\n"
	.string "πηγές είναι καλές για την ηρεμία \l"
	.string "της νευρικής έντασης, την \l"
	.string "ανακούφιση μυϊκών πόνων, την\l"
	.string "επίλυση ρομαντικών προβλημάτων \l"
	.string "και την προσέλκυση χρημάτων…$"

LavaridgeTown_Text_TownSign:
	.string "LAVARIDGE TOWN\p"
	.string "“POKéMON CENTER HOT SPRINGS\n"
	.string "Ένα εξαιρετικό μέρος \l"
	.string "για χαλάρωση!”$"

LavaridgeTown_Text_GymSign:
	.string "LAVARIDGE TOWN POKéMON GYM\n"
	.string "LEADER: FLANNERY\l"
	.string "“Μία με φλογερό πάθος που καίει!”$"

LavaridgeTown_Text_HerbShopSign:
	.string "POKéMON HERB SHOP\n"
	.string "“Πικρή γεύση - καλύτερη θεραπεία!”$"

