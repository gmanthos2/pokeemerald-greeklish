MauvilleCity_House1_MapScripts::
	.byte 0

MauvilleCity_House1_EventScript_RockSmashDude::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, MauvilleCity_House1_EventScript_ReceivedRockSmash
	msgbox MauvilleCity_House1_Text_ImRockSmashDudeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_HM_ROCK_SMASH
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	setflag FLAG_HIDE_ROUTE_111_ROCK_SMASH_TIP_GUY
	msgbox MauvilleCity_House1_Text_ExplainRockSmash, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_ReceivedRockSmash::
	msgbox MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_Text_ImRockSmashDudeTakeThis:
	.string "Γιούχου!\p"
	.string "Ακούω ότι με φωνάζουν ROCK SMASH\n"
	.string "GUY, και το θεωρώ υποτιμητικό.\p"
	.string "Πιστεύω ότι αξίζω περισσότερο, \n"
	.string "όπως ας πούμε ROCK SMASH DUDE.\p"
	.string "Γιούχου!\p"
	.string "Τέλος πάντων τα POKéMON \n"
	.string "σου φαίνονται αρκετά δυνατά.\p"
	.string "Αυτό μου αρέσει!\n"
	.string "Ορίστε, πάρε αυτό το HIDDEN MACHINE!$"

MauvilleCity_House1_Text_ExplainRockSmash:
	.string "Αυτό το HM περιέχει το ROCK SMASH.\p"
	.string "Εάν συναντήσεις μεγάλους \n"
	.string "ογκόλιθους που σου κλείνουν \l"
	.string "το δρόμο…\p"
	.string "Χρησιμοποίησε αυτήν την HM κίνηση\n"
	.string "και σπάσε τους για να περάσεις!\p"
	.string "Μάλιστα! Σπάστε τους βράχους, λέω!\n"
	.string "Γιούχου!$"

MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock:
	.string "Α, ναι, αν σπάσεις έναν βράχο, ένα \n"
	.string "POKéMON μπορεί να πεταχτεί έξω \l"
	.string "από την κρυψώνα του.\p"
	.string "Γιούχου!$"

