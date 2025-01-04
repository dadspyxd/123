#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include "config.h"

using std::max;
using std::min;
using std::sqrt;
using std::sin;
using std::exp;
using std::pow;

// Windows function implementations
DWORD GetTickCount64() { return 0; }
short GetAsyncKeyState(int key) { return 0; }
void Sleep(DWORD ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

// Class implementations
void enemy_scanner::update() {}
std::array<double, 2> enemy_scanner::find_closest_enemy_head(double x, double y, const char*) { 
    return {0, 0}; 
}
bool enemy_scanner::is_enemy_in_crosshair() { return false; }

void driver::move_mouse(double x, double y, int flags) {
    (void)x;
    (void)y;
    (void)flags;
}

driver& driver::get_instance() {
    static driver instance;
    return instance;
}

void stopwatch::update() {}
double stopwatch::get_elapsed() { return 0.0; }
extern bool render_menu;
extern int fps_target;
extern bool login_state;
extern bool aimbot_state;
extern int a1mb0tKey;
extern double aimbot_fov_x;
extern double aimbot_fov_y;
extern std::string color;
extern float last_target_time;
extern int aim_mode;
extern double aimbot_speed;
extern double sticky_strength;
extern double sensx;
extern double sensy;
extern double recoil_offset;
extern double head_offset;
extern bool humanization_enabled;
extern double micro_adjust_strength;
extern int micro_adjust_min;
extern int micro_adjust_max;
extern bool enable_curve;
extern double curve_strength;
extern bool enable_speed_randomization;
extern double speed_random_strength;
extern double linear_speed;
extern bool linear_constant_speed;
extern bool magnet_enabled;
extern int magnet_key;
extern double magnet_fov;
extern double magnet_smooth;
extern bool magnet_auto_shoot;
extern double magnet_delay_between_shots;
extern bool flick_state;
extern int flickKey;
extern double flick_delay;
extern int flick_mode;
extern bool flick_double_click;
extern int flick_smoothing;
extern bool silent_state;
extern int silentKey;
extern double silent_delay;
extern double silent_fov_x;
extern double silent_fov_y;
extern bool trigger_state;
extern int triggerKey;
extern int first_shoot_delay;
extern double trigger_fov;
extern double flick_fov_x;
extern double flick_fov_y;

// Global variables for aim assist
static double last_adjust_x = 0.0;
static double last_adjust_y = 0.0;
static double distance = 0.0; // Distance to target

void meain();  // Forward declaration

int main() {
    meain();
    return 0;
}

void meain() {
    system("cls");

    //ShowWindow(GetConsoleWindow(), SW_HIDE);
    render_menu = true;

    // Configurable target FPS with common Valorant refresh rates
    const int TARGET_FPS_OPTIONS[] = {60, 144, 240, 360};
    const int DEFAULT_TARGET_FPS = 144; // Most common competitive refresh rate
    
    // User-configurable target FPS (default to 144 if not set)
    static int target_fps = DEFAULT_TARGET_FPS;
    
    // Allow dynamic FPS adjustment through configuration
    auto it = std::find(std::begin(TARGET_FPS_OPTIONS), std::end(TARGET_FPS_OPTIONS), fps_target);
    if (it != std::end(TARGET_FPS_OPTIONS)) {
        target_fps = fps_target;
    }
    
    // Calculate frame timing with high precision
    const std::chrono::microseconds TPF(1000000 / target_fps);
    
    // Initialize timing control variables
    std::chrono::high_resolution_clock::time_point last_frame_time;
    double frame_time_accumulator = 0.0;
    const double FIXED_TIME_STEP = 1.0 / target_fps;
    
    // Initialize game components
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Reduced initial delay
    stopwatch s1lnt;
    stopwatch flck;
    stopwatch trgger;
    enemy_scanner en3myy;
    
    // Initialize frame timing
    last_frame_time = std::chrono::high_resolution_clock::now();

    while (true)
    {
        // Calculate frame timing
        auto current_time = std::chrono::high_resolution_clock::now();
        auto frame_duration = std::chrono::duration_cast<std::chrono::microseconds>(
            current_time - last_frame_time);
        last_frame_time = current_time;
        
        // Update frame accumulator
        frame_time_accumulator += frame_duration.count() / 1000000.0;
        
        // Process fixed time steps
        while (frame_time_accumulator >= FIXED_TIME_STEP) {
            // Main game logic
            if (login_state)
        {
            if (aimbot_state && GetAsyncKeyState(a1mb0tKey) < 0)
            {
                en3myy.update();
                auto enemy_h34D = en3myy.find_closest_enemy_head(aimbot_fov_x / 2, aimbot_fov_y / 2, color.c_str());

                if (enemy_h34D[0] != 0 || enemy_h34D[1] != 0) {
                    double moveX, moveY;
                    
                    // Update last target time
                    last_target_time = static_cast<float>(GetTickCount64());

                    if (aim_mode == 1) { // Enhanced Sticky aim with dynamic strength and acceleration
                        // Calculate base smoothing from aimbot speed
                        double baseSmoothing = (100.0 - aimbot_speed) / 100.0;
                        
                        // Calculate distance to target for dynamic stickiness
                        double distance = sqrt(enemy_h34D[0]*enemy_h34D[0] + enemy_h34D[1]*enemy_h34D[1]);
                        
                        // Dynamic factor increases stickiness when closer to target
                        // Using exponential falloff for more natural feeling
                        const double CLOSE_DISTANCE = 50.0; // Adjust based on Valorant's units
                        const double MIN_DYNAMIC_FACTOR = 1.0;
                        const double MAX_DYNAMIC_FACTOR = 3.0;
                        
                        double dynamicFactor;
                        if (distance < CLOSE_DISTANCE) {
                            // Exponential increase in stickiness as we get closer
                            double distanceRatio = distance / CLOSE_DISTANCE;
                            dynamicFactor = MIN_DYNAMIC_FACTOR + 
                                (MAX_DYNAMIC_FACTOR - MIN_DYNAMIC_FACTOR) * 
                                (1.0 - pow(distanceRatio, 2.0)); // Quadratic falloff
                        } else {
                            dynamicFactor = MIN_DYNAMIC_FACTOR;
                        }
                        
                        // Apply sticky strength with dynamic factor
                        double smoothing = baseSmoothing + 
                            (1.0 - baseSmoothing) * sticky_strength * dynamicFactor;

                        // Calculate raw movement values
                        double rawMoveX = enemy_h34D[0] * sensx * (1.0 - smoothing);
                        double rawMoveY = (enemy_h34D[1] + recoil_offset) * sensy * (1.0 - smoothing) + head_offset;
                        
                        // Calculate time-based acceleration factor
                        static std::chrono::high_resolution_clock::time_point lastAimTime;
                        auto currentTime = std::chrono::high_resolution_clock::now();
                        double elapsedTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(
                            currentTime - lastAimTime).count();
                        lastAimTime = currentTime;
                        
                        // Enhanced acceleration curve parameters
                        const double ACCEL_TIME_FACTOR = 0.012; // Slightly slower initial acceleration
                        const double DECEL_THRESHOLD = 7.5; // Increased threshold for earlier deceleration
                        const double MICRO_ADJUST_THRESHOLD = 2.0; // Very fine control threshold
                        
                        // Calculate acceleration factor with improved interpolation
                        double accelerationFactor;
                        if (distance > DECEL_THRESHOLD) {
                            // Smooth acceleration ramp using cubic ease-in
                            double normalizedTime = std::min(1.0, elapsedTimeMs / 1000.0);
                            accelerationFactor = normalizedTime * normalizedTime * normalizedTime;
                            accelerationFactor = 1.0 - exp(-ACCEL_TIME_FACTOR * accelerationFactor * elapsedTimeMs);
                        } else if (distance > MICRO_ADJUST_THRESHOLD) {
                            // Gradual deceleration zone with quadratic ease-out
                            double decelRatio = (distance - MICRO_ADJUST_THRESHOLD) / 
                                              (DECEL_THRESHOLD - MICRO_ADJUST_THRESHOLD);
                            double easeOut = 1.0 - (decelRatio * decelRatio);
                            accelerationFactor = 0.7 * easeOut * (1.0 - exp(-ACCEL_TIME_FACTOR * elapsedTimeMs));
                        } else {
                            // Micro-adjustment zone with linear precision
                            double microRatio = distance / MICRO_ADJUST_THRESHOLD;
                            accelerationFactor = 0.3 * microRatio * (1.0 - exp(-ACCEL_TIME_FACTOR * elapsedTimeMs));
                        }
                        
                        // Apply acceleration to movement
                        moveX = rawMoveX * accelerationFactor;
                        moveY = rawMoveY * accelerationFactor;
                    }
                    else if (aim_mode == 2) { // Linear aim
                        // Calculate direction vector
                        double dx = enemy_h34D[0] * sensx;
                        double dy = (enemy_h34D[1] + recoil_offset) * sensy + head_offset;
                        double length = sqrt(dx * dx + dy * dy);
                        
                        if (length > 0) {
                            // Normalize and apply speed
                            if (linear_constant_speed) {
                                // Constant speed regardless of distance
                                moveX = (dx / length) * linear_speed * (aimbot_speed / 50.0);
                                moveY = (dy / length) * linear_speed * (aimbot_speed / 50.0);
                            } else {
                                // Speed scales with distance
                                moveX = dx * linear_speed * (aimbot_speed / 100.0);
                                moveY = dy * linear_speed * (aimbot_speed / 100.0);
                            }
                        } else {
                            moveX = moveY = 0;
                        }
                    }
                    else { // Normal aim - simple speed-based aiming
                        // Simple speed calculation like before
                       moveX = enemy_h34D[0] * sensx * (((double)aimbot_speed / 190));
                       moveY = (enemy_h34D[1] + recoil_offset) * sensy * (((double)aimbot_speed / 190)) + head_offset;
                       driver::get_instance().move_mouse(moveX, moveY, 0x0);
                    }

                    // Enhanced humanization layer for Valorant's precise requirements
                    if (humanization_enabled && aim_mode != 0) { // Don't apply to normal mode
                        // Calculate base movement
                        double humanized_x = moveX;
                        double humanized_y = moveY;

                        // Enhanced micro-adjustments tuned specifically for Valorant's hitboxes
                        if (micro_adjust_strength > 0) {
                            static stopwatch micro_adjust;
                            static stopwatch dwell_timer;
                            static bool in_dwell = false;
                            static double last_overshoot_x = 0.0;
                            static double last_overshoot_y = 0.0;
                            
                            // Tighter adjustments for Valorant's precise hitboxes
                            const float VALORANT_SCALE = 0.45f; // Further reduced adjustment magnitude
                            const float DISTANCE_SCALE = std::max(0.3f, std::min(1.0f, static_cast<float>(distance) / 100.0f));
                            
                            if (!in_dwell && micro_adjust.get_elapsed() > (micro_adjust_min + (rand() % (micro_adjust_max - micro_adjust_min)))) {
                                // Even tighter bounds for Valorant's precise hitboxes
                                last_adjust_x = ((rand() % 100 - 50) / 2000.0f) *   // Increased denominator
                                    micro_adjust_strength * VALORANT_SCALE * DISTANCE_SCALE;
                                last_adjust_y = ((rand() % 100 - 50) / 2000.0f) * 
                                    micro_adjust_strength * VALORANT_SCALE * DISTANCE_SCALE;
                                
                                // Improved human-like overcompensation
                                if (rand() % 100 < 25) { // Reduced chance of overshooting (25%)
                                    // Calculate overshoot based on current speed
                                    double currentSpeed = sqrt(moveX*moveX + moveY*moveY);
                                    double overshootBase = 1.0 + (rand() % 15) / 100.0; // 1-15% overshoot
                                    double overshoot = overshootBase * (1.0 - std::min(1.0, currentSpeed / 10.0));
                                    
                                    last_overshoot_x = last_adjust_x * overshoot;
                                    last_overshoot_y = last_adjust_y * overshoot;
                                    
                                    // Apply overshoot with smoothing
                                    humanized_x += last_overshoot_x;
                                    humanized_y += last_overshoot_y;
                                    
                                    // Enter dwell state for recovery
                                    in_dwell = true;
                                    dwell_timer.update();
                                }
                                
                                micro_adjust.update();
                            }
                            
                            // Enhanced dwell behavior with dynamic duration
                            if (in_dwell) {
                                double dwellDuration = 10.0 + // Base dwell time
                                    (rand() % 15) + // Random component
                                    (sqrt(last_overshoot_x*last_overshoot_x + 
                                         last_overshoot_y*last_overshoot_y) * 50.0); // Scale with overshoot magnitude
                                
                                if (dwell_timer.get_elapsed() > dwellDuration) {
                                    in_dwell = false;
                                    // Smooth recovery from overshoot
                                    last_overshoot_x *= 0.5;
                                    last_overshoot_y *= 0.5;
                                }
                            }
                            
                            humanized_x += last_adjust_x;
                            humanized_y += last_adjust_y;
                        }

                        // Enhanced curve with dynamic amplitude
                        if (enable_curve) {
                            const float VALORANT_CURVE_SCALE = 0.25f; // Further reduced curve strength
                            const float CURVE_DISTANCE_SCALE = std::max(0.2f, std::min(1.0f, static_cast<float>(distance) / 150.0f));
                            
                            // Combine multiple frequencies for more natural movement
                            float curve = (
                                sin(GetTickCount64() * 0.001f) * 0.7f +
                                sin(GetTickCount64() * 0.002f) * 0.2f +
                                sin(GetTickCount64() * 0.004f) * 0.1f
                            ) * (curve_strength * VALORANT_CURVE_SCALE * CURVE_DISTANCE_SCALE);
                            
                            humanized_x += humanized_x * curve;
                            humanized_y += humanized_y * curve;
                        }

                        // Enhanced speed randomization with dynamic bounds
                        if (enable_speed_randomization) {
                            const float VALORANT_SPEED_SCALE = 0.6f; // Tighter speed variation
                            const float SPEED_DISTANCE_SCALE = std::max(0.4f, std::min(1.0f, static_cast<float>(distance) / 120.0f));
                            
                            // Smoother random factor calculation
                            float random_base = (float)(rand() % 100 - 50) / 800.0f; // Further reduced range
                            float random_factor = 1.0f + 
                                random_base * speed_random_strength * 
                                VALORANT_SPEED_SCALE * SPEED_DISTANCE_SCALE;
                            
                            humanized_x *= random_factor;
                            humanized_y *= random_factor;
                        }

                        // Update movement values with smoothing
                        const float SMOOTHING_FACTOR = 0.8f;
                        moveX = moveX * (1.0f - SMOOTHING_FACTOR) + humanized_x * SMOOTHING_FACTOR;
                        moveY = moveY * (1.0f - SMOOTHING_FACTOR) + humanized_y * SMOOTHING_FACTOR;
                    }
                    
                    // Apply final movement
                    driver::get_instance().move_mouse(moveX, moveY, 0x0);
                    
                    // Add small delay for smoother movement only in advanced modes
                    if (aim_mode != 0 && rand() % 100 < 15) {
                        Sleep(rand() % 3 + 1);
                    }

                    continue;
                }
            }
            else if (magnet_enabled && GetAsyncKeyState(magnet_key) < 0)
            {
                en3myy.update();
                auto enemy_head = en3myy.find_closest_enemy_head(magnet_fov, magnet_fov, color.c_str());

                if (enemy_head[0] != 0 || enemy_head[1] != 0)
                {
                    double moveX = enemy_head[0] * sensx * (((double)magnet_smooth / 100.0));
                    double moveY = enemy_head[1] * sensy * (((double)magnet_smooth / 100.0));
                    driver::get_instance().move_mouse(moveX, moveY, 0x0);
                }

                if (magnet_auto_shoot && en3myy.is_enemy_in_crosshair() && trgger.get_elapsed() > magnet_delay_between_shots)
                {
                    driver::get_instance().move_mouse(0, 0, 0x1);
                    Sleep(50);
                    driver::get_instance().move_mouse(0, 0, 0x2);
                    trgger.update();
                }
                continue;
            }
            else if (flick_state && GetAsyncKeyState(flickKey) < 0 && flck.get_elapsed() > flick_delay)
            {
                en3myy.update();
                auto e34y_head = en3myy.find_closest_enemy_head(flick_fov_x / 2, flick_fov_y / 2, color.c_str());
                if (e34y_head[0] != 0 || e34y_head[1] != 0) {
                    // Calculate base movement with enhanced precision
                    float moveX = (e34y_head[0]) * sensx;
                    float moveY = (e34y_head[1]) * sensy + head_offset;

                    switch (flick_mode) {
                        case 0: // Pure Instant flick - Maximum power
                            {
                                // Direct, powerful flick
                                driver::get_instance().move_mouse(moveX, moveY, 0x1);
                                
                                // Optional double click
                                if (flick_double_click) {
                                    Sleep(5);
                                    driver::get_instance().move_mouse(0, 0, 0x2);
                                    Sleep(5);
                                    driver::get_instance().move_mouse(0, 0, 0x1);
                                }
                                driver::get_instance().move_mouse(0, 0, 0x2);
                            }
                            break;

                        case 1: // Precise flick
                            {
                                int steps = max(1, flick_smoothing);
                                float stepX = moveX / steps;
                                float stepY = moveY / steps;
                                
                                for (int i = 0; i < steps; i++) {
                                    driver::get_instance().move_mouse(stepX, stepY, (i == 0) ? 0x1 : 0x0);
                                    Sleep(1);
                                }
                                
                                driver::get_instance().move_mouse(0, 0, 0x2);
                            }
                            break;
                    }
                    
                    flck.update();
                    continue;
                }
            }
            else if (silent_state && GetAsyncKeyState(silentKey) < 0 && s1lnt.get_elapsed() > silent_delay)
            {
                en3myy.update();
                auto eem3nemy_head = en3myy.find_closest_enemy_head(silent_fov_x / 2, silent_fov_y / 2, color.c_str());
                if (eem3nemy_head[0] != 0 || eem3nemy_head[1] != 0) {
                    eem3nemy_head[0] = (eem3nemy_head[0]) * sensx;
                    eem3nemy_head[1] = (eem3nemy_head[1]) * sensy + head_offset;

                    driver::get_instance().move_mouse(eem3nemy_head[0], eem3nemy_head[1], 0x1);
                    driver::get_instance().move_mouse(0, 0, 1);
                    Sleep(50);
                    driver::get_instance().move_mouse(0, 0, 0x2);
                    driver::get_instance().move_mouse(eem3nemy_head[0] * -1, eem3nemy_head[1] * -1, 0x2);
                    s1lnt.update();
                    continue;
                }
            }
            else if (trigger_state && GetAsyncKeyState(triggerKey) < 0)
            {
                en3myy.update();
                auto enemy_head = en3myy.find_closest_enemy_head(trigger_fov, trigger_fov, color.c_str());
                if (enemy_head[0] != 0 || enemy_head[1] != 0) {
                    if (GetAsyncKeyState(triggerKey) & 0x8000)
                        Sleep(first_shoot_delay);
                    driver::get_instance().move_mouse(0, 0, 0x1);
                    Sleep(50);
                    driver::get_instance().move_mouse(0, 0, 0x2);
                    continue;
                }
            }
        }

            frame_time_accumulator -= FIXED_TIME_STEP;
        }
        
        // Calculate and apply frame timing
        auto end_time = std::chrono::high_resolution_clock::now();
        auto processing_time = std::chrono::duration_cast<std::chrono::microseconds>(
            end_time - current_time);
        auto sleep_duration = TPF - processing_time;
        
        // Ensure consistent frame timing
        if (sleep_duration.count() > 0) {
            std::this_thread::sleep_for(sleep_duration);
        } else {
            // If we're running behind, yield to prevent CPU overload
            std::this_thread::yield();
        }
    }
}
