
SUBDIRS=$(patsubst %/Makefile,%,$(wildcard */Makefile))

.PHONY: default clean $(SUBDIRS)
default: $(SUBDIRS)

clean: $(SUBDIRS)

simple-module-user: simple-module

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

