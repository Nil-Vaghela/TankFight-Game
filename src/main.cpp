#include "bn_core.h"
#include "bn_fixed_point.h"
#include "bn_keypad.h"
#include "bn_math.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_items_tank_player_final.h"
#include "bn_sprite_items_tank_ai_final.h"
#include "bn_sprite_items_bullet_final.h"
#include "common_variable_8x16_sprite_font.h"
#include "bn_string.h"
#include "bn_vector.h"
#include "bn_random.h"
#include "bn_sound_items.h" // Include sound items header

struct Bullet
{
    bn::sprite_ptr sprite;
    bn::fixed_point velocity;

    Bullet(const bn::sprite_ptr& _sprite, const bn::fixed_point& _velocity) :
        sprite(_sprite), velocity(_velocity) {}
};

struct AiTank
{
    bn::sprite_ptr tank;
    int direction;

    AiTank(const bn::sprite_ptr& _tank, int _direction) : tank(_tank), direction(_direction) {}
};

// Function for the start screen
void start_screen(bn::sprite_text_generator& text_generator)
{
    bn::vector<bn::sprite_ptr, 32> start_screen_text;

    // Generate text for the start screen
    text_generator.set_center_alignment();
    text_generator.generate(0, -20, "OG TANK GAME", start_screen_text);
    text_generator.generate(0, 10, "PRESS START TO PLAY", start_screen_text);

    // Wait for the player to press Start
    while (!bn::keypad::start_pressed())
    {
        bn::core::update();
    }

    // Clear the text after the start screen
    start_screen_text.clear();
}

// Function for transitioning to the second level
void level_two_transition(bn::sprite_text_generator& text_generator)
{
    bn::vector<bn::sprite_ptr, 32> transition_text;
    text_generator.set_center_alignment();
    text_generator.generate(0, 0, "LEVEL 2", transition_text);

    for (int i = 0; i < 120; ++i) // Display message for 2 seconds
    {
        bn::core::update();
    }

    transition_text.clear();
}

int main()
{
    bn::core::init();
    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    text_generator.set_left_alignment(); // Set alignment for gameplay text

    // Call the start screen
    start_screen(text_generator);

    // Player tank
    bn::sprite_ptr player_tank = bn::sprite_items::tank_player_final.create_sprite(0, 60);

    // AI tanks
    bn::vector<AiTank, 2> ai_tanks; // Supports up to 2 AI tanks for level 2
    ai_tanks.push_back(AiTank(bn::sprite_items::tank_ai_final.create_sprite(0, -60), 1)); // First AI tank

    // Bullets
    bn::vector<Bullet, 8> player_bullets;
    bn::vector<Bullet, 8> ai_bullets;

    // Scores
    int player_hits = 0;
    int ai_hits = 0;

    // Hit count text sprites
    bn::vector<bn::sprite_ptr, 32> player_hits_text_sprites;
    bn::vector<bn::sprite_ptr, 32> ai_hits_text_sprites;

    // Adjusted positions for text
    int player_hits_text_x = -80;
    int player_hits_text_y = -50;
    int ai_hits_text_x = -80;
    int ai_hits_text_y = 50;

    // Generate initial text
    text_generator.generate(player_hits_text_x, player_hits_text_y, "Player Hits: 0", player_hits_text_sprites);
    text_generator.generate(ai_hits_text_x, ai_hits_text_y, "AI Hits: 0", ai_hits_text_sprites);

    bool second_level = false; // Track if the game is in the second level

    while (true)
    {
        // Player movement
        if (bn::keypad::left_held() && player_tank.x() > -112)
        {
            player_tank.set_x(player_tank.x() - 1);
        }
        if (bn::keypad::right_held() && player_tank.x() < 112)
        {
            player_tank.set_x(player_tank.x() + 1);
        }

        // Player shooting
        if (bn::keypad::a_pressed())
        {
            player_bullets.push_back(Bullet(bn::sprite_items::bullet_final.create_sprite(player_tank.x(), player_tank.y() - 10),
                                            bn::fixed_point(0, -2)));
        }

        // AI movement and shooting
        static bn::random random;
        for (auto& ai_tank : ai_tanks)
        {
            // Move AI tanks
            ai_tank.tank.set_x(ai_tank.tank.x() + ai_tank.direction);
            if (ai_tank.tank.x() > 112 || ai_tank.tank.x() < -112)
            {
                ai_tank.direction *= -1;
            }

            // AI shooting
            if (random.get_int(50) == 0)
            {
                ai_bullets.push_back(Bullet(bn::sprite_items::bullet_final.create_sprite(ai_tank.tank.x(), ai_tank.tank.y() + 10),
                                            bn::fixed_point(0, 2)));
            }
        }

        // Move player bullets and check collision with AI tanks
        for (int i = 0; i < player_bullets.size();)
        {
            Bullet& bullet = player_bullets[i];
            bullet.sprite.set_position(bullet.sprite.x() + bullet.velocity.x(),
                                       bullet.sprite.y() + bullet.velocity.y());

            // Check collision with any AI tank
            bool bullet_hit = false;
            for (auto& ai_tank : ai_tanks)
            {
                if (bn::abs(bullet.sprite.x() - ai_tank.tank.x()) < 16 &&
                    bn::abs(bullet.sprite.y() - ai_tank.tank.y()) < 16)
                {
                    bullet_hit = true;
                    ai_hits++;
                    break;
                }
            }

            if (bullet_hit)
            {
                bn::sound_items::bomb.play(1); // Play sound on tank hit
                player_bullets.erase(player_bullets.begin() + i);

                // Update AI hit count dynamically
                ai_hits_text_sprites.clear();
                bn::string<32> ai_hits_string = "AI Hits: ";
                ai_hits_string.append(bn::to_string<4>(ai_hits));
                text_generator.generate(ai_hits_text_x, ai_hits_text_y, ai_hits_string, ai_hits_text_sprites);

                if (!second_level && ai_hits >= 5)
                {
                    // Transition to second level
                    second_level = true;
                    ai_hits = 0; // Reset AI hits for the second level
                    level_two_transition(text_generator);

                    // Add one more AI tank (for a total of 2 AI tanks in level 2)
                    ai_tanks.push_back(AiTank(bn::sprite_items::tank_ai_final.create_sprite(-40, -60), 1));
                }
                else if (second_level && ai_hits >= 15)
                {
                    // Player wins after 10 hits in level 2
                    bn::vector<bn::sprite_ptr, 32> text_sprites;
                    text_generator.generate(-50, 0, "YOU WIN!", text_sprites);

                    for (int j = 0; j < 200; ++j)
                    {
                        bn::core::update();
                    }
                    return 0;
                }
                continue;
            }

            // Remove bullets out of bounds
            if (bullet.sprite.y() < -80)
            {
                player_bullets.erase(player_bullets.begin() + i);
            }
            else
            {
                ++i;
            }
        }

        // Move AI bullets and check collision with player
        for (int i = 0; i < ai_bullets.size();)
        {
            Bullet& bullet = ai_bullets[i];
            bullet.sprite.set_position(bullet.sprite.x() + bullet.velocity.x(),
                                       bullet.sprite.y() + bullet.velocity.y());

            if (bn::abs(bullet.sprite.x() - player_tank.x()) < 16 &&
                bn::abs(bullet.sprite.y() - player_tank.y()) < 16)
            {
                bn::sound_items::bomb.play(1); // Play sound on player hit
                ai_bullets.erase(ai_bullets.begin() + i);
                player_hits++;

                // Update player hit count dynamically
                player_hits_text_sprites.clear();
                bn::string<32> player_hits_string = "Player Hits: ";
                player_hits_string.append(bn::to_string<4>(player_hits));
                text_generator.generate(player_hits_text_x, player_hits_text_y, player_hits_string, player_hits_text_sprites);

                if (player_hits >= 5)
                {
                    // AI wins
                    bn::vector<bn::sprite_ptr, 32> text_sprites;
                    text_generator.generate(-50, 0, "YOU LOSE!", text_sprites);

                    for (int j = 0; j < 200; ++j)
                    {
                        bn::core::update();
                    }
                    return 0;
                }
                continue;
            }

            // Remove bullets out of bounds
            if (bullet.sprite.y() > 80)
            {
                ai_bullets.erase(ai_bullets.begin() + i);
            }
            else
            {
                ++i;
            }
        }

        // Update game
        bn::core::update();
    }
}
