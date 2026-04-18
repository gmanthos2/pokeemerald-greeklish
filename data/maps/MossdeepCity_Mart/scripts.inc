MossdeepCity_Mart_MapScripts::
	.byte 0

MossdeepCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MossdeepCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MossdeepCity_Mart_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_NONE
	release
	end

MossdeepCity_Mart_EventScript_Woman::
	msgbox MossdeepCity_Mart_Text_ReviveIsFantastic, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Boy::
	msgbox MossdeepCity_Mart_Text_MaxRepelLastsLongest, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Sailor::
	msgbox MossdeepCity_Mart_Text_NetAndDiveBallsRare, MSGBOX_NPC
	end

MossdeepCity_Mart_Text_ReviveIsFantastic:
	.string "Το REVIVE είναι φανταστικό!\p"
	.string "Δώσε το σε ένα POKéMON που έχει \n"
	.string "λιποθυμήσει και το POKéMON \l"
	.string "θα συνέλθει.\p"
	.string "Πρόσεχε όμως, το REVIVE δεν \n"
	.string "επαναφέρει τα PP των κινήσεων.$"

MossdeepCity_Mart_Text_MaxRepelLastsLongest:
	.string "Το MAX REPEL κρατά μακριά όλα τα \n"
	.string "αδύναμα POKéMON.\p"
	.string "Από όλα τα σπρέι REPEL, αυτό \n"
	.string "διαρκεί περισσότερο.$"

MossdeepCity_Mart_Text_NetAndDiveBallsRare:
	.string "Oι NET και DIVE BALLS είναι σπάνιες \n"
	.string "POKé BALLS που φτιάχνονται μόνο \l"
	.string "στο MOSSDEEP.\p"
	.string "Μια NET BALL είναι αποτελεσματική \n"
	.string "ενάντια σε POKéMON τύπου BUG \l"
	.string "και WATER.\p"
	.string "Mια DIVE BALL λειτουργεί καλύτερα \n"
	.string "σε POKéMON στον βυθό της θάλασσας.$"

