/*
* Copyright (c) 2025 Chris Giles
*
* Permission to use, copy, modify, distribute and sell this software
* and its documentation for any purpose is hereby granted without fee,
* provided that the above copyright notice appear in all copies.
* Chris Giles makes no representations about the suitability
* of this software for any purpose.
* It is provided "as is" without express or implied warranty.
*/

#include "solver.h"

Rigid::Rigid(Solver* solver, float2 size, float density, float friction, float3 position, float3 velocity)
    : solver(solver), forces(0), next(0), position(position), velocity(velocity), prevVelocity(velocity), size(size), friction(friction)
{
    // Add to linked list
    next = solver->bodies;
    solver->bodies = this;

    // Compute mass properties and bounding radius
    mass = size.x * size.y * density;
    moment = mass * dot(size, size) / 12.0f;
    radius = length(size * 0.5f);
}

Rigid::~Rigid()
{
    // Remove from linked list
    Rigid** p = &solver->bodies;
    while (*p != this)
        p = &(*p)->next;
    *p = next;
}

bool Rigid::constrainedTo(Rigid* other) const
{
    // Check if this body is constrained to the other body
    for (Force* f = forces; f != 0; f = f->next)
        if ((f->bodyA == this && f->bodyB == other) || (f->bodyA == other && f->bodyB == this))
            return true;
    return false;
}

void Rigid::draw()
{
    // Draw as a thin 3D box for a simple 3D look
    float depth = 0.5f;
    float3 pos = { position.x, position.y, 0.0f };
    float3 rot = { 0.0f, 0.0f, position.z };

    float3 v0 = transform(pos, rot, { -size.x * 0.5f, -size.y * 0.5f, -depth });
    float3 v1 = transform(pos, rot, {  size.x * 0.5f, -size.y * 0.5f, -depth });
    float3 v2 = transform(pos, rot, {  size.x * 0.5f,  size.y * 0.5f, -depth });
    float3 v3 = transform(pos, rot, { -size.x * 0.5f,  size.y * 0.5f, -depth });
    float3 v4 = transform(pos, rot, { -size.x * 0.5f, -size.y * 0.5f,  depth });
    float3 v5 = transform(pos, rot, {  size.x * 0.5f, -size.y * 0.5f,  depth });
    float3 v6 = transform(pos, rot, {  size.x * 0.5f,  size.y * 0.5f,  depth });
    float3 v7 = transform(pos, rot, { -size.x * 0.5f,  size.y * 0.5f,  depth });

    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
    // Front face
    glVertex3f(v4.x, v4.y, v4.z);
    glVertex3f(v5.x, v5.y, v5.z);
    glVertex3f(v6.x, v6.y, v6.z);
    glVertex3f(v7.x, v7.y, v7.z);
    // Back face
    glVertex3f(v0.x, v0.y, v0.z);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(v0.x, v0.y, v0.z);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(v4.x, v4.y, v4.z);
    glVertex3f(v5.x, v5.y, v5.z);
    glVertex3f(v6.x, v6.y, v6.z);
    glVertex3f(v7.x, v7.y, v7.z);
    glEnd();
}
