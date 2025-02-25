/**
 * Copyright 2020-2022 Huawei Technologies Co., Ltd
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
#include "common/bboxop_common.h"
#include "minddata/dataset/kernels/image/bounding_box_augment_op.h"
#include "minddata/dataset/kernels/image/random_rotation_op.h"
#include "utils/log_adapter.h"

using namespace mindspore::dataset;

const bool kSaveExpected = false;
const char kOpName[] = "bounding_box_augment_op";

class MindDataTestBoundingBoxAugmentOp : public UT::CVOP::BBOXOP::BBoxOpCommon {
 protected:
  MindDataTestBoundingBoxAugmentOp() : UT::CVOP::BBOXOP::BBoxOpCommon() {}
};

/// Feature: BoundingBoxAugment op
/// Description: Test BoundingBoxAugment op basic usage
/// Expectation: Output is equal to the expected output
TEST_F(MindDataTestBoundingBoxAugmentOp, DISABLED_TestOp) {
  MS_LOG(INFO) << "Doing testBoundingBoxAugment.";
  TensorTable results;
  auto random_rotation_op = std::make_shared<RandomRotationOp>(90, 90, InterpolationMode::kNearestNeighbour, false,
                                                               std::vector<float>(), 0, 0, 0);
  std::unique_ptr<BoundingBoxAugmentOp> op = std::make_unique<BoundingBoxAugmentOp>(random_rotation_op, 1);
  for (const auto &row : images_and_annotations_) {
    TensorRow output_row;
    Status s = op->Compute(row, &output_row);
    EXPECT_TRUE(s.IsOk());
    results.push_back(output_row);
  }
  if (kSaveExpected) {
    SaveImagesWithAnnotations(FileType::kExpected, std::string(kOpName), results);
  }
  SaveImagesWithAnnotations(FileType::kActual, std::string(kOpName), results);
  if (!kSaveExpected) {
    CompareActualAndExpected(std::string(kOpName));
  }
}
