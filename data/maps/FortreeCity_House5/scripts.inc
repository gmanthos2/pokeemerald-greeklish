FortreeCity_House5_MapScripts::
	.byte 0

FortreeCity_House5_EventScript_PokefanF::
	msgbox FortreeCity_House5_Text_TreeHousesAreGreat, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Man::
	msgbox FortreeCity_House5_Text_AdaptedToNature, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox FortreeCity_House5_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House5_Text_TreeHousesAreGreat:
	.string "Τα δεντρόσπιτα του FORTREE είναι \n"
	.string "φανταστικά!\p"
	.string "Νομίζω πως είναι η καλύτερη πόλη \n"
	.string "για να ζεις μαζί με POKéMON.$"

FortreeCity_House5_Text_AdaptedToNature:
	.string "Τα POKéMON και οι άνθρωποι έχουν \n"
	.string "προσαρμοστεί στη φύση για επιβίωση.\p"
	.string "Δεν υπάρχει λόγος να κάνουμε τη φύση \n"
	.string "να ταιριάζει στον τρόπο που \l"
	.string "θέλουμε να ζούμε.$"

FortreeCity_House5_Text_Zigzagoon:
	.string "ZIGZAGOON: Bufuu!$"

