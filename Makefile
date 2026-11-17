.PHONY: build run test clean format

build:
	cmake -S . -B build
	cmake --build build

run: build
	./build/raytracer

test: build
	cd build && ctest --output-on-failure

clean:
	rm -rf build

format:
	find src tests -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' \) -print0 | xargs -0 clang-format -i
