bl_info = {
    "name": "AVBD Physics",
    "author": "Chris Giles",
    "version": (1, 1),
    "blender": (2, 80, 0),
    "location": "View3D > Tool Shelf",
    "description": "Run AVBD 2D physics inside Blender",
    "category": "Physics",
}

import bpy
import avbd

_solver = None
_rigids = {}


def _update_scene(scene):
    global _solver
    if not _solver:
        return
    _solver.step()
    for name, rigid in _rigids.items():
        obj = bpy.data.objects.get(name)
        if obj:
            p = rigid.position
            obj.location.x = p[0]
            obj.location.y = p[1]
            obj.rotation_euler.z = p[2]


def start_simulation(context):
    global _solver, _rigids
    _solver = avbd.Solver()
    avbd.scene_ground(_solver)
    _rigids = {}
    for obj in context.selected_objects:
        size = (obj.dimensions.x, obj.dimensions.y)
        pos = (obj.location.x, obj.location.y, obj.rotation_euler.z)
        rigid = avbd.Rigid(_solver, size, 1.0, 0.5, pos)
        _rigids[obj.name] = rigid
    if _update_scene not in bpy.app.handlers.frame_change_pre:
        bpy.app.handlers.frame_change_pre.append(_update_scene)


def stop_simulation():
    if _update_scene in bpy.app.handlers.frame_change_pre:
        bpy.app.handlers.frame_change_pre.remove(_update_scene)
    global _solver
    _solver = None
    _rigids.clear()


class AVBD_OT_start(bpy.types.Operator):
    bl_idname = "avbd.start"
    bl_label = "Start AVBD Simulation"

    def execute(self, context):
        start_simulation(context)
        return {'FINISHED'}


class AVBD_OT_stop(bpy.types.Operator):
    bl_idname = "avbd.stop"
    bl_label = "Stop AVBD Simulation"

    def execute(self, context):
        stop_simulation()
        return {'FINISHED'}


class AVBD_PT_panel(bpy.types.Panel):
    bl_label = "AVBD 2D"
    bl_idname = "AVBD_PT_panel"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = 'AVBD'

    def draw(self, context):
        layout = self.layout
        layout.operator(AVBD_OT_start.bl_idname, text="Start")
        layout.operator(AVBD_OT_stop.bl_idname, text="Stop")


classes = (AVBD_OT_start, AVBD_OT_stop, AVBD_PT_panel)


def register():
    for cls in classes:
        bpy.utils.register_class(cls)


def unregister():
    stop_simulation()
    for cls in reversed(classes):
        bpy.utils.unregister_class(cls)

if __name__ == "__main__":
    register()
