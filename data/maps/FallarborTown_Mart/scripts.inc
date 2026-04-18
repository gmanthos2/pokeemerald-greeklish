FallarborTown_Mart_MapScripts::
	.byte 0

FallarborTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FallarborTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FallarborTown_Mart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_X_SPECIAL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_NONE
	release
	end

FallarborTown_Mart_EventScript_Woman::
	msgbox FallarborTown_Mart_Text_DecidingSkittyEvolve, MSGBOX_NPC
	end

FallarborTown_Mart_EventScript_PokefanM::
	msgbox FallarborTown_Mart_Text_SellNuggetIFound, MSGBOX_NPC
	end

FallarborTown_Mart_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox FallarborTown_Mart_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_Mart_Text_DecidingSkittyEvolve:
	.string "Δυσκολεύομαι να αποφασίσω αν πρέπει\n"
	.string "να κάνω το SKITTY μου να εξελιχθεί.\p"
	.string "Το μόνο που χρειάζεται είναι αυτή η\n"
	.string "MOON STONE, αλλά είναι δύσκολο…\p"
	.string "Αν το αφήσω να εξελιχθεί, θα γίνει\n"
	.string "πολύ πιο δυνατό.\p"
	.string "Αλλά θα φαίνεται και πολύ\n"
	.string "διαφορετικό.$"

FallarborTown_Mart_Text_Skitty:
	.string "SKITTY: Μιάου;$"

FallarborTown_Mart_Text_SellNuggetIFound:
	.string "Αυτό το NUGGET που βρήκα εδώ…\n"
	.string "Υποθέτω πώς θα πρέπει να το\l"
	.string "πουλήσω, μιας και δεν έχει \l"
	.string "άλλη χρήση.$"

