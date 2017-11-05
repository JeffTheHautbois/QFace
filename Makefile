include Makefile.variable

# ----- Build Settings, you shouldn't really need to touch these ------
PROJECT = Turbo

# Directories where the source file will be compiled
BIN_DIR = ./bin
OBJ_DIR = $(BIN_DIR)/obj

# Source file directories
SRC_DIR = ./src/cpp
SRC_DIR_MODELS = $(SRC_DIR)/models
SRC_DIR_VIEWS = $(SRC_DIR)/views
SRC_DIR_CONTROLLERS = $(SRC_DIR)/controllers
SRC_DIR_TEST = $(SRC_DIR)/test

LIB_DIR = ./lib

# Compiler Settings
CXX = $(EMSCRIPTEN_HOME)/em++
CXXFLAGS = -Wall \
       -Wextra \
       -std=c++11 \
       -I$(SRC_DIR) \
       -O1 \
       --bind \

LDFLAGS = \
       --preload-file data \
       -s NO_EXIT_RUNTIME=1 \
       -s ASSERTIONS=2 \
       --llvm-lto 1 \
       -s DEMANGLE_SUPPORT=1 \
       -s TOTAL_MEMORY=117440512  # 112MB

# The source file themselves
MAIN = $(SRC_DIR)/main.cpp
SOURCES = $(MAIN)
SOURCES += $(wildcard $(SRC_DIR_MODELS)/*.cpp)
SOURCES += $(wildcard $(SRC_DIR_VIEWS)/*.cpp)
SOURCES += $(wildcard $(SRC_DIR_CONTROLLERS)/*.cpp)

COMPILED_JS = $(BIN_DIR)/$(PROJECT).asm.js
COMPILED_BC = $(BIN_DIR)/$(PROJECT).bc

# Automatic header dependecy management. Not 100% how it works.
DEPS = $(OBJECTS:%.o=%.d)
-include $(DEPS)

TEST_OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.cpp, %.o, $(TEST_SOURCES))))

# The executible file itself
PROJECT = Turbo
COMPILED_JS = $(BIN_DIR)/$(PROJECT).asm.js
COMPILED_BC = $(BIN_DIR)/$(PROJECT).bc

TEST_COMPILED_JS = $(BIN_DIR)/$(PROJECT).test.asm.js

# json
JSON_INCLUDE = $(LIB_DIR)/json
INCLUDE = \
  -I$(JSON_INCLUDE) \
 
# ----- OpenCV Dependencies ----- 
OPENCV_DIR = $(LIB_DIR)/opencv_3.1.0
OPENCV_INCLUDE = $(OPENCV_DIR)/modules
OPENCV_LIB = $(OPENCV_DIR)/precompiled
OPENCV_3RD_PARTY = $(OPENCV_DIR)/share/OpenCV/3rdparty/lib

# Libs
INCLUDE += \
  -I$(OPENCV_INCLUDE)/core/include \
  -I$(OPENCV_INCLUDE)/flann/include \
  -I$(OPENCV_INCLUDE)/ml/include \
  -I$(OPENCV_INCLUDE)/photo/include \
  -I$(OPENCV_INCLUDE)/shape/include \
  -I$(OPENCV_INCLUDE)/imgproc/include \
  -I$(OPENCV_INCLUDE)/calib3d/include \
  -I$(OPENCV_INCLUDE)/features2d/include \
  -I$(OPENCV_INCLUDE)/video/include \
  -I$(OPENCV_INCLUDE)/objdetect/include \
  -I$(OPENCV_INCLUDE)/imgcodecs/include \
  -I$(OPENCV_INCLUDE)/hal/include \

# Do NOT change the order of these libs. The order matters.
LIBS = \
    $(OPENCV_LIB)/libopencv_videoio.a \
    $(OPENCV_LIB)/libopencv_shape.a \
    $(OPENCV_LIB)/libopencv_photo.a \
    $(OPENCV_LIB)/libopencv_objdetect.a \
    $(OPENCV_LIB)/libopencv_ml.a \
    $(OPENCV_LIB)/libopencv_imgcodecs.a \
    $(OPENCV_LIB)/libopencv_highgui.a \
    $(OPENCV_LIB)/libopencv_features2d.a \
    $(OPENCV_3RD_PARTY)/liblibpng.a \
    $(OPENCV_3RD_PARTY)/liblibjpeg.a \
    $(OPENCV_LIB)/libopencv_video.a \
    $(OPENCV_LIB)/libopencv_imgproc.a \
    $(OPENCV_LIB)/libopencv_flann.a \
    $(OPENCV_LIB)/libopencv_core.a \
    $(OPENCV_3RD_PARTY)/libzlib.a


# Specify the executible
ifeq ($(MAKECMDGOALS), test)
    $(info Building with unit tests.)
    COMPILED_BC = $(BIN_DIR)/$(PROJECT).test.bc
    COMPILED_JS = $(BIN_DIR)/$(PROJECT).test.html
    LDFLAGS += --preload-file test_data
    SOURCES += $(wildcard $(SRC_DIR_TEST)/*.cpp)
    CXXFLAGS += -D TEST_ENV
endif

# Object Directory
OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.cpp, %.o, $(SOURCES))))

# ----- Actual Build targets. Add new ones as needed. ------
test: all

all: $(COMPILED_JS)

$(COMPILED_JS): $(COMPILED_BC)
	$(info ---- Compiling bitcode into $(COMPILED_JS) ----)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(COMPILED_BC) -o $(COMPILED_JS)

$(COMPILED_BC): $(OBJECTS)
	$(info ---- Linking with 3rd party libs ----)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $(COMPILED_BC)

# ---- Compiling C++/Headers in objects. -------
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(info ---- Compiling $^ ----)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -MMD $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR_MODELS)/%.cpp
	$(info ---- Compiling $^ ----)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -MMD $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR_VIEWS)/%.cpp
	$(info ---- Compiling $^ ----)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -MMD $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR_CONTROLLERS)/%.cpp
	$(info ---- Compiling $^ ----)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -MMD $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR_TEST)/%.cpp
	$(info ---- Compiling $^ ----)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -MMD $< -o $@


# ----- Other useful scripts ------


server:
	$(PYTHON3) server.py

clean:
	-rm $(BIN_DIR)/$(PROJECT).* $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d $(BIN_DIR)/*.bc

lint:
	$(CPPLINT) --filter=-legal/copyright --recursive src/cpp
