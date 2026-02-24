return {
  texture = "assets/farm rpg assets/Farm Animals/Female Cow Brown.png",
  frame_w = 32,
  frame_h = 32,
  animations = {
    idle_left  = { row = 0, frames = 1, fps = 1 },
    idle_right = { row = 0, frames = 1, fps = 1, flip = "horizontal" },
    idle_down  = { row = 1, frames = 1, fps = 1 },
    idle_up    = { row = 2, frames = 1, fps = 1 },
    walk_left  = { row = 0, frames = 4, fps = 8 },
    walk_right = { row = 0, frames = 4, fps = 8, flip = "horizontal" },
    walk_down  = { row = 1, frames = 4, fps = 8 },
    walk_up    = { row = 2, frames = 4, fps = 8 },
  },
}
