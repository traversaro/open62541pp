#pragma once

#include <cstdint>

#include "open62541pp/open62541pp.h"

struct MC_MoveAbsoluteIN {
    bool execute;
    double position;
    double velocity;
    double acceleration;
    double deceleration;
    double jerk;
};

struct MC_MoveAbsoluteOUT {
    bool busy;
    bool done;
    bool active;
    bool error;
    int errorID;
    bool commandAborted;
};

const opcua::DataType& getMcMoveAbsoluteInDataType() {
    static const opcua::DataType dt =
        opcua::DataTypeBuilder<MC_MoveAbsoluteIN>::createStructure(
            "MC_MOVE_ABS_IN", {1, 5001}, {1, 1}
        )
            .addField<&MC_MoveAbsoluteIN::execute>("Execute")
            .addField<&MC_MoveAbsoluteIN::position>("Position")
            .addField<&MC_MoveAbsoluteIN::velocity>("Velocity")
            .addField<&MC_MoveAbsoluteIN::acceleration>("Acceleration")
            .addField<&MC_MoveAbsoluteIN::deceleration>("Deceleration")
            .addField<&MC_MoveAbsoluteIN::jerk>("Jerk")
            .build();
    return dt;
}

const opcua::DataType& getMcMoveAbsoluteOutDataType() {
    static const opcua::DataType dt =
        opcua::DataTypeBuilder<MC_MoveAbsoluteOUT>::createStructure(
            "MC_MOVE_ABS_OUT", {1, 5004}, {1, 2}
        )
            .addField<&MC_MoveAbsoluteOUT::done>("Done")
            .addField<&MC_MoveAbsoluteOUT::busy>("Busy")
            .addField<&MC_MoveAbsoluteOUT::active>("Active")
            .addField<&MC_MoveAbsoluteOUT::error>("Error")
            .addField<&MC_MoveAbsoluteOUT::errorID>("Error_ID")
            .addField<&MC_MoveAbsoluteOUT::commandAborted>("CommandAborted")
            .build();
    return dt;
}
