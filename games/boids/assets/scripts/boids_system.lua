local leader_e
local orbit_t      = 0
local orbit_cx     = 0
local orbit_cy     = 0
local orbit_radius = 220
local orbit_speed  = 0.6

function on_init()
	math.randomseed(os.time())

	for _ = 1, 1000 do
		local e = world:create()
		e:emplace(Position)
		e:emplace(Velocity)
		local pos = e:get(Position)
		pos.pos.x = math.random(0, math.floor(world_w))
		pos.pos.y = math.random(0, math.floor(world_h))
		local angle = math.random() * math.pi * 2
		local vel = e:get(Velocity)
		vel.vel.x = math.cos(angle) * 60
		vel.vel.y = math.sin(angle) * 60
	end

	leader_e = world:create()
	leader_e:emplace(Position)
	leader_e:emplace(Velocity)
	leader_e:emplace(Leader)
	orbit_cx = world_w / 2
	orbit_cy = world_h / 2
	local lpos = leader_e:get(Position)
	lpos.pos.x = orbit_cx
	lpos.pos.y = orbit_cy
end

function on_update(dt)
	orbit_t = orbit_t + dt * orbit_speed
	local lp = leader_e:get(Position)
	local lv = leader_e:get(Velocity)
	lp.pos.x = orbit_cx + math.cos(orbit_t) * orbit_radius
	lp.pos.y = orbit_cy + math.sin(orbit_t) * orbit_radius
	lv.vel.x = -math.sin(orbit_t) * 900
	lv.vel.y = math.cos(orbit_t) * 900
end
