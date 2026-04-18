MtPyre_1F_MapScripts::
	.byte 0

MtPyre_1F_EventScript_CleanseTagWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CLEANSE_TAG, MtPyre_1F_EventScript_ReceivedCleanseTag
	msgbox MtPyre_1F_Text_TakeThisForYourOwnGood, MSGBOX_DEFAULT
	giveitem ITEM_CLEANSE_TAG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CLEANSE_TAG
	release
	end

MtPyre_1F_EventScript_ReceivedCleanseTag::
	msgbox MtPyre_1F_Text_ExplainCleanseTag, MSGBOX_DEFAULT
	release
	end

MtPyre_1F_EventScript_PokefanF::
	msgbox MtPyre_1F_Text_ComeToPayRespects, MSGBOX_NPC
	end

MtPyre_1F_EventScript_Man::
	msgbox MtPyre_1F_Text_RestingPlaceOfZigzagoon, MSGBOX_NPC
	end

MtPyre_1F_Text_TakeThisForYourOwnGood:
	.string "Κάθε λογής πλάσματα περιπλανώνται \n"
	.string "στις πλαγιές του MT. PYRE…\p"
	.string "Κανείς δεν ξέρει τι μπορεί να \n"
	.string "συμβεί. Πάρε αυτό. Είναι για το \l"
	.string "καλό σου.$"

MtPyre_1F_Text_ExplainCleanseTag:
	.string "Δώσε σε ένα POKéMON να κρατήσει \n"
	.string "αυτό το CLEANSE TAG.\p"
	.string "Θα βοηθήσει να απωθήσεις τα \n"
	.string "άγρια POKéMON.$"

MtPyre_1F_Text_ComeToPayRespects:
	.string "Ήρθες να αποτίσεις φόρο τιμής \n"
	.string "στα πνεύματα των POKéMON που \l"
	.string "έφυγαν;\p"
	.string "Πρέπει να νοιάζεσαι πολύ για \n"
	.string "τα POKéMON σου.$"

MtPyre_1F_Text_RestingPlaceOfZigzagoon:
	.string "Αυτός είναι ο τόπος ανάπαυσης του \n"
	.string "ZIGZAGOON μου. Το αγαπούσα πολύ…$"

