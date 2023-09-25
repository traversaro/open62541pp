#include <iostream>
#include <thread>

#include "open62541pp/open62541pp.h"

#include "custom_datatypes.h"

int main() {
    opcua::Client client;

    // Get custom type definitions from common header
    const auto& mcMoveAbsoluteOutDataType = getMcMoveAbsoluteOutDataType();
    const auto& mcMoveAbsoluteInDataType = getMcMoveAbsoluteInDataType();

    // Provide custom data type definitions to server
    client.setCustomDataTypes({mcMoveAbsoluteOutDataType, mcMoveAbsoluteInDataType});

    client.connect("opc.tcp://localhost:4840");

    auto mcMoveAbsoluteWriteNode = client.getNode({1, "Push_Cylinder_ABS_IN"});
    auto mcMoveAbsoluteReadNode = client.getNode({1, "Push_Cylinder_ABS_OUT"});

    // Initialize the struct
    MC_MoveAbsoluteIN moveAbsoluteData{};
    moveAbsoluteData.execute = true;
    moveAbsoluteData.position = 99.0;
    moveAbsoluteData.velocity = 5.0;
    moveAbsoluteData.acceleration = 2.0;
    moveAbsoluteData.deceleration = 2.0;
    moveAbsoluteData.jerk = 1.0;

    // Write custom variables
    auto mcMoveAbsoluteWriteVar = opcua::Variant::fromScalar(
        moveAbsoluteData, mcMoveAbsoluteInDataType
    );
    mcMoveAbsoluteWriteNode.writeValue(mcMoveAbsoluteWriteVar);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    auto variant = mcMoveAbsoluteReadNode.readValue();
    if (variant.isScalar() && variant.isType(mcMoveAbsoluteOutDataType)) {
        std::cout << "Reading from node\n";
        const auto* mcMoveAbsoluteRead = static_cast<MC_MoveAbsoluteOUT*>(variant.data());
        std::cout << "busy: " << mcMoveAbsoluteRead->busy << std::endl;
    } else {
        std::cout << "Not reading from node\n";
    }

    std::cin.ignore();
}
