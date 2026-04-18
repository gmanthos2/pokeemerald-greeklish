MossdeepCity_House1_MapScripts::
	.byte 0

MossdeepCity_House1_EventScript_BlackBelt::
	lock
	faceplayer
	bufferleadmonspeciesname STR_VAR_1
	msgbox MossdeepCity_House1_Text_HmmYourPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetPokeblockNameByMonNature
	goto_if_eq VAR_RESULT, 0, MossdeepCity_House1_EventScript_NeutralNature
	msgbox MossdeepCity_House1_Text_ItLikesXPokeblocks, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House1_EventScript_NeutralNature::
	msgbox MossdeepCity_House1_Text_DoesntLikeOrDislikePokeblocks, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House1_EventScript_Woman::
	msgbox MossdeepCity_House1_Text_HusbandCanTellPokeblockMonLikes, MSGBOX_NPC
	end

MossdeepCity_House1_Text_HmmYourPokemon:
	.string "Χμμ!\n"
	.string "Το {STR_VAR_1} σου…$"

MossdeepCity_House1_Text_ItLikesXPokeblocks:
	.string "Του αρέσουν τα {STR_VAR_1}S,\n"
	.string "έτσι δεν είναι;\p"
	.string "Όχι, είμαι σίγουρος! Σίγουρα του \n"
	.string "αρέσουν τα {STR_VAR_1}S!$"

MossdeepCity_House1_Text_DoesntLikeOrDislikePokeblocks:
	.string "Δεν φαίνεται να του αρέσει ή να \n"
	.string "μην του αρέσει κάποιο {POKEBLOCK}S.$"

MossdeepCity_House1_Text_HusbandCanTellPokeblockMonLikes:
	.string "Ο σύζυγός μου μπορεί να καταλάβει \n"
	.string "τι είδους {POKEBLOCK}S αρέσουν σε ένα \l"
	.string "POKéMON με μια ματιά.$"

