# -----------------------------------------------------------------------------
# Makefile for LVGL Sample Application using Yocto SDK
# -----------------------------------------------------------------------------
#. /opt/poky/4.0.28/environment-setup-arm1176jzfshf-vfp-poky-linux-gnueabi
TARGET   = lvgl_sample
SRCDIR   = source
OBJDIR   = objects
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CFLAGS   += -Wall
LDLIBS   = -lm -llvgl_demos -llvgl_examples -llvgl_thorvg -llvgl

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(CC) $(OBJECTS) -o $@ $(LDFLAGS) $(LDLIBS)
	@echo "Linking complete! Output -> $@"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< successfully!"

.PHONY: clean
clean:
	@rm -f $(OBJECTS)
	@rm -f $(BINDIR)/$(TARGET)
	@echo "Cleanup complete!"
