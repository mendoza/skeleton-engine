local t = 0
local radius = 220
local cx, cy = 1920, 1080
local orbit_speed = 0.6
local move_speed = 90000

function on_update(self, dt)
  t = t + dt * orbit_speed

  local pos = self:get(Position)
  local vel = self:get(Velocity)

  if pos then
    pos.pos.x = cx + math.cos(t) * radius
    pos.pos.y = cy + math.sin(t) * radius
  end

  if vel then
    vel.vel.x = -math.sin(t) * move_speed
    vel.vel.y =  math.cos(t) * move_speed
  end
end
