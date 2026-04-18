LilycoveCity_CoveLilyMotel_2F_MapScripts::
	.byte 0

LilycoveCity_CoveLilyMotel_2F_EventScript_GameDesigner::
	lock
	faceplayer
	call_if_unset FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex
	call_if_set FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	specialvar VAR_RESULT, HasAllHoennMons
	goto_if_eq VAR_RESULT, TRUE, LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex, MSGBOX_DEFAULT
	return

LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare::
	setflag FLAG_TEMP_2
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	goto LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma::
	message LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	special Special_ShowDiploma
	waitstate
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Programmer::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GraphicArtist::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_FatMan::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Woman::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GameBoyKid::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_IN_LILYCOVE, LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_IN_LILYCOVE
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy, MSGBOX_DEFAULT
	release
	end

LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex:
	.string "Είμαι ο GAME DESIGNER.\p"
	.string "Α, αλήθεια;\n"
	.string "Δουλεύεις σε ένα POKéDEX;\p"
	.string "Είναι δύσκολο να προσπαθείς \n"
	.string "να το ολοκληρώσεις, αλλά μην \l"
	.string "τα παρατάς.\p"
	.string "Αν το ολοκληρώσεις, σε παρακαλώ \n"
	.string "έλα να μου το δείξεις.$"

LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis:
	.string "Ουάου! Αυτό είναι φοβερό!\n"
	.string "Ναι, είναι εντελώς φοβερό!\p"
	.string "Αυτό το POKéDEX είναι εντελώς γεμάτο!\n"
	.string "Πραγματικά πρέπει να αγαπάς τα POKéMON!\p"
	.string "Είμαι τόσο εντυπωσιασμένος!\p"
	.string "Άσε με να σου δώσω κάτι σε \n"
	.string "αναγνώριση του κατορθώματός σου!$"

LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer:
	.string "Εμένα; Μιλάς σε εμένα;\n"
	.string "Είμαι ο PROGRAMMER.\p"
	.string "Αναρωτιέμαι πώς είναι τα SLOTS\n"
	.string "εδώ.$"

LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist:
	.string "Είμαι ο GRAPHIC ARTIST! Δεν είναι\n"
	.string "ενδιαφέροντα τα POKéMON του HOENN;$"

LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute:
	.string "Τα κορίτσια TUBERS, είναι \n"
	.string "χαριτωμένα, ε;\l"
	.string "Το να παλεύεις εναντίον \l"
	.string "μιας χαριτωμένης TUBER…\p"
	.string "Ουπ, είναι τόσο φοβερό!\p"
	.string "Και οι TWINS! Δεν είναι \n"
	.string "χαριτωμένες;\l"
	.string "Μια 2-on-2 μάχη με TWINS…\p"
	.string "Ουπ, είναι αφόρητα διασκεδαστικό!$"

LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart:
	.string "Η θαλασσινή αύρα γαργαλάει την\n"
	.string "καρδιά μου. Είναι υπέροχα εδώ!$"

LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy:
	.string "Ποτέ δεν ξέρεις πότε και πού οι\n"
	.string "άνθρωποι θα σε προκαλέσουν.\p"
	.string "Γι' αυτό ποτέ δεν φεύγω από το σπίτι\n"
	.string "χωρίς το GAME BOY ADVANCE μου.$"

LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles:
	.string "SCOTT: … … … … …\n"
	.string "… … … … … Ζζζ…\p"
	.string "… … … … … Ε;!\n"
	.string "Α, συγγνώμη, συγγνώμη! Ονειρευόμουν!\p"
	.string "Ήρθα να δω αυτό το πράγμα με τα \n"
	.string "POKéMON CONTEST.\p"
	.string "Οφείλω να παραδεχτώ,\n"
	.string "φαίνεται αρκετά διασκεδαστικό, αλλά…\p"
	.string "Να με θεωρείς πουρίστα--προτιμώ\n"
	.string "τις μάχες και τους \l"
	.string "σκληρούς TRAINERS.\p"
	.string "Αλλά αυτός είμαι εγώ.\p"
	.string "{PLAYER}{KUN}, ελπίζω να \n"
	.string "απολαύσεις τα πάντα, \l"
	.string "όπως τα GYMS, CONTESTS, \l"
	.string "BATTLE TENT, όλη τη δουλειά!$"

LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy:
	.string "SCOTT: Νομίζω πως θέλει στρατηγική\n"
	.string "για να νικήσεις ένα CONTEST.\p"
	.string "Η επινόηση CONTEST στρατηγικών \n"
	.string "είναι ένας τρόπος για να γίνεις  \l"
	.string "καλύτερος TRAINER, θα έλεγα.$"

