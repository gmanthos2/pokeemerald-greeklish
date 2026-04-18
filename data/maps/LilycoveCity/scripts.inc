.set LOCALID_WOMAN_1, 19
.set LOCALID_MAN_1, 20

LilycoveCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, LilycoveCity_OnLoad
	.byte 0

LilycoveCity_OnTransition:
	setflag FLAG_VISITED_LILYCOVE_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_HIDE_LILYCOVE_CONTEST_HALL_REPORTER
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	call Common_EventScript_SetupRivalGfxId
	end

LilycoveCity_OnLoad:
	call_if_unset FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_SetWailmerMetatiles
	end

LilycoveCity_EventScript_SetWailmerMetatiles::
	setmetatile 76, 12, METATILE_Lilycove_Wailmer0, TRUE
	setmetatile 77, 12, METATILE_Lilycove_Wailmer1, TRUE
	setmetatile 76, 13, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 13, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 76, 14, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 77, 14, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 76, 15, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 15, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 77, 16, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 78, 16, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 77, 17, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 78, 17, METATILE_Lilycove_Wailmer3, TRUE
	return

LilycoveCity_EventScript_BerryGentleman::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_LILYCOVE_RECEIVED_BERRY, LilycoveCity_EventScript_ReceivedBerry
	msgbox LilycoveCity_Text_BerrySuitsYou, MSGBOX_DEFAULT
	random 10
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_LILYCOVE_RECEIVED_BERRY
	msgbox LilycoveCity_Text_BecauseYoureTrainer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ReceivedBerry::
	msgbox LilycoveCity_Text_PokeblocksSuitPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man3::
	msgbox LilycoveCity_Text_ContestHallInTown, MSGBOX_NPC
	end

LilycoveCity_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_GirlAquaGone
	msgbox LilycoveCity_Text_StrangeCaveInCove, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_GirlAquaGone::
	msgbox LilycoveCity_Text_GoingToMoveDeleterForHMs, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_RichBoy::
	msgbox LilycoveCity_Text_ImFromKanto, MSGBOX_NPC
	end

LilycoveCity_EventScript_Sailor2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Sailor2AquaGone
	msgbox LilycoveCity_Text_TeamAquaBeenTrainingWailmer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor2AquaGone::
	msgbox LilycoveCity_Text_SomeonePuntedTeamAquaOut, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Woman2AquaGone
	msgbox LilycoveCity_Text_SomeoneStoleMyPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2AquaGone::
	msgbox LilycoveCity_Text_MissingPokemonCameBack, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man2::
	msgbox LilycoveCity_Text_ImArtDealer, MSGBOX_NPC
	end

LilycoveCity_EventScript_ExpertM1::
	msgbox LilycoveCity_Text_SeaRemainsForeverYoung, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertF::
	msgbox LilycoveCity_Text_SixtyYearsAgoHusbandProposed, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertM2::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_ExpertM2AquaGone
	msgbox LilycoveCity_Text_TeamAquaRenovatedCavern, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ExpertM2AquaGone::
	msgbox LilycoveCity_Text_TeamAquaLotGoneForGood, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor1::
	msgbox LilycoveCity_Text_HeardTowerCalledSkyPillar, MSGBOX_NPC
	end

LilycoveCity_EventScript_FatMan::
	msgbox LilycoveCity_Text_SawTallTowerOnRoute131, MSGBOX_NPC
	end

LilycoveCity_EventScript_Man1::
	lockall
	msgbox LilycoveCity_Text_JustArrivedAndSawRarePokemon, MSGBOX_NPC
	applymovement LOCALID_MAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_Woman1::
	lockall
	msgbox LilycoveCity_Text_HoneymoonVowToSeeRarePokemon, MSGBOX_NPC
	applymovement LOCALID_WOMAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_CitySign::
	msgbox LilycoveCity_Text_CitySign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ContestHallSign::
	msgbox LilycoveCity_Text_ContestHallSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MotelSign::
	msgbox LilycoveCity_Text_MotelSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MuseumSign::
	lockall
	specialvar VAR_0x8004, CountPlayerMuseumPaintings
	switch VAR_0x8004
	case 0, LilycoveCity_EventScript_MuseumSignNoPaintings
	msgbox LilycoveCity_Text_MuseumSignPlayersExhibit, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_MuseumSignNoPaintings::
	msgbox LilycoveCity_Text_MuseumSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_HarborSignFerryReady
	msgbox LilycoveCity_Text_HarborSignUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSignFerryReady::
	msgbox LilycoveCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_TrainerFanClubSign::
	msgbox LilycoveCity_Text_TrainerFanClubSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_DepartmentStoreSign::
	msgbox LilycoveCity_Text_DepartmentStoreSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MoveDeletersHouseSign::
	msgbox LilycoveCity_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_WailmerTrainerGrunt::
	lockall
	goto_if_set FLAG_MET_WAILMER_TRAINER, LilycoveCity_EventScript_MetWailmerTrainer
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_Text_GetLostMessingUpTraining, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_MET_WAILMER_TRAINER
	releaseall
	end

LilycoveCity_EventScript_MetWailmerTrainer::
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_AquaGrunt1::
	msgbox LilycoveCity_Text_MovedLootIntoHideoutToday, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt2::
	msgbox LilycoveCity_Text_ChanceToDoBigThings, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt3::
	msgbox LilycoveCity_Text_DontGoNearCaveInCove, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt4::
	msgbox LilycoveCity_Text_IfWorldBecomesOurs, MSGBOX_NPC
	end

LilycoveCity_EventScript_Rival::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LilycoveCity_EventScript_May
	goto_if_eq VAR_RESULT, FEMALE, LilycoveCity_EventScript_Brendan
	end

LilycoveCity_EventScript_May::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineMayBattle
	msgbox LilycoveCity_Text_MayWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleMayTreecko
	case 1, LilycoveCity_EventScript_BattleMayTorchic
	case 2, LilycoveCity_EventScript_BattleMayMudkip
	end

LilycoveCity_EventScript_MayAskToBattleAgain::
	msgbox LilycoveCity_Text_MayBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_MayAskToBattle::
	msgbox LilycoveCity_Text_MayShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineMayBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_MayNotRaisingPokemon, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_Brendan::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineBrendanBattle
	msgbox LilycoveCity_Text_BrendanWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleBrendanTreecko
	case 1, LilycoveCity_EventScript_BattleBrendanTorchic
	case 2, LilycoveCity_EventScript_BattleBrendanMudkip
	end

LilycoveCity_EventScript_BrendanAskToBattleAgain::
	msgbox LilycoveCity_Text_BrendanBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_BrendanAskToBattle::
	msgbox LilycoveCity_Text_BrendanShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineBrendanBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_BattleMayTreecko::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TREECKO, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayTorchic::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TORCHIC, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayMudkip::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_MUDKIP, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleBrendanTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TREECKO, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TORCHIC, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_MUDKIP, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_DefeatedMay::
	msgbox LilycoveCity_Text_MayGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_MayCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_MayPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_PICHU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_CheckFinalBadge::
	goto_if_set FLAG_BADGE08_GET, LilycoveCity_EventScript_HasFinalBadge
	return

LilycoveCity_EventScript_HasFinalBadge::
	setvar VAR_RESULT, TRUE
	return

LilycoveCity_EventScript_MayCollectBadges::
	msgbox LilycoveCity_Text_MayYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_MayBattleFrontier
	msgbox LilycoveCity_Text_MayYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayBattleFrontier::
	msgbox LilycoveCity_Text_MayYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DefeatedBrendan::
	msgbox LilycoveCity_Text_BrendanGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_BrendanCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_BrendanPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_SWABLU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_BrendanCollectBadges::
	msgbox LilycoveCity_Text_BrendanYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_BrendanBattleFrontier
	msgbox LilycoveCity_Text_BrendanYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanBattleFrontier::
	msgbox LilycoveCity_Text_BrendanYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_RivalFlyAway::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject VAR_LAST_TALKED
	waitfieldeffect FLDEFF_NPCFLY_OUT
	savebgm MUS_DUMMY
	fadedefaultbgm
	setflag FLAG_MET_RIVAL_LILYCOVE
	release
	end

LilycoveCity_EventScript_SchoolKidM::
	lock
	faceplayer
	msgbox LilycoveCity_Text_DoYouKnowAboutBerryBlender, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, LilycoveCity_EventScript_KnowAboutBerryBlender
	call_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DontKnowAboutBerryBlender
	release
	end

LilycoveCity_EventScript_KnowAboutBerryBlender::
	msgbox LilycoveCity_Text_FasterSpinBetterPokeblocks, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DontKnowAboutBerryBlender::
	msgbox LilycoveCity_Text_ExplainBerryBlender, MSGBOX_DEFAULT
	return

LilycoveCity_Text_MayShoppingLetsBattle:
	.string "MAY: Ωπ, γεια;\n"
	.string "{PLAYER}{KUN}, ψωνίζεις κι εσύ;\p"
	.string "Αγόρασα ένα σωρό DOLLS και \n"
	.string "POSTERS.\p"
	.string "Φυσικά, έχω πιάσει και πολλά \n"
	.string "POKéMON, και τα εκπαιδεύω \l"
	.string "σωστά, επίσης.\p"
	.string "Βασικά, πιο πολύ ανησυχώ αν εσύ \n"
	.string "εκπαιδεύεις τα POKéMON σου σωστά, \l"
	.string "{PLAYER}{KUN}.\p"
	.string "Θα παλέψω μαζί σου, για να μπορέσεις να \n"
	.string "μου δείξεις τα POKéMON σου, {PLAYER}{KUN}.$"

LilycoveCity_Text_MayNotRaisingPokemon:
	.string "MAY: Ω, γιατί; {PLAYER}{KUN}, δεν \n"
	.string "εκπαιδεύεις τα POKéMON σου;\p"
	.string "Αυτή δεν είναι πολύ καλή εμφάνιση \n"
	.string "για έναν TRAINER…$"

LilycoveCity_Text_MayBattleMe:
	.string "MAY: Έλα, πάλεψε μαζί μου, για να \n"
	.string "τσεκάρω τα POKéMON σου!$"

LilycoveCity_Text_MayWontBeBeaten:
	.string "MAY: Τα POKéMON που μεγάλωσα δεν θα \n"
	.string "νικηθούν από τα POKéMON σου, {PLAYER}{KUN}!$"

LilycoveCity_Text_MayDefeat:
	.string "… … … … … … … …\p"
	.string "Θυμάμαι τη μάχη που είχαμε,\n"
	.string "{PLAYER}{KUN}, στην ROUTE 103.\p"
	.string "Αυτή η μάχη σε βοήθησε να γίνεις τόσο \n"
	.string "δυνατός, {PLAYER}{KUN}, έτσι δεν είναι;$"

LilycoveCity_Text_MayGoingBackToLittleroot:
	.string "MAY: Σκέφτομαι να επιστρέψω στο \n"
	.string "LITTLEROOT σύντομα.\p"
	.string "Έχω πιάσει μια καλή ομάδα POKéMON,\n"
	.string "και το POKéDEX μου προχωράει, οπότε \l"
	.string "πάω σπίτι να το δείξω στον μπαμπά μου.$"

LilycoveCity_Text_MayYouGoingToCollectBadges:
	.string "{PLAYER}{KUN}, τι σκοπεύεις να κάνεις;\p"
	.string "Θα συλλέξεις όλα τα GYM BADGES και θα \n"
	.string "αναλάβεις την πρόκληση του POKéMON \l"
	.string "LEAGUE;\p"
	.string "Λοιπόν, όσο συλλέγεις BADGES,\n"
	.string "{PLAYER}{KUN}, εγώ θα δουλέψω στο POKéDEX \l"
	.string "μου. Θα το ολοκληρώσω πριν από σένα!\p"
	.string "Τα λέμε!$"

LilycoveCity_Text_MayYouGoingToPokemonLeague:
	.string "{PLAYER}{KUN}, τι σκοπεύεις να κάνεις;\p"
	.string "Αναλαμβάνεις την πρόκληση του \n"
	.string "POKéMON LEAGUE;\p"
	.string "Ή σκοπεύεις να ολοκληρώσεις το \n"
	.string "POKéDEX σου;\p"
	.string "Μπορεί να έχασα από σένα στη μάχη,\n"
	.string "αλλά θα τελειώσω το POKéDEX μου \l"
	.string "πριν από σένα!\p"
	.string "Τα λέμε!$"

LilycoveCity_Text_MayYouGoingToBattleFrontier:
	.string "{PLAYER}{KUN}, τι σκοπεύεις να κάνεις;\p"
	.string "Αναλαμβάνεις την πρόκληση του \n"
	.string "BATTLE FRONTIER;\p"
	.string "Ή σκοπεύεις να ολοκληρώσεις το \n"
	.string "POKéDEX σου;\p"
	.string "Μπορεί να έχασα από σένα στη μάχη,\n"
	.string "αλλά θα τελειώσω το POKéDEX μου \l"
	.string "πριν από σένα!\p"
	.string "Τα λέμε!$"

LilycoveCity_Text_BrendanShoppingLetsBattle:
	.string "BRENDAN: Ω, γεια, είσαι εσύ, {PLAYER}.\p"
	.string "Κάνω ένα θέλημα για τον μπαμπά μου.\n"
	.string "Όχι, δεν αγοράζω DOLLS.\p"
	.string "Τέλος πάντων, πάει καιρός.\p"
	.string "Θέλεις να παλέψουμε για να δούμε \n"
	.string "ποιος μεγαλώνει καλύτερα τα POKéMON;$"

LilycoveCity_Text_BrendanNoConfidence:
	.string "BRENDAN: Ω, τι τρέχει;\n"
	.string "Δεν έχεις αυτοπεποίθηση;$"

LilycoveCity_Text_BrendanBattleMe:
	.string "BRENDAN: Θες να παλέψουμε για να δούμε \n"
	.string "ποιος μεγαλώνει καλύτερα τα POKéMON;$"

LilycoveCity_Text_BrendanWontBeBeaten:
	.string "BRENDAN: Α, αλλά ξέρεις ότι δεν \n"
	.string "πρόκειται να χάσω από κανένα {PLAYER}.$"

LilycoveCity_Text_BrendanDefeat:
	.string "Χμ…\n"
	.string "Έχεις κάνει πολλή προπόνηση.\p"
	.string "Αυτό τσούζει λίγο--είχα ένα \n"
	.string "προβάδισμα από σένα ως TRAINER…$"

LilycoveCity_Text_BrendanGoingBackToLittleroot:
	.string "BRENDAN: Εγώ…\n"
	.string "Σκοπεύω να πάω σπίτι στο LITTLEROOT.\p"
	.string "Ξέρεις, βοηθάω τον μπαμπά μου με το \n"
	.string "POKéDEX. Πάει αρκετά καλά,\l"
	.string "οπότε θα πάω να του το δείξω.$"

LilycoveCity_Text_BrendanYouGoingToCollectBadges:
	.string "{PLAYER}, τι σκοπεύεις να κάνεις;\p"
	.string "Θα μαζέψεις όλα τα GYM BADGES και θα \n"
	.string "αναλάβεις την πρόκληση του \l"
	.string "POKéMON LEAGUE;\p"
	.string "Ίσως το κάνω κι εγώ…\p"
	.string "Λοιπόν, όπως και να 'χει, κράτα γερά!$"

LilycoveCity_Text_BrendanYouGoingToPokemonLeague:
	.string "{PLAYER}, τι σκοπεύεις να κάνεις;\p"
	.string "Αφού είσαι τόσο δυνατός,\n"
	.string "θα αναλάβεις την πρόκληση του \l"
	.string "POKéMON LEAGUE;\p"
	.string "Χε, ακόμα κι εγώ--αν προπονήσω λίγο \n"
	.string "περισσότερο τα POKéMON μου,\l"
	.string "θα πρέπει να είμαι πιο \l"
	.string "δυνατός από σένα, {PLAYER}.\p"
	.string "Λοιπόν, όπως και να 'χει, κράτα γερά!$"

LilycoveCity_Text_BrendanYouGoingToBattleFrontier:
	.string "{PLAYER}, τι σκοπεύεις να κάνεις;\p"
	.string "Θα αναλάβεις την πρόκληση του \n"
	.string "BATTLE FRONTIER;\p"
	.string "Ή σκοπεύεις να ολοκληρώσεις το \n"
	.string "POKéDEX σου;\p"
	.string "Αφού είσαι τόσο δυνατός, θα έπρεπε να \n"
	.string "σκεφτείς το BATTLE FRONTIER.\p"
	.string "Χε, αν προπονήσω τα POKéMON μου λίγο \n"
	.string "παραπάνω, θα γίνω πιο δυνατός \l"
	.string "από σένα, {PLAYER}.\p"
	.string "Ίσως και να πρέπει να πάω \n"
	.string "στο BATTLE FRONTIER.\p"
	.string "Λοιπόν, όπως και να 'χει, κράτα γερά!$"

LilycoveCity_Text_MovedLootIntoHideoutToday:
	.string "Φουφουφου…\p"
	.string "Μεταφέραμε περισσότερα λάφυρα στο \n"
	.string "μυστικό μας HIDEOUT σήμερα…\p"
	.string "Π-ποιος είσαι;\n"
	.string "Απλά μιλούσα στον εαυτό μου!$"

LilycoveCity_Text_ChanceToDoBigThings:
	.string "Είμαι απλά ένας GRUNT, οπότε δεν \n"
	.string "ξέρω τι σκέφτεται ο BOSS…\p"
	.string "Αλλά όντας στην TEAM AQUA, ξέρω ότι θα \n"
	.string "έχω την ευκαιρία να \l"
	.string "κάνω μεγάλα πράγματα!\p"
	.string "Π-ποιος είσαι;\n"
	.string "Απλά μιλούσα στον εαυτό μου!$"

LilycoveCity_Text_DontGoNearCaveInCove:
	.string "Έι, εσύ!\p"
	.string "Μην πλησιάζεις τη σπηλιά \n"
	.string "στον όρμο!\p"
	.string "Γιατί; Δεν χρειάζεσαι το γιατί!\n"
	.string "Είμαι ενήλικας, οπότε άκουσέ με!$"

LilycoveCity_Text_IfWorldBecomesOurs:
	.string "Αν όλος αυτός ο κόσμος γίνει δικός μας,\n"
	.string "της TEAM AQUA, θα είναι ένα πιο χαρούμενο \l"
	.string "μέρος και για τα POKéMON.$"

LilycoveCity_Text_WailmerLeapOutOfWater:
	.string "Εκεί! WAILMER!\n"
	.string "Πήδα έξω από το νερό τώρα!$"

LilycoveCity_Text_GetLostMessingUpTraining:
	.string "Ε; Τι θες;\p"
	.string "Μας χαλάς την προπόνηση,\n"
	.string "μπορείς, τύπου, να χαθείς;$"

LilycoveCity_Text_ContestHallInTown:
	.string "Υπάρχει ένα POKéMON CONTEST HALL\n"
	.string "ακριβώς εδώ σ' αυτή την πόλη. \p"
	.string "Αυτό σημαίνει ότι καλοαναθρεμμένα \n"
	.string "POKéMON θα έρθουν από \l"
	.string "όλη τη χώρα.\p"
	.string "Η καρδιά μου φουσκώνει \n"
	.string "από ενθουσιασμό!$"

LilycoveCity_Text_StrangeCaveInCove:
	.string "Έχεις δει αυτήν την παράξενη σπηλιά\n"
	.string "στον όρμο στην άκρη της πόλης;$"

LilycoveCity_Text_GoingToMoveDeleterForHMs:
	.string "Πάω να μάθω στο POKéMON μου κάποιες νέες \n"
	.string "κινήσεις για να μπω σε ένα CONTEST.\p"
	.string "Λοιπόν, πάω να δω τον MOVE DELETER\n"
	.string "για να το κάνω να ξεχάσει HM κινήσεις.$"

LilycoveCity_Text_ImFromKanto:
	.string "Ήρθα από το KANTO.\p"
	.string "Η περιοχή HOENN είναι πανέμορφη με \n"
	.string "όλο της το νερό και τη φύση.\p"
	.string "Ε; Περίμενε ένα λεπτό…\p"
	.string "Μπορεί να υπάρχουν σπάνια POKéMON που \n"
	.string "ζουν μόνο σε αυτήν την περιοχή;$"

LilycoveCity_Text_TeamAquaBeenTrainingWailmer:
	.string "Η TEAM AQUA προπονεί τα \n"
	.string "WAILMER της στον όρμο.\p"
	.string "Εμείς οι SAILORS δεν μπορούμε να \n"
	.string "βγάλουμε τις βάρκες μας στη θάλασσα \l"
	.string "με αυτούς στη μέση!$"

LilycoveCity_Text_SomeonePuntedTeamAquaOut:
	.string "Oέο, το ήξερες;\p"
	.string "Κάποιος έδιωξε την TEAM AQUA από \n"
	.string "τη μέση για μας!\p"
	.string "Αυτό έβγαλε τα WAILMER από τον όρμο,\n"
	.string "οπότε μπορούμε να ξαναβγάλουμε \l"
	.string "τις βάρκες μας.$"

LilycoveCity_Text_SomeoneStoleMyPokemon:
	.string "Έπαιρνα έναν χαλαρωτικό υπνάκο στο\n"
	.string "παραθαλάσσιο πανδοχείο με \l"
	.string "τον ήχο των κυμάτων…\p"
	.string "Όταν κάποιος έκλεψε το POKéMON μου!\p"
	.string "Ποιος είναι ο απαγωγέας;\n"
	.string "Η TEAM AQUA; Είναι η TEAM AQUA;$"

LilycoveCity_Text_MissingPokemonCameBack:
	.string "Το χαμένο μου POKéMON…\n"
	.string "Επέστρεψε χωρίς να το καταλάβω!$"

LilycoveCity_Text_ImArtDealer:
	.string "Είμαι ένας ART DEALER.\p"
	.string "Αγοράζω και πουλάω έργα τέχνης,\n"
	.string "ειδικά πίνακες.\p"
	.string "Έχω ακούσει ότι το MUSEUM εδώ έχει\n"
	.string "πολύ όμορφα έργα σε έκθεση…$"

LilycoveCity_Text_SeaRemainsForeverYoung:
	.string "Ακόμα κι όταν γερνάμε και ζαρώνουμε,\n"
	.string "η θάλασσα παραμένει για πάντα \l"
	.string "νέα με τη ζωηρή \l"
	.string "λάμψη της ζωής…\p"
	.string "Φωχοχο φωχοχοχοχο…$"

LilycoveCity_Text_SixtyYearsAgoHusbandProposed:
	.string "Πέρασαν εξήντα χρόνια από τότε που ο\n"
	.string "άντρας μου μού έκανε \l"
	.string "πρόταση γάμου εδώ.\l"
	.string "Η θάλασσα παραμένει \l"
	.string "όσο όμορφη πάντα.\p"
	.string "Μουφουφουφου μουφουφουφουφου…$"

LilycoveCity_Text_TeamAquaRenovatedCavern:
	.string "Χμ, ξέρεις αυτήν την παράξενη σπηλιά\n"
	.string "σε αυτόν τον όρμο;\p"
	.string "Ήταν ένας φυσικός σχηματισμός,\n"
	.string "αλλά μετά ήρθαν αυτοί από \l"
	.string "την TEAM AQUA και\l"
	.string "έκαναν ανακαινίσεις.\p"
	.string "Αποκαλούν τους εαυτούς \n"
	.string "τους TEAM AQUA \l"
	.string "που “αγαπάει τη φύση”!\p"
	.string "Αλλά αυτά που κάνουν κι αυτά \n"
	.string "που λένε δεν ταιριάζουν καθόλου!$"

LilycoveCity_Text_TeamAquaLotGoneForGood:
	.string "Αυτή η σπηλιά στον όρμο…\p"
	.string "Δεν το πρόσεξα αμέσως,\n"
	.string "αλλά είναι εντελώς άδεια τώρα.\p"
	.string "Αυτή η παρέα της TEAM AQUA, μάλλον\n"
	.string "έφυγε για τα καλά.$"

LilycoveCity_Text_CitySign:
	.string "LILYCOVE CITY\p"
	.string "“Εκεί που τελειώνει η γη και \n"
	.string "αρχίζει η θάλασσα.”$"

LilycoveCity_Text_ContestHallSign:
	.string "POKéMON CONTEST HALL\n"
	.string "“Το μέρος συνάντησης των TRAINERS!”$"

LilycoveCity_Text_MotelSign:
	.string "COVE LILY MOTEL\p"
	.string "“Θυμήσου μας ως το COVE LILY \n"
	.string "της LILYCOVE.”$"

LilycoveCity_Text_MuseumSign:
	.string "LILYCOVE MUSEUM\p"
	.string "“Συλλογή Masterpiece POKéMON \n"
	.string "σε έκθεση!”$"

LilycoveCity_Text_MuseumSignPlayersExhibit:
	.string "LILYCOVE MUSEUM\p"
	.string "“Συλλογή POKéMON του {PLAYER}\n"
	.string "σε έκθεση!”$"

LilycoveCity_Text_HarborSignUnderConstruction:
	.string "LILYCOVE CITY HARBOR\p"
	.string "“Το πλοίο S.S. TIDAL είναι υπό\n"
	.string "κατασκευή στο SLATEPORT CITY.\p"
	.string "“Η εξυπηρέτηση έχει \n"
	.string "προγραμματιστεί να αρχίσει \l"
	.string "σύντομα.”$"

LilycoveCity_Text_HarborSign:
	.string "LILYCOVE CITY HARBOR\p"
	.string "“Απολαύστε μια υπέροχη κρουαζιέρα \n"
	.string "στο πλοίο S.S. TIDAL.”$"

LilycoveCity_Text_TrainerFanClubSign:
	.string "POKéMON TRAINER FAN CLUB\p"
	.string "Τα ονόματα των TRAINERS είναι \n"
	.string "γραμμένα παντού στην ταμπέλα…$"

LilycoveCity_Text_DepartmentStoreSign:
	.string "LILYCOVE DEPARTMENT STORE\p"
	.string "“Ξεχειλίζει με υπέροχα εμπορεύματα\n"
	.string "και ενθουσιασμό!\p"
	.string "“Ένα υπέροχο μέρος για να \n"
	.string "βρεις αυτό που ψάχνεις!”$"

LilycoveCity_Text_MoveDeletersHouseSign:
	.string "ΣΠΙΤΙ TOY MOVE DELETER\p"
	.string "“Ανεπιθύμητες POKéMON \n"
	.string "κινήσεις διαγράφονται.”$"

LilycoveCity_Text_DoYouKnowAboutBerryBlender:
	.string "Ξέρεις τη μηχανή\n"
	.string "BERRY BLENDER;$"

LilycoveCity_Text_FasterSpinBetterPokeblocks:
	.string "Οι άνθρωποι πρέπει να συνεργαστούν \n"
	.string "για να γυρίσει πιο γρήγορα.\p"
	.string "Όσο πιο γρήγορα την κάνεις να\n"
	.string "γυρίσει, τόσο καλύτερα {POKEBLOCK}S \l"
	.string "μπορείς να πάρεις, έτσι άκουσα.$"

LilycoveCity_Text_ExplainBerryBlender:
	.string "Χρησιμοποιείται για να φτιάξεις\n"
	.string "ένα είδος καραμέλας που λέγεται {POKEBLOCK}.\p"
	.string "Αν δώσεις ένα καλό {POKEBLOCK} σε ένα \n"
	.string "POKéMON, η κατάστασή του \l"
	.string "θα βελτιωθεί πολύ.$"

LilycoveCity_Text_HeardTowerCalledSkyPillar:
	.string "Άκουσα ότι υπάρχει ένας πύργος κάπου \n"
	.string "έξω στις θαλάσσιες διαδρομές.\p"
	.string "Ονομάζεται SKY PILLAR, απ' ό,τι άκουσα.$"

LilycoveCity_Text_SawTallTowerOnRoute131:
	.string "Είδα αυτόν τον ψηλό πύργο κάπου \n"
	.string "κοντά στην ROUTE 131.\p"
	.string "Μπορεί άραγε να είναι…;$"

LilycoveCity_Text_JustArrivedAndSawRarePokemon:
	.string "Μόλις φτάσαμε εδώ για \n"
	.string "τον μήνα του μέλιτος.\p"
	.string "Τύχαινε να δούμε ένα POKéMON τύπου\n"
	.string "DRAGON να πετάει ψηλά \l"
	.string "στον ουρανό.\p"
	.string "Ζουν τέτοια κουλ POKéMON \n"
	.string "στην περιοχή HOENN;$"

LilycoveCity_Text_HoneymoonVowToSeeRarePokemon:
	.string "Στον μήνα του μέλιτός μας, \n"
	.string "ορκιστήκαμε να δούμε όσα \l"
	.string "πιο πολλά σπάνια \l"
	.string "POKéMON μπορούμε.\p"
	.string "Οπότε χαρήκαμε που είδαμε ένα \n"
	.string "σπάνιο POKéMON \l"
	.string "μόλις φτάσαμε.\p"
	.string "Εννοώ, είμαστε απόλυτα \n"
	.string "ευτυχισμένοι!$"

