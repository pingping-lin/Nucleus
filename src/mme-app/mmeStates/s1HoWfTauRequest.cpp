/*
 * Copyright 2020-present Infosys Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
/**************************************
 * s1HoWfTauRequest.cpp
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

#include "mmeStates/s1HoWfTauRequest.h"

using namespace mme;
using namespace SM;

/******************************************************************************
* Constructor
******************************************************************************/
S1HoWfTauRequest::S1HoWfTauRequest():State(s1_ho_wf_tau_request)
{
        stateEntryAction = &MmeStatesUtils::on_state_entry;
        stateExitAction = &MmeStatesUtils::on_state_exit;
        eventValidator = &MmeStatesUtils::validate_event;
}

/******************************************************************************
* Destructor
******************************************************************************/
S1HoWfTauRequest::~S1HoWfTauRequest()
{
}

/******************************************************************************
* creates and returns static instance
******************************************************************************/
S1HoWfTauRequest* S1HoWfTauRequest::Instance()
{
        static S1HoWfTauRequest state;
        return &state;
}

/******************************************************************************
* initializes eventToActionsMap
******************************************************************************/
void S1HoWfTauRequest::initialize()
{
        {
                ActionTable actionTable;
                actionTable.addAction(&ActionHandlers::process_tau_request);
                actionTable.addAction(&ActionHandlers::send_tau_response_to_ue);
                actionTable.addAction(&ActionHandlers::ho_complete);
                eventToActionsMap.insert(pair<uint16_t, ActionTable>(TAU_REQUEST_FROM_UE, actionTable));
        }
}
