MtPyre_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, CaveHole_FixCrackedGround
	map_script MAP_SCRIPT_ON_RESUME, MtPyre_2F_SetHoleWarp
	.byte 0

MtPyre_2F_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_MT_PYRE_1F
	end

MtPyre_2F_EventScript_Woman::
	msgbox MtPyre_2F_Text_MemoriesOfSkitty, MSGBOX_NPC
	end

MtPyre_2F_EventScript_PokefanM::
	msgbox MtPyre_2F_Text_TumbledFromFloorAbove, MSGBOX_NPC
	end

MtPyre_2F_EventScript_Mark::
	trainerbattle_single TRAINER_MARK, MtPyre_2F_Text_MarkIntro, MtPyre_2F_Text_MarkDefeat
	msgbox MtPyre_2F_Text_MarkPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Luke::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_LukeIntro, MtPyre_2F_Text_LukeDefeat, MtPyre_2F_Text_LukeNotEnoughMons
	msgbox MtPyre_2F_Text_LukePostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Dez::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_DezIntro, MtPyre_2F_Text_DezDefeat, MtPyre_2F_Text_DezNotEnoughMons
	msgbox MtPyre_2F_Text_DezPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Leah::
	trainerbattle_single TRAINER_LEAH, MtPyre_2F_Text_LeahIntro, MtPyre_2F_Text_LeahDefeat
	msgbox MtPyre_2F_Text_LeahPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Zander::
	trainerbattle_single TRAINER_ZANDER, MtPyre_2F_Text_ZanderIntro, MtPyre_2F_Text_ZanderDefeat
	msgbox MtPyre_2F_Text_ZanderPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_Text_MemoriesOfSkitty:
	.string "Αναμνήσεις από την αγαπημένη μου \n"
	.string "SKITTY… Τα μάτια μου βουρκώνουν \l"
	.string "μόνο που το σκέφτομαι.$"

MtPyre_2F_Text_TumbledFromFloorAbove:
	.string "Ωχ, αχ… Υπάρχουν τρύπες στο έδαφος \n"
	.string "εδώ κι εκεί.\p"
	.string "Δεν το πρόσεξα και έπεσα από τον \n"
	.string "πάνω όροφο.$"

MtPyre_2F_Text_MarkIntro:
	.string "Έι! Ψάχνεις για POKéMON; Ήρθες \n"
	.string "μετά από μένα! Είσαι αγενής!$"

MtPyre_2F_Text_MarkDefeat:
	.string "Αϊιιιι!\n"
	.string "Λυπήσου με, συγχώρεσέ με, σε \l"
	.string "παρακαλώ!$"

MtPyre_2F_Text_MarkPostBattle:
	.string "Ο κόσμος δεν έρχεται συχνά εδώ, οπότε \n"
	.string "νόμιζα ότι θα υπήρχαν σπάνια POKéMON.$"

MtPyre_2F_Text_LukeIntro:
	.string "LUKE: Ήρθαμε εδώ για ένα \n"
	.string "στοίχημα.\p"
	.string "Χεχ, αν της δείξω πόσο κουλ είμαι, \n"
	.string "θα με ερωτευτεί. Το ξέρω!\p"
	.string "Το βρήκα! Θα σε τσακίσω και θα της \n"
	.string "δείξω πόσο κουλ είμαι!$"

MtPyre_2F_Text_LukeDefeat:
	.string "LUKE: Ούπσι!$"

MtPyre_2F_Text_LukePostBattle:
	.string "LUKE: Λοιπόν, χάσαμε αλλά δεν \n"
	.string "πειράζει! Είμαι ακριβώς εδώ δίπλα \l"
	.string "σου. Θα το περάσουμε αυτό το \l"
	.string "στοίχημα!$"

MtPyre_2F_Text_LukeNotEnoughMons:
	.string "LUKE: Αν θες να με αντιμετωπίσεις, \n"
	.string "φέρε κι άλλα POKéMON.\p"
	.string "Αν δεν το κάνεις, δεν θα μπορέσω \n"
	.string "να δείξω στο κορίτσι μου πόσο \l"
	.string "κουλ είμαι!$"

MtPyre_2F_Text_DezIntro:
	.string "DEZ: Ήρθα εδώ για ένα στοίχημα με \n"
	.string "το αγόρι μου.\p"
	.string "Είναι πολύ τρομακτικά, αλλά είμαι \n"
	.string "με το αγόρι μου. Είναι εντάξει.\p"
	.string "Το βρήκα! Θα κάνω το αγόρι μου να \n"
	.string "φανεί κουλ νικώντας σε!$"

MtPyre_2F_Text_DezDefeat:
	.string "DEZ: Ουάαα! Φοβάμαι!$"

MtPyre_2F_Text_DezPostBattle:
	.string "DEZ: Είμαστε πολύ ερωτευμένοι, \n"
	.string "οπότε δεν μας νοιάζει αν χάνουμε!$"

MtPyre_2F_Text_DezNotEnoughMons:
	.string "DEZ: Αν θες να μας προκαλέσεις, θα \n"
	.string "πρέπει να φέρεις τουλάχιστον δύο \l"
	.string "POKéMON.\p"
	.string "Το αγόρι μου είναι δυνατό. Ένα \n"
	.string "POKéMON μόνο δεν φτάνει καθόλου.$"

MtPyre_2F_Text_LeahIntro:
	.string "Είσαι ένα ασυνήθιστο θέαμα… \n"
	.string "Φύγε πριν σου συμβεί κάτι κακό!$"

MtPyre_2F_Text_LeahDefeat:
	.string "Χμ…\n"
	.string "Έχεις αντοχές.$"

MtPyre_2F_Text_LeahPostBattle:
	.string "Η οικογένειά μας είναι TRAINERS \n"
	.string "εδώ από την εποχή της προγιαγιάς \l"
	.string "μου…\p"
	.string "Είναι καθήκον μου να προστατεύω \n"
	.string "αυτό το βουνό…$"

MtPyre_2F_Text_ZanderIntro:
	.string "Κιάαααα!\n"
	.string "Είμαι τρομοκρατημένος!$"

MtPyre_2F_Text_ZanderDefeat:
	.string "Oοοοοοχι!\n"
	.string "Έχασα τα λογικά μου!$"

MtPyre_2F_Text_ZanderPostBattle:
	.string "Τρομάζω κάθε φορά που βλέπω \n"
	.string "κάτι να κινείται…\p"
	.string "Δεν έπρεπε να έρθω εδώ για \n"
	.string "προπόνηση…$"

