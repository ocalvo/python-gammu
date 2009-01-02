# Top level makefile for Gammu
#  - wraps CMake build as used by configure
#  - provides some operations which can be done on source

BUILD_DIR=build-configure

.PHONY: all clean package package_source apidoc interndoc translations gammu install distclean test NightlyMemoryCheck Nightly

all: $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR)

clean: $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) clean

package: $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) package

package_source: $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) package_source

apidoc: $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) apidoc

interndoc: $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) interndoc

translations: $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) translations

gammu: $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) gammu

install: $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) install

test: $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) test

Nightly: $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) Nightly

NightlyMemoryCheck: $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) NightlyMemoryCheck

TAGFILESFIND = find gammu common include smsd tests -name '*.[ch]' -o -name '*.cpp'

tags: $(shell $(TAGFILESFIND))
	@echo Generating tags file...
	@ctags $(shell $(TAGFILESFIND))

distclean:
	rm -rf build*
	rm -f tags

$(BUILD_DIR):
	@echo 'You should run configure before running make!'
	@exit 1
