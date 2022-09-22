#include "main.hpp"
#include "QolourSwitcherHooks.hpp"
#include "QolourSwitcherConfig.hpp"

#include "GlobalNamespace/PlayerDataModel.hpp"
#include "GlobalNamespace/PlayerData.hpp"
#include "GlobalNamespace/ColorScheme.hpp"
#include "GlobalNamespace/ColorSchemesSettings.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"

#include "System/Collections/Generic/Dictionary_2.hpp"

#include "questui/shared/QuestUI.hpp"
#include "UnityEngine/GameObject.hpp"

using namespace QuestUI;
using namespace GlobalNamespace;
using namespace UnityEngine;

GameObject *leftSaberScreen;
GameObject *rightSaberScreen;
bool isEnabled = false;

MAKE_AUTO_HOOK_MATCH(PauseMenuManager_ShowMenu, &PauseMenuManager::ShowMenu, void, PauseMenuManager *self)
{
    PauseMenuManager_ShowMenu(self);

    auto playerDataModel = Object::FindObjectOfType<PlayerDataModel *>();
    auto playerData = playerDataModel->playerData;
    auto colourScheme = playerData->colorSchemesSettings->GetColorSchemeForId(playerData->colorSchemesSettings->selectedColorSchemeId);

    leftSaberScreen = BeatSaberUI::CreateFloatingScreen(Vector2(10.0f, 10.0f), Vector3(-1.2f, 2.8f, 2.2f), Vector3(-35.0f, -15.0f, 0.0f), 0.0f, false, false);
    rightSaberScreen = BeatSaberUI::CreateFloatingScreen(Vector2(10.0f, 10.0f), Vector3(1.2f, 2.8f, 2.2f), Vector3(-35.0f, 15.0f, 0.0f), 0.0f, false, false);

    BeatSaberUI::CreateText(leftSaberScreen->get_transform(), "Left Saber Colour!", Vector2(17.5f, 0.0f));

    BeatSaberUI::CreateColorPicker(leftSaberScreen->get_transform(), "", colourScheme->get_saberAColor(), [colourScheme](Color color) 
    {
        colourScheme->saberAColor = color;
        getBareModConfig().LeftSaberColour.SetValue(color);
        getBareModConfig().isUpdated.SetValue(true);
    });


    BeatSaberUI::CreateText(rightSaberScreen->get_transform(), "Right Saber Colour!", Vector2(15.0f, 0.0f));

    BeatSaberUI::CreateColorPicker(rightSaberScreen->get_transform(), "", colourScheme->get_saberBColor(), [colourScheme](Color color) 
    {
        colourScheme->saberBColor = color;
        getBareModConfig().LeftSaberColour.SetValue(color);
        getBareModConfig().isUpdated.SetValue(true);
    });
}


MAKE_AUTO_HOOK_MATCH(PauseMenuManager_ContinueButtonPressed, &GlobalNamespace::PauseMenuManager::ContinueButtonPressed, void, GlobalNamespace::PauseMenuManager *self) {
    PauseMenuManager_ContinueButtonPressed(self);
    getLogger().info("Disabling Colour Picker!");
    leftSaberScreen->SetActive(false);
    rightSaberScreen->SetActive(false);
}

MAKE_AUTO_HOOK_MATCH(PauseMenuManager_MenuButtonPressed, &GlobalNamespace::PauseMenuManager::MenuButtonPressed, void, GlobalNamespace::PauseMenuManager *self) {
    PauseMenuManager_MenuButtonPressed(self);
    leftSaberScreen->SetActive(false);
    rightSaberScreen->SetActive(false);
}

MAKE_AUTO_HOOK_MATCH(PauseMenuManager_RestartButtonPressed, &GlobalNamespace::PauseMenuManager::RestartButtonPressed, void, GlobalNamespace::PauseMenuManager *self) {
    PauseMenuManager_RestartButtonPressed(self);
    leftSaberScreen->SetActive(false);
    rightSaberScreen->SetActive(false);
}