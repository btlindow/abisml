#ifndef ABISML_H
#define ABISML_H

#define ABISML_STATE(s)            \
    static void s##_routine(void); \
    static abisml_state s##_state = {.routine = s##_routine};
#define ABISML_ROUTINE(r) static void r##_routine(void)
#define ABISML_EDGE(f, t) {.from = &f##_state, .to = &t##_state},
#define ABISML_EDGES(n, e) static abisml_edge n[] = {e};
#define ABISML_MACHINE(n, s, e) static abisml_machine n = {.state = &s##_state, .num_edges = sizeof(e) / sizeof(abisml_edge), .edges = e};
#define ABISML_RUN(m) abisml_machine_run(&m);
#define ABISML_TRANSITION(m, t) abisml_machine_transition(&m, &t##_state); \
    return;

typedef struct abisml_state
{
    void (*routine)(void);
} abisml_state;

typedef struct abisml_edge
{
    abisml_state *from;
    abisml_state *to;
} abisml_edge;

typedef struct abisml_machine
{
    abisml_state *state;
    int num_edges;
    abisml_edge* edges;
} abisml_machine;


void abisml_machine_run(abisml_machine *m)
{
    while (m->state != NULL)
    {
        m->state->routine();
    }
}

void abisml_machine_transition(abisml_machine *m, abisml_state *s)
{
    abisml_edge *edge = m->edges;
    for (int i = 0; i < m->num_edges; i++, edge++)
    {
        if (edge->from == m->state && edge->to == s)
        {
            m->state = s;
            return;
        }
    }
}

#endif
