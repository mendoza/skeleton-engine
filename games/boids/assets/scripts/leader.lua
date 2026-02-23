local steer_force = 300
local friction = 2.0

function on_update(self, dt)
	local pos = self:get(Position)
	local vel = self:get(Velocity)

	local dx, dy = 0, 0
	if input:held("move_up") then
		dy = dy - 1
	end
	if input:held("move_down") then
		dy = dy + 1
	end
	if input:held("move_left") then
		dx = dx - 1
	end
	if input:held("move_right") then
		dx = dx + 1
	end

	if dx ~= 0 and dy ~= 0 then
		local len = math.sqrt(dx * dx + dy * dy)
		dx = dx / len
		dy = dy / len
	end

	vel.vel.x = vel.vel.x + dx * steer_force * dt
	vel.vel.y = vel.vel.y + dy * steer_force * dt

	local damp = math.max(0, 1.0 - friction * dt)
	vel.vel.x = vel.vel.x * damp
	vel.vel.y = vel.vel.y * damp

	local speed = math.sqrt(vel.vel.x * vel.vel.x + vel.vel.y * vel.vel.y)
	if speed > max_speed then
		vel.vel.x = vel.vel.x / speed * max_speed
		vel.vel.y = vel.vel.y / speed * max_speed
	end

	pos.pos.x = pos.pos.x + vel.vel.x * dt
	pos.pos.y = pos.pos.y + vel.vel.y * dt
end
