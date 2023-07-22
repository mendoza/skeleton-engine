actor_parameters = {
    graphic_parameters = {
        sprite_name = "bones_sprite_sheet",
        sprite_filepath = "assets/spritesheets/player.png",
        animated = true,
        animation = {
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

direction = vector_2f.new(0.0, 0.0)
speed = 0
function on_update(dt)
    direction = actor:get_direction()
    new_direction = vector_2f.new(direction.x * (speed * dt), direction.y * (speed * dt))
    actor:move(new_direction)
end

function handle_input(event)
    if event.type == skeleton.event_type.key_pressed then
        direction = actor:get_direction()
        if event.key.code == skeleton.keyboard["right"] then
            if (direction.x < 0) then
                actor:flip_horizontal()
            end
            actor:play_animation("walking", true)
            speed = 100
        elseif event.key.code == skeleton.keyboard["left"] then
            if (direction.x > 0) then
                actor:flip_horizontal()
            end
            actor:play_animation("walking", true)
            speed = 100
        elseif event.key.code == skeleton.keyboard["space"] then
            actor:play_animation("punching", false)
            speed = 0
        end
    elseif event.type == skeleton.event_type.key_released then
        if event.key.code == skeleton.keyboard["right"] or event.key.code == skeleton.keyboard["left"] then
            speed = 0
            actor:play_animation("idle", false)
        end
    end
end
