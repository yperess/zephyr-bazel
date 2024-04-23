// Copyright 2023 The Pigweed Authors
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

#include <cstddef>

#include "pw_sys_io/sys_io.h"
#include "zephyr/devicetree.h"
#include "pw_log/log.h"

void LogDevicetreeInfo(void) {
  // Basic example on how we can get devicetree info with Zephyr's API
  // Devicetree data is in //src/pw_devicetree_betty
  PW_LOG_INFO("Devicetree info:");
  const char * str = DT_PROP(DT_ROOT, compatible);
  PW_LOG_INFO(" compatible: %s", str);
  str = DT_PROP(DT_NODELABEL(cpu0), compatible);
  PW_LOG_INFO(" cpu0: %s", str);
}

int main() {
  LogDevicetreeInfo();
  while (true) {
    std::byte data;
    pw::sys_io::ReadByte(&data).IgnoreError();
    pw::sys_io::WriteByte(data).IgnoreError();
  }
  return 0;
}
