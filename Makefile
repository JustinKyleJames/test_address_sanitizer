shared.so: shared.cpp
	/opt/irods-externals/clang13.0.0-0/bin/clang++ -g -shared -nostdinc++ -lc++abi -DCOMPILER_RT_BUILD_SHARED_ASAN=ON -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -O1 -shared-libasan -fPIC -Wall -ansi -pedantic -o shared.so shared.cpp -Wl,-rpath,/opt/irods-externals/clang-runtime13.0.0-0/lib 

dlopen: dlopen.cpp
	/opt/irods-externals/clang13.0.0-0/bin/clang++ -g -o dlopen -lc++abi -nostdinc++ -Wall -ansi -pedantic dlopen.cpp -ldl -Wl,-rpath,/opt/irods-externals/clang-runtime13.0.0-0/lib

rundlopen: dlopen shared.so
	ASAN_SYMBOLIZER_PATH=/opt/irods-externals/clang13.0.0-0/bin/llvm-symbolizer LD_PRELOAD=/opt/irods-externals/clang13.0.0-0/lib/clang/13.0.0/lib/linux/libclang_rt.asan-x86_64.so ./dlopen

cleandlopen:
	rm dlopen shared.so

#export LD_LIBRARY_PATH=/opt/irods-externals/clang13.0.0-0/lib/clang/13.0.0/lib/linux
