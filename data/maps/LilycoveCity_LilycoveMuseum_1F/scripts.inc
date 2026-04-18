.set LOCALID_CURATOR, 2
.set LOCALID_ARTIST_2, 8

LilycoveCity_LilycoveMuseum_1F_MapScripts::
	.byte 0

LilycoveCity_LilycoveMuseum_1F_EventScript_Greeter::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_WelcomeToLilycoveMuseum, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Curator::
	lockall
	applymovement LOCALID_CURATOR, Common_Movement_FacePlayer
	message LilycoveCity_LilycoveMuseum_1F_Text_ImCuratorHaveYouViewedOurPaintings
	waitmessage
	multichoice 20, 8, MULTI_VIEWED_PAINTINGS, TRUE
	goto_if_eq VAR_RESULT, 0, LilycoveCity_LilycoveMuseum_1F_EventScript_SawPaintings
	goto_if_eq VAR_RESULT, 1, LilycoveCity_LilycoveMuseum_1F_EventScript_NotYet
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_NotYet::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_NotDisturbYouTakeYourTime, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_SawPaintings::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_HaveYouAnInterestInPaintings, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LilycoveCity_LilycoveMuseum_1F_EventScript_NotInterested
	goto_if_eq VAR_RESULT, YES, LilycoveCity_LilycoveMuseum_1F_EventScript_InterestedInPaintings
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_NotInterested::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_HonoredYoudVisitInSpiteOfThat, MSGBOX_SIGN
	releaseall
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_InterestedInPaintings::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ExcellentCanYouComeWithMe, MSGBOX_SIGN
	applymovement LOCALID_CURATOR, LilycoveCity_LilycoveMuseum_1F_Movement_CuratorEnterStairs
	waitmovement 0
	removeobject LOCALID_CURATOR
	switch VAR_FACING
	case DIR_NORTH, LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorNorth
	case DIR_WEST, LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorWest
	case DIR_EAST, LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorEast
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorNorth::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorNorth
	waitmovement 0
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_2F, 11, 8
	waitstate
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorWest::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorWest
	waitmovement 0
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_2F, 11, 8
	waitstate
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorEast::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorEast
	waitmovement 0
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_2F, 11, 8
	waitstate
	end

LilycoveCity_LilycoveMuseum_1F_Movement_CuratorEnterStairs:
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorWest:
	walk_left
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorEast:
	walk_right
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorNorth:
	walk_up
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_EventScript_OldPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_VeryOldPainting, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FantasyPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_OddLandscapeFantasticScenery, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_WomanPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBeautifulWoman, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_LegendaryPokemonPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfLegendaryPokemon, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_GrassPokemonPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfGrassPokemon, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_BerryPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBerries, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_EventScript_BirdSculpture::
	msgbox LilycoveCity_LilycoveMuseum_Text_BirdPokemonSculptureReplica, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_PokeBallSculpture::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_BigPokeBallCarvedFromStone, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_StoneTablet::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_StoneTabletWithAncientText, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_SchoolKidM::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_MustntForgetLoveForFineArts, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Artist1::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ThisMuseumIsInspiration, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_NinjaBoy::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ThisLadyIsPretty, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Woman1::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ThisPokemonIsAdorable, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Woman2::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_HeardMuseumGotNewPaintings, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_PsychicM::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_CuratorHasBeenCheerful, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Artist2::
	lock
	faceplayer
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_AimToSeeGreatPaintings, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARTIST_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FatMan::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_MuseumTouristDestination, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_Text_WelcomeToLilycoveMuseum:
	.string "Καλωσήρθατε στο LILYCOVE MUSEUM.\p"
	.string "Παρακαλώ αφιερώστε χρόνο για \n"
	.string "να απολαύσετε τη συλλογή μας από \l"
	.string "φανταστικά έργα τέχνης με POKéMON.$"

LilycoveCity_LilycoveMuseum_1F_Text_ImCuratorHaveYouViewedOurPaintings:
	.string "Είμαι ο CURATOR αυτού του MUSEUM \n"
	.string "της Καλών Τεχνών.\p"
	.string "Είναι ενθαρρυντικό να βλέπεις \n"
	.string "κάποιον τόσο νέο όσο εσύ εδώ.\p"
	.string "Έχεις δει ήδη τη συλλογή μας \n"
	.string "από πίνακες;$"

LilycoveCity_LilycoveMuseum_1F_Text_NotDisturbYouTakeYourTime:
	.string "Α, τότε ας μην σε ενοχλώ.\n"
	.string "Παρακαλώ, πάρε το χρόνο σου.$"

LilycoveCity_LilycoveMuseum_1F_Text_HaveYouAnInterestInPaintings:
	.string "Ω; Πιστεύω ότι φαίνεσαι να είσαι\n"
	.string "ένας POKéMON TRAINER.\p"
	.string "Έχεις ενδιαφέρον και για τους\n"
	.string "πίνακες;$"

LilycoveCity_LilycoveMuseum_1F_Text_HonoredYoudVisitInSpiteOfThat:
	.string "Καταλαβαίνω…\p"
	.string "Με τιμά που μας επισκέπτεσαι\n"
	.string "παρ' όλα αυτά.$"

LilycoveCity_LilycoveMuseum_1F_Text_ExcellentCanYouComeWithMe:
	.string "Α, εξαιρετικά!\n"
	.string "Σου αρέσουν οι πίνακες!\p"
	.string "Τότε, μπορώ να σου ζητήσω να \n"
	.string "έρθεις μαζί μου;$"

LilycoveCity_LilycoveMuseum_1F_Text_VeryOldPainting:
	.string "Είναι ένας πολύ παλιός πίνακας.\n"
	.string "Το χρώμα ξεφλουδίζει εδώ κι εκεί.$"

LilycoveCity_LilycoveMuseum_1F_Text_OddLandscapeFantasticScenery:
	.string "Είναι ένα παράξενο τοπίο με \n"
	.string "αλλόκοτα και φανταστικά σκηνικά.$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBeautifulWoman:
	.string "Είναι ένας πίνακας μιας όμορφης, \n"
	.string "χαμογελαστής γυναίκας με ένα \l"
	.string "POKéMON στην αγκαλιά της.$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfLegendaryPokemon:
	.string "Είναι ένας πίνακας ενός θρυλικού \n"
	.string "POKéMON από τα παλιά χρόνια.\p"
	.string "Ο καλλιτέχνης το ζωγράφισε από \n"
	.string "φαντασία.$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfGrassPokemon:
	.string "Είναι ένας πίνακας με GRASS \n"
	.string "POKéMON που λικνίζονται.\p"
	.string "Φαίνεται να απολαμβάνουν το απαλό \n"
	.string "χάδι του ανέμου.$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBerries:
	.string "Είναι ένας λαχταριστός πίνακας \n"
	.string "με BERRIES.\p"
	.string "Αυτός ο πίνακας θα μπορούσε να \n"
	.string "σε κάνει να πεινάσεις!$"

LilycoveCity_LilycoveMuseum_Text_BirdPokemonSculptureReplica:
	.string "Είναι αντίγραφο ενός διάσημου \n"
	.string "γλυπτού.\p"
	.string "Απεικονίζει ένα αρχαίο BIRD POKéMON.$"

LilycoveCity_LilycoveMuseum_1F_Text_BigPokeBallCarvedFromStone:
	.string "Είναι μια μεγάλη POKé BALL \n"
	.string "σκαλισμένη από μαύρη πέτρα.\p"
	.string "Φαίνεται να χρησιμοποιούνταν σε \n"
	.string "φεστιβάλ στα παλιά χρόνια.$"

LilycoveCity_LilycoveMuseum_1F_Text_StoneTabletWithAncientText:
	.string "Είναι μια τεράστια πέτρινη πλάκα \n"
	.string "γραμμένη με POKéMON και \l"
	.string "πυκνό κείμενο\l"
	.string "σε μια αρχαία, δυσανάγνωστη γλώσσα.$"

LilycoveCity_LilycoveMuseum_1F_Text_WorksOfMagnificence:
	.string "Χμμμ…\n"
	.string "Τι έργα μεγάλου μεγαλείου…$"

LilycoveCity_LilycoveMuseum_1F_Text_MustntForgetLoveForFineArts:
	.string "Οι μάχες με POKéMON είναι διασκέδαση,\n"
	.string "στο εγγυώμαι αυτό.\p"
	.string "Αλλά δεν πρέπει κανείς να ξεχνά \n"
	.string "την αγάπη μας για τις τέχνες.$"

LilycoveCity_LilycoveMuseum_1F_Text_ThisMuseumIsInspiration:
	.string "Αυτό το ART MUSEUM… Λοιπόν, μπορείς \n"
	.string "να δεις πολλούς πίνακες.\p"
	.string "Και ο CURATOR είναι ένας υπέροχος \n"
	.string "άνθρωπος.\p"
	.string "Ανάμεσα σε καλλιτέχνες σαν εμένα, \n"
	.string "αυτό το MUSEUM είναι μια έμπνευση.$"

LilycoveCity_LilycoveMuseum_1F_Text_ThisLadyIsPretty:
	.string "Αυτή η κυρία είναι όμορφη!\n"
	.string "Μοιάζει με τη μαμά!$"

LilycoveCity_LilycoveMuseum_1F_Text_ThisPokemonIsAdorable:
	.string "Αυτό το POKéMON είναι αξιολάτρευτο!\n"
	.string "Ακριβώς σαν το μικρό μας αγόρι!$"

LilycoveCity_LilycoveMuseum_1F_Text_HeardMuseumGotNewPaintings:
	.string "Είχα ακούσει ότι αυτό το ART MUSEUM\n"
	.string "πήρε κάποιους νέους πίνακες.\p"
	.string "Οπότε, φυσικά βιάστηκα να έρθω.\p"
	.string "Οι νέοι πίνακες είναι πάνω στον \n"
	.string "δεύτερο όροφο;$"

LilycoveCity_LilycoveMuseum_1F_Text_CuratorHasBeenCheerful:
	.string "Τελευταία, ο CURATOR είναι \n"
	.string "ασυνήθιστα χαρούμενος.\p"
	.string "Βάζω στοίχημα ότι του συνέβη κάτι \n"
	.string "καλό. Σίγουρα.$"

LilycoveCity_LilycoveMuseum_1F_Text_AimToSeeGreatPaintings:
	.string "Σκοπεύω να δω πολλούς σπουδαίους \n"
	.string "πίνακες εδώ και να μάθω από αυτούς.\p"
	.string "Έχω αυτό το όνειρο κάποια μέρα\n"
	.string "να εκθέσω εδώ τα έργα τέχνης μου.$"

LilycoveCity_LilycoveMuseum_1F_Text_MuseumTouristDestination:
	.string "Το ART MUSEUM έχει γίνει αγαπημένος \n"
	.string "τουριστικός προορισμός.\p"
	.string "Είναι υπέροχο για το LILYCOVE…\n"
	.string "Όχι, υπέροχο για την περιοχή HOENN!\p"
	.string "Άκουσα ότι ένας TRAINER \n"
	.string "αγόρασε όλους τους πίνακες επάνω.$"

