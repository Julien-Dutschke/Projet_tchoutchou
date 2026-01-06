CXX ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Werror -pedantic

TARGET = Tchoutchou

SRC = main.cpp \
      Source/Train.cpp
SRC += options.cpp

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
