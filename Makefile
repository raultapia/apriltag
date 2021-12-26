default: deps apriltag
.PHONY: default deps apriltag apriltag_pybind install_apriltag

deps:
	@sudo apt-get install -y -qq \
		libeigen3-dev \
		libeigen3-doc \
		libopencv-* \
		python3-dev

apriltag:
	@git submodule init
	@git submodule update
	@make -s -C apriltag

pybind:
	@make -s -C apriltag_pybind

install_apriltag:
	@make -C apriltag -s install

install_pybind:
	@make -C apriltag_pybind -s install

clean:
	@make -C apriltag -s clean
	@make -C apriltag_pybind -s clean
