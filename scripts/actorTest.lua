function getRandom(m, n)
    local rand = math.random(m, n)
    return rand
end
actorTable = {
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

    physics = {
        speed = 300
    }

}
shouldRun = true
hasBeenPrint = true
startingX = actorTable.graphicComponent.position.x
function update(dt)

    if (hasBeenPrint) then
        hasBeenPrint = false
        logger:Log("X: " .. position.x)
    end

    if (shouldRun) then
        if (position.x < 600) then
            local speed = actorTable["physics"]["speed"] * dt;
            playAnimation("walking")
            forward(speed)
        else
            stop()
            playAnimation("idle")
            logger:Log("Finished walking: " .. (math.abs(startingX - position.x)) .. "px !")
            shouldRun = false
        end
    end

end
