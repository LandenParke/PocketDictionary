MOSSFW_FRAMEWORK_ENABLE=en
MOSSFW_SENSORLIB_ENABLE=en
include ../../mktools/sources.mk

CFLAGS= -I ../../include -I . -g -fdiagnostics-color=always -O2 -mfma -DOK=0 -DERROR=-1
LDFLAGS=-L . -lmossfw -lm -lpthread
CSRCS = stableacc.c expecteddata.c inputdata.c output.c sample_attitude.c attitude_main.c

attitude: $(CSRCS:.c=.o) libmossfw.a
	$(CC) -o $@ $(CSRCS:.c=.o) $(LDFLAGS)

clean:
	rm -f attitude
	rm -f $(CSRCS:.c=.o)
	rm -f libmossfw.a

dep: $(MAINSRC) $(CSRCS)
	$(CC) $(CFLAGS) -M $(CSRCS) $(addprefix ../../, $(MOSSFW_CSRCS)) > Make.dep

libmossfw.a: libmossfw.a($(addprefix ../../, $(MOSSFW_CSRCS:.c=.o)))

include Make.dep
