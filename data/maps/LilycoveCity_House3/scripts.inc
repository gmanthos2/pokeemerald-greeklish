LilycoveCity_House3_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_House3_OnTransition
	.byte 0

LilycoveCity_House3_OnTransition:
	random 4
	copyvar VAR_TEMP_1, VAR_RESULT
	end

LilycoveCity_House3_EventScript_PokefanF::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LilycoveCity_House3_EventScript_DeclinePokeblockLearn
	msgbox LilycoveCity_House3_Text_ExplainPokeblocks, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_DeclinePokeblockLearn::
	msgbox LilycoveCity_House3_Text_OhAreYouSure, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_Man::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_HappyToHaveQuadruplets, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_GameBoyKid1::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid2::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid3::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid4::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_WereDoingMultiBattle::
	msgbox LilycoveCity_House3_Text_GoingToWinMultiBattles, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereMixingRecords::
	msgbox LilycoveCity_House3_Text_LikeMixingAtRecordCorner, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereBlendingBerries::
	msgbox LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereDoingContest::
	msgbox LilycoveCity_House3_Text_GoingToEnterContest, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks:
	.string "Ω, μα τι βλέπω! Ταξιδεύεις \n"
	.string "χωρίς παρέα; Μα είσαι τόσο μικρό!\l"
	.string "Μπράβο σου!\p"
	.string "Είμαι σίγουρη ότι τα παιδιά μου \n"
	.string "θα μπορούσαν να μάθουν \l"
	.string "κάτι ή δύο από σένα!\p"
	.string "Εγώ; Είμαι μια ειδικός στα {POKEBLOCK}S.\p"
	.string "Αν το πάρω λίγο σοβαρά, ε,\n"
	.string "μπορώ να φτιάξω υπέροχα {POKEBLOCK}S.\p"
	.string "Θα ήθελες να μάθεις από \n"
	.string "μένα, μια ειδικός στα {POKEBLOCK}S;$"

LilycoveCity_House3_Text_OhAreYouSure:
	.string "Ω; Σίγουρα;\p"
	.string "Δεν πρέπει να προσπαθείς πάντα να\n"
	.string "τα κάνεις όλα μόνο σου, αγάπη μου!$"

LilycoveCity_House3_Text_ExplainPokeblocks:
	.string "Καλά! Είσαι έξυπνη ψυχή!\n"
	.string "Αυτό είναι λίγο μεγάλο, γι' αυτό άκου!\p"
	.string "Είσαι έτοιμο;\p"
	.string "Αν κοιτάξεις τα {POKEBLOCK}S, θα δεις\n"
	.string "ότι βαθμολογούνται με βάση \l"
	.string "την αίσθηση τους.\p"
	.string "Όσο χαμηλότερη η βαθμολογία αίσθησης,\n"
	.string "τόσο το καλύτερο. Μην το ξεχνάς αυτό!\p"
	.string "Ένα καλό {POKEBLOCK} έχει χαμηλή\n"
	.string "βαθμολογία αίσθησης και υψηλό Level.\p"
	.string "Ένα POKéMON μπορεί να φάει περισσότερα \n"
	.string "καλά {POKEBLOCK}S παρά συνηθισμένα.\p"
	.string "Και αυτό είναι σημαντικό.\p"
	.string "Αν θες να φτιάξεις απαλά {POKEBLOCK}S,\n"
	.string "χρησιμοποίησε διαφορετικά είδη BERRIES.\p"
	.string "Μην είσαι τσιγκούνης--τα είδη των \n"
	.string "BERRIES επηρεάζουν την απαλότητα \l"
	.string "των {POKEBLOCK}S.\p"
	.string "Και κάτι ακόμα.\p"
	.string "Όσο περισσότεροι ανακατεύουν BERRIES,\n"
	.string "τόσο πιο απαλά τα {POKEBLOCK}S.\p"
	.string "Γι' αυτό θα έπρεπε να μιλάς σε άλλους\n"
	.string "ανθρώπους και να φτιάχνετε {POKEBLOCK}S \l"
	.string "μαζί.\p"
	.string "Αυτά είναι όλα όσα πρέπει να ξέρεις για\n"
	.string "να φτιάχνεις καλά {POKEBLOCK}S.\p"
	.string "Αν όλοι είχαν POKéMON που \n"
	.string "αγαπούσαν, απαλά {POKEBLOCK}S,\l"
	.string "και μια οικογένεια με αγάπη,\l"
	.string "ο κόσμος θα ήταν ένα \l"
	.string "πιο χαρούμενο μέρος.\p"
	.string "Μην τα παρατάς, αγάπη μου!$"

LilycoveCity_House3_Text_HappyToHaveQuadruplets:
	.string "Όταν η γυναίκα μου γέννησε τετράδυμα,\n"
	.string "στοιχηματίζω ότι ήμουν \l"
	.string "σοκαρισμένος.\p"
	.string "Αλλά, τώρα, βλέποντάς τα να \n"
	.string "παίζουν μαζί, με κάνει χαρούμενο.$"

LilycoveCity_House3_Text_GoingToWinMultiBattles:
	.string "Είμαστε σε MULTI BATTLES, αλλά ξέρω\n"
	.string "ότι θα κερδίσω.$"

LilycoveCity_House3_Text_LikeMixingAtRecordCorner:
	.string "Μας αρέσει να ανακατεύουμε πράγματα\n"
	.string "στο RECORD CORNER.\p"
	.string "Αλλά τι ανακατεύεται;$"

LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender:
	.string "Θα φτιάξουμε σούπερ {POKEBLOCK}S\n"
	.string "με ένα BERRY BLENDER!$"

LilycoveCity_House3_Text_GoingToEnterContest:
	.string "Θέλω να καυχηθώ για το πόσο δυνατό είναι\n"
	.string "το POKéMON μου, γι' αυτό θα μπούμε \l"
	.string "μαζί σε ένα CONTEST.$"

