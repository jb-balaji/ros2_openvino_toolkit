// Copyright (c) 2018-2022 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @brief a header file with declaration of LandmarksDetectionModel class
 * @file landmarks_detection_model.cpp
 */
#include <string>
#include "openvino_wrapper_lib/models/landmarks_detection_model.hpp"
#include "openvino_wrapper_lib/slog.hpp"
// Validated Landmarks Detection Network
Models::LandmarksDetectionModel::LandmarksDetectionModel(const std::string& label_loc, const std::string& model_loc,
                                                         int max_batch_size)
  : BaseModel(label_loc, model_loc, max_batch_size)
{
}

bool Models::LandmarksDetectionModel::updateLayerProperty(std::shared_ptr<ov::Model>& model)
{
  slog::info << "Checking Inputs for Model" << getModelName() << slog::endl;
  if (model->inputs().size() != 1) {
    throw std::logic_error("Landmarks Detection topology should have only one input");
  }
  if (model->outputs().size() != 1) {
    throw std::logic_error("Landmarks Detection Network expects networks having one output");
  }
  ov::preprocess::PrePostProcessor ppp = ov::preprocess::PrePostProcessor(model);
  input_ = model->input().get_any_name();
  const ov::Layout input_tensor_layout{ "NCHW" };
  ppp.input(input_).tensor().set_element_type(ov::element::u8).set_layout(input_tensor_layout);
  output_ = model->output().get_any_name();
  ppp.output(output_).tensor().set_element_type(ov::element::f32);

  model = ppp.build();
  ov::set_batch(model, getMaxBatchSize());

  return true;
}

const std::string Models::LandmarksDetectionModel::getModelCategory() const
{
  return "Landmarks Detection";
}
