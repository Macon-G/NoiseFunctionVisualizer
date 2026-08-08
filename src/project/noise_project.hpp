#pragma once

#include "noise/function_registry.hpp"
#include "noise/modifiers/fbm.hpp"
#include "noise/worley_registry.hpp"

#include <cstdint>

struct NoiseProject {
    Noise::Registry::FunctionType function_type =
        Noise::Registry::FunctionType::Perlin;

    std::uint32_t seed = 0;
    float scale = 0.02f;

    Noise::Functions::WorleyDistanceMetric worley_distance =
        Noise::Functions::WorleyDistanceMetric::EUCLIDEAN;
    Noise::Functions::WorleyOutputMode worley_output =
        Noise::Functions::WorleyOutputMode::F1;

    Noise::Modifiers::FBMParameters fbm_params{};
};