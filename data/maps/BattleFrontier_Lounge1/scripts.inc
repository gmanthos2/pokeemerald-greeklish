BattleFrontier_Lounge1_MapScripts::
	.byte 0

@ NPC that rates pokemon based on their IVs
BattleFrontier_Lounge1_EventScript_Breeder::
	lock
	faceplayer
	call_if_unset FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_BreederIntro
	call_if_set FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder
	setflag FLAG_MET_BATTLE_FRONTIER_BREEDER
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder
	end

BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder::
	special ChoosePartyMon
	waitstate
	goto_if_ne VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge1_EventScript_ShowMonToBreeder
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge1_EventScript_CancelMonSelect
	end

BattleFrontier_Lounge1_EventScript_BreederIntro::
	msgbox BattleFrontier_Lounge1_Text_PokemonBreederIntro, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder::
	msgbox BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon, MSGBOX_DEFAULT
	return

@ BufferVarsForIVRater buffers the following values
@ VAR_0x8005: Sum of the mons IVs
@ VAR_0x8006: Stat id of highest IV stat
@ VAR_0x8007: IV of the highest IV stat
BattleFrontier_Lounge1_EventScript_ShowMonToBreeder::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, BattleFrontier_Lounge1_EventScript_ShowEggToBreeder
	special BufferVarsForIVRater
	goto_if_le VAR_0x8005, 90, BattleFrontier_Lounge1_EventScript_AverageTotalIVs       @ Average of 15
	goto_if_le VAR_0x8005, 120, BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs @ Average of 20
	goto_if_le VAR_0x8005, 150, BattleFrontier_Lounge1_EventScript_HighTotalIVs         @ Average of 25
	goto_if_ge VAR_0x8005, 151, BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs     @ Average of > 25
	end

BattleFrontier_Lounge1_EventScript_ShowEggToBreeder::
	msgbox BattleFrontier_Lounge1_Text_EvenICantTell, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder
	end

@ Comment on the highest IV stat
BattleFrontier_Lounge1_EventScript_HighestIVStat::
	goto_if_eq VAR_0x8006, STAT_HP, BattleFrontier_Lounge1_EventScript_HighestIVHP
	goto_if_eq VAR_0x8006, STAT_ATK, BattleFrontier_Lounge1_EventScript_HighestIVAtk
	goto_if_eq VAR_0x8006, STAT_DEF, BattleFrontier_Lounge1_EventScript_HighestIVDef
	goto_if_eq VAR_0x8006, STAT_SPEED, BattleFrontier_Lounge1_EventScript_HighestIVSpeed
	goto_if_eq VAR_0x8006, STAT_SPATK, BattleFrontier_Lounge1_EventScript_HighestIVSpAtk
	goto_if_eq VAR_0x8006, STAT_SPDEF, BattleFrontier_Lounge1_EventScript_HighestIVSpDef
	end

@ Comment on the highest IV value
BattleFrontier_Lounge1_EventScript_HighestIVValue::
	goto_if_le VAR_0x8007, 15, BattleFrontier_Lounge1_EventScript_HighestIVLow
	goto_if_le VAR_0x8007, 25, BattleFrontier_Lounge1_EventScript_HighestIVMid
	goto_if_le VAR_0x8007, 30, BattleFrontier_Lounge1_EventScript_HighestIVHigh
	goto_if_ge VAR_0x8007, 31, BattleFrontier_Lounge1_EventScript_HighestIVMax
	end

BattleFrontier_Lounge1_EventScript_EndBreederComments::
	release
	end

BattleFrontier_Lounge1_EventScript_AverageTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_AverageAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_BetterThanAverageAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_HighTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_ImpressiveAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_OutstandingAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_HighestIVHP::
	msgbox BattleFrontier_Lounge1_Text_BestAspectHP, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVAtk::
	msgbox BattleFrontier_Lounge1_Text_BestAspectAtk, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVDef::
	msgbox BattleFrontier_Lounge1_Text_BestAspectDef, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpeed::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpeed, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpAtk::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpAtk, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpDef::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpDef, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVLow::
	msgbox BattleFrontier_Lounge1_Text_StatRelativelyGood, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVMid::
	msgbox BattleFrontier_Lounge1_Text_StatImpressive, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVHigh::
	msgbox BattleFrontier_Lounge1_Text_StatOutstanding, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVMax::
	msgbox BattleFrontier_Lounge1_Text_StatFlawless, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_CancelMonSelect::
	msgbox BattleFrontier_Lounge1_Text_NoTimeForMyAdvice, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge1_EventScript_Boy1::
	msgbox BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding, MSGBOX_NPC
	end

BattleFrontier_Lounge1_EventScript_Boy2::
	msgbox BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt, MSGBOX_NPC
	end

BattleFrontier_Lounge1_Text_PokemonBreederIntro:
	.string "Για 70 χρόνια μεγαλώνω POKéMON!\n"
	.string "Είμαι ο άνθρωπος που σέβονται ως\l"
	.string "o θρυλικός κορυφαίος POKéMON BREEDER!\p"
	.string "Εάν γίνεις ποτέ τόσο έμπειρος όσο εγώ,\n"
	.string "θα βλέπεις τις ικανότητες των POKéMON\l"
	.string "με μια ματιά.\p"
	.string "Είσαι TRAINER. Δεν σε ενδιαφέρει να\n"
	.string "μάθεις τις ικανότητες των δικών σου\l"
	.string "POKéMON;\p"
	.string "Εδώ!\n"
	.string "Ας ρίξουμε μια ματιά στα POKéMON σου!$"

BattleFrontier_Lounge1_Text_AverageAbility:
	.string "…Χμμ…\p"
	.string "Αυτό, συνολικά, θα το περιέγραφα\n"
	.string "ως μέσης ικανότητας.$"

BattleFrontier_Lounge1_Text_BetterThanAverageAbility:
	.string "…Χμμ…\p"
	.string "Αυτό, συνολικά, θα το περιέγραφα ως\n"
	.string "καλύτερο από το μέσο όρο.$"

BattleFrontier_Lounge1_Text_ImpressiveAbility:
	.string "…Χμμ…\p"
	.string "Αυτό, συνολικά, θα έλεγα ότι είναι\n"
	.string "αρκετά εντυπωσιακό σε ικανότητες!$"

BattleFrontier_Lounge1_Text_OutstandingAbility:
	.string "…Χμμ…\p"
	.string "Αυτό, συνολικά, θα έλεγα ότι είναι\n"
	.string "υπέροχο σε ικανότητες!$"

BattleFrontier_Lounge1_Text_BestAspectHP:
	.string "Παρεμπιπτόντως, η καλύτερη πτυχή του,\n"
	.string "θα έλεγα, είναι το HP του…$"

BattleFrontier_Lounge1_Text_BestAspectAtk:
	.string "Παρεμπιπτόντως, η καλύτερη πτυχή του,\n"
	.string "θα έλεγα, είναι η EΠΙΘΕΣΗ του…$"

BattleFrontier_Lounge1_Text_BestAspectDef:
	.string "Παρεμπιπτόντως, η καλύτερη πτυχή του,\n"
	.string "θα έλεγα, είναι η AMYNA του…$"

BattleFrontier_Lounge1_Text_BestAspectSpAtk:
	.string "Παρεμπιπτόντως, η καλύτερη πτυχή του,\n"
	.string "θα έλεγα, είναι η ΕΙΔΙΚΗ του EΠΙΘΕΣΗ…$"

BattleFrontier_Lounge1_Text_BestAspectSpDef:
	.string "Παρεμπιπτόντως, η καλύτερη πτυχή του,\n"
	.string "θα έλεγα, είναι η EΙΔΙΚΗ του AMYNA…$"

BattleFrontier_Lounge1_Text_BestAspectSpeed:
	.string "Παρεμπιπτόντως, η καλύτερη πτυχή του,\n"
	.string "θα έλεγα, είναι η TAXYTHTA του…$"

BattleFrontier_Lounge1_Text_StatRelativelyGood:
	.string "Αυτό το στατιστικό είναι σχετικά καλό.\n"
	.string "…Χμ… Έτσι το λέω.$"

BattleFrontier_Lounge1_Text_StatImpressive:
	.string "Αυτό το στατιστικό είναι εντυπωσιακό.\n"
	.string "…Χμ… Έτσι το λέω.$"

BattleFrontier_Lounge1_Text_StatOutstanding:
	.string "Αυτό το στατιστικό είναι εξαιρετικό!\n"
	.string "…Χμ… Έτσι το λέω.$"

BattleFrontier_Lounge1_Text_StatFlawless:
	.string "Είναι άψογο! Ένα δείγμα τελειότητας!\n"
	.string "…Χμ… Έτσι το λέω.$"

BattleFrontier_Lounge1_Text_NoTimeForMyAdvice:
	.string "Τι;\n"
	.string "Δεν έχεις χρόνο για τις συμβουλές μου;\p"
	.string "Πρέπει πάντα να είσαι πρόθυμος να \n"
	.string "μαθαίνεις από τις εμπειρίες \l"
	.string "των μεγαλύτερων!$"

@ Unused
BattleFrontier_Lounge1_Text_HaveBusinessNeedsTending:
	.string "Ναι, τι είναι πάλι;\p"
	.string "Έχω δουλειές που πρέπει να φροντίσω!\n"
	.string "Άστο για την επόμενη φορά!$"

BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon:
	.string "Α, πιτσιρίκι! Σε ιντριγκάρουν οι \n"
	.string "ικανότητες των POKéMON σου;\p"
	.string "Έλα!\n"
	.string "Ας ρίξουμε μια ματιά στα POKéMON σου!$"

BattleFrontier_Lounge1_Text_EvenICantTell:
	.string "Μπορεί να είμαι ειδικός, αλλά \n"
	.string "ακόμη και εγώ δε μπορώ να καταλάβω\l"
	.string "κάτι για ένα αγέννητο POKéMON!\p"
	.string "Δείξε μου ένα POKéMON!\n"
	.string "Ένα POKéMON είναι αυτό που θέλω να δω!$"

BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding:
	.string "Είπε ότι το POKéMON μου είναι\n"
	.string "εξαιρετικό!\l"
	.string "Χαίρομαι που το μεγάλωσα προσεκτικά!$"

BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt:
	.string "Είπε ότι το POKéMON μου είναι\n"
	.string "εξαιρετικό!\p"
	.string "Αλλά δεν έκανα τίποτα ιδιαίτερο για\n"
	.string "να το μεγαλώσω…$"

