MeteorFalls_1F_2R_MapScripts::
	.byte 0

MeteorFalls_1F_2R_EventScript_Nicolas::
	trainerbattle_single TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasIntro, MeteorFalls_1F_2R_Text_NicolasDefeat, MeteorFalls_1F_2R_EventScript_RegisterNicolas
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchNicolas
	msgbox MeteorFalls_1F_2R_Text_NicolasPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterNicolas::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MeteorFalls_1F_2R_Text_NicolasRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_NICOLAS_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchNicolas::
	trainerbattle_rematch TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasRematchIntro, MeteorFalls_1F_2R_Text_NicolasRematchDefeat
	msgbox MeteorFalls_1F_2R_Text_NicolasPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_John::
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnIntro, MeteorFalls_1F_2R_Text_JohnDefeat, MeteorFalls_1F_2R_Text_JohnNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJohn
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchJohn
	msgbox MeteorFalls_1F_2R_Text_JohnPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJohn::
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJohn::
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnRematchIntro, MeteorFalls_1F_2R_Text_JohnRematchDefeat, MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JohnPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_Jay::
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayIntro, MeteorFalls_1F_2R_Text_JayDefeat, MeteorFalls_1F_2R_Text_JayNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJay
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchJay
	msgbox MeteorFalls_1F_2R_Text_JayPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJay::
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT  @ John speaks for both during register
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJay::
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayRematchIntro, MeteorFalls_1F_2R_Text_JayRematchDefeat, MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JayPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_Text_NicolasIntro:
	.string "Εδώ είναι που εμείς οι χρήστες \n"
	.string "DRAGON κάνουμε την προπόνησή μας.\p"
	.string "Ακόμα και o CHAMPION μας επισκέπτεται.\n"
	.string "Βλέπεις πόσο ιδιαίτερα είναι εδώ;$"

MeteorFalls_1F_2R_Text_NicolasDefeat:
	.string "Αργκ!\n"
	.string "Δεν περίμενα να είσαι τόσο δυνατός!$"

MeteorFalls_1F_2R_Text_NicolasPostBattle:
	.string "Ο δρόμος μπροστά παραμένει \n"
	.string "μακρύς και σκληρός.\p"
	.string "Πότε τα POKéMON μου κι εγώ \n"
	.string "θα γίνουμε οι καλύτεροι;$"

MeteorFalls_1F_2R_Text_NicolasRegister:
	.string "Θέλω να μάθω περισσότερα για \n"
	.string "τη δύναμή σου. Επίτρεψέ μου να \l"
	.string "σε καταχωρήσω στο POKéNAV μου.$"

MeteorFalls_1F_2R_Text_NicolasRematchIntro:
	.string "Από τότε που συναντηθήκαμε, \n"
	.string "προπονηθήκαμε σκληρά με στόχο \l"
	.string "την πρώτη θέση.\p"
	.string "Βοήθησέ μας να δούμε πόσο \n"
	.string "πιο δυνατοί έχουμε γίνει!$"

MeteorFalls_1F_2R_Text_NicolasRematchDefeat:
	.string "Αργκ!\n"
	.string "Δεν περίμενα να είσαι τόσο δυνατός!$"

MeteorFalls_1F_2R_Text_NicolasPostRematch:
	.string "Προφανώς συνέχισες την προπόνηση \n"
	.string "των POKéMON σου.\p"
	.string "Όσο παραμένεις δυνατός, \n"
	.string "μπορώ κι εγώ να γίνω δυνατότερος!$"

MeteorFalls_1F_2R_Text_JohnIntro:
	.string "JOHN: Πάντα παλεύουμε με POKéMON \n"
	.string "μαζί σαν ζευγάρι.\l"
	.string "Έχουμε εμπιστοσύνη στον εαυτό μας.$"

MeteorFalls_1F_2R_Text_JohnDefeat:
	.string "JOHN: Ω, αγαπητή μου.\n"
	.string "Χάσαμε, καλή μου σύζυγε.$"

MeteorFalls_1F_2R_Text_JohnPostBattle:
	.string "JOHN: Είμαστε παντρεμένοι \n"
	.string "εδώ και πενήντα χρόνια.\p"
	.string "Αν το καλοσκεφτείς, δεν έχω νικήσει \n"
	.string "ακόμα την καλή μου γυναίκα σε μάχη.$"

MeteorFalls_1F_2R_Text_JohnNotEnoughMons:
	.string "JOHN: Λοιπόν, λοιπόν, τι \n"
	.string "νεαρός TRAINER!\p"
	.string "Θα παλέψεις μαζί μας; Αν ναι, θα \n"
	.string "πρέπει να επιστρέψεις με \l"
	.string "περισσότερα POKéMON.$"

MeteorFalls_1F_2R_Text_JohnRegister:
	.string "JOHN: Νεαρέ TRAINER, αν δοθεί η \n"
	.string "ευκαιρία, θα παλέψεις μαζί μας πάλι;$"

MeteorFalls_1F_2R_Text_JayIntro:
	.string "JAY: Είμαστε παντρεμένοι \n"
	.string "εδώ και πενήντα χρόνια.\p"
	.string "Ο δεσμός που μοιραζόμαστε ως \n"
	.string "ζευγάρι δεν θα μπορούσε να σπάσει.$"

MeteorFalls_1F_2R_Text_JayDefeat:
	.string "JAY: Ω, αγαπητέ μου.\n"
	.string "Χάσαμε, καλέ μου σύζυγε.$"

MeteorFalls_1F_2R_Text_JayPostBattle:
	.string "JAY: Πενήντα χρόνια γάμου…\p"
	.string "Αν ποτέ μαλώναμε, πάντα το λύναμε \n"
	.string "με μια μάχη POKéMON…$"

MeteorFalls_1F_2R_Text_JayNotEnoughMons:
	.string "JAY: Λοιπόν, λοιπόν, δεν είσαι \n"
	.string "ένας νεαρός TRAINER;\p"
	.string "Αν θες να παλέψεις μαζί μας, θα \n"
	.string "πρέπει να επιστρέψεις με \l"
	.string "περισσότερα POKéMON.$"

MeteorFalls_1F_2R_Text_JohnRematchIntro:
	.string "JOHN: Πάντα παλεύουμε με POKéMON \n"
	.string "μαζί σαν ζευγάρι.\l"
	.string "Έχουμε εμπιστοσύνη στον εαυτό μας.$"

MeteorFalls_1F_2R_Text_JohnRematchDefeat:
	.string "JOHN: Ω, αγαπητή μου.\n"
	.string "Χάσαμε, καλή μου σύζυγε.$"

MeteorFalls_1F_2R_Text_JohnPostRematch:
	.string "JOHN: Παντρεμένοι για πενήντα χρόνια…\p"
	.string "Μετά από σκέψη, η καλή μου σύζυγος \n"
	.string "κι εγώ, παλεύαμε μέρα μπαίνει, \l"
	.string "μέρα βγαίνει…$"

MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons:
	.string "JOHN: Λοιπόν, λοιπόν, τι \n"
	.string "νεαρός TRAINER!\p"
	.string "Θα παλέψεις μαζί μας; Αν ναι, θα \n"
	.string "πρέπει να επιστρέψεις με \l"
	.string "περισσότερα POKéMON.$"

MeteorFalls_1F_2R_Text_JayRematchIntro:
	.string "JAY: Είμαστε παντρεμένοι \n"
	.string "εδώ και πενήντα χρόνια.\p"
	.string "Υποστηρίζουμε ο ένας τον άλλον \n"
	.string "όλο αυτό το διάστημα. \l"
	.string "Κάναμε τους εαυτούς μας δυνατούς.$"

MeteorFalls_1F_2R_Text_JayRematchDefeat:
	.string "JAY: Ω, αγαπητέ μου.\n"
	.string "Χάσαμε, καλέ μου σύζυγε.$"

MeteorFalls_1F_2R_Text_JayPostRematch:
	.string "JAY: Πενήντα χρόνια γάμου…\n"
	.string "Πολλά πράγματα έχουν συμβεί.\p"
	.string "Ελπίζω ότι θα συνεχίσουμε να \n"
	.string "κάνουμε χαρούμενες αναμνήσεις μαζί.$"

MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons:
	.string "JAY: Λοιπόν, λοιπόν, δεν είσαι \n"
	.string "ένας νεαρός TRAINER;\p"
	.string "Αν θες να παλέψεις μαζί μας, θα \n"
	.string "πρέπει να επιστρέψεις με \l"
	.string "περισσότερα POKéMON.$"

