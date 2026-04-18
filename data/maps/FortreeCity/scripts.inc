FortreeCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, FortreeCity_OnResume
	.byte 0

FortreeCity_OnTransition:
	setflag FLAG_VISITED_FORTREE_CITY
	end

FortreeCity_OnResume:
	setstepcallback STEP_CB_FORTREE_BRIDGE
	end

FortreeCity_EventScript_Man::
	msgbox FortreeCity_Text_SawGiganticPokemonInSky, MSGBOX_NPC
	end

FortreeCity_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_KECLEON_FLED_FORTREE, FortreeCity_EventScript_WomanGymAccessible
	msgbox FortreeCity_Text_SomethingBlockingGym, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_WomanGymAccessible::
	msgbox FortreeCity_Text_ThisTimeIllBeatWinona, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_Girl::
	msgbox FortreeCity_Text_TreesGrowByDrinkingRainwater, MSGBOX_NPC
	end

FortreeCity_EventScript_OldMan::
	msgbox FortreeCity_Text_EveryoneHealthyAndLively, MSGBOX_NPC
	end

FortreeCity_EventScript_Boy::
	msgbox FortreeCity_Text_BugPokemonComeThroughWindow, MSGBOX_NPC
	end

FortreeCity_EventScript_GameboyKid::
	msgbox FortreeCity_Text_PokemonThatEvolveWhenTraded, MSGBOX_NPC
	end

FortreeCity_EventScript_CitySign::
	msgbox FortreeCity_Text_CitySign, MSGBOX_SIGN
	end

FortreeCity_EventScript_GymSign::
	msgbox FortreeCity_Text_GymSign, MSGBOX_SIGN
	end

FortreeCity_EventScript_Kecleon::
	lock
	faceplayer
	checkitem ITEM_DEVON_SCOPE
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_EventScript_AskUseDevonScope
	msgbox FortreeCity_Text_SomethingUnseeable, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_AskUseDevonScope::
	msgbox FortreeCity_Text_UnseeableUseDevonScope, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FortreeCity_EventScript_UseDevonScope
	release
	end

FortreeCity_EventScript_UseDevonScope::
	msgbox FortreeCity_Text_UsedDevonScopePokemonFled, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Movement_KecleonAppears
	waitmovement 0
	waitse
	playmoncry SPECIES_KECLEON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	applymovement VAR_LAST_TALKED, FortreeCity_Movement_KecleonFlee
	waitmovement 0
	removeobject VAR_LAST_TALKED
	setflag FLAG_KECLEON_FLED_FORTREE
	release
	end

FortreeCity_Movement_KecleonFlee:
	walk_right
	step_end

FortreeCity_Text_SawGiganticPokemonInSky:
	.string "Δεν με πιστεύει κανείς, αλλά είδα αυτό\n"
	.string "το γιγάντιο POKéMON στον ουρανό.\p"
	.string "Φαινόταν να στριφογυρίζει καθώς\n"
	.string "πετούσε προς την ROUTE 131.\p"
	.string "Παρεμπιπτόντως… Σνιφ…\n"
	.string "Εμ… ε… μυρίζεις καμένο.\p"
	.string "Ήσουν σε κανένα ηφαίστειο ή \l"
	.string "κάτι τέτοιο;$"

FortreeCity_Text_SomethingBlockingGym:
	.string "Θέλω να πάω στο POKéMON GYM,\n"
	.string "αλλά κάτι μπλοκάρει τον δρόμο.\p"
	.string "Και μετά από όλον αυτόν τον κόπο\n"
	.string "που έκανα στην ROUTE 120…$"

FortreeCity_Text_ThisTimeIllBeatWinona:
	.string "Έχω μαζί μου το καμάρι μου, \n"
	.string "το POKéMON μου. \l"
	.string "Αυτή τη φορά, θα νικήσω την WINONA.$"

FortreeCity_Text_TreesGrowByDrinkingRainwater:
	.string "Το έδαφος απορροφά το νερό της βροχής, \n"
	.string "και τα δέντρα μεγαλώνουν πίνοντας\l"
	.string "αυτό το νερό…\p"
	.string "Η FORTREE CITY μας υπάρχει επειδή\n"
	.string "υπάρχει και νερό και χώμα.$"

FortreeCity_Text_EveryoneHealthyAndLively:
	.string "Η CITY αποτελείται από σπίτια \n"
	.string "χτισμένα πάνω σε δέντρα.\p"
	.string "Ίσως λόγω αυτού του τρόπου ζωής,\n"
	.string "όλοι είναι υγιείς και ζωηροί.\p"
	.string "Γιατί, ακόμα κι εγώ--νιώθω σαν να \n"
	.string "έχω γίνει τριάντα χρόνια νεότερος.$"

FortreeCity_Text_BugPokemonComeThroughWindow:
	.string "Η ζωή πάνω στα δέντρα είναι ωραία.\p"
	.string "Αλλά μερικές φορές μπαίνουν \n"
	.string "BUG POKéMON μέσα από τα παράθυρα.\l"
	.string "Μπορεί να σε τρομάξουν πραγματικά.$"

FortreeCity_Text_PokemonThatEvolveWhenTraded:
	.string "Υπάρχουν POKéMON που εξελίσσονται όταν\n"
	.string "τα ανταλλάσσεις! Έτσι άκουσα.$"

FortreeCity_Text_SomethingUnseeable:
	.string "Κάτι αόρατο κλείνει τον δρόμο.$"

FortreeCity_Text_UnseeableUseDevonScope:
	.string "Κάτι αόρατο κλείνει τον δρόμο.\p"
	.string "Θέλεις να χρησιμοποιήσεις το \n"
	.string "DEVON SCOPE;$"

FortreeCity_Text_UsedDevonScopePokemonFled:
	.string "Χρησιμοποίησες το DEVON SCOPE.\p"
	.string "Ένα αόρατο POKéMON έγινε \n"
	.string "εντελώς ορατό!\p"
	.string "Το τρομαγμένο POKéMON το έσκασε!$"

FortreeCity_Text_CitySign:
	.string "FORTREE CITY\n"
	.string "“Η πόλη στα δέντρα που \l"
	.string "παίζει με τη φύση.”$"

FortreeCity_Text_GymSign:
	.string "FORTREE CITY POKéMON GYM\n"
	.string "LEADER: WINONA\p"
	.string "“Ο χρήστης πουλιών που πετάει \n"
	.string "στον κόσμο.”$"

