all:
	g++ closest.cpp -o closest -lm -O2

clean:
	rm -f closest;
