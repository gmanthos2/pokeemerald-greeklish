PacifidlogTown_House4_MapScripts::
	.byte 0

PacifidlogTown_House4_EventScript_LittleGirl::
	msgbox PacifidlogTown_House4_Text_SkyPokemon, MSGBOX_NPC
	end

PacifidlogTown_House4_EventScript_Woman::
	msgbox PacifidlogTown_House4_Text_PeopleSawHighFlyingPokemon, MSGBOX_NPC
	end

PacifidlogTown_House4_EventScript_Boy::
	lock
	faceplayer
	msgbox PacifidlogTown_House4_Text_WhereDidYouComeFrom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PacifidlogTown_House4_EventScript_Yes
	goto_if_eq VAR_RESULT, NO, PacifidlogTown_House4_EventScript_No
	end

PacifidlogTown_House4_EventScript_Yes::
	msgbox PacifidlogTown_House4_Text_YesTown, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House4_EventScript_No::
	msgbox PacifidlogTown_House4_Text_YouHaveToComeFromSomewhere, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House4_Text_PeopleSawHighFlyingPokemon:
	.string "Κάποιοι έλεγαν ότι είδαν ένα POKéMON\n"
	.string "να πετά ψηλά πάνω από τη HOENN.\p"
	.string "Πετάει συνέχεια;\n"
	.string "Δεν χρειάζεται να ξεκουραστεί κάπου;$"

PacifidlogTown_House4_Text_SkyPokemon:
	.string "Ένα POKéMON του ουρανού!\n"
	.string "Ένα POKéMON του ουρανού!$"

PacifidlogTown_House4_Text_WhereDidYouComeFrom:
	.string "Από πού ήρθες;$"

PacifidlogTown_House4_Text_YesTown:
	.string "Ναι;\n"
	.string "YES TOWN;\p"
	.string "Δεν έχω ακούσει ποτέ για ένα\n"
	.string "τέτοιο μέρος.$"

PacifidlogTown_House4_Text_YouHaveToComeFromSomewhere:
	.string "Όχι; Αυτό δεν έχει νόημα.\n"
	.string "Πρέπει να ήρθες από κάπου.\p"
	.string "Ω! Περίμενε! Μην μου πεις ότι\n"
	.string "γεννήθηκες στον βυθό της θάλασσας;$"

