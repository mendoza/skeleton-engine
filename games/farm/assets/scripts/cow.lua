local speed = 30
local move_timer = math.random() * 3
local sound_timer = math.random(3, 8) * 10
local dx, dy = 0, 0
local last_dir = "down"

local function pick_direction()
	-- 0,0 is weighted twice so cows stand still fairly often
	local choices = {
		{ 1,  0 },
		{ -1, 0 },
		{ 0,  1 },
		{ 0,  -1 },
		{ 0,  0 },
		{ 0,  0 },
	}
	local c = choices[math.random(#choices)]
	dx, dy = c[1], c[2]
	move_timer = math.random(2, 4) + math.random()
end

function on_init(self)
	pick_direction()
end

function on_update(self, dt)
	local pos  = self:get(Position)
	local anim = self:get(AnimationPlayer)

	-- movement
	move_timer = move_timer - dt
	if move_timer <= 0 then
		pick_direction()
	end

	pos.pos.x = pos.pos.x + dx * speed * dt
	pos.pos.y = pos.pos.y + dy * speed * dt

	-- track direction and pick walk vs idle clip
	if dx < 0 then
		last_dir = "left"
	elseif dx > 0 then
		last_dir = "right"
	elseif dy < 0 then
		last_dir = "up"
	elseif dy > 0 then
		last_dir = "down"
	end

	local clip = (dx ~= 0 or dy ~= 0) and "walk_" .. last_dir or "idle_" .. last_dir
	anim:play(clip)
	anim:update(dt)

	-- random moo
	sound_timer = sound_timer - dt
	if sound_timer <= 0 then
		audio:play("moo")
		sound_timer = math.random(5, 12) + math.random()
	end
end
