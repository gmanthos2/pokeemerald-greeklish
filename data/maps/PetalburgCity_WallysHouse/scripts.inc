.set LOCALID_WALLYS_DAD, 1

PetalburgCity_WallysHouse_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_WallysHouse_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgCity_WallysHouse_OnWarp
	.byte 0

PetalburgCity_WallysHouse_OnWarp:
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther
	.2byte 0

PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	turnobject LOCALID_WALLYS_DAD, DIR_WEST
	end

PetalburgCity_WallysHouse_OnFrame:
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_GiveHMSurf
	.2byte 0

PetalburgCity_WallysHouse_EventScript_GiveHMSurf::
	lockall
	msgbox PetalburgCity_WallysHouse_Text_PleaseExcuseUs, MSGBOX_DEFAULT
	giveitem ITEM_HM_SURF
	setflag FLAG_RECEIVED_HM_SURF
	msgbox PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces, MSGBOX_DEFAULT
	setvar VAR_PETALBURG_CITY_STATE, 5
	releaseall
	end

PetalburgCity_WallysHouse_EventScript_WallysDad::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_ReceievedHMSurf
	goto_if_set FLAG_THANKED_FOR_PLAYING_WITH_WALLY, PetalburgCity_WallysHouse_EventScript_PlayedWithWally
	msgbox PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally, MSGBOX_DEFAULT
	setflag FLAG_THANKED_FOR_PLAYING_WITH_WALLY
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceievedHMSurf::
	msgbox PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad::
	msgbox PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_PlayedWithWally::
	msgbox PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_WallysMom::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_ReceivedHMSurf
	msgbox PetalburgCity_WallysHouse_Text_WallyWasReallyHappy, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceivedHMSurf::
	msgbox PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally:
	.string "Είσαι…\n"
	.string "Α, πρέπει να είσαι {PLAYER}{KUN}, \l"
	.string "σωστά;\p"
	.string "Σε ευχαριστώ που έπαιξες με τον \n"
	.string "WALLY πριν από λίγο.\p"
	.string "Είναι αδύναμος και φιλάσθενος από \n"
	.string "τότε που ήταν μωρό.\p"
	.string "Τον στείλαμε να μείνει στους \n"
	.string "συγγενείς μου στη VERDANTURF TOWN\l"
	.string "για λίγο.\p"
	.string "Ο αέρας είναι πολύ πιο καθαρός \n"
	.string "εκεί απ' ό,τι είναι εδώ.\p"
	.string "Πώς είπες; Πού είναι ο WALLY;\n"
	.string "Έχει ήδη φύγει, ο δικός μας WALLY.\p"
	.string "Αναρωτιέμαι πού να έχει\n"
	.string "φτάσει μέχρι τώρα;$"

PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing:
	.string "Αναρωτιέμαι τι να κάνει ο WALLY;$"

PetalburgCity_WallysHouse_Text_PleaseExcuseUs:
	.string "{PLAYER}{KUN}! Συγχώρεσέ μας που σε\n"
	.string "φέραμε εδώ με αυτόν τον τρόπο.\p"
	.string "Όμως, ο WALLY μας έχει γίνει πολύ \n"
	.string "πιο υγιής από τότε που πήγε \l"
	.string "στην VERDANTURF TOWN.\p"
	.string "Τα χρωστάμε όλα σε εσένα!\p"
	.string "Όταν ο WALLY έφυγε από την πόλη, τον \n"
	.string "βοήθησες να πιάσει ένα POKéMON.\p"
	.string "Νομίζω ότι αυτό έδωσε μεγάλη\n"
	.string "χαρά στον WALLY.\p"
	.string "Στην πραγματικότητα, όχι μόνο\n"
	.string "στον WALLY.\p"
	.string "Έδωσε χαρά και σε μένα,\n"
	.string "τον πατέρα του.\p"
	.string "Χαίρομαι που απέκτησε έναν τόσο\n"
	.string "καλό φίλο σαν εσένα.\p"
	.string "Δεν είναι δωροδοκία, αλλά θα\n"
	.string "ήθελα πολύ να το πάρεις αυτό.$"

PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces:
	.string "Αν το POKéMON σου χρησιμοποιεί SURF,\n"
	.string "θα μπορείς να πας σε όλα τα μέρη.$"

PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon:
	.string "Ο WALLY επιστρέφει σύντομα. \n"
	.string "Ανυπομονώ γι' αυτό.$"

PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity:
	.string "Α; Γνώρισες τον WALLY στην\n"
	.string "EVER GRANDE CITY;\p"
	.string "Αχ, {PLAYER}{KUN}, μην λες αστεία.\p"
	.string "Μπορεί να έχει γίνει πιο υγιής, \n"
	.string "αλλά δεν μπορεί να πάει κάπου \l"
	.string "τόσο μακριά μόνος του.$"

PetalburgCity_WallysHouse_Text_WallyWasReallyHappy:
	.string "Ο WALLY ήταν πολύ χαρούμενος όταν \n"
	.string "μας είπε ότι έπιασε ένα POKéMON.\p"
	.string "Πάει πολύς καιρός από τότε που τον \n"
	.string "είδα να χαμογελάει έτσι.$"

PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling:
	.string "Θέλω να το κρατήσεις αυτό μυστικό \n"
	.string "από τον σύζυγό μου…\p"
	.string "Αλλά ο WALLY έφυγε από την \n"
	.string "VERDANTURF TOWN χωρίς να το πει.\p"
	.string "Ξέρεις, ο WALLY είναι αδύναμος, \n"
	.string "αλλά έχει εκπληκτική θέληση.\p"
	.string "Είμαι σίγουρη ότι θα επιστρέψει \n"
	.string "σώος και αβλαβής μια μέρα!$"

