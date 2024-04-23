.. _module-pw_devicetree:

-------------
pw_devicetree
-------------
This module provides a way to reuse Zephyr's devicetree tools on your Pigweed
project. This enables you to:
1. Parse DTS files
2. Convert them into a header file that can be used in C/C++ to read devicetree
data using `Zephyr's devicetree API (Macros)
<https://docs.zephyrproject.org/latest/build/dts/api-usage.html>`_

TODO Docs:
* How to use/setup this module on your Pigweed project
* Add small .dts file Example
* How to override the devicetree_generated.h
* Code example on how to use Zephyr macros to read DT props in code

Add Zephyr as a Submodule
=========================

Zephyr doesn't provide a bazel build file so we add one to reference the
necessary files to use the devicetree. You can add Zephyr as a submodule in
your project and then, in Bazel, "mount" it in your project's WORKSPACE file
as shown below:

```
# In the WORKSPACE file
new_local_repository(
    name = "zephyr",
    build_file = "//src/pw_devicetree:zephyr.BUILD", # self
    path = "third_party/zephyr", # this is the submodule path
)
```

Devicetree API Tests
====================

Devicetree API unit tests are included in `api_test/`. These tests exercise all
of the Zephyr DT Macros based on the devicetree header `api_test/devicetree_generated.h`.
In order to run the unit tests from Bazel, you need to override the backend, for
example `bazel test //src/pw_devicetree:api_test --//src/pw_devicetree:config_override=//src/pw_devicetree:api_test_config_overrides`.

The api tests use `zephyr/boards/posix/native_sim/native_sim.dts` as the base DTS and
`zephyr/tests/lib/devicetree/api/app.overlay` as application overlay.


How to go from DTS to `devicetree_generated.h`
==============================================

The `devicetree_generated.h` header file contains all the information in the DTS
file in a way that allows Zephyr's DT macros to read the data in build time.

Generating `devicetree_generated.h` can be done in 2 steps:
1. Run the preprocessor on the DTS file so it can resolve `#includes`
2. Run the script `zephyr/scripts/dts/gen_defines.py` on the preprocessed DTS
to generate the header file

As an example, let's regenerate the `devicetree_generated.h` for the API tests.
The API tests example shown above use 2 DTS files:
* `zephyr/tests/lib/devicetree/api/app.overlay`
* `zephyr/boards/posix/native_sim/native_sim.dts`

1. Regenerate the preprocessed DTS file by running the preprocessor on the app
overlay and the board DTS files:

```
cpp  -x assembler-with-cpp -nostdinc $BETTY_ROOT/third_party/zephyr/tests/lib/devicetree/api/app.overlay -include $BETTY_ROOT/third_party/zephyr/boards/posix/native_sim/native_sim.dts -I$BETTY_ROOT/third_party/zephyr/include -I$BETTY_ROOT/third_party/zephyr/dts -I$BETTY_ROOT/third_party/zephyr/dts/common -I -D__DTS__ -E -o preprocessed.dts
```
This will generate the `preprocessed.dts` file in the current directory. This
file will be used in the next step.

2. Run the script `zephyr/scripts/dts/gen_defines.py` on the preprocessed DTS
(`preprocessed.dts`) to generate the header file `devicetree_generated.h` (required to read the DTS data
from C++):

```
$BETTY_ROOT/third_party/zephyr/scripts/dts/gen_defines.py --dts preprocessed.dts --bindings-dirs $BETTY_ROOT/third_party/zephyr/dts/bindings --header-out devicetree_generated.h --dts-out dts_out.dts --dtc-flags Wno-simple_bus_reg
```

How to Override `devicetree_generated.h` For Your Target
========================================================


