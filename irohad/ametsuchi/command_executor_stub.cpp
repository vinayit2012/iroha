/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ametsuchi/command_executor_stub.hpp>
#include <iostream>

namespace iroha {
  namespace ametsuchi {

    bool CommandExecutorStub::execute(const model::Command &command) {
      auto handler = map_.find(command);
      return handler.value_or([](const model::Command &) {
        std::cout << "[CE] handler not found" << std::endl;
        return false;
      })(command);
    }

    bool CommandExecutorStub::executeAddPeer(const model::AddPeer &command) {
      std::cout << "[CE] add peer executed" << std::endl;
      return true;
    }

    CommandExecutorStub::CommandExecutorStub(WsvQuery &query) : query_(query) {
      // https://stackoverflow.com/questions/9998402/c11-does-not-deduce-type-when-stdfunction-or-lambda-functions-are-involved
      map_.insert<model::AddPeer>(std::bind(&CommandExecutorStub::executeAddPeer,
                                          this, std::placeholders::_1));
    }
  }  // namespace ametsuchi
}  // namespace iroha
