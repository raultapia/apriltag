default: deps build

deps:
	@sudo apt-get install -y -qq \
		libeigen3-dev \
		libeigen3-doc \
		libopencv-* \
		python3-dev

build:
	@mkdir -p build && cd build && cmake .. && make

install:
	@cd build && sudo make install

clean:
	@rm -rf build
