OldaleTown_House2_MapScripts::
	.byte 0

OldaleTown_House2_EventScript_Woman::
	msgbox OldaleTown_House2_Text_PokemonLevelUp, MSGBOX_NPC
	end

OldaleTown_House2_EventScript_Man::
	msgbox OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon, MSGBOX_NPC
	end

OldaleTown_House2_Text_PokemonLevelUp:
	.string "Όταν τα POKéMON παλεύουν, τελικά \n"
	.string "ανεβαίνουν επίπεδο και γίνονται \l"
	.string "πιο δυνατά.$"

OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon:
	.string "Αν τα POKéMON που έχεις μαζί σου \n"
	.string "γίνουν πιο δυνατά, θα μπορείς να \l"
	.string "πας πιο μακριά από εδώ.$"

