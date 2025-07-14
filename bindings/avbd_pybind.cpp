#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "source/solver.h"
#include "source/scenes.h"

namespace py = pybind11;

static py::tuple get_pos(const Rigid& r) {
    return py::make_tuple(r.position.x, r.position.y, r.position.z);
}

static void set_pos(Rigid& r, py::tuple t) {
    r.position = float3{t[0].cast<float>(), t[1].cast<float>(), t[2].cast<float>()};
}

PYBIND11_MODULE(avbd, m) {
    py::class_<Solver>(m, "Solver")
        .def(py::init<>())
        .def("clear", &Solver::clear)
        .def("default_params", &Solver::defaultParams)
        .def("step", &Solver::step);

    py::class_<Rigid>(m, "Rigid")
        .def(py::init<Solver*, float2, float, float, float3, float3>(),
             py::arg("solver"), py::arg("size"), py::arg("density"), py::arg("friction"),
             py::arg("position"), py::arg("velocity") = float3{0,0,0})
        .def_property("position", get_pos, set_pos);

    py::class_<Joint>(m, "Joint")
        .def(py::init<Solver*, Rigid*, Rigid*, float2, float2, float3, float, float>(),
             py::arg("solver"), py::arg("bodyA"), py::arg("bodyB"), py::arg("rA"), py::arg("rB"),
             py::arg("stiffness"), py::arg("motor") = 0.0f, py::arg("fracture") = INFINITY);

    py::class_<Spring>(m, "Spring")
        .def(py::init<Solver*, Rigid*, Rigid*, float2, float2, float, float>(),
             py::arg("solver"), py::arg("bodyA"), py::arg("bodyB"), py::arg("rA"), py::arg("rB"),
             py::arg("stiffness"), py::arg("rest") = -1.0f);

    m.def("scene_ground", &sceneGround);
    m.def("scene_empty", &sceneEmpty);
}
