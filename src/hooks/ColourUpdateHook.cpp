#include "main.hpp"

#include "GlobalNamespace/BeatEffectSpawner.hpp"
#include "QolourSwitcherConfig.hpp"
#include "QolourSwitcherHooks.hpp"
#include "GlobalNamespace/SaberType.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "chroma/shared/SaberAPI.hpp"
#include "chroma/shared/NoteAPI.hpp"
#include "GlobalNamespace/SaberManager.hpp"
#include "GlobalNamespace/PlayerDataModel.hpp"
#include "GlobalNamespace/PlayerData.hpp"
#include "GlobalNamespace/ColorScheme.hpp"
#include "GlobalNamespace/ColorSchemesSettings.hpp"
#include "System/Collections/Generic/Dictionary_2.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/SaberModelController.hpp"

using namespace GlobalNamespace;
using namespace QuestUI;
using namespace UnityEngine;
using namespace Chroma;

MAKE_AUTO_HOOK_MATCH(BeatEffectSpawner_Update, &BeatEffectSpawner::Update, void, BeatEffectSpawner *self)
{
    BeatEffectSpawner_Update(self);

    auto playerDataModel = UnityEngine::Object::FindObjectOfType<PlayerDataModel *>();
    auto playerData = playerDataModel->playerData;
    auto colorScheme = playerData->colorSchemesSettings->GetColorSchemeForId(playerData->colorSchemesSettings->selectedColorSchemeId);

    auto saberA = colorScheme->saberAColor;
    auto saberB = colorScheme->saberBColor;

    auto saberManager = UnityEngine::Object::FindObjectOfType<SaberManager *>(); 
    auto leftSaberModelController = saberManager->get_leftSaber()->GetComponent<SaberModelController *>();
    auto rightSaberModelController = saberManager->get_rightSaber()->GetComponent<SaberModelController *>();

    getLogger().info("Updating Colours");
    //SaberAPI::setSaberColorable    Color(getBareModConfig().LeftSaberColour.GetValue())
    SaberAPI::setSaberColorSafe(leftSaberModelController, std::make_optional(saberA));
}