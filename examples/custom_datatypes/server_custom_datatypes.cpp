#include "open62541pp/open62541pp.h"

#include "custom_datatypes.h"

int main() {
    opcua::Server server;

    // Get custom type definitions from common header
    const auto& mcMoveAbsoluteOutDataType = getMcMoveAbsoluteOutDataType();
    const auto& mcMoveAbsoluteInDataType = getMcMoveAbsoluteInDataType();

    // Provide custom data type definitions to server
    server.setCustomDataTypes({mcMoveAbsoluteOutDataType, mcMoveAbsoluteInDataType});

    // Add data type nodes
    auto nodeStructureDataType = server.getNode(opcua::DataTypeId::Structure);
    nodeStructureDataType.addDataType(mcMoveAbsoluteOutDataType.getTypeId(), "MC_MOVE_ABS_OUT");
    nodeStructureDataType.addDataType(mcMoveAbsoluteInDataType.getTypeId(), "MC_MOVE_ABS_IN");

    // Add variable nodes with some values
    auto nodeObjects = server.getObjectsNode();
    nodeObjects.addVariable(
        {1, "Push_Cylinder_ABS_OUT"},
        "Push_Cylinder_ABS_OUT",
        opcua::VariableAttributes{}
            .setDataType(mcMoveAbsoluteOutDataType.getTypeId())
            .setAccessLevel(UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE)
            .setValueScalar(MC_MoveAbsoluteOUT{}, mcMoveAbsoluteOutDataType)
    );
    nodeObjects.addVariable(
        {1, "Push_Cylinder_ABS_IN"},
        "Push_Cylinder_ABS_IN",
        opcua::VariableAttributes{}
            .setDataType(mcMoveAbsoluteInDataType.getTypeId())
            .setAccessLevel(UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE)
            .setValueScalar(MC_MoveAbsoluteIN{}, mcMoveAbsoluteInDataType)
    );

    server.run();
}
