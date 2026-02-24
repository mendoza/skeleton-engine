local speed = 150
local last_dir = "down"

function on_update(self, dt)
  local pos  = self:get(Position)
  local anim = self:get(AnimationPlayer)

  local dx, dy = 0, 0
  if input:held("move_up")    then dy = dy - 1 end
  if input:held("move_down")  then dy = dy + 1 end
  if input:held("move_left")  then dx = dx - 1 end
  if input:held("move_right") then dx = dx + 1 end

  if dx ~= 0 and dy ~= 0 then
    local len = math.sqrt(dx * dx + dy * dy)
    dx = dx / len
    dy = dy / len
  end

  pos.pos.x = pos.pos.x + dx * speed * dt
  pos.pos.y = pos.pos.y + dy * speed * dt

  if     dx < 0 then last_dir = "left"
  elseif dx > 0 then last_dir = "right"
  elseif dy < 0 then last_dir = "up"
  elseif dy > 0 then last_dir = "down"
  end

  local clip = ((dx ~= 0 or dy ~= 0) and "walk_" or "idle_") .. last_dir
  anim:play(clip)
  anim:update(dt)
end
