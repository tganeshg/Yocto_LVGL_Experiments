# -----------------------------------------------------------------------------
# Makefile for LVGL Sample Application using Yocto SDK
# -----------------------------------------------------------------------------
SDK_ENV ?= /opt/poky/4.0.28/environment-setup-arm1176jzfshf-vfp-poky-linux-gnueabi
TARGET   = lvgl_sample
SRCDIR   = source
OBJDIR   = objects
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# No -static here
LDLIBS   = -lm -llvgl_demos -llvgl_examples -llvgl_thorvg -llvgl

$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo "Linking using Yocto toolchain..."
	@mkdir -p $(BINDIR)
	@bash -c "source $(SDK_ENV) && $(CC) $(OBJECTS) -o $@ $(LDFLAGS) $(LDLIBS)"
	@echo "Linking complete! Output -> $@"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo "Compiling $< using Yocto toolchain..."
	@bash -c "source $(SDK_ENV) && $(CC) $(CFLAGS) -c $< -o $@"
	@echo "Compiled $< successfully!"

.PHONY: clean
clean:
	@rm -f $(OBJECTS)
	@rm -f $(BINDIR)/$(TARGET)
	@echo "Cleanup complete!"
