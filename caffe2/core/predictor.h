/**
 * Copyright (c) 2016-present, Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "caffe2/core/net.h"
#include "caffe2/core/tensor.h"

namespace caffe2 {

class Predictor {
 public:
  using TensorVector = std::vector<TensorCPU*>;
  // Runs the `init_net` once, then saves the `run_net` to be executed
  // in `::run`
  Predictor(
      const NetDef& init_net,
      const NetDef& run_net,
      Workspace* parent = nullptr);
  ~Predictor();

  // Executes `run_net` on the inputs.
  // The first `inputs.size()` inputs from run_net::external_inputs
  // are shared with the data in `inputs`.

  // Precondition:
  //   inputs.size() <= run_net_.external_inputs.size()

  // Postcondition:
  //   outputs->size() == run_net.external_inputs.size()

  // Returns true on success
  bool run(const TensorVector& inputs, TensorVector* outputs);

  const NetDef& def() const {
    return run_net_;
  };

  Workspace* ws() {
    return &ws_;
  };

 private:
  NetDef run_net_;
  Workspace ws_;
};
}
