#pragma once

#include <depthai/pipeline/DeviceNode.hpp>

// shared
#include <depthai-shared/properties/SystemLoggerProperties.hpp>

namespace dai {
namespace node {

/**
 * @brief SystemLoggerNode. Send system information periodically.
 */
class SystemLoggerNode : public NodeGroup<DeviceNode, SystemLogger, SystemLoggerProperties> {
   public:
    constexpr static const char* NAME = "SystemLogger";

    /// Creates a SystemLogger node with default properties
    SystemLoggerNode();
    /// Creates a SystemLogger node with given properties
    SystemLoggerNode(std::unique_ptr<Properties> props);

    /**
     * Outputs SystemInformation[S3] message that carries various system information
     * like memory and CPU usage, temperatures, ...
     * For series 2 devices outputs SystemInformation message,
     * for series 3 devices outputs SystemInformationS3 message
     */
    Output out{*this, "out", Output::Type::MSender, {{DatatypeEnum::SystemInformation, false}, {DatatypeEnum::SystemInformationS3, false}}};

    /**
     * Optional - consumes an SystemInformation message from pool to send outwards
     * Otherwise uses dynamic allocation and/or default pool
     */
    Input inputPool{
        *this, "inputPool", Input::Type::MReceiver, false, 4, {{DatatypeEnum::SystemInformation, false}, {DatatypeEnum::SystemInformationS3, false}}};

    /**
     * Specify logging rate, at which messages will be sent out
     * @param hz Sending rate in hertz (messages per second)
     */
    void setRate(float hz);

    /**
     * Gets logging rate, at which messages will be sent out
     */
    float getRate();
};

}  // namespace node
}  // namespace dai