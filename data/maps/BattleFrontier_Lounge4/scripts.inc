BattleFrontier_Lounge4_MapScripts::
	.byte 0

BattleFrontier_Lounge4_EventScript_Woman::
	msgbox BattleFrontier_Lounge4_Text_WonderIfInterviewsAiring, MSGBOX_NPC
	end

BattleFrontier_Lounge4_EventScript_Cook::
	msgbox BattleFrontier_Lounge4_Text_IfIOpenedRestaurantHere, MSGBOX_NPC
	end

BattleFrontier_Lounge4_EventScript_Man::
	msgbox BattleFrontier_Lounge4_Text_NeedBreatherAfterBattles, MSGBOX_NPC
	end

BattleFrontier_Lounge4_Text_WonderIfInterviewsAiring:
	.string "Άραγε θα δείξουν συνεντεύξεις με\n"
	.string "σκληρούς TRAINERS σήμερα;$"

BattleFrontier_Lounge4_Text_IfIOpenedRestaurantHere:
	.string "Αν άνοιγα ένα εστιατόριο εδώ,\n"
	.string "σίγουρα θα έβγαζε λεφτά.$"

BattleFrontier_Lounge4_Text_NeedBreatherAfterBattles:
	.string "Ουφ…\p"
	.string "Πρέπει να πάρω μια ανάσα μετά\n"
	.string "από κάποιες έντονες μάχες…\p"
	.string "Αλλά ακόμα και τώρα, δεν κάνω ποτέ\n"
	.string "διάλειμμα από στρατηγική και combos.$"

