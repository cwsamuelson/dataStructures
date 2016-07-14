include Makefile.cfg

.PHONY:clean $(DEPENDS) Makefile Makefile.cfg $(builds)

ifndef BINLOC

.DEFAULT_GOAL:=default

.SECONDEXPANSION:
$(builds): export BINLOC = $(binarydir)/$($@dir)/$(name)
$(builds): export FLAGS  = $($@flags)
$(builds): export objdir +=$(objectdir)/$($@dir)
$(builds): export DIRS   = $(binarydir)/$($@dir)
$(builds):
	@$(MAKE)

else

.DEFAULT_GOAL:=$(BINLOC)

SOURCES:=$(shell find $(sourcedir) -name '*.cc')
OBJECTS:=$(subst $(sourcedir),$(objdir), $(subst .cc,.o, $(SOURCES)))
DEPENDS:=$(subst $(sourcedir),$(dependdir), $(subst .cc,.d, $(SOURCES)))
DIRS := $(sourcedir) $(headerdir) $(objectdir) $(objdir) $(dependdir) $(binarydir) $(DIRS)

.SECONDARY:$(OBJECTS)

# link everything together
%/$(name):$(OBJECTS)
	$(CC) $+ $(FLAGS) -o $@

-include $(DEPENDS)

# generate directories
$(DIRS):
	@echo Making directory: $@
	@mkdir $@

# more complicated dependency computation, so all prereqs listed
# will also become command-less, prereq-less targets
#   sed:    strip the target (everything before colon)
#   sed:    remove any continuation backslashes
#   fmt -1: list words one per line
#   sed:    strip leading spaces
#   sed:    add trailing colons
$(objdir)/%.o:|$(DIRS)
	$(CC) -c $(sourcedir)/$*.cc $(FLAGS) -o $@
	$(CC) -MM $(FLAGS) $(sourcedir)/$*.cc > $(dependdir)/$*.d
	@mv -f $(dependdir)/$*.d $(dependdir)/$*.d.tmp
	@sed -e 's|.*:|$(objdir)/$*.o:|' < $(dependdir)/$*.d.tmp > $(dependdir)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(dependdir)/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $(dependdir)/$*.d
	@$(RM) -f $(dependdir)/$*.d.tmp

endif

clean:
	-@$(RM) -rf $(objectdir) *.exe* $(dependdir) $(binarydir)

#file partially written based on information from:
#http://scottmcpeak.com/autodepend/autodepend.html

