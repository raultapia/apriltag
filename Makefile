default: deps apriltag apriltag_pybind
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

apriltag_pybind:
	@make -s -C apriltag_pybind
