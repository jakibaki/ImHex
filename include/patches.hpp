#pragma once

#include <hex.hpp>

#include <map>
#include <vector>

namespace hex {

    using Patches = std::map<u64, u8>;

    std::vector<u8> generateIPSPatch(const Patches &patches);
    std::vector<u8> generateIPS32Patch(const Patches &patches);

}