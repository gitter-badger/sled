// Simple checkerboard animation.

#include <types.h>
#include <matrix.h>
#include <timers.h>
#include <random.h>
#include <stddef.h>

#define FPS 2
#define FRAMETIME (T_SECOND / FPS)
#define FRAMES (RANDOM_TIME * FPS)

static int modno;
static int frame;
static ulong nexttick;

int init(int moduleno) {
	if (matrix_getx() < 2)
		return 1;
	if (matrix_gety() < 2)
		return 1;

	modno = moduleno;
	return 0;
}

RGB black = { .red = 0, .green = 0, .blue = 0 };
RGB white = { .red = 255, .green = 255, .blue = 255 };

int draw(int argc, char* argv[]) {
	if (frame == 0)
		nexttick = utime();

	matrix_clear();

	int mx = matrix_getx();
	int my = matrix_gety();

	int off1 = (frame + 0) % 2;
	int off2 = (off1 == 1) ? 0 : 1;

	int x;
	int y;
	for (y = 0; y < my; y += 2)
		for (x = off1; x < mx; x += 2)
			matrix_set(x, y, &white);
	for (y = 1; y < my; y += 2)
		for (x = off2; x < mx; x += 2)
			matrix_set(x, y, &white);

	matrix_render();
	if (frame >= FRAMES) {
		frame = 0;
		return 1;
	}
	frame++;
	nexttick += FRAMETIME;
	timer_add(nexttick, modno, 0, NULL);
	return 0;
}

int deinit() {
	return 0;
}
