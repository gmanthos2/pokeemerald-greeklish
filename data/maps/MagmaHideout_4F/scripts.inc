.set LOCALID_GROUDON, 1
.set LOCALID_GRUNT_1, 2
.set LOCALID_GRUNT_2, 3
.set LOCALID_GRUNT_3, 4
.set LOCALID_TABITHA, 5
.set LOCALID_MAXIE, 6
.set LOCALID_GROUDON_SLEEPING, 7

MagmaHideout_4F_MapScripts::
	.byte 0

MagmaHideout_4F_EventScript_Maxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MagmaHideout_4F_Text_MaxieAwakenGroudon, MSGBOX_DEFAULT
	closemessage
	delay 20
	setvar VAR_RESULT, 1
	playse SE_M_DETECT
	dofieldeffectsparkle 18, 42, 0
	waitfieldeffect FLDEFF_SPARKLE
	setvar VAR_RESULT, 1
	playfanfare MUS_AWAKEN_LEGEND
	playse SE_ORB
	special DoOrbEffect
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 150
	removeobject LOCALID_GROUDON_SLEEPING
	addobject LOCALID_GROUDON
	waitstate
	delay 60
	applymovement LOCALID_GROUDON, MagmaHideout_4F_Movement_GroudonApproach
	waitmovement 0
	special FadeOutOrbEffect
	waitstate
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_GROUDON, MagmaHideout_4F_Movement_GroudonExit
	waitmovement 0
	removeobject LOCALID_GROUDON
	delay 4
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	delay 30
	applymovement LOCALID_MAXIE, MagmaHideout_4F_Movement_MaxieLookAround
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieGroudonWhatsWrong, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieOhItWasYou, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_MAXIE_MAGMA_HIDEOUT, MagmaHideout_4F_Text_MaxieDefeat
	msgbox MagmaHideout_4F_Text_MaxieImGoingAfterGroudon, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_SLATEPORT_CITY_CAPTAIN_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_GABBY_AND_TY
	setvar VAR_SLATEPORT_CITY_STATE, 1
	setflag FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT
	setvar VAR_SLATEPORT_HARBOR_STATE, 1
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAXIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_TABITHA
	setflag FLAG_HIDE_MAGMA_HIDEOUT_GRUNTS
	fadescreen FADE_FROM_BLACK
	releaseall
	end

MagmaHideout_4F_Movement_GroudonApproach:
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	step_end

MagmaHideout_4F_Movement_GroudonExit:
	slide_up
	slide_up
	step_end

MagmaHideout_4F_Movement_MaxieLookAround:
	face_left
	delay_16
	face_right
	delay_16
	face_left
	delay_16
	face_right
	delay_16
	face_up
	delay_16
	delay_16
	step_end

MagmaHideout_4F_EventScript_Grunt11::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_11, MagmaHideout_4F_Text_Grunt11Intro, MagmaHideout_4F_Text_Grunt11Defeat
	msgbox MagmaHideout_4F_Text_Grunt11PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt12::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_12, MagmaHideout_4F_Text_Grunt12Intro, MagmaHideout_4F_Text_Grunt12Defeat
	msgbox MagmaHideout_4F_Text_Grunt12PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt13::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_13, MagmaHideout_4F_Text_Grunt13Intro, MagmaHideout_4F_Text_Grunt13Defeat
	msgbox MagmaHideout_4F_Text_Grunt13PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MAGMA_HIDEOUT, MagmaHideout_4F_Text_TabithaIntro, MagmaHideout_4F_Text_TabithaDefeat
	msgbox MagmaHideout_4F_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_Text_Grunt11Intro:
	.string "Θέλω να δω το GROUDON, κι εγώ!\n"
	.string "Δεν με αφήνουν να δω \l"
	.string "ούτε την ουρά του…\p"
	.string "Αυτό με απογοητεύει πραγματικά.\p"
	.string "Ω, όχι!\n"
	.string "Μίλησα για το GROUDON!$"

MagmaHideout_4F_Text_Grunt11Defeat:
	.string "Υποθέτω ότι είναι αδύνατο να κερδίσεις\n"
	.string "αν δεν έχεις ήρεμο μυαλό…$"

MagmaHideout_4F_Text_Grunt11PostBattle:
	.string "Αναρωτιέμαι αν το GROUDON \n"
	.string "έχει καν ουρά;$"

MagmaHideout_4F_Text_Grunt12Intro:
	.string "Φουχαχαχα!\n"
	.string "Σύντομα! Πολύ σύντομα!\l"
	.string "Ο μεγάλος μας στόχος θα επιτευχθεί!$"

MagmaHideout_4F_Text_Grunt12Defeat:
	.string "Γκρρρ…\n"
	.string "Έφτασα τόσο μακριά, \l"
	.string "μόνο για να γίνει αυτό;$"

MagmaHideout_4F_Text_Grunt12PostBattle:
	.string "Αρχηγέ MAXIE!\n"
	.string "Ένας εισβολέας έρχεται \l"
	.string "κατά πάνω σου!$"

MagmaHideout_4F_Text_Grunt13Intro:
	.string "Δεν έχεις τελειώσει ακόμα!\n"
	.string "Δεν θα με περάσεις εύκολα!$"

MagmaHideout_4F_Text_Grunt13Defeat:
	.string "Ήμουν τόσο εύκολος να νικηθώ;$"

MagmaHideout_4F_Text_Grunt13PostBattle:
	.string "Έλα, ακόμα ένας αγώνας…$"

MagmaHideout_4F_Text_TabithaIntro:
	.string "Χεχεχε!\n"
	.string "Έφτασες μέχρι εδώ, οπότε \l"
	.string "θα σου πω!\p"
	.string "Αυτό είναι σωστό!\n"
	.string "Πιο μπροστά, το GROUDON κοιμάται!\p"
	.string "Ο MAXIE πήγε στο GROUDON μόλις πριν \n"
	.string "από λίγα δευτερόλεπτα!\p"
	.string "Θα ξυπνήσει πολύ σύντομα!\n"
	.string "Χεχε! Χεχεχε!$"

MagmaHideout_4F_Text_TabithaDefeat:
	.string "Νικήθηκα ξανά…\n"
	.string "Χεχε…$"

MagmaHideout_4F_Text_TabithaPostBattle:
	.string "…Και όσο \n"
	.string "έχασες χρόνο μαζί μου,\l"
	.string "ο MAXIE θα πρέπει να \l"
	.string "ξύπνησε το GROUDON…$"

MagmaHideout_4F_Text_MaxieAwakenGroudon:
	.string "MAXIE: GROUDON…\p"
	.string "Τίποτα δεν μπορούσε να σε \n"
	.string "ξυπνήσει από τον ύπνο \l"
	.string "σου κυλισμένο στο μάγμα…\p"
	.string "Αυτό το BLUE ORB \n"
	.string "είναι αυτό που έψαχνες.\l"
	.string "Δεν είναι;\p"
	.string "Σου έφερα το BLUE ORB.\n"
	.string "Άσε τη λάμψη του να σε ξυπνήσει!\p"
	.string "Και δείξε μου…\n"
	.string "Δείξε μου την πλήρη \l"
	.string "έκταση της δύναμής σου!$"

MagmaHideout_4F_Text_MaxieGroudonWhatsWrong:
	.string "MAXIE: GROUDON!\n"
	.string "Τι τρέχει;\p"
	.string "Δεν ήταν το BLUE ORB \n"
	.string "το κλειδί;\p"
	.string "GROUDON!\n"
	.string "Πού έχεις πάει…$"

MagmaHideout_4F_Text_MaxieOhItWasYou:
	.string "MAXIE: Α, άρα ήσουν εσύ;\p"
	.string "Σε είδα να χώνεις τη \n"
	.string "μύτη σου απρόσκλητος \l"
	.string "εδώ κι εκεί…\p"
	.string "Tο έπιασα τώρα!\n"
	.string "Πρέπει να έκανες \l"
	.string "ένα φτηνό κόλπο!$"

MagmaHideout_4F_Text_MaxieDefeat:
	.string "Τι σε κάνει τόσο ικανό \n"
	.string "στο χειρισμό των POKéMON;$"

MagmaHideout_4F_Text_MaxieImGoingAfterGroudon:
	.string "MAXIE: Πρέπει να υπάρχει κάποιος λόγος\n"
	.string "για τον οποίο τράπηκε\l"
	.string "σε φυγή το GROUDON…\p"
	.string "Αυτό προσπαθείς να \n"
	.string "μου πεις, έτσι δεν είναι;\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Χαμπφ…\n"
	.string "Νομίζεις ότι δεν το ήξερα;\p"
	.string "Με τον GROUDON να έχει φύγει, \n"
	.string "δεν υπάρχει πλέον καμία\l"
	.string "ανάγκη για αυτό το\l"
	.string "καταραμένο ηφαίστειο.\p"
	.string "Θα ακολουθήσω τον \n"
	.string "GROUDON, οπότε \l"
	.string "εδώ χωρίζουν οι δρόμοι μας!$"
