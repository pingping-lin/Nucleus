/*
 * Copyright 2020-present Infosys Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
/**************************************
 * s1HoWfHoRequestAck.cpp
 * This is an auto generated file.
 * Please do not edit this file.
 * All edits to be made through template source file
 * <TOP-DIR/scripts/SMCodeGen/templates/stateMachineTmpls/state.cpp.tt>
 **************************************/


#include "actionTable.h"
#include "actionHandlers/actionHandlers.h"
#include "mmeSmDefs.h"
#include "utils/mmeStatesUtils.h"
#include "utils/mmeTimerTypes.h"

#include "mmeStates/s1HoWfHoRequestAck.h"	
#include "mmeStates/s1HoWfHoNotify.h"

using namespace mme;
using namespace SM;

/******************************************************************************
* Constructor
******************************************************************************/
S1HoWfHoRequestAck::S1HoWfHoRequestAck():State(s1_ho_wf_ho_request_ack)
{
        stateEntryAction = &MmeStatesUtils::on_state_entry;
        stateExitAction = &MmeStatesUtils::on_state_exit;
        eventValidator = &MmeStatesUtils::validate_event;
}

/******************************************************************************
* Destructor
******************************************************************************/
S1HoWfHoRequestAck::~S1HoWfHoRequestAck()
{
}

/******************************************************************************
* creates and returns static instance
******************************************************************************/
S1HoWfHoRequestAck* S1HoWfHoRequestAck::Instance()
{
        static S1HoWfHoRequestAck state;
        return &state;
}

/******************************************************************************
* initializes eventToActionsMap
******************************************************************************/
void S1HoWfHoRequestAck::initialize()
{
        {
                ActionTable actionTable;
                actionTable.addAction(&ActionHandlers::process_ho_request_ack);
                actionTable.addAction(&ActionHandlers::send_ho_command_to_src_enb);
                actionTable.setNextState(S1HoWfHoNotify::Instance());
                eventToActionsMap.insert(pair<uint16_t, ActionTable>(HO_REQUEST_ACK_FROM_ENB, actionTable));
        }
        {
                ActionTable actionTable;
                actionTable.addAction(&ActionHandlers::process_ho_failure);
                actionTable.addAction(&ActionHandlers::send_ho_prep_failure_to_src_enb);
                actionTable.addAction(&ActionHandlers::abort_handover);
                eventToActionsMap.insert(pair<uint16_t, ActionTable>(HO_FAILURE_FROM_TARGET_ENB, actionTable));
        }
        {
                ActionTable actionTable;
                actionTable.addAction(&ActionHandlers::send_s1_rel_cmd_to_target_enb);
                actionTable.addAction(&ActionHandlers::send_ho_prep_failure_to_src_enb);
                actionTable.addAction(&ActionHandlers::abort_handover);
                eventToActionsMap.insert(pair<uint16_t, ActionTable>(ABORT_EVENT, actionTable));
        }
        {
                ActionTable actionTable;
                actionTable.addAction(&ActionHandlers::process_ho_cancel_req);
                actionTable.addAction(&ActionHandlers::send_ho_cancel_ack_to_src_enb);
                actionTable.addAction(&ActionHandlers::abort_handover);
                eventToActionsMap.insert(pair<uint16_t, ActionTable>(HO_CANCEL_REQ_FROM_SRC_ENB, actionTable));
        }
}
