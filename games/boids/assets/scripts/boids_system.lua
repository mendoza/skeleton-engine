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
end
