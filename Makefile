NAME = ft_containers
CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

INCLUDES = containers/stack.hpp containers/vector.hpp containers/map.hpp utils/Pair.hpp utils/Node.hpp \
			utils/algorithm.hpp utils/IteratorTraits.hpp utils/randomAccessIterator.hpp utils/RBTree.hpp \
			utils/RBTreeIterator.hpp utils/RBTreeReverseIterator.hpp utils/ReverseIterator.hpp utils/TypeTraits.hpp \
			tester/tester.hpp 

_RED=	$'\033[1;31m
_GREEN=	$'\033[1;32m
_END=	$'\033[0m

SRC = tester/containers_main.cpp tester/stack_tester.cpp tester/vector_tester.cpp \
		tester/map_tester.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

%.o: %.cpp ${INCLUDES} 
	${CXX} ${CXXFLAGS} -c $< -o $@

$(NAME): $(OBJ) $(INCLUDES)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo "$(_GREEN)Executable created : ft_containers$(_END)"

clean:
	rm -f $(OBJ)
	@echo "$(_RED)o. files removed.$(_END)"

fclean: clean
	rm -f $(NAME)
	@echo "$(_RED)Executable removed.$(_END)"

re: fclean all

.PHONY: all re clean fclean