#include "raylib.h"
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Player structure
struct Player {
    Rectangle rect;
    float speed;
};

// Bullet structure
struct Bullet {
    Rectangle rect;
    float speed;
};

// Enemy structure
struct Enemy {
    Rectangle rect;
    float speed;
};

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple Space Game");
    SetTargetFPS(60);

    Player player = {{SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT - 40, 40, 20}, 5.0f};
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    int score = 0;

    while (!WindowShouldClose()) {
        // Move player
        if (IsKeyDown(KEY_LEFT)) player.rect.x -= player.speed;
        if (IsKeyDown(KEY_RIGHT)) player.rect.x += player.speed;

        // Shoot bullets
        if (IsKeyPressed(KEY_SPACE)) {
            bullets.push_back({{player.rect.x + 18, player.rect.y, 5, 10}, 6.0f});
        }

        // Move bullets
        for (auto &bullet : bullets) bullet.rect.y -= bullet.speed;

        // Spawn & move enemies
        if (GetRandomValue(0, 100) < 2) {
            enemies.push_back({{(float)GetRandomValue(0, SCREEN_WIDTH - 40), 0, 40, 20}, 2.0f});
        }
        for (auto &enemy : enemies) enemy.rect.y += enemy.speed;

        // Check collisions
        for (auto &bullet : bullets) {
            for (auto &enemy : enemies) {
                if (CheckCollisionRecs(bullet.rect, enemy.rect)) {
                    score += 10;
                    bullet.rect.y = -10; // Move off-screen (removes it later)
                    enemy.rect.y = SCREEN_HEIGHT + 10; // Move off-screen (removes it later)
                }
            }
        }

        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleRec(player.rect, BLUE);
        for (auto &bullet : bullets) DrawRectangleRec(bullet.rect, RED);
        for (auto &enemy : enemies) DrawRectangleRec(enemy.rect, GREEN);
        DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
