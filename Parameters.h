#pragma once

enum FTFlangerParameter
{
    kFTFlangerParameter_Feedback = 0,
    kFTFlangerParameter_WetDry,
    kFTFlangerParameter_ModulationRate,
    kFTFlangerParameter_ModulationDepth,
    kFTFlangerParameter_RateOffset,
    kFTFlangerParameter_PhaseOffset,
    kFTFlangerParameter_TotalNumParameters
};

static String FTFlangerParameterID [ kFTFlangerParameter_TotalNumParameters ] =
{
    "Feedback",
    "Wet / Dry",
    "Modulation Rate",
    "Modulation Depth",
    "Rate Offset",
    "Phase Offset"
};

static String FTFlangerParameterLabel [ kFTFlangerParameter_TotalNumParameters ] =
{
    "Feedback",
    "Wet/Dry",
    "Modulation Rate",
    "Modulation Depth",
    "Rate Offset",
    "Phase Offset"
};

static float FTFlangerParameterDefaultValue [ kFTFlangerParameter_TotalNumParameters ] =
{
    0.5f,
    0.5f,
    0.25f,
    0.5f,
    0.0f,
    0.0f
};
