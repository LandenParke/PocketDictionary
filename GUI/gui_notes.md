# premise
use open source LVGL library to create GUI
- modified by user input and dictionary queries
- outputs to display driver

# design reference
![](gui_design_reference.png)

# important
lv_conf.h params to be set
```
#define LV_USE_FONT_COMPRESSED 1
#define LV_FONT_FMT_TXT_LARGE 1
```
---
from nuttx sim to hardware
https://lvgl.io/docs/open/integration/rtos/nuttx#nuttx-on-device