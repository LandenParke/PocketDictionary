# Important
main UI file is lvgldemo.c\
nuttxspace folder reflects nuttx sim structure\
nuttxspace folder uses symlinks to reference files elsewhere in repo

# Premise
use open source LVGL library to create GUI
- modified by user input and dictionary queries
- outputs to lcd (320x240px)

# Design Reference
![](gui_design_reference.png)

# Sim Setup
using nuttx sim LATEST (lvgl v9.2.2)\
using sim:sqlite\
(but actually using frankenstein .config)

---
from nuttx sim to hardware
https://lvgl.io/docs/open/integration/rtos/nuttx#nuttx-on-device