DewfordTown_House1_MapScripts::
	.byte 0

DewfordTown_House1_EventScript_Man::
	msgbox DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Woman::
	msgbox DewfordTown_House1_Text_LifeGoesSlowlyOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox DewfordTown_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland:
	.string "Έχει πολλά πλεονεκτήματα το να ζεις σε\n"
	.string "ένα μικρό νησί όπως αυτό με τα\l"
	.string "POKéMON και την οικογένειά σου.$"

DewfordTown_House1_Text_LifeGoesSlowlyOnIsland:
	.string "Έφυγα από το μεγάλο λιμάνι της\n"
	.string "SLATEPORT όταν παντρεύτηκα\l"
	.string "τον άντρα μου εδώ.\p"
	.string "Η ζωή κυλάει αργά σε αυτό το μικρό\n"
	.string "νησί. Αλλά περιτριγυρισμένη από την\l"
	.string "όμορφη θάλασσα… κι αυτό είναι \l"
	.string "ευτυχία.$"

DewfordTown_House1_Text_Zigzagoon:
	.string "ZIGZAGOON: Γκουγκούχ!$"

