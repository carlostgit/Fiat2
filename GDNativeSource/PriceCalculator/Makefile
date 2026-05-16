CXX = g++
CXXFLAGS = -O0 -g -Wall -Isrc -Itests -Iinclude
LDFLAGS = 

SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests

# Fuentes del núcleo (todos los .cpp en src excepto main.cpp y los bindings de Emscripten)
CORE_SOURCES = $(filter-out $(SRC_DIR)/main.cpp $(SRC_DIR)/EmscriptenBindings.cpp, $(wildcard $(SRC_DIR)/*.cpp))
CORE_OBJECTS = $(CORE_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Fuentes de la aplicación principal
APP_SOURCES = $(SRC_DIR)/main.cpp
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Fuentes de los tests
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/test_%.o)

TARGET = PriceCalculator
TEST_TARGET = run_tests

all: $(TARGET)

$(TARGET): $(CORE_OBJECTS) $(APP_OBJECTS)
	$(CXX) $(CORE_OBJECTS) $(APP_OBJECTS) -o $(TARGET) $(LDFLAGS)

# Objetivo para compilar y ejecutar tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(CORE_OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CORE_OBJECTS) $(TEST_OBJECTS) -o $(TEST_TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_TARGET)

# Lanzar el servidor web para el Runner (WASM)
serve-runner:
	@echo "Lanzando servidor en http://localhost:8000..."
	@echo "Cierra esta terminal o pulsa Ctrl+C para detener el servidor."
	@python3 -m http.server 8000 & sleep 1 && xdg-open http://localhost:8000/tools/runner/index.html || open http://localhost:8000/tools/runner/index.html

.PHONY: all clean test serve-runner
