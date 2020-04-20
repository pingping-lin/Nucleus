/*
 * Copyright 2020-present Infosys Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/******************************************************************************
 *
 * This file has both generated and manual code.
 * 
 * File template used for code generation:
 * <TOP-DIR/scripts/SMCodeGen/templates/stateMachineTmpls/actionHandlers.cpp.tt>
 *
 ******************************************************************************/
#include "actionHandlers/actionHandlers.h"
#include "controlBlock.h"
#include "msgType.h"
#include "procedureStats.h"
#include "log.h"
#include "secUtils.h"
#include "state.h"
#include <string.h>
#include <sstream>
#include <mmeSmDefs.h>
#include "common_proc_info.h"
#include <ipcTypes.h>
#include <tipcTypes.h>
#include <msgBuffer.h>
#include <interfaces/mmeIpcInterface.h>
#include <event.h>
#include <stateMachineEngine.h>
#include <utils/mmeCommonUtils.h>
#include <utils/mmeContextManagerUtils.h>
#include <utils/mmeS1MsgUtils.h>
#include <utils/mmeGtpMsgUtils.h>
#include <contextManager/dataBlocks.h>

using namespace mme;
using namespace SM;
using namespace cmn::utils;

extern MmeIpcInterface *mmeIpcIf_g;

using namespace mme;
using namespace SM;

/***************************************
 * Action handler : send_ho_request_to_target_enb
 ***************************************/
ActStatus ActionHandlers::send_ho_request_to_target_enb(ControlBlock &cb)
{
    log_msg(LOG_INFO, "Inside send_ho_request_to_target_enb\n");

    UEContext *ueCtxt = static_cast<UEContext*>(cb.getPermDataBlock());

    if (ueCtxt == NULL)
    {
        log_msg(LOG_DEBUG,
                "send_ho_request_to_target_enb: ue context is NULL\n");
        return ActStatus::HALT;
    }

    S1HandoverProcedureContext *hoProcCtxt =
            dynamic_cast<S1HandoverProcedureContext*>(cb.getTempDataBlock());
    if (hoProcCtxt == NULL)
    {
        log_msg(LOG_DEBUG,
                "send_ho_request_to_target_enb: MmeS1HandoverProcedureCtxt is NULL\n");
        return ActStatus::HALT;
    }

    struct handover_request_Q_msg hoReq;
    memset(&hoReq, 0, sizeof(struct handover_request_Q_msg));

    MmeS1MsgUtils::populateHoRequest(cb, *ueCtxt, *hoProcCtxt, hoReq);

    /*Send message to S1AP-APP*/
    cmn::ipc::IpcAddress destAddr;
    destAddr.u32 = TipcServiceInstance::s1apAppInstanceNum_c;

    mmeIpcIf_g->dispatchIpcMsg((char*)&hoReq, sizeof(hoReq), destAddr);

    log_msg(LOG_DEBUG, "Leaving send_ho_request_to_target_enb \n");

    ProcedureStats::num_of_ho_request_to_target_enb_sent++;
    return ActStatus::PROCEED;
}

/***************************************
 * Action handler : process_ho_request_ack
 ***************************************/
ActStatus ActionHandlers::process_ho_request_ack(ControlBlock &cb)
{
    log_msg(LOG_DEBUG, "Inside process_ho_request_ack\n");

    UEContext *ue_ctxt = static_cast<UEContext*>(cb.getPermDataBlock());
    if (ue_ctxt == NULL)
    {
        log_msg(LOG_DEBUG, "process_ho_request_ack: ue ctxt is NULL \n");
        return ActStatus::HALT;
    }

    S1HandoverProcedureContext *ho_ctxt =
            dynamic_cast<S1HandoverProcedureContext*>(cb.getTempDataBlock());
    if (ho_ctxt == NULL)
    {
        log_msg(LOG_DEBUG, "process_ho_request_ack: procedure ctxt is NULL \n");
        return ActStatus::HALT;
    }

    MsgBuffer *msgBuf = static_cast<MsgBuffer*>(cb.getMsgData());
    if (msgBuf == NULL)
    {
        log_msg(LOG_ERROR, "Failed to retrieve message buffer \n");
        return ActStatus::HALT;
    }

    const s1_incoming_msg_data_t *msgData_p =
            static_cast<const s1_incoming_msg_data_t*>(msgBuf->getDataPointer());
    if (msgData_p == NULL)
    {
        log_msg(LOG_ERROR, "Failed to retrieve data buffer \n");
        return ActStatus::HALT;
    }

    const struct handover_req_acknowledge_Q_msg &ho_request_ack =
    		(msgData_p->msg_data.handover_req_acknowledge_Q_msg_m);

    ho_ctxt->setTargetS1apEnbUeId(ho_request_ack.s1ap_enb_ue_id);
    ho_ctxt->setTargetToSrcTransContainer(
    		ho_request_ack.targetToSrcTranspContainer);
    ho_ctxt->setErabAdmittedItem(
            ho_request_ack.erab_admitted_list.erab_admitted[0]);

    ProcedureStats::num_of_ho_request_ack_received++;
    log_msg(LOG_DEBUG, "Leaving process_ho_request_ack\n");
    return ActStatus::PROCEED;
}

/***************************************
 * Action handler : send_ho_command_to_src_enb
 ***************************************/
ActStatus ActionHandlers::send_ho_command_to_src_enb(ControlBlock &cb)
{
    log_msg(LOG_DEBUG, "Inside send_ho_command_to_src_enb\n");

    UEContext *ue_ctxt = static_cast<UEContext*>(cb.getPermDataBlock());
    if (ue_ctxt == NULL)
    {
        log_msg(LOG_DEBUG, "send_ho_command_to_src_enb: ue ctxt is NULL \n");
        return ActStatus::HALT;
    }

    S1HandoverProcedureContext *ho_ctxt =
            dynamic_cast<S1HandoverProcedureContext*>(cb.getTempDataBlock());
    if (ho_ctxt == NULL)
    {
        log_msg(LOG_DEBUG,
                "send_ho_command_to_src_enb: procedure ctxt is NULL \n");
        return ActStatus::HALT;
    }

    struct handover_command_Q_msg ho_command;
    memset(&ho_command, 0, sizeof(struct handover_command_Q_msg));

    MmeS1MsgUtils::populateHoCommand(cb, *ue_ctxt, *ho_ctxt, ho_command);

    cmn::ipc::IpcAddress destAddr;
    destAddr.u32 = TipcServiceInstance::s1apAppInstanceNum_c;

    mmeIpcIf_g->dispatchIpcMsg((char*) &ho_command, sizeof(ho_command),
            destAddr);

    ProcedureStats::num_of_ho_command_to_src_enb_sent++;
    log_msg(LOG_DEBUG, "Leaving send_ho_command_to_src_enb\n");

    return ActStatus::PROCEED;
}

/***************************************
* Action handler : send_mme_status_tranfer_to_target_enb
***************************************/
ActStatus ActionHandlers::send_mme_status_tranfer_to_target_enb(ControlBlock& cb)
{
    log_msg(LOG_DEBUG, "Inside send_mme_status_tranfer_to_target_enb\n");
    UEContext *ue_ctxt = static_cast<UEContext*>(cb.getPermDataBlock());
    if (ue_ctxt == NULL)
    {
        log_msg(LOG_DEBUG, "send_mme_status_tranfer_to_target_enb: ue ctxt is NULL \n");
        return ActStatus::HALT;
    }

    S1HandoverProcedureContext *ho_ctxt =
            dynamic_cast<S1HandoverProcedureContext*>(cb.getTempDataBlock());
    if (ho_ctxt == NULL)
    {
        log_msg(LOG_DEBUG, "send_mme_status_tranfer_to_target_enb: procedure ctxt is NULL \n");
        return ActStatus::HALT;
    }

    MsgBuffer *msgBuf = static_cast<MsgBuffer*>(cb.getMsgData());
    if (msgBuf == NULL)
    {
        log_msg(LOG_ERROR, "Failed to retrieve message buffer \n");
        return ActStatus::HALT;
    }

    const s1_incoming_msg_data_t *msgData_p =
            static_cast<const s1_incoming_msg_data_t*>(msgBuf->getDataPointer());
    if (msgData_p == NULL)
    {
        log_msg(LOG_ERROR, "Failed to retrieve data buffer \n");
        return ActStatus::HALT;
    }

    const struct enb_status_transfer_Q_msg & enb_status_trans =
            (msgData_p->msg_data.enb_status_transfer_Q_msg_m);

    struct mme_status_transfer_Q_msg mme_status_trans;
    memset(&mme_status_trans, 0, sizeof(struct mme_status_transfer_Q_msg));

    mme_status_trans.msg_type = mme_status_transfer;
    mme_status_trans.enb_fd = ho_ctxt->getTargetEnbFd();
    mme_status_trans.s1ap_enb_ue_id = ho_ctxt->getTargetEnbFd();
    mme_status_trans.s1ap_mme_ue_id = ue_ctxt->getContextID();
    mme_status_trans.enB_status_transfer_transparent_containerlist.count =
    	enb_status_trans.enB_status_transfer_transparent_containerlist.count;
    memcpy(&(mme_status_trans.enB_status_transfer_transparent_containerlist.enB_status_transfer_transparent_container) ,
    	&(enb_status_trans.enB_status_transfer_transparent_containerlist.enB_status_transfer_transparent_container),
	sizeof(struct enB_status_transfer_transparent_container));

    cmn::ipc::IpcAddress destAddr;
    destAddr.u32 = TipcServiceInstance::s1apAppInstanceNum_c;

    mmeIpcIf_g->dispatchIpcMsg((char*) &mme_status_trans, sizeof(struct  mme_status_transfer_Q_msg),
            destAddr);
    return ActStatus::PROCEED;
}

/***************************************
 * Action handler : process_ho_notify
 ***************************************/
ActStatus ActionHandlers::process_ho_notify(ControlBlock &cb)
{
    log_msg(LOG_DEBUG, "Inside process_ho_notify\n");
    UEContext *ue_ctxt = static_cast<UEContext*>(cb.getPermDataBlock());
    if (ue_ctxt == NULL)
    {
        log_msg(LOG_DEBUG, "process_ho_notify: ue ctxt is NULL \n");
        return ActStatus::HALT;
    }

    S1HandoverProcedureContext *ho_ctxt =
            dynamic_cast<S1HandoverProcedureContext*>(cb.getTempDataBlock());
    if (ho_ctxt == NULL)
    {
        log_msg(LOG_DEBUG, "process_ho_notify: procedure ctxt is NULL \n");
        return ActStatus::HALT;
    }

    MsgBuffer *msgBuf = static_cast<MsgBuffer*>(cb.getMsgData());
    if (msgBuf == NULL)
    {
        log_msg(LOG_ERROR, "Failed to retrieve message buffer \n");
        return ActStatus::HALT;
    }

    const s1_incoming_msg_data_t *msgData_p =
            static_cast<const s1_incoming_msg_data_t*>(msgBuf->getDataPointer());
    if (msgData_p == NULL)
    {
        log_msg(LOG_ERROR, "Failed to retrieve data buffer \n");
        return ActStatus::HALT;
    }

    const struct handover_notify_Q_msg &ho_notify =
            (msgData_p->msg_data.handover_notify_Q_msg_m);

    // The UE has synced to target cell. Set the current enb
    // to target enb.
    ue_ctxt->setEnbFd(ho_ctxt->getTargetEnbFd());
    ue_ctxt->setS1apEnbUeId(ho_ctxt->getTargetS1apEnbUeId());

    // Wait till TAU complete to overwrite TAI?
    ho_ctxt->setTargetTai(Tai(ho_notify.tai));
    ho_ctxt->setTargetCgi(Cgi(ho_notify.utran_cgi));

    ProcedureStats::num_of_ho_notify_received++;
    log_msg(LOG_DEBUG, "Leaving process_ho_notify\n");

    return ActStatus::PROCEED;
}

/********************************************
 * Action handler : send_mb_req_to_sgw_for_ho
 ********************************************/
ActStatus ActionHandlers::send_mb_req_to_sgw_for_ho(ControlBlock &cb)
{
    log_msg(LOG_DEBUG, "Inside send_mb_req_to_sgw_for_ho \n");

    UEContext *ue_ctxt = static_cast<UEContext*>(cb.getPermDataBlock());
    if (ue_ctxt == NULL)
    {
        log_msg(LOG_DEBUG,
                "send_mb_req_to_sgw_for_ho: ue context or procedure ctxt is NULL \n");
        return ActStatus::HALT;
    }

    S1HandoverProcedureContext *ho_ctxt =
            dynamic_cast<S1HandoverProcedureContext*>(cb.getTempDataBlock());
    if (ho_ctxt == NULL)
    {
        log_msg(LOG_DEBUG, "process_ho_notify: procedure ctxt is NULL \n");
        return ActStatus::HALT;
    }
    SessionContext *sessionCtxt = ue_ctxt->getSessionContext();
    if (sessionCtxt == NULL)
    {
        log_msg(LOG_DEBUG,
                "send_mb_req_to_sgw_for_ho: session ctxt is NULL \n");
        return ActStatus::HALT;
    }

    BearerContext *bearerCtxt = sessionCtxt->getBearerContext();
    if (bearerCtxt == NULL)
    {
        log_msg(LOG_DEBUG, "send_mb_req_to_sgw_for_ho: bearer ctxt is NULL \n");
        return ActStatus::HALT;
    }

    struct MB_Q_msg mb_msg;
    MmeGtpMsgUtils::populateModifyBearerRequestHo(cb, *ue_ctxt,
    		*ho_ctxt, mb_msg);
    if (bearerCtxt)
        bearerCtxt->setS1uEnbUserFteid(Fteid(mb_msg.s1u_enb_fteid));

    cmn::ipc::IpcAddress destAddr;
    destAddr.u32 = TipcServiceInstance::s11AppInstanceNum_c;

    mmeIpcIf_g->dispatchIpcMsg((char*) &mb_msg, sizeof(mb_msg), destAddr);

    ProcedureStats::num_of_mb_req_to_sgw_sent++;
    log_msg(LOG_DEBUG, "Leaving send_mb_req_to_sgw_for_ho \n");
    return ActStatus::PROCEED;
}

/***************************************
* Action handler : process_mb_resp_for_ho
***************************************/
ActStatus ActionHandlers::process_mb_resp_for_ho(ControlBlock& cb)
{
    log_msg(LOG_DEBUG, "Inside process_mb_resp_for_ho \n");

    ProcedureStats::num_of_processed_mb_resp ++;
    return ActStatus::PROCEED;
}

/***************************************
* Action handler : send_s1_rel_cmd_to_ue_for_ho
***************************************/
ActStatus ActionHandlers::send_s1_rel_cmd_to_ue_for_ho(ControlBlock& cb)
{
    log_msg(LOG_DEBUG, "Inside send_s1_rel_cmd_to_ue_for_ho\n");
    UEContext *ue_ctxt = static_cast<UEContext*>(cb.getPermDataBlock());
    if(ue_ctxt == NULL)
    {
    	log_msg(LOG_DEBUG, "send_s1_rel_cmd_to_ue_for_ho: ue context is NULL \n");
    	return ActStatus::HALT;
    }

    S1HandoverProcedureContext *ho_ctxt =
            dynamic_cast<S1HandoverProcedureContext*>(cb.getTempDataBlock());
    if (ho_ctxt == NULL)
    {
        log_msg(LOG_DEBUG, "process_ho_notify: procedure ctxt is NULL \n");
        return ActStatus::HALT;
    }
    struct s1relcmd_info s1relcmd;
    s1relcmd.msg_type = s1_release_command;
    s1relcmd.ue_idx = ue_ctxt->getContextID();
    s1relcmd.enb_s1ap_ue_id = ho_ctxt->getSrcS1apEnbUeId();
    s1relcmd.cause.present = s1apCause_PR_radioNetwork;
    s1relcmd.cause.choice.radioNetwork = s1apCauseRadioNetwork_successful_handover;
    s1relcmd.enb_fd = ho_ctxt->getSrcEnbFd();
    /*Send message to S1AP-APP*/
    cmn::ipc::IpcAddress destAddr;
    destAddr.u32 = TipcServiceInstance::s1apAppInstanceNum_c;

    mmeIpcIf_g->dispatchIpcMsg((char *) &s1relcmd, sizeof(s1relcmd), destAddr);

    ProcedureStats::num_of_s1_rel_cmd_sent ++;
    log_msg(LOG_DEBUG,"Leaving send_s1ap_ue_ctxt_rel_command_to_src_enb \n");
    return ActStatus::PROCEED;
}

/***************************************
* Action handler : process_ue_ctxt_rel_comp_for_ho
***************************************/
ActStatus ActionHandlers::process_ue_ctxt_rel_comp_for_ho(ControlBlock& cb)
{
    log_msg(LOG_DEBUG, "Inside process_ue_ctxt_rel_comp_for_ho \n");

    ProcedureStats::num_of_s1_rel_comp_received++;

    return ActStatus::PROCEED;
}

/***************************************
 * Action handler : ho_complete
 ***************************************/
ActStatus ActionHandlers::ho_complete(ControlBlock &cb)
{
    log_msg(LOG_INFO, "Inside ho_complete\n");

    UEContext *ue_ctxt = static_cast<UEContext*>(cb.getPermDataBlock());
    if (ue_ctxt == NULL)
    {
        log_msg(LOG_ERROR, "ho_complete: ue context is NULL\n",
                cb.getCBIndex());
        return ActStatus::HALT;
    }

    S1HandoverProcedureContext *s1HoPrcdCtxt_p =
            dynamic_cast<S1HandoverProcedureContext*>(cb.getTempDataBlock());
    if (s1HoPrcdCtxt_p == NULL)
    {
        log_msg(LOG_DEBUG, "ho_complete: S1HandoverProcedureContext is NULL\n");
        return ActStatus::HALT;
    }

    ue_ctxt->setTai(Tai(s1HoPrcdCtxt_p->getTargetTai()));
    ue_ctxt->setUtranCgi(Cgi(s1HoPrcdCtxt_p->getTargetCgi()));

    ProcedureStats::num_of_ho_complete++;

    MmeContextManagerUtils::deallocateProcedureCtxt(cb, s1Handover_c);

    return ActStatus::PROCEED;
}

