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
       -s NO_EXIT_RUNTIME=1 -s ASSERTIONS=1 \
       -I$(SRC_DIR) \
       -O2 \
       --bind \
       --preload-file data 

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

TEST_COMPILED_JS = $(BIN_DIR)/$(PROJECT).test.asm.js

# ----- OpenCV Dependencies ----- 
OPENCV_DIR = $(LIB_DIR)/opencv
OPENCV_SRC = $(OPENCV_DIR)/src
OPENCV_BUILD = $(OPENCV_DIR)/build
OPENCV_LIB = $(OPENCV_DIR)/lib

# Libs
INCLUDE = \
  -I$(OPENCV_LIB)/include \
  -I$(OPENCV_LIB)/include/opencv

LIBS = \
    -L$(OPENCV_LIB)/lib \
    -llibopencv_core \
    -llibopencv_highgui \
    -llibopencv_imgcodecs \
    -llibopencv_imgproc \
    -llibopencv_objdetect \
    -llibopencv_video \
    -L$(OPENCV_LIB)/share/OpenCV/3rdparty/lib \
    -lzlib \

opencv: $(OPENCV_LIB)

$(OPENCV_LIB): $(OPENCV_BUILD)

$(OPENCV_BUILD): $(OPENCV_SRC)
	$(EMSCRIPTEN_HOME)/emcmake \
    cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCPU_BASELINE='' \
    -DCPU_DISPATCH='' \
    -DCV_TRACE=OFF \
    -DBUILD_SHARED_LIBS=OFF \
    -DWITH_1394=OFF \
    -DWITH_VTK=OFF \
    -DWITH_CUDA=OFF \
    -DWITH_CUFFT=OFF \
    -DWITH_CUBLAS=OFF \
    -DWITH_NVCUVID=OFF \
    -DWITH_EIGEN=OFF \
    -DWITH_FFMPEG=OFF \
    -DWITH_GSTREAMER=OFF \
    -DWITH_GTK=OFF \
    -DWITH_GTK_2_X=OFF \
    -DWITH_IPP=OFF \
    -DWITH_JASPER=OFF \
    -DWITH_JPEG=OFF \
    -DWITH_WEBP=OFF \
    -DWITH_OPENEXR=OFF \
    -DWITH_OPENGL=OFF \
    -DWITH_OPENVX=OFF \
    -DWITH_OPENNI=OFF \
    -DWITH_OPENNI2=OFF \
    -DWITH_PNG=OFF \
    -DWITH_TBB=OFF \
    -DWITH_PTHREADS_PF=OFF \
    -DWITH_TIFF=OFF \
    -DWITH_V4L=OFF \
    -DWITH_OPENCL=OFF \
    -DWITH_OPENCL_SVM=OFF \
    -DWITH_OPENCLAMDFFT=OFF \
    -DWITH_OPENCLAMDBLAS=OFF \
    -DWITH_MATLAB=OFF \
    -DWITH_GPHOTO2=OFF \
    -DWITH_LAPACK=OFF \
    -DWITH_ITT=OFF \
    -DBUILD_ZLIB=ON \
    -DBUILD_opencv_apps=OFF \
    -DBUILD_opencv_calib3d=OFF \
    -DBUILD_opencv_dnn=OFF \
    -DBUILD_opencv_features2d=OFF \
    -DBUILD_opencv_flann=OFF \
    -DBUILD_opencv_ml=OFF \
    -DBUILD_opencv_photo=OFF \
    -DBUILD_opencv_imgcodecs=ON \
    -DBUILD_opencv_shape=OFF \
    -DBUILD_opencv_videoio=OFF \
    -DBUILD_opencv_videostab=OFF \
    -DBUILD_opencv_superres=OFF \
    -DBUILD_opencv_stitching=OFF \
    -DBUILD_opencv_java=OFF \
    -DBUILD_opencv_js=ON \
    -DBUILD_opencv_python2=OFF \
    -DBUILD_opencv_python3=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_PACKAGE=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_PERF_TESTS=OFF \
    -DBUILD_DOCS=OFF\
    -B$(OPENCV_BUILD) \
    -H$(OPENCV_SRC)
	$(EMSCRIPTEN_HOME)/emmake make -C $(OPENCV_BUILD) install
	mv $(OPENCV_BUILD)/install $(OPENCV_LIB)

$(OPENCV_SRC):
	git clone --depth 1 https://github.com/opencv/opencv $(OPENCV_SRC)

# ----- Actual Build targets. Add new ones as needed. ------
all: opencv $(COMPILED_JS)

$(COMPILED_JS): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $^ -o $(COMPILED_JS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -MMD $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR_MODELS)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -MMD $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR_VIEWS)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -MMD $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR_CONTROLLERS)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -MMD $< -o $@

# ----- Build targets for testing
test: $(TEST_OBJECTS)
	$(eval $(CXXFLAGS) += -I$(TEST_DIR))
	$(CXX) $(CXXFLAGS) $^ -o $(TEST_COMPILED_JS)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ----- Other useful scripts ------
server:
	$(PYTHON3) -m http.server 8080 --bind localhost

clean:
	rm $(BIN_DIR)/$(PROJECT).* $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d

lint:
	$(CPPLINT) --filter=-legal/copyright --recursive src/cpp
