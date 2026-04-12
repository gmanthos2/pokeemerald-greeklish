AbandonedShip_Corridors_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, AbandonedShip_Corridors_B1F_OnResume
	map_script MAP_SCRIPT_ON_LOAD, AbandonedShip_Corridors_B1F_OnLoad
	.byte 0

AbandonedShip_Corridors_B1F_OnResume:
	setdivewarp MAP_ABANDONED_SHIP_UNDERWATER1, 5, 4
	end

AbandonedShip_Corridors_B1F_OnLoad:
	call_if_unset FLAG_USED_STORAGE_KEY, AbandonedShip_Corridors_B1F_EventScript_LockStorageRoom
	call_if_set FLAG_USED_STORAGE_KEY, AbandonedShip_Corridors_B1F_EventScript_UnlockStorageRoom
	end

AbandonedShip_Corridors_B1F_EventScript_LockStorageRoom::
	setmetatile 11, 4, METATILE_InsideShip_IntactDoor_Bottom_Locked, TRUE
	return

AbandonedShip_Corridors_B1F_EventScript_UnlockStorageRoom::
	setmetatile 11, 4, METATILE_InsideShip_IntactDoor_Bottom_Unlocked, TRUE
	return

AbandonedShip_Corridors_B1F_EventScript_TuberM::
	msgbox AbandonedShip_Corridors_B1F_Text_YayItsAShip, MSGBOX_NPC
	end

AbandonedShip_Corridors_B1F_EventScript_StorageRoomDoor::
	lockall
	goto_if_set FLAG_USED_STORAGE_KEY, AbandonedShip_Corridors_B1F_EventScript_DoorIsUnlocked
	checkitem ITEM_STORAGE_KEY
	goto_if_eq VAR_RESULT, FALSE, AbandonedShip_Corridors_B1F_EventScript_DoorIsLocked
	msgbox AbandonedShip_Corridors_B1F_Text_InsertedStorageKey, MSGBOX_DEFAULT
	playse SE_PIN
	removeitem ITEM_STORAGE_KEY
	setflag FLAG_USED_STORAGE_KEY
	call AbandonedShip_Corridors_B1F_EventScript_UnlockStorageRoom
	special DrawWholeMapView
	releaseall
	end

AbandonedShip_Corridors_B1F_EventScript_DoorIsLocked::
	msgbox AbandonedShip_Corridors_B1F_Text_DoorIsLocked, MSGBOX_DEFAULT
	releaseall
	end

AbandonedShip_Corridors_B1F_EventScript_DoorIsUnlocked::
	msgbox AbandonedShip_Text_TheDoorIsOpen, MSGBOX_DEFAULT
	releaseall
	end

AbandonedShip_Corridors_B1F_EventScript_Duncan::
	trainerbattle_single TRAINER_DUNCAN, AbandonedShip_Corridors_B1F_Text_DuncanIntro, AbandonedShip_Corridors_B1F_Text_DuncanDefeat
	msgbox AbandonedShip_Corridors_B1F_Text_DuncanPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Corridors_B1F_Text_DuncanIntro:
	.string "Όταν βγαίνουμε στη θάλασσα, οι SAILORS\n"
	.string "πάντα φέρνουμε τα POKéMON μας.\l"
	.string "Τι θα λέγατε για μια γρήγορη μάχη;$"

AbandonedShip_Corridors_B1F_Text_DuncanDefeat:
	.string "Ωχ, βυθίστηκα!$"

AbandonedShip_Corridors_B1F_Text_DuncanPostBattle:
	.string "Ο πάτος του πλοίου έχει βυθιστεί στα\n"
	.string "βάθη.\p"
	.string "Αν ένα POKéMON ήξερε να καταδυθεί,\n"
	.string "θα μπορούσαμε να προχωρήσουμε…$"

AbandonedShip_Corridors_B1F_Text_YayItsAShip:
	.string "Ζήτω!\n"
	.string "Είναι ένα πλοίο!$"

AbandonedShip_Corridors_B1F_Text_DoorIsLocked:
	.string "Η πόρτα είναι κλειδωμένη.\p"
	.string "Στην πόρτα γράφει ΑΠΟΘΗΚΗ\n"
	.string "αλλά δεν ανοίγει...$"

AbandonedShip_Corridors_B1F_Text_InsertedStorageKey:
	.string "Εισήγαγες και γύρισες το\n"
	.string "ΚΛΕΙΔΙ ΑΠΟΘΗΚΗΣ.\p"
	.string "Το εισαχθέν κλειδί κόλλησε γερά,\n"
	.string "αλλά η πόρτα άνοιξε.$"

AbandonedShip_Text_TheDoorIsOpen:
	.string "Η πόρτα είναι ανοιχτή.$"

