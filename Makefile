# define libraries
ifeq ($(shell uname),Darwin)
LIB = -DMAC -framework OPENGL -framework GLUT
else
LIB = -lGL -lGLU -lglut
endif
LIB2 = libim/libim.a jpeg/libjpeg.a

# define makefile targets
CC = g++ -Wall -Wno-deprecated-declarations -O3
BIN = balls balls2 balls3 balls4 bezier bitmap building building2 building3 clip cube cube2 cube3 curve disk gasket2d gasket3d gouraud lagrange line_split line_test mandelbrot mandelbrot2 object object2 object3 object4 office office2 office3 office4 pong rectangles render render2 render3 square square2 surface surface2 surface3 surface4 texture texture2 texture3 texture4 texture5 tree whack_a_mole

all: $(LIB2) $(BIN)


clean: 
	/bin/rm -f $(LIB2) $(BIN)

jpeg/libjpeg.a:
	cd jpeg;make;cd ..

libim/libim.a:
	cd libim;make;cd ..

balls: balls.cpp shading.cpp
	$(CC) -o balls balls.cpp $(LIB)

balls2: balls2.cpp shading.cpp
	$(CC) -o balls2 balls2.cpp $(LIB)

balls3: balls3.cpp shading.cpp
	$(CC) -o balls3 balls3.cpp $(LIB)

balls4: balls4.cpp shading.cpp
	$(CC) -o balls4 balls4.cpp $(LIB)

bezier: bezier.cpp
	$(CC) -o bezier bezier.cpp $(LIB)

bitmap: bitmap.cpp
	$(CC) -o bitmap bitmap.cpp $(LIB)

building: building.cpp
	$(CC) -o building building.cpp $(LIB)

building2: building2.cpp
	$(CC) -o building2 building2.cpp $(LIB)

building3: building3.cpp
	$(CC) -o building3 building3.cpp $(LIB)

clip: clip.cpp
	$(CC) -o clip clip.cpp $(LIB)

cube: cube.cpp
	$(CC) -o cube cube.cpp $(LIB)

cube2: cube2.cpp
	$(CC) -o cube2 cube2.cpp $(LIB)

cube3: cube3.cpp
	$(CC) -o cube3 cube3.cpp $(LIB)

curve: curve.cpp
	$(CC) -o curve curve.cpp $(LIB)

disk: disk.cpp
	$(CC) -o disk disk.cpp $(LIB)

gasket2d: gasket2d.cpp
	$(CC) -o gasket2d gasket2d.cpp $(LIB)

gasket3d: gasket3d.cpp
	$(CC) -o gasket3d gasket3d.cpp $(LIB)

gouraud: gouraud.cpp
	$(CC) -o gouraud gouraud.cpp $(LIB)

lagrange: lagrange.cpp
	$(CC) -o lagrange lagrange.cpp $(LIB)

line_split: line_split.cpp
	$(CC) -o line_split line_split.cpp $(LIB)

line_test: line_test.cpp timer.cpp
	$(CC) -o line_test line_test.cpp timer.cpp $(LIB)

mandelbrot: mandelbrot.cpp
	$(CC) -o mandelbrot mandelbrot.cpp $(LIB)

mandelbrot2: mandelbrot2.cpp
	$(CC) -o mandelbrot2 mandelbrot2.cpp $(LIB)

object: object.cpp
	$(CC) -o object object.cpp $(LIB)

object2: object2.cpp
	$(CC) -o object2 object2.cpp $(LIB)

object3: object3.cpp
	$(CC) -o object3 object3.cpp $(LIB)

object4: object4.cpp shading.cpp
	$(CC) -o object4 object4.cpp $(LIB)

office: office.cpp
	$(CC) -o office office.cpp $(LIB)

office2: office2.cpp
	$(CC) -o office2 office2.cpp $(LIB)

office3: office3.cpp
	$(CC) -o office3 office3.cpp $(LIB)

office4: office4.cpp
	$(CC) -o office4 office4.cpp $(LIB)

pong: pong.cpp
	$(CC) -o pong pong.cpp $(LIB)

rectangles: rectangles.cpp
	$(CC) -o rectangles rectangles.cpp $(LIB)

render: render.cpp
	$(CC) -o render render.cpp $(LIB)

render2: render2.cpp
	$(CC) -o render2 render2.cpp $(LIB)

render3: render3.cpp
	$(CC) -o render3 render3.cpp $(LIB)

square: square.cpp
	$(CC) -o square square.cpp $(LIB)

square2: square2.cpp
	$(CC) -o square2 square2.cpp $(LIB)

surface: surface.cpp
	$(CC) -o surface surface.cpp $(LIB)

surface2: surface2.cpp
	$(CC) -o surface2 surface2.cpp $(LIB)

surface3: surface3.cpp shading.cpp
	$(CC) -o surface3 surface3.cpp $(LIB)

surface4: surface4.cpp shading.cpp
	$(CC) -o surface4 surface4.cpp $(LIB)

texture: texture.cpp
	$(CC) -o texture texture.cpp $(LIB)

texture2: texture2.cpp
	$(CC) -o texture2 texture2.cpp $(LIB)

texture3: texture3.cpp
	$(CC) -o texture3 texture3.cpp $(LIB) $(LIB2)

texture4: texture4.cpp
	$(CC) -o texture4 texture4.cpp $(LIB) $(LIB2)

texture5: texture5.cpp
	$(CC) -o texture5 texture5.cpp $(LIB) $(LIB2)

tree: tree.cpp
	$(CC) -o tree tree.cpp $(LIB)

whack_a_mole: whack_a_mole.cpp timer.cpp
	$(CC) -o whack_a_mole whack_a_mole.cpp timer.cpp $(LIB)

