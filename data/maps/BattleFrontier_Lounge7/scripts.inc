BattleFrontier_Lounge7_MapScripts::
	.byte 0

BattleFrontier_Lounge7_EventScript_LeftMoveTutor::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_1
	goto_if_set FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetLeftTutor
	msgbox BattleFrontier_Lounge7_Text_LeftTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetLeftTutor::
	msgbox BattleFrontier_Lounge7_Text_LeftTutorWelcomeBack, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Softboiled
	case 1, BattleFrontier_Lounge7_EventScript_SeismicToss
	case 2, BattleFrontier_Lounge7_EventScript_DreamEater
	case 3, BattleFrontier_Lounge7_EventScript_MegaPunch
	case 4, BattleFrontier_Lounge7_EventScript_MegaKick
	case 5, BattleFrontier_Lounge7_EventScript_BodySlam
	case 6, BattleFrontier_Lounge7_EventScript_RockSlide
	case 7, BattleFrontier_Lounge7_EventScript_Counter
	case 8, BattleFrontier_Lounge7_EventScript_ThunderWave
	case 9, BattleFrontier_Lounge7_EventScript_SwordsDance
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewLeftTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Softboiled
	case 1, BattleFrontier_Lounge7_EventScript_SeismicToss
	case 2, BattleFrontier_Lounge7_EventScript_DreamEater
	case 3, BattleFrontier_Lounge7_EventScript_MegaPunch
	case 4, BattleFrontier_Lounge7_EventScript_MegaKick
	case 5, BattleFrontier_Lounge7_EventScript_BodySlam
	case 6, BattleFrontier_Lounge7_EventScript_RockSlide
	case 7, BattleFrontier_Lounge7_EventScript_Counter
	case 8, BattleFrontier_Lounge7_EventScript_ThunderWave
	case 9, BattleFrontier_Lounge7_EventScript_SwordsDance
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_Softboiled::
	setvar VAR_0x8008, 16
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_SeismicToss::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_DreamEater::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MegaPunch::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MegaKick::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_BodySlam::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_RockSlide::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Counter::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ThunderWave::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_SwordsDance::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_RightMoveTutor::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_2
	goto_if_set FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetRightTutor
	msgbox BattleFrontier_Lounge7_Text_RightTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetRightTutor::
	msgbox BattleFrontier_Lounge7_Text_RightTutorWelcomeBack, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl
	case 1, BattleFrontier_Lounge7_EventScript_Snore
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap
	case 3, BattleFrontier_Lounge7_EventScript_Swift
	case 4, BattleFrontier_Lounge7_EventScript_IcyWind
	case 5, BattleFrontier_Lounge7_EventScript_Endure
	case 6, BattleFrontier_Lounge7_EventScript_PsychUp
	case 7, BattleFrontier_Lounge7_EventScript_IcePunch
	case 8, BattleFrontier_Lounge7_EventScript_ThunderPunch
	case 9, BattleFrontier_Lounge7_EventScript_FirePunch
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewRightTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl
	case 1, BattleFrontier_Lounge7_EventScript_Snore
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap
	case 3, BattleFrontier_Lounge7_EventScript_Swift
	case 4, BattleFrontier_Lounge7_EventScript_IcyWind
	case 5, BattleFrontier_Lounge7_EventScript_Endure
	case 6, BattleFrontier_Lounge7_EventScript_PsychUp
	case 7, BattleFrontier_Lounge7_EventScript_IcePunch
	case 8, BattleFrontier_Lounge7_EventScript_ThunderPunch
	case 9, BattleFrontier_Lounge7_EventScript_FirePunch
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_DefenseCurl::
	setvar VAR_0x8008, 16
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Snore::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MudSlap::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Swift::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_IcyWind::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Endure::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_PsychUp::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_IcePunch::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ThunderPunch::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_FirePunch::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect::
	special CloseBattleFrontierTutorWindow
	special CloseBattlePointsWindow
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge7_EventScript_CancelChooseMon::
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

@ VAR_0x8008 is the price
@ VAR_TEMP_C is the scroll multichoice ID
@ VAR_TEMP_FRONTIER_TUTOR_SELECTION is the move selection
@ VAR_TEMP_FRONTIER_TUTOR_ID is which move tutor was spoken to
BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection::
	copyvar VAR_0x8004, VAR_TEMP_FRONTIER_TUTOR_SELECTION
	copyvar VAR_0x8005, VAR_TEMP_FRONTIER_TUTOR_ID
	special BufferBattleFrontierTutorMoveName
	buffernumberstring STR_VAR_2, VAR_0x8008
	copyvar VAR_0x8004, VAR_TEMP_C
	msgbox BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge7_EventScript_ChooseNewMove
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_Lounge7_EventScript_TeachTutorMove
	msgbox BattleFrontier_Lounge7_Text_HaventGotEnoughPoints, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseNewMove
	end

BattleFrontier_Lounge7_EventScript_TeachTutorMove::
	msgbox BattleFrontier_Lounge7_Text_TeachMoveToWhichMon, MSGBOX_DEFAULT
	special GetBattleFrontierTutorMoveIndex
	fadescreen FADE_TO_BLACK
	special CloseBattlePointsWindow
	special CloseBattleFrontierTutorWindow
	special ChooseMonForMoveTutor
	waitstate
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_Lounge7_EventScript_CancelChooseMon
	msgbox BattleFrontier_Lounge7_Text_IllTakeBattlePoints, MSGBOX_DEFAULT
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	release
	end

BattleFrontier_Lounge7_EventScript_ChooseNewMove::
	goto_if_eq VAR_TEMP_FRONTIER_TUTOR_ID, 0, BattleFrontier_Lounge7_EventScript_ChooseNewLeftTutorMove
	goto BattleFrontier_Lounge7_EventScript_ChooseNewRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_Sailor::
	msgbox BattleFrontier_Lounge7_Text_ThinkLadiesDontGetAlong, MSGBOX_NPC
	end

BattleFrontier_Lounge7_EventScript_Gentleman::
	msgbox BattleFrontier_Lounge7_Text_LadiesWereStrongAndBeautiful, MSGBOX_NPC
	end

BattleFrontier_Lounge7_Text_LeftTutorIntro:
	.string "Μπουχαχαχα!\p"
	.string "Δεν φαίνεται αν με δεις τώρα, αλλά \n"
	.string "ήμουν ένας σκληρός TRAINER.\p"
	.string "Είχα τη φήμη ως η πιο σκληρή\n"
	.string "BEAUTY τριγύρω, σου λέω!\p"
	.string "… … … … … …\p"
	.string "Τι τρέχει τώρα;\n"
	.string "Δεν με πιστεύεις;\p"
	.string "Δεν είμαι σαν αυτή τη φαντασμένη \n"
	.string "γυναίκα εκεί πέρα. Έχω ταλέντο!\p"
	.string "Άσε με να σου το αποδείξω.\n"
	.string "Μπορώ διδάξω στα POKéMON σου ειδικές \l"
	.string "αλλά χαριτωμένες κινήσεις.\p"
	.string "Όμως τα μαθήματά μου δεν είναι \n"
	.string "δωρεάν. Τι θα έλεγες να πλήρωνες για\l"
	.string "τις κινήσεις με λίγα Battle Points;$"

BattleFrontier_Lounge7_Text_LeftTutorWelcomeBack:
	.string "Μπουχαχαχα!\p"
	.string "Επέστρεψες για να μάθεις ειδικές\n"
	.string "κι ωστόσο χαριτωμένες κινήσεις;$"

BattleFrontier_Lounge7_Text_TeachWhichMove:
	.string "Καλά, καλά, κοίτα εδώ!\n"
	.string "Ποια κίνηση να διδάξω;$"

BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints:
	.string "Η κίνηση {STR_VAR_1}, έτσι;\n"
	.string "Θα κοστίσει {STR_VAR_2} Battle Points, οκ;$"

BattleFrontier_Lounge7_Text_TeachMoveToWhichMon:
	.string "Καλά, καλά, τώρα διάλεξε το POKéMON\n"
	.string "που θα διδάξω την κίνηση.$"

BattleFrontier_Lounge7_Text_HaventGotEnoughPoints:
	.string "Τι στο...\n"
	.string "Δεν έχεις αρκετά Battle Points!$"

BattleFrontier_Lounge7_Text_IllTakeBattlePoints:
	.string "Βλέπεις πόσο επιδέξια είμαι τώρα;\n"
	.string "Θα πάρω τα Battle Points σου!$"

BattleFrontier_Lounge7_Text_YouDontWantTo:
	.string "Τι είναι αυτό;\n"
	.string "Δεν θέλεις…\p"
	.string "Αν θέλεις να δεις πόσο επιδέξια \n"
	.string "είμαι, έλα να με δεις όποτε θες!$"

BattleFrontier_Lounge7_Text_RightTutorIntro:
	.string "Ιχιχιχι!\p"
	.string "Ξέρω ότι είναι δύσκολο να φανεί,\n"
	.string "αλλά ήμουν φανταστική TRAINER.\p"
	.string "Είχα τη φήμη της πιο\n"
	.string "ανίκητης SWIMMER, σου λέω!\p"
	.string "… … … … … …\p"
	.string "Τι τρέχει;\n"
	.string "Δεν με πιστεύεις;\p"
	.string "Δεν είμαι σαν αυτή τη γελοία γυναίκα\n"
	.string "εκείπέρα. Είμαι έμπειρη!\p"
	.string "Μπορώ να στο αποδείξω.\n"
	.string "Μπορώ να διδάξω στα POKéMON σκληρές\l"
	.string "όμως όμορφες κινήσεις.\p"
	.string "Αλλά τα μαθήματά μου δεν είναι\n"
	.string "δωρεάν. Τι θα έλεγες να πλήρωνες για \l"
	.string "τις κινήσεις με λίγα Battle Points;$"

BattleFrontier_Lounge7_Text_RightTutorWelcomeBack:
	.string "Ιχιχιχι!\p"
	.string "Ήρθες για να μάθεις σκληρές\n"
	.string "αλλά και όμορφες κινήσεις POKéMON;$"

BattleFrontier_Lounge7_Text_ThinkLadiesDontGetAlong:
	.string "Αυτές οι κυρίες, όπως κακολογούν η\n"
	.string "μια την άλλη, μάλλον νομίζεις ότι δεν\l"
	.string "τα πάνε καλά.\p"
	.string "Αλλά αν ίσχυε αυτό, δεν θα βρίσκονταν\n"
	.string "εδώ έξω μαζί, έτσι δεν είναι;$"

BattleFrontier_Lounge7_Text_LadiesWereStrongAndBeautiful:
	.string "Όταν ήμουν απλώς ένας YOUNGSTER,\n"
	.string "αυτές οι κυρίες ήταν δυνατές & όμορφες.\p"
	.string "Ήταν είδωλα ανάμεσα στους TRAINERS μας.\p"
	.string "Ακόμα και τώρα, η ηλικία δεν έχει\n"
	.string "αμβλύνει τις ικανότητές τους.\p"
	.string "Στην πραγματικότητα, οι κινήσεις τους\n"
	.string "έγιναν ακόμα πιο εκλεπτυσμένες.\p"
	.string "Αλλά… Για κάποιο λόγο, δεν μπορώ\n"
	.string "παρά να το νιώσω αυτό…\p"
	.string "Ο χρόνος είναι τόσο σκληρός…$"

BattleFrontier_Lounge7_Text_SoftboiledDesc::
	.string "Ανακτά έως\n"
	.string "το μισό max HP\n"
	.string "του χρήστη.$"

BattleFrontier_Lounge7_Text_SeismicTossDesc::
	.string "Κάνει damage\n"
	.string "ίσο με το \n"
	.string "level του χρήστη.$"

BattleFrontier_Lounge7_Text_DreamEaterDesc::
	.string "Ανακτά μισό \n"
	.string "damage από κοιμώ-\n"
	.string "μενο εχθρό.$"

BattleFrontier_Lounge7_Text_MegaPunchDesc::
	.string "Δυνατή γροθιά\n"
	.string "που δίνεται με\n"
	.string "απίστευτη δύναμη.$"

BattleFrontier_Lounge7_Text_MegaKickDesc::
	.string "Ένα εξαιρετικά\n"
	.string "δυνατό λάκτισμα με\n"
	.string "έντονη δύναμη.$"

BattleFrontier_Lounge7_Text_BodySlamDesc::
	.string "Πέσιμο με όλο το\n"
	.string "σώμα. Μπορεί να\n"
	.string "κάνει παράλυση.$"

BattleFrontier_Lounge7_Text_RockSlideDesc::
	.string "Πέφτουν μεγάλοι\n"
	.string "βράχοι. Μπορεί \n"
	.string "να κάνει flinch.$"

BattleFrontier_Lounge7_Text_CounterDesc::
	.string "Ανταποδίδει κάθε\n"
	.string "physical hit με\n"
	.string "διπλάσια δύναμη.$"

BattleFrontier_Lounge7_Text_ThunderWaveDesc::
	.string "Αδύναμο χτύπημα\n"
	.string "ηλεκτρισμού που\n"
	.string "παραλύει τον εχθρό.$"

BattleFrontier_Lounge7_Text_SwordsDanceDesc::
	.string "Fighter χορός\n"
	.string "που αυξάνει πολύ\n"
	.string "την ΕΠΙΘΕΣΗ.$"

BattleFrontier_Lounge7_Text_DefenseCurlDesc::
	.string "Κυλιέται για κά-\n"
	.string "λυψη και αύξηση \n"
	.string "της ΑΜΥΝΑΣ.$"

BattleFrontier_Lounge7_Text_SnoreDesc::
	.string "Δυνατή επίθεση\n"
	.string "που γίνεται\n"
	.string "μόνο στον ύπνο.$"

BattleFrontier_Lounge7_Text_MudSlapDesc::
	.string "Ρίχνει λάσπη στο\n"
	.string "πρόσωπο. Μειώνει\n"
	.string "την ευστοχία.$"

BattleFrontier_Lounge7_Text_SwiftDesc::
	.string "Ρίχνει ακτίνες\n"
	.string "που μοιάζουν με\n"
	.string "αστέρι. Δεν χάνει.$"

BattleFrontier_Lounge7_Text_IcyWindDesc::
	.string "Παγωμένη επίθεση\n"
	.string "που μειώνει την\n"
	.string "ΤΑΧΥΤΗΤΑ.$"

BattleFrontier_Lounge7_Text_EndureDesc::
	.string "Αντέχει κάθε\n"
	.string "επίθεση για 1 γύρο\n"
	.string "αφήνοντας 1HP.$"

BattleFrontier_Lounge7_Text_PsychUpDesc::
	.string "Αντιγράφει το\n"
	.string "εφέ του εχθρού\n"
	.string "στο χρήστη.$"

BattleFrontier_Lounge7_Text_IcePunchDesc::
	.string "Μια παγωμένη \n"
	.string "γροθιά που μπορεί\n"
	.string "να παγώσει.$"

BattleFrontier_Lounge7_Text_ThunderPunchDesc::
	.string "Γροθιά ρεύματος\n"
	.string "που μπορεί να\n"
	.string "κάνει παράλυση.$"

BattleFrontier_Lounge7_Text_FirePunchDesc::
	.string "Μια πύρινη \n"
	.string "γροθιά που μπορεί\n"
	.string "να κάψει.$"
