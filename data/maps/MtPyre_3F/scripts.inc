MtPyre_3F_MapScripts::
	.byte 0

MtPyre_3F_EventScript_William::
	trainerbattle_single TRAINER_WILLIAM, MtPyre_3F_Text_WilliamIntro, MtPyre_3F_Text_WilliamDefeat
	msgbox MtPyre_3F_Text_WilliamPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Kayla::
	trainerbattle_single TRAINER_KAYLA, MtPyre_3F_Text_KaylaIntro, MtPyre_3F_Text_KaylaDefeat
	msgbox MtPyre_3F_Text_KaylaPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Gabrielle::
	trainerbattle_single TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleIntro, MtPyre_3F_Text_GabrielleDefeat, MtPyre_3F_EventScript_RegisterGabrielle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_3F_EventScript_RematchGabrielle
	msgbox MtPyre_3F_Text_GabriellePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_3F_EventScript_RegisterGabrielle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_3F_Text_GabrielleRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_GABRIELLE_1
	release
	end

MtPyre_3F_EventScript_RematchGabrielle::
	trainerbattle_rematch TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleRematchIntro, MtPyre_3F_Text_GabrielleRematchDefeat
	msgbox MtPyre_3F_Text_GabriellePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_Text_WilliamIntro:
	.string "Η πλούσια ατμόσφαιρα του βουνού \n"
	.string "έχει ανεβάσει την ψυχική μου \l"
	.string "δύναμη!\p"
	.string "Ένα απλό παιδί σαν εσένα… \n"
	.string "Ονειρεύεσαι να νικήσεις;$"

MtPyre_3F_Text_WilliamDefeat:
	.string "Πνίγομαι στην αυτολύπηση…$"

MtPyre_3F_Text_WilliamPostBattle:
	.string "Οι ψυχικές μου δυνάμεις σίγουρα \n"
	.string "έχουν αυξηθεί κατά πολύ, αλλά…$"

MtPyre_3F_Text_KaylaIntro:
	.string "Αχαχαχαχα!\p"
	.string "Αυτό το μέρος δεν είναι για \n"
	.string "παιδιά, και ειδικά για σένα!$"

MtPyre_3F_Text_KaylaDefeat:
	.string "Έχασα τόσο καθαρά…$"

MtPyre_3F_Text_KaylaPostBattle:
	.string "Αυτό σημαίνει ότι η προπόνησή \n"
	.string "μου δεν είναι ακόμα αρκετή…\p"
	.string "Πρέπει να συνεχίσω να δουλεύω \n"
	.string "προς την κορυφή…\p"
	.string "Εμπρός, εγώ!$"

MtPyre_3F_Text_GabrielleIntro:
	.string "Γιατί ήρθες εδώ;$"

MtPyre_3F_Text_GabrielleDefeat:
	.string "Αυτό ήταν εκπληκτικό!\n"
	.string "Είσαι ένας πολύ ιδιαίτερος TRAINER.$"

MtPyre_3F_Text_GabriellePostBattle:
	.string "POKéMON που δεν βρίσκονται πια σε \n"
	.string "αυτόν τον κόσμο. POKéMON που είναι \l"
	.string "μαζί σου τώρα.\p"
	.string "Και τα POKéMON που θα συναντήσεις \n"
	.string "στο μέλλον…\p"
	.string "Πρέπει όλα να τα αγαπάς εξίσου. \n"
	.string "Σε παρακαλώ, θυμήσου το αυτό.$"

MtPyre_3F_Text_GabrielleRegister:
	.string "Θα ήθελα να δω τα POKéMON σου \n"
	.string "όταν μεγαλώσουν λίγο ακόμα…\p"
	.string "Σε παρακαλώ, χρειάζεται να δω το \n"
	.string "POKéNAV σου.$"

MtPyre_3F_Text_GabrielleRematchIntro:
	.string "Ω, εσύ είσαι…\p"
	.string "Ήρθες να μου δείξεις τα \n"
	.string "αναπτυγμένα σου POKéMON;$"

MtPyre_3F_Text_GabrielleRematchDefeat:
	.string "Πόσο εκπληκτικό!\n"
	.string "Είσαι ένα ιδιαίτερο άτομο.$"

MtPyre_3F_Text_GabriellePostRematch:
	.string "POKéMON που δεν βρίσκονται πια σε \n"
	.string "αυτόν τον κόσμο. POKéMON που είναι \l"
	.string "μαζί σου τώρα.\p"
	.string "Και τα POKéMON που θα συναντήσεις \n"
	.string "στο μέλλον…\p"
	.string "Πρέπει όλα να τα αγαπάς εξίσου. \n"
	.string "Βλέπω ότι το θυμήθηκες αυτό.$"

