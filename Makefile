CXX ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Werror -pedantic

TARGET = Tchoutchou

SRC = Source/main.cpp
SRC += Source/Train.cpp
SRC += Source/options.cpp
SRC += Source/Parser.cpp

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -IInclude -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all
