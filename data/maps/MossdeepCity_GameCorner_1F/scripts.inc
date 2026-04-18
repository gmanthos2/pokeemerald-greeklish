MossdeepCity_GameCorner_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MossdeepCity_GameCorner_1F_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MossdeepCity_GameCorner_1F_OnWarp
	map_script MAP_SCRIPT_ON_LOAD, CableClub_OnLoad
	.byte 0

MossdeepCity_GameCorner_1F_OnWarp:
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_CheckTurnAttendant
	.2byte 0

MossdeepCity_GameCorner_1F_OnFrame:
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_ExitMinigameRoom
	.2byte 0

@ Script is redundant, the label in the goto also does lock and faceplayer
MossdeepCity_GameCorner_1F_EventScript_InfoMan::
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_InfoMan2
	release
	end

@ Script is redundant, the label in the goto also does lock and faceplayer
MossdeepCity_GameCorner_1F_EventScript_OldMan::
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_OldMan2
	release
	end


@ Everything below is leftover from RS
@ The house that was here in RS was moved to Sootopolis and replaced by the Game Corner
@ The text below is unused and duplicated in its replacement in Sootopolis City
@ And the BG Door event was moved inaccessibly into a wall

RS_MysteryEventsHouse_EventScript_Door::
	msgbox RS_MysteryEventsHouse_Text_DoorIsLocked, MSGBOX_SIGN
	end

RS_MysteryEventsHouse_Text_OldManGreeting:
	.string "Όταν ήμουν νέος, ταξίδευα \n"
	.string "στον κόσμο ως POKéMON TRAINER.\p"
	.string "Τώρα που έγινα ένας γέρος, η \n"
	.string "μόνη μου διασκέδαση είναι να βλέπω \l"
	.string "νέους TRAINERS να παλεύουν.$"

RS_MysteryEventsHouse_Text_DoorIsLocked:
	.string "Η πόρτα φαίνεται να είναι \n"
	.string "κλειδωμένη.$"

RS_MysteryEventsHouse_Text_ChallengeVisitingTrainer:
	.string "Ένας TRAINER με το όνομα \n"
	.string "{STR_VAR_1} επισκέπτεται \l"
	.string "το σπίτι μου.\p"
	.string "Θα ήθελες να προκαλέσεις \n"
	.string "το {STR_VAR_1};$"

RS_MysteryEventsHouse_Text_YouWonBattle:
	.string "Δεν θα παλέψεις; Απογοητεύομαι \n"
	.string "που δεν μπορώ να σε δω να \l"
	.string "παλεύεις…$"

RS_MysteryEventsHouse_Text_KeepItToA3On3:
	.string "Α, καλά, καλά!\p"
	.string "Αλλά το σπίτι μου δεν είναι και \n"
	.string "πολύ γερό.\p"
	.string "Θα μπορούσα να σου ζητήσω να το \n"
	.string "περιορίσετε σε μια μάχη 3-εναντίον-3;$"

RS_MysteryEventsHouse_Text_SaveYourProgress:
	.string "Πριν παλέψετε οι δυο σας, θα \n"
	.string "πρέπει να αποθηκεύσετε την \l"
	.string "πρόοδό σας.$"

RS_MysteryEventsHouse_Text_HopeToSeeAGoodMatch:
	.string "Ελπίζω να δω έναν καλό αγώνα!$"

RS_MysteryEventsHouse_Text_BattleTie:
	.string "Λοιπόν, κατέληξε σε ισοπαλία.\p"
	.string "Ήταν ένας λαμπρός αγώνας στον οποίο \n"
	.string "καμία πλευρά δεν υποχώρησε \l"
	.string "ούτε βήμα!$"

RS_MysteryEventsHouse_Text_BattleWon:
	.string "Αυτό ήταν εξαιρετικό!\p"
	.string "Γιατί, ήταν σαν να έβλεπα τον εαυτό \n"
	.string "μου στα νιάτα μου ξανά!$"

RS_MysteryEventsHouse_Text_BattleLost:
	.string "Αχ, κρίμα για σένα!\p"
	.string "Αλλά ήταν ένας καλός αγώνας.\n"
	.string "Ελπίζω να κερδίσεις την επόμενη φορά.$"
