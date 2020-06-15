
/*
 * Copyright 2020-present Infosys Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
/**************************************
 * serviceRequestStart.cpp
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

#include "mmeStates/serviceRequestStart.h"	
#include "mmeStates/serviceRequestWfAuthResponse.h"

using namespace mme;
using namespace SM;

/******************************************************************************
* Constructor
******************************************************************************/
ServiceRequestStart::ServiceRequestStart():State(service_request_start)
{
        stateEntryAction = &MmeStatesUtils::on_state_entry;
        stateExitAction = &MmeStatesUtils::on_state_exit;
        eventValidator = &MmeStatesUtils::validate_event;
}

/******************************************************************************
* Destructor
******************************************************************************/
ServiceRequestStart::~ServiceRequestStart()
{
}

/******************************************************************************
* creates and returns static instance
******************************************************************************/
ServiceRequestStart* ServiceRequestStart::Instance()
{
        static ServiceRequestStart state;
        return &state;
}

/******************************************************************************
* initializes eventToActionsMap
******************************************************************************/
void ServiceRequestStart::initialize()
{
        {
                ActionTable actionTable;
                actionTable.addAction(&ActionHandlers::auth_req_to_ue);
                actionTable.setNextState(ServiceRequestWfAuthResponse::Instance());
                eventToActionsMap.insert(pair<uint16_t, ActionTable>(SERVICE_REQUEST_FROM_UE, actionTable));
        }
}
