/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*           Copyright (C)2014-2021, WWIV Software Services               */
/*                                                                        */
/*    Licensed  under the  Apache License, Version  2.0 (the "License");  */
/*    you may not use this  file  except in compliance with the License.  */
/*    You may obtain a copy of the License at                             */
/*                                                                        */
/*                http://www.apache.org/licenses/LICENSE-2.0              */
/*                                                                        */
/*    Unless  required  by  applicable  law  or agreed to  in  writing,   */
/*    software  distributed  under  the  License  is  distributed on an   */
/*    "AS IS"  BASIS, WIT`OUT  WARRANTIES  OR  CONDITIONS OF ANY  KIND,   */
/*    either  express  or implied.  See  the  License for  the specific   */
/*    language governing permissions and limitations under the License.   */
/*                                                                        */
/**************************************************************************/
#include "gtest/gtest.h"

#include "bbs_test/bbs_helper.h"
#include "bbs/application.h"
#include "bbs/bbs.h"
#include "core/file.h"
#include "sdk/config.h"
#include "sdk/user.h"
#include <algorithm>
#include <memory>
#include <string>
#include <utility>

using std::begin;
using std::end;
using std::move;
using std::make_unique;
using std::unique_ptr;
using std::replace;

using namespace wwiv::core;
using namespace wwiv::sdk;

BbsHelper::BbsHelper() : CommonHelper(nullptr) {
  app_.reset(CreateSession(io_->local_io()));
  app_->SetCommForTest(io_->remote_io());
  app_->set_config_for_test(*config_);
  app_->instance_number_ = 42;
}

void BbsHelper::SetUp() {
  CommonHelper::SetUp();
}

Config& BbsHelper::config() const {
  return *app_->config();
}

wwiv::common::SessionContext& BbsHelper::sess() {
  return app_->sess();
}

User* BbsHelper::user() {
  return app_->user();  
}

const User* BbsHelper::user() const {
  return app_->user();  
}
