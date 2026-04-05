#include <raylib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

#define THICKNESS 20
#define LENGTH 150
#define TREE_COLOR RAYWHITE
#define START_ANGLE 0
#define DEPTH 20

#define OFFSET 0.7f
#define OFFSET_ANGLE (20 * DEG2RAD)

void draw_tree(Vector2 start, float len, float angle, float thickness, int tree_depth)
{
    if (tree_depth == 0)
        return;

    Vector2 end;
    end.x = start.x + len * sinf(angle);
    end.y = start.y - len * cosf(angle);

    DrawLineEx(start, end, thickness, TREE_COLOR);

    float n_len = len * OFFSET;
    float n_thickness = thickness * OFFSET;

    draw_tree(end, n_len, angle + OFFSET_ANGLE, n_thickness, tree_depth - 1);
    draw_tree(end, n_len, angle - OFFSET_ANGLE, n_thickness, tree_depth - 1);
}

void draw_square(Vector2 origin, float size, float angle, int depth)
{
    if (depth == 0 || size < 2)
        return;

    Vector2 p1 = origin;

    Vector2 p2 = {
        p1.x + cosf(angle) * size,
        p1.y - sinf(angle) * size
    };

    Vector2 p3 = {
        p2.x - sinf(angle) * size,
        p2.y - cosf(angle) * size
    };

    Vector2 p4 = {
        p1.x - sinf(angle) * size,
        p1.y - cosf(angle) * size
    };

    DrawLineV(p1, p2, WHITE);
    DrawLineV(p2, p3, WHITE);
    DrawLineV(p3, p4, WHITE);
    DrawLineV(p4, p1, WHITE);

    float newSize = size * 0.7f;

    draw_square(p4, newSize, angle + PI / 4, depth - 1);
    draw_square(p3, newSize, angle - PI / 4, depth - 1);
}

int main()
{
    InitWindow(WIDTH, HEIGHT, "Fractal Trees");
    SetTargetFPS(60);

    Vector2 start = { WIDTH / 2.0f - 40, HEIGHT - 100 };

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            draw_square(start, 80, 0, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
