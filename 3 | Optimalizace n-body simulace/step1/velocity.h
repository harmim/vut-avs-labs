/*
 * Architektura procesoru (ACH 2016)
 * Projekt c. 1 (nbody)
 * Login: xlogin00
 */

#ifndef __VELOCITY_H__
#define __VELOCITY_H__

#include <cstdlib>
#include <cstdio>

/* struktura castice (hmotneho bodu) */
struct t_particle
{
    float pos_x;
    float pos_y;
    float pos_z;
    float vel_x;
    float vel_y;
    float vel_z;
    float weight;
};

/* vektor zmeny rychlosti */
struct t_velocity
{
    float x;
    float y;
    float z;
};

/* gravitacni konstanta */
constexpr float G = 6.67384e-11f;

/* collision threshold */
constexpr float COLLISION_DISTANCE = 0.01f;

void calculate_gravitation_velocity(const t_particle* p1, const t_particle* p2, t_velocity* vel);

void calculate_collision_velocity(const t_particle* p1, const t_particle* p2, t_velocity* vel);

/*
void calculate_gravitation_velocity(
    const float &p1_pos_x,
    const float &p1_pos_y,
    const float &p1_pos_z,
    const float &p1_vel_x,
    const float &p1_vel_y,
    const float &p1_vel_z,
    const float &p1_weight,
    const float &p2_pos_x,
    const float &p2_pos_y,
    const float &p2_pos_z,
    const float &p2_vel_x,
    const float &p2_vel_y,
    const float &p2_vel_z,
    const float &p2_weight,
    float &vel_x,
    float &vel_y,
    float &vel_z
);

void calculate_collision_velocity(
    const float &p1_pos_x,
    const float &p1_pos_y,
    const float &p1_pos_z,
    const float &p1_vel_x,
    const float &p1_vel_y,
    const float &p1_vel_z,
    const float &p1_weight,
    const float &p2_pos_x,
    const float &p2_pos_y,
    const float &p2_pos_z,
    const float &p2_vel_x,
    const float &p2_vel_y,
    const float &p2_vel_z,
    const float &p2_weight,
    float &vel_x,
    float &vel_y,
    float &vel_z
);
*/


#endif /* __VELOCITY_H__ */
