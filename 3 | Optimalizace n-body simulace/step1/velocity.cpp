/*
 * Architektura procesoru (ACH 2016)
 * Projekt c. 1 (nbody)
 * Login: xlogin00
 */

#include <cmath>
#include <cfloat>
#include "velocity.h"

/**
 * @breef   Funkce vypocte rychlost kterou teleso p1 ziska vlivem gravitace p2->
 */
void calculate_gravitation_velocity(
        const t_particle* p1,
        const t_particle* p2,
        t_velocity* vel
)
{
    float r, dx, dy, dz;
    float vx, vy, vz;

    dx = p1->pos_x - p2->pos_x;
    dy = p1->pos_y - p2->pos_y;
    dz = p1->pos_z - p2->pos_z;

    r = sqrt(dx*dx + dy*dy + dz*dz);

    //Version 1: Straightforwardly derived from physics formulae
    //Force
    float F = -G * (p1->weight) * (p2->weight) / (r * r + FLT_MIN);
    //normalize per dimension
    float nx = F * dx/ (r + FLT_MIN);
    float ny = F * dy/ (r + FLT_MIN);
    float nz = F * dz/ (r + FLT_MIN);

    vx = nx * DT / p1->weight;
    vy = ny * DT / p1->weight;
    vz = nz * DT / p1->weight;


    //Version 2: Algebraically optimized for CPU (reducing the number of divisions)

//    float r3, G_dt_r3, Fg_dt_m2_r;
//
//    r3 = r * r * r + FLT_MIN;
//
//    // Fg*dt/m1/r = G*m1*m2*dt / r^3 / m1 = G*dt/r^3 * m2
//    G_dt_r3 = -G * DT / r3;
//    Fg_dt_m2_r = G_dt_r3 * p2->weight;
//
//    // vx = - Fx*dt/m2 = - Fg*dt/m2 * dx/r = - Fg*dt/m2/r * dx
//    vx = Fg_dt_m2_r * dx;
//    vy = Fg_dt_m2_r * dy;
//    vz = Fg_dt_m2_r * dz;

    vel->x += (r > COLLISION_DISTANCE) ? vx : 0.0f;
    vel->y += (r > COLLISION_DISTANCE) ? vy : 0.0f;
    vel->z += (r > COLLISION_DISTANCE) ? vz : 0.0f;
}

/**
 * @breef   Funkce vypocte rozdil mezi rychlostmi pred a po kolizi telesa p1 do telesa p2->
 * @details Vyjdeme ze zakonu o zachovani kineticke energie a zakonu o zachovani hybnosti.
 *
 *          Hybnost:
 *              v1*m1 + v2*m2 = v1f * m1 + v2f * m2
 *          Kineticka energie:
 *              1/2 * (m1 * v1^2) + 1/2 * (m2 * v2^2) = 1/2 * (m1 * v1f^2) + 1/2 * (m2 * v2f^2)
 *
 *          Kde: v1 a v2 jsou aktualni rychlosti teles p1 a p2,
 *               m1 a m2 jsou hmotnosti teles p1 a p2,
 *               v1f a v2f jsou rychlosti po kolizi teles p1 a p2->
 *
 *          Vyjadrenim v1f lze ziskat vzorec:
 *              v1f = (m1*v1 - m2*v1 + 2*m2*v2)/(m1+m2)
*/
void calculate_collision_velocity(
  const t_particle* p1,
  const t_particle* p2,
  t_velocity* vel
)
{
    float r, dx, dy, dz;
    float vx, vy, vz;

    dx = p1->pos_x - p2->pos_x;
    dy = p1->pos_y - p2->pos_y;
    dz = p1->pos_z - p2->pos_z;

    r = sqrtf(dx*dx + dy*dy + dz*dz);


    vx = ((p1->weight* p1->vel_x - p2->weight *p1->vel_x + 2* p2->weight* p2->vel_x) /
            (p1->weight + p2->weight)) - p1->vel_x ;
    vy = ((p1->weight* p1->vel_y - p2->weight *p1->vel_y + 2* p2->weight* p2->vel_y) /
            (p1->weight + p2->weight)) - p1->vel_y ;
    vz = ((p1->weight* p1->vel_z - p2->weight *p1->vel_z + 2* p2->weight* p2->vel_z) /
            (p1->weight + p2->weight)) - p1->vel_z ;


    // jedna se o rozdilne ale blizke prvky
    if (r > 0.0f && r < COLLISION_DISTANCE) {
        vel->x += vx;
        vel->y += vy;
        vel->z += vz;
    }
}
