#pragma once

#include "platformBackend.hpp"

namespace bloom::ui::backends {

    class InputBackend : public PlatformBackend {
      public:
        InputBackend() = default;
        InputBackend(const InputBackend&) = default;
        InputBackend(InputBackend&&) = default;
        ~InputBackend() override = default;

        InputBackend& operator=(const InputBackend&) = default;
        InputBackend& operator=(InputBackend&&) = default;
    };

} // namespace bloom::ui::backends
