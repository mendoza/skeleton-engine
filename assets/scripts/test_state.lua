actor_parameters = {
    graphic_parameters = {
        sprite_name = "bones_sprite_sheet",
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
    physics_parameters = {
        speed = 100,
        weight = 10
    }
}

speed = 0
direction = 0
isPunching = false
function on_update(dt)
    if (speed ~= 0) then
        if direction == 1 then
            actor:forward(speed * dt)
        elseif direction == -1 then
            actor:backward(speed * dt)
        end
    end
end

function handle_input(event)
    if event.type == skeleton.event_type.key_pressed then
        if event.key.code == skeleton.keyboard["right"] then
            speed = actor_parameters.physics_parameters.speed
            if (direction == -1) then
                actor:flip_horizontal()
            end
            direction = 1
            actor:play_animation("walking")
        elseif event.key.code == skeleton.keyboard["left"] then
            speed = actor_parameters.physics_parameters.speed
            if (direction == 1) then
                actor:flip_horizontal()
            end
            direction = -1
            actor:play_animation("walking")
        end
    elseif event.type == skeleton.event_type.key_released then
        if event.key.code == skeleton.keyboard["space"] and ~isPunching then
            speed = 0
            isPunching = true
            actor:play_animation("punching")
        else
            actor:play_animation("idle")
            speed = 0
            actor:stop()
        end
        isPunching = false
    end
end
