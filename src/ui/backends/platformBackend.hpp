#pragma once

namespace bloom::ui::backends {

    class PlatformBackend {
      public:
        PlatformBackend() = default;
        PlatformBackend(const PlatformBackend&) = default;
        PlatformBackend(PlatformBackend&&) = default;
        virtual ~PlatformBackend() = default;

        PlatformBackend& operator=(const PlatformBackend&) = default;
        PlatformBackend& operator=(PlatformBackend&&) = default;

        virtual void initialize() = 0;
        virtual void shutdown() = 0;
        virtual void beginFrame() = 0;
    };

} // namespace bloom::ui::backends
