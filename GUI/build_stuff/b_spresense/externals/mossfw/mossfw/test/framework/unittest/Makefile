MKFILES = $(wildcard */Makefile)

define run_test
	@ (cd $(dir $(1)) && make)

endef

define clean_test
	@ (cd $(dir $(1)) && make clean)

endef

define cov_test
	@ (cd $(dir $(1)) && make cov)

endef

all:
	$(foreach mk,$(MKFILES),$(call run_test,$(mk)))

clean:
	$(foreach mk,$(MKFILES),$(call clean_test,$(mk)))
	rm -f lcov.info
	rm -rf lcov

cov:
	$(foreach mk,$(MKFILES),$(call cov_test,$(mk)))
	lcov -c -d . --rc lcov_branch_coverage=1 -o lcov.info
	genhtml -o lcov --branch-coverage -p C: lcov.info
