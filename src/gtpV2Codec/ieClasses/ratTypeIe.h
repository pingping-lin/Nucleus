/*
 * Copyright (c) 2020, Infosys Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 /******************************************************************************
 *
 * This is an auto generated file.
 * Please do not edit this file.
 * All edits to be made through template source file
 * <TOP-DIR/scripts/GtpV2StackCodeGen/tts/ietemplate.h.tt>
 ******************************************************************************/
#ifndef RATTYPEIE_H_
#define RATTYPEIE_H_

#include "manual/gtpV2Ie.h"



class RatTypeIe: public GtpV2Ie {
public:
    RatTypeIe();
    virtual ~RatTypeIe();

    bool encodeRatTypeIe(MsgBuffer &buffer,
                 RatTypeIeData const &data);
    bool decodeRatTypeIe(MsgBuffer &buffer,
                 RatTypeIeData &data, Uint16 length);
    void displayRatTypeIe_v(RatTypeIeData const &data,
                 Debug &stream);
};

#endif /* RATTYPEIE_H_ */
