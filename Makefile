default: deps build python
.PHONY: default deps build python install

deps:
	@sudo apt-get install -y -qq python3-dev libopencv-*

build:
	@git submodule init
	@git submodule update
	@mkdir -p build \
		&& cd build \
		&& cmake .. \
		&& make

python:
	@cd python && mkdir -p build && cd build && cmake .. && make

install:
	cd build && sudo make install
