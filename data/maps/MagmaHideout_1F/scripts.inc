MagmaHideout_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MagmaHideout_1F_OnTransition
	.byte 0

MagmaHideout_1F_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 0
	end

MagmaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_1, MagmaHideout_1F_Text_Grunt1Intro, MagmaHideout_1F_Text_Grunt1Defeat
	msgbox MagmaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_2, MagmaHideout_1F_Text_Grunt2Intro, MagmaHideout_1F_Text_Grunt2Defeat
	msgbox MagmaHideout_1F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_Text_Grunt1Intro:
	.string "Όταν η TEAM MAGMA παίρνει παρουσίες,\n"
	.string "παίρνουμε τις σκοπιές με τη \l"
	.string "σειρά που στεκόμαστε.\p"
	.string "Γι' αυτό έχω κολλήσει σε\n"
	.string "αυτή τη γωνία.\l"
	.string "Αργώ πάντα στις παρουσίες!$"

MagmaHideout_1F_Text_Grunt1Defeat:
	.string "Αργώ πάντα και στις \n"
	.string "προπονήσεις, επίσης!\p"
	.string "Μισώ που το λέω, αλλά \n"
	.string "είμαι αδύναμος…$"

MagmaHideout_1F_Text_Grunt1PostBattle:
	.string "Εντάξει, θα προσπαθήσω να κάνω\n"
	.string "λίγη περισσότερη προσπάθεια πια…$"

MagmaHideout_1F_Text_Grunt2Intro:
	.string "Ο αρχηγός μας, μας είπε να σκάψουμε\n"
	.string "στο MT. CHIMNEY, οπότε σκάβαμε \l"
	.string "και σκάβαμε.\p"
	.string "Και κατά τη διάρκεια του σκαψίματος,\n"
	.string "βρήκαμε κάτι που μας πήρε τα μυαλά!\p"
	.string "Τι βρήκαμε;\p"
	.string "Φουχαχαχα!\n"
	.string "Θα σου πω αν με κερδίσεις!$"

MagmaHideout_1F_Text_Grunt2Defeat:
	.string "Ααααχ!\n"
	.string "Έχασα!$"

MagmaHideout_1F_Text_Grunt2PostBattle:
	.string "Δεν θα σου πω τελικά.\n"
	.string "Θα μάθεις όταν πας εκεί!\p"
	.string "Είναι καλύτερα αν κρατάς τις \n"
	.string "εκπλήξεις για το τέλος, \l"
	.string "δε νομίζεις;$"

