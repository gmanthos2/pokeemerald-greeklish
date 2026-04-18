PacifidlogTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, PacifidlogTown_OnResume
	.byte 0

PacifidlogTown_OnTransition:
	setflag FLAG_VISITED_PACIFIDLOG_TOWN
	end

PacifidlogTown_OnResume:
	setstepcallback STEP_CB_PACIFIDLOG_BRIDGE
	end

PacifidlogTown_EventScript_NinjaBoy::
	msgbox PacifidlogTown_Text_NeatHousesOnWater, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Girl::
	msgbox PacifidlogTown_Text_FastRunningCurrent, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Fisherman::
	msgbox PacifidlogTown_Text_SkyPillarTooScary, MSGBOX_NPC
	end

PacifidlogTown_EventScript_TownSign::
	msgbox PacifidlogTown_Text_TownSign, MSGBOX_SIGN
	end

PacifidlogTown_Text_FastRunningCurrent:
	.string "Η θάλασσα ανάμεσα στην PACIFIDLOG \n"
	.string "και την SLATEPORT έχει ισχυρά \l"
	.string "ρεύματα.\p"
	.string "Αν αποφασίσεις να κάνεις SURF, \n"
	.string "μπορεί να παρασυρθείς κάπου \l"
	.string "αλλού.$"

PacifidlogTown_Text_NeatHousesOnWater:
	.string "Δες, δεν είναι υπέροχο;\n"
	.string "Αυτά τα σπίτια είναι πάνω στο \l"
	.string "νερό!\p"
	.string "Γεννήθηκα εδώ!$"

PacifidlogTown_Text_SkyPillarTooScary:
	.string "Ο SKY PILLAR;\p"
	.string "…Ω, θα εννοείς εκείνον τον \n"
	.string "πελώριο πύργο λίγο πιο πέρα.\p"
	.string "Αν με ρωτάς, εγώ δεν θα τον \n"
	.string "σκαρφάλωνα. Είναι πολύ \l"
	.string "τρομακτικό τόσο ψηλά.\p"
	.string "Η ζωή στο επίπεδο της θάλασσας \n"
	.string "στην PACIFIDLOG μου ταιριάζει \l"
	.string "μια χαρά.$"

PacifidlogTown_Text_TownSign:
	.string "PACIFIDLOG TOWN\p"
	.string "“Εκεί που ο πρωινός ήλιος \n"
	.string "χαμογελά πάνω στα νερά.”$"

