ifndef PROJECT_NAME
	PROJECT_NAME = newport8742
endif

usetrunk ?= 1
ifeq ($(usetrunk), 1)
IOLIBDIR = $(TANGO_DIR)/Libraries/libio/trunk
endif

ifeq ($(usetrunk), 0)
IOLIBDIR = $(shell find $(TANGO_DIR)/Libraries/libio/tags -type d -regex '.*Release_[0-9]*_[0-9]*' | sort -t '_' -k2 -k3 -nr | head -1)
endif

RELEASE_TYPE ?= DEBUG
OBJ_DIR=$(shell pwd)/obj
TARGETLIB=lib$(PROJECT_NAME).a


CXXFLAGS=-Wall -D_LINUX -D_REENTRANT -I$(OBJ_DIR) -I.
ifeq ($(RELEASE_TYPE), DEBUG) 
CXXFLAGS += -D_DEBUG
endif

ifeq ($(RELEASE_TYPE), OPTIMIZED) 
	CXXFLAGS += -O2
endif



OBJS =	$(OBJ_DIR)/$(PROJECT_NAME).o

all: lib
	$(CXX) $(CXXFLAGS) -o $(PROJECT_NAME) main.cpp -l$(PROJECT_NAME) -L $(OBJ_DIR) -lpthread

lib: $(TARGETLIB)

$(OBJ_DIR)/%.o: %.cpp %.h
	@echo "Compiling here $< ..."
	$(CXX) $(CXXFLAGS) -c $< -o $@


objdir:
	mkdir -p $(OBJ_DIR)

$(TARGETLIB): iolib $(OBJS) 
	ar vrucs $(OBJ_DIR)/$(TARGETLIB) $(OBJS)
	cd $(IOLIBDIR) && $(MAKE) clean

iolib: objdir ioinc $(OBJS)
	cd $(IOLIBDIR) && $(MAKE) clean && $(MAKE) install DESTDIR=$(OBJ_DIR) PROJECT_NAME=$(PROJECT_NAME) RELEASE_TYPE=$(RELEASE_TYPE)

ioinc: objdir
	cd $(IOLIBDIR) && $(MAKE) inc_install DESTDIR=$(OBJ_DIR) PROJECT_NAME=$(PROJECT_NAME) RELEASE_TYPE=$(RELEASE_TYPE)

ioobj: objdir  $(OBJS)
	cd $(IOLIBDIR) && $(MAKE) clean && $(MAKE) obj_install DESTDIR=$(OBJ_DIR) PROJECT_NAME=$(PROJECT_NAME) RELEASE_TYPE=$(RELEASE_TYPE)

clean:
	rm -rf $(OBJ_DIR) $(PROJECT_NAME) *.o doc

install:
	cp $(OBJ_DIR)/$(TARGETLIB) $(DESTDIR)


doc:
	@mkdir -p doc && cd doc && \
	cp $(IOLIBDIR)/*.cpp . && \
	cp $(IOLIBDIR)/*.h . && \
	cp $(IOLIBDIR)/doxy.in . && \
	cp  $(IOLIBDIR)/mainpage.in . && \
	cp ../*.cpp . && \
	cp ../*.h . &&\
	cp doxy.in doxy.cfg && \
	cat ../mainpage.h >> mainpage.in && \
	mv mainpage.in mainpage.h && \
	doxygen doxy.cfg && \
	rm *.h *.cpp doxy.* && \
	echo -e "\nCreated documentation in `pwd`"

