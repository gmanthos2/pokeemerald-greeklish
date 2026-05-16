#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_message.h"
#include "battle_setup.h"
#include "battle_tower.h"
#include "data.h"
#include "event_data.h"
#include "frontier_util.h"
#include "graphics.h"
#include "international_string_util.h"
#include "item.h"
#include "link.h"
#include "menu.h"
#include "palette.h"
#include "recorded_battle.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"
#include "trainer_hill.h"
#include "window.h"
#include "constants/battle_dome.h"
#include "constants/battle_string_ids.h"
#include "constants/frontier_util.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/trainers.h"
#include "constants/trainer_hill.h"
#include "constants/weather.h"

struct BattleWindowText
{
    u8 fillValue;
    u8 fontId;
    u8 x;
    u8 y;
    u8 letterSpacing;
    u8 lineSpacing;
    u8 speed;
    u8 fgColor;
    u8 bgColor;
    u8 shadowColor;
};

static void ChooseMoveUsedParticle(u8 *textPtr);
static void ChooseTypeOfMoveUsedString(u8 *dst);
static void ExpandBattleTextBuffPlaceholders(const u8 *src, u8 *dst);

static EWRAM_DATA u8 sBattlerAbilities[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA struct BattleMsgData *gBattleMsgDataPtr = NULL;

// todo: make some of those names less vague: attacker/target vs pkmn, etc.

static const u8 sText_Trainer1LoseText[] = _("{B_TRAINER1_LOSE_TEXT}");
static const u8 sText_PkmnGainedEXP[] = _("Το {B_BUFF1} πήρε{B_BUFF2}\n{B_BUFF3} EXP. Points!\p");
static const u8 sText_EmptyString4[] = _("");
static const u8 sText_ABoosted[] = _(" ενισχυμένα");
static const u8 sText_PkmnGrewToLv[] = _("Το {B_BUFF1} έφτασε στο\nLV. {B_BUFF2}!{WAIT_SE}\p");
static const u8 sText_PkmnLearnedMove[] = _("Το {B_BUFF1} έμαθε\nτο {B_BUFF2}!{WAIT_SE}\p");
static const u8 sText_TryToLearnMove1[] = _("Το {B_BUFF1} προσπαθεί να\nμάθει το {B_BUFF2}.\p");
static const u8 sText_TryToLearnMove2[] = _("Αλλά, το {B_BUFF1} δεν μαθαίνει\nπάνω από 4 κινήσεις.\p");
static const u8 sText_TryToLearnMove3[] = _("Να σβηστεί μια κίνηση για να\nκάνει χώρο για το {B_BUFF2};");
static const u8 sText_PkmnForgotMove[] = _("Το {B_BUFF1} ξέχασε\nτο {B_BUFF2}.\p");
static const u8 sText_StopLearningMove[] = _("{PAUSE 32}Να σταματήσει η\nεκμάθηση του {B_BUFF2};");
static const u8 sText_DidNotLearnMove[] = _("Το {B_BUFF1} δεν έμαθε\nτο {B_BUFF2}.\p");
static const u8 sText_UseNextPkmn[] = _("Χρήση του επόμενου POKéMON;");
static const u8 sText_AttackMissed[] = _("Η επίθεση του {B_ATK_NAME_WITH_PREFIX}\nαστόχησε!");
static const u8 sText_PkmnProtectedItself[] = _("Το {B_DEF_NAME_WITH_PREFIX}\nπροστατεύτηκε!");
static const u8 sText_AvoidedDamage[] = _("Το {B_DEF_NAME_WITH_PREFIX} απέφυγε\nζημιά με το {B_DEF_ABILITY}!");
static const u8 sText_PkmnMakesGroundMiss[] = _("Το {B_DEF_NAME_WITH_PREFIX} αποφεύγει GROUND\nεπιθέσεις με το {B_DEF_ABILITY}!");
static const u8 sText_PkmnAvoidedAttack[] = _("Το {B_DEF_NAME_WITH_PREFIX} απέφυγε\nτην επίθεση!");
static const u8 sText_ItDoesntAffect[] = _("Δεν επηρεάζει καθόλου\nτο {B_DEF_NAME_WITH_PREFIX}…");
static const u8 sText_AttackerFainted[] = _("Το {B_ATK_NAME_WITH_PREFIX}\nλιποθύμησε!\p");
static const u8 sText_TargetFainted[] = _("Το {B_DEF_NAME_WITH_PREFIX}\nλιποθύμησε!\p");
static const u8 sText_PlayerGotMoney[] = _("Πήρες ¥{B_BUFF1}\nγια τη νίκη σου!\p");
static const u8 sText_PlayerWhiteout[] = _("Δεν έχεις POKéMON για μάχη!\p");
static const u8 sText_PlayerWhiteout2[] = _("Έχασες!{PAUSE_UNTIL_PRESS}");
static const u8 sText_PreventsEscape[] = _("Το {B_SCR_ACTIVE_NAME_WITH_PREFIX} εμποδίζει τη\nφυγή με το {B_SCR_ACTIVE_ABILITY}!\p");
static const u8 sText_CantEscape2[] = _("Δεν μπορείς να ξεφύγεις!\p");
static const u8 sText_AttackerCantEscape[] = _("Το {B_ATK_NAME_WITH_PREFIX} δεν μπορεί να φύγει!");
static const u8 sText_HitXTimes[] = _("Χτύπησε {B_BUFF1} φορά(ές)!");
static const u8 sText_PkmnFellAsleep[] = _("Το {B_EFF_NAME_WITH_PREFIX}\nαποκοιμήθηκε!");
static const u8 sText_PkmnMadeSleep[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nκοίμισε το {B_EFF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnAlreadyAsleep[] = _("Το {B_DEF_NAME_WITH_PREFIX} ήδη\nκοιμάται!");
static const u8 sText_PkmnAlreadyAsleep2[] = _("Το {B_ATK_NAME_WITH_PREFIX} ήδη\nκοιμάται!");
static const u8 sText_PkmnWasntAffected[] = _("Το {B_DEF_NAME_WITH_PREFIX}\nδεν επηρεάστηκε!");
static const u8 sText_PkmnWasPoisoned[] = _("Το {B_EFF_NAME_WITH_PREFIX}\nδηλητηριάστηκε!");
static const u8 sText_PkmnPoisonedBy[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nδηλητηρίασε το {B_EFF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnHurtByPoison[] = _("Το {B_ATK_NAME_WITH_PREFIX} χτυπιέται\nαπό το δηλητήριο!");
static const u8 sText_PkmnAlreadyPoisoned[] = _("Το {B_DEF_NAME_WITH_PREFIX} είναι ήδη\nδηλητηριασμένο.");
static const u8 sText_PkmnBadlyPoisoned[] = _("Το {B_EFF_NAME_WITH_PREFIX} είναι βαριά\nδηλητηριασμένο!");
static const u8 sText_PkmnEnergyDrained[] = _("Απορροφήθηκε ενέργεια από\nτο {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnWasBurned[] = _("Το {B_EFF_NAME_WITH_PREFIX} κάηκε!");
static const u8 sText_PkmnBurnedBy[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nέκαψε το {B_EFF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnHurtByBurn[] = _("Το {B_ATK_NAME_WITH_PREFIX} χτυπιέται\nαπό το έγκαυμά του!");
static const u8 sText_PkmnAlreadyHasBurn[] = _("Το {B_DEF_NAME_WITH_PREFIX} έχει ήδη\nκάποιο έγκαυμα.");
static const u8 sText_PkmnWasFrozen[] = _("Το {B_EFF_NAME_WITH_PREFIX}\nπάγωσε εντελώς!");
static const u8 sText_PkmnFrozenBy[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nπάγωσε το {B_EFF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnIsFrozen[] = _("Το {B_ATK_NAME_WITH_PREFIX} είναι\nεντελώς παγωμένο!");
static const u8 sText_PkmnWasDefrosted[] = _("Το {B_DEF_NAME_WITH_PREFIX}\nξεπάγωσε!");
static const u8 sText_PkmnWasDefrosted2[] = _("Το {B_ATK_NAME_WITH_PREFIX}\nξεπάγωσε!");
static const u8 sText_PkmnWasDefrostedBy[] = _("Το {B_ATK_NAME_WITH_PREFIX} ξεπάγωσε\nαπό το {B_CURRENT_MOVE}!");
static const u8 sText_PkmnWasParalyzed[] = _("Το {B_EFF_NAME_WITH_PREFIX} παρέλυσε!\nΊσως να μην μπορεί να κινηθεί!");
static const u8 sText_PkmnWasParalyzedBy[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nπαρέλυσε το {B_EFF_NAME_WITH_PREFIX}!\lΊσως να μην μπορεί να κινηθεί!");
static const u8 sText_PkmnIsParalyzed[] = _("Το {B_ATK_NAME_WITH_PREFIX} παρέλυσε!\nΔεν μπορεί να κινηθεί!");
static const u8 sText_PkmnIsAlreadyParalyzed[] = _("Το {B_DEF_NAME_WITH_PREFIX} έχει\nήδη παραλύσει!");
static const u8 sText_PkmnHealedParalysis[] = _("Η παράλυση του {B_DEF_NAME_WITH_PREFIX}\nθεραπεύτηκε!");
static const u8 sText_PkmnDreamEaten[] = _("Το όνειρο του {B_DEF_NAME_WITH_PREFIX}\nφαγώθηκε!");
static const u8 sText_StatsWontIncrease[] = _("Το {B_BUFF1} του {B_ATK_NAME_WITH_PREFIX}\nδεν πάει πιο ψηλά!");
static const u8 sText_StatsWontDecrease[] = _("Το {B_BUFF1} του {B_DEF_NAME_WITH_PREFIX}\nδεν πάει πιο χαμηλά!");
static const u8 sText_TeamStoppedWorking[] = _("Το {B_BUFF1} της ομάδας σου\nσταμάτησε να δουλεύει!");
static const u8 sText_FoeStoppedWorking[] = _("Το {B_BUFF1} του αντιπάλου\nσταμάτησε να δουλεύει!");
static const u8 sText_PkmnIsConfused[] = _("Το {B_ATK_NAME_WITH_PREFIX} είναι σε\nσύγχυση!");
static const u8 sText_PkmnHealedConfusion[] = _("Το {B_ATK_NAME_WITH_PREFIX} βγήκε\nαπό τη σύγχυσή του!");
static const u8 sText_PkmnWasConfused[] = _("Το {B_EFF_NAME_WITH_PREFIX} μπήκε\nσε σύγχυση!");
static const u8 sText_PkmnAlreadyConfused[] = _("Το {B_DEF_NAME_WITH_PREFIX} έχει ήδη\nμπει σε σύγχυση!");
static const u8 sText_PkmnFellInLove[] = _("Το {B_DEF_NAME_WITH_PREFIX}\nερωτεύτηκε!");
static const u8 sText_PkmnInLove[] = _("Το {B_ATK_NAME_WITH_PREFIX} ερωτεύτηκε\nτο {B_SCR_ACTIVE_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnImmobilizedByLove[] = _("Το {B_ATK_NAME_WITH_PREFIX} ακινητοποιήθηκε\nαπό τον έρωτα!");
static const u8 sText_PkmnBlownAway[] = _("Το {B_DEF_NAME_WITH_PREFIX}\nπαρασύρθηκε μακριά!");
static const u8 sText_PkmnChangedType[] = _("Το {B_ATK_NAME_WITH_PREFIX} πήρε τη\nμορφή του τύπου {B_BUFF1}!");
static const u8 sText_PkmnFlinched[] = _("Το {B_ATK_NAME_WITH_PREFIX} δείλιασε!");
static const u8 sText_PkmnRegainedHealth[] = _("Το {B_DEF_NAME_WITH_PREFIX} ανέκτησε\nυγιή κατάσταση!");
static const u8 sText_PkmnHPFull[] = _("Τα HP του {B_DEF_NAME_WITH_PREFIX}\nείναι γεμάτα!");
static const u8 sText_PkmnRaisedSpDef[] = _("Το {B_CURRENT_MOVE} του {B_ATK_PREFIX2}\nανέβασε τη SP. DEF!");
static const u8 sText_PkmnRaisedSpDefALittle[] = _("Το {B_CURRENT_MOVE} του {B_ATK_PREFIX2}\nανέβασε τη SP. DEF λίγο!");
static const u8 sText_PkmnRaisedDef[] = _("Το {B_CURRENT_MOVE} του {B_ATK_PREFIX2}\nανέβασε τη DEFENSE!");
static const u8 sText_PkmnRaisedDefALittle[] = _("Το {B_CURRENT_MOVE} του {B_ATK_PREFIX2}\nανέβασε τη DEFENSE λίγο!");
static const u8 sText_PkmnCoveredByVeil[] = _("Η ομάδα του {B_ATK_PREFIX2} καλύφθηκε\nμε ένα πέπλο!");
static const u8 sText_PkmnUsedSafeguard[] = _("Η ομάδα του {B_DEF_NAME_WITH_PREFIX} προστατεύεται\nαπό το SAFEGUARD!");
static const u8 sText_PkmnSafeguardExpired[] = _("Η ομάδα του {B_ATK_PREFIX3} δεν προστατεύεται\nπια από το SAFEGUARD!");
static const u8 sText_PkmnWentToSleep[] = _("Το {B_ATK_NAME_WITH_PREFIX} πήγε\nγια ύπνο!");
static const u8 sText_PkmnSleptHealthy[] = _("Το {B_ATK_NAME_WITH_PREFIX} κοιμήθηκε\nκαι έγινε υγιές!");
static const u8 sText_PkmnWhippedWhirlwind[] = _("Το {B_ATK_NAME_WITH_PREFIX} δημιούργησε\nέναν ανεμοστρόβιλο!");
static const u8 sText_PkmnTookSunlight[] = _("Το {B_ATK_NAME_WITH_PREFIX} απορρόφησε\nτο φως του ήλιου!");
static const u8 sText_PkmnLoweredHead[] = _("Το {B_ATK_NAME_WITH_PREFIX} χαμήλωσε\nτο κεφάλι του!");
static const u8 sText_PkmnIsGlowing[] = _("Το {B_ATK_NAME_WITH_PREFIX} λάμπει!");
static const u8 sText_PkmnFlewHigh[] = _("Το {B_ATK_NAME_WITH_PREFIX} πέταξε\nψηλά!");
static const u8 sText_PkmnDugHole[] = _("Το {B_ATK_NAME_WITH_PREFIX} έσκαψε μια τρύπα!");
static const u8 sText_PkmnHidUnderwater[] = _("Το {B_ATK_NAME_WITH_PREFIX} κρύφτηκε\nκάτω από το νερό!");
static const u8 sText_PkmnSprangUp[] = _("Το {B_ATK_NAME_WITH_PREFIX} πετάχτηκε πάνω!");
static const u8 sText_PkmnSqueezedByBind[] = _("Το {B_DEF_NAME_WITH_PREFIX} σφίχτηκε από το\nBIND του {B_ATK_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnTrappedInVortex[] = _("Το {B_DEF_NAME_WITH_PREFIX} παγιδεύτηκε\nστη δίνη!");
static const u8 sText_PkmnTrappedBySandTomb[] = _("Το {B_DEF_NAME_WITH_PREFIX} παγιδεύτηκε\nαπό το SAND TOMB!");
static const u8 sText_PkmnWrappedBy[] = _("Το {B_DEF_NAME_WITH_PREFIX} τυλίχθηκε από\nτο {B_ATK_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnClamped[] = _("Το {B_ATK_NAME_WITH_PREFIX} έσφιξε\nτο {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnHurtBy[] = _("Το {B_ATK_NAME_WITH_PREFIX} χτυπιέται\nαπό το {B_BUFF1}!");
static const u8 sText_PkmnFreedFrom[] = _("Το {B_ATK_NAME_WITH_PREFIX} ελευθερώθηκε\nαπό το {B_BUFF1}!");
static const u8 sText_PkmnCrashed[] = _("Το {B_ATK_NAME_WITH_PREFIX} συνέχισε και\nέπεσε σε τοίχο!");
const u8 gText_PkmnShroudedInMist[] = _("Το {B_ATK_PREFIX2} τυλίχθηκε\nστο MIST!");
static const u8 sText_PkmnProtectedByMist[] = _("Το {B_SCR_ACTIVE_NAME_WITH_PREFIX} προστατεύεται\nαπό το MIST!");
const u8 gText_PkmnGettingPumped[] = _("Το {B_ATK_NAME_WITH_PREFIX} παίρνει\nδυνάμεις!");
static const u8 sText_PkmnHitWithRecoil[] = _("Το {B_ATK_NAME_WITH_PREFIX} χτυπιέται\nαπό την ανάκρουση!");
static const u8 sText_PkmnProtectedItself2[] = _("Το {B_ATK_NAME_WITH_PREFIX} προστάτεψε\nτον εαυτό του!");
static const u8 sText_PkmnBuffetedBySandstorm[] = _("Το {B_ATK_NAME_WITH_PREFIX} σφυροκοπείται\nαπό την αμμοθύελλα!");
static const u8 sText_PkmnPeltedByHail[] = _("Το {B_ATK_NAME_WITH_PREFIX} χτυπιέται\nαπό το HAIL!");
static const u8 sText_PkmnsXWoreOff[] = _("Το {B_BUFF1} του {B_ATK_PREFIX1}\nέληξε!");
static const u8 sText_PkmnSeeded[] = _("Το {B_DEF_NAME_WITH_PREFIX} μολύνθηκε με σπόρο!");
static const u8 sText_PkmnEvadedAttack[] = _("Το {B_DEF_NAME_WITH_PREFIX} απέφυγε\nτην επίθεση!");
static const u8 sText_PkmnSappedByLeechSeed[] = _("Η ενέργεια του {B_ATK_NAME_WITH_PREFIX} αδειάζει\nαπό το LEECH SEED!");
static const u8 sText_PkmnFastAsleep[] = _("Το {B_ATK_NAME_WITH_PREFIX} έχει\nκοιμηθεί βαθιά.");
static const u8 sText_PkmnWokeUp[] = _("Το {B_ATK_NAME_WITH_PREFIX} ξύπνησε!");
static const u8 sText_PkmnUproarKeptAwake[] = _("Όμως το UPROAR του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nτο κράτησε ξύπνιο!");
static const u8 sText_PkmnWokeUpInUproar[] = _("Το {B_ATK_NAME_WITH_PREFIX} ξύπνησε\nαπό το UPROAR!");
static const u8 sText_PkmnCausedUproar[] = _("Το {B_ATK_NAME_WITH_PREFIX} προκάλεσε\nένα UPROAR!");
static const u8 sText_PkmnMakingUproar[] = _("Το {B_ATK_NAME_WITH_PREFIX} κάνει\nUPROAR!");
static const u8 sText_PkmnCalmedDown[] = _("Το {B_ATK_NAME_WITH_PREFIX} ηρέμησε.");
static const u8 sText_PkmnCantSleepInUproar[] = _("Μα το {B_DEF_NAME_WITH_PREFIX} δεν μπορεί\nνα κοιμηθεί με το UPROAR!");
static const u8 sText_PkmnStockpiled[] = _("Το {B_ATK_NAME_WITH_PREFIX} έκανε STOCKPILE\n{B_BUFF1}!");
static const u8 sText_PkmnCantStockpile[] = _("Το {B_ATK_NAME_WITH_PREFIX} δεν μπορεί\nνα κάνει άλλο STOCKPILE!");
static const u8 sText_PkmnCantSleepInUproar2[] = _("Μα το {B_DEF_NAME_WITH_PREFIX} δεν μπορεί\nνα κοιμηθεί με το UPROAR!");
static const u8 sText_UproarKeptPkmnAwake[] = _("Αλλά το UPROAR κράτησε\nξύπνιο το {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnStayedAwakeUsing[] = _("Το {B_DEF_NAME_WITH_PREFIX} έμεινε ξύπνιο\nχάρη στο {B_DEF_ABILITY}!");
static const u8 sText_PkmnStoringEnergy[] = _("Το {B_ATK_NAME_WITH_PREFIX} συσσωρεύει\nενέργεια!");
static const u8 sText_PkmnUnleashedEnergy[] = _("Το {B_ATK_NAME_WITH_PREFIX} απελευθέρωσε\nενέργεια!");
static const u8 sText_PkmnFatigueConfusion[] = _("Το {B_ATK_NAME_WITH_PREFIX} μπήκε\nσε σύγχυση λόγω κούρασης!");
static const u8 sText_PlayerPickedUpMoney[] = _("Μάζεψες\n¥{B_BUFF1}!\p");
static const u8 sText_PkmnUnaffected[] = _("Το {B_DEF_NAME_WITH_PREFIX}\nδεν επηρεάζεται!");
static const u8 sText_PkmnTransformedInto[] = _("Το {B_ATK_NAME_WITH_PREFIX} μεταμορφώθηκε\nσε {B_BUFF1}!");
static const u8 sText_PkmnMadeSubstitute[] = _("Το {B_ATK_NAME_WITH_PREFIX} έφτιαξε\nένα SUBSTITUTE!");
static const u8 sText_PkmnHasSubstitute[] = _("Το {B_ATK_NAME_WITH_PREFIX} έχει ήδη\nένα SUBSTITUTE!");
static const u8 sText_SubstituteDamaged[] = _("Το SUBSTITUTE δέχτηκε ζημιά\nαντί για το {B_DEF_NAME_WITH_PREFIX}!\p");
static const u8 sText_PkmnSubstituteFaded[] = _("Το SUBSTITUTE του {B_DEF_NAME_WITH_PREFIX}\nεξαφανίστηκε!\p");
static const u8 sText_PkmnMustRecharge[] = _("Το {B_ATK_NAME_WITH_PREFIX} πρέπει\nνα επαναφορτιστεί!");
static const u8 sText_PkmnRageBuilding[] = _("Το RAGE του {B_DEF_NAME_WITH_PREFIX}\nμεγαλώνει!");
static const u8 sText_PkmnMoveWasDisabled[] = _("Το {B_BUFF1} του {B_DEF_NAME_WITH_PREFIX}\nαπενεργοποιήθηκε!");
static const u8 sText_PkmnMoveDisabledNoMore[] = _("Το {B_ATK_NAME_WITH_PREFIX} δεν είναι πια\nαπενεργοποιημένο!");
static const u8 sText_PkmnGotEncore[] = _("Το {B_DEF_NAME_WITH_PREFIX} δέχτηκε\nένα ENCORE!");
static const u8 sText_PkmnEncoreEnded[] = _("Το ENCORE του {B_ATK_NAME_WITH_PREFIX}\nέληξε!");
static const u8 sText_PkmnTookAim[] = _("Το {B_ATK_NAME_WITH_PREFIX} στόχευσε\nτο {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnSketchedMove[] = _("Το {B_ATK_NAME_WITH_PREFIX} έκανε SKETCH\nτο {B_BUFF1}!");
static const u8 sText_PkmnTryingToTakeFoe[] = _("Το {B_ATK_NAME_WITH_PREFIX} προσπαθεί να\nπάρει τον εχθρό μαζί του!");
static const u8 sText_PkmnTookFoe[] = _("Το {B_DEF_NAME_WITH_PREFIX} πήρε μαζί\nτου το {B_ATK_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnReducedPP[] = _("Μείωσε το {B_BUFF1} του\n{B_DEF_NAME_WITH_PREFIX} κατά {B_BUFF2}!");
static const u8 sText_PkmnStoleItem[] = _("Το {B_ATK_NAME_WITH_PREFIX} έκλεψε το\n{B_LAST_ITEM} του {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_TargetCantEscapeNow[] = _("Το {B_DEF_NAME_WITH_PREFIX} δεν μπορεί\nνα ξεφύγει τώρα!");
static const u8 sText_PkmnFellIntoNightmare[] = _("Το {B_DEF_NAME_WITH_PREFIX} έπεσε\nσε NIGHTMARE!");
static const u8 sText_PkmnLockedInNightmare[] = _("Το {B_ATK_NAME_WITH_PREFIX} κλειδώθηκε\nσε ένα NIGHTMARE!");
static const u8 sText_PkmnLaidCurse[] = _("Το {B_ATK_NAME_WITH_PREFIX} μείωσε τα HP του και\nέριξε CURSE στο {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnAfflictedByCurse[] = _("Το {B_ATK_NAME_WITH_PREFIX} ταλαιπωρείται\nαπό το CURSE!");
static const u8 sText_SpikesScattered[] = _("SPIKES σκορπίστηκαν γύρω από\nτην πλευρά του αντιπάλου!");
static const u8 sText_PkmnHurtBySpikes[] = _("Το {B_SCR_ACTIVE_NAME_WITH_PREFIX} χτυπιέται\nαπό τα SPIKES!");
static const u8 sText_PkmnIdentified[] = _("Το {B_ATK_NAME_WITH_PREFIX} ταυτοποίησε\nτο {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnPerishCountFell[] = _("Το PERISH count του {B_ATK_NAME_WITH_PREFIX}\nέπεσε στο {B_BUFF1}!");
static const u8 sText_PkmnBracedItself[] = _("Το {B_ATK_NAME_WITH_PREFIX} ετοιμάστηκε!");
static const u8 sText_PkmnEnduredHit[] = _("Το {B_DEF_NAME_WITH_PREFIX} ΑΝΤΕΞΕ\nτο χτύπημα!");
static const u8 sText_MagnitudeStrength[] = _("MAGNITUDE {B_BUFF1}!");
static const u8 sText_PkmnCutHPMaxedAttack[] = _("Το {B_ATK_NAME_WITH_PREFIX} μείωσε τα HP του\nκαι μεγιστοποίησε το ATTACK!");
static const u8 sText_PkmnCopiedStatChanges[] = _("Το {B_ATK_NAME_WITH_PREFIX} αντέγραψε τα stat\nτου {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnGotFree[] = _("Το {B_ATK_NAME_WITH_PREFIX} ελευθερώθηκε\nαπό το {B_BUFF1} του {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnShedLeechSeed[] = _("Το {B_ATK_NAME_WITH_PREFIX} αποτίναξε\nτο LEECH SEED!");
static const u8 sText_PkmnBlewAwaySpikes[] = _("Το {B_ATK_NAME_WITH_PREFIX} έδιωξε τα\nSPIKES!");
static const u8 sText_PkmnFledFromBattle[] = _("Το {B_ATK_NAME_WITH_PREFIX} έφυγε από\nτη μάχη!");
static const u8 sText_PkmnForesawAttack[] = _("Το {B_ATK_NAME_WITH_PREFIX} προέβλεψε\nμια επίθεση!");
static const u8 sText_PkmnTookAttack[] = _("Το {B_DEF_NAME_WITH_PREFIX} δέχτηκε την\nεπίθεση {B_BUFF1}!");
static const u8 sText_PkmnChoseXAsDestiny[] = _("Το {B_ATK_NAME_WITH_PREFIX} διάλεξε την\n{B_CURRENT_MOVE} ως πεπρωμένο!");
static const u8 sText_PkmnAttack[] = _("Επίθεση του {B_BUFF1}!");
static const u8 sText_PkmnCenterAttention[] = _("Το {B_ATK_NAME_WITH_PREFIX} έγινε το\nκέντρο της προσοχής!");
static const u8 sText_PkmnChargingPower[] = _("Το {B_ATK_NAME_WITH_PREFIX} άρχισε να\nφορτίζει δύναμη!");
static const u8 sText_NaturePowerTurnedInto[] = _("Το NATURE POWER έγινε\n{B_CURRENT_MOVE}!");
static const u8 sText_PkmnStatusNormal[] = _("Το status του {B_ATK_NAME_WITH_PREFIX}\nέγινε ξανά κανονικό!");
static const u8 sText_PkmnSubjectedToTorment[] = _("Το {B_DEF_NAME_WITH_PREFIX} υποβλήθηκε\nσε TORMENT!");
static const u8 sText_PkmnTighteningFocus[] = _("Το {B_ATK_NAME_WITH_PREFIX} συγκεντρώνει\nτη δύναμή του!");
static const u8 sText_PkmnFellForTaunt[] = _("Το {B_DEF_NAME_WITH_PREFIX} έπεσε\nστο TAUNT!");
static const u8 sText_PkmnReadyToHelp[] = _("Το {B_ATK_NAME_WITH_PREFIX} είναι έτοιμο να\nβοηθήσει το {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnSwitchedItems[] = _("Το {B_ATK_NAME_WITH_PREFIX} άλλαξε\nαντικείμενα με τον αντίπαλο!");
static const u8 sText_PkmnObtainedX[] = _("Το {B_ATK_NAME_WITH_PREFIX} πήρε\n{B_BUFF1}.");
static const u8 sText_PkmnObtainedX2[] = _("Το {B_DEF_NAME_WITH_PREFIX} πήρε\n{B_BUFF2}.");
static const u8 sText_PkmnObtainedXYObtainedZ[] = _("Το {B_ATK_NAME_WITH_PREFIX} πήρε\n{B_BUFF1}.\pΤο {B_DEF_NAME_WITH_PREFIX} πήρε\n{B_BUFF2}.");
static const u8 sText_PkmnCopiedFoe[] = _("Το {B_ATK_NAME_WITH_PREFIX} αντέγραψε το\n{B_DEF_ABILITY} του {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnMadeWish[] = _("Το {B_ATK_NAME_WITH_PREFIX} έκανε μια WISH!");
static const u8 sText_PkmnWishCameTrue[] = _("Η WISH του {B_BUFF1}\nέγινε πραγματικότητα!");
static const u8 sText_PkmnPlantedRoots[] = _("Το {B_ATK_NAME_WITH_PREFIX} φύτεψε ρίζες!");
static const u8 sText_PkmnAbsorbedNutrients[] = _("Το {B_ATK_NAME_WITH_PREFIX} απορρόφησε\nθρεπτικά συστατικά με τις ρίζες του!");
static const u8 sText_PkmnAnchoredItself[] = _("Το {B_DEF_NAME_WITH_PREFIX} αγκυρώθηκε\nμε τις ρίζες του!");
static const u8 sText_PkmnWasMadeDrowsy[] = _("Το {B_ATK_NAME_WITH_PREFIX} έκανε\nτο {B_DEF_NAME_WITH_PREFIX} νυσταγμένο!");
static const u8 sText_PkmnKnockedOff[] = _("Το {B_ATK_NAME_WITH_PREFIX} έριξε το\n{B_LAST_ITEM} του {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnSwappedAbilities[] = _("Το {B_ATK_NAME_WITH_PREFIX} άλλαξε ability\nμε τον αντίπαλό του!");
static const u8 sText_PkmnSealedOpponentMove[] = _("Το {B_ATK_NAME_WITH_PREFIX} σφράγισε τις\nκινήσεις του αντιπάλου!");
static const u8 sText_PkmnWantsGrudge[] = _("Το {B_ATK_NAME_WITH_PREFIX} θέλει ο\nαντίπαλος να κρατήσει GRUDGE!");
static const u8 sText_PkmnLostPPGrudge[] = _("Το {B_BUFF1} του {B_ATK_NAME_WITH_PREFIX} έχασε\nόλα του τα PP λόγω του GRUDGE!");
static const u8 sText_PkmnShroudedItself[] = _("Το {B_ATK_NAME_WITH_PREFIX} τυλίχθηκε\nμε {B_CURRENT_MOVE}!");
static const u8 sText_PkmnMoveBounced[] = _("Το {B_CURRENT_MOVE} του {B_ATK_NAME_WITH_PREFIX}\nανακλάστηκε από το MAGIC COAT!");
static const u8 sText_PkmnWaitsForTarget[] = _("Το {B_ATK_NAME_WITH_PREFIX} περιμένει ένα στόχο\nγια να κάνει κίνηση!");
static const u8 sText_PkmnSnatchedMove[] = _("Το {B_DEF_NAME_WITH_PREFIX} ΑΡΠΑΞΕ\nτην κίνηση του {B_SCR_ACTIVE_NAME_WITH_PREFIX}!");
static const u8 sText_ElectricityWeakened[] = _("Η δύναμη του Ηλεκτρισμού\nαποδυναμώθηκε!");
static const u8 sText_FireWeakened[] = _("Η δύναμη της Φωτιάς\nαποδυναμώθηκε!");
static const u8 sText_XFoundOneY[] = _("Το {B_ATK_NAME_WITH_PREFIX} βρήκε\nένα {B_LAST_ITEM}!");
static const u8 sText_SoothingAroma[] = _("Ένα καταπραυντικό άρωμα απλώθηκε\nστην περιοχή!");
static const u8 sText_ItemsCantBeUsedNow[] = _("Αντικείμενα δεν μπορούν να\nχρησιμοποιηθούν τώρα.{PAUSE 64}");
static const u8 sText_ForXCommaYZ[] = _("Για το {B_SCR_ACTIVE_NAME_WITH_PREFIX},\n{B_LAST_ITEM} {B_BUFF1}");
static const u8 sText_PkmnUsedXToGetPumped[] = _("Το {B_SCR_ACTIVE_NAME_WITH_PREFIX} χρησιμοποίησε\n{B_LAST_ITEM} για να πωρωθεί!");
static const u8 sText_PkmnLostFocus[] = _("Το {B_ATK_NAME_WITH_PREFIX} έχασε τη\nσυγκέντρωσή του και δεν κουνήθηκε!");
static const u8 sText_PkmnWasDraggedOut[] = _("Το {B_DEF_NAME_WITH_PREFIX} σύρθηκε\nέξω!\p");
static const u8 sText_TheWallShattered[] = _("Ο τοίχος θρυμματίστηκε!");
static const u8 sText_ButNoEffect[] = _("Αλλά δεν είχε αποτέλεσμα!");
static const u8 sText_PkmnHasNoMovesLeft[] = _("Το {B_ACTIVE_NAME_WITH_PREFIX} δεν έχει\nάλλες κινήσεις!\p");
static const u8 sText_PkmnMoveIsDisabled[] = _("Το {B_CURRENT_MOVE} του {B_ACTIVE_NAME_WITH_PREFIX}\nαπενεργοποιήθηκε!\p");
static const u8 sText_PkmnCantUseMoveTorment[] = _("Το {B_ACTIVE_NAME_WITH_PREFIX} δεν μπορεί την\nίδια κίνηση λόγω TORMENT!\p");
static const u8 sText_PkmnCantUseMoveTaunt[] = _("Το {B_ACTIVE_NAME_WITH_PREFIX} δεν μπορεί να\nκάνει {B_CURRENT_MOVE} μετά το TAUNT!\p");
static const u8 sText_PkmnCantUseMoveSealed[] = _("Το {B_ACTIVE_NAME_WITH_PREFIX} δεν μπορεί να κάνει\nτο σφραγισμένο {B_CURRENT_MOVE}!\p");
static const u8 sText_PkmnMadeItRain[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nέφερε βροχή!");
static const u8 sText_PkmnRaisedSpeed[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nανέβασε το SPEED του!");
static const u8 sText_PkmnProtectedBy[] = _("Το {B_DEF_NAME_WITH_PREFIX} προστατεύτηκε\nαπό το {B_DEF_ABILITY}!");
static const u8 sText_PkmnPreventsUsage[] = _("Το {B_DEF_ABILITY} του {B_DEF_NAME_WITH_PREFIX}\nεμποδίζει το {B_ATK_NAME_WITH_PREFIX}\lνα χρησιμοποιήσει το {B_CURRENT_MOVE}!");
static const u8 sText_PkmnRestoredHPUsing[] = _("Το {B_DEF_NAME_WITH_PREFIX} ανέκτησε HP\nμε το {B_DEF_ABILITY} του!");
static const u8 sText_PkmnsXMadeYUseless[] = _("Το {B_DEF_ABILITY} του {B_DEF_NAME_WITH_PREFIX}\nέκανε το {B_CURRENT_MOVE} άχρηστο!");
static const u8 sText_PkmnChangedTypeWith[] = _("Το {B_DEF_ABILITY} του {B_DEF_NAME_WITH_PREFIX}\nτο έκανε τύπου {B_BUFF1}!");
static const u8 sText_PkmnPreventsParalysisWith[] = _("Το {B_DEF_ABILITY} του {B_EFF_NAME_WITH_PREFIX}\nεμποδίζει την παράλυση!");
static const u8 sText_PkmnPreventsRomanceWith[] = _("Το {B_DEF_ABILITY} του {B_DEF_NAME_WITH_PREFIX}\nεμποδίζει τον έρωτα!");
static const u8 sText_PkmnPreventsPoisoningWith[] = _("Το {B_DEF_ABILITY} του {B_EFF_NAME_WITH_PREFIX}\nεμποδίζει τη δηλητηρίαση!");
static const u8 sText_PkmnPreventsConfusionWith[] = _("Το {B_DEF_ABILITY} του {B_DEF_NAME_WITH_PREFIX}\nεμποδίζει τη σύγχυση!");
static const u8 sText_PkmnRaisedFirePowerWith[] = _("Το {B_DEF_ABILITY} του {B_DEF_NAME_WITH_PREFIX}\nανέβασε τη δύναμη της FIRE!");
static const u8 sText_PkmnAnchorsItselfWith[] = _("Το {B_DEF_NAME_WITH_PREFIX} αγκυρώνεται\nμε το {B_DEF_ABILITY}!");
static const u8 sText_PkmnCutsAttackWith[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nκόβει το ATTACK του {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnPreventsStatLossWith[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nαποτρέπει τη μείωση των stat!");
static const u8 sText_PkmnHurtsWith[] = _("Το {B_DEF_ABILITY} του {B_DEF_NAME_WITH_PREFIX}\nχτύπησε το {B_ATK_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnTraced[] = _("Το {B_SCR_ACTIVE_NAME_WITH_PREFIX} ΑΝΤΕΓΡΑΨΕ\nτο {B_BUFF2} του {B_BUFF1}!");
static const u8 sText_PkmnsXPreventsBurns[] = _("Το {B_EFF_ABILITY} του {B_EFF_NAME_WITH_PREFIX}\nεμποδίζει τα εγκαύματα!");
static const u8 sText_PkmnsXBlocksY[] = _("Το {B_DEF_ABILITY} του {B_DEF_NAME_WITH_PREFIX}\nμπλοκάρει το {B_CURRENT_MOVE}!");
static const u8 sText_PkmnsXBlocksY2[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nμπλοκάρει το {B_CURRENT_MOVE}!");
static const u8 sText_PkmnsXRestoredHPALittle2[] = _("Το {B_ATK_ABILITY} του {B_ATK_NAME_WITH_PREFIX}\nεπανέφερε τα HP του λίγο!");
static const u8 sText_PkmnsXWhippedUpSandstorm[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nέφερε αμμοθύελλα!");
static const u8 sText_PkmnsXIntensifiedSun[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nδυνάμωσε τις ακτίνες του ήλιου!");
static const u8 sText_PkmnsXPreventsYLoss[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nεμποδίζει την απώλεια {B_BUFF1}!");
static const u8 sText_PkmnsXInfatuatedY[] = _("Το {B_DEF_ABILITY} του {B_DEF_NAME_WITH_PREFIX}\nξεμυάλισε το {B_ATK_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnsXMadeYIneffective[] = _("Το {B_DEF_ABILITY} του {B_DEF_NAME_WITH_PREFIX}\nακύρωσε το {B_CURRENT_MOVE}!");
static const u8 sText_PkmnsXCuredYProblem[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nθεράπευσε το {B_BUFF1} του!");
static const u8 sText_ItSuckedLiquidOoze[] = _("Ρούφηξε το\nLIQUID OOZE!");
static const u8 sText_PkmnTransformed[] = _("Το {B_SCR_ACTIVE_NAME_WITH_PREFIX} μεταμορφώθηκε!");
static const u8 sText_PkmnsXTookAttack[] = _("Το {B_DEF_ABILITY} του {B_DEF_NAME_WITH_PREFIX}\nδέχτηκε την επίθεση!");
const u8 gText_PkmnsXPreventsSwitching[] = _("Το {B_LAST_ABILITY} του {B_BUFF1}\nεμποδίζει την αλλαγή!\p");
static const u8 sText_PreventedFromWorking[] = _("Το {B_DEF_ABILITY} του {B_DEF_NAME_WITH_PREFIX}\nεμπόδισε το {B_BUFF1} του\l{B_SCR_ACTIVE_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnsXMadeItIneffective[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nτο έκανε αναποτελεσματικό!");
static const u8 sText_PkmnsXPreventsFlinching[] = _("Το {B_EFF_ABILITY} του {B_EFF_NAME_WITH_PREFIX}\nεμποδίζει τη δειλία!");
static const u8 sText_PkmnsXPreventsYsZ[] = _("Το {B_ATK_ABILITY} του {B_ATK_NAME_WITH_PREFIX}\nεμποδίζει το {B_DEF_ABILITY}\lτου {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnsXCuredItsYProblem[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nθεράπευσε το {B_BUFF1} του!");
static const u8 sText_PkmnsXHadNoEffectOnY[] = _("Το {B_SCR_ACTIVE_ABILITY} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nδεν επηρέασε το {B_EFF_NAME_WITH_PREFIX}!");
static const u8 sText_StatSharply[] = _("πολύ ");
const u8 gText_StatRose[] = _("ανέβηκε!");
static const u8 sText_StatHarshly[] = _("πάρα πολύ ");
static const u8 sText_StatFell[] = _("έπεσε!");
static const u8 sText_AttackersStatRose[] = _("Το {B_BUFF1} του {B_ATK_NAME_WITH_PREFIX}\n{B_BUFF2}");
const u8 gText_DefendersStatRose[] = _("Το {B_BUFF1} του {B_DEF_NAME_WITH_PREFIX}\n{B_BUFF2}");
static const u8 sText_UsingItemTheStatOfPkmnRose[] = _("Με το {B_LAST_ITEM}, το {B_BUFF1}\nτου {B_SCR_ACTIVE_NAME_WITH_PREFIX} {B_BUFF2}");
static const u8 sText_AttackersStatFell[] = _("Το {B_BUFF1} του {B_ATK_NAME_WITH_PREFIX}\n{B_BUFF2}");
static const u8 sText_DefendersStatFell[] = _("Το {B_BUFF1} του {B_DEF_NAME_WITH_PREFIX}\n{B_BUFF2}");
static const u8 sText_StatsWontIncrease2[] = _("Τα stat του {B_ATK_NAME_WITH_PREFIX}\nδεν πάνε πιο ψηλά!");
static const u8 sText_StatsWontDecrease2[] = _("Τα stat του {B_DEF_NAME_WITH_PREFIX}\nδεν πάνε πιο χαμηλά!");
static const u8 sText_CriticalHit[] = _("Καίριο χτύπημα!");
static const u8 sText_OneHitKO[] = _("Είναι KO με ένα χτύπημα!");
static const u8 sText_123Poof[] = _("{PAUSE 32}1, {PAUSE 15}2, και{PAUSE 15}… {PAUSE 15}… {PAUSE 15}… {PAUSE 15}{PLAY_SE SE_BALL_BOUNCE_1}Πουφ!\p");
static const u8 sText_AndEllipsis[] = _("Και…\p");
static const u8 sText_HMMovesCantBeForgotten[] = _("Οι κινήσεις HM δεν μπορούν\nνα ξεχαστούν τώρα.\p");
static const u8 sText_NotVeryEffective[] = _("Δεν είναι πολύ αποτελεσματικό…");
static const u8 sText_SuperEffective[] = _("Είναι σούπερ αποτελεσματικό!");
static const u8 sText_GotAwaySafely[] = _("{PLAY_SE SE_FLEE}Ξέφυγες με ασφάλεια!\p");
static const u8 sText_PkmnFledUsingIts[] = _("{PLAY_SE SE_FLEE}Το {B_ATK_NAME_WITH_PREFIX} έφυγε\nμε το {B_LAST_ITEM}!\p");
static const u8 sText_PkmnFledUsing[] = _("{PLAY_SE SE_FLEE}Το {B_ATK_NAME_WITH_PREFIX} έφυγε\nμε το {B_ATK_ABILITY}!\p");
static const u8 sText_WildPkmnFled[] = _("{PLAY_SE SE_FLEE}Το άγριο {B_BUFF1} έφυγε!");
static const u8 sText_PlayerDefeatedLinkTrainer[] = _("Παίκτης νίκησε:\n{B_LINK_OPPONENT1_NAME}!");
static const u8 sText_TwoLinkTrainersDefeated[] = _("Παίκτης νίκησε {B_LINK_OPPONENT1_NAME}\nκαι {B_LINK_OPPONENT2_NAME}!");
static const u8 sText_PlayerLostAgainstLinkTrainer[] = _("Παίκτης έχασε από\n{B_LINK_OPPONENT1_NAME}!");
static const u8 sText_PlayerLostToTwo[] = _("Παίκτης έχασε από {B_LINK_OPPONENT1_NAME}\nκαι {B_LINK_OPPONENT2_NAME}!");
static const u8 sText_PlayerBattledToDrawLinkTrainer[] = _("Παίκτης έφερε ισοπαλία με\n{B_LINK_OPPONENT1_NAME}!");
static const u8 sText_PlayerBattledToDrawVsTwo[] = _("Παίκτης έφερε ισοπαλία με {B_LINK_OPPONENT1_NAME}\nκαι {B_LINK_OPPONENT2_NAME}!");
static const u8 sText_WildFled[] = _("{PLAY_SE SE_FLEE}Το {B_LINK_OPPONENT1_NAME} έφυγε!");
static const u8 sText_TwoWildFled[] = _("{PLAY_SE SE_FLEE}Τα {B_LINK_OPPONENT1_NAME} και\n{B_LINK_OPPONENT2_NAME} έφυγαν!");
static const u8 sText_NoRunningFromTrainers[] = _("Όχι! Δεν μπορείς να φύγεις από\nμάχη με TRAINER!\p");
static const u8 sText_CantEscape[] = _("Δεν μπορείς να ξεφύγεις!\p");
static const u8 sText_DontLeaveBirch[] = _("PROF. BIRCH: Μη μ' αφήνεις έτσι!\p");
static const u8 sText_ButNothingHappened[] = _("Αλλά δεν έγινε τίποτα!");
static const u8 sText_ButItFailed[] = _("Αλλά απέτυχε!");
static const u8 sText_ItHurtConfusion[] = _("Χτύπησε τον εαυτό του λόγω\nτης σύγχυσης!");
static const u8 sText_MirrorMoveFailed[] = _("Το MIRROR MOVE απέτυχε!");
static const u8 sText_StartedToRain[] = _("Άρχισε να βρέχει!");
static const u8 sText_DownpourStarted[] = _("Ξεκίνησε μια νεροποντή!"); // corresponds to DownpourText in pokegold and pokecrystal and is used by Rain Dance in GSC
static const u8 sText_RainContinues[] = _("Η βροχή συνεχίζει να πέφτει.");
static const u8 sText_DownpourContinues[] = _("Η νεροποντή συνεχίζεται."); // unused
static const u8 sText_RainStopped[] = _("Η βροχή σταμάτησε.");
static const u8 sText_SandstormBrewed[] = _("Μια αμμοθύελλα άρχισε!");
static const u8 sText_SandstormRages[] = _("Η αμμοθύελλα μαίνεται.");
static const u8 sText_SandstormSubsided[] = _("Η αμμοθύελλα υποχώρησε.");
static const u8 sText_SunlightGotBright[] = _("Το φως του ήλιου δυνάμωσε!");
static const u8 sText_SunlightStrong[] = _("Το φως του ήλιου είναι δυνατό.");
static const u8 sText_SunlightFaded[] = _("Το φως του ήλιου ξεθώριασε.");
static const u8 sText_StartedHail[] = _("Άρχισε να ρίχνει χαλάζι!");
static const u8 sText_HailContinues[] = _("Το χαλάζι συνεχίζει να πέφτει.");
static const u8 sText_HailStopped[] = _("Το χαλάζι σταμάτησε.");
static const u8 sText_FailedToSpitUp[] = _("Μα απέτυχε να ΦΤΥΣΕΙ κάτι!");
static const u8 sText_FailedToSwallow[] = _("Μα απέτυχε να ΚΑΤΑΠΙΕΙ κάτι!");
static const u8 sText_WindBecameHeatWave[] = _("Ο άνεμος έγινε ένα\nHEAT WAVE!");
static const u8 sText_StatChangesGone[] = _("Όλες οι αλλαγές στα stat\nεξαλείφθηκαν!");
static const u8 sText_CoinsScattered[] = _("Κέρματα σκορπίστηκαν παντού!");
static const u8 sText_TooWeakForSubstitute[] = _("Ήταν πολύ αδύναμο για να\nφτιάξει ένα SUBSTITUTE!");
static const u8 sText_SharedPain[] = _("Οι μαχητές μοιράστηκαν\nτον πόνο τους!");
static const u8 sText_BellChimed[] = _("Μια καμπάνα χτύπησε!");
static const u8 sText_FaintInThree[] = _("Τα επηρεασμένα POKéMON θα\nλιποθυμήσουν σε 3 γύρους!");
static const u8 sText_NoPPLeft[] = _("Δεν έχουν μείνει PP για\nαυτή την κίνηση!\p");
static const u8 sText_ButNoPPLeft[] = _("Αλλά δεν είχαν μείνει PP\nγια την κίνηση!");
static const u8 sText_PkmnIgnoresAsleep[] = _("Το {B_ATK_NAME_WITH_PREFIX} αγνόησε τις\nδιαταγές ενώ κοιμόταν!");
static const u8 sText_PkmnIgnoredOrders[] = _("Το {B_ATK_NAME_WITH_PREFIX} αγνόησε τις\nδιαταγές!");
static const u8 sText_PkmnBeganToNap[] = _("Το {B_ATK_NAME_WITH_PREFIX} πήρε\nέναν υπνάκο!");
static const u8 sText_PkmnLoafing[] = _("Το {B_ATK_NAME_WITH_PREFIX}\nτεμπελιάζει!");
static const u8 sText_PkmnWontObey[] = _("Το {B_ATK_NAME_WITH_PREFIX} δεν\nυπακούει!");
static const u8 sText_PkmnTurnedAway[] = _("Το {B_ATK_NAME_WITH_PREFIX} γύρισε\nαλλού!");
static const u8 sText_PkmnPretendNotNotice[] = _("Το {B_ATK_NAME_WITH_PREFIX} έκανε\nπως δεν κατάλαβε!");
static const u8 sText_EnemyAboutToSwitchPkmn[] = _("Ο {B_TRAINER1_CLASS} {B_TRAINER1_NAME} θα\nχρησιμοποιήσει {B_BUFF2}.\pΘα αλλάξεις POKéMON;");
static const u8 sText_PkmnLearnedMove2[] = _("Το {B_ATK_NAME_WITH_PREFIX} έμαθε την\nκίνηση {B_BUFF1}!");
static const u8 sText_PlayerDefeatedLinkTrainerTrainer1[] = _("Ο παίκτης νίκησε:\n{B_TRAINER1_CLASS} {B_TRAINER1_NAME}!\p");
static const u8 sText_CreptCloser[] = _("πλησίασες \nτον {B_OPPONENT_MON1_NAME}!");
static const u8 sText_CantGetCloser[] = _("δεν μπορείς\nνα πλησιάσεις άλλο!");
static const u8 sText_PkmnWatchingCarefully[] = _("Το {B_OPPONENT_MON1_NAME} παρακολουθεί\nπροσεκτικά!");
static const u8 sText_PkmnCuriousAboutX[] = _("Το {B_OPPONENT_MON1_NAME} έχει περιέργεια\nγια το {B_BUFF1}!");
static const u8 sText_PkmnEnthralledByX[] = _("Το {B_OPPONENT_MON1_NAME} έχει μαγευτεί\nαπό το {B_BUFF1}!");
static const u8 sText_PkmnIgnoredX[] = _("Το {B_OPPONENT_MON1_NAME} αγνόησε τελείως\nτο {B_BUFF1}!");
static const u8 sText_ThrewPokeblockAtPkmn[] = _("Έριξες ένα {POKEBLOCK}\nστον {B_OPPONENT_MON1_NAME}!\p");
static const u8 sText_OutOfSafariBalls[] = _("{PLAY_SE SE_DING_DONG}ΕΚΦΩΝΗΤΗΣ: Ξέμεινες από\nSAFARI BALLS! Τέλος χρόνου!\p");
static const u8 sText_OpponentMon1Appeared[] = _("Εμφανίστηκε ένα\n{B_OPPONENT_MON1_NAME}!\p");
static const u8 sText_WildPkmnAppeared[] = _("Εμφανίστηκε ένα άγριο\n{B_OPPONENT_MON1_NAME}!\p");
static const u8 sText_LegendaryPkmnAppeared[] = _("Εμφανίστηκε ένα άγριο\n{B_OPPONENT_MON1_NAME}!\p");
static const u8 sText_WildPkmnAppearedPause[] = _("Εμφανίστηκε ένα άγριο\n{B_OPPONENT_MON1_NAME}!{PAUSE 127}");
static const u8 sText_TwoWildPkmnAppeared[] = _("Εμφανίστηκε ένα άγριο {B_OPPONENT_MON1_NAME}\nκαι ένα {B_OPPONENT_MON2_NAME}!\p");
static const u8 sText_Trainer1WantsToBattle[] = _("Ο {B_TRAINER1_CLASS} {B_TRAINER1_NAME}\nθέλει να μονομαχήσετε!\p");
static const u8 sText_LinkTrainerWantsToBattle[] = _("Ο {B_LINK_OPPONENT1_NAME}\nθέλει να μονομαχήσετε!");
static const u8 sText_TwoLinkTrainersWantToBattle[] = _("Οι {B_LINK_OPPONENT1_NAME} και {B_LINK_OPPONENT2_NAME}\nθέλουν να μονομαχήσετε!");
static const u8 sText_Trainer1SentOutPkmn[] = _("Ο {B_TRAINER1_CLASS} {B_TRAINER1_NAME} έστειλε\nτο {B_OPPONENT_MON1_NAME}!");
static const u8 sText_Trainer1SentOutTwoPkmn[] = _("Ο {B_TRAINER1_CLASS} {B_TRAINER1_NAME} έστειλε τα\n{B_OPPONENT_MON1_NAME} και {B_OPPONENT_MON2_NAME}!");
static const u8 sText_Trainer1SentOutPkmn2[] = _("Ο {B_TRAINER1_CLASS} {B_TRAINER1_NAME} έστειλε\nτο {B_BUFF1}!");
static const u8 sText_LinkTrainerSentOutPkmn[] = _("Ο {B_LINK_OPPONENT1_NAME} έστειλε\nτο {B_OPPONENT_MON1_NAME}!");
static const u8 sText_LinkTrainerSentOutTwoPkmn[] = _("Ο {B_LINK_OPPONENT1_NAME} έστειλε τα\n{B_OPPONENT_MON1_NAME} και {B_OPPONENT_MON2_NAME}!");
static const u8 sText_TwoLinkTrainersSentOutPkmn[] = _("Ο {B_LINK_OPPONENT1_NAME} έστειλε το {B_LINK_OPPONENT_MON1_NAME}!\nΟ {B_LINK_OPPONENT2_NAME} έστειλε το {B_LINK_OPPONENT_MON2_NAME}!");
static const u8 sText_LinkTrainerSentOutPkmn2[] = _("Ο {B_LINK_OPPONENT1_NAME} έστειλε\nτο {B_BUFF1}!");
static const u8 sText_LinkTrainerMultiSentOutPkmn[] = _("Ο {B_LINK_SCR_TRAINER_NAME} έστειλε\nτο {B_BUFF1}!");
static const u8 sText_GoPkmn[] = _("Πήγαινε! {B_PLAYER_MON1_NAME}!");
static const u8 sText_GoTwoPkmn[] = _("Πηγαίνετε! {B_PLAYER_MON1_NAME} και\n{B_PLAYER_MON2_NAME}!");
static const u8 sText_GoPkmn2[] = _("Πήγαινε! {B_BUFF1}!");
static const u8 sText_DoItPkmn[] = _("Κάντο! {B_BUFF1}!");
static const u8 sText_GoForItPkmn[] = _("Προσπάθησε, {B_BUFF1}!");
static const u8 sText_YourFoesWeakGetEmPkmn[] = _("Ο αντίπαλος είναι αδύναμος!\nΕμπρός, {B_BUFF1}!");
static const u8 sText_LinkPartnerSentOutPkmnGoPkmn[] = _("Ο {B_LINK_PARTNER_NAME} έστειλε το {B_LINK_PLAYER_MON2_NAME}!\nΠήγαινε! {B_LINK_PLAYER_MON1_NAME}!");
static const u8 sText_PkmnThatsEnough[] = _("{B_BUFF1}, φτάνει!\nΓύρνα πίσω!");
static const u8 sText_PkmnComeBack[] = _("{B_BUFF1}, γύρνα πίσω!");
static const u8 sText_PkmnOkComeBack[] = _("{B_BUFF1}, εντάξει!\nΓύρνα πίσω!");
static const u8 sText_PkmnGoodComeBack[] = _("{B_BUFF1}, καλά τα πήγες!\nΓύρνα πίσω!");
static const u8 sText_Trainer1WithdrewPkmn[] = _("Ο {B_TRAINER1_CLASS} {B_TRAINER1_NAME}\nαπέσυρε το {B_BUFF1}!");
static const u8 sText_LinkTrainer1WithdrewPkmn[] = _("Ο {B_LINK_OPPONENT1_NAME} απέσυρε\nτο {B_BUFF1}!");
static const u8 sText_LinkTrainer2WithdrewPkmn[] = _("Ο {B_LINK_SCR_TRAINER_NAME} απέσυρε\nτο {B_BUFF1}!");
static const u8 sText_WildPkmnPrefix[] = _("Άγριο ");
static const u8 sText_FoePkmnPrefix[] = _("Αντίπαλο ");
static const u8 sText_EmptyString8[] = _("");
static const u8 sText_FoePkmnPrefix2[] = _("Αντίπαλο");
static const u8 sText_AllyPkmnPrefix[] = _("Σύμμαχο");
static const u8 sText_FoePkmnPrefix3[] = _("Αντίπαλο");
static const u8 sText_AllyPkmnPrefix2[] = _("Σύμμαχο");
static const u8 sText_FoePkmnPrefix4[] = _("Αντίπαλο");
static const u8 sText_AllyPkmnPrefix3[] = _("Σύμμαχο");
static const u8 sText_AttackerUsedX[] = _("Το {B_ATK_NAME_WITH_PREFIX} χρησιμοποίησε\n{B_BUFF2}");
static const u8 sText_ExclamationMark[] = _("!");
static const u8 sText_ExclamationMark2[] = _("!");
static const u8 sText_ExclamationMark3[] = _("!");
static const u8 sText_ExclamationMark4[] = _("!");
static const u8 sText_ExclamationMark5[] = _("!");
static const u8 sText_HP2[] = _("HP");
static const u8 sText_Attack2[] = _("ATTACK");
static const u8 sText_Defense2[] = _("DEFENSE");
static const u8 sText_Speed[] = _("SPEED");
static const u8 sText_SpAtk2[] = _("SP. ATK");
static const u8 sText_SpDef2[] = _("SP. DEF");
static const u8 sText_Accuracy[] = _("ευστοχία");
static const u8 sText_Evasiveness[] = _("αποφυγή");

const u8 * const gStatNamesTable[NUM_BATTLE_STATS] =
{
    [STAT_HP]      = sText_HP2,
    [STAT_ATK]     = sText_Attack2,
    [STAT_DEF]     = sText_Defense2,
    [STAT_SPEED]   = sText_Speed,
    [STAT_SPATK]   = sText_SpAtk2,
    [STAT_SPDEF]   = sText_SpDef2,
    [STAT_ACC]     = sText_Accuracy,
    [STAT_EVASION] = sText_Evasiveness,
};

static const u8 sText_PokeblockWasTooSpicy[] = _("ήταν πολύ καυτερό!");
static const u8 sText_PokeblockWasTooDry[] = _("ήταν πολύ στεγνό!");
static const u8 sText_PokeblockWasTooSweet[] = _("ήταν πολύ γλυκό!");
static const u8 sText_PokeblockWasTooBitter[] = _("ήταν πολύ πικρό!");
static const u8 sText_PokeblockWasTooSour[] = _("ήταν πολύ ξινό!");

const u8 * const gPokeblockWasTooXStringTable[FLAVOR_COUNT] =
{
    [FLAVOR_SPICY]  = sText_PokeblockWasTooSpicy,
    [FLAVOR_DRY]    = sText_PokeblockWasTooDry,
    [FLAVOR_SWEET]  = sText_PokeblockWasTooSweet,
    [FLAVOR_BITTER] = sText_PokeblockWasTooBitter,
    [FLAVOR_SOUR]   = sText_PokeblockWasTooSour
};

static const u8 sText_PlayerUsedItem[] = _("Χρησιμοποίησες\n{B_LAST_ITEM}!");
static const u8 sText_WallyUsedItem[] = _("Ο WALLY χρησιμοποίησε\n{B_LAST_ITEM}!");
static const u8 sText_Trainer1UsedItem[] = _("Ο {B_TRAINER1_CLASS} {B_TRAINER1_NAME}\nχρησιμοποίησε {B_LAST_ITEM}!");
static const u8 sText_TrainerBlockedBall[] = _("Ο TRAINER μπλόκαρε την BALL!");
static const u8 sText_DontBeAThief[] = _("Μην γίνεσαι κλέφτης!");
static const u8 sText_ItDodgedBall[] = _("Απέφυγε την BALL!\nΔεν μπορείς να το πιάσεις!");
static const u8 sText_YouMissedPkmn[] = _("Αστόχησες!");
static const u8 sText_PkmnBrokeFree[] = _("Ω, όχι!\nΤο POKéMON ελευθερώθηκε!");
static const u8 sText_ItAppearedCaught[] = _("Ααα!\nΦάνηκε ότι πιάστηκε!");
static const u8 sText_AarghAlmostHadIt[] = _("Αααργκ!\nΠαρά λίγο να το πιάσεις!");
static const u8 sText_ShootSoClose[] = _("Κρίμα!\nΠαρά λίγο να το πιάσεις!");
static const u8 sText_GotchaPkmnCaughtPlayer[] = _("Το 'χω!\nΤο {B_OPPONENT_MON1_NAME} πιάστηκε!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}\p");
static const u8 sText_GotchaPkmnCaughtWally[] = _("Το 'χω!\nΤο {B_OPPONENT_MON1_NAME} πιάστηκε!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}{PAUSE 127}");
static const u8 sText_GiveNicknameCaptured[] = _("Θες να δώσεις όνομα στο\nπιασμένο {B_OPPONENT_MON1_NAME};");
static const u8 sText_PkmnSentToPC[] = _("Το {B_OPPONENT_MON1_NAME} στάλθηκε\nστο PC ({B_PC_CREATOR_NAME}).");
static const u8 sText_Someones[] = _("Κάποιος");
static const u8 sText_Lanettes[] = _("LANETTE");
static const u8 sText_PkmnDataAddedToDex[] = _("Τα δεδομένα του {B_OPPONENT_MON1_NAME}\nπροστέθηκαν στο POKéDEX.\p");
static const u8 sText_ItIsRaining[] = _("Βρέχει.");
static const u8 sText_SandstormIsRaging[] = _("Μια αμμοθύελλα μαίνεται.");
static const u8 sText_BoxIsFull[] = _("Το BOX είναι γεμάτο!\nΔεν μπορείς να πιάσεις άλλο!\p");
static const u8 sText_EnigmaBerry[] = _("ENIGMA BERRY");
static const u8 sText_BerrySuffix[] = _(" BERRY");
static const u8 sText_PkmnsItemCuredParalysis[] = _("Το {B_LAST_ITEM} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nθεράπευσε την παράλυση!");
static const u8 sText_PkmnsItemCuredPoison[] = _("Το {B_LAST_ITEM} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nθεράπευσε τη δηλητηρίαση!");
static const u8 sText_PkmnsItemHealedBurn[] = _("Το {B_LAST_ITEM} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nθεράπευσε το έγκαυμα!");
static const u8 sText_PkmnsItemDefrostedIt[] = _("Το {B_LAST_ITEM} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nτο ξεπάγωσε!");
static const u8 sText_PkmnsItemWokeIt[] = _("Το {B_LAST_ITEM} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nτο ξύπνησε!");
static const u8 sText_PkmnsItemSnappedOut[] = _("Το {B_LAST_ITEM} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nτο συνέφερε από τη σύγχυση!");
static const u8 sText_PkmnsItemCuredProblem[] = _("Το {B_LAST_ITEM} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nθεράπευσε το {B_BUFF1} του!");
static const u8 sText_PkmnsItemNormalizedStatus[] = _("Το {B_LAST_ITEM} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nεξομάλυνε την κατάστασή του!");
static const u8 sText_PkmnsItemRestoredHealth[] = _("Το {B_LAST_ITEM} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nανέκτησε υγεία!");
static const u8 sText_PkmnsItemRestoredPP[] = _("Το {B_LAST_ITEM} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nανέκτησε PP για το {B_BUFF1}!");
static const u8 sText_PkmnsItemRestoredStatus[] = _("Το {B_LAST_ITEM} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nεξομάλυνε την κατάστασή του!");
static const u8 sText_PkmnsItemRestoredHPALittle[] = _("Το {B_LAST_ITEM} του {B_SCR_ACTIVE_NAME_WITH_PREFIX}\nανέκτησε λίγο τα HP του!");
static const u8 sText_ItemAllowsOnlyYMove[] = _("Το {B_LAST_ITEM} επιτρέπει\nμόνο το {B_CURRENT_MOVE}!\p");
static const u8 sText_PkmnHungOnWithX[] = _("Το {B_DEF_NAME_WITH_PREFIX} κρατήθηκε\nμε το {B_LAST_ITEM}!");
const u8 gText_EmptyString3[] = _("");
static const u8 sText_YouThrowABallNowRight[] = _("Θα ρίξεις μια BALL τώρα, σωστά;\nΕ… Θα κάνω ό,τι μπορώ!");

// early declaration of strings
static const u8 sText_PkmnIncapableOfPower[];
static const u8 sText_GlintAppearsInEye[];
static const u8 sText_PkmnGettingIntoPosition[];
static const u8 sText_PkmnBeganGrowlingDeeply[];
static const u8 sText_PkmnEagerForMore[];
static const u8 sText_DefeatedOpponentByReferee[];
static const u8 sText_LostToOpponentByReferee[];
static const u8 sText_TiedOpponentByReferee[];
static const u8 sText_QuestionForfeitMatch[];
static const u8 sText_ForfeitedMatch[];
static const u8 sText_Trainer1WinText[];
static const u8 sText_Trainer2WinText[];
static const u8 sText_TwoInGameTrainersDefeated[];
static const u8 sText_Trainer2LoseText[];

const u8 * const gBattleStringsTable[BATTLESTRINGS_COUNT - BATTLESTRINGS_TABLE_START] =
{
    [STRINGID_TRAINER1LOSETEXT - BATTLESTRINGS_TABLE_START] = sText_Trainer1LoseText,
    [STRINGID_PKMNGAINEDEXP - BATTLESTRINGS_TABLE_START] = sText_PkmnGainedEXP,
    [STRINGID_PKMNGREWTOLV - BATTLESTRINGS_TABLE_START] = sText_PkmnGrewToLv,
    [STRINGID_PKMNLEARNEDMOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnLearnedMove,
    [STRINGID_TRYTOLEARNMOVE1 - BATTLESTRINGS_TABLE_START] = sText_TryToLearnMove1,
    [STRINGID_TRYTOLEARNMOVE2 - BATTLESTRINGS_TABLE_START] = sText_TryToLearnMove2,
    [STRINGID_TRYTOLEARNMOVE3 - BATTLESTRINGS_TABLE_START] = sText_TryToLearnMove3,
    [STRINGID_PKMNFORGOTMOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnForgotMove,
    [STRINGID_STOPLEARNINGMOVE - BATTLESTRINGS_TABLE_START] = sText_StopLearningMove,
    [STRINGID_DIDNOTLEARNMOVE - BATTLESTRINGS_TABLE_START] = sText_DidNotLearnMove,
    [STRINGID_PKMNLEARNEDMOVE2 - BATTLESTRINGS_TABLE_START] = sText_PkmnLearnedMove2,
    [STRINGID_ATTACKMISSED - BATTLESTRINGS_TABLE_START] = sText_AttackMissed,
    [STRINGID_PKMNPROTECTEDITSELF - BATTLESTRINGS_TABLE_START] = sText_PkmnProtectedItself,
    [STRINGID_STATSWONTINCREASE2 - BATTLESTRINGS_TABLE_START] = sText_StatsWontIncrease2,
    [STRINGID_AVOIDEDDAMAGE - BATTLESTRINGS_TABLE_START] = sText_AvoidedDamage,
    [STRINGID_ITDOESNTAFFECT - BATTLESTRINGS_TABLE_START] = sText_ItDoesntAffect,
    [STRINGID_ATTACKERFAINTED - BATTLESTRINGS_TABLE_START] = sText_AttackerFainted,
    [STRINGID_TARGETFAINTED - BATTLESTRINGS_TABLE_START] = sText_TargetFainted,
    [STRINGID_PLAYERGOTMONEY - BATTLESTRINGS_TABLE_START] = sText_PlayerGotMoney,
    [STRINGID_PLAYERWHITEOUT - BATTLESTRINGS_TABLE_START] = sText_PlayerWhiteout,
    [STRINGID_PLAYERWHITEOUT2 - BATTLESTRINGS_TABLE_START] = sText_PlayerWhiteout2,
    [STRINGID_PREVENTSESCAPE - BATTLESTRINGS_TABLE_START] = sText_PreventsEscape,
    [STRINGID_HITXTIMES - BATTLESTRINGS_TABLE_START] = sText_HitXTimes,
    [STRINGID_PKMNFELLASLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnFellAsleep,
    [STRINGID_PKMNMADESLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnMadeSleep,
    [STRINGID_PKMNALREADYASLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnAlreadyAsleep,
    [STRINGID_PKMNALREADYASLEEP2 - BATTLESTRINGS_TABLE_START] = sText_PkmnAlreadyAsleep2,
    [STRINGID_PKMNWASNTAFFECTED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasntAffected,
    [STRINGID_PKMNWASPOISONED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasPoisoned,
    [STRINGID_PKMNPOISONEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnPoisonedBy,
    [STRINGID_PKMNHURTBYPOISON - BATTLESTRINGS_TABLE_START] = sText_PkmnHurtByPoison,
    [STRINGID_PKMNALREADYPOISONED - BATTLESTRINGS_TABLE_START] = sText_PkmnAlreadyPoisoned,
    [STRINGID_PKMNBADLYPOISONED - BATTLESTRINGS_TABLE_START] = sText_PkmnBadlyPoisoned,
    [STRINGID_PKMNENERGYDRAINED - BATTLESTRINGS_TABLE_START] = sText_PkmnEnergyDrained,
    [STRINGID_PKMNWASBURNED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasBurned,
    [STRINGID_PKMNBURNEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnBurnedBy,
    [STRINGID_PKMNHURTBYBURN - BATTLESTRINGS_TABLE_START] = sText_PkmnHurtByBurn,
    [STRINGID_PKMNWASFROZEN - BATTLESTRINGS_TABLE_START] = sText_PkmnWasFrozen,
    [STRINGID_PKMNFROZENBY - BATTLESTRINGS_TABLE_START] = sText_PkmnFrozenBy,
    [STRINGID_PKMNISFROZEN - BATTLESTRINGS_TABLE_START] = sText_PkmnIsFrozen,
    [STRINGID_PKMNWASDEFROSTED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasDefrosted,
    [STRINGID_PKMNWASDEFROSTED2 - BATTLESTRINGS_TABLE_START] = sText_PkmnWasDefrosted2,
    [STRINGID_PKMNWASDEFROSTEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnWasDefrostedBy,
    [STRINGID_PKMNWASPARALYZED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasParalyzed,
    [STRINGID_PKMNWASPARALYZEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnWasParalyzedBy,
    [STRINGID_PKMNISPARALYZED - BATTLESTRINGS_TABLE_START] = sText_PkmnIsParalyzed,
    [STRINGID_PKMNISALREADYPARALYZED - BATTLESTRINGS_TABLE_START] = sText_PkmnIsAlreadyParalyzed,
    [STRINGID_PKMNHEALEDPARALYSIS - BATTLESTRINGS_TABLE_START] = sText_PkmnHealedParalysis,
    [STRINGID_PKMNDREAMEATEN - BATTLESTRINGS_TABLE_START] = sText_PkmnDreamEaten,
    [STRINGID_STATSWONTINCREASE - BATTLESTRINGS_TABLE_START] = sText_StatsWontIncrease,
    [STRINGID_STATSWONTDECREASE - BATTLESTRINGS_TABLE_START] = sText_StatsWontDecrease,
    [STRINGID_TEAMSTOPPEDWORKING - BATTLESTRINGS_TABLE_START] = sText_TeamStoppedWorking,
    [STRINGID_FOESTOPPEDWORKING - BATTLESTRINGS_TABLE_START] = sText_FoeStoppedWorking,
    [STRINGID_PKMNISCONFUSED - BATTLESTRINGS_TABLE_START] = sText_PkmnIsConfused,
    [STRINGID_PKMNHEALEDCONFUSION - BATTLESTRINGS_TABLE_START] = sText_PkmnHealedConfusion,
    [STRINGID_PKMNWASCONFUSED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasConfused,
    [STRINGID_PKMNALREADYCONFUSED - BATTLESTRINGS_TABLE_START] = sText_PkmnAlreadyConfused,
    [STRINGID_PKMNFELLINLOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnFellInLove,
    [STRINGID_PKMNINLOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnInLove,
    [STRINGID_PKMNIMMOBILIZEDBYLOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnImmobilizedByLove,
    [STRINGID_PKMNBLOWNAWAY - BATTLESTRINGS_TABLE_START] = sText_PkmnBlownAway,
    [STRINGID_PKMNCHANGEDTYPE - BATTLESTRINGS_TABLE_START] = sText_PkmnChangedType,
    [STRINGID_PKMNFLINCHED - BATTLESTRINGS_TABLE_START] = sText_PkmnFlinched,
    [STRINGID_PKMNREGAINEDHEALTH - BATTLESTRINGS_TABLE_START] = sText_PkmnRegainedHealth,
    [STRINGID_PKMNHPFULL - BATTLESTRINGS_TABLE_START] = sText_PkmnHPFull,
    [STRINGID_PKMNRAISEDSPDEF - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedSpDef,
    [STRINGID_PKMNRAISEDDEF - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedDef,
    [STRINGID_PKMNCOVEREDBYVEIL - BATTLESTRINGS_TABLE_START] = sText_PkmnCoveredByVeil,
    [STRINGID_PKMNUSEDSAFEGUARD - BATTLESTRINGS_TABLE_START] = sText_PkmnUsedSafeguard,
    [STRINGID_PKMNSAFEGUARDEXPIRED - BATTLESTRINGS_TABLE_START] = sText_PkmnSafeguardExpired,
    [STRINGID_PKMNWENTTOSLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnWentToSleep,
    [STRINGID_PKMNSLEPTHEALTHY - BATTLESTRINGS_TABLE_START] = sText_PkmnSleptHealthy,
    [STRINGID_PKMNWHIPPEDWHIRLWIND - BATTLESTRINGS_TABLE_START] = sText_PkmnWhippedWhirlwind,
    [STRINGID_PKMNTOOKSUNLIGHT - BATTLESTRINGS_TABLE_START] = sText_PkmnTookSunlight,
    [STRINGID_PKMNLOWEREDHEAD - BATTLESTRINGS_TABLE_START] = sText_PkmnLoweredHead,
    [STRINGID_PKMNISGLOWING - BATTLESTRINGS_TABLE_START] = sText_PkmnIsGlowing,
    [STRINGID_PKMNFLEWHIGH - BATTLESTRINGS_TABLE_START] = sText_PkmnFlewHigh,
    [STRINGID_PKMNDUGHOLE - BATTLESTRINGS_TABLE_START] = sText_PkmnDugHole,
    [STRINGID_PKMNSQUEEZEDBYBIND - BATTLESTRINGS_TABLE_START] = sText_PkmnSqueezedByBind,
    [STRINGID_PKMNTRAPPEDINVORTEX - BATTLESTRINGS_TABLE_START] = sText_PkmnTrappedInVortex,
    [STRINGID_PKMNWRAPPEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnWrappedBy,
    [STRINGID_PKMNCLAMPED - BATTLESTRINGS_TABLE_START] = sText_PkmnClamped,
    [STRINGID_PKMNHURTBY - BATTLESTRINGS_TABLE_START] = sText_PkmnHurtBy,
    [STRINGID_PKMNFREEDFROM - BATTLESTRINGS_TABLE_START] = sText_PkmnFreedFrom,
    [STRINGID_PKMNCRASHED - BATTLESTRINGS_TABLE_START] = sText_PkmnCrashed,
    [STRINGID_PKMNSHROUDEDINMIST - BATTLESTRINGS_TABLE_START] = gText_PkmnShroudedInMist,
    [STRINGID_PKMNPROTECTEDBYMIST - BATTLESTRINGS_TABLE_START] = sText_PkmnProtectedByMist,
    [STRINGID_PKMNGETTINGPUMPED - BATTLESTRINGS_TABLE_START] = gText_PkmnGettingPumped,
    [STRINGID_PKMNHITWITHRECOIL - BATTLESTRINGS_TABLE_START] = sText_PkmnHitWithRecoil,
    [STRINGID_PKMNPROTECTEDITSELF2 - BATTLESTRINGS_TABLE_START] = sText_PkmnProtectedItself2,
    [STRINGID_PKMNBUFFETEDBYSANDSTORM - BATTLESTRINGS_TABLE_START] = sText_PkmnBuffetedBySandstorm,
    [STRINGID_PKMNPELTEDBYHAIL - BATTLESTRINGS_TABLE_START] = sText_PkmnPeltedByHail,
    [STRINGID_PKMNSEEDED - BATTLESTRINGS_TABLE_START] = sText_PkmnSeeded,
    [STRINGID_PKMNEVADEDATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnEvadedAttack,
    [STRINGID_PKMNSAPPEDBYLEECHSEED - BATTLESTRINGS_TABLE_START] = sText_PkmnSappedByLeechSeed,
    [STRINGID_PKMNFASTASLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnFastAsleep,
    [STRINGID_PKMNWOKEUP - BATTLESTRINGS_TABLE_START] = sText_PkmnWokeUp,
    [STRINGID_PKMNUPROARKEPTAWAKE - BATTLESTRINGS_TABLE_START] = sText_PkmnUproarKeptAwake,
    [STRINGID_PKMNWOKEUPINUPROAR - BATTLESTRINGS_TABLE_START] = sText_PkmnWokeUpInUproar,
    [STRINGID_PKMNCAUSEDUPROAR - BATTLESTRINGS_TABLE_START] = sText_PkmnCausedUproar,
    [STRINGID_PKMNMAKINGUPROAR - BATTLESTRINGS_TABLE_START] = sText_PkmnMakingUproar,
    [STRINGID_PKMNCALMEDDOWN - BATTLESTRINGS_TABLE_START] = sText_PkmnCalmedDown,
    [STRINGID_PKMNCANTSLEEPINUPROAR - BATTLESTRINGS_TABLE_START] = sText_PkmnCantSleepInUproar,
    [STRINGID_PKMNSTOCKPILED - BATTLESTRINGS_TABLE_START] = sText_PkmnStockpiled,
    [STRINGID_PKMNCANTSTOCKPILE - BATTLESTRINGS_TABLE_START] = sText_PkmnCantStockpile,
    [STRINGID_PKMNCANTSLEEPINUPROAR2 - BATTLESTRINGS_TABLE_START] = sText_PkmnCantSleepInUproar2,
    [STRINGID_UPROARKEPTPKMNAWAKE - BATTLESTRINGS_TABLE_START] = sText_UproarKeptPkmnAwake,
    [STRINGID_PKMNSTAYEDAWAKEUSING - BATTLESTRINGS_TABLE_START] = sText_PkmnStayedAwakeUsing,
    [STRINGID_PKMNSTORINGENERGY - BATTLESTRINGS_TABLE_START] = sText_PkmnStoringEnergy,
    [STRINGID_PKMNUNLEASHEDENERGY - BATTLESTRINGS_TABLE_START] = sText_PkmnUnleashedEnergy,
    [STRINGID_PKMNFATIGUECONFUSION - BATTLESTRINGS_TABLE_START] = sText_PkmnFatigueConfusion,
    [STRINGID_PLAYERPICKEDUPMONEY - BATTLESTRINGS_TABLE_START] = sText_PlayerPickedUpMoney,
    [STRINGID_PKMNUNAFFECTED - BATTLESTRINGS_TABLE_START] = sText_PkmnUnaffected,
    [STRINGID_PKMNTRANSFORMEDINTO - BATTLESTRINGS_TABLE_START] = sText_PkmnTransformedInto,
    [STRINGID_PKMNMADESUBSTITUTE - BATTLESTRINGS_TABLE_START] = sText_PkmnMadeSubstitute,
    [STRINGID_PKMNHASSUBSTITUTE - BATTLESTRINGS_TABLE_START] = sText_PkmnHasSubstitute,
    [STRINGID_SUBSTITUTEDAMAGED - BATTLESTRINGS_TABLE_START] = sText_SubstituteDamaged,
    [STRINGID_PKMNSUBSTITUTEFADED - BATTLESTRINGS_TABLE_START] = sText_PkmnSubstituteFaded,
    [STRINGID_PKMNMUSTRECHARGE - BATTLESTRINGS_TABLE_START] = sText_PkmnMustRecharge,
    [STRINGID_PKMNRAGEBUILDING - BATTLESTRINGS_TABLE_START] = sText_PkmnRageBuilding,
    [STRINGID_PKMNMOVEWASDISABLED - BATTLESTRINGS_TABLE_START] = sText_PkmnMoveWasDisabled,
    [STRINGID_PKMNMOVEISDISABLED - BATTLESTRINGS_TABLE_START] = sText_PkmnMoveIsDisabled,
    [STRINGID_PKMNMOVEDISABLEDNOMORE - BATTLESTRINGS_TABLE_START] = sText_PkmnMoveDisabledNoMore,
    [STRINGID_PKMNGOTENCORE - BATTLESTRINGS_TABLE_START] = sText_PkmnGotEncore,
    [STRINGID_PKMNENCOREENDED - BATTLESTRINGS_TABLE_START] = sText_PkmnEncoreEnded,
    [STRINGID_PKMNTOOKAIM - BATTLESTRINGS_TABLE_START] = sText_PkmnTookAim,
    [STRINGID_PKMNSKETCHEDMOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnSketchedMove,
    [STRINGID_PKMNTRYINGTOTAKEFOE - BATTLESTRINGS_TABLE_START] = sText_PkmnTryingToTakeFoe,
    [STRINGID_PKMNTOOKFOE - BATTLESTRINGS_TABLE_START] = sText_PkmnTookFoe,
    [STRINGID_PKMNREDUCEDPP - BATTLESTRINGS_TABLE_START] = sText_PkmnReducedPP,
    [STRINGID_PKMNSTOLEITEM - BATTLESTRINGS_TABLE_START] = sText_PkmnStoleItem,
    [STRINGID_TARGETCANTESCAPENOW - BATTLESTRINGS_TABLE_START] = sText_TargetCantEscapeNow,
    [STRINGID_PKMNFELLINTONIGHTMARE - BATTLESTRINGS_TABLE_START] = sText_PkmnFellIntoNightmare,
    [STRINGID_PKMNLOCKEDINNIGHTMARE - BATTLESTRINGS_TABLE_START] = sText_PkmnLockedInNightmare,
    [STRINGID_PKMNLAIDCURSE - BATTLESTRINGS_TABLE_START] = sText_PkmnLaidCurse,
    [STRINGID_PKMNAFFLICTEDBYCURSE - BATTLESTRINGS_TABLE_START] = sText_PkmnAfflictedByCurse,
    [STRINGID_SPIKESSCATTERED - BATTLESTRINGS_TABLE_START] = sText_SpikesScattered,
    [STRINGID_PKMNHURTBYSPIKES - BATTLESTRINGS_TABLE_START] = sText_PkmnHurtBySpikes,
    [STRINGID_PKMNIDENTIFIED - BATTLESTRINGS_TABLE_START] = sText_PkmnIdentified,
    [STRINGID_PKMNPERISHCOUNTFELL - BATTLESTRINGS_TABLE_START] = sText_PkmnPerishCountFell,
    [STRINGID_PKMNBRACEDITSELF - BATTLESTRINGS_TABLE_START] = sText_PkmnBracedItself,
    [STRINGID_PKMNENDUREDHIT - BATTLESTRINGS_TABLE_START] = sText_PkmnEnduredHit,
    [STRINGID_MAGNITUDESTRENGTH - BATTLESTRINGS_TABLE_START] = sText_MagnitudeStrength,
    [STRINGID_PKMNCUTHPMAXEDATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnCutHPMaxedAttack,
    [STRINGID_PKMNCOPIEDSTATCHANGES - BATTLESTRINGS_TABLE_START] = sText_PkmnCopiedStatChanges,
    [STRINGID_PKMNGOTFREE - BATTLESTRINGS_TABLE_START] = sText_PkmnGotFree,
    [STRINGID_PKMNSHEDLEECHSEED - BATTLESTRINGS_TABLE_START] = sText_PkmnShedLeechSeed,
    [STRINGID_PKMNBLEWAWAYSPIKES - BATTLESTRINGS_TABLE_START] = sText_PkmnBlewAwaySpikes,
    [STRINGID_PKMNFLEDFROMBATTLE - BATTLESTRINGS_TABLE_START] = sText_PkmnFledFromBattle,
    [STRINGID_PKMNFORESAWATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnForesawAttack,
    [STRINGID_PKMNTOOKATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnTookAttack,
    [STRINGID_PKMNATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnAttack,
    [STRINGID_PKMNCENTERATTENTION - BATTLESTRINGS_TABLE_START] = sText_PkmnCenterAttention,
    [STRINGID_PKMNCHARGINGPOWER - BATTLESTRINGS_TABLE_START] = sText_PkmnChargingPower,
    [STRINGID_NATUREPOWERTURNEDINTO - BATTLESTRINGS_TABLE_START] = sText_NaturePowerTurnedInto,
    [STRINGID_PKMNSTATUSNORMAL - BATTLESTRINGS_TABLE_START] = sText_PkmnStatusNormal,
    [STRINGID_PKMNHASNOMOVESLEFT - BATTLESTRINGS_TABLE_START] = sText_PkmnHasNoMovesLeft,
    [STRINGID_PKMNSUBJECTEDTOTORMENT - BATTLESTRINGS_TABLE_START] = sText_PkmnSubjectedToTorment,
    [STRINGID_PKMNCANTUSEMOVETORMENT - BATTLESTRINGS_TABLE_START] = sText_PkmnCantUseMoveTorment,
    [STRINGID_PKMNTIGHTENINGFOCUS - BATTLESTRINGS_TABLE_START] = sText_PkmnTighteningFocus,
    [STRINGID_PKMNFELLFORTAUNT - BATTLESTRINGS_TABLE_START] = sText_PkmnFellForTaunt,
    [STRINGID_PKMNCANTUSEMOVETAUNT - BATTLESTRINGS_TABLE_START] = sText_PkmnCantUseMoveTaunt,
    [STRINGID_PKMNREADYTOHELP - BATTLESTRINGS_TABLE_START] = sText_PkmnReadyToHelp,
    [STRINGID_PKMNSWITCHEDITEMS - BATTLESTRINGS_TABLE_START] = sText_PkmnSwitchedItems,
    [STRINGID_PKMNCOPIEDFOE - BATTLESTRINGS_TABLE_START] = sText_PkmnCopiedFoe,
    [STRINGID_PKMNMADEWISH - BATTLESTRINGS_TABLE_START] = sText_PkmnMadeWish,
    [STRINGID_PKMNWISHCAMETRUE - BATTLESTRINGS_TABLE_START] = sText_PkmnWishCameTrue,
    [STRINGID_PKMNPLANTEDROOTS - BATTLESTRINGS_TABLE_START] = sText_PkmnPlantedRoots,
    [STRINGID_PKMNABSORBEDNUTRIENTS - BATTLESTRINGS_TABLE_START] = sText_PkmnAbsorbedNutrients,
    [STRINGID_PKMNANCHOREDITSELF - BATTLESTRINGS_TABLE_START] = sText_PkmnAnchoredItself,
    [STRINGID_PKMNWASMADEDROWSY - BATTLESTRINGS_TABLE_START] = sText_PkmnWasMadeDrowsy,
    [STRINGID_PKMNKNOCKEDOFF - BATTLESTRINGS_TABLE_START] = sText_PkmnKnockedOff,
    [STRINGID_PKMNSWAPPEDABILITIES - BATTLESTRINGS_TABLE_START] = sText_PkmnSwappedAbilities,
    [STRINGID_PKMNSEALEDOPPONENTMOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnSealedOpponentMove,
    [STRINGID_PKMNCANTUSEMOVESEALED - BATTLESTRINGS_TABLE_START] = sText_PkmnCantUseMoveSealed,
    [STRINGID_PKMNWANTSGRUDGE - BATTLESTRINGS_TABLE_START] = sText_PkmnWantsGrudge,
    [STRINGID_PKMNLOSTPPGRUDGE - BATTLESTRINGS_TABLE_START] = sText_PkmnLostPPGrudge,
    [STRINGID_PKMNSHROUDEDITSELF - BATTLESTRINGS_TABLE_START] = sText_PkmnShroudedItself,
    [STRINGID_PKMNMOVEBOUNCED - BATTLESTRINGS_TABLE_START] = sText_PkmnMoveBounced,
    [STRINGID_PKMNWAITSFORTARGET - BATTLESTRINGS_TABLE_START] = sText_PkmnWaitsForTarget,
    [STRINGID_PKMNSNATCHEDMOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnSnatchedMove,
    [STRINGID_PKMNMADEITRAIN - BATTLESTRINGS_TABLE_START] = sText_PkmnMadeItRain,
    [STRINGID_PKMNRAISEDSPEED - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedSpeed,
    [STRINGID_PKMNPROTECTEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnProtectedBy,
    [STRINGID_PKMNPREVENTSUSAGE - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsUsage,
    [STRINGID_PKMNRESTOREDHPUSING - BATTLESTRINGS_TABLE_START] = sText_PkmnRestoredHPUsing,
    [STRINGID_PKMNCHANGEDTYPEWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnChangedTypeWith,
    [STRINGID_PKMNPREVENTSPARALYSISWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsParalysisWith,
    [STRINGID_PKMNPREVENTSROMANCEWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsRomanceWith,
    [STRINGID_PKMNPREVENTSPOISONINGWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsPoisoningWith,
    [STRINGID_PKMNPREVENTSCONFUSIONWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsConfusionWith,
    [STRINGID_PKMNRAISEDFIREPOWERWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedFirePowerWith,
    [STRINGID_PKMNANCHORSITSELFWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnAnchorsItselfWith,
    [STRINGID_PKMNCUTSATTACKWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnCutsAttackWith,
    [STRINGID_PKMNPREVENTSSTATLOSSWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsStatLossWith,
    [STRINGID_PKMNHURTSWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnHurtsWith,
    [STRINGID_PKMNTRACED - BATTLESTRINGS_TABLE_START] = sText_PkmnTraced,
    [STRINGID_STATSHARPLY - BATTLESTRINGS_TABLE_START] = sText_StatSharply,
    [STRINGID_STATROSE - BATTLESTRINGS_TABLE_START] = gText_StatRose,
    [STRINGID_STATHARSHLY - BATTLESTRINGS_TABLE_START] = sText_StatHarshly,
    [STRINGID_STATFELL - BATTLESTRINGS_TABLE_START] = sText_StatFell,
    [STRINGID_ATTACKERSSTATROSE - BATTLESTRINGS_TABLE_START] = sText_AttackersStatRose,
    [STRINGID_DEFENDERSSTATROSE - BATTLESTRINGS_TABLE_START] = gText_DefendersStatRose,
    [STRINGID_ATTACKERSSTATFELL - BATTLESTRINGS_TABLE_START] = sText_AttackersStatFell,
    [STRINGID_DEFENDERSSTATFELL - BATTLESTRINGS_TABLE_START] = sText_DefendersStatFell,
    [STRINGID_CRITICALHIT - BATTLESTRINGS_TABLE_START] = sText_CriticalHit,
    [STRINGID_ONEHITKO - BATTLESTRINGS_TABLE_START] = sText_OneHitKO,
    [STRINGID_123POOF - BATTLESTRINGS_TABLE_START] = sText_123Poof,
    [STRINGID_ANDELLIPSIS - BATTLESTRINGS_TABLE_START] = sText_AndEllipsis,
    [STRINGID_NOTVERYEFFECTIVE - BATTLESTRINGS_TABLE_START] = sText_NotVeryEffective,
    [STRINGID_SUPEREFFECTIVE - BATTLESTRINGS_TABLE_START] = sText_SuperEffective,
    [STRINGID_GOTAWAYSAFELY - BATTLESTRINGS_TABLE_START] = sText_GotAwaySafely,
    [STRINGID_WILDPKMNFLED - BATTLESTRINGS_TABLE_START] = sText_WildPkmnFled,
    [STRINGID_NORUNNINGFROMTRAINERS - BATTLESTRINGS_TABLE_START] = sText_NoRunningFromTrainers,
    [STRINGID_CANTESCAPE - BATTLESTRINGS_TABLE_START] = sText_CantEscape,
    [STRINGID_DONTLEAVEBIRCH - BATTLESTRINGS_TABLE_START] = sText_DontLeaveBirch,
    [STRINGID_BUTNOTHINGHAPPENED - BATTLESTRINGS_TABLE_START] = sText_ButNothingHappened,
    [STRINGID_BUTITFAILED - BATTLESTRINGS_TABLE_START] = sText_ButItFailed,
    [STRINGID_ITHURTCONFUSION - BATTLESTRINGS_TABLE_START] = sText_ItHurtConfusion,
    [STRINGID_MIRRORMOVEFAILED - BATTLESTRINGS_TABLE_START] = sText_MirrorMoveFailed,
    [STRINGID_STARTEDTORAIN - BATTLESTRINGS_TABLE_START] = sText_StartedToRain,
    [STRINGID_DOWNPOURSTARTED - BATTLESTRINGS_TABLE_START] = sText_DownpourStarted,
    [STRINGID_RAINCONTINUES - BATTLESTRINGS_TABLE_START] = sText_RainContinues,
    [STRINGID_DOWNPOURCONTINUES - BATTLESTRINGS_TABLE_START] = sText_DownpourContinues,
    [STRINGID_RAINSTOPPED - BATTLESTRINGS_TABLE_START] = sText_RainStopped,
    [STRINGID_SANDSTORMBREWED - BATTLESTRINGS_TABLE_START] = sText_SandstormBrewed,
    [STRINGID_SANDSTORMRAGES - BATTLESTRINGS_TABLE_START] = sText_SandstormRages,
    [STRINGID_SANDSTORMSUBSIDED - BATTLESTRINGS_TABLE_START] = sText_SandstormSubsided,
    [STRINGID_SUNLIGHTGOTBRIGHT - BATTLESTRINGS_TABLE_START] = sText_SunlightGotBright,
    [STRINGID_SUNLIGHTSTRONG - BATTLESTRINGS_TABLE_START] = sText_SunlightStrong,
    [STRINGID_SUNLIGHTFADED - BATTLESTRINGS_TABLE_START] = sText_SunlightFaded,
    [STRINGID_STARTEDHAIL - BATTLESTRINGS_TABLE_START] = sText_StartedHail,
    [STRINGID_HAILCONTINUES - BATTLESTRINGS_TABLE_START] = sText_HailContinues,
    [STRINGID_HAILSTOPPED - BATTLESTRINGS_TABLE_START] = sText_HailStopped,
    [STRINGID_FAILEDTOSPITUP - BATTLESTRINGS_TABLE_START] = sText_FailedToSpitUp,
    [STRINGID_FAILEDTOSWALLOW - BATTLESTRINGS_TABLE_START] = sText_FailedToSwallow,
    [STRINGID_WINDBECAMEHEATWAVE - BATTLESTRINGS_TABLE_START] = sText_WindBecameHeatWave,
    [STRINGID_STATCHANGESGONE - BATTLESTRINGS_TABLE_START] = sText_StatChangesGone,
    [STRINGID_COINSSCATTERED - BATTLESTRINGS_TABLE_START] = sText_CoinsScattered,
    [STRINGID_TOOWEAKFORSUBSTITUTE - BATTLESTRINGS_TABLE_START] = sText_TooWeakForSubstitute,
    [STRINGID_SHAREDPAIN - BATTLESTRINGS_TABLE_START] = sText_SharedPain,
    [STRINGID_BELLCHIMED - BATTLESTRINGS_TABLE_START] = sText_BellChimed,
    [STRINGID_FAINTINTHREE - BATTLESTRINGS_TABLE_START] = sText_FaintInThree,
    [STRINGID_NOPPLEFT - BATTLESTRINGS_TABLE_START] = sText_NoPPLeft,
    [STRINGID_BUTNOPPLEFT - BATTLESTRINGS_TABLE_START] = sText_ButNoPPLeft,
    [STRINGID_PLAYERUSEDITEM - BATTLESTRINGS_TABLE_START] = sText_PlayerUsedItem,
    [STRINGID_WALLYUSEDITEM - BATTLESTRINGS_TABLE_START] = sText_WallyUsedItem,
    [STRINGID_TRAINERBLOCKEDBALL - BATTLESTRINGS_TABLE_START] = sText_TrainerBlockedBall,
    [STRINGID_DONTBEATHIEF - BATTLESTRINGS_TABLE_START] = sText_DontBeAThief,
    [STRINGID_ITDODGEDBALL - BATTLESTRINGS_TABLE_START] = sText_ItDodgedBall,
    [STRINGID_YOUMISSEDPKMN - BATTLESTRINGS_TABLE_START] = sText_YouMissedPkmn,
    [STRINGID_PKMNBROKEFREE - BATTLESTRINGS_TABLE_START] = sText_PkmnBrokeFree,
    [STRINGID_ITAPPEAREDCAUGHT - BATTLESTRINGS_TABLE_START] = sText_ItAppearedCaught,
    [STRINGID_AARGHALMOSTHADIT - BATTLESTRINGS_TABLE_START] = sText_AarghAlmostHadIt,
    [STRINGID_SHOOTSOCLOSE - BATTLESTRINGS_TABLE_START] = sText_ShootSoClose,
    [STRINGID_GOTCHAPKMNCAUGHTPLAYER - BATTLESTRINGS_TABLE_START] = sText_GotchaPkmnCaughtPlayer,
    [STRINGID_GOTCHAPKMNCAUGHTWALLY - BATTLESTRINGS_TABLE_START] = sText_GotchaPkmnCaughtWally,
    [STRINGID_GIVENICKNAMECAPTURED - BATTLESTRINGS_TABLE_START] = sText_GiveNicknameCaptured,
    [STRINGID_PKMNSENTTOPC - BATTLESTRINGS_TABLE_START] = sText_PkmnSentToPC,
    [STRINGID_PKMNDATAADDEDTODEX - BATTLESTRINGS_TABLE_START] = sText_PkmnDataAddedToDex,
    [STRINGID_ITISRAINING - BATTLESTRINGS_TABLE_START] = sText_ItIsRaining,
    [STRINGID_SANDSTORMISRAGING - BATTLESTRINGS_TABLE_START] = sText_SandstormIsRaging,
    [STRINGID_CANTESCAPE2 - BATTLESTRINGS_TABLE_START] = sText_CantEscape2,
    [STRINGID_PKMNIGNORESASLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnIgnoresAsleep,
    [STRINGID_PKMNIGNOREDORDERS - BATTLESTRINGS_TABLE_START] = sText_PkmnIgnoredOrders,
    [STRINGID_PKMNBEGANTONAP - BATTLESTRINGS_TABLE_START] = sText_PkmnBeganToNap,
    [STRINGID_PKMNLOAFING - BATTLESTRINGS_TABLE_START] = sText_PkmnLoafing,
    [STRINGID_PKMNWONTOBEY - BATTLESTRINGS_TABLE_START] = sText_PkmnWontObey,
    [STRINGID_PKMNTURNEDAWAY - BATTLESTRINGS_TABLE_START] = sText_PkmnTurnedAway,
    [STRINGID_PKMNPRETENDNOTNOTICE - BATTLESTRINGS_TABLE_START] = sText_PkmnPretendNotNotice,
    [STRINGID_ENEMYABOUTTOSWITCHPKMN - BATTLESTRINGS_TABLE_START] = sText_EnemyAboutToSwitchPkmn,
    [STRINGID_CREPTCLOSER - BATTLESTRINGS_TABLE_START] = sText_CreptCloser,
    [STRINGID_CANTGETCLOSER - BATTLESTRINGS_TABLE_START] = sText_CantGetCloser,
    [STRINGID_PKMNWATCHINGCAREFULLY - BATTLESTRINGS_TABLE_START] = sText_PkmnWatchingCarefully,
    [STRINGID_PKMNCURIOUSABOUTX - BATTLESTRINGS_TABLE_START] = sText_PkmnCuriousAboutX,
    [STRINGID_PKMNENTHRALLEDBYX - BATTLESTRINGS_TABLE_START] = sText_PkmnEnthralledByX,
    [STRINGID_PKMNIGNOREDX - BATTLESTRINGS_TABLE_START] = sText_PkmnIgnoredX,
    [STRINGID_THREWPOKEBLOCKATPKMN - BATTLESTRINGS_TABLE_START] = sText_ThrewPokeblockAtPkmn,
    [STRINGID_OUTOFSAFARIBALLS - BATTLESTRINGS_TABLE_START] = sText_OutOfSafariBalls,
    [STRINGID_PKMNSITEMCUREDPARALYSIS - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemCuredParalysis,
    [STRINGID_PKMNSITEMCUREDPOISON - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemCuredPoison,
    [STRINGID_PKMNSITEMHEALEDBURN - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemHealedBurn,
    [STRINGID_PKMNSITEMDEFROSTEDIT - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemDefrostedIt,
    [STRINGID_PKMNSITEMWOKEIT - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemWokeIt,
    [STRINGID_PKMNSITEMSNAPPEDOUT - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemSnappedOut,
    [STRINGID_PKMNSITEMCUREDPROBLEM - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemCuredProblem,
    [STRINGID_PKMNSITEMRESTOREDHEALTH - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemRestoredHealth,
    [STRINGID_PKMNSITEMRESTOREDPP - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemRestoredPP,
    [STRINGID_PKMNSITEMRESTOREDSTATUS - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemRestoredStatus,
    [STRINGID_PKMNSITEMRESTOREDHPALITTLE - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemRestoredHPALittle,
    [STRINGID_ITEMALLOWSONLYYMOVE - BATTLESTRINGS_TABLE_START] = sText_ItemAllowsOnlyYMove,
    [STRINGID_PKMNHUNGONWITHX - BATTLESTRINGS_TABLE_START] = sText_PkmnHungOnWithX,
    [STRINGID_EMPTYSTRING3 - BATTLESTRINGS_TABLE_START] = gText_EmptyString3,
    [STRINGID_PKMNSXPREVENTSBURNS - BATTLESTRINGS_TABLE_START] = sText_PkmnsXPreventsBurns,
    [STRINGID_PKMNSXBLOCKSY - BATTLESTRINGS_TABLE_START] = sText_PkmnsXBlocksY,
    [STRINGID_PKMNSXRESTOREDHPALITTLE2 - BATTLESTRINGS_TABLE_START] = sText_PkmnsXRestoredHPALittle2,
    [STRINGID_PKMNSXWHIPPEDUPSANDSTORM - BATTLESTRINGS_TABLE_START] = sText_PkmnsXWhippedUpSandstorm,
    [STRINGID_PKMNSXPREVENTSYLOSS - BATTLESTRINGS_TABLE_START] = sText_PkmnsXPreventsYLoss,
    [STRINGID_PKMNSXINFATUATEDY - BATTLESTRINGS_TABLE_START] = sText_PkmnsXInfatuatedY,
    [STRINGID_PKMNSXMADEYINEFFECTIVE - BATTLESTRINGS_TABLE_START] = sText_PkmnsXMadeYIneffective,
    [STRINGID_PKMNSXCUREDYPROBLEM - BATTLESTRINGS_TABLE_START] = sText_PkmnsXCuredYProblem,
    [STRINGID_ITSUCKEDLIQUIDOOZE - BATTLESTRINGS_TABLE_START] = sText_ItSuckedLiquidOoze,
    [STRINGID_PKMNTRANSFORMED - BATTLESTRINGS_TABLE_START] = sText_PkmnTransformed,
    [STRINGID_ELECTRICITYWEAKENED - BATTLESTRINGS_TABLE_START] = sText_ElectricityWeakened,
    [STRINGID_FIREWEAKENED - BATTLESTRINGS_TABLE_START] = sText_FireWeakened,
    [STRINGID_PKMNHIDUNDERWATER - BATTLESTRINGS_TABLE_START] = sText_PkmnHidUnderwater,
    [STRINGID_PKMNSPRANGUP - BATTLESTRINGS_TABLE_START] = sText_PkmnSprangUp,
    [STRINGID_HMMOVESCANTBEFORGOTTEN - BATTLESTRINGS_TABLE_START] = sText_HMMovesCantBeForgotten,
    [STRINGID_XFOUNDONEY - BATTLESTRINGS_TABLE_START] = sText_XFoundOneY,
    [STRINGID_PLAYERDEFEATEDTRAINER1 - BATTLESTRINGS_TABLE_START] = sText_PlayerDefeatedLinkTrainerTrainer1,
    [STRINGID_SOOTHINGAROMA - BATTLESTRINGS_TABLE_START] = sText_SoothingAroma,
    [STRINGID_ITEMSCANTBEUSEDNOW - BATTLESTRINGS_TABLE_START] = sText_ItemsCantBeUsedNow,
    [STRINGID_FORXCOMMAYZ - BATTLESTRINGS_TABLE_START] = sText_ForXCommaYZ,
    [STRINGID_USINGITEMSTATOFPKMNROSE - BATTLESTRINGS_TABLE_START] = sText_UsingItemTheStatOfPkmnRose,
    [STRINGID_PKMNUSEDXTOGETPUMPED - BATTLESTRINGS_TABLE_START] = sText_PkmnUsedXToGetPumped,
    [STRINGID_PKMNSXMADEYUSELESS - BATTLESTRINGS_TABLE_START] = sText_PkmnsXMadeYUseless,
    [STRINGID_PKMNTRAPPEDBYSANDTOMB - BATTLESTRINGS_TABLE_START] = sText_PkmnTrappedBySandTomb,
    [STRINGID_EMPTYSTRING4 - BATTLESTRINGS_TABLE_START] = sText_EmptyString4,
    [STRINGID_ABOOSTED - BATTLESTRINGS_TABLE_START] = sText_ABoosted,
    [STRINGID_PKMNSXINTENSIFIEDSUN - BATTLESTRINGS_TABLE_START] = sText_PkmnsXIntensifiedSun,
    [STRINGID_PKMNMAKESGROUNDMISS - BATTLESTRINGS_TABLE_START] = sText_PkmnMakesGroundMiss,
    [STRINGID_YOUTHROWABALLNOWRIGHT - BATTLESTRINGS_TABLE_START] = sText_YouThrowABallNowRight,
    [STRINGID_PKMNSXTOOKATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnsXTookAttack,
    [STRINGID_PKMNCHOSEXASDESTINY - BATTLESTRINGS_TABLE_START] = sText_PkmnChoseXAsDestiny,
    [STRINGID_PKMNLOSTFOCUS - BATTLESTRINGS_TABLE_START] = sText_PkmnLostFocus,
    [STRINGID_USENEXTPKMN - BATTLESTRINGS_TABLE_START] = sText_UseNextPkmn,
    [STRINGID_PKMNFLEDUSINGITS - BATTLESTRINGS_TABLE_START] = sText_PkmnFledUsingIts,
    [STRINGID_PKMNFLEDUSING - BATTLESTRINGS_TABLE_START] = sText_PkmnFledUsing,
    [STRINGID_PKMNWASDRAGGEDOUT - BATTLESTRINGS_TABLE_START] = sText_PkmnWasDraggedOut,
    [STRINGID_PREVENTEDFROMWORKING - BATTLESTRINGS_TABLE_START] = sText_PreventedFromWorking,
    [STRINGID_PKMNSITEMNORMALIZEDSTATUS - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemNormalizedStatus,
    [STRINGID_TRAINER1USEDITEM - BATTLESTRINGS_TABLE_START] = sText_Trainer1UsedItem,
    [STRINGID_BOXISFULL - BATTLESTRINGS_TABLE_START] = sText_BoxIsFull,
    [STRINGID_PKMNAVOIDEDATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnAvoidedAttack,
    [STRINGID_PKMNSXMADEITINEFFECTIVE - BATTLESTRINGS_TABLE_START] = sText_PkmnsXMadeItIneffective,
    [STRINGID_PKMNSXPREVENTSFLINCHING - BATTLESTRINGS_TABLE_START] = sText_PkmnsXPreventsFlinching,
    [STRINGID_PKMNALREADYHASBURN - BATTLESTRINGS_TABLE_START] = sText_PkmnAlreadyHasBurn,
    [STRINGID_STATSWONTDECREASE2 - BATTLESTRINGS_TABLE_START] = sText_StatsWontDecrease2,
    [STRINGID_PKMNSXBLOCKSY2 - BATTLESTRINGS_TABLE_START] = sText_PkmnsXBlocksY2,
    [STRINGID_PKMNSXWOREOFF - BATTLESTRINGS_TABLE_START] = sText_PkmnsXWoreOff,
    [STRINGID_PKMNRAISEDDEFALITTLE - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedDefALittle,
    [STRINGID_PKMNRAISEDSPDEFALITTLE - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedSpDefALittle,
    [STRINGID_THEWALLSHATTERED - BATTLESTRINGS_TABLE_START] = sText_TheWallShattered,
    [STRINGID_PKMNSXPREVENTSYSZ - BATTLESTRINGS_TABLE_START] = sText_PkmnsXPreventsYsZ,
    [STRINGID_PKMNSXCUREDITSYPROBLEM - BATTLESTRINGS_TABLE_START] = sText_PkmnsXCuredItsYProblem,
    [STRINGID_ATTACKERCANTESCAPE - BATTLESTRINGS_TABLE_START] = sText_AttackerCantEscape,
    [STRINGID_PKMNOBTAINEDX - BATTLESTRINGS_TABLE_START] = sText_PkmnObtainedX,
    [STRINGID_PKMNOBTAINEDX2 - BATTLESTRINGS_TABLE_START] = sText_PkmnObtainedX2,
    [STRINGID_PKMNOBTAINEDXYOBTAINEDZ - BATTLESTRINGS_TABLE_START] = sText_PkmnObtainedXYObtainedZ,
    [STRINGID_BUTNOEFFECT - BATTLESTRINGS_TABLE_START] = sText_ButNoEffect,
    [STRINGID_PKMNSXHADNOEFFECTONY - BATTLESTRINGS_TABLE_START] = sText_PkmnsXHadNoEffectOnY,
    [STRINGID_TWOENEMIESDEFEATED - BATTLESTRINGS_TABLE_START] = sText_TwoInGameTrainersDefeated,
    [STRINGID_TRAINER2LOSETEXT - BATTLESTRINGS_TABLE_START] = sText_Trainer2LoseText,
    [STRINGID_PKMNINCAPABLEOFPOWER - BATTLESTRINGS_TABLE_START] = sText_PkmnIncapableOfPower,
    [STRINGID_GLINTAPPEARSINEYE - BATTLESTRINGS_TABLE_START] = sText_GlintAppearsInEye,
    [STRINGID_PKMNGETTINGINTOPOSITION - BATTLESTRINGS_TABLE_START] = sText_PkmnGettingIntoPosition,
    [STRINGID_PKMNBEGANGROWLINGDEEPLY - BATTLESTRINGS_TABLE_START] = sText_PkmnBeganGrowlingDeeply,
    [STRINGID_PKMNEAGERFORMORE - BATTLESTRINGS_TABLE_START] = sText_PkmnEagerForMore,
    [STRINGID_DEFEATEDOPPONENTBYREFEREE - BATTLESTRINGS_TABLE_START] = sText_DefeatedOpponentByReferee,
    [STRINGID_LOSTTOOPPONENTBYREFEREE - BATTLESTRINGS_TABLE_START] = sText_LostToOpponentByReferee,
    [STRINGID_TIEDOPPONENTBYREFEREE - BATTLESTRINGS_TABLE_START] = sText_TiedOpponentByReferee,
    [STRINGID_QUESTIONFORFEITMATCH - BATTLESTRINGS_TABLE_START] = sText_QuestionForfeitMatch,
    [STRINGID_FORFEITEDMATCH - BATTLESTRINGS_TABLE_START] = sText_ForfeitedMatch,
    [STRINGID_PKMNTRANSFERREDSOMEONESPC - BATTLESTRINGS_TABLE_START] = gText_PkmnTransferredSomeonesPC,
    [STRINGID_PKMNTRANSFERREDLANETTESPC - BATTLESTRINGS_TABLE_START] = gText_PkmnTransferredLanettesPC,
    [STRINGID_PKMNBOXSOMEONESPCFULL - BATTLESTRINGS_TABLE_START] = gText_PkmnTransferredSomeonesPCBoxFull,
    [STRINGID_PKMNBOXLANETTESPCFULL - BATTLESTRINGS_TABLE_START] = gText_PkmnTransferredLanettesPCBoxFull,
    [STRINGID_TRAINER1WINTEXT - BATTLESTRINGS_TABLE_START] = sText_Trainer1WinText,
    [STRINGID_TRAINER2WINTEXT - BATTLESTRINGS_TABLE_START] = sText_Trainer2WinText,
};

const u16 gMissStringIds[] =
{
    [B_MSG_MISSED]      = STRINGID_ATTACKMISSED,
    [B_MSG_PROTECTED]   = STRINGID_PKMNPROTECTEDITSELF,
    [B_MSG_AVOIDED_ATK] = STRINGID_PKMNAVOIDEDATTACK,
    [B_MSG_AVOIDED_DMG] = STRINGID_AVOIDEDDAMAGE,
    [B_MSG_GROUND_MISS] = STRINGID_PKMNMAKESGROUNDMISS
};

const u16 gNoEscapeStringIds[] =
{
    [B_MSG_CANT_ESCAPE]          = STRINGID_CANTESCAPE,
    [B_MSG_DONT_LEAVE_BIRCH]     = STRINGID_DONTLEAVEBIRCH,
    [B_MSG_PREVENTS_ESCAPE]      = STRINGID_PREVENTSESCAPE,
    [B_MSG_CANT_ESCAPE_2]        = STRINGID_CANTESCAPE2,
    [B_MSG_ATTACKER_CANT_ESCAPE] = STRINGID_ATTACKERCANTESCAPE
};

const u16 gMoveWeatherChangeStringIds[] =
{
    [B_MSG_STARTED_RAIN]      = STRINGID_STARTEDTORAIN,
    [B_MSG_STARTED_DOWNPOUR]  = STRINGID_DOWNPOURSTARTED, // Unused
    [B_MSG_WEATHER_FAILED]    = STRINGID_BUTITFAILED,
    [B_MSG_STARTED_SANDSTORM] = STRINGID_SANDSTORMBREWED,
    [B_MSG_STARTED_SUNLIGHT]  = STRINGID_SUNLIGHTGOTBRIGHT,
    [B_MSG_STARTED_HAIL]      = STRINGID_STARTEDHAIL,
};

const u16 gSandStormHailContinuesStringIds[] =
{
    [B_MSG_SANDSTORM] = STRINGID_SANDSTORMRAGES,
    [B_MSG_HAIL]      = STRINGID_HAILCONTINUES
};

const u16 gSandStormHailDmgStringIds[] =
{
    [B_MSG_SANDSTORM] = STRINGID_PKMNBUFFETEDBYSANDSTORM,
    [B_MSG_HAIL]      = STRINGID_PKMNPELTEDBYHAIL
};

const u16 gSandStormHailEndStringIds[] =
{
    [B_MSG_SANDSTORM] = STRINGID_SANDSTORMSUBSIDED,
    [B_MSG_HAIL]      = STRINGID_HAILSTOPPED
};

const u16 gRainContinuesStringIds[] =
{
    [B_MSG_RAIN_CONTINUES]     = STRINGID_RAINCONTINUES,
    [B_MSG_DOWNPOUR_CONTINUES] = STRINGID_DOWNPOURCONTINUES,
    [B_MSG_RAIN_STOPPED]       = STRINGID_RAINSTOPPED
};

const u16 gProtectLikeUsedStringIds[] =
{
    [B_MSG_PROTECTED_ITSELF] = STRINGID_PKMNPROTECTEDITSELF2,
    [B_MSG_BRACED_ITSELF]    = STRINGID_PKMNBRACEDITSELF,
    [B_MSG_PROTECT_FAILED]   = STRINGID_BUTITFAILED,
};

const u16 gReflectLightScreenSafeguardStringIds[] =
{
    [B_MSG_SIDE_STATUS_FAILED]     = STRINGID_BUTITFAILED,
    [B_MSG_SET_REFLECT_SINGLE]     = STRINGID_PKMNRAISEDDEF,
    [B_MSG_SET_REFLECT_DOUBLE]     = STRINGID_PKMNRAISEDDEFALITTLE,
    [B_MSG_SET_LIGHTSCREEN_SINGLE] = STRINGID_PKMNRAISEDSPDEF,
    [B_MSG_SET_LIGHTSCREEN_DOUBLE] = STRINGID_PKMNRAISEDSPDEFALITTLE,
    [B_MSG_SET_SAFEGUARD]          = STRINGID_PKMNCOVEREDBYVEIL,
};

const u16 gLeechSeedStringIds[] =
{
    [B_MSG_LEECH_SEED_SET]   = STRINGID_PKMNSEEDED,
    [B_MSG_LEECH_SEED_MISS]  = STRINGID_PKMNEVADEDATTACK,
    [B_MSG_LEECH_SEED_FAIL]  = STRINGID_ITDOESNTAFFECT,
    [B_MSG_LEECH_SEED_DRAIN] = STRINGID_PKMNSAPPEDBYLEECHSEED,
    [B_MSG_LEECH_SEED_OOZE]  = STRINGID_ITSUCKEDLIQUIDOOZE,
};

const u16 gRestUsedStringIds[] =
{
    [B_MSG_REST]          = STRINGID_PKMNWENTTOSLEEP,
    [B_MSG_REST_STATUSED] = STRINGID_PKMNSLEPTHEALTHY
};

const u16 gUproarOverTurnStringIds[] =
{
    [B_MSG_UPROAR_CONTINUES] = STRINGID_PKMNMAKINGUPROAR,
    [B_MSG_UPROAR_ENDS]      = STRINGID_PKMNCALMEDDOWN
};

const u16 gStockpileUsedStringIds[] =
{
    [B_MSG_STOCKPILED]     = STRINGID_PKMNSTOCKPILED,
    [B_MSG_CANT_STOCKPILE] = STRINGID_PKMNCANTSTOCKPILE,
};

const u16 gWokeUpStringIds[] =
{
    [B_MSG_WOKE_UP]        = STRINGID_PKMNWOKEUP,
    [B_MSG_WOKE_UP_UPROAR] = STRINGID_PKMNWOKEUPINUPROAR
};

const u16 gSwallowFailStringIds[] =
{
    [B_MSG_SWALLOW_FAILED]  = STRINGID_FAILEDTOSWALLOW,
    [B_MSG_SWALLOW_FULL_HP] = STRINGID_PKMNHPFULL
};

const u16 gUproarAwakeStringIds[] =
{
    [B_MSG_CANT_SLEEP_UPROAR]  = STRINGID_PKMNCANTSLEEPINUPROAR2,
    [B_MSG_UPROAR_KEPT_AWAKE]  = STRINGID_UPROARKEPTPKMNAWAKE,
    [B_MSG_STAYED_AWAKE_USING] = STRINGID_PKMNSTAYEDAWAKEUSING,
};

const u16 gStatUpStringIds[] =
{
    [B_MSG_ATTACKER_STAT_ROSE] = STRINGID_ATTACKERSSTATROSE,
    [B_MSG_DEFENDER_STAT_ROSE] = STRINGID_DEFENDERSSTATROSE,
    [B_MSG_STAT_WONT_INCREASE] = STRINGID_STATSWONTINCREASE,
    [B_MSG_STAT_ROSE_EMPTY]    = STRINGID_EMPTYSTRING3,
    [B_MSG_STAT_ROSE_ITEM]     = STRINGID_USINGITEMSTATOFPKMNROSE,
    [B_MSG_USED_DIRE_HIT]      = STRINGID_PKMNUSEDXTOGETPUMPED,
};

const u16 gStatDownStringIds[] =
{
    [B_MSG_ATTACKER_STAT_FELL] = STRINGID_ATTACKERSSTATFELL,
    [B_MSG_DEFENDER_STAT_FELL] = STRINGID_DEFENDERSSTATFELL,
    [B_MSG_STAT_WONT_DECREASE] = STRINGID_STATSWONTDECREASE,
    [B_MSG_STAT_FELL_EMPTY]    = STRINGID_EMPTYSTRING3,
};

// Index read from sTWOTURN_STRINGID
const u16 gFirstTurnOfTwoStringIds[] =
{
    [B_MSG_TURN1_RAZOR_WIND] = STRINGID_PKMNWHIPPEDWHIRLWIND,
    [B_MSG_TURN1_SOLAR_BEAM] = STRINGID_PKMNTOOKSUNLIGHT,
    [B_MSG_TURN1_SKULL_BASH] = STRINGID_PKMNLOWEREDHEAD,
    [B_MSG_TURN1_SKY_ATTACK] = STRINGID_PKMNISGLOWING,
    [B_MSG_TURN1_FLY]        = STRINGID_PKMNFLEWHIGH,
    [B_MSG_TURN1_DIG]        = STRINGID_PKMNDUGHOLE,
    [B_MSG_TURN1_DIVE]       = STRINGID_PKMNHIDUNDERWATER,
    [B_MSG_TURN1_BOUNCE]     = STRINGID_PKMNSPRANGUP,
};

// Index copied from move's index in gTrappingMoves
const u16 gWrappedStringIds[NUM_TRAPPING_MOVES] =
{
    STRINGID_PKMNSQUEEZEDBYBIND,   // MOVE_BIND
    STRINGID_PKMNWRAPPEDBY,        // MOVE_WRAP
    STRINGID_PKMNTRAPPEDINVORTEX,  // MOVE_FIRE_SPIN
    STRINGID_PKMNCLAMPED,          // MOVE_CLAMP
    STRINGID_PKMNTRAPPEDINVORTEX,  // MOVE_WHIRLPOOL
    STRINGID_PKMNTRAPPEDBYSANDTOMB // MOVE_SAND_TOMB
};

const u16 gMistUsedStringIds[] =
{
    [B_MSG_SET_MIST]    = STRINGID_PKMNSHROUDEDINMIST,
    [B_MSG_MIST_FAILED] = STRINGID_BUTITFAILED
};

const u16 gFocusEnergyUsedStringIds[] =
{
    [B_MSG_GETTING_PUMPED]      = STRINGID_PKMNGETTINGPUMPED,
    [B_MSG_FOCUS_ENERGY_FAILED] = STRINGID_BUTITFAILED
};

const u16 gTransformUsedStringIds[] =
{
    [B_MSG_TRANSFORMED]      = STRINGID_PKMNTRANSFORMEDINTO,
    [B_MSG_TRANSFORM_FAILED] = STRINGID_BUTITFAILED
};

const u16 gSubstituteUsedStringIds[] =
{
    [B_MSG_SET_SUBSTITUTE]    = STRINGID_PKMNMADESUBSTITUTE,
    [B_MSG_SUBSTITUTE_FAILED] = STRINGID_TOOWEAKFORSUBSTITUTE
};

const u16 gGotPoisonedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASPOISONED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNPOISONEDBY
};

const u16 gGotParalyzedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASPARALYZED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNWASPARALYZEDBY
};

const u16 gFellAsleepStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNFELLASLEEP,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNMADESLEEP,
};

const u16 gGotBurnedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASBURNED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNBURNEDBY
};

const u16 gGotFrozenStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASFROZEN,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNFROZENBY
};

const u16 gGotDefrostedStringIds[] =
{
    [B_MSG_DEFROSTED]         = STRINGID_PKMNWASDEFROSTED2,
    [B_MSG_DEFROSTED_BY_MOVE] = STRINGID_PKMNWASDEFROSTEDBY
};

const u16 gKOFailedStringIds[] =
{
    [B_MSG_KO_MISS]       = STRINGID_ATTACKMISSED,
    [B_MSG_KO_UNAFFECTED] = STRINGID_PKMNUNAFFECTED
};

const u16 gAttractUsedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNFELLINLOVE,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNSXINFATUATEDY
};

const u16 gAbsorbDrainStringIds[] =
{
    [B_MSG_ABSORB]      = STRINGID_PKMNENERGYDRAINED,
    [B_MSG_ABSORB_OOZE] = STRINGID_ITSUCKEDLIQUIDOOZE
};

const u16 gSportsUsedStringIds[] =
{
    [B_MSG_WEAKEN_ELECTRIC] = STRINGID_ELECTRICITYWEAKENED,
    [B_MSG_WEAKEN_FIRE]     = STRINGID_FIREWEAKENED
};

const u16 gPartyStatusHealStringIds[] =
{
    [B_MSG_BELL]                     = STRINGID_BELLCHIMED,
    [B_MSG_BELL_SOUNDPROOF_ATTACKER] = STRINGID_BELLCHIMED,
    [B_MSG_BELL_SOUNDPROOF_PARTNER]  = STRINGID_BELLCHIMED,
    [B_MSG_BELL_BOTH_SOUNDPROOF]     = STRINGID_BELLCHIMED,
    [B_MSG_SOOTHING_AROMA]           = STRINGID_SOOTHINGAROMA
};

const u16 gFutureMoveUsedStringIds[] =
{
    [B_MSG_FUTURE_SIGHT] = STRINGID_PKMNFORESAWATTACK,
    [B_MSG_DOOM_DESIRE]  = STRINGID_PKMNCHOSEXASDESTINY
};

const u16 gBallEscapeStringIds[] =
{
    [BALL_NO_SHAKES]     = STRINGID_PKMNBROKEFREE,
    [BALL_1_SHAKE]       = STRINGID_ITAPPEAREDCAUGHT,
    [BALL_2_SHAKES]      = STRINGID_AARGHALMOSTHADIT,
    [BALL_3_SHAKES_FAIL] = STRINGID_SHOOTSOCLOSE
};

// Overworld weathers that don't have an associated battle weather default to "It is raining."
const u16 gWeatherStartsStringIds[] =
{
    [WEATHER_NONE]               = STRINGID_ITISRAINING,
    [WEATHER_SUNNY_CLOUDS]       = STRINGID_ITISRAINING,
    [WEATHER_SUNNY]              = STRINGID_ITISRAINING,
    [WEATHER_RAIN]               = STRINGID_ITISRAINING,
    [WEATHER_SNOW]               = STRINGID_ITISRAINING,
    [WEATHER_RAIN_THUNDERSTORM]  = STRINGID_ITISRAINING,
    [WEATHER_FOG_HORIZONTAL]     = STRINGID_ITISRAINING,
    [WEATHER_VOLCANIC_ASH]       = STRINGID_ITISRAINING,
    [WEATHER_SANDSTORM]          = STRINGID_SANDSTORMISRAGING,
    [WEATHER_FOG_DIAGONAL]       = STRINGID_ITISRAINING,
    [WEATHER_UNDERWATER]         = STRINGID_ITISRAINING,
    [WEATHER_SHADE]              = STRINGID_ITISRAINING,
    [WEATHER_DROUGHT]            = STRINGID_SUNLIGHTSTRONG,
    [WEATHER_DOWNPOUR]           = STRINGID_ITISRAINING,
    [WEATHER_UNDERWATER_BUBBLES] = STRINGID_ITISRAINING,
    [WEATHER_ABNORMAL]           = STRINGID_ITISRAINING
};

const u16 gInobedientStringIds[] =
{
    [B_MSG_LOAFING]            = STRINGID_PKMNLOAFING,
    [B_MSG_WONT_OBEY]          = STRINGID_PKMNWONTOBEY,
    [B_MSG_TURNED_AWAY]        = STRINGID_PKMNTURNEDAWAY,
    [B_MSG_PRETEND_NOT_NOTICE] = STRINGID_PKMNPRETENDNOTNOTICE,
    [B_MSG_INCAPABLE_OF_POWER] = STRINGID_PKMNINCAPABLEOFPOWER
};

const u16 gSafariGetNearStringIds[] =
{
    [B_MSG_CREPT_CLOSER]    = STRINGID_CREPTCLOSER,
    [B_MSG_CANT_GET_CLOSER] = STRINGID_CANTGETCLOSER
};

const u16 gSafariPokeblockResultStringIds[] =
{
    [B_MSG_MON_CURIOUS]    = STRINGID_PKMNCURIOUSABOUTX,
    [B_MSG_MON_ENTHRALLED] = STRINGID_PKMNENTHRALLEDBYX,
    [B_MSG_MON_IGNORED]    = STRINGID_PKMNIGNOREDX
};

const u16 gTrainerItemCuredStatusStringIds[] =
{
    [AI_HEAL_CONFUSION] = STRINGID_PKMNSITEMSNAPPEDOUT,
    [AI_HEAL_PARALYSIS] = STRINGID_PKMNSITEMCUREDPARALYSIS,
    [AI_HEAL_FREEZE]    = STRINGID_PKMNSITEMDEFROSTEDIT,
    [AI_HEAL_BURN]      = STRINGID_PKMNSITEMHEALEDBURN,
    [AI_HEAL_POISON]    = STRINGID_PKMNSITEMCUREDPOISON,
    [AI_HEAL_SLEEP]     = STRINGID_PKMNSITEMWOKEIT
};

const u16 gBerryEffectStringIds[] =
{
    [B_MSG_CURED_PROBLEM]     = STRINGID_PKMNSITEMCUREDPROBLEM,
    [B_MSG_NORMALIZED_STATUS] = STRINGID_PKMNSITEMNORMALIZEDSTATUS
};

const u16 gBRNPreventionStringIds[] =
{
    [B_MSG_ABILITY_PREVENTS_MOVE_STATUS]    = STRINGID_PKMNSXPREVENTSBURNS,
    [B_MSG_ABILITY_PREVENTS_ABILITY_STATUS] = STRINGID_PKMNSXPREVENTSYSZ,
    [B_MSG_STATUS_HAD_NO_EFFECT]            = STRINGID_PKMNSXHADNOEFFECTONY
};

const u16 gPRLZPreventionStringIds[] =
{
    [B_MSG_ABILITY_PREVENTS_MOVE_STATUS]    = STRINGID_PKMNPREVENTSPARALYSISWITH,
    [B_MSG_ABILITY_PREVENTS_ABILITY_STATUS] = STRINGID_PKMNSXPREVENTSYSZ,
    [B_MSG_STATUS_HAD_NO_EFFECT]            = STRINGID_PKMNSXHADNOEFFECTONY
};

const u16 gPSNPreventionStringIds[] =
{
    [B_MSG_ABILITY_PREVENTS_MOVE_STATUS]    = STRINGID_PKMNPREVENTSPOISONINGWITH,
    [B_MSG_ABILITY_PREVENTS_ABILITY_STATUS] = STRINGID_PKMNSXPREVENTSYSZ,
    [B_MSG_STATUS_HAD_NO_EFFECT]            = STRINGID_PKMNSXHADNOEFFECTONY
};

const u16 gItemSwapStringIds[] =
{
    [B_MSG_ITEM_SWAP_TAKEN] = STRINGID_PKMNOBTAINEDX,
    [B_MSG_ITEM_SWAP_GIVEN] = STRINGID_PKMNOBTAINEDX2,
    [B_MSG_ITEM_SWAP_BOTH]  = STRINGID_PKMNOBTAINEDXYOBTAINEDZ
};

const u16 gFlashFireStringIds[] =
{
    [B_MSG_FLASH_FIRE_BOOST]    = STRINGID_PKMNRAISEDFIREPOWERWITH,
    [B_MSG_FLASH_FIRE_NO_BOOST] = STRINGID_PKMNSXMADEYINEFFECTIVE
};

const u16 gCaughtMonStringIds[] =
{
    [B_MSG_SENT_SOMEONES_PC]  = STRINGID_PKMNTRANSFERREDSOMEONESPC,
    [B_MSG_SENT_LANETTES_PC]  = STRINGID_PKMNTRANSFERREDLANETTESPC,
    [B_MSG_SOMEONES_BOX_FULL] = STRINGID_PKMNBOXSOMEONESPCFULL,
    [B_MSG_LANETTES_BOX_FULL] = STRINGID_PKMNBOXLANETTESPCFULL,
};

const u16 gTrappingMoves[NUM_TRAPPING_MOVES + 1] =
{
    MOVE_BIND,
    MOVE_WRAP,
    MOVE_FIRE_SPIN,
    MOVE_CLAMP,
    MOVE_WHIRLPOOL,
    MOVE_SAND_TOMB,
    0xFFFF // Never read
};

const u8 gText_PkmnIsEvolving[] = _("Τι;\nΤο {STR_VAR_1} εξελίσσεται!");
const u8 gText_CongratsPkmnEvolved[] = _("Συγχαρητήρια! Το {STR_VAR_1}\nεξελίχθηκε σε {STR_VAR_2}!{WAIT_SE}\p");
const u8 gText_PkmnStoppedEvolving[] = _("Ε; Το {STR_VAR_1}\nσταμάτησε να εξελίσσεται!\p");
const u8 gText_EllipsisQuestionMark[] = _("……;\p");
const u8 gText_WhatWillPkmnDo[] = _("Τι θα κάνει\nτο {B_ACTIVE_NAME_WITH_PREFIX};");
const u8 gText_WhatWillPkmnDo2[] = _("Τι θα κάνεις;");
const u8 gText_WhatWillWallyDo[] = _("Τι θα κάνει\nο WALLY;");
const u8 gText_LinkStandby[] = _("{PAUSE 16}Αναμονή σύνδεσης…");
const u8 gText_BattleMenu[] = _("ΕΠΙΘΕΣΗ{CLEAR_TO 56}ΤΣΑΝΤΑ\nPOKéMON{CLEAR_TO 56}ΤΡΕΧΑ");
const u8 gText_SafariZoneMenu[] = _("BALL{CLEAR_TO 56}{POKEBLOCK}\nΠΛΗΣΙΑΣΕ{CLEAR_TO 56}ΤΡΕΧΑ");
const u8 gText_MoveInterfacePP[] = _("PP ");
const u8 gText_MoveInterfaceType[] = _("TYPE/");
const u8 gText_MoveInterfacePpType[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}PP\nΤΥΠΟΣ/");
const u8 gText_MoveInterfaceDynamicColors[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}");
const u8 gText_WhichMoveToForget4[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}Ποια κίνηση πρέπει να\nξεχαστεί;");
const u8 gText_BattleYesNoChoice[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}Ναι\nΌχι");
const u8 gText_BattleSwitchWhich[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}Αλλαγή\nμε ποιο;");
const u8 gText_BattleSwitchWhich2[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}");
const u8 gText_BattleSwitchWhich3[] = _("{UP_ARROW}");
const u8 gText_BattleSwitchWhich4[] = _("{ESCAPE 4}");
const u8 gText_BattleSwitchWhich5[] = _("-");

static const u8 sText_HP[] = _("HP");
static const u8 sText_Attack[] = _("ATTACK");
static const u8 sText_Defense[] = _("DEFENSE");
static const u8 sText_SpAtk[] = _("SP. ATK");
static const u8 sText_SpDef[] = _("SP. DEF");

// Unused
static const u8 * const sStatNamesTable2[] =
{
    sText_HP, sText_SpAtk, sText_Attack,
    sText_SpDef, sText_Defense, sText_Speed
};

const u8 gText_SafariBalls[] = _("{HIGHLIGHT DARK_GRAY}SAFARI BALLS");
const u8 gText_SafariBallLeft[] = _("{HIGHLIGHT DARK_GRAY}Έμειναν: $" "{HIGHLIGHT DARK_GRAY}");
const u8 gText_Sleep[] = _("ύπνος");
const u8 gText_Poison[] = _("δηλητηρίαση");
const u8 gText_Burn[] = _("έγκαυμα");
const u8 gText_Paralysis[] = _("παράλυση");
const u8 gText_Ice[] = _("πάγωμα");
const u8 gText_Confusion[] = _("σύγχυση");
const u8 gText_Love[] = _("έρωτας");
const u8 gText_SpaceAndSpace[] = _(" και ");
const u8 gText_CommaSpace[] = _(", ");
const u8 gText_Space2[] = _(" ");
const u8 gText_LineBreak[] = _("\l");
const u8 gText_NewLine[] = _("\n");
const u8 gText_Are[] = _("είναι");
const u8 gText_Are2[] = _("είναι");
const u8 gText_BadEgg[] = _("Χαλασμένο ΑΥΓΟ");
const u8 gText_BattleWallyName[] = _("WALLY");
const u8 gText_Win[] = _("{HIGHLIGHT TRANSPARENT}Νίκη");
const u8 gText_Loss[] = _("{HIGHLIGHT TRANSPARENT}Ήττα");
const u8 gText_Draw[] = _("{HIGHLIGHT TRANSPARENT}Ισοπαλία");
static const u8 sText_SpaceIs[] = _(" είναι");
static const u8 sText_ApostropheS[] = _("'s");

// For displaying names of invalid moves.
// This is large enough that the text for TYPE_ELECTRIC will exceed TEXT_BUFF_ARRAY_COUNT.
static const u8 sATypeMove_Table[NUMBER_OF_MON_TYPES][17] =
{
    [TYPE_NORMAL]   = _("κίνηση NORMAL"),
    [TYPE_FIGHTING] = _("κίνηση FIGHTING"),
    [TYPE_FLYING]   = _("κίνηση FLYING"),
    [TYPE_POISON]   = _("κίνηση POISON"),
    [TYPE_GROUND]   = _("κίνηση GROUND"),
    [TYPE_ROCK]     = _("κίνηση ROCK"),
    [TYPE_BUG]      = _("κίνηση BUG"),
    [TYPE_GHOST]    = _("κίνηση GHOST"),
    [TYPE_STEEL]    = _("κίνηση STEEL"),
    [TYPE_MYSTERY]  = _("κίνηση ???"),
    [TYPE_FIRE]     = _("κίνηση FIRE"),
    [TYPE_WATER]    = _("κίνηση WATER"),
    [TYPE_GRASS]    = _("κίνηση GRASS"),
    [TYPE_ELECTRIC] = _("κίνηση ELECTRIC"),
    [TYPE_PSYCHIC]  = _("κίνηση PSYCHIC"),
    [TYPE_ICE]      = _("κίνηση ICE"),
    [TYPE_DRAGON]   = _("κίνηση DRAGON"),
    [TYPE_DARK]     = _("κίνηση DARK")
};

const u8 gText_BattleTourney[] = _("ΤΟΥΡΝΟΥΑ ΜΑΧΗΣ");
static const u8 sText_Round1[] = _("Γύρος 1");
static const u8 sText_Round2[] = _("Γύρος 2");
static const u8 sText_Semifinal[] = _("Ημιτελικός");
static const u8 sText_Final[] = _("Τελικός");

const u8 *const gRoundsStringTable[DOME_ROUNDS_COUNT] =
{
    [DOME_ROUND1]    = sText_Round1,
    [DOME_ROUND2]    = sText_Round2,
    [DOME_SEMIFINAL] = sText_Semifinal,
    [DOME_FINAL]     = sText_Final
};

const u8 gText_TheGreatNewHope[] = _("Η νέα μεγάλη ελπίδα!\p");
const u8 gText_WillChampionshipDreamComeTrue[] = _("Θα γίνει το όνειρο πραγματικότητα;\p");
const u8 gText_AFormerChampion[] = _("Ένας πρώην ΠΡΩΤΑΘΛΗΤΗΣ!\p");
const u8 gText_ThePreviousChampion[] = _("Ο προηγούμενος ΠΡΩΤΑΘΛΗΤΗΣ!\p");
const u8 gText_TheUnbeatenChampion[] = _("Ο αήττητος ΠΡΩΤΑΘΛΗΤΗΣ!\p");
const u8 gText_PlayerMon1Name[] = _("{B_PLAYER_MON1_NAME}");
const u8 gText_Vs[] = _("VS");
const u8 gText_OpponentMon1Name[] = _("{B_OPPONENT_MON1_NAME}");
const u8 gText_Mind[] = _("Μυαλό");
const u8 gText_Skill[] = _("Τεχνική");
const u8 gText_Body[] = _("Σώμα");
const u8 gText_Judgment[] = _("{B_BUFF1}{CLEAR 13}Κρίση{CLEAR 13}{B_BUFF2}");
static const u8 sText_TwoTrainersSentPkmn[] = _("Ο {B_TRAINER1_CLASS} {B_TRAINER1_NAME} έστειλε\nτο {B_OPPONENT_MON1_NAME}!\pΟ {B_TRAINER2_CLASS} {B_TRAINER2_NAME} έστειλε\nτο {B_OPPONENT_MON2_NAME}!");
static const u8 sText_Trainer2SentOutPkmn[] = _("Ο {B_TRAINER2_CLASS} {B_TRAINER2_NAME} έστειλε\nτο {B_BUFF1}!");
static const u8 sText_TwoTrainersWantToBattle[] = _("Ο {B_TRAINER1_CLASS} {B_TRAINER1_NAME} και\nο {B_TRAINER2_CLASS} {B_TRAINER2_NAME}\lθέλουν να παλέψουν!\p");
static const u8 sText_InGamePartnerSentOutZGoN[] = _("Ο {B_PARTNER_CLASS} {B_PARTNER_NAME} έστειλε\nτο {B_PLAYER_MON2_NAME}!\lΠάμε, {B_PLAYER_MON1_NAME}!");
static const u8 sText_TwoInGameTrainersDefeated[] = _("Ο {B_TRAINER1_CLASS} {B_TRAINER1_NAME} και\nο {B_TRAINER2_CLASS} {B_TRAINER2_NAME}\lηττήθηκαν!\p");
static const u8 sText_Trainer2LoseText[] = _("{B_TRAINER2_LOSE_TEXT}");
static const u8 sText_PkmnIncapableOfPower[] = _("Το {B_ATK_NAME_WITH_PREFIX} δεν μπορεί\nνα χρησιμοποιήσει τη δύναμή του!");
static const u8 sText_GlintAppearsInEye[] = _("Μια λάμψη εμφανίζεται\nστα μάτια του {B_SCR_ACTIVE_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnGettingIntoPosition[] = _("Το {B_SCR_ACTIVE_NAME_WITH_PREFIX} παίρνει\nθέση!");
static const u8 sText_PkmnBeganGrowlingDeeply[] = _("Το {B_SCR_ACTIVE_NAME_WITH_PREFIX} γρύλισε δυνατά!");
static const u8 sText_PkmnEagerForMore[] = _("Το {B_SCR_ACTIVE_NAME_WITH_PREFIX} διψάει για μάχη!");

const u16 gBattlePalaceFlavorTextTable[] =
{
    [B_MSG_GLINT_IN_EYE]   = STRINGID_GLINTAPPEARSINEYE,
    [B_MSG_GETTING_IN_POS] = STRINGID_PKMNGETTINGINTOPOSITION,
    [B_MSG_GROWL_DEEPLY]   = STRINGID_PKMNBEGANGROWLINGDEEPLY,
    [B_MSG_EAGER_FOR_MORE] = STRINGID_PKMNEAGERFORMORE,
};

static const u8 sText_RefIfNothingIsDecided[] = _("ΔΙΑΙΤΗΤΗΣ: Αν δεν υπάρξει νικητής σε\n3 γύρους, θα πάμε σε απόφαση!");
static const u8 sText_RefThatsIt[] = _("ΔΙΑΙΤΗΤΗΣ: Αυτό ήταν! Θα πάμε σε\nαπόφαση για να βγει ο νικητής!");
static const u8 sText_RefJudgeMind[] = _("ΔΙΑΙΤΗΤΗΣ: Κατηγορία 1, Μυαλό!\nΤο POKéMON με το μεγαλύτερο θάρρος!\p");
static const u8 sText_RefJudgeSkill[] = _("ΔΙΑΙΤΗΤΗΣ: Κατηγορία 2, Τεχνική!\nΤο POKéMON με τις καλύτερες κινήσεις!\p");
static const u8 sText_RefJudgeBody[] = _("ΔΙΑΙΤΗΤΗΣ: Κατηγορία 3, Σώμα!\nΤο POKéMON με τη μεγαλύτερη αντοχή!\p");
static const u8 sText_RefPlayerWon[] = _("ΔΙΑΙΤΗΤΗΣ: Κρίση: {B_BUFF1} - {B_BUFF2}!\nΝικά το {B_PLAYER_MON1_NAME} ({B_PLAYER_NAME})!\p");
static const u8 sText_RefOpponentWon[] = _("ΔΙΑΙΤΗΤΗΣ: Κρίση: {B_BUFF1} - {B_BUFF2}!\nΝικά το {B_OPPONENT_MON1_NAME} ({B_TRAINER1_NAME})!\p");
static const u8 sText_RefDraw[] = _("ΔΙΑΙΤΗΤΗΣ: Κρίση: 3 με 3!\nΈχουμε ισοπαλία!\p");
static const u8 sText_DefeatedOpponentByReferee[] = _("Το {B_PLAYER_MON1_NAME} νίκησε\nτο {B_OPPONENT_MON1_NAME} με απόφαση ΔΙΑΙΤΗΤΗ!");
static const u8 sText_LostToOpponentByReferee[] = _("Το {B_PLAYER_MON1_NAME} έχασε από\nτο {B_OPPONENT_MON1_NAME} με απόφαση ΔΙΑΙΤΗΤΗ!");
static const u8 sText_TiedOpponentByReferee[] = _("Το {B_PLAYER_MON1_NAME} ισοπάλησε με\nτο {B_OPPONENT_MON1_NAME} με απόφαση ΔΙΑΙΤΗΤΗ!");
static const u8 sText_RefCommenceBattle[] = _("ΔΙΑΙΤΗΤΗΣ: {B_PLAYER_MON1_NAME} VS {B_OPPONENT_MON1_NAME}!\nΞεκινήστε τη μάχη!");

const u8 * const gRefereeStringsTable[] =
{
    [B_MSG_REF_NOTHING_IS_DECIDED] = sText_RefIfNothingIsDecided,
    [B_MSG_REF_THATS_IT]           = sText_RefThatsIt,
    [B_MSG_REF_JUDGE_MIND]         = sText_RefJudgeMind,
    [B_MSG_REF_JUDGE_SKILL]        = sText_RefJudgeSkill,
    [B_MSG_REF_JUDGE_BODY]         = sText_RefJudgeBody,
    [B_MSG_REF_PLAYER_WON]         = sText_RefPlayerWon,
    [B_MSG_REF_OPPONENT_WON]       = sText_RefOpponentWon,
    [B_MSG_REF_DRAW]               = sText_RefDraw,
    [B_MSG_REF_COMMENCE_BATTLE]    = sText_RefCommenceBattle,
};

static const u8 sText_QuestionForfeitMatch[] = _("Θέλεις να εγκαταλείψεις τον αγώνα\nκαι να φύγεις τώρα;");
static const u8 sText_ForfeitedMatch[] = _("Εγκατέλειψες τον αγώνα!");
static const u8 sText_Trainer1WinText[] = _("{B_TRAINER1_WIN_TEXT}");
static const u8 sText_Trainer2WinText[] = _("{B_TRAINER2_WIN_TEXT}");
static const u8 sText_Trainer1Fled[] = _("{PLAY_SE SE_FLEE}Ο {B_TRAINER1_CLASS} {B_TRAINER1_NAME} το 'σκασε!");
static const u8 sText_PlayerLostAgainstTrainer1[] = _("Ο Παίκτης έχασε από τον\n{B_TRAINER1_CLASS} {B_TRAINER1_NAME}!");
static const u8 sText_PlayerBattledToDrawTrainer1[] = _("Ο Παίκτης ήρθε ισοπαλία με τον\n{B_TRAINER1_CLASS} {B_TRAINER1_NAME}!");
const u8 gText_RecordBattleToPass[] = _("Θέλεις να καταγράψεις τη μάχη\nστο FRONTIER PASS;");
const u8 gText_BattleRecordedOnPass[] = _("Το αποτέλεσμα της μάχης\nκαταγράφηκε στο FRONTIER PASS.");
static const u8 sText_LinkTrainerWantsToBattlePause[] = _("Ο/Η {B_LINK_OPPONENT1_NAME}\nθέλει να παλέψετε!{PAUSE 49}");
static const u8 sText_TwoLinkTrainersWantToBattlePause[] = _("Ο/Η {B_LINK_OPPONENT1_NAME} και {B_LINK_OPPONENT2_NAME}\nθέλουν να παλέψουν!{PAUSE 49}");

// This is four lists of moves which use a different attack string in Japanese
// to the default. See the documentation for ChooseTypeOfMoveUsedString for more detail.
static const u16 sGrammarMoveUsedTable[] =
{
    MOVE_SWORDS_DANCE, MOVE_STRENGTH, MOVE_GROWTH,
    MOVE_HARDEN, MOVE_MINIMIZE, MOVE_SMOKESCREEN,
    MOVE_WITHDRAW, MOVE_DEFENSE_CURL, MOVE_EGG_BOMB,
    MOVE_SMOG, MOVE_BONE_CLUB, MOVE_FLASH, MOVE_SPLASH,
    MOVE_ACID_ARMOR, MOVE_BONEMERANG, MOVE_REST, MOVE_SHARPEN,
    MOVE_SUBSTITUTE, MOVE_MIND_READER, MOVE_SNORE,
    MOVE_PROTECT, MOVE_SPIKES, MOVE_ENDURE, MOVE_ROLLOUT,
    MOVE_SWAGGER, MOVE_SLEEP_TALK, MOVE_HIDDEN_POWER,
    MOVE_PSYCH_UP, MOVE_EXTREME_SPEED, MOVE_FOLLOW_ME,
    MOVE_TRICK, MOVE_ASSIST, MOVE_INGRAIN, MOVE_KNOCK_OFF,
    MOVE_CAMOUFLAGE, MOVE_ASTONISH, MOVE_ODOR_SLEUTH,
    MOVE_GRASS_WHISTLE, MOVE_SHEER_COLD, MOVE_MUDDY_WATER,
    MOVE_IRON_DEFENSE, MOVE_BOUNCE, 0,

    MOVE_TELEPORT, MOVE_RECOVER, MOVE_BIDE, MOVE_AMNESIA,
    MOVE_FLAIL, MOVE_TAUNT, MOVE_BULK_UP, 0,

    MOVE_MEDITATE, MOVE_AGILITY, MOVE_MIMIC, MOVE_DOUBLE_TEAM,
    MOVE_BARRAGE, MOVE_TRANSFORM, MOVE_STRUGGLE, MOVE_SCARY_FACE,
    MOVE_CHARGE, MOVE_WISH, MOVE_BRICK_BREAK, MOVE_YAWN,
    MOVE_FEATHER_DANCE, MOVE_TEETER_DANCE, MOVE_MUD_SPORT,
    MOVE_FAKE_TEARS, MOVE_WATER_SPORT, MOVE_CALM_MIND, 0,

    MOVE_POUND, MOVE_SCRATCH, MOVE_VICE_GRIP,
    MOVE_WING_ATTACK, MOVE_FLY, MOVE_BIND, MOVE_SLAM,
    MOVE_HORN_ATTACK, MOVE_WRAP, MOVE_THRASH, MOVE_TAIL_WHIP,
    MOVE_LEER, MOVE_BITE, MOVE_GROWL, MOVE_ROAR,
    MOVE_SING, MOVE_PECK, MOVE_ABSORB, MOVE_STRING_SHOT,
    MOVE_EARTHQUAKE, MOVE_FISSURE, MOVE_DIG, MOVE_TOXIC,
    MOVE_SCREECH, MOVE_METRONOME, MOVE_LICK, MOVE_CLAMP,
    MOVE_CONSTRICT, MOVE_POISON_GAS, MOVE_BUBBLE,
    MOVE_SLASH, MOVE_SPIDER_WEB, MOVE_NIGHTMARE, MOVE_CURSE,
    MOVE_FORESIGHT, MOVE_CHARM, MOVE_ATTRACT, MOVE_ROCK_SMASH,
    MOVE_UPROAR, MOVE_SPIT_UP, MOVE_SWALLOW, MOVE_TORMENT,
    MOVE_FLATTER, MOVE_ROLE_PLAY, MOVE_ENDEAVOR, MOVE_TICKLE,
    MOVE_COVET, 0
};

static const u8 sText_EmptyStatus[] = _("$$$$$$$");

static const struct BattleWindowText sTextOnWindowsInfo_Normal[] =
{
    [B_WIN_MSG] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_PROMPT] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_MENU] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    [B_WIN_DUMMY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP_REMAINING] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 1,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    [B_WIN_MOVE_TYPE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_YESNO] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = 32,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 2,
    },
    [B_WIN_VS_PLAYER] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_OPPONENT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_OUTCOME_DRAW] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 6,
    },
    [B_WIN_VS_OUTCOME_LEFT] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 6,
    },
    [B_WIN_VS_OUTCOME_RIGHT] = {
        .fillValue = PIXEL_FILL(0x0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 6,
    },
};

static const struct BattleWindowText sTextOnWindowsInfo_Arena[] =
{
    [B_WIN_MSG] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_PROMPT] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_MENU] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    [B_WIN_DUMMY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP_REMAINING] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 1,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    [B_WIN_MOVE_TYPE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_YESNO] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = 32,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 2,
    },
    [ARENA_WIN_PLAYER_NAME] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_VS] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_OPPONENT_NAME] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_MIND] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_SKILL] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_BODY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_JUDGMENT_TITLE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_JUDGMENT_TEXT] = {
        .fillValue = PIXEL_FILL(0x1),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .fgColor = 2,
        .bgColor = 1,
        .shadowColor = 3,
    },
};

static const struct BattleWindowText *const sBattleTextOnWindowsInfo[] =
{
    [B_WIN_TYPE_NORMAL] = sTextOnWindowsInfo_Normal,
    [B_WIN_TYPE_ARENA]  = sTextOnWindowsInfo_Arena
};

static const u8 sRecordedBattleTextSpeeds[] = {8, 4, 1, 0};

void BufferStringBattle(u16 stringID)
{
    s32 i;
    const u8 *stringPtr = NULL;

    gBattleMsgDataPtr = (struct BattleMsgData *)(&gBattleBufferA[gActiveBattler][4]);
    gLastUsedItem = gBattleMsgDataPtr->lastItem;
    gLastUsedAbility = gBattleMsgDataPtr->lastAbility;
    gBattleScripting.battler = gBattleMsgDataPtr->scrActive;
    *(&gBattleStruct->scriptPartyIdx) = gBattleMsgDataPtr->bakScriptPartyIdx;
    *(&gBattleStruct->hpScale) = gBattleMsgDataPtr->hpScale;
    gPotentialItemEffectBattler = gBattleMsgDataPtr->itemEffectBattler;
    *(&gBattleStruct->stringMoveType) = gBattleMsgDataPtr->moveType;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        sBattlerAbilities[i] = gBattleMsgDataPtr->abilities[i];
    }
    for (i = 0; i < TEXT_BUFF_ARRAY_COUNT; i++)
    {
        gBattleTextBuff1[i] = gBattleMsgDataPtr->textBuffs[0][i];
        gBattleTextBuff2[i] = gBattleMsgDataPtr->textBuffs[1][i];
        gBattleTextBuff3[i] = gBattleMsgDataPtr->textBuffs[2][i];
    }

    switch (stringID)
    {
    case STRINGID_INTROMSG: // first battle msg
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                {
                    stringPtr = sText_TwoTrainersWantToBattle;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                        stringPtr = sText_TwoLinkTrainersWantToBattlePause;
                    else
                        stringPtr = sText_TwoLinkTrainersWantToBattle;
                }
                else
                {
                    if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                        stringPtr = sText_Trainer1WantsToBattle;
                    else if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                        stringPtr = sText_LinkTrainerWantsToBattlePause;
                    else
                        stringPtr = sText_LinkTrainerWantsToBattle;
                }
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                    stringPtr = sText_TwoTrainersWantToBattle;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_TwoTrainersWantToBattle;
                else
                    stringPtr = sText_Trainer1WantsToBattle;
            }
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_LEGENDARY)
                stringPtr = sText_LegendaryPkmnAppeared;
            else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE) // interesting, looks like they had something planned for wild double battles
                stringPtr = sText_TwoWildPkmnAppeared;
            else if (gBattleTypeFlags & BATTLE_TYPE_WALLY_TUTORIAL)
                stringPtr = sText_WildPkmnAppearedPause;
            else
                stringPtr = sText_WildPkmnAppeared;
        }
        break;
    case STRINGID_INTROSENDOUT: // poke first send-out
        if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        {
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                    stringPtr = sText_InGamePartnerSentOutZGoN;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_GoTwoPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_LinkPartnerSentOutPkmnGoPkmn;
                else
                    stringPtr = sText_GoTwoPkmn;
            }
            else
            {
                stringPtr = sText_GoPkmn;
            }
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_TwoTrainersSentPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                    stringPtr = sText_TwoTrainersSentPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_TwoLinkTrainersSentOutPkmn;
                else if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
                    stringPtr = sText_LinkTrainerSentOutTwoPkmn;
                else
                    stringPtr = sText_Trainer1SentOutTwoPkmn;
            }
            else
            {
                if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK)))
                    stringPtr = sText_Trainer1SentOutPkmn;
                else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                    stringPtr = sText_Trainer1SentOutPkmn;
                else
                    stringPtr = sText_LinkTrainerSentOutPkmn;
            }
        }
        break;
    case STRINGID_RETURNMON: // sending poke to ball msg
        if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        {
            if (*(&gBattleStruct->hpScale) == 0)
                stringPtr = sText_PkmnThatsEnough;
            else if (*(&gBattleStruct->hpScale) == 1 || gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                stringPtr = sText_PkmnComeBack;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = sText_PkmnOkComeBack;
            else
                stringPtr = sText_PkmnGoodComeBack;
        }
        else
        {
            if (gTrainerBattleOpponent_A == TRAINER_LINK_OPPONENT || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_LinkTrainer2WithdrewPkmn;
                else
                    stringPtr = sText_LinkTrainer1WithdrewPkmn;
            }
            else
            {
                stringPtr = sText_Trainer1WithdrewPkmn;
            }
        }
        break;
    case STRINGID_SWITCHINMON: // switch-in msg
        if (GetBattlerSide(gBattleScripting.battler) == B_SIDE_PLAYER)
        {
            if (*(&gBattleStruct->hpScale) == 0 || gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                stringPtr = sText_GoPkmn2;
            else if (*(&gBattleStruct->hpScale) == 1)
                stringPtr = sText_DoItPkmn;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = sText_GoForItPkmn;
            else
                stringPtr = sText_YourFoesWeakGetEmPkmn;
        }
        else
        {
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                {
                    if (gBattleScripting.battler == 1)
                        stringPtr = sText_Trainer1SentOutPkmn2;
                    else
                        stringPtr = sText_Trainer2SentOutPkmn;
                }
                else
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                        stringPtr = sText_LinkTrainerMultiSentOutPkmn;
                    else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                        stringPtr = sText_Trainer1SentOutPkmn2;
                    else
                        stringPtr = sText_LinkTrainerSentOutPkmn2;
                }
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                {
                    if (gBattleScripting.battler == 1)
                        stringPtr = sText_Trainer1SentOutPkmn2;
                    else
                        stringPtr = sText_Trainer2SentOutPkmn;
                }
                else
                {
                    stringPtr = sText_Trainer1SentOutPkmn2;
                }
            }
        }
        break;
    case STRINGID_USEDMOVE: // Pokémon used a move msg
        ChooseMoveUsedParticle(gBattleTextBuff1); // buff1 doesn't appear in the string, leftover from japanese move names

        if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT)
            StringCopy(gBattleTextBuff2, sATypeMove_Table[*(&gBattleStruct->stringMoveType)]);
        else
            StringCopy(gBattleTextBuff2, gMoveNames[gBattleMsgDataPtr->currentMove]);

        ChooseTypeOfMoveUsedString(gBattleTextBuff2);
        stringPtr = sText_AttackerUsedX;
        break;
    case STRINGID_BATTLEEND: // battle end
        if (gBattleTextBuff1[0] & B_OUTCOME_LINK_BATTLE_RAN)
        {
            gBattleTextBuff1[0] &= ~(B_OUTCOME_LINK_BATTLE_RAN);
            if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTextBuff1[0] == B_OUTCOME_LOST || gBattleTextBuff1[0] == B_OUTCOME_DREW)
                stringPtr = sText_GotAwaySafely;
            else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                stringPtr = sText_TwoWildFled;
            else
                stringPtr = sText_WildFled;
        }
        else
        {
            if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                        stringPtr = sText_TwoInGameTrainersDefeated;
                    else
                        stringPtr = sText_TwoLinkTrainersDefeated;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostToTwo;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawVsTwo;
                    break;
                }
            }
            else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainerTrainer1;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstTrainer1;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawTrainer1;
                    break;
                }
            }
            else
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainer;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstLinkTrainer;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawLinkTrainer;
                    break;
                }
            }
        }
        break;
    default: // load a string from the table
        if (stringID >= BATTLESTRINGS_COUNT)
        {
            gDisplayedStringBattle[0] = EOS;
            return;
        }
        else
        {
            stringPtr = gBattleStringsTable[stringID - BATTLESTRINGS_TABLE_START];
        }
        break;
    }

    BattleStringExpandPlaceholdersToDisplayedString(stringPtr);
}

u32 BattleStringExpandPlaceholdersToDisplayedString(const u8 *src)
{
    BattleStringExpandPlaceholders(src, gDisplayedStringBattle);
}

static const u8 *TryGetStatusString(u8 *src)
{
    u32 i;
    u8 status[8];
    u32 chars1, chars2;
    u8 *statusPtr;

    memcpy(status, sText_EmptyStatus, min(ARRAY_COUNT(status), ARRAY_COUNT(sText_EmptyStatus)));

    statusPtr = status;
    for (i = 0; i < ARRAY_COUNT(status); i++)
    {
        if (*src == EOS) break; // one line required to match -g
        *statusPtr = *src;
        src++;
        statusPtr++;
    }

    chars1 = *(u32 *)(&status[0]);
    chars2 = *(u32 *)(&status[4]);

    for (i = 0; i < ARRAY_COUNT(gStatusConditionStringsTable); i++)
    {
        if (chars1 == *(u32 *)(&gStatusConditionStringsTable[i][0][0])
            && chars2 == *(u32 *)(&gStatusConditionStringsTable[i][0][4]))
            return gStatusConditionStringsTable[i][1];
    }
    return NULL;
}

#define HANDLE_NICKNAME_STRING_CASE(battlerId, monIndex)                \
    if (GetBattlerSide(battlerId) != B_SIDE_PLAYER)                     \
    {                                                                   \
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)                     \
            toCpy = sText_FoePkmnPrefix;                                \
        else                                                            \
            toCpy = sText_WildPkmnPrefix;                               \
        while (*toCpy != EOS)                                           \
        {                                                               \
            dst[dstID] = *toCpy;                                        \
            dstID++;                                                    \
            toCpy++;                                                    \
        }                                                               \
        GetMonData(&gEnemyParty[monIndex], MON_DATA_NICKNAME, text);    \
    }                                                                   \
    else                                                                \
    {                                                                   \
        GetMonData(&gPlayerParty[monIndex], MON_DATA_NICKNAME, text);   \
    }                                                                   \
    StringGet_Nickname(text);                                           \
    toCpy = text;

// Ensure the defined length for an item name can contain the full defined length of a berry name.
// This ensures that custom Enigma Berry names will fit in the text buffer at the top of BattleStringExpandPlaceholders.
STATIC_ASSERT(BERRY_NAME_LENGTH + ARRAY_COUNT(sText_BerrySuffix) <= ITEM_NAME_LENGTH, BerryNameTooLong);

u32 BattleStringExpandPlaceholders(const u8 *src, u8 *dst)
{
    u32 dstID = 0; // if they used dstID, why not use srcID as well?
    const u8 *toCpy = NULL;
    // This buffer may hold either the name of a trainer, Pokémon, or item.
    u8 text[max(max(max(32, TRAINER_NAME_LENGTH + 1), POKEMON_NAME_LENGTH + 1), ITEM_NAME_LENGTH)];
    u8 multiplayerId;
    s32 i;

    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
        multiplayerId = gRecordedBattleMultiplayerId;
    else
        multiplayerId = GetMultiplayerId();

    while (*src != EOS)
    {
        if (*src == PLACEHOLDER_BEGIN)
        {
            src++;
            switch (*src)
            {
            case B_TXT_BUFF1:
                if (gBattleTextBuff1[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff1, gStringVar1);
                    toCpy = gStringVar1;
                }
                else
                {
                    toCpy = TryGetStatusString(gBattleTextBuff1);
                    if (toCpy == NULL)
                        toCpy = gBattleTextBuff1;
                }
                break;
            case B_TXT_BUFF2:
                if (gBattleTextBuff2[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff2, gStringVar2);
                    toCpy = gStringVar2;
                }
                else
                    toCpy = gBattleTextBuff2;
                break;
            case B_TXT_BUFF3:
                if (gBattleTextBuff3[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff3, gStringVar3);
                    toCpy = gStringVar3;
                }
                else
                    toCpy = gBattleTextBuff3;
                break;
            case B_TXT_COPY_VAR_1:
                toCpy = gStringVar1;
                break;
            case B_TXT_COPY_VAR_2:
                toCpy = gStringVar2;
                break;
            case B_TXT_COPY_VAR_3:
                toCpy = gStringVar3;
                break;
            case B_TXT_PLAYER_MON1_NAME: // first player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_OPPONENT_MON1_NAME: // first enemy poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_PLAYER_MON2_NAME: // second player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_OPPONENT_MON2_NAME: // second enemy poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_LINK_PLAYER_MON1_NAME: // link first player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_LINK_OPPONENT_MON1_NAME: // link first opponent poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id ^ 1]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_LINK_PLAYER_MON2_NAME: // link second player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id ^ 2]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_LINK_OPPONENT_MON2_NAME: // link second opponent poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id ^ 3]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX_MON1: // attacker name with prefix, only battlerId 0/1
                HANDLE_NICKNAME_STRING_CASE(gBattlerAttacker,
                                            gBattlerPartyIndexes[GetBattlerAtPosition(GET_BATTLER_SIDE(gBattlerAttacker))])
                break;
            case B_TXT_ATK_PARTNER_NAME: // attacker partner name
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    GetMonData(&gPlayerParty[gBattlerPartyIndexes[GetBattlerAtPosition(GET_BATTLER_SIDE(gBattlerAttacker)) + 2]], MON_DATA_NICKNAME, text);
                else
                    GetMonData(&gEnemyParty[gBattlerPartyIndexes[GetBattlerAtPosition(GET_BATTLER_SIDE(gBattlerAttacker)) + 2]], MON_DATA_NICKNAME, text);

                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX: // attacker name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattlerAttacker, gBattlerPartyIndexes[gBattlerAttacker])
                break;
            case B_TXT_DEF_NAME_WITH_PREFIX: // target name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattlerTarget, gBattlerPartyIndexes[gBattlerTarget])
                break;
            case B_TXT_EFF_NAME_WITH_PREFIX: // effect battlerId name with prefix
                HANDLE_NICKNAME_STRING_CASE(gEffectBattler, gBattlerPartyIndexes[gEffectBattler])
                break;
            case B_TXT_ACTIVE_NAME_WITH_PREFIX: // active battlerId name with prefix
                HANDLE_NICKNAME_STRING_CASE(gActiveBattler, gBattlerPartyIndexes[gActiveBattler])
                break;
            case B_TXT_SCR_ACTIVE_NAME_WITH_PREFIX: // scripting active battlerId name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattleScripting.battler, gBattlerPartyIndexes[gBattleScripting.battler])
                break;
            case B_TXT_CURRENT_MOVE: // current move name
                if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT)
                    toCpy = sATypeMove_Table[gBattleStruct->stringMoveType];
                else
                    toCpy = gMoveNames[gBattleMsgDataPtr->currentMove];
                break;
            case B_TXT_LAST_MOVE: // originally used move name
                if (gBattleMsgDataPtr->originallyUsedMove >= MOVES_COUNT)
                    toCpy = sATypeMove_Table[gBattleStruct->stringMoveType];
                else
                    toCpy = gMoveNames[gBattleMsgDataPtr->originallyUsedMove];
                break;
            case B_TXT_LAST_ITEM: // last used item
                if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
                {
                    if (gLastUsedItem == ITEM_ENIGMA_BERRY)
                    {
                        if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
                        {
                            if ((gBattleScripting.multiplayerId != 0 && (gPotentialItemEffectBattler & BIT_SIDE))
                                || (gBattleScripting.multiplayerId == 0 && !(gPotentialItemEffectBattler & BIT_SIDE)))
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                            {
                                toCpy = sText_EnigmaBerry;
                            }
                        }
                        else
                        {
                            if (gLinkPlayers[gBattleScripting.multiplayerId].id == gPotentialItemEffectBattler)
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                                toCpy = sText_EnigmaBerry;
                        }
                    }
                    else
                    {
                        CopyItemName(gLastUsedItem, text);
                        toCpy = text;
                    }
                }
                else
                {
                    CopyItemName(gLastUsedItem, text);
                    toCpy = text;
                }
                break;
            case B_TXT_LAST_ABILITY: // last used ability
                toCpy = gAbilityNames[gLastUsedAbility];
                break;
            case B_TXT_ATK_ABILITY: // attacker ability
                toCpy = gAbilityNames[sBattlerAbilities[gBattlerAttacker]];
                break;
            case B_TXT_DEF_ABILITY: // target ability
                toCpy = gAbilityNames[sBattlerAbilities[gBattlerTarget]];
                break;
            case B_TXT_SCR_ACTIVE_ABILITY: // scripting active ability
                toCpy = gAbilityNames[sBattlerAbilities[gBattleScripting.battler]];
                break;
            case B_TXT_EFF_ABILITY: // effect battlerId ability
                toCpy = gAbilityNames[sBattlerAbilities[gEffectBattler]];
                break;
            case B_TXT_TRAINER1_CLASS: // trainer class name
                if (gBattleTypeFlags & BATTLE_TYPE_SECRET_BASE)
                    toCpy = gTrainerClassNames[GetSecretBaseTrainerClass()];
                else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                    toCpy = gTrainerClassNames[GetUnionRoomTrainerClass()];
                else if (gTrainerBattleOpponent_A == TRAINER_FRONTIER_BRAIN)
                    toCpy = gTrainerClassNames[GetFrontierBrainTrainerClass()];
                else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                    toCpy = gTrainerClassNames[GetFrontierOpponentClass(gTrainerBattleOpponent_A)];
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                    toCpy = gTrainerClassNames[GetTrainerHillOpponentClass(gTrainerBattleOpponent_A)];
                else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
                    toCpy = gTrainerClassNames[GetEreaderTrainerClassId()];
                else
                    toCpy = gTrainerClassNames[gTrainers[gTrainerBattleOpponent_A].trainerClass];
                break;
            case B_TXT_TRAINER1_NAME: // trainer1 name
                if (gBattleTypeFlags & BATTLE_TYPE_SECRET_BASE)
                {
                    for (i = 0; i < (s32) ARRAY_COUNT(gBattleResources->secretBase->trainerName); i++)
                        text[i] = gBattleResources->secretBase->trainerName[i];
                    text[i] = EOS;
                    ConvertInternationalString(text, gBattleResources->secretBase->language);
                    toCpy = text;
                }
                else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                {
                    toCpy = gLinkPlayers[multiplayerId ^ BIT_SIDE].name;
                }
                else if (gTrainerBattleOpponent_A == TRAINER_FRONTIER_BRAIN)
                {
                    CopyFrontierBrainTrainerName(text);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    GetFrontierTrainerName(text, gTrainerBattleOpponent_A);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    GetTrainerHillTrainerName(text, gTrainerBattleOpponent_A);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
                {
                    GetEreaderTrainerName(text);
                    toCpy = text;
                }
                else
                {
                    toCpy = gTrainers[gTrainerBattleOpponent_A].trainerName;
                }
                break;
            case B_TXT_LINK_PLAYER_NAME: // link player name
                toCpy = gLinkPlayers[multiplayerId].name;
                break;
            case B_TXT_LINK_PARTNER_NAME: // link partner name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_PARTNER(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_OPPONENT1_NAME: // link opponent 1 name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_OPPOSITE(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_OPPONENT2_NAME: // link opponent 2 name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_PARTNER(BATTLE_OPPOSITE(gLinkPlayers[multiplayerId].id)))].name;
                break;
            case B_TXT_LINK_SCR_TRAINER_NAME: // link scripting active name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(gBattleScripting.battler)].name;
                break;
            case B_TXT_PLAYER_NAME: // player name
                if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                    toCpy = gLinkPlayers[0].name;
                else
                    toCpy = gSaveBlock2Ptr->playerName;
                break;
            case B_TXT_TRAINER1_LOSE_TEXT: // trainerA lose text
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_WON_TEXT, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_WON, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerALoseText();
                }
                break;
            case B_TXT_TRAINER1_WIN_TEXT: // trainerA win text
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_LOST_TEXT, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_LOST, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                break;
            case B_TXT_26: // ?
                HANDLE_NICKNAME_STRING_CASE(gBattleScripting.battler, *(&gBattleStruct->scriptPartyIdx))
                break;
            case B_TXT_PC_CREATOR_NAME: // lanette pc
                if (FlagGet(FLAG_SYS_PC_LANETTE))
                    toCpy = sText_Lanettes;
                else
                    toCpy = sText_Someones;
                break;
            case B_TXT_ATK_PREFIX2:
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_TXT_DEF_PREFIX2:
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_TXT_ATK_PREFIX1:
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_TXT_DEF_PREFIX1:
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_TXT_ATK_PREFIX3:
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break;
            case B_TXT_DEF_PREFIX3:
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break;
            case B_TXT_TRAINER2_CLASS:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                    toCpy = gTrainerClassNames[GetFrontierOpponentClass(gTrainerBattleOpponent_B)];
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                    toCpy = gTrainerClassNames[GetTrainerHillOpponentClass(gTrainerBattleOpponent_B)];
                else
                    toCpy = gTrainerClassNames[gTrainers[gTrainerBattleOpponent_B].trainerClass];
                break;
            case B_TXT_TRAINER2_NAME:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    GetFrontierTrainerName(text, gTrainerBattleOpponent_B);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    GetTrainerHillTrainerName(text, gTrainerBattleOpponent_B);
                    toCpy = text;
                }
                else
                {
                    toCpy = gTrainers[gTrainerBattleOpponent_B].trainerName;
                }
                break;
            case B_TXT_TRAINER2_LOSE_TEXT:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_WON_TEXT, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_WON, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerBLoseText();
                }
                break;
            case B_TXT_TRAINER2_WIN_TEXT:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_LOST_TEXT, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_LOST, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                break;
            case B_TXT_PARTNER_CLASS:
                toCpy = gTrainerClassNames[GetFrontierOpponentClass(gPartnerTrainerId)];
                break;
            case B_TXT_PARTNER_NAME:
                GetFrontierTrainerName(text, gPartnerTrainerId);
                toCpy = text;
                break;
            }

            // missing if (toCpy != NULL) check
            while (*toCpy != EOS)
            {
                dst[dstID] = *toCpy;
                dstID++;
                toCpy++;
            }
            if (*src == B_TXT_TRAINER1_LOSE_TEXT || *src == B_TXT_TRAINER2_LOSE_TEXT
                || *src == B_TXT_TRAINER1_WIN_TEXT || *src == B_TXT_TRAINER2_WIN_TEXT)
            {
                dst[dstID] = EXT_CTRL_CODE_BEGIN;
                dstID++;
                dst[dstID] = EXT_CTRL_CODE_PAUSE_UNTIL_PRESS;
                dstID++;
            }
        }
        else
        {
            dst[dstID] = *src;
            dstID++;
        }
        src++;
    }

    dst[dstID] = *src;
    dstID++;

    return dstID;
}

static void ExpandBattleTextBuffPlaceholders(const u8 *src, u8 *dst)
{
    u32 srcID = 1;
    u32 value = 0;
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    u16 hword;

    *dst = EOS;
    while (src[srcID] != B_BUFF_EOS)
    {
        switch (src[srcID])
        {
        case B_BUFF_STRING: // battle string
            hword = T1_READ_16(&src[srcID + 1]);
            StringAppend(dst, gBattleStringsTable[hword - BATTLESTRINGS_TABLE_START]);
            srcID += 3;
            break;
        case B_BUFF_NUMBER: // int to string
            switch (src[srcID + 1])
            {
            case 1:
                value = src[srcID + 3];
                break;
            case 2:
                value = T1_READ_16(&src[srcID + 3]);
                break;
            case 4:
                value = T1_READ_32(&src[srcID + 3]);
                break;
            }
            ConvertIntToDecimalStringN(dst, value, STR_CONV_MODE_LEFT_ALIGN, src[srcID + 2]);
            srcID += src[srcID + 1] + 3;
            break;
        case B_BUFF_MOVE: // move name
            StringAppend(dst, gMoveNames[T1_READ_16(&src[srcID + 1])]);
            srcID += 3;
            break;
        case B_BUFF_TYPE: // type name
            StringAppend(dst, gTypeNames[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_MON_NICK_WITH_PREFIX: // poke nick with prefix
            if (GetBattlerSide(src[srcID + 1]) == B_SIDE_PLAYER)
            {
                GetMonData(&gPlayerParty[src[srcID + 2]], MON_DATA_NICKNAME, nickname);
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                    StringAppend(dst, sText_FoePkmnPrefix);
                else
                    StringAppend(dst, sText_WildPkmnPrefix);

                GetMonData(&gEnemyParty[src[srcID + 2]], MON_DATA_NICKNAME, nickname);
            }
            StringGet_Nickname(nickname);
            StringAppend(dst, nickname);
            srcID += 3;
            break;
        case B_BUFF_STAT: // stats
            StringAppend(dst, gStatNamesTable[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_SPECIES: // species name
            GetSpeciesName(dst, T1_READ_16(&src[srcID + 1]));
            srcID += 3;
            break;
        case B_BUFF_MON_NICK: // poke nick without prefix
            if (GetBattlerSide(src[srcID + 1]) == B_SIDE_PLAYER)
                GetMonData(&gPlayerParty[src[srcID + 2]], MON_DATA_NICKNAME, dst);
            else
                GetMonData(&gEnemyParty[src[srcID + 2]], MON_DATA_NICKNAME, dst);
            StringGet_Nickname(dst);
            srcID += 3;
            break;
        case B_BUFF_NEGATIVE_FLAVOR: // flavor table
            StringAppend(dst, gPokeblockWasTooXStringTable[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_ABILITY: // ability names
            StringAppend(dst, gAbilityNames[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_ITEM: // item name
            hword = T1_READ_16(&src[srcID + 1]);
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (hword == ITEM_ENIGMA_BERRY)
                {
                    if (gLinkPlayers[gBattleScripting.multiplayerId].id == gPotentialItemEffectBattler)
                    {
                        StringCopy(dst, gEnigmaBerries[gPotentialItemEffectBattler].name);
                        StringAppend(dst, sText_BerrySuffix);
                    }
                    else
                    {
                        StringAppend(dst, sText_EnigmaBerry);
                    }
                }
                else
                {
                    CopyItemName(hword, dst);
                }
            }
            else
            {
                CopyItemName(hword, dst);
            }
            srcID += 3;
            break;
        }
    }
}

// Loads one of two text strings into the provided buffer. This is functionally
// unused, since the value loaded into the buffer is not read; it loaded one of
// two particles (either "は" or "の") which works in tandem with ChooseTypeOfMoveUsedString
// below to effect changes in the meaning of the line.
static void ChooseMoveUsedParticle(u8 *textBuff)
{
    s32 counter = 0;
    u32 i = 0;

    while (counter != MAX_MON_MOVES)
    {
        if (sGrammarMoveUsedTable[i] == 0)
            counter++;
        if (sGrammarMoveUsedTable[i++] == gBattleMsgDataPtr->currentMove)
            break;
    }

    if (counter >= 0)
    {
        if (counter <= 2)
            StringCopy(textBuff, sText_SpaceIs); // is
        else if (counter <= MAX_MON_MOVES)
            StringCopy(textBuff, sText_ApostropheS); // 's
    }
}

// Appends "!" to the text buffer `dst`. In the original Japanese this looked
// into the table of moves at sGrammarMoveUsedTable and varied the line accordingly.
//
// sText_ExclamationMark was a plain "!", used for any attack not on the list.
// It resulted in the translation "<NAME>'s <ATTACK>!".
//
// sText_ExclamationMark2 was "を つかった！". This resulted in the translation
// "<NAME> used <ATTACK>!", which was used for all attacks in English.
//
// sText_ExclamationMark3 was "した！". This was used for those moves whose
// names were verbs, such as Recover, and resulted in translations like "<NAME>
// recovered itself!".
//
// sText_ExclamationMark4 was "を した！" This resulted in a translation of
// "<NAME> did an <ATTACK>!".
//
// sText_ExclamationMark5 was " こうげき！" This resulted in a translation of
// "<NAME>'s <ATTACK> attack!".
static void ChooseTypeOfMoveUsedString(u8 *dst)
{
    s32 counter = 0;
    s32 i = 0;

    while (*dst != EOS)
        dst++;

    while (counter != MAX_MON_MOVES)
    {
        if (sGrammarMoveUsedTable[i] == MOVE_NONE)
            counter++;
        if (sGrammarMoveUsedTable[i++] == gBattleMsgDataPtr->currentMove)
            break;
    }

    switch (counter)
    {
    case 0:
        StringCopy(dst, sText_ExclamationMark);
        break;
    case 1:
        StringCopy(dst, sText_ExclamationMark2);
        break;
    case 2:
        StringCopy(dst, sText_ExclamationMark3);
        break;
    case 3:
        StringCopy(dst, sText_ExclamationMark4);
        break;
    case 4:
        StringCopy(dst, sText_ExclamationMark5);
        break;
    }
}

void BattlePutTextOnWindow(const u8 *text, u8 windowId)
{
    const struct BattleWindowText *textInfo = sBattleTextOnWindowsInfo[gBattleScripting.windowsType];
    bool32 copyToVram;
    struct TextPrinterTemplate printerTemplate;
    u8 speed;

    if (windowId & B_WIN_COPYTOVRAM)
    {
        windowId &= ~B_WIN_COPYTOVRAM;
        copyToVram = FALSE;
    }
    else
    {
        FillWindowPixelBuffer(windowId, textInfo[windowId].fillValue);
        copyToVram = TRUE;
    }

    printerTemplate.currentChar = text;
    printerTemplate.windowId = windowId;
    printerTemplate.fontId = textInfo[windowId].fontId;
    printerTemplate.x = textInfo[windowId].x;
    printerTemplate.y = textInfo[windowId].y;
    printerTemplate.currentX = printerTemplate.x;
    printerTemplate.currentY = printerTemplate.y;
    printerTemplate.letterSpacing = textInfo[windowId].letterSpacing;
    printerTemplate.lineSpacing = textInfo[windowId].lineSpacing;
    printerTemplate.unk = 0;
    printerTemplate.fgColor = textInfo[windowId].fgColor;
    printerTemplate.bgColor = textInfo[windowId].bgColor;
    printerTemplate.shadowColor = textInfo[windowId].shadowColor;

    if (printerTemplate.x == 0xFF)
    {
        u32 width = GetBattleWindowTemplatePixelWidth(gBattleScripting.windowsType, windowId);
        s32 alignX = GetStringCenterAlignXOffsetWithLetterSpacing(printerTemplate.fontId, printerTemplate.currentChar, width, printerTemplate.letterSpacing);
        printerTemplate.x = printerTemplate.currentX = alignX;
    }

    if (windowId == ARENA_WIN_JUDGMENT_TEXT)
        gTextFlags.useAlternateDownArrow = FALSE;
    else
        gTextFlags.useAlternateDownArrow = TRUE;

    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED))
        gTextFlags.autoScroll = TRUE;
    else
        gTextFlags.autoScroll = FALSE;

    if (windowId == B_WIN_MSG || windowId == ARENA_WIN_JUDGMENT_TEXT)
    {
        if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            speed = 1;
        else if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            speed = sRecordedBattleTextSpeeds[GetTextSpeedInRecordedBattle()];
        else
            speed = GetPlayerTextSpeedDelay();

        gTextFlags.canABSpeedUpPrint = 1;
    }
    else
    {
        speed = textInfo[windowId].speed;
        gTextFlags.canABSpeedUpPrint = 0;
    }

    AddTextPrinter(&printerTemplate, speed, NULL);

    if (copyToVram)
    {
        PutWindowTilemap(windowId);
        CopyWindowToVram(windowId, COPYWIN_FULL);
    }
}

void SetPpNumbersPaletteInMoveSelection(void)
{
    struct ChooseMoveStruct *chooseMoveStruct = (struct ChooseMoveStruct *)(&gBattleBufferA[gActiveBattler][4]);
    const u16 *palPtr = gPPTextPalette;
    u8 var = GetCurrentPpToMaxPpState(chooseMoveStruct->currentPp[gMoveSelectionCursor[gActiveBattler]],
                         chooseMoveStruct->maxPp[gMoveSelectionCursor[gActiveBattler]]);

    gPlttBufferUnfaded[BG_PLTT_ID(5) + 12] = palPtr[(var * 2) + 0];
    gPlttBufferUnfaded[BG_PLTT_ID(5) + 11] = palPtr[(var * 2) + 1];

    CpuCopy16(&gPlttBufferUnfaded[BG_PLTT_ID(5) + 12], &gPlttBufferFaded[BG_PLTT_ID(5) + 12], PLTT_SIZEOF(1));
    CpuCopy16(&gPlttBufferUnfaded[BG_PLTT_ID(5) + 11], &gPlttBufferFaded[BG_PLTT_ID(5) + 11], PLTT_SIZEOF(1));
}

u8 GetCurrentPpToMaxPpState(u8 currentPp, u8 maxPp)
{
    if (maxPp == currentPp)
    {
        return 3;
    }
    else if (maxPp <= 2)
    {
        if (currentPp > 1)
            return 3;
        else
            return 2 - currentPp;
    }
    else if (maxPp <= 7)
    {
        if (currentPp > 2)
            return 3;
        else
            return 2 - currentPp;
    }
    else
    {
        if (currentPp == 0)
            return 2;
        if (currentPp <= maxPp / 4)
            return 1;
        if (currentPp > maxPp / 2)
            return 3;
    }

    return 0;
}
