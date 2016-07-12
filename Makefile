include Makefile.cfg

SOURCES:=$(shell find $(SOURCEDIR) -name '*.cc')
OBJECTS:=$(subst $(SOURCEDIR),$(OBJECTDIR), $(subst .cc,.o, $(SOURCES)))
DEPENDS:=$(subst $(SOURCEDIR),$(DEPENDDIR), $(subst .cc,.d, $(SOURCES)))
DIRS:=$(SOURCEDIR) $(HEADERDIR) $(OBJECTDIR) $(DEPENDDIR) $(BINARYDIR)\
			$(DEBUGDIR) $(RELEASEDIR)
BINLOC=

.PHONY:clean default release debug $(DEPENDS) Makefile Makefile.cfg DEFAULT RELEASE DEBUG

default:DEFAULT
debug:DEBUG
release:RELEASE
all:DEBUG RELEASE

.SECONDEXPANSION:
DEFAULT DEBUG RELEASE: FLAGS += $($@FLAGS)
DEFAULT DEBUG RELEASE: BINLOC += $($@DIR)/$(name)
DEFAULT DEBUG RELEASE:$(DIRS) $$(BINLOC)

# link everything together
%/$(name):$(OBJECTS)
	$(CC) $+ $(FLAGS) -o $@

-include $(DEPENDS)

# generate directories
$(DIRS):
	@echo Making directory: $@
	@mkdir $@

#dummy:
#	@for VAR in $(DIRS); do \
#		if [ ! -d $$VAR ]; then \
#			echo "Making directory: $$VAR"; \
#			mkdir $$VAR; \
#		fi \
#	done

# more complicated dependency computation, so all prereqs listed
# will also become command-less, prereq-less targets
#   sed:    strip the target (everything before colon)
#   sed:    remove any continuation backslashes
#   fmt -1: list words one per line
#   sed:    strip leading spaces
#   sed:    add trailing colons
$(OBJECTDIR)/%.o:
	$(CC) -c $(SOURCEDIR)/$*.cc $(FLAGS) -o $@
	$(CC) -MM $(FLAGS) $(SOURCEDIR)/$*.cc > $(DEPENDDIR)/$*.d
	@mv -f $(DEPENDDIR)/$*.d $(DEPENDDIR)/$*.d.tmp
	@sed -e 's|.*:|$(OBJECTDIR)/$*.o:|' < $(DEPENDDIR)/$*.d.tmp > $(DEPENDDIR)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(DEPENDDIR)/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $(DEPENDDIR)/$*.d
	@$(RM) -f $(DEPENDDIR)/$*.d.tmp

clean:
	@$(RM) -rf $(OBJECTDIR) *.exe* $(DEPENDDIR) $(BINARYDIR)

#file partially written based on information from:
#http://scottmcpeak.com/autodepend/autodepend.html

