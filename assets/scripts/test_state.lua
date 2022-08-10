function getRandom(m, n)
    local rand = math.random(m, n)
    return rand
end

actor_params = {
    graphic_component = {
        sprite_name = "bones",
        sprite_filepath = "assets/spritesheets/player.png",
        animated = true,
        animation = {
            switch_time = 1 / 10,
            rows = 4,
            cols = 3,
            initial_image = {
                row = 0,
                col = 0
            },
            animations = {{
                name = "idle",
                row = 0
            }, {
                name = "walking",
                row = 1
            }, {
                name = "punching",
                row = 2
            }, {
                name = "dying",
                row = 3
            }}
        },
        scale = {
            width = 3,
            height = 3
        },
        origin = {
            x = 30,
            y = 40
        },
        position = {
            x = 600 / 2,
            y = 800 / 2
        },
        sprite_orientation = {
            x = 1,
            y = 0
        }
    },
    physics_component = {
        speed = 10,
        weight = 10
    }
}

shouldRun = true
hasBeenPrint = true
startingX = 600 / 2
startTimeStamp = -1
function on_update(dt)
    if (hasBeenPrint) then
        hasBeenPrint = false
        startTimeStamp = os.time()
        console:log("Start! x: " .. actor:position().x)
    end

    if (shouldRun) then
        if (actor:position().x < 600) then
            local speed = actor_params["physics_component"]["speed"] * dt;
            actor:play_animation("walking")
            actor:forward(speed)
        else
            actor:play_animation("idle")
            local time = os.time() - startTimeStamp
            local distance = math.abs(startingX - actor:position().x)
            console:log(
                "Tooked: " .. time .. "s! finished walking: " .. distance .. "px! speed: " .. (distance / time) ..
                    " px/s")
            shouldRun = false
        end
    end
end

function on_key_pressed(key_code)
    if key_code == 72 then
        speed = actor_params["physics_component"]["speed"]
        actor:play_animation("walking")
        actor:forward(speed)
    elseif key_code == 71 then
        speed = actor_params["physics_component"]["speed"]
        actor:play_animation("walking")
        actor:backward(speed)
    end
end

function on_key_released(key_code)
    actor:play_animation("idle")
    actor:stop()
end

