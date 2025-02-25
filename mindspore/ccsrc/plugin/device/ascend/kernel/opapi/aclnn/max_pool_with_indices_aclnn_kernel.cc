/**
 * Copyright 2024 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "plugin/device/ascend/kernel/opapi/aclnn/max_pool_with_indices_aclnn_kernel.h"
#include <algorithm>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include "ir/tensor.h"
#include "runtime/device/kernel_runtime.h"
#include "transform/acl_ir/acl_helper.h"
#include "abstract/ops/primitive_infer_map.h"

namespace mindspore {
namespace kernel {

void MaxPoolWithIndicesAscend::GetWorkSpaceInfo(const std::vector<KernelTensor *> &inputs,
                                                const std::vector<KernelTensor *> &outputs) {
  auto kernel_size = inputs[kIndex1]->GetValueWithCheck<std::vector<int64_t>>();
  std::vector<int64_t> strides = kernel_size;
  if (inputs[kIndex2]->type_id() != kMetaTypeNone) {
    strides = inputs[kIndex2]->GetValueWithCheck<std::vector<int64_t>>();
  }
  auto pads = inputs[kIndex3]->GetValueWithCheck<std::vector<int64_t>>();
  auto dilation = inputs[kIndex4]->GetValueWithCheck<std::vector<int64_t>>();
  auto ceil_mode = inputs[kIndex5]->GetValueWithCheck<bool>();
  GetWorkspaceForResize(inputs[kIndex0], kernel_size, strides, pads, dilation, ceil_mode, outputs[kIndex0],
                        outputs[kIndex1]);
}

bool MaxPoolWithIndicesAscend::Launch(const std::vector<KernelTensor *> &inputs,
                                      const std::vector<KernelTensor *> &workspace,
                                      const std::vector<KernelTensor *> &outputs, void *stream_ptr) {
  MS_EXCEPTION_IF_NULL(stream_ptr);
  auto kernel_size = inputs[kIndex1]->GetValueWithCheck<std::vector<int64_t>>();
  std::vector<int64_t> strides = kernel_size;
  if (inputs[kIndex2]->type_id() != kMetaTypeNone) {
    strides = inputs[kIndex2]->GetValueWithCheck<std::vector<int64_t>>();
  }
  auto pads = inputs[kIndex3]->GetValueWithCheck<std::vector<int64_t>>();
  auto dilation = inputs[kIndex4]->GetValueWithCheck<std::vector<int64_t>>();
  auto ceil_mode = inputs[kIndex5]->GetValueWithCheck<bool>();
  ParseGenExecutor(GEN_EXECUTOR_BOOST(op_type_, hash_id_, inputs[kIndex0], kernel_size, strides, pads, dilation,
                                      ceil_mode, outputs[kIndex0], outputs[kIndex1]));
  RunOp(stream_ptr, workspace);
  return true;
}

MS_ACLNN_KERNEL_FACTORY_REG(MaxPoolWithIndices, MaxPoolWithIndicesAscend);
}  // namespace kernel
}  // namespace mindspore
