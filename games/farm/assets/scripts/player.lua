local speed = 150

function on_update(self, dt)
  local pos = self:get(Position)

  local dx, dy = 0, 0
  if input:held("move_up")    then dy = dy - 1 end
  if input:held("move_down")  then dy = dy + 1 end
  if input:held("move_left")  then dx = dx - 1 end
  if input:held("move_right") then dx = dx + 1 end

  -- normalize diagonal movement so it doesn't go faster
  if dx ~= 0 and dy ~= 0 then
    local len = math.sqrt(dx * dx + dy * dy)
    dx = dx / len
    dy = dy / len
  end

  pos.pos.x = pos.pos.x + dx * speed * dt
  pos.pos.y = pos.pos.y + dy * speed * dt
end
