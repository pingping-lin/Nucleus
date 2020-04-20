 /*
 * Copyright 2019-present, Infosys Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
 /******************************************************
 * s1HoWfSrcS1RelTauRequest.h
 * This is an auto generated file.
 * Please do not edit this file.
 * All edits to be made through template source file
 * <TOP-DIR/scripts/SMCodeGen/templates/stateMachineTmpls/state.h.tt>
 ******************************************************/
 
#ifndef __S1HoWfSrcS1RelTauRequest__
#define __S1HoWfSrcS1RelTauRequest__

#include "state.h"

namespace mme {

	class S1HoWfSrcS1RelTauRequest : public SM::State
	{
		public:
			/******************************************
			* Instance 
			*    Creates static instance for the state
			*******************************************/
			static S1HoWfSrcS1RelTauRequest* Instance();

			/****************************************
			* S1HoWfSrcS1RelTauRequest
			*    Destructor
			****************************************/
			~S1HoWfSrcS1RelTauRequest();			
			
			/******************************************
			* initialize
			*  Initializes action handlers for the state
			* and next state
			******************************************/
			void initialize();
	
		private:
			/****************************************
			* S1HoWfSrcS1RelTauRequest
			*    Private constructor
			****************************************/
			S1HoWfSrcS1RelTauRequest();  
	};
};
#endif // __S1HoWfSrcS1RelTauRequest__
