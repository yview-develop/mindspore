# Copyright 2020 Huawei Technologies Co., Ltd
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ============================================================================
"""
This interface is ONLY used in Auto-parallel procedure.
"""
from .dp_allreduce_fusion import set_fusion_strategy_by_idx, set_fusion_strategy_by_size
from .algo_parameter_config import get_algo_parameters, reset_algo_parameters, \
    set_algo_parameters

__all__ = ["set_fusion_strategy_by_idx", "set_fusion_strategy_by_size", "get_algo_parameters",
           "reset_algo_parameters", "set_algo_parameters"]
