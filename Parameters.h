#pragma once

enum FTFlangerParameter
{
    kFTFlangerParameter_Feedback = 0,
    kFTFlangerParameter_WetDry,
    kFTFlangerParameter_ModulationRate,
    kFTFlangerParameter_ModulationDepth,
    kFTFlangerParameter_TotalNumParameters
};

static String FTFlangerParameterID [ kFTFlangerParameter_TotalNumParameters ] =
{
    "Feedback",
    "Wet / Dry",
    "Modulation Rate",
    "Modulation Depth"
};

static String FTFlangerParameterLabel [ kFTFlangerParameter_TotalNumParameters ] =
{
    "Feedback",
    "Wet/Dry",
    "Modulation Rate",
    "Modulation Depth"
};

static float FTFlangerParameterDefaultValue [ kFTFlangerParameter_TotalNumParameters ] =
{
    0.5f,
    0.5f,
    0.25f,
    0.5f
};