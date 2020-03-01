ZIA_INC =	-I ../inc/Core/Http			\
			-I ../inc/Core/Http/api		\
			-I ../inc/Core/Module		\
			-I ../inc/Network			\
			-I ../inc					\
			-I ../inc/Core/Configs		\
			-I ../inc/Ihm				\
			-I ../inc/Core/Listeners	\
			-I ../inc/Core				\

ZIA_SRC =	../src/Ihm/CmdLine.cpp						\
			../src/Core/Configs/Configurations.cpp		\
			../src/Core/Configs/Route.cpp				\
			../src/Core/Configs/Host.cpp				\
			../src/Core/Configs/ModulesContainer.cpp	\
			../src/Core/Configs/Module.cpp				\
			../src/Core/Http/HttpRequest.cpp			\
			../src/Core/Http/HttpResponse.cpp			\
			../src/Core/Listeners/ListenersControl.cpp	\
			../src/Core/Module/Module.cpp				\
			../src/util.cpp								\
			../src/ConfigNode.cpp						\
			../src/Network/NetworkManager.cpp			\
			../src/Network/BoostNetworkServer.cpp		\
			../src/Network/BoostNetworkClient.cpp

TESTS_SRC =	HttpRequest.cpp		\
			RouteConf.cpp		\
			HttpResponse.cpp	\
			ModuleConf.cpp		\
			ModulePhp.cpp		\
			HostConf.cpp		\
			ModuleFile.cpp		\

LIB_INC =	-I ~/.conan/data/yaml-cpp/0.6.2/bincrafters/stable/package/b911f48570f9bb2902d9e83b2b9ebf9d376c8c56/include \
			-I ~/.conan/data/boost/1.70.0/conan/stable/package/71a3ea6bfbaaf69a904e48a2da11313dfabb0b9d/include

LIB_DIR =	-L ~/.conan/data/yaml-cpp/0.6.2/bincrafters/stable/package/b911f48570f9bb2902d9e83b2b9ebf9d376c8c56/lib \
			-L ~/.conan/data/boost/1.70.0/conan/stable/package/71a3ea6bfbaaf69a904e48a2da11313dfabb0b9d/lib

LDFLAGS +=	-lyaml-cpp			\
			-lboost_filesystem	\
			-lcriterion			\
			-lpthread			\
			-ldl

CXXFLAGS += $(ZIA_INC) $(LIB_INC) --coverage

ZIA_OBJ =	$(ZIA_SRC:.cpp=.o)

TESTS_OBJ =	$(TESTS_SRC:.cpp=.o)

MOD_PHP_SRC = ../modules/Php/Php.cpp

MOD_FILE_SRC = ../modules/File/File.cpp

MOD_PROXY_SRC = ../modules/Proxy/Proxy.cpp

CONAN := $(shell conan config home)

FOLDER := $(shell pwd)

NO_TEST := $(shell dirname $(FOLDER))

all: $(ZIA_OBJ) $(TESTS_OBJ) $(MOD_PHP_OBJ) $(MOD_FILE_OBJ) $(MOD_PROXY_OBJ)
	@$(CXX) $(ZIA_OBJ) $(TESTS_OBJ) -o unit-tests $(LIB_DIR) $(LDFLAGS) --coverage
	@mkdir -p ../build/lib
	@$(CXX) -fPIC -shared $(MOD_PHP_SRC) $(LIB_DIR) $(LDFLAGS) $(CXXFLAGS) -o ../build/lib/libphp.so
	@$(CXX) -fPIC -shared $(MOD_FILE_SRC) $(LIB_DIR) $(LDFLAGS) $(CXXFLAGS) -o ../build/lib/libfile.so
	@$(CXX) -fPIC -shared $(MOD_PROXY_SRC) $(LIB_DIR) $(LDFLAGS) $(CXXFLAGS) -o ../build/lib/libproxy.so

coverage:
	lcov -c -d .. --output-file Coverage
	lcov --remove Coverage -o Coverage '$(CONAN)/*'
	lcov --remove Coverage -o Coverage '/usr/*'
	lcov --remove Coverage -o Coverage '$(FOLDER)/*'
	mkdir -p html
	genhtml Coverage --output-directory html

clean:
	$(RM) $(ZIA_OBJ) $(TESTS_OBJ)
	find .. -name "*.gcda" -delete
	find .. -name "*.gcno" -delete
	$(RM) ../build/lib/libphp.so
	$(RM) ../build/lib/libfile.so
	$(RM) ../build/lib/libproxy.so
	$(RM) -rf html
	$(RM) Coverage

fclean: clean
	$(RM) unit-tests

re: fclean all

.PHONY:		all fclean re clean coverage
