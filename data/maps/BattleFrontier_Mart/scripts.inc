.set LOCALID_OLD_WOMAN, 2

BattleFrontier_Mart_MapScripts::
	.byte 0

BattleFrontier_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart BattleFrontier_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
BattleFrontier_Mart_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_PROTEIN
	.2byte ITEM_CALCIUM
	.2byte ITEM_IRON
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_HP_UP
	.2byte ITEM_NONE
	release
	end

BattleFrontier_Mart_EventScript_OldMan::
	msgbox BattleFrontier_Mart_Text_ChaperonGrandson, MSGBOX_NPC
	end

BattleFrontier_Mart_EventScript_OldWoman::
	lock
	applymovement LOCALID_OLD_WOMAN, Common_Movement_FaceDown
	waitmovement 0
	msgbox BattleFrontier_Mart_Text_ProteinMakeNiceGift, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Mart_EventScript_Boy::
	msgbox BattleFrontier_Mart_Text_FacilitiesDontAllowItems, MSGBOX_NPC
	end

BattleFrontier_Mart_Text_ChaperonGrandson:
	.string "Ήρθαμε εδώ για να συνοδεύσουμε τον\n"
	.string "εγγονό μας.\p"
	.string "Αλλά μιας και ήμαστε εδώ, σκεφτήκαμε\n"
	.string "να πάρουμε και μερικά σουβενίρ.$"

BattleFrontier_Mart_Text_ProteinMakeNiceGift:
	.string "Αγάπη μου, πώς σου φαίνεται αυτό;\n"
	.string "Δεν θα ήταν ένα ωραίο δώρο;\p"
	.string "Λέει…PRO…TE…IN;\n"
	.string "Ακούγεται νόστιμο, δεν νομίζεις;$"

BattleFrontier_Mart_Text_FacilitiesDontAllowItems:
	.string "Πολλές εγκαταστάσεις στο BATTLE\n"
	.string "FRONTIER δεν επιτρέπουν τη χρήση items\l"
	.string "κατά τη διάρκεια της μάχης.\p"
	.string "Αυτός ο κανόνας κάνει τα πράγματα πιο\n"
	.string "δύσκολα απ' όσο ήδη είναι!$"

