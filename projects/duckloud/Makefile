sources := $(wildcard source/*.cpp)
test_source := $(wildcard test/*.cpp)
test := $(test_source:%.cpp=%.o)
headers := $(wildcard include/*.h)
objs := $(sources:source/%.cpp=obj/%.o)
depends:= $(objs:%.o=%.d) $(test:%.o=%.d)
exes:= $(test:test/%.o=bin/%.out)

CPPFLAGS = -std=c++11 -g -Wall -Wextra -Wpedantic -I./include 
DEPFLAGS = -MT $@ -MMD -MP -MF ${@:%.o=%.d}
LDLIBS = -pthread -ldl -rdynamic ##-lconfig++
# ============================================================================= 
all:
	@echo "sources: ${sources}"
	@echo "objects: ${objs}"
	@echo "test_source: ${test_source}"
	@echo "test: ${test}"
	@echo "exes: ${exes}"
	$(MAKE) ${exes}
# all: $(exes)
# $(objs) $(test)
# ============================================================================= 
# bin/handleton_test.out: test/handleton_test.o
# bin/logger_test.out: test/logger_test.o obj/logger.obj
# bin/factory_test.out: test/factory_test.o obj/factory.o

# ============================================================================= 
$(exes): bin/%.out: test/%.o lib 
	g++ $< obj/duckloud_lib.a $(LDLIBS) -o $@
		
release: CPPFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -O3 -I./include 
release: 
	@echo "sources: ${sources}"
	@echo "objects: ${objs}"
	@echo "test_source: ${test_source}"
	@echo "test: ${test}"
	@echo "exes: ${exes}"
	$(MAKE) ${exes}

lib: ${objs}
	ar cr obj/duckloud_lib.a $^

# ============================================================================= 
obj/%.o: source/%.cpp
	g++ -c $(CPPFLAGS) $(DEPFLAGS) $< -o $@

test/%.o: test/%.cpp
	g++ -c $(CPPFLAGS) $(DEPFLAGS) $< -o $@

# ============================================================================= 
.PHONY: clean
clean:
	rm $(objs) $(depends) $(test) $(exes) obj/duckloud_lib.a 

-include $(objs:.o=.d) 
