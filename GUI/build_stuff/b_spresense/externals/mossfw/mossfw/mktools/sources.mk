MOSSFW_CSRCS =

ifeq ($(MOSSFW_FRAMEWORK_ENABLE),en)
MOSSFW_CSRCS += src/mossfw/mossfw_component.c
MOSSFW_CSRCS += src/mossfw/mossfw_lock.c
MOSSFW_CSRCS += src/mossfw/mossfw_debug.c
MOSSFW_CSRCS += src/mossfw/mossfw_memoryallocator.c
MOSSFW_CSRCS += src/mossfw/mossfw_ringbuff.c
MOSSFW_CSRCS += src/mossfw/mossfw_ringbuffary.c
endif

ifeq ($(MOSSFW_SENSORLIB_ENABLE),en)
MOSSFW_CSRCS += src/mossfw/mosscalib.c
MOSSFW_CSRCS += src/mossfw/mossdsp_axis.c
MOSSFW_CSRCS += src/mossfw/mossdsp_filter.c
MOSSFW_CSRCS += src/mossfw/mossdsp_rot.c
MOSSFW_CSRCS += src/mossfw/mossdsp_integral.c
MOSSFW_CSRCS += src/mossfw/mossdsp_resampling.c
MOSSFW_CSRCS += src/mossfw/components/averageacc.c
MOSSFW_CSRCS += src/mossfw/components/complementaryfilter.c
MOSSFW_CSRCS += src/mossfw/components/eiscalibration.c
MOSSFW_CSRCS += src/mossfw/components/estimateposeacc.c
MOSSFW_CSRCS += src/mossfw/components/lpf.c
MOSSFW_CSRCS += src/mossfw/components/transform.c
endif

ifeq ($(MOSSFW_SENSORLIB_USE_CMSIS),en)
MOSSFW_CFLAGS += -DMOSSFW_USE_ARMCMSIS_DSP
endif
