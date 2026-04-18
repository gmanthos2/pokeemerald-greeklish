PacifidlogTown_House5_MapScripts::
	.byte 0

PacifidlogTown_House5_EventScript_MirageIslandWatcher::
	lock
	faceplayer
	specialvar VAR_RESULT, IsMirageIslandPresent
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_House5_EventScript_MirageIslandPresent
	msgbox PacifidlogTown_House5_Text_CantSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_MirageIslandPresent::
	msgbox PacifidlogTown_House5_Text_CanSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_Gentleman::
	msgbox PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather, MSGBOX_NPC
	end

PacifidlogTown_House5_Text_CantSeeMirageIslandToday:
	.string "Δεν βλέπω το MIRAGE ISLAND σήμερα…$"

PacifidlogTown_House5_Text_CanSeeMirageIslandToday:
	.string "Ω! Μα την πίστη μου!\n"
	.string "Βλέπω το MIRAGE ISLAND σήμερα!$"

PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather:
	.string "MIRAGE ISLAND…\p"
	.string "Πρέπει να γίνεται ορατό και αόρατο\n"
	.string "ανάλογα με τις καιρικές συνθήκες\l"
	.string "που κάνουν τις οφθαλμαπάτες να \l"
	.string "εμφανίζονται.\p"
	.string "Ή μήπως πραγματικά εμφανίζεται και \n"
	.string "εξαφανίζεται;$"

