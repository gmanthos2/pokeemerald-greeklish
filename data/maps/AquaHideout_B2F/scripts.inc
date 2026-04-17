.set LOCALID_MATT, 1
.set LOCALID_SUBMARINE, 4

AquaHideout_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AquaHideout_B2F_OnTransition
	.byte 0

AquaHideout_B2F_OnTransition:
	call_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, AquaHideout_B2F_EventScript_PreventMattNoticing
	end

AquaHideout_B2F_EventScript_PreventMattNoticing::
	setvar VAR_TEMP_1, 1
	return

AquaHideout_B2F_EventScript_MattNoticePlayer::
	lockall
	setvar VAR_0x8008, LOCALID_MATT
	playse SE_PIN
	applymovement VAR_0x8008, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_TEMP_1, 1
	releaseall
	end

AquaHideout_B2F_EventScript_Matt::
	trainerbattle_single TRAINER_MATT, AquaHideout_B2F_Text_MattIntro, AquaHideout_B2F_Text_MattDefeat, AquaHideout_B2F_EventScript_SubmarineEscape
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_SubmarineEscape::
	setvar VAR_0x8008, LOCALID_MATT
	setvar VAR_0x8009, LOCALID_SUBMARINE
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_OurBossGotThroughHisPreparations, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFasterLeft
	applymovement VAR_0x8009, AquaHideout_B2F_Movement_SumbarineDepartLeft
	waitmovement 0
	removeobject VAR_0x8009
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	setflag FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE
	setflag FLAG_HIDE_LILYCOVE_CITY_AQUA_GRUNTS
	release
	end

AquaHideout_B2F_Movement_SumbarineDepartLeft:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

@ Unused
AquaHideout_B2F_Movement_SumbarineDepartRight:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

AquaHideout_B2F_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_4, AquaHideout_B2F_Text_Grunt4Intro, AquaHideout_B2F_Text_Grunt4Defeat, AquaHideout_B2F_EventScript_Grunt4Defeated
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt4Defeated::
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_6, AquaHideout_B2F_Text_Grunt6Intro, AquaHideout_B2F_Text_Grunt6Defeat
	msgbox AquaHideout_B2F_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_8, AquaHideout_B2F_Text_Grunt8Intro, AquaHideout_B2F_Text_Grunt8Defeat
	msgbox AquaHideout_B2F_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_Text_MattIntro:
	.string "Χεχεχε…\p"
	.string "Έφτασες ήδη εδώ, ε;\n"
	.string "Σε υποτιμήσαμε!\p"
	.string "Αλλά ως εδώ ήταν!\p"
	.string "Είμαι ανώτερος από τους GRUNTS που\n"
	.string "έχεις δει μέχρι τώρα.\p"
	.string "Δεν προσπαθώ να κερδίσω χρόνο.\n"
	.string "Θα σε συντρίψω!$"

AquaHideout_B2F_Text_MattDefeat:
	.string "Χεχεχε…\n"
	.string "Οπότε, έχασα κι εγώ…$"

AquaHideout_B2F_Text_OurBossGotThroughHisPreparations:
	.string "Χεχεχε!\p"
	.string "Όσο έπαιζα μαζί σου, ο BOSS μας\n"
	.string "τελείωσε με τις προετοιμασίες του!$"

AquaHideout_B2F_Text_MattPostBattle:
	.string "Χεχεχε!\p"
	.string "Ο BOSS μας έχει ήδη αναχωρήσει για\n"
	.string "κάποια σπηλιά κάτω από τη θάλασσα!\p"
	.string "Αν σκοπεύεις να τον κυνηγήσεις, θα\n"
	.string "ήταν καλό να ψάξεις στην απέραντη\l"
	.string "θάλασσα πέρα από την LILYCOVE.\p"
	.string "Αλλά θα τον βρεις ποτέ;\n"
	.string "Χεχεχε!$"

AquaHideout_B2F_Text_Grunt4Intro:
	.string "Ουαχαχα, κουράστηκα να περιμένω!\n"
	.string "Μου χρωστάς κι εμένα μια μάχη!$"

AquaHideout_B2F_Text_Grunt4Defeat:
	.string "Κουρασμένος από την αναμονή…\n"
	.string "Χαμένος και ζαλισμένος…$"

AquaHideout_B2F_Text_Grunt4PostBattle:
	.string "BOSS…\n"
	.string "Είναι αρκετά καλό αυτό;$"

AquaHideout_B2F_Text_Grunt6Intro:
	.string "Warp panels, το καμάρι κι η χαρά\n"
	.string "του HIDEOUT!\p"
	.string "Δεν έχεις ιδέα πού βρίσκεσαι,\n"
	.string "έτσι δεν είναι;\p"
	.string "Μπέρδεψε και κούρασε τον εχθρό, κι\n"
	.string "έπειτα επιτέσου! Αυτό είναι το σχέδιο!$"

AquaHideout_B2F_Text_Grunt6Defeat:
	.string "Τι τρέχει με εσένα;\n"
	.string "Δεν έχεις κουραστεί καθόλου;$"

AquaHideout_B2F_Text_Grunt6PostBattle:
	.string "Αυτό μου θυμίζει… Δεν μπορώ να θυμηθώ\n"
	.string "πού έβαλα την MASTER BALL.\p"
	.string "Αν αποτύχω να τη φυλάξω, ο BOSS μας\n"
	.string "θα μου βάλει τις φωνές…$"

AquaHideout_B2F_Text_Grunt8Intro:
	.string "Όταν μπήκα στην TEAM AQUA, το πρώτο\n"
	.string "πράγμα που έπρεπε να μάθω ήταν πώς αυτά\l"
	.string "τα warp panels συνδέονταν μεταξύ τους.$"

AquaHideout_B2F_Text_Grunt8Defeat:
	.string "Ήμουν πολύ απασχολημένος προσπαθώντας\n"
	.string "να καταλάβω τα warp panels…$"

AquaHideout_B2F_Text_Grunt8PostBattle:
	.string "Θα πρέπει να μάθω πώς μπορώ να\n"
	.string "μάχομαι πιο αποτελεσματικά…$"
