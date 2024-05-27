#include <kinc/audio1/audio.h>
#include <kinc/graphics1/graphics.h>
#include <kinc/image.h>
#include <kinc/input/keyboard.h>
#include <kinc/input/mouse.h>
#include <kinc/io/filereader.h>
#include <kinc/math/core.h>
#include <kinc/system.h>

#include "GraphicsHelper.h"
#include "Memory.h"
#include "ObjLoader.h"

#define WIDTH 512
#define HEIGHT 512

double start_time;
struct Mesh* mesh;

kinc_image_t image;

void update(void* data) {
	float t = (float)(kinc_time() - start_time);

	kinc_g1_begin();
	clear(0.0f, 0.0f, 0.0f);

	// Add some nice transformations
	for (int i = 0; i < mesh->num_faces; ++i) {
		int i1 = mesh->indices[i * 3 + 0];
		int i2 = mesh->indices[i * 3 + 1];
		int i3 = mesh->indices[i * 3 + 2];

		float x1 = mesh->vertices[i1 * 5 + 0];
		float y1 = -mesh->vertices[i1 * 5 + 1];
		float z1 = mesh->vertices[i1 * 5 + 2];
		float u1 = mesh->vertices[i1 * 5 + 3];
		float v1 = mesh->vertices[i1 * 5 + 4];

		float x2 = mesh->vertices[i2 * 5 + 0];
		float y2 = -mesh->vertices[i2 * 5 + 1];
		float z2 = mesh->vertices[i2 * 5 + 2];
		float u2 = mesh->vertices[i2 * 5 + 3];
		float v2 = mesh->vertices[i2 * 5 + 4];

		float x3 = mesh->vertices[i3 * 5 + 0];
		float y3 = -mesh->vertices[i3 * 5 + 1];
		float z3 = mesh->vertices[i3 * 5 + 2];
		float u3 = mesh->vertices[i3 * 5 + 3];
		float v3 = mesh->vertices[i3 * 5 + 4];

		// Draw the triangle
		float draw_scale = 128;
		draw_triangle(
			x1 * draw_scale + WIDTH / 2, y1 * draw_scale + HEIGHT / 2, z1, u1, v1,
			x2 * draw_scale + WIDTH / 2, y2 * draw_scale + HEIGHT / 2, z2, u2, v2,
			x3 * draw_scale + WIDTH / 2, y3 * draw_scale + HEIGHT / 2, z3, u3, v3);
	}

	kinc_g1_end();
}

void key_down(int code, void* data) {
	if (code == KINC_KEY_LEFT) {
		// ...
	}
}

void key_up(int code, void* data) {
	if (code == KINC_KEY_LEFT) {
		// ...
	}
}

void mouse_move(int window, int x, int y, int movementX, int movementY, void* data) {
	// ...
}

void mouse_press(int window, int button, int x, int y, void* data) {
	// ...
}

void mouse_release(int window, int button, int x, int y, void* data) {
	// ...
}

void shade_pixel(int x, int y, float z, float u, float v) {
	/************************************************************************/
	/* Exercise 4: Practical Task                                           */
	/************************************************************************/
	// Use the passed values to draw a nice pixel using kinc_g1_set_pixel(x, y, ...).
	// Implement z-buffering
	// Use read_pixel() to read image data, which is returned in the reference parameters.
	// The texture is provided in the image "image" (tiger-atlas.jpg in the Deployment-folder)
	kinc_g1_set_pixel(x, y, 1.0f, 0.0f, 0.0f);
}

int kickstart(int argc, char** argv) {
	kinc_init("Exercise 4", WIDTH, HEIGHT, NULL, NULL);

	kinc_g1_init(WIDTH, HEIGHT);
	kinc_set_update_callback(update, NULL);

	start_time = kinc_time();

	memory_init();
	mesh = load_obj("tiger.obj");
	uint8_t* memory = malloc(10 * 1024 * 1024);
	kinc_image_init_from_file(&image, memory, "tiger-atlas.jpg");

	kinc_keyboard_set_key_down_callback(key_down, NULL);
	kinc_keyboard_set_key_up_callback(key_up, NULL);
	kinc_mouse_set_move_callback(mouse_move, NULL);
	kinc_mouse_set_press_callback(mouse_press, NULL);
	kinc_mouse_set_release_callback(mouse_release, NULL);

	kinc_start();

	return 0;
}
