
CXXFLAGS       :=-shared -fPIC -DCPU_ONLY -std=c++11 -MMD -MP 

INCLUDEFLAGS   =-I"$(GENN_PATH)/lib/include"

all: librunner.so

-include librunner.d
librunner.so: runner.cc librunner.d
	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) $(GENN_PATH)/lib/src/sparseUtils.cc runner.cc -o librunner.so

%.d: ;

clean:
	rm -f librunner.so librunner.d
