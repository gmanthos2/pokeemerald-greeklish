.set LOCALID_NURSE, 1

MauvilleCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

MauvilleCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_MAUVILLE_CITY
	call Common_EventScript_UpdateBrineyLocation
	goto MauvilleCity_PokemonCenter_1F_EventScript_SetMauvilleOldManGfx
	end

MauvilleCity_PokemonCenter_1F_EventScript_SetMauvilleOldManGfx::
	special SetMauvilleOldManObjEventGfx
	end

MauvilleCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman1::
	msgbox MauvilleCity_PokemonCenter_1F_Text_ManOverThereSaysWeirdThings, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman2::
	msgbox MauvilleCity_PokemonCenter_1F_Text_MyDataUpdatedFromRecordCorner, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox MauvilleCity_PokemonCenter_1F_Text_RecordCornerSoundsFun, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_Text_ManOverThereSaysWeirdThings:
	.string "Αυτός ο άντρας εκεί πέρα, λέει \n"
	.string "περίεργα πράγματα!\p"
	.string "Είναι αστείος με έναν περίεργο τρόπο.\n"
	.string "Πολύ αμφιβάλλω αν θα τον ξεχάσω!$"

MauvilleCity_PokemonCenter_1F_Text_MyDataUpdatedFromRecordCorner:
	.string "Όταν μπήκα στο RECORD CORNER, \n"
	.string "τα δεδομένα μου για το τι είναι\l"
	.string "στη μόδα στο DEWFORD ενημερώθηκαν.\p"
	.string "Τώρα αυτά τα δεδομένα είναι \n"
	.string "τα ίδια με τους φίλους μου!$"

MauvilleCity_PokemonCenter_1F_Text_RecordCornerSoundsFun:
	.string "Ένα RECORD CORNER άνοιξε πάνω\n"
	.string "στο POKéMON CENTER.\p"
	.string "Δεν ξέρω τι είναι, αλλά \n"
	.string "ακούγεται διασκεδαστικό. \l"
	.string "Θα πάω να το δω!$"

