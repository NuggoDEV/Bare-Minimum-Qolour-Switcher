#pragma once
#include "config-utils/shared/config-utils.hpp"
using namespace UnityEngine;

DECLARE_CONFIG(BareModConfig,
    CONFIG_VALUE(LeftSaberColour, Color, "", Color(0, 0, 0, 0));
    CONFIG_VALUE(RightSaberColour, Color, "", Color(0, 0, 0, 0));

    CONFIG_VALUE(isUpdated, bool, "", false);

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(LeftSaberColour);
        CONFIG_INIT_VALUE(RightSaberColour);
        CONFIG_INIT_VALUE(isUpdated);
    )
)