actor_parameters = {
    graphic_parameters = {
        sprite_name = "bones_sprite_sheet",
        sprite_filepath = "assets/spritesheets/player.png",
        animated = true,
        animation = {
            switch_time = 1,
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
should_move = false
is_punching = false
update_count = 0
function on_update(dt)
    if should_move and not is_punching then
        local speed = actor_parameters.physics_parameters.speed
        direction = actor:get_direction()
        new_direction = vector_2f.new(direction.x * (speed * dt), direction.y * (speed * dt))
        actor:move(new_direction)
        actor:play_animation("walking", true)
    end

    if not should_move and not is_punching then
        actor:play_animation("idle", true)
    end

    if is_punching then
        is_punching = false
    end

end

function print_vector(vect)
    print("(" .. vect.x .. ", " .. vect.y .. ")")
end

function handle_input(event)
    if event.type == skeleton.event_type.key_pressed then
        direction = actor:get_direction()
        if event.key.code == skeleton.keyboard["right"] then
            if (direction.x < 0) then
                actor:flip_horizontal()
            end
            should_move = true
        elseif event.key.code == skeleton.keyboard["left"] then
            if (direction.x > 0) then
                actor:flip_horizontal()
            end
            should_move = true
        elseif event.key.code == skeleton.keyboard["space"] then
            is_punching = true
            actor:play_animation("punching", false)
        end
    elseif event.type == skeleton.event_type.key_released then
        should_move = false
    end
end
