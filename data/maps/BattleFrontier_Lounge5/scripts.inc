BattleFrontier_Lounge5_MapScripts::
	.byte 0

BattleFrontier_Lounge5_EventScript_NatureGirl::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge5_Text_NatureGirlGreeting, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	special ChoosePartyMon
	waitstate
	lock
	faceplayer
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, BattleFrontier_Lounge5_EventScript_NatureGirlEgg
	special ShowNatureGirlMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlEgg::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlEgg, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlNoneShown, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_Gentleman::
	msgbox BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_BlackBelt::
	msgbox BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_LittleBoy::
	msgbox BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot, MSGBOX_NPC
	end

BattleFrontier_Lounge5_Text_NatureGirlGreeting::
	.string "Εχεχε!\n"
	.string "Ξέρω τι σκέφτονται τα POKéMON!\p"
	.string "Σε παρακαλώ!\n"
	.string "Μπορώ να δω τα POKéMON σου;$"

BattleFrontier_Lounge5_Text_NatureGirlNoneShown::
	.string "Μπου!\n"
	.string "Κρίμα!$"

BattleFrontier_Lounge5_Text_NatureGirlHardy::
	.string "Χμχμ…\p"
	.string "Αυτό λέει ότι του αρέσει να πολεμάει!\n"
	.string "Θα παλέψει ακόμα κι αν έχει πολλά\l"
	.string "βαβά!$"

BattleFrontier_Lounge5_Text_NatureGirlLonely::
	.string "Χμχμ…\p"
	.string "Λέει ότι του αρέσει να είναι πονηρό!\n"
	.string "Αλλά αν αποκτήσει αρκετά βαβά,\l"
	.string "θα ανταποδώσει το χτύπημα!$"

BattleFrontier_Lounge5_Text_NatureGirlBrave::
	.string "Χμχμ…\p"
	.string "Αυτό λέει ότι του αρέσει να πολεμάει!\n"
	.string "Αλλά αν αποκτήσει αρκετά βαβά,\l"
	.string "θα ανησυχήσει για τον εαυτό του!$"

BattleFrontier_Lounge5_Text_NatureGirlAdamant::
	.string "Χμχμ…\p"
	.string "Αυτό λέει ότι του αρέσει να πολεμάει!\n"
	.string "Θα παλέψει ακόμα κι αν έχει πολλά\l"
	.string "βαβά!$"

BattleFrontier_Lounge5_Text_NatureGirlNaughty::
	.string "Χμχμ…\p"
	.string "Αυτό λέει ότι προσέχει τον εαυτό του!\n"
	.string "Αλλά αν αποκτήσει αρκετά βαβά,\l"
	.string "θα ανταποδώσει το χτύπημα!$"

BattleFrontier_Lounge5_Text_NatureGirlBold::
	.string "Χμχμ…\p"
	.string "Λέει ότι του αρέσει να είναι πονηρό!\n"
	.string "Αλλά αν αποκτήσει αρκετά βαβά,\l"
	.string "θα ανησυχήσει για τον εαυτό του!$"

BattleFrontier_Lounge5_Text_NatureGirlDocileNaiveQuietQuirky::
	.string "Χμχμ…\p"
	.string "Αυτό λέει ότι του αρέσει να πολεμάει!\n"
	.string "Θα παλέψει ακόμα κι αν έχει πολλά\l"
	.string "βαβά!$"

BattleFrontier_Lounge5_Text_NatureGirlRelaxed::
	.string "Χμχμ…\p"
	.string "Λέει ότι του αρέσει να είναι πονηρό!\n"
	.string "Αλλά αν αποκτήσει αρκετά βαβά,\l"
	.string "θα ανταποδώσει το χτύπημα!$"

BattleFrontier_Lounge5_Text_NatureGirlImpish::
	.string "Χμχμ…\p"
	.string "Αυτό λέει ότι του αρέσει να πολεμάει!\n"
	.string "Αλλά αν αποκτήσει αρκετά βαβά,\l"
	.string "θα ανησυχήσει για τον εαυτό του!$"

BattleFrontier_Lounge5_Text_NatureGirlLax::
	.string "Χμχμ…\p"
	.string "Λέει ότι του αρέσει να είναι πονηρό!\n"
	.string "Λέει ότι του αρέσει να είναι πονηρό\l"
	.string "ακόμα κι αν έχει πολλά βαβά!$"

BattleFrontier_Lounge5_Text_NatureGirlTimid::
	.string "Χμχμ…\p"
	.string "Αυτό λέει ότι του αρέσει να πολεμάει!\n"
	.string "Αλλά αν αποκτήσει αρκετά βαβά,\l"
	.string "θα γίνει πονηρό!$"

BattleFrontier_Lounge5_Text_NatureGirlHasty::
	.string "Χμχμ…\p"
	.string "Αυτό λέει ότι του αρέσει να πολεμάει!\n"
	.string "Θα παλέψει ακόμα κι αν έχει πολλά\l"
	.string "βαβά!$"

BattleFrontier_Lounge5_Text_NatureGirlSerious::
	.string "Χμχμ…\p"
	.string "Λέει ότι του αρέσει να είναι πονηρό!\n"
	.string "Λέει ότι του αρέσει να είναι πονηρό\l"
	.string "ακόμα κι αν έχει πολλά βαβά!$"

BattleFrontier_Lounge5_Text_NatureGirlJolly::
	.string "Χμχμ…\p"
	.string "Λέει ότι του αρέσει να είναι πονηρό!\n"
	.string "Αλλά αν αποκτήσει αρκετά βαβά,\l"
	.string "θα ανησυχήσει για τον εαυτό του!$"

BattleFrontier_Lounge5_Text_NatureGirlModest::
	.string "Χμχμ…\p"
	.string "Αυτό λέει ότι προσέχει τον εαυτό του!\n"
	.string "Ανησυχεί για τον εαυτό του είτε\l"
	.string "έχει πολλά βαβά είτε όχι!$"

BattleFrontier_Lounge5_Text_NatureGirlMild::
	.string "Χμχμ…\p"
	.string "Αυτό λέει ότι προσέχει τον εαυτό του!\n"
	.string "Αλλά αν αποκτήσει αρκετά βαβά,\l"
	.string "θα γίνει πονηρό!$"

BattleFrontier_Lounge5_Text_NatureGirlBashful::
	.string "Χμχμ…\p"
	.string "Αυτό λέει ότι προσέχει τον εαυτό του!\n"
	.string "Ανησυχεί για τον εαυτό του ακόμα κι\l"
	.string "αν έχει πολλά βαβά!$"

BattleFrontier_Lounge5_Text_NatureGirlRash::
	.string "Χμχμ…\p"
	.string "Λέει ότι του αρέσει να είναι πονηρό!\n"
	.string "Λέει ότι του αρέσει να είναι πονηρό\l"
	.string "ακόμα κι αν έχει πολλά βαβά!$"

BattleFrontier_Lounge5_Text_NatureGirlCalm::
	.string "Χμχμ…\p"
	.string "Αυτό λέει ότι προσέχει τον εαυτό του!\n"
	.string "Ανησυχεί για τον εαυτό του ακόμα κι\l"
	.string "αν έχει πολλά βαβά!$"

BattleFrontier_Lounge5_Text_NatureGirlGentle::
	.string "Χμχμ…\p"
	.string "Αυτό λέει ότι προσέχει τον εαυτό του!\n"
	.string "Αλλά αν αποκτήσει αρκετά βαβά,\l"
	.string "θα ανταποδώσει το χτύπημα!$"

BattleFrontier_Lounge5_Text_NatureGirlSassy::
	.string "Χμχμ…\p"
	.string "Αυτό λέει ότι του αρέσει να πολεμάει!\n"
	.string "Αλλά αν αποκτήσει αρκετά βαβά,\l"
	.string "θα γίνει πονηρό!$"

BattleFrontier_Lounge5_Text_NatureGirlCareful::
	.string "Χμχμ…\p"
	.string "Αυτό λέει ότι προσέχει τον εαυτό του!\n"
	.string "Αλλά αν αποκτήσει αρκετά βαβά,\l"
	.string "θα γίνει πονηρό!$"

BattleFrontier_Lounge5_Text_NatureGirlEgg::
	.string "Αυτό είναι χαζό! Ένα EGG κοιμάται!\n"
	.string "Δεν μπορώ να του μιλήσω!$"

BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon::
	.string "Τι γοητευτικό!\n"
	.string "Αυτή η μικρή κυρία ισχυρίζεται ότι \l"
	.string "μπορεί να καταλάβει τα POKéMON!$"

BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound::
	.string "Έχω την αίσθηση ότι το κοριτσάκι\n"
	.string "λέει κάτι σοφό.$"

BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot::
	.string "Ξέρω κάτι!\p"
	.string "Αυτό το κοριτσάκι παίζει πολύ \n"
	.string "στο κόκκινο σπίτι!$"

