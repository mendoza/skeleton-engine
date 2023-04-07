actor_parameters = {
    graphic_parameters = {
        sprite_name = "bones_sprite_sheet",
        sprite_filepath = "assets/spritesheets/player.png",
        animated = true,
        animation = {
            switch_time = 1 / 60,
            rows = 4,
            cols = 3,
            initial_image = {
                row = 0,
                col = 0
            },
            animations = {{
                name = "idle",
                row = 0,
                should_loop = true
            }, {
                name = "walking",
                row = 1,
                should_loop = true
            }, {
                name = "punching",
                row = 2,
                should_loop = false
            }, {
                name = "dying",
                row = 3,
                should_loop = true
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
        actor:play_animation("punching", false)
    end

end

function tprint (tbl, indent)
    if not indent then indent = 0 end
    for k, v in pairs(tbl) do
      formatting = string.rep("  ", indent) .. k .. ": "
      if type(v) == "table" then
        print(formatting)
        tprint(v, indent+1)
      else
        print(formatting .. v)
      end
    end
  end


function handle_input(event)
    if event.type == skeleton.event_type.key_pressed then
        direction = actor:get_direction()
        tprint(skeleton)
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
        end
    elseif event.type == skeleton.event_type.key_released then
        should_move = false
    end
end
