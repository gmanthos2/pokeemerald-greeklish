FallarborTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_OnTransition
	.byte 0

FallarborTown_OnTransition:
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	clearflag FLAG_CONTEST_SKETCH_CREATED
	end

FallarborTown_EventScript_ExpertM::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_EventScript_ExpertMNormal
	msgbox FallarborTown_Text_ShadyCharactersCozmosHome, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_ExpertMNormal::
	msgbox FallarborTown_Text_RegionKnownForMeteors, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_Girl::
	msgbox FallarborTown_Text_MyPreciousAzurill, MSGBOX_NPC
	end

FallarborTown_EventScript_Gentleman::
	msgbox FallarborTown_Text_HaveYouChallengedFlannery, MSGBOX_NPC
	end

FallarborTown_EventScript_Azurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox FallarborTown_Text_Azurill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_EventScript_BattleTentSign::
	msgbox FallarborTown_Text_BattleTentSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_TownSign::
	msgbox FallarborTown_Text_TownSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_MoveTutorSign::
	msgbox FallarborTown_Text_MoveTutorSign, MSGBOX_SIGN
	end

FallarborTown_Text_ShadyCharactersCozmosHome:
	.string "Κάτι συμβαίνε εδώ, \n"
	.string "και δεν μου αρέσει καθόλου!\p"
	.string "Είδα κάτι ύποπτους τύπους να\n"
	.string "μπαινοβγαίνουν στο σπίτι του\l"
	.string "PROF. COZMO…$"

FallarborTown_Text_RegionKnownForMeteors:
	.string "Αυτή η περιοχή είναι γνωστή για \n"
	.string "τους μετεωρίτες από τα παλιά χρόνια.\p"
	.string "Λένε ότι το METEOR FALLS σκάφτηκε\n"
	.string "από έναν μετεωρίτη που έπεσε \l"
	.string "πριν από πολύ καιρό.$"

FallarborTown_Text_MyPreciousAzurill:
	.string "Δες! Κοίταξε εδώ!\n"
	.string "Αυτό είναι το πολύτιμο AZURILL μου!\p"
	.string "Είναι λείο και απαλό και ζουλιχτερό!$"

FallarborTown_Text_Azurill:
	.string "AZURILL: Rooreelooo.$"

FallarborTown_Text_HaveYouChallengedFlannery:
	.string "Έχεις προκαλέσει την FLANNERY,\n"
	.string "την LEADER του LAVARIDGE GYM;\p"
	.string "Ο παππούς του κοριτσιού ήταν διάσημος.\n"
	.string "Κάποτε ήταν ένας από τους ELITE FOUR\l"
	.string "στο POKéMON LEAGUE.\p"
	.string "Δεν θα με εξέπληττε να δω\n"
	.string "και την FLANNERY να γίνεται\l"
	.string "μια σπουδαία TRAINER και η ίδια.$"

FallarborTown_Text_BattleTentSign:
	.string "BATTLE TENT FALLARBOR SITE\n"
	.string "“Είθε να μαζευτούν οι καλύτεροι!”$"

FallarborTown_Text_TownSign:
	.string "FALLARBOR TOWN\n"
	.string "“Αγροτική κοινότητα με μικρούς κήπους.”$"

FallarborTown_Text_MoveTutorSign:
	.string "MOVE TUTOR'S HOUSE\n"
	.string "“Μαθαίνουμε νέες κινήσεις στα POKéMON.”$"

