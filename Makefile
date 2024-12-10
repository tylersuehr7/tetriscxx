SOURCE_DIR=.
BUILD_DIR=./.build
EXECUTABLE=tetris

build:
	cmake -S ${SOURCE_DIR} -B ${BUILD_DIR}
	cmake --build ${BUILD_DIR}
	
clean:
	rm -rf ${BUILD_DIR} ${EXECUTABLE}

run:
	./${BUILD_DIR}/${EXECUTABLE}
