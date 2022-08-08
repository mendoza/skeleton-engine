function getRandom(m, n)
    local rand = math.random(m, n)
    return rand
end

actorParams = {
    graphicComponent = {
        spriteName = "bones",
        spriteFilepath = "assets/spritesheets/player.png",
        animated = true,
        animation = {
            switchTime = 1 / 10,
            rows = 4,
            cols = 3,
            initialImage = {
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
        spriteOrientation = {
            x = 1,
            y = 0
        }
    },
    physicsComponent = {
        speed = 100,
        weight = 10
    }
}


shouldRun = true
hasBeenPrint = true
startingX = 600 / 2
startTimeStamp = -1
function update(dt)
    if (hasBeenPrint) then
        hasBeenPrint = false
        startTimeStamp = os.time()
        logger:Log("Start! x: " .. position.x)
    end

    if (shouldRun) then
        if (actor:position().x < 600) then
            local speed = actorParams["physicsComponent"]["speed"] * dt;
            actor:playAnimation("walking")
            actor:forward(speed)
        else
            actor:stop()
            actor:playAnimation("idle")
            local time = os.time() - startTimeStamp
            local distance = math.abs(startingX - position.x)
            logger:Log(
                "Tooked: " .. time .. "s! finished walking: " .. distance .. "px! speed: " .. (distance / time) ..
                    " px/s")
            shouldRun = false
        end
    end
end

function  handle_input(key_stroke)
    
end
