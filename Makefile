CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I.

SRC = src/models/student.cpp \
      src/models/PhDStudent.cpp \
      src/models/UndergraduateStudent.cpp \
      src/models/GraduateStudent.cpp \
      src/services/StudentManager.cpp \
      tests/test_main.cpp

OBJ = $(SRC:.cpp=.o)

TARGET = program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
