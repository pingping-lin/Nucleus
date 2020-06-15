/*
 * Copyright 2020-present Infosys Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
 /******************************************************
 * serviceRequestWfAia.h
 * This is an auto generated file.
 * Please do not edit this file.
 * All edits to be made through template source file
 * <TOP-DIR/scripts/SMCodeGen/templates/stateMachineTmpls/state.h.tt>
 ******************************************************/
 
#ifndef __ServiceRequestWfAia__
#define __ServiceRequestWfAia__

#include "state.h"

namespace mme {

	class ServiceRequestWfAia : public SM::State
	{
		public:
			/******************************************
			* Instance 
			*    Creates static instance for the state
			*******************************************/
			static ServiceRequestWfAia* Instance();

			/****************************************
			* ServiceRequestWfAia
			*    Destructor
			****************************************/
			~ServiceRequestWfAia();			
			
			/******************************************
			* initialize
			*  Initializes action handlers for the state
			* and next state
			******************************************/
			void initialize();
	
		private:
			/****************************************
			* ServiceRequestWfAia
			*    Private constructor
			****************************************/
			ServiceRequestWfAia();  
	};
};
#endif // __ServiceRequestWfAia__
