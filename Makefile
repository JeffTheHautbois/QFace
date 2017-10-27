include Makefile.variable

# ----- Build Settings, you shouldn't really need to touch these ------

# Directories where the source file will be compiled
BIN_DIR = ./bin
OBJ_DIR = $(BIN_DIR)/obj

# Source file directories
SRC_DIR = ./src/cpp
SRC_DIR_MODELS = $(SRC_DIR)/models
SRC_DIR_VIEWS = $(SRC_DIR)/views
SRC_DIR_CONTROLLERS = $(SRC_DIR)/controllers

TEST_DIR = ./test

LIB_DIR = ./lib

# Compiler Settings
CXX = $(EMSCRIPTEN_HOME)/em++
CXXFLAGS = -Wall \
       -Wextra \
       -std=c++11 \
       -I$(SRC_DIR) \
       -O3 \
       --bind \

LDFLAGS = \
       --preload-file data \
       -s NO_EXIT_RUNTIME=1 \
       --llvm-lto 1 \
       -s TOTAL_MEMORY=117440512# 112MB


# The source file themselves
MAIN = $(SRC_DIR)/main.cpp
SOURCES = $(MAIN)
SOURCES += $(wildcard $(SRC_DIR_MODELS)/*.cpp)
SOURCES += $(wildcard $(SRC_DIR_VIEWS)/*.cpp)
SOURCES += $(wildcard $(SRC_DIR_CONTROLLERS)/*.cpp)

TEST_SOURCES = $(filter-out $(MAIN), $(SOURCES))
TEST_SOURCES += $(wildcard $(TEST_DIR)/*.cpp)

# Object Directory
OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.cpp, %.o, $(SOURCES))))

# Automatic header dependecy management. Not 100% how it works.
DEPS = $(OBJECTS:%.o=%.d)
-include $(DEPS)

TEST_OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.cpp, %.o, $(TEST_SOURCES))))

# The executible file itself
PROJECT = Turbo
COMPILED_JS = $(BIN_DIR)/$(PROJECT).asm.js
COMPILED_BC = $(BIN_DIR)/$(PROJECT).bc

TEST_COMPILED_JS = $(BIN_DIR)/$(PROJECT).test.asm.js

# ----- OpenCV Dependencies ----- 
OPENCV_DIR = $(LIB_DIR)/opencv_3.1.0
OPENCV_INCLUDE = $(OPENCV_DIR)/modules
OPENCV_LIB = $(OPENCV_DIR)/precompiled

# Libs
INCLUDE = \
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

LIBS = \
    -Wl,--start-group \
    $(OPENCV_LIB)/libopencv_core.a \
    $(OPENCV_LIB)/libopencv_features2d.a \
    $(OPENCV_LIB)/libopencv_flann.a \
    $(OPENCV_LIB)/libopencv_highgui.a \
    $(OPENCV_LIB)/libopencv_imgcodecs.a \
    $(OPENCV_LIB)/libopencv_imgproc.a \
    $(OPENCV_LIB)/libopencv_ml.a \
    $(OPENCV_LIB)/libopencv_objdetect.a \
    $(OPENCV_LIB)/libopencv_photo.a \
    $(OPENCV_LIB)/libopencv_shape.a \
    $(OPENCV_LIB)/libopencv_video.a \
    $(OPENCV_LIB)/libopencv_videoio.a \
    $(OPENCV_LIB)/share/OpenCV/3rdparty/lib/libzlib.a \
    $(OPENCV_LIB)/share/OpenCV/3rdparty/lib/liblibjpeg.a \
    $(OPENCV_LIB)/share/OpenCV/3rdparty/lib/liblibpng.a \
    -Wl,--end-group \

# ----- Actual Build targets. Add new ones as needed. ------
all: $(COMPILED_JS)

$(COMPILED_JS): $(COMPILED_BC)
	$(info ---- Linking bitcode with OpenCV ----)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(COMPILED_BC) $(LIBS) -o $(COMPILED_JS)

$(COMPILED_BC): $(OBJECTS)
	$(info ---- Compiling bitcode ----)
	$(CXX) $(CXXFLAGS) $^ -o $(COMPILED_BC)

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

# ----- Build targets for testing
test: $(TEST_OBJECTS)
	$(eval $(CXXFLAGS) += -I$(TEST_DIR))
	$(CXX) $(CXXFLAGS) $^ -o $(TEST_COMPILED_JS)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ----- Other useful scripts ------
server:
	$(PYTHON3) server.py

clean:
	rm $(BIN_DIR)/$(PROJECT).* $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d $(OBJ_DIR)/*.bc

lint:
	$(CPPLINT) --filter=-legal/copyright --recursive src/cpp
