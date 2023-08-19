#include "validationHelper.h"

#include <stdexcept>

namespace Bloom {
    void validateVkResult(const VkResult& result) {
#ifndef NDEBUG
        switch (result) {
            case VK_SUCCESS:
            case VK_NOT_READY:
            case VK_TIMEOUT:
            case VK_EVENT_SET:
            case VK_EVENT_RESET:
            case VK_INCOMPLETE:
            case VK_SUBOPTIMAL_KHR:
            case VK_ERROR_OUT_OF_DATE_KHR: // handled
            case VK_THREAD_IDLE_KHR:
            case VK_THREAD_DONE_KHR:
            case VK_OPERATION_DEFERRED_KHR:
            case VK_OPERATION_NOT_DEFERRED_KHR:
            case VK_PIPELINE_COMPILE_REQUIRED_EXT:
                // Ok
                break;
            case VK_ERROR_OUT_OF_HOST_MEMORY:
                throw std::runtime_error("VK_ERROR_OUT_OF_HOST_MEMORY");
            case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                throw std::runtime_error("VK_ERROR_OUT_OF_DEVICE_MEMORY");
            case VK_ERROR_INITIALIZATION_FAILED:
                throw std::runtime_error("VK_ERROR_INITIALIZATION_FAILED");
            case VK_ERROR_DEVICE_LOST:
                throw std::runtime_error("VK_ERROR_DEVICE_LOST");
            case VK_ERROR_MEMORY_MAP_FAILED:
                throw std::runtime_error("VK_ERROR_MEMORY_MAP_FAILED");
            case VK_ERROR_LAYER_NOT_PRESENT:
                throw std::runtime_error("VK_ERROR_LAYER_NOT_PRESENT");
            case VK_ERROR_EXTENSION_NOT_PRESENT:
                throw std::runtime_error("VK_ERROR_EXTENSION_NOT_PRESENT");
            case VK_ERROR_FEATURE_NOT_PRESENT:
                throw std::runtime_error("VK_ERROR_FEATURE_NOT_PRESENT");
            case VK_ERROR_INCOMPATIBLE_DRIVER:
                throw std::runtime_error("VK_ERROR_INCOMPATIBLE_DRIVER");
            case VK_ERROR_TOO_MANY_OBJECTS:
                throw std::runtime_error("VK_ERROR_TOO_MANY_OBJECTS");
            case VK_ERROR_FORMAT_NOT_SUPPORTED:
                throw std::runtime_error("VK_ERROR_FORMAT_NOT_SUPPORTED");
            case VK_ERROR_FRAGMENTED_POOL:
                throw std::runtime_error("VK_ERROR_FRAGMENTED_POOL");
            case VK_ERROR_OUT_OF_POOL_MEMORY:
                throw std::runtime_error("VK_ERROR_OUT_OF_POOL_MEMORY");
            case VK_ERROR_INVALID_EXTERNAL_HANDLE:
                throw std::runtime_error("VK_ERROR_INVALID_EXTERNAL_HANDLE");
            case VK_ERROR_FRAGMENTATION:
                throw std::runtime_error("VK_ERROR_FRAGMENTATION");
            case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
                throw std::runtime_error("VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS");
            case VK_ERROR_SURFACE_LOST_KHR:
                throw std::runtime_error("VK_ERROR_SURFACE_LOST_KHR");
            case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
                throw std::runtime_error("VK_ERROR_NATIVE_WINDOW_IN_USE_KHR");
            case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
                throw std::runtime_error("VK_ERROR_INCOMPATIBLE_DISPLAY_KHR");
            case VK_ERROR_VALIDATION_FAILED_EXT:
                throw std::runtime_error("VK_ERROR_VALIDATION_FAILED_EXT");
            case VK_ERROR_INVALID_SHADER_NV:
                throw std::runtime_error("VK_ERROR_INVALID_SHADER_NV");
            case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR:
                throw std::runtime_error("VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR");
            case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR:
                throw std::runtime_error("VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR");
            case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR:
                throw std::runtime_error("VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR");
            case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR:
                throw std::runtime_error("VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR");
            case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR:
                throw std::runtime_error("VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR");
            case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR:
                throw std::runtime_error("VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR");
            case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
                throw std::runtime_error("VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT");
            case VK_ERROR_NOT_PERMITTED_EXT:
                throw std::runtime_error("VK_ERROR_NOT_PERMITTED_EXT");
            case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
                throw std::runtime_error("VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT");
            case VK_ERROR_COMPRESSION_EXHAUSTED_EXT:
                throw std::runtime_error("VK_ERROR_COMPRESSION_EXHAUSTED_EXT");
            case VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT:
                throw std::runtime_error("VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT");
            case VK_ERROR_UNKNOWN:
                throw std::runtime_error("VK_ERROR_UNKNOWN");
            case VK_RESULT_MAX_ENUM:
                throw std::runtime_error("VK_RESULT_MAX_ENUM");
        }
#endif
    }
} // namespace Bloom